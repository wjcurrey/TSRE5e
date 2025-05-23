/*  This file is part of TSRE5.
 *
 *  TSRE5 - train sim game engine and MSTS/OR Editors. 
 *  Copyright (C) 2016 Piotr Gadecki <pgadecki@gmail.com>
 *
 *  Licensed under GNU General Public License 3.0 or later. 
 *
 *  See LICENSE.md or https://www.gnu.org/licenses/gpl.html
 */

#include "SignalObj.h"
#include "SFile.h"
#include "ShapeLib.h"
#include "GLMatrix.h"
#include <math.h>
#include "ParserX.h"
#include <QDebug>
#include "TrackItemObj.h"
#include "TDB.h"
#include "TRitem.h"
#include "SigCfg.h"
#include "SignalShape.h"
#include "Game.h"
#include "TS.h"
#include "TRnode.h"
#include "ErrorMessagesLib.h"
#include "ErrorMessage.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

SignalObj::SignalObj() {
    this->shape = -1;
    this->loaded = false;
    //pointer3d = new TrackItemObj();
    //pointer3d->setMaterial(1,0,0);
    //pointer3dSelected = new TrackItemObj();
    //pointer3dSelected->setMaterial(1,0.5,0.5);
}

void SignalObj::loadingFixes(){
    if(Game::useOnlyPositiveQuaternions){
        if(qDirection[3] < 0){
            Quat::makePositive(qDirection);
            ErrorMessage *e = new ErrorMessage(
                    ErrorMessage::Type_Info, 
                    ErrorMessage::Source_Editor, 
                    QString("Fixed negative quaternion in tile ") + QString::number(x) + " " + QString::number(y) + " : " + QString::number(typeID) 
                    );
            ErrorMessagesLib::PushErrorMessage(e);
            setModified();
        }            
    }
}

SignalObj::SignalObj(const SignalObj& o) : WorldObj(o) {
    subObjSelected = o.subObjSelected;
    signalSubObj = o.signalSubObj;
    signalUnits = o.signalUnits; // 
    for(int i = 0; i < 32; i++){
        signalUnit[i].enabled = o.signalUnit[i].enabled;
        signalUnit[i].head = o.signalUnit[i].head;
        signalUnit[i].itemId = o.signalUnit[i].itemId;
        signalUnit[i].tdbId = o.signalUnit[i].tdbId;
    }

    selectionValue = o.selectionValue;
    signalShape = o.signalShape;
}

WorldObj* SignalObj::clone(){
    return new SignalObj(*this);
}

SignalObj::~SignalObj() {
}

void SignalObj::load(int x, int y) {
    this->shape = Game::currentShapeLib->addShape(resPath +"/"+ fileName);
    this->shapePointer = Game::currentShapeLib->shape[this->shape];
        
    this->x = x;
    this->y = y;
    this->position[2] = -this->position[2];
    this->qDirection[2] = -this->qDirection[2];
    this->loaded = true;
    this->size = -1;
    this->skipLevel = 1;
    this->modified = false;
    
    if(Game::trackDB != NULL)
        this->signalShape = Game::trackDB->sigCfg->signalShape[fileName];
    setMartix();
    
    if(shapePointer != NULL && signalShape != NULL){
        shapeState = shapePointer->newState();
        for(int j = 0; j < 32; j++){
            if(j < signalShape->iSubObj)
                shapePointer->enableSubObjByNameQueue(shapeState, signalShape->subObj[j].type, ((this->signalSubObj >> j) & 1));
                //shapePointer->enableSubObjByName(shapeState, signalShape->subObj[j].type, ((this->signalSubObj >> j) & 1));
        }
    }
    // chec flags
    //QStringList list;
    //checkFlags(list);
}

void SignalObj::loadInit(){
    if(Game::trackDB != NULL)  {
        this->signalShape = Game::trackDB->sigCfg->signalShape[fileName];
        
    }
}

bool SignalObj::allowNew(){
    return true;
}

bool SignalObj::isTrackItem(){
    return true;
}

ErrorMessage* SignalObj::checkForErrors(){
    
    TDB* tdb = Game::trackDB;
    //Get track items
    
    SignalShape* sShape = tdb->sigCfg->signalShape[this->fileName];
    if(sShape == NULL){
            ErrorMessage *e = new ErrorMessage(
                ErrorMessage::Type_Error, 
                ErrorMessage::Source_World, 
                QString("Object '") + type + "' - reference to SignalShape not found. UiD: " + QString::number(UiD) + ". ",
                        "Check Route Signal configuration. \n"
                );
            e->setLocationXYZ(x, -y, position[0], position[1], -position[2]);
            e->setObject((GameObj*)this);
            ErrorMessagesLib::PushErrorMessage(e);
        return e;
    }
    
    for(int i = 0; i< 32; i++){
        if(!this->signalUnit[i].enabled)
            continue;
        if(!this->signalUnit[i].head)
            continue;
        
        TRitem* item = NULL;
        item = tdb->trackItems[this->signalUnit[i].itemId];
        
        if(item == NULL){
            ErrorMessage *e = new ErrorMessage(
                ErrorMessage::Type_Error, 
                ErrorMessage::Source_World, 
                QString("Object '") + type + "' - reference to trackItem not found. UiD: " + QString::number(UiD) + ". ",
                        "World Object requires Interactive Item that does not exist in Track DB. \n"
                );
            e->setLocationXYZ(x, -y, position[0], position[1], -position[2]);
            e->setObject((GameObj*)this);
            ErrorMessagesLib::PushErrorMessage(e);
            return e;
        }
        if(item->type != "signalitem"){
            ErrorMessage *e = new ErrorMessage(
                ErrorMessage::Type_Error, 
                ErrorMessage::Source_World, 
                QString("Object '") + type + "' - referenced trackItem has wrong type. UiD: " + QString::number(UiD) + ". ",
                        QString("World Object doesn't match TDB data. Is World Database and TDB out of sync? \n")+
                        "Expected: signalitem but found: "+item->type+" .\n"+
                        "This may cause fatal errors."
                );
            e->setLocationXYZ(x, -y, position[0], position[1], -position[2]);
            e->setObject((GameObj*)this);
            ErrorMessagesLib::PushErrorMessage(e);
            return e;
        }
        if(i >= sShape->iSubObj){
            ErrorMessage *e = new ErrorMessage(
                ErrorMessage::Type_Error, 
                ErrorMessage::Source_World, 
                QString("Object '") + type + "' - has too many Signal Parts. UiD: " + QString::number(UiD) + ". ",
                        "Signal Object has more patrs than it's definition. \n"
                        "This may cause fatal errors."
                );
            e->setLocationXYZ(x, -y, position[0], position[1], -position[2]);
            e->setObject((GameObj*)this);
            ErrorMessagesLib::PushErrorMessage(e);            
            return e;
        }
        
        if(item->trSignalType4.toUpper() != sShape->subObj[i].sigSubSType.toUpper()){
            if(Game::debugOutput) qDebug() << "!SS "<< item->trSignalType4<< sShape->subObj[i].sigSubSType;
            ErrorMessage *e = new ErrorMessage(
                ErrorMessage::Type_Error, 
                ErrorMessage::Source_World, 
                QString("Object '") + type + "' - referenced wrong Signal Type. UiD: " + QString::number(UiD) + ". ",
                        QString("Referenced TrackDB item belong to another World Object or is broken. \n")+
                        "Expected: "+sShape->subObj[i].sigSubSType.toUpper()+" but found: "+item->trSignalType4.toUpper()+" .\n"+
                        "This may cause fatal errors."
                );
            e->setLocationXYZ(x, -y, position[0], position[1], -position[2]);
            e->setObject((GameObj*)this);
            ErrorMessagesLib::PushErrorMessage(e);
            return e;
        }
        
        // Check Track Node Location
        int id = tdb->findTrItemNodeId(this->signalUnit[i].itemId);
        if (id < 1) {
            ErrorMessage *e = new ErrorMessage(
                ErrorMessage::Type_Error, 
                ErrorMessage::Source_World, 
                QString("Object '") + type + "' - referenced trackItem has no TrackNode. UiD: " + QString::number(UiD) + ". ",
                        "Referenced TrackDB has no TrackNode. \n"
                        "This may cause fatal errors."
                );
            e->setLocationXYZ(x, -y, position[0], position[1], -position[2]);
            e->setObject((GameObj*)this);
            ErrorMessagesLib::PushErrorMessage(e);
            return e;
        }
        
        // Check World Location
        float data[7];
        bool ok = tdb->getDrawPositionOnTrNode(data, id, item->getTrackPosition());
        if(!ok){
            ErrorMessage *e = new ErrorMessage(
                ErrorMessage::Type_Error, 
                ErrorMessage::Source_World, 
                QString("Object '") + type + "' - referenced trackItem has no location. UiD: " + QString::number(UiD) + ". ",
                        "Referenced TrackDB Item has no location. \n"
                        "This may cause fatal errors."
                );
            e->setLocationXYZ(x, -y, position[0], position[1], -position[2]);
            e->setObject((GameObj*)this);
            ErrorMessagesLib::PushErrorMessage(e);
            return e;
        }
    }

    return NULL;
}

void SignalObj::deleteTrItems(){
    TDB* tdb = Game::trackDB;
    TDB* rdb = Game::roadDB;
    
    if(checkForErrors() != NULL){
        return;
    }
    
    for(int i = 0; i< 32; i++){
        if(!this->signalUnit[i].enabled)
            continue;
        this->signalUnit[i].enabled = false;
        if(!this->signalUnit[i].head)
            continue;
        if(this->signalUnit[i].tdbId == 0)
            tdb->deleteTrItem(this->signalUnit[i].itemId);
        else if(this->signalUnit[i].tdbId == 1)
            rdb->deleteTrItem(this->signalUnit[i].itemId);
    }
}

bool SignalObj::containsTrackItem(int tdbId, int id){
    for(int i = 0; i < 32; i++){
        if(this->signalUnit[i].tdbId != tdbId)
            continue;
        if(this->signalUnit[i].itemId == id)
            return true;
    }
    return false;
}

void SignalObj::addTrackItemIdOffset(unsigned int trackOffset, unsigned int roadOffset){
    for(int i = 0; i < 32; i++){ // 
        if(this->signalUnit[i].tdbId == 0)
            this->signalUnit[i].itemId += trackOffset;
        if(this->signalUnit[i].tdbId == 1)
            this->signalUnit[i].itemId += roadOffset;
    }
}

void SignalObj::getTrackItemIds(QVector<int> &ids, int tdbId){
    if(!this->loaded)
        return;
    for(int i = 0; i < 32; i++){
        if(this->signalUnit[i].tdbId != tdbId)
            continue;
        ids.push_back(this->signalUnit[i].itemId);
    }

}

void SignalObj::initTrItems(float* tpos){
    if(tpos == NULL)
        return;
    int trNodeId = tpos[0];
    float metry = tpos[1];
    // 
    TDB* tdb = Game::trackDB;
    if(Game::debugOutput) qDebug() <<"new signal  "<<this->fileName;

    Game::resetTools = true;  // fake signal
    
    tdb->newSignalObject(this->fileName, this->signalUnit, this->signalUnits, trNodeId, metry, this->typeID);
    
    this->signalSubObj = 0;
    
    for(int i = 0; i < 32; i++){
        if(this->signalUnit[i].enabled)
            this->signalSubObj = this->signalSubObj | (1 << i);
    }
    if(Game::debugOutput) qDebug() <<"signalUnits  "<<this->signalUnits << this->signalSubObj;
   // this->trItemIdCount = 4;
  //  this->trItemId[0] = isRoad;
   // this->trItemId[1] = trItemId[0];
   // this->trItemId[2] = isRoad;
  //  this->trItemId[3] = trItemId[1];
    this->drawPositions = NULL;
    
    // find head item 
    int base = getBaseSignalItemId();
    if(this->signalUnits > 0 && base >= 0){
        this->rotate(0,-tdb->trackItems[this->signalUnit[base].itemId]->trSignalType3+M_PI,0);
    }
}

void SignalObj::set(QString sh, long long int val) { // 
    if (sh == ("ref_value")) {
        SignalShape * signal = Game::trackDB->sigCfg->signalShapeById[val];
        fileName = signal->name; 
        return;
    } 
    WorldObj::set(sh, val);
    setModified();
}

void SignalObj::set(QString sh, QString val){ // 
    if (sh == ("filename")) {
        fileName = val;
        return;
    }
    if (sh == ("ref_filename")) {
        fileName = val;
        return;
    }
    WorldObj::set(sh, val);
    return;
}

void SignalObj::set(int sh, FileBuffer* data) { // 
    if (sh == TS::FileName) {
        data->off++;
        int slen = data->getShort()*2;
        fileName = *data->getString(data->off, data->off + slen);
        data->off += slen;
        return;
    }
    if (sh == TS::SignalSubObj) {
        data->off++;
        signalSubObj = data->getUint();
        return;
    }
    if (sh == TS::SignalUnits) {
        data->off++;
        signalUnits = data->getUint();
        for(int i = 0; i < signalUnits; i++){
            data->getToken();
            data->getInt();
            data->off++;
            int sUnitId = data->getInt();
            data->getToken();
            data->getInt();
            data->off++;
            signalUnit[sUnitId].enabled = true;
            signalUnit[sUnitId].head = true;
            signalUnit[sUnitId].tdbId = data->getUint();
            signalUnit[sUnitId].itemId = data->getUint();
        }
        return;
    }
    
    WorldObj::set(sh, data);
    return;
}

void SignalObj::set(QString sh, FileBuffer* data) { 
    if (sh == ("filename")) {
        fileName = ParserX::GetString(data);
        return;
    }
    if (sh == ("signalsubobj")) {
        signalSubObj = ParserX::GetHex(data);
        return;
    }
    if (sh == ("signalunits")) {
        signalUnits = ParserX::GetNumber(data);
        for(int i = 0; i < signalUnits; i++){
            int sUnitId = ParserX::GetNumber(data);
            signalUnit[sUnitId].enabled = true;
            signalUnit[sUnitId].head = true;
            signalUnit[sUnitId].tdbId = ParserX::GetNumber(data);
            signalUnit[sUnitId].itemId = ParserX::GetNumber(data);
        }
        ParserX::SkipToken(data);
        ParserX::SkipToken(data);
        return;
    }
    WorldObj::set(sh, data);
    return;
}

int SignalObj::getLinkedJunctionValue(int i){
    if(!this->signalUnit[i].enabled) return -1;
    if(!this->signalUnit[i].head) return -1;
    TDB* tdb = Game::trackDB;
    TRitem* trit = tdb->trackItems[this->signalUnit[i].itemId];
    if(trit == NULL) return -1;
    if(trit->trSignalDirs < 1) return 0;
    return trit->trSignalDir[0];
}

void SignalObj::getLinkInfo(int *ids){
    ids[0] = -1;
    if(!this->signalUnit[subObjSelected].enabled) return;
    if(!this->signalUnit[subObjSelected].head) return;
    TDB* tdb = Game::trackDB;
    TRitem* trit = tdb->trackItems[this->signalUnit[subObjSelected].itemId];
    if(trit == NULL) return;
    if(trit->trSignalDirs < 1) return;
    int jid = trit->trSignalDir[0];
    int dir = trit->trSignalDir[2];
    ids[0] = jid;
    ids[1] = tdb->trackNodes[jid]->TrPinS[1+dir];
    TRnode *n = tdb->trackNodes[ids[1]];
    if(n->TrPinS[0] == ids[0])
        ids[2] = n->TrPinS[1];
    else
        ids[2] = n->TrPinS[0];
}

bool SignalObj::isJunctionAvailable(int i){
    if(!this->signalUnit[i].enabled) return false;
    if(!this->signalUnit[i].head) return false;
    TDB* tdb = Game::trackDB;
    int tritId = this->signalUnit[i].itemId;
    TRitem* trit = tdb->trackItems[tritId];
    if(trit == NULL) return false;
    int nid = tdb->findTrItemNodeId(tritId);
    if(nid < 0) return false;
    int direction = fabs(trit->trSignalType2 - 1);
    int endPointType = tdb->getEndpointType(nid, direction);
       
    if(endPointType == 2) return true;
    return false;
}

/*void SignalObj::linkSignal(int subsigId, int from, int to){
    if(!this->signalUnit[subsigId].enabled) return;
    if(!this->signalUnit[subsigId].head) return;
    TDB* tdb = Game::trackDB;
    if(tdb->trackItems[this->signalUnit[subsigId].itemId] == NULL)
        return;
    tdb->trackItems[this->signalUnit[subsigId].itemId]->linkSignal(from, to);
}*/

void SignalObj::linkSignal(int trackId, int dist){
    if(!this->signalUnit[subObjSelected].enabled) return;
    if(!this->signalUnit[subObjSelected].head) return;
    TDB* tdb = Game::trackDB;
    if(tdb->trackItems[this->signalUnit[subObjSelected].itemId] == NULL)
        return;
    tdb->trackItems[this->signalUnit[subObjSelected].itemId]->linkSignal(trackId, dist);       
/// EFO Redraw?? 

    qDebug() << "signalUnits: " << signalUnits ;    
    spointer3d->setMaterial(0.3,0.8,0.3);
    for(int i = 1; i < 32; i++){
        if((signalUnit[i].enabled) & (signalUnit[i].head))
        {
            if(!getLinkedJunctionValue(i) > 0 )
            spointer3d->setMaterial(1,1,0);    
        }
    }
   
    setModified();
    delete[] drawPositions;
    drawPositions = NULL;
   
}

bool SignalObj::isSubObjEnabled(int i){
    return ((this->signalSubObj >> i) & 1) == 1;
}

void SignalObj::enableSubObj(int i){
    if(isSubObjEnabled(i)) return;
    if(signalShape == NULL)
        return;
    
    TDB* tdb = Game::trackDB;
    
    // find head item 
    int base = getBaseSignalItemId();
    // add signal item to tdb
    if(signalShape->subObj[i].sigSubTypeId == SignalShape::SIGNAL_HEAD){
        if(base < 0)
            return;
        tdb->enableSignalSubObj(this->fileName, this->signalUnit[i], i, this->signalUnit[base].itemId );
        for(int j = 0; j < 32; j++){
            //qDebug() << ((this->signalSubObj >> j) & 1);
            if(!((this->signalSubObj >> j) & 1))
                continue;
            if(this->signalUnit[j].head)
                continue;
            //qDebug() << signalShape->subObj[i].backFacing << signalShape->subObj[j].backFacing;
            if(signalShape->subObj[i].backFacing == signalShape->subObj[j].backFacing)
                tdb->trackItems[this->signalUnit[i].itemId]->enableSignalSubObjFlag(signalShape->subObj[j].sigSubType);
        }
    }
    
    // set signal unit flag enabled
    this->signalSubObj = this->signalSubObj | (1 << i);
    
    // update flags
    if(!this->signalUnit[i].head)
        for(int j = 0; j < 32; j++){
            if(!this->signalUnit[j].enabled)
                continue;
            if(!this->signalUnit[j].head)
                continue;
            if(tdb->trackItems[this->signalUnit[j].itemId] == NULL)
                continue;
            if(signalShape->subObj[i].backFacing == signalShape->subObj[j].backFacing)
                tdb->trackItems[this->signalUnit[j].itemId]->enableSignalSubObjFlag(signalShape->subObj[i].sigSubType);
        }
    setModified();
    if(shapePointer != NULL)
        shapePointer->enableSubObjByName(shapeState, signalShape->subObj[i].type, true);
    return;
}

void SignalObj::disableSubObj(int i){
    if(!isSubObjEnabled(i)) 
        return;
    if(signalShape == NULL)
        return;
    if(!signalShape->subObj[i].optional)
        return;
    
    TDB* tdb = Game::trackDB;
    // add signal item to tdb
    //tdb->enableSignalSubObj(this->fileName, i);
    this->signalSubObj = this->signalSubObj & ~(1 << i);
    this->signalUnit[i].enabled = false;
    
    if(signalShape->subObj[i].sigSubTypeId == SignalShape::SIGNAL_HEAD)
        tdb->deleteTrItem(this->signalUnit[i].itemId);
    
    if(!this->signalUnit[i].head)
        for(int j = 0; j < 32; j++){
            if(!this->signalUnit[j].enabled)
                continue;
            if(!this->signalUnit[j].head)
                continue;
            if(tdb->trackItems[this->signalUnit[j].itemId] == NULL)
                continue;
            if(signalShape->subObj[i].backFacing == signalShape->subObj[j].backFacing)
                tdb->trackItems[this->signalUnit[j].itemId]->disableSignalSubObjFlag(signalShape->subObj[i].sigSubType);
        }
    setModified();
    if(shapePointer != NULL)
        shapePointer->enableSubObjByName(shapeState, signalShape->subObj[i].type, false);
}

void SignalObj::checkFlags(QStringList &list){
    TDB* tdb = Game::trackDB;
    unsigned int tFlags[32];
    for(int i = 0; i < 32; i++){
        if(!signalUnit[i].enabled)
            continue;
        if(!signalUnit[i].head)
            continue;
        if(tdb->trackItems[signalUnit[i].itemId] == NULL)
            continue;
        list.push_back(ParserX::MakeFlagsString(tdb->trackItems[signalUnit[i].itemId]->trSignalType1));
        
        tFlags[i] = 0;
        if(signalShape->subObj[i].isJnLink)
            tFlags[i] |= 0b0000001;
        for(int j = 0; j < 32; j++){
            if(!((this->signalSubObj >> j) & 1))
                continue;
            if(this->signalUnit[j].head)
                continue;
            if(signalShape->subObj[i].backFacing != signalShape->subObj[j].backFacing)
                continue;
            if(signalShape->subObj[j].sigSubType == "NUMBER_PLATE")
                tFlags[i] |= 0b0000010000;
            if(signalShape->subObj[j].sigSubType == "GRADIENT_PLATE")
                tFlags[i] |= 0b0000100000;
            if(signalShape->subObj[j].sigSubType == "USER1")
                tFlags[i] |= 0b0001000000;
            if(signalShape->subObj[j].sigSubType == "USER2")
                tFlags[i] |= 0b0010000000;
            if(signalShape->subObj[j].sigSubType == "USER3")
                tFlags[i] |= 0b0100000000;
            if(signalShape->subObj[j].sigSubType == "USER4")
                tFlags[i] |= 0b1000000000;
        }
        
        list.back() += " " + ParserX::MakeFlagsString(tFlags[i]);
        if(list.back().split(" ")[0] != list.back().split(" ")[1]){
            qDebug() << "[E] --- signal flags fail: "<< this->UiD << this->x << this->y << this->position[0] << this->position[2] << list.back();
            list.back() += " [E]";
        }
    }
}

void SignalObj::fixFlags(){
    TDB* tdb = Game::trackDB;
    unsigned int tFlags;
    for(int i = 0; i < 32; i++){
        if(!signalUnit[i].enabled)
            continue;
        if(!signalUnit[i].head)
            continue;
        if(tdb->trackItems[signalUnit[i].itemId] == NULL)
            continue;
        
        tFlags = 0;
        if(signalShape->subObj[i].isJnLink)
            tFlags |= 0b0000001;
        for(int j = 0; j < 32; j++){
            if(!((this->signalSubObj >> j) & 1))
                continue;
            if(this->signalUnit[j].head)
                continue;
            if(signalShape->subObj[i].backFacing != signalShape->subObj[j].backFacing)
                continue;
            if(signalShape->subObj[j].sigSubType == "NUMBER_PLATE")
                tFlags |= 0b0000010000;
            if(signalShape->subObj[j].sigSubType == "GRADIENT_PLATE")
                tFlags |= 0b0000100000;
            if(signalShape->subObj[j].sigSubType == "USER1")
                tFlags |= 0b0001000000;
            if(signalShape->subObj[j].sigSubType == "USER2")
                tFlags |= 0b0010000000;
            if(signalShape->subObj[j].sigSubType == "USER3")
                tFlags |= 0b0100000000;
            if(signalShape->subObj[j].sigSubType == "USER4")
                tFlags |= 0b1000000000;
        }
        tdb->trackItems[signalUnit[i].itemId]->trSignalType1 = tFlags;
    }
    setModified();
}

void SignalObj::flip(bool flipShape){
    if(flipShape){
        Quat::rotateY(this->qDirection, this->qDirection, M_PI);
        this->setMartix();
    }

    TDB* tdb = Game::trackDB;
    for(int j = 0; j < 32; j++){
        if(!this->signalUnit[j].enabled)
            continue;
        if(!this->signalUnit[j].head)
            continue;
        if(tdb->trackItems[this->signalUnit[j].itemId] == NULL)
            continue;
        tdb->trackItems[this->signalUnit[j].itemId]->flipSignal();
    }
    setModified();
    delete[] drawPositions;
    drawPositions = NULL;
}

QString SignalObj::getShapePath(){ // 
    if (!loaded) return "";
    if (shape < 0) return "";
    return Game::currentShapeLib->shape[shape]->pathid+"|"+Game::currentShapeLib->shape[shape]->texPath;
}

bool SignalObj::isSimilar(WorldObj* obj){
    if(obj->typeID != this->typeID)
        return false;
    if(obj->fileName == this->fileName)
        return true;
    return false;
}

void SignalObj::render(GLUU* gluu, float lod, float posx, float posz, float* pos, float* target, float fov, int selectionColor, int renderMode) {
    if (!loaded) return;
    if (shape < 0) return;
    if (jestPQ < 2) return;
    if (renderMode == gluu->RENDER_SHADOWMAP && Game::mstsShadows) {
        if(this->getShadowType() != WorldObj::ShadowDynamic )
            return;
    }
    //GLUU* gluu = GLUU::get();
    //if((this.position===undefined)||this.qDirection===undefined) return;
    //
    if (size > 0) {
        if ((lod > size + 150)) {
            float v1[2];
            v1[0] = pos[0] - (target[0]);
            v1[1] = pos[2] - (target[2]);
            float v2[2];
            v2[0] = posx;
            v2[1] = posz;
            float iloczyn = v1[0] * v2[0] + v1[1] * v2[1];
            float d1 = sqrt(v1[0] * v1[0] + v1[1] * v1[1]);
            float d2 = sqrt(v2[0] * v2[0] + v2[1] * v2[1]);
            float zz = iloczyn / (d1 * d2);
            if (zz > 0) return;

            float ccos = cos(fov) + zz;
            float xxx = sqrt(2 * d2 * d2 * (1 - ccos));
            //if((ccos > 0) && (xxx > 200+50)) return;
            if ((ccos > 0) && (xxx > size) && (skipLevel == 1)) return;
        }
    } else {
        if (Game::currentShapeLib->shape[shape]->loaded)
            size = Game::currentShapeLib->shape[shape]->size;
    }
    
    gluu->mvPushMatrix();
    Mat4::multiply(gluu->mvMatrix, gluu->mvMatrix, matrix);
    gluu->currentShader->setUniformValue(gluu->currentShader->mvMatrixUniform, *reinterpret_cast<float(*)[4][4]> (gluu->mvMatrix));
    
    if(Game::showWorldObjPivotPoints){
        if(pointer3d == NULL){
            pointer3d = new TrackItemObj(1);  
            pointer3d->setMaterial(0.9,0.9,0.7);
        }
        pointer3d->render(selectionColor);
    }
    
    if(selectionColor != 0){
        gluu->disableTextures(selectionColor);
    } else {
        gluu->enableTextures();
    }
    if(shapePointer != NULL)
        shapePointer->render(selectionColor, shapeState);
    //Game::currentShapeLib->shape[shape]->render(false, signalSubObj);
    
    if(selected){
        drawBox();
    }
    gluu->mvPopMatrix();
    
    if(trLoaded >= 0)
        if(Game::viewInteractives && renderMode != gluu->RENDER_SHADOWMAP) 
            this->renderTritems(gluu, selectionColor);
};

void SignalObj::renderTritems(GLUU* gluu, int selectionColor){

    ///////////////////////////////
    if (drawPositions == NULL) {
        if(spointer3d == NULL){
            spointer3d = new TrackItemObj(Game::pointerOut);   /// EFO orig ())  new shape  newSymbols          
            // qDebug() << this->getLinkedJunctionValue(1);

        spointer3d->setMaterial(0,1,0);
        for(int i = 1; i < 32; i++){
          if((signalUnit[i].enabled) & (signalUnit[i].head))
             {
                 if(!getLinkedJunctionValue(i) > 0 )
                 spointer3d->setMaterial(1,0,0);    
             }
          }
            
        }
        if(spointer3dSelected == NULL){
            spointer3dSelected = new TrackItemObj(Game::pointerOut);    /// EFO orig())  new shape   newSymbols
            spointer3dSelected->setMaterial(1,0.5,0.5);
        }
        drawPositions = new float*[32];
        TDB* tdb = Game::trackDB;
        for(int i = 0; i < 32; i++){
            drawPositions[i] = NULL;
            if(!this->signalUnit[i].enabled || !this->signalUnit[i].head)
                continue;
            if(tdb->trackItems[this->signalUnit[i].itemId] == NULL){
                qDebug() << "signal fail tid";
                this->trLoaded = -1;
                return;
            }
            int id = tdb->findTrItemNodeId(this->signalUnit[i].itemId);
            if (id < 0) {
                qDebug() << "signal fail nid";
                this->trLoaded = -1;
                return;
            }
            //qDebug() << "id: "<< this->trItemId[i*2+1] << " "<< id;
            drawPositions[i] = new float[8];
            bool ok = tdb->getDrawPositionOnTrNode(drawPositions[i], id, tdb->trackItems[this->signalUnit[i].itemId]->getTrackPosition());
            if(!ok){
                qDebug() << "signal fail tdb" << this->signalUnit[i].itemId ;
                this->trLoaded = -1;
                return;
            }
            //drawPositions[i][7] = tdb->trackItems[this->signalUnit[i].itemId]->trSignalType2;
            drawPositions[i][7] = tdb->trackItems[this->signalUnit[i].itemId]->trSignalType3;
            drawPositions[i][0] += 2048 * (drawPositions[i][5] - this->x);
            drawPositions[i][2] -= 2048 * (-drawPositions[i][6] - this->y);
        }
    }

    //if(pos == NULL) return;
    //gluu->setMatrixUniforms();
    int useSC;
    int w = 1;
    //w = this->signalUnits;

    // find head item 
    int i = getBaseSignalItemId();
    if(drawPositions[i] == NULL) return;
    //for(int i = 0; i < w; i++){
        //if(drawPositions[i] == NULL) continue;
        gluu->mvPushMatrix();
        Mat4::translate(gluu->mvMatrix, gluu->mvMatrix, drawPositions[i][0] + 0 * (drawPositions[i][4] - this->x), drawPositions[i][1] + /*i +*/ 1, -drawPositions[i][2] + 0 * (-drawPositions[i][5] - this->y));
        //Mat4::rotateY(gluu->mvMatrix, gluu->mvMatrix, drawPositions[i][3] + drawPositions[i][7]*M_PI);
        Mat4::rotateY(gluu->mvMatrix, gluu->mvMatrix, -drawPositions[i][7]+M_PI);
        //Mat4::translate(gluu->mvMatrix, gluu->mvMatrix, this->trItemRData[0] + 2048*(this->trItemRData[3] - playerT[0] ), this->trItemRData[1]+2, -this->trItemRData[2] + 2048*(-this->trItemRData[4] - playerT[1]));
        //Mat4::translate(gluu->mvMatrix, gluu->mvMatrix, this->trItemRData[0] + 0, this->trItemRData[1]+0, -this->trItemRData[2] + 0);
        gluu->currentShader->setUniformValue(gluu->currentShader->mvMatrixUniform, *reinterpret_cast<float(*)[4][4]> (gluu->mvMatrix));
        useSC = (float)selectionColor/(float)(selectionColor+0.000001);
        if(this->selected && this->selectionValue > 0) 
            spointer3dSelected->render(selectionColor | (i+1)*useSC);
        else
            spointer3d->render(selectionColor | (i+1)*useSC);
        gluu->mvPopMatrix();
    //}
};

int SignalObj::getTrItemId(){
    for(int i=0; i<32; i++){
        if(signalUnit[i].enabled && signalUnit[i].head)
            return signalUnit[i].itemId;
    }
    return -1;
}

int SignalObj::getBaseSignalItemId(){ 
    int i = -1;
    for(int j = 0; j < 32; j++){
        if(!this->signalUnit[j].enabled)
            continue;
        if(!this->signalUnit[j].head)
            continue;
        i = j;
        break;
    }
    return i;
}

bool SignalObj::select(int value){
    this->selectionValue = value;
    this->selected = true;
    return true;
}

bool SignalObj::getSimpleBorder(float* border){
    if (shape < 0) return false;
    if (!Game::currentShapeLib->shape[shape]->loaded)
        return false;
    float* bound = Game::currentShapeLib->shape[shape]->bound;
    border[0] = bound[0];
    border[1] = bound[1];
    border[2] = bound[2];
    border[3] = bound[3];
    border[4] = bound[4];
    border[5] = bound[5];
    return true;
}

bool SignalObj::getBoxPoints(QVector<float>& points){
        float bound[6];
        if (!getSimpleBorder((float*)&bound)) return false;
        
        for(int i=0; i<2; i++)
            for(int j=4; j<6; j++){
                points.push_back(bound[i]);
                points.push_back(bound[2]);
                points.push_back(bound[j]);
                points.push_back(bound[i]);
                points.push_back(bound[3]);
                points.push_back(bound[j]);
            }
        for(int i=0; i<2; i++)
            for(int j=2; j<4; j++){
                points.push_back(bound[i]);
                points.push_back(bound[j]);
                points.push_back(bound[4]);
                points.push_back(bound[i]);
                points.push_back(bound[j]);
                points.push_back(bound[5]);
            }
        for(int i=4; i<6; i++)
            for(int j=2; j<4; j++){
                points.push_back(bound[0]);
                points.push_back(bound[j]);
                points.push_back(bound[i]);
                points.push_back(bound[1]);
                points.push_back(bound[j]);
                points.push_back(bound[i]);
            }
        return true;
}

int SignalObj::getDefaultDetailLevel(){
    return -6;
}

Ref::RefItem* SignalObj::getRefInfo(){ // 
    Ref::RefItem* r = new Ref::RefItem();
    r->type = this->type;
    r->filename.push_back(this->fileName);
    r->staticFlags = this->staticFlags;
    r->value = this->signalShape->listId;
    return r;
}

void SignalObj::save(QTextStream* out){
    if (!loaded) return;
    if (!trLoaded < 0) return;
    if(Game::useOnlyPositiveQuaternions)
        Quat::makePositive(this->qDirection);
    
*(out) << "	Signal (\n";
*(out) << "		UiD ( "<<this->UiD<<" )\n";
*(out) << "		FileName ( "<<ParserX::AddComIfReq(this->fileName)<<" )\n";
*(out) << "		Position ( "<<this->position[0]<<" "<<this->position[1]<<" "<<-this->position[2]<<" )\n";
*(out) << "		QDirection ( "<<this->qDirection[0]<<" "<<this->qDirection[1]<<" "<<-this->qDirection[2]<<" "<<this->qDirection[3]<<" )\n";
if(Game::legacySupport)   *(out) << "		VDbId ( " << this->vDbId << " )\n";  // EFO 
if(this->staticDetailLevel > -1)
*(out) << "		StaticDetailLevel ( "<<this->staticDetailLevel<<" )\n";
*(out) << "		SignalSubObj ( "<<ParserX::MakeFlagsString(this->signalSubObj)<<" )\n";
signalUnits = 0;
for(int i=0; i<32; i++)
    if(this->signalUnit[i].enabled && this->signalUnit[i].head)
        signalUnits++;
if(signalUnits > 0){
*(out) << "		SignalUnits ( "<<this->signalUnits<<"\n";
for(int i=0; i<32; i++)
    if(this->signalUnit[i].enabled && this->signalUnit[i].head){
*(out) << "			SignalUnit ( "<<i<<"\n";
*(out) << "				TrItemId ( "<<this->signalUnit[i].tdbId<<" "<<this->signalUnit[i].itemId<<" )\n";
*(out) << "			)\n";
}
*(out) << "		)\n";
}
*(out) << "	)\n";
}


