/*  This file is part of TSRE5.
 *
 *  TSRE5 - train sim game engine and MSTS/OR Editors. 
 *  Copyright (C) 2016 Piotr Gadecki <pgadecki@gmail.com>
 *
 *  Licensed under GNU General Public License 3.0 or later. 
 *
 *  See LICENSE.md or https://www.gnu.org/licenses/gpl.html
 */

#include "HazardObj.h"
#include "SFile.h"
#include "ShapeLib.h"
#include "GLMatrix.h"
#include <math.h>
#include "ParserX.h"
#include <QDebug>
#include "Game.h"
#include "TDB.h"
#include "TRitem.h"
#include "TS.h"
#include "TrackItemObj.h"
#include "ErrorMessage.h"
#include "ErrorMessagesLib.h"

HazardObj::HazardObj() {
    this->shape = -1;
    this->loaded = false;
}

HazardObj::HazardObj(const HazardObj& o) : WorldObj(o) {
    if(o.trItemIdCount > 0){
        trItemIdCount = o.trItemIdCount;
        trItemId = new int[trItemIdCount];
        for(int i = 0; i < trItemIdCount; i++){
            trItemId[i] = o.trItemId[i];
        }
    }
}

WorldObj* HazardObj::clone(){
    return new HazardObj(*this);
}

HazardObj::~HazardObj() {
}

bool HazardObj::allowNew(){
    return true;
}

bool HazardObj::isTrackItem(){
    return true;
}

bool HazardObj::containsTrackItem(int tdbId, int id){
    for(int i = 0; i<this->trItemIdCount/2; i++){
        if(this->trItemId[i*2] == tdbId){
            if(this->trItemId[i*2+1] == id)
                return true;
        }
    }
    return false;
}

void HazardObj::addTrackItemIdOffset(unsigned int trackOffset, unsigned int roadOffset){
    for(int i = 0; i<this->trItemIdCount/2; i++){
        if(this->trItemId[i*2] == 0)
            this->trItemId[i*2+1] += trackOffset;
        if(this->trItemId[i*2] == 1)
            this->trItemId[i*2+1] += roadOffset;
    }
}

void HazardObj::getTrackItemIds(QVector<int> &ids, int tdbId){
    if(!this->loaded)
        return;
    for(int i = 0; i<this->trItemIdCount/2; i++){
        if(this->trItemId[i*2] == tdbId){
            ids.push_back(this->trItemId[i*2+1]);
        }
    }
}

void HazardObj::load(int x, int y) {
    this->shape = Game::currentShapeLib->addShape(resPath +"/"+ fileName);
    this->x = x;
    this->y = y;
    this->position[2] = -this->position[2];
    this->qDirection[2] = -this->qDirection[2];
    this->loaded = true;
    this->size = -1;
    this->skipLevel = 1;

    setMartix();
}

void HazardObj::deleteTrItems(){
    TDB* tdb = Game::trackDB;
    TDB* rdb = Game::roadDB;

    if(checkForErrors() != NULL){
        return;
    }
    
    for(int i = 0; i<this->trItemIdCount/2; i++){
        if(this->trItemId[i*2] == 0)
            tdb->deleteTrItem(this->trItemId[i*2+1]);
        else if(this->trItemId[i*2] == 1)
            rdb->deleteTrItem(this->trItemId[i*2+1]);
        this->trItemId[i*2+1] = -1;
    }
}

ErrorMessage* HazardObj::checkForErrors(){
    TDB* tdb = Game::trackDB;
    TRitem* item = NULL;
    for(int i = 0; i<this->trItemIdCount/2; i++){
        if(this->trItemId[i*2] != 0)
            continue;
        item = tdb->trackItems[this->trItemId[i*2+1]];
        
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
        if((item->type != "hazarditem") && (item->type != "hazzarditem"))  {
            ErrorMessage *e = new ErrorMessage(
                ErrorMessage::Type_Error, 
                ErrorMessage::Source_World, 
                QString("Object '") + type + "' - referenced trackItem has wrong type. UiD: " + QString::number(UiD) + ". ",
                        QString("World Object doesn't match TDB data. Is World Database and TDB out of sync? \n")+
                        "Expected: hazarditem but found: "+item->type+" .\n"
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


void HazardObj::initTrItems(float* tpos){
    if(tpos == NULL)
        return;
    int trNodeId = tpos[0];
    float metry = tpos[1];
    
    TDB* tdb = Game::trackDB;
    qDebug() <<"new hazard  "<<this->fileName;
    
    trItemIdCount = 2;
    tdb->newHazardObject(trItemId, trNodeId, metry, this->typeID);
    drawPosition = NULL;
}

void HazardObj::set(QString sh, QString val){
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

void HazardObj::set(int sh, FileBuffer* data) {
    if (sh == TS::FileName) {
        data->off++;
        int slen = data->getShort()*2;
        fileName = *data->getString(data->off, data->off + slen);
        data->off += slen;
        return;
    }
    if (sh == TS::TrItemId) {
        data->off++;
        this->trItemIdCount = 2;
        trItemId = new int[2];
        trItemId[0] = data->getUint();
        trItemId[1] = data->getUint();
        return;
    }
    WorldObj::set(sh, data);
    return;
}

void HazardObj::set(QString sh, FileBuffer* data) {
    if (sh == ("filename")) {
        fileName = ParserX::GetString(data);
        return;
    }
    if (sh == ("tritemid")) {
        this->trItemIdCount = 2;
        trItemId = new int[2];
        trItemId[0] = ParserX::GetNumber(data);
        trItemId[1] = ParserX::GetNumber(data);
        return;
    }
    WorldObj::set(sh, data);
    return;
}

void HazardObj::render(GLUU* gluu, float lod, float posx, float posz, float* pos, float* target, float fov, int selectionColor, int renderMode) {
    if (!loaded) 
        return;
    if (shape < 0) return;
    if (jestPQ < 2) return;

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
    
    if(Game::viewInteractives) 
        this->renderTritems(gluu, selectionColor);
};

void HazardObj::renderTritems(GLUU* gluu, int selectionColor){
    
    ///////////////////////////////
    TDB* tdb = Game::trackDB;
    if(drawPosition == NULL){
        int id = tdb->findTrItemNodeId(this->trItemId[1]);
        if (id < 0) {
            qDebug() << "fail id";
            return;
        }
                //qDebug() << "id: "<< this->trItemId[i*2+1] << " "<< id;
        drawPosition = new float[7];
        bool ok = tdb->getDrawPositionOnTrNode(drawPosition, id, tdb->trackItems[this->trItemId[1]]->getTrackPosition());
        if(!ok){
            this->loaded = false;
            return;
        }
        drawPosition[0] += 2048 * (drawPosition[5] - this->x);
        drawPosition[2] -= 2048 * (-drawPosition[6] - this->y);
        if(pointer3d == NULL){
            pointer3d = new TrackItemObj(6);
            pointer3d->setMaterial(0.8,0.2,0.8);
        }
    }

    //if(pos == NULL) return;
    int useSC;

    gluu->mvPushMatrix();
    Mat4::translate(gluu->mvMatrix, gluu->mvMatrix, drawPosition[0] + 0 * (drawPosition[4] - this->x), drawPosition[1] + 1, -drawPosition[2] + 0 * (-drawPosition[5] - this->y));
    Mat4::rotateY(gluu->mvMatrix, gluu->mvMatrix, drawPosition[3]);
    //Mat4::translate(gluu->mvMatrix, gluu->mvMatrix, this->trItemRData[0] + 2048*(this->trItemRData[3] - playerT[0] ), this->trItemRData[1]+2, -this->trItemRData[2] + 2048*(-this->trItemRData[4] - playerT[1]));
    //Mat4::translate(gluu->mvMatrix, gluu->mvMatrix, this->trItemRData[0] + 0, this->trItemRData[1]+0, -this->trItemRData[2] + 0);
    gluu->currentShader->setUniformValue(gluu->currentShader->mvMatrixUniform, *reinterpret_cast<float(*)[4][4]> (gluu->mvMatrix));
    useSC = (float)selectionColor/(float)(selectionColor+0.000001);
    pointer3d->render(selectionColor | 1*useSC);
   
    if(Game::renderTrItems == false)            
    {
        trRef.clear();
        trRef = QString::number(this->trItemId[1]);
        TextObj* txt;  /// EFO
        TextObj* txt2;  /// EFO
        txt = new TextObj(trRef, 4);    
        txt->setColor(200,55,200);
        txt->render();
        txt2 = txt;
        txt2->render(M_PI);
    }
    gluu->mvPopMatrix();

        

};

bool HazardObj::getSimpleBorder(float* border){
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

bool HazardObj::getBoxPoints(QVector<float>& points){
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

int HazardObj::getDefaultDetailLevel(){
    return -10;
}

void HazardObj::save(QTextStream* out){
    if (!loaded) return;
    if(Game::useOnlyPositiveQuaternions)
        Quat::makePositive(this->qDirection);
    
*(out) << "	Hazard (\n";
*(out) << "		UiD ( "<<this->UiD<<" )\n";
*(out) << "		TrItemId ( "<<this->trItemId[0]<<" "<<this->trItemId[1]<<" )\n";
*(out) << "		FileName ( "<<ParserX::AddComIfReq(this->fileName)<<" )\n";
*(out) << "		Position ( "<<this->position[0]<<" "<<this->position[1]<<" "<<-this->position[2]<<" )\n";
*(out) << "		QDirection ( "<<this->qDirection[0]<<" "<<this->qDirection[1]<<" "<<-this->qDirection[2]<<" "<<this->qDirection[3]<<" )\n";
if(Game::legacySupport)   *(out) << "		VDbId ( " << this->vDbId << " )\n";  // EFO 
if(this->staticDetailLevel > -1)
*(out) << "		StaticDetailLevel ( "<<this->staticDetailLevel<<" )\n";
*(out) << "	)\n";
}