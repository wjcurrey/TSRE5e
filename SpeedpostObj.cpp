/*  This file is part of TSRE5.
 *
 *  TSRE5 - train sim game engine and MSTS/OR Editors. 
 *  Copyright (C) 2016 Piotr Gadecki <pgadecki@gmail.com>
 *
 *  Licensed under GNU General Public License 3.0 or later. 
 *
 *  See LICENSE.md or https://www.gnu.org/licenses/gpl.html
 */

#include "SpeedpostObj.h"
#include "SFile.h"
#include "ShapeLib.h"
#include "GLMatrix.h"
#include <math.h>
#include "ParserX.h"
#include "TDB.h"
#include "TRitem.h"
#include "Game.h"
#include "TrackItemObj.h"
#include "TS.h"
#include "SpeedPostDAT.h"
#include "SpeedPost.h"
#include <QDebug>
#include "Vector4f.h"
#include "ErrorMessagesLib.h"
#include "ErrorMessage.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

float SpeedpostObj::MaxPlacingDistance = 20;

bool SpeedpostObj::allowNew(){
    return true;
}

bool SpeedpostObj::isTrackItem(){
    return true;
}

SpeedpostObj::SpeedpostObj() {
    this->shape = -1;
    this->loaded = false;
}

SpeedpostObj::SpeedpostObj(const SpeedpostObj& o) : WorldObj(o) {
    speedPostId = o.speedPostId;
    speedPostType = o.speedPostType;
    speedDigitTex = o.speedDigitTex;
    if(o.speedSignShape != NULL){
        speedSignShape = new float[(int)o.speedSignShape[0]*4+1];
        for(int i = 0; i < this->speedSignShape[0]*4+1; i++)
            speedSignShape[i] = o.speedSignShape[i];
    }
    speedTextSize[0] = o.speedTextSize[0];
    speedTextSize[1] = o.speedTextSize[1];
    speedTextSize[2] = o.speedTextSize[2];
    trItemId.append(o.trItemId);
    selectionValue = o.selectionValue;
}

WorldObj* SpeedpostObj::clone(){
    return new SpeedpostObj(*this);
}

SpeedpostObj::~SpeedpostObj() {
}

void SpeedpostObj::loadingFixes(){
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

bool SpeedpostObj::containsTrackItem(int tdbId, int id){
    for(int i = 0; i<this->trItemId.size()/2; i++){
        if(this->trItemId[i*2] == tdbId){
            if(this->trItemId[i*2+1] == id)
                return true;
        }
    }
    return false;
}

void SpeedpostObj::addTrackItemIdOffset(unsigned int trackOffset, unsigned int roadOffset){
    for(int i = 0; i<this->trItemId.size()/2; i++){
        if(this->trItemId[i*2] == 0)
            this->trItemId[i*2+1] += trackOffset;
        if(this->trItemId[i*2] == 1)
            this->trItemId[i*2+1] += roadOffset;
    }
}

void SpeedpostObj::getTrackItemIds(QVector<int> &ids, int tdbId){
    if(!this->loaded)
        return;
    for(int i = 0; i<this->trItemId.size()/2; i++){
        if(this->trItemId[i*2] == tdbId){
            ids.push_back(this->trItemId[i*2+1]);
        }
    }
}

void SpeedpostObj::load(int x, int y) {
    this->shape = Game::currentShapeLib->addShape(resPath +"/"+ fileName);
    this->x = x;
    this->y = y;
    this->position[2] = -this->position[2];
    this->qDirection[2] = -this->qDirection[2];
    this->loaded = true;
    this->size = -1;
    this->skipLevel = 1;
    this->modified = false;
    this->drawPosition = NULL;
    this->pointer3d = NULL;
    this->txt = NULL;
    this->txt2 = NULL;
    setMartix();
}

ErrorMessage* SpeedpostObj::checkForErrors(){
    TDB* tdb = Game::trackDB;

    TRitem::SType stype;

    TRitem *item = NULL;
    for(int i = 0; i < trItemId.size()/2; i++){
        if(this->trItemId[i*2] != 0)
            continue;
        
        item = Game::trackDB->trackItems[this->trItemId[i*2+1]];
        if(item == NULL) {
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
        if(item->type != "speedpostitem"){
            ErrorMessage *e = new ErrorMessage(
                ErrorMessage::Type_Error, 
                ErrorMessage::Source_World, 
                QString("Object '") + type + "' - referenced trackItem has wrong type. UiD: " + QString::number(UiD) + ". ",
                        QString("World Object doesn't match TDB data. Is World Database and TDB out of sync? \n")+
                        "Expected: speedpostitem but found: "+item->type+" .\n"
                        "This may cause fatal errors."
                );
            e->setLocationXYZ(x, -y, position[0], position[1], -position[2]);
            e->setObject((GameObj*)this);
            ErrorMessagesLib::PushErrorMessage(e);
            return e;
        }
        
        if(i == 0){
            stype = item->getSpeedpostType();
        } else {
            if(stype != item->getSpeedpostType()){
                ErrorMessage *e = new ErrorMessage(
                    ErrorMessage::Type_Error, 
                    ErrorMessage::Source_World, 
                    QString("Object '") + type + "' - referenced wrong SpeedPost Type. UiD: " + QString::number(UiD) + ". ",
                            QString("World Object doesn't match TDB data. Is World Database and TDB out of sync? \n") +
                            "Expected: " + TRitem::speedpostTypeName(stype) + " but found: " + TRitem::speedpostTypeName(item->getSpeedpostType()) + "\n" +
                            "This may cause fatal errors."
                    );
                e->setLocationXYZ(x, -y, position[0], position[1], -position[2]);
                e->setObject((GameObj*)this);
                ErrorMessagesLib::PushErrorMessage(e);
                return e;
            }
        }
    }
    
    return NULL;
}

void SpeedpostObj::deleteTrItems(){
    TDB* tdb = Game::trackDB;
    TDB* rdb = Game::roadDB;
    
    if(checkForErrors() != NULL){
        return;
    }
    
    for(int i = 0; i<this->trItemId.size()/2; i++){
        if(this->trItemId[i*2] == 0)
            tdb->deleteTrItem(this->trItemId[i*2+1]);
        else if(this->trItemId[i*2] == 1)
            rdb->deleteTrItem(this->trItemId[i*2+1]);
        this->trItemId[i*2+1] = -1;
    }
}

QString SpeedpostObj::getSpeedpostType(){
    if(this->trItemId.size() < 2){
        qDebug() << "speedpost: fail trItemId";
        return "";
    }
    TRitem* item = Game::trackDB->trackItems[this->trItemId[1]];
    if(item == NULL) return "";
    TRitem::SType val = item->getSpeedpostType();
    if((val) == TRitem::MILEPOST)
        return QString("milepost");
    if((val) == TRitem::WARNING)
        return QString("warning");
    if((val) == TRitem::SIGN)
        return QString("speedsign");
    if((val) == TRitem::RESUME)
        return QString("resume");
    return "";
}

float SpeedpostObj::getSpeed(){
    if(this->trItemId.size() < 2){
        qDebug() << "speedpost: fail trItemId";
        return 0;
    }
    TRitem* item = Game::trackDB->trackItems[this->trItemId[1]];
    if(item == NULL) return 0;
    return item->getSpeedpostSpeed();
}

float SpeedpostObj::getNumber(){
    if(this->trItemId.size() < 2){
        qDebug() << "speedpost: fail trItemId";
        return 0;
    }
    TRitem* item = Game::trackDB->trackItems[this->trItemId[1]];
    if(item == NULL) return 0;
    return item->getSpeedpostNumber();
}

void SpeedpostObj::setSpeed(float val){
    if(this->trItemId.size() < 2){
        qDebug() << "speedpost: fail trItemId";
        return;
    }
    TDB* tdb = Game::trackDB;
    for(int j = 0; j < this->trItemId.size()/2; j++){
        if(tdb->trackItems[this->trItemId[j*2+1]] == NULL)
            continue;
        tdb->trackItems[this->trItemId[j*2+1]]->setSpeedpostSpeed(val);
    }
    setModified();
}

void SpeedpostObj::setNumber(float val){
    if(this->trItemId.size() < 2){
        qDebug() << "speedpost: fail trItemId";
        return;
    }
    TDB* tdb = Game::trackDB;
    for(int j = 0; j < this->trItemId.size()/2; j++){
        if(tdb->trackItems[this->trItemId[j*2+1]] == NULL)
            continue;
        tdb->trackItems[this->trItemId[j*2+1]]->setSpeedpostNumber(val);
    }
    setModified();
}

void SpeedpostObj::setSpeedUnitId(int val){
    TDB* tdb = Game::trackDB;
    if(this->trItemId.size() < 2)
        return;
    if(tdb->trackItems[this->trItemId[1]] == NULL)
        return;
    for(int j = 0; j < this->trItemId.size()/2; j++){
        if(tdb->trackItems[this->trItemId[j*2+1]] == NULL)
            continue;
        tdb->trackItems[this->trItemId[j*2+1]]->setSpeedPostSpeedUnitId(val);
    }
    setModified();
}

int SpeedpostObj::getSpeedUnitId(){
    TDB* tdb = Game::trackDB;
    if(this->trItemId.size() < 2)
        return 0;
    if(tdb->trackItems[this->trItemId[1]] == NULL)
        return 0;
    return tdb->trackItems[this->trItemId[1]]->getSpeedPostSpeedUnitId();
}

void SpeedpostObj::setSpeedInsteadNumber(bool val){
    TDB* tdb = Game::trackDB;
    if(this->trItemId.size() < 2)
        return;
    if(tdb->trackItems[this->trItemId[1]] == NULL)
        return;
    tdb->trackItems[this->trItemId[1]]->setSpeedpostSpeedInsteadNumber(val);
    setModified();
}

void SpeedpostObj::setNumberInsteadSpeed(bool val){
    TDB* tdb = Game::trackDB;
    if(this->trItemId.size() < 2)
        return;
    if(tdb->trackItems[this->trItemId[1]] == NULL)
        return;
    tdb->trackItems[this->trItemId[1]]->setSpeedpostNumberInsteadSpeed(val);
    setModified();
}

bool SpeedpostObj::getSpeedInsteadNumber(){
    TDB* tdb = Game::trackDB;
    if(this->trItemId.size() < 2)
        return 0;
    if(tdb->trackItems[this->trItemId[1]] == NULL)
        return 0;
    return tdb->trackItems[this->trItemId[1]]->getSpeedpostSpeedInsteadNumber();
}

bool SpeedpostObj::getNumberInsteadSpeed(){
    TDB* tdb = Game::trackDB;
    if(this->trItemId.size() < 2)
        return 0;
    if(tdb->trackItems[this->trItemId[1]] == NULL)
        return 0;
    return tdb->trackItems[this->trItemId[1]]->getSpeedpostNumberInsteadSpeed();
}

int SpeedpostObj::getTrainType(){
    TDB* tdb = Game::trackDB;
    if(this->trItemId.size() < 2)
        return 0;
    if(tdb->trackItems[this->trItemId[1]] == NULL)
        return 0;
    return tdb->trackItems[this->trItemId[1]]->getSpeedPostTrainType();
}

bool SpeedpostObj::isNumberDot(){
    TDB* tdb = Game::trackDB;
    if(this->trItemId.size() < 2)
        return 0;
    if(tdb->trackItems[this->trItemId[1]] == NULL)
        return 0;
    return tdb->trackItems[this->trItemId[1]]->getSpeedPostNumberDot();
}

void SpeedpostObj::setNumberDot(bool val){
    TDB* tdb = Game::trackDB;
    if(this->trItemId.size() < 2)
        return;
    if(tdb->trackItems[this->trItemId[1]] == NULL)
        return;
    for(int j = 0; j < this->trItemId.size()/2; j++){
        if(tdb->trackItems[this->trItemId[j*2+1]] == NULL)
            continue;
        tdb->trackItems[this->trItemId[j*2+1]]->setSpeedPostNumberDot(val);
    }
    setModified();
}

void SpeedpostObj::setTrainType(int val){
    TDB* tdb = Game::trackDB;

    for(int j = 0; j < this->trItemId.size()/2; j++){
        if(tdb->trackItems[this->trItemId[j*2+1]] == NULL)
            continue;
        tdb->trackItems[this->trItemId[j*2+1]]->setSpeedPostTrainType(val);
    }
    setModified();
}


void SpeedpostObj::flip(bool flipShape){
    if(flipShape){
        Quat::rotateY(this->qDirection, this->qDirection, M_PI);
        this->setMartix();
    }

    TDB* tdb = Game::trackDB;
    for(int j = 0; j < this->trItemId.size()/2; j++){
        if(tdb->trackItems[this->trItemId[j*2+1]] == NULL)
            continue;
        tdb->trackItems[this->trItemId[j*2+1]]->flipSpeedpost();
    }
    setModified();
    drawPositions.clear();
    //delete[] drawPositions;
    //drawPositions = NULL;
    drawPosition = NULL;
}

void SpeedpostObj::expandTrItems(){
    TDB* tdb = Game::trackDB;
    qDebug() <<"expand sound region  "<<this->fileName;

    float* playerT = Vec2::fromValues(this->x, this->y);
    float pos[3];
    Vec3::set(pos, position[0], position[1], position[2]);
    float quat[4];
    float* buffer = new float[12];
    float vec1[3];
    float vec2[3];
    Vec3::set(vec1, -MaxPlacingDistance, 0, 0);
    Vec3::set(vec2, MaxPlacingDistance, 0, 0);
    Quat::fill(quat);
    Quat::rotateY(quat, quat, tdb->trackItems[this->trItemId[1]]->getSpeedpostRot()-M_PI/2);
    Vec3::transformQuat(vec1, vec1, quat);
    Vec3::transformQuat(vec2, vec2, quat);
    
    buffer[0] = position[0]+vec1[0];
    buffer[1] = position[1];
    buffer[2] = position[2]+vec1[2];
    buffer[6] = position[0]+vec2[0];
    buffer[7] = position[1];
    buffer[8] = position[2]+vec2[2]; 
    int len = 12;
    qDebug() << "and find intersections ";
    QVector<TDB::IntersectionPoint> ipoints;
    tdb->getSegmentIntersectionPositionOnTDB(ipoints, NULL, playerT, buffer, len, (float*)&pos);
    qDebug() << "intersection count: "<<ipoints.size();
        
    int tid = tdb->findTrItemNodeId(this->trItemId[1]);
    for(int i = 0; i < ipoints.size(); i++){
        qDebug() << ipoints[i].distance;
        
        if(ipoints[i].distance < 0.5)
            continue;
//        if(ipoints[i].idx == tid)
//            continue;
        
        int trNodeId = ipoints[i].idx;
        float metry = ipoints[i].m;
        
        qDebug() <<"new speedpost  "<<this->fileName;
Game::resetTools = true;  // fake signal
        tdb->newSpeedPostObject(tdb->trackItems[this->trItemId[1]]->getSpeedpostType(), trItemId, trNodeId, metry, this->typeID);
        tdb->trackItems[this->trItemId.last()]->setSpeedpostRot(tdb->trackItems[this->trItemId[1]]->getSpeedpostRot());
        tdb->trackItems[this->trItemId.last()]->setSpeedpostNumber(tdb->trackItems[this->trItemId[1]]->getSpeedpostNumber());
        tdb->trackItems[this->trItemId.last()]->setSpeedpostSpeed(tdb->trackItems[this->trItemId[1]]->getSpeedpostSpeed());
        tdb->trackItems[this->trItemId.last()]->setSpeedPostSpeedUnitId(tdb->trackItems[this->trItemId[1]]->getSpeedPostSpeedUnitId());
    }
    drawPositions.clear();
    setModified();
}

int SpeedpostObj::fixTrackItems(){
    if(this->trItemId.size() < 2)
        return -1;
    TRitem* item = Game::trackDB->trackItems[this->trItemId[1]];
    if(item == NULL) 
        return -1;
    if(this->trItemId.size() < 4)
        return 0;
    
    TRitem::SType stype = item->getSpeedpostType();

    //if(trItemId)
    int errors = 0;
    for(int i = 1; i < trItemId.size()/2; i++){
        if(this->trItemId[i*2] != 0)
            continue;
        item = Game::trackDB->trackItems[this->trItemId[i*2+1]];
        if(item == NULL) {
            errors++;
            continue;
        }
        if(stype != item->getSpeedpostType()){
            errors++;
            continue;
        }
    }
    
    if(errors > 0){
        for(int i = 1; i < trItemId.size()-1;){
            Game::trackDB->deleteTrItem(this->trItemId[i*2+1]);
            trItemId.remove(i*2+1);
            trItemId.remove(i*2+0);
        }
        selectionValue = 0;
        
        expandTrItems();
    }

    return errors;
}

void SpeedpostObj::deleteSelectedTrItem(){
    if(selectionValue < 1)
        return;
    if(selectionValue > trItemId.size()/2)
        return;
    if(trItemId.size() < 3)
        return;

    TDB* tdb = Game::trackDB;
    
    int i = selectionValue - 1;
    qDebug() << "remove tritem " << i;
    tdb->deleteTrItem(this->trItemId[i*2+1]);
    trItemId.remove(i*2+1);
    trItemId.remove(i*2+0);
    
    drawPositions.clear();
    setModified();
}

void SpeedpostObj::initTrItems(float* tpos){
    if(tpos == NULL)
        return;
    int trNodeId = tpos[0];
    float metry = tpos[1];
    
    trItemId.clear();
    TDB* tdb = Game::trackDB;
    qDebug() <<"new speedpost  "<<this->fileName;
    
    Game::resetTools = true;

    tdb->newSpeedPostObject(speedPostType, trItemId, trNodeId, metry, this->typeID);
    
    if(this->trItemId.size() < 2)
        return;
    this->rotate(0,tdb->trackItems[this->trItemId[1]]->getSpeedpostRot()-M_PI/2,0);
    drawPositions.clear();
}

void SpeedpostObj::set(QString sh, long long int val){
    if (sh == ("ref_value")) {
        speedPostId = val/1000;
        speedPostType = val - speedPostId*1000;
        qDebug() << "speedPostId "<<speedPostId<< " speedPostType " << speedPostType;
        SpeedPost *speedPost = Game::trackDB->speedPostDAT->speedPost[speedPostId];
        
            
        if(speedPostType == TRitem::SIGN){
            fileName = speedPost->speedSignShapeName;
            speedSignShape = new float[speedPost->speedSignShapeCount*4+1];
            speedSignShape[0] = speedPost->speedSignShapeCount;
            for(int i = 0; i<speedSignShape[0]*4; i++)
                speedSignShape[i+1] = speedPost->speedSignShape[i];
        }else if(speedPostType == TRitem::RESUME){
            fileName = speedPost->speedResumeSignShapeName;
            speedSignShape = new float[speedPost->speedResumeSignShapeCount*4+1];
            speedSignShape[0] = speedPost->speedResumeSignShapeCount;
            for(int i = 0; i<speedSignShape[0]*4; i++)
                speedSignShape[i+1] = speedPost->speedResumeSignShape[i];
        }else if(speedPostType == TRitem::WARNING){
            fileName = speedPost->speedWarningSignShapeName;
            speedSignShape = new float[speedPost->speedWarningSignShapeCount*4+1];
            speedSignShape[0] = speedPost->speedWarningSignShapeCount;
            for(int i = 0; i<speedSignShape[0]*4; i++)
                speedSignShape[i+1] = speedPost->speedWarningSignShape[i];
        }else if(speedPostType == TRitem::MILEPOST){
            fileName = speedPost->milepostShapeName;
            speedSignShape = new float[speedPost->milepostShapeCount*4+1];
            speedSignShape[0] = speedPost->milepostShapeCount;
            for(int i = 0; i<speedSignShape[0]*4; i++)
                speedSignShape[i+1] = speedPost->milepostShape[i];
        }
        
        if(speedPostType == TRitem::SIGN || speedPostType == TRitem::RESUME || speedPostType == TRitem::WARNING){
            speedDigitTex = speedPost->speedDigitTex;
            speedTextSize[0] = speedPost->speedTextSize[0];
            speedTextSize[1] = speedPost->speedTextSize[1];
            speedTextSize[2] = speedPost->speedTextSize[2];
        } else if(speedPostType == TRitem::MILEPOST) {
            speedDigitTex = speedPost->milepostDigitTex;
            speedTextSize[0] = speedPost->milepostTextSize[0];
            speedTextSize[1] = speedPost->milepostTextSize[1];
            speedTextSize[2] = speedPost->milepostTextSize[2];
        }
        return;
    }
    WorldObj::set(sh, val);
    return;
}

void SpeedpostObj::set(QString sh, QString val){
    if (sh == ("filename")) {
        fileName = val;
        return;
    }
    if (sh == ("ref_filename")) {
        fileName = val;
        return;
    }
    /*if (sh == ("ref_class")) {
        if(val == "speedsign")
            this->sType = SIGN;
        else if(val == "speedresume")
            this->sType = RESUME;
        else if(val == "speedwarning")
            this->sType = WARNING;
        else if(val == "milepost")
            this->sType = MILEPOST;
        else
            this->sType = UNDEFINED;
        return;
    }*/
    WorldObj::set(sh, val);
    return;
}

void SpeedpostObj::set(int sh, FileBuffer* data) {
    if (sh == TS::FileName) {
        data->off++;
        int slen = data->getShort()*2;
        fileName = *data->getString(data->off, data->off + slen);
        data->off += slen;
        return;
    }
    if (sh == TS::Speed_Digit_Tex) {
        data->off++;
        int slen = data->getShort()*2;
        speedDigitTex = *data->getString(data->off, data->off + slen);
        data->off += slen;
        return;
    }
    if (sh == TS::Speed_Sign_Shape) {
        data->off++;
        int len = data->getUint();
        speedSignShape = new float[len*4+1];
        speedSignShape[0] = len;
        for(int i = 0; i<speedSignShape[0]*4; i++)
            speedSignShape[i+1] = data->getFloat();
        return;
    }
    if (sh == TS::Speed_Text_Size) {
        data->off++;
        speedTextSize[0] = data->getFloat();
        speedTextSize[1] = data->getFloat();
        speedTextSize[2] = data->getFloat();
        return;
    }
    if (sh == TS::TrItemId) {
        data->off++;
        //this->trItemId = new int[2];
        //trItemId[0] = data->getUint();
        //trItemId[1] = data->getUint();
        trItemId.push_back(data->getUint());
        trItemId.push_back(data->getUint());
        return;
    }
    WorldObj::set(sh, data);
    return;
}

void SpeedpostObj::set(QString sh, FileBuffer* data) {
    if (sh == ("filename")) {
        fileName = ParserX::GetString(data);
        return;
    }
    if (sh == ("speed_digit_tex")) {
        speedDigitTex = ParserX::GetString(data);
        return;
    }
    if (sh == ("speed_sign_shape")) {
        int len = ParserX::GetNumber(data);
        speedSignShape = new float[len*4+1];
        speedSignShape[0] = len;
        for(int i = 0; i<speedSignShape[0]*4; i++)
            speedSignShape[i+1] = ParserX::GetNumber(data);
        return;
    }
    if (sh == ("speed_text_size")) {
        speedTextSize[0] = ParserX::GetNumber(data);
        speedTextSize[1] = ParserX::GetNumber(data);
        speedTextSize[2] = ParserX::GetNumber(data);
        return;
    }
    if (sh == ("tritemid")) {
        //this->trItemId = new int[2];
        //his->trItemId[0] = ParserX::GetUInt(data);
        //this->trItemId[1] = ParserX::GetUInt(data);
        trItemId.push_back(ParserX::GetUInt(data));
        trItemId.push_back(ParserX::GetUInt(data));
        return;
    }
    WorldObj::set(sh, data);

    return;
}

bool SpeedpostObj::select(int value){
    this->selectionValue = value;
    this->selected = true;
    return true;
}

void SpeedpostObj::render(GLUU* gluu, float lod, float posx, float posz, float* pos, float* target, float fov, int selectionColor, int renderMode) {
    if (!loaded) return;

    if (shape < 0) return;
    if (jestPQ < 2) return;
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
        
    Game::currentShapeLib->shape[shape]->render(selectionColor, 0);
    
    if(selected){
        drawBox();
    }
    gluu->mvPopMatrix();
    
    if(Game::viewInteractives && renderMode != gluu->RENDER_SHADOWMAP) 
        this->renderTritems(gluu, selectionColor);
};

void SpeedpostObj::renderTritems(GLUU* gluu, int selectionColor){
    
    ///////////////////////////////
    TDB* tdb = Game::trackDB;
    if(drawPositions.size() == 0){
        if(this->trItemId.size() < 2){
            qDebug() << "speedpost: fail trItemId";
            loaded = false;
            return;
        }

        drawLine = new OglObj();
        float* tpoints = new float[7];
        int ptr = 0;
        QVector<Vector4f> ipoints;
        int minlidx = -1;
        float minlval = 9999;
        
        if(pointer3d == NULL){
            pointer3d = new TrackItemObj(Game::pointerOut);  // EFO switching to the new shape newSymbols
            pointer3d->setMaterial(0.7,0.7,0.7);
        }
        if(pointer3dSelected == NULL){
            pointer3dSelected = new TrackItemObj(Game::pointerOut);   // EFO switching to the new shape newSymbols
            pointer3dSelected->setMaterial(0.9,0.9,0.9);
        }

        for(int i = 0; i < trItemId.size()/2; i++){
            if(this->trItemId[i*2] != 0)
                continue;
            int id = tdb->findTrItemNodeId(this->trItemId[i*2+1]);
            if (id < 0) {
                qDebug() << "speedpost: fail id";
                loaded = false;
                return;
            }
            
            drawPosition = new float[8];

            bool ok = tdb->getDrawPositionOnTrNode(drawPosition, id, tdb->trackItems[this->trItemId[i*2+1]]->getTrackPosition());
            if(!ok){
                this->loaded = false;
                return;
            }
            memcpy(tpoints, drawPosition, sizeof(float)*7 );
            drawPosition[7] = tdb->trackItems[this->trItemId[1]]->getSpeedpostRot();
            drawPosition[0] += 2048 * (drawPosition[5] - this->x);
            drawPosition[2] -= 2048 * (-drawPosition[6] - this->y);
            drawPositions.push_back(drawPosition);

            tpoints[0] += 2048 * (tpoints[5] - this->x);
            tpoints[2] -= 2048 * (-tpoints[6] - this->y);
            ipoints.push_back(Vector4f(tpoints[0], tpoints[1]+1.0, -tpoints[2], 0));
            if(tpoints[0] < minlval){
                minlval = tpoints[0];
                minlidx = ipoints.size()-1;
            }
        }

        if(ipoints.size() > 1){
            for(int i = 0; i < ipoints.size(); i++){
                ipoints[i].c = Vec3::dist((float*)&ipoints[minlidx], (float*)&ipoints[i]);
            }
            std::sort(ipoints.begin(), ipoints.end(), Vector4f::SortByC);
            float* lpoints = new float[ipoints.size()*6];
            for(int i = 0; i < ipoints.size()-1; i++){
                lpoints[ptr++] = ipoints[i].x;
                lpoints[ptr++] = ipoints[i].y;
                lpoints[ptr++] = ipoints[i].z;
                lpoints[ptr++] = ipoints[i+1].x;
                lpoints[ptr++] = ipoints[i+1].y;
                lpoints[ptr++] = ipoints[i+1].z;
            }
            drawLine->init(lpoints, ptr, RenderItem::V, GL_LINES);
            drawLine->setMaterial(1.0, 0.0, 0.0);
        }
    }
    
    //int aaa = drawPosition[0];
    //if(pos == NULL) return;
    gluu->currentShader->setUniformValue(gluu->currentShader->mvMatrixUniform, *reinterpret_cast<float(*)[4][4]> (gluu->mvMatrix));
    if(selectionColor == 0)
        drawLine->render();
    int useSC;
    

    for(int i = 0; i < drawPositions.size(); i++){
        drawPosition = drawPositions[i];
        gluu->mvPushMatrix();
        Mat4::translate(gluu->mvMatrix, gluu->mvMatrix, drawPosition[0] + 0 * (drawPosition[4] - this->x), drawPosition[1] + 1, -drawPosition[2] + 0 * (-drawPosition[5] - this->y));
        Mat4::rotateY(gluu->mvMatrix, gluu->mvMatrix, drawPosition[7]-M_PI/2);
        //Mat4::translate(gluu->mvMatrix, gluu->mvMatrix, this->trItemRData[0] + 2048*(this->trItemRData[3] - playerT[0] ), this->trItemRData[1]+2, -this->trItemRData[2] + 2048*(-this->trItemRData[4] - playerT[1]));
        //Mat4::translate(gluu->mvMatrix, gluu->mvMatrix, this->trItemRData[0] + 0, this->trItemRData[1]+0, -this->trItemRData[2] + 0);
        gluu->currentShader->setUniformValue(gluu->currentShader->mvMatrixUniform, *reinterpret_cast<float(*)[4][4]> (gluu->mvMatrix));
        useSC = (float)selectionColor/(float)(selectionColor+0.000001);
        if(this->selected && this->selectionValue == i+1) 
            pointer3dSelected->render(selectionColor | (i+1)*useSC);
        else
            pointer3d->render(selectionColor | (i+1)*useSC);

        if((Game::renderTrItems == false) && ((this->getNumber()) || (this->getSpeed())))
        {
            QString trRefN = "";
            QString trRefS = "";
            
            trRefN = QString::number(this->getNumber());
            trRefS = QString::number(this->getSpeed());
            
            if((this->getNumberInsteadSpeed()) || (this->getNumber()))
            {
                txt = new TextObj(trRefN, 4);    
                txt->setColor(99,149,238);   /// CORNFLOWER BLUE
            }

            if((this->getSpeedInsteadNumber()) || (this->getSpeed()))
            {
                txt = new TextObj(trRefS, 4);                    
                txt->setColor(69,242,72);  ///  GREEN
            }

            txt->render();
            txt2 = txt;
            txt2->render(M_PI);
            txt->loaded = true;
            
        }
             
        
        gluu->mvPopMatrix();
    }

};

bool SpeedpostObj::getSimpleBorder(float* border){
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

bool SpeedpostObj::getBoxPoints(QVector<float>& points){
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

int SpeedpostObj::getDefaultDetailLevel(){
    return -3;
}

void SpeedpostObj::save(QTextStream* out){
    if (!loaded) return;
    if(Game::useOnlyPositiveQuaternions)
        Quat::makePositive(this->qDirection);
    
*(out) << "	Speedpost (\n";
*(out) << "		UiD ( "<<this->UiD<<" )\n";
*(out) << "		Speed_Digit_Tex ( "<<this->speedDigitTex<<" )\n";
*(out) << "		Speed_Sign_Shape ( "<<this->speedSignShape[0];
for(int i = 0; i < this->speedSignShape[0]*4; i++)
    *(out) <<" "<<this->speedSignShape[i+1];
*(out) <<" )\n";
//<<" "<<this->speedSignShape[1]<<" "<<this->speedSignShape[2]<<" "<<this->speedSignShape[3]<<" "<<this->speedSignShape[4]<<" "<<this->speedSignShape[5]<<" "<<this->speedSignShape[6]<<" "<<this->speedSignShape[7]<<" "<<this->speedSignShape[8]<<" )\n";
*(out) << "		Speed_Text_Size ( "<<this->speedTextSize[0]<<" "<<this->speedTextSize[1]<<" "<<this->speedTextSize[2]<<" )\n";
for(int i = 0; i < this->trItemId.size(); i+=2)
    *(out) << "		TrItemId ( "<<this->trItemId[i]<<" "<<this->trItemId[i+1]<<" )\n";
*(out) << "		FileName ( "<<ParserX::AddComIfReq(this->fileName)<<" )\n";
*(out) << "		Position ( "<<this->position[0]<<" "<<this->position[1]<<" "<<-this->position[2]<<" )\n";
*(out) << "		QDirection ( "<<this->qDirection[0]<<" "<<this->qDirection[1]<<" "<<-this->qDirection[2]<<" "<<this->qDirection[3]<<" )\n";
if(Game::legacySupport)   *(out) << "		VDbId ( " << this->vDbId << " )\n";  // EFO 
*(out) << "	)\n";
}