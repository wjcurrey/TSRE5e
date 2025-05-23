/*  This file is part of TSRE5.
 *
 *  TSRE5 - train sim game engine and MSTS/OR Editors. 
 *  Copyright (C) 2016 Piotr Gadecki <pgadecki@gmail.com>
 *
 *  Licensed under GNU General Public License 3.0 or later. 
 *
 *  See LICENSE.md or https://www.gnu.org/licenses/gpl.html
 */

#include "TransferObj.h"
#include "ShapeLib.h"
#include "GLMatrix.h"
#include <math.h>
#include "ParserX.h"
#include <QDebug>
#include <cstdlib>
#include "TexLib.h"
#include "Vector2f.h"
#include "TerrainLib.h"
#include <QOpenGLShaderProgram>
#include "Game.h"
#include "TS.h"
#include "Ref.h"

TransferObj::TransferObj() {
    this->width = 10;
    this->height = 10;
    this->texture = "shadwrct.ace";
}

TransferObj::TransferObj(const TransferObj& o) : WorldObj(o) {
    texture = o.texture;
    width = o.width;
    height = o.height;

    tex = o.tex;
    init = false;
    if(o.texturePath != NULL){
        texturePath = new QString();
        *texturePath = *o.texturePath;
    }
}

WorldObj* TransferObj::clone(){
    return new TransferObj(*this);
}

TransferObj::~TransferObj() {
    
}

void TransferObj::load(int x, int y) {
    this->x = x;
    this->y = y;
    this->position[2] = -this->position[2];
    this->loaded = true;
    this->size = -1;
    this->tex = -1;
    this->init = false;
    this->skipLevel = 3;
    this->modified = false;
}

bool TransferObj::allowNew(){
    return true;
}

void TransferObj::set(QString sh, QString val){
    if (sh == ("filename")) {
        texture = val;
        return;
    }
    if (sh == ("ref_filename")) {
        texture = val;
        //TexLib::addTex(resPath+"/"+texture);
        return;
    }
    WorldObj::set(sh, val);
    return;
}

void TransferObj::set(QString sh, long long int val){
    if (sh == ("ref_value")) {
        if(val != 0){
        long long int val1 = (val & 0xFFFFFFFF00000000) >> 32;
        long long int val2 = (val & 0x00000000FFFFFFFF);
        width = (float)val1/1000;
        height = (float)val2/1000;
        //TexLib::addTex(resPath+"/"+texture);
        }
        return;
    }    
    WorldObj::set(sh, val);
    return;
}

void TransferObj::set(QString sh, float val){
    if (sh == ("width")) {
        width = val;
        return;
    }
    if (sh == ("height")) {
        height = val;
        return;
    }
    WorldObj::set(sh, val);
    return;
}

void TransferObj::set(int sh, FileBuffer* data) {
    if (sh == TS::FileName) {
        data->off++;
        int slen = data->getShort()*2;
        texture = *data->getString(data->off, data->off + slen);
        data->off += slen;
        return;
    }
    if (sh == TS::Width) {
        data->off++;
        width = data->getFloat();
        return;
    }
    if (sh == TS::Height) {
        data->off++;
        height = data->getFloat();
        return;
    }
    WorldObj::set(sh, data);
    return;
}

void TransferObj::set(QString sh, FileBuffer* data) {
    if (sh == ("filename")) {
        texture = ParserX::GetString(data);
        return;
    }
    if (sh == ("width")) {
        width = ParserX::GetNumber(data);
        return;
    }
    if (sh == ("height")) {
        height = ParserX::GetNumber(data);
        return;
    }
    WorldObj::set(sh, data);
    return;
}

Ref::RefItem* TransferObj::getRefInfo(){
    Ref::RefItem* r = new Ref::RefItem();
    r->type = this->type;
    r->filename.push_back(this->texture);
    
    long long int val1 = this->width*1000;
    long long int val2 = this->height*1000;
    r->value = val1 << 32 | val2;
    return r;
}

void TransferObj::deleteVBO(){
    //this->shape.deleteVBO();
    this->init = false;
    this->box.deleteVBO();
}

void TransferObj::translate(float px, float py, float pz){
    this->position[0]+=px;
    //this->position[1]+=py;
    this->position[2]+=pz;
    setModified();
    deleteVBO();
}

void TransferObj::rotate(float x, float y, float z){
    if(matrix3x3 != NULL) matrix3x3 = NULL;
    if(x!=0) Quat::rotateX(this->qDirection, this->qDirection, x);
    if(y!=0) Quat::rotateY(this->qDirection, this->qDirection, y);
    if(z!=0) Quat::rotateZ(this->qDirection, this->qDirection, z);
    setModified();
    deleteVBO();
}

void TransferObj::resize(float x, float y, float z){
    if(x == 0 && y == 0) return;
    this->width += x;
    this->height += y;
    setModified();
    deleteVBO();
}

void TransferObj::render(GLUU* gluu, float lod, float posx, float posz, float* pos, float* target, float fov, int selectionColor, int renderMode) {
    if (!loaded) 
        return;
    if(renderMode == gluu->RENDER_SHADOWMAP) 
        return;
    //if (jestPQ < 2) return;
    //GLUU* gluu = GLUU::get();
    //if((this.position===undefined)||this.qDirection===undefined) return;

    /*if (size > 0) {
        if ((lod > size)) {
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
            if ((ccos > 0) && (xxx > size + 150) && (skipLevel == 1)) return;
        }
    } else {
        if (ShapeLib::shape[shape]->loaded)
            size = ShapeLib::shape[shape]->size;
    }
*/
    Mat4::translate(gluu->mvMatrix, gluu->mvMatrix, position[0], 0, position[2]);
    //float scale = sqrt(qDirection[0] * qDirection[0] + qDirection[1] * qDirection[1] + qDirection[2] * qDirection[2]);
    //float angle = ((acos(qDirection[3])*360) / M_PI);
    //Mat4::rotate(gluu->mvMatrix, gluu->mvMatrix, gluu->degToRad(-angle), -qDirection[0] * scale, -qDirection[1] * scale, qDirection[2] * scale);
    //Mat4::rotate(gluu->mvMatrix, gluu->mvMatrix, gluu->degToRad(180), 0, -1, 0);

    //if(selected){
    //    selected = !selected;
    //    selectionColor = 155;
    //}
    //gluu.setMatrixUniforms();

    //
    //var z = this.position[0]*mmm[9] + this.position[1]*mmm[7] + this.position[2]*mmm[9];

    gluu->currentShader->setUniformValue(gluu->currentShader->mvMatrixUniform, *reinterpret_cast<float(*)[4][4]> (gluu->mvMatrix));
       
    drawShape(selectionColor);
    if(selected){
        drawBox();
    }
};

void TransferObj::reload(){

}


void TransferObj::drawShape(int selectionColor){

    if (!init) {
        if(!Game::ignoreLoadLimits){
            if(Game::allowObjLag < 1)  return;
            Game::allowObjLag-=2;
        }
        
            GLUU* gluu = GLUU::get();
            float alpha = -gluu->alphaTest;
            
            float scale = (float) sqrt(qDirection[0] * qDirection[0] + qDirection[1] * qDirection[1] + qDirection[2] * qDirection[2]);
            float off = ((qDirection[1]+0.000001f)/fabs(scale+0.000001f))*(float)-acos(qDirection[3])*2;
        
            Vector2f x1y1(-width/2,-height/2, off, 0);
            Vector2f x1y2(-width/2,height/2, off, 0);
            Vector2f x2y1(width/2,-height/2, off, 0);
            Vector2f x1y12 = x1y2.subv(x1y1);
            Vector2f x12y1 = x2y1.subv(x1y1);
            float x1y12d = x1y12.getDlugosc();
            float x12y1d = x12y1.getDlugosc();
            
            float step = 2.0;
            bool addR = true;
            if(x12y1d*x1y12d < 2000) {
                step = 1;
                addR = false;
            }
                
            int iloscv = (int)((x12y1d/step)+1)*(int)((x1y12d/step)+1);
            float* punkty = new float[iloscv*54];
            
            int ptr = 0;
            float wysokosc = 0;
            for(float j = 0; j < x12y1d; j+=step){
                float jj = j+step;
                if(jj>x12y1d) jj = x12y1d;
                for(float i = 0; i < x1y12d; i+=step){

                        float ii = i+step;
                        if(ii>x1y12d) ii = x1y12d;
                        
                        wysokosc = Game::terrainLib->getHeight(x, y, x1y1.x + x1y12.divf(x1y12d/i).x + x12y1.divf(x12y1d/j).x + position[0], ( x1y1.y + x1y12.divf(x1y12d/i).y + x12y1.divf(x12y1d/j).y + position[2]), addR);
                        punkty[ptr++] = x1y1.x + x1y12.divf(x1y12d/i).x + x12y1.divf(x12y1d/j).x;
                        punkty[ptr++] = wysokosc+0.05f;
                        punkty[ptr++] = x1y1.y + x1y12.divf(x1y12d/i).y + x12y1.divf(x12y1d/j).y;
                        punkty[ptr++] = 0; punkty[ptr++] = 1; punkty[ptr++] = 0;
                        punkty[ptr++] = j/x12y1d;
                        punkty[ptr++] = i/x1y12d;
                        punkty[ptr++] = alpha;

                        wysokosc = Game::terrainLib->getHeight(x, y, x1y1.x + x1y12.divf(x1y12d/ii).x + x12y1.divf(x12y1d/j).x + position[0], ( x1y1.y + x1y12.divf(x1y12d/ii).y + x12y1.divf(x12y1d/j).y + position[2]), addR);
                        punkty[ptr++] = x1y1.x + x1y12.divf(x1y12d/ii).x + x12y1.divf(x12y1d/j).x;
                        punkty[ptr++] = wysokosc+0.05f;
                        punkty[ptr++] = x1y1.y + x1y12.divf(x1y12d/ii).y + x12y1.divf(x12y1d/j).y;
                        punkty[ptr++] = 0; punkty[ptr++] = 1; punkty[ptr++] = 0;
                        punkty[ptr++] = j/x12y1d;
                        punkty[ptr++] = ii/x1y12d;
                        punkty[ptr++] = alpha;
                        
                        wysokosc = Game::terrainLib->getHeight(x, y, x1y1.x + x1y12.divf(x1y12d/ii).x + x12y1.divf(x12y1d/jj).x + position[0], ( x1y1.y + x1y12.divf(x1y12d/ii).y + x12y1.divf(x12y1d/jj).y + position[2]), addR);
                        punkty[ptr++] = x1y1.x + x1y12.divf(x1y12d/ii).x + x12y1.divf(x12y1d/jj).x;
                        punkty[ptr++] = wysokosc+0.05f;
                        punkty[ptr++] = x1y1.y + x1y12.divf(x1y12d/ii).y + x12y1.divf(x12y1d/jj).y;
                        punkty[ptr++] = 0; punkty[ptr++] = 1; punkty[ptr++] = 0;
                        punkty[ptr++] = jj/x12y1d;
                        punkty[ptr++] = ii/x1y12d;
                        punkty[ptr++] = alpha;

                        wysokosc = Game::terrainLib->getHeight(x, y, x1y1.x + x1y12.divf(x1y12d/i).x + x12y1.divf(x12y1d/j).x + position[0], ( x1y1.y + x1y12.divf(x1y12d/i).y + x12y1.divf(x12y1d/j).y + position[2]), addR);
                        punkty[ptr++] = x1y1.x + x1y12.divf(x1y12d/i).x + x12y1.divf(x12y1d/j).x;
                        punkty[ptr++] = wysokosc+0.05f;
                        punkty[ptr++] = x1y1.y + x1y12.divf(x1y12d/i).y + x12y1.divf(x12y1d/j).y;
                        punkty[ptr++] = 0; punkty[ptr++] = 1; punkty[ptr++] = 0;
                        punkty[ptr++] = j/x12y1d;
                        punkty[ptr++] = i/x1y12d;
                        punkty[ptr++] = alpha;

                        wysokosc = Game::terrainLib->getHeight(x, y, x1y1.x + x1y12.divf(x1y12d/ii).x + x12y1.divf(x12y1d/jj).x + position[0], ( x1y1.y + x1y12.divf(x1y12d/ii).y + x12y1.divf(x12y1d/jj).y + position[2]), addR);
                        punkty[ptr++] = x1y1.x + x1y12.divf(x1y12d/ii).x + x12y1.divf(x12y1d/jj).x;
                        punkty[ptr++] = wysokosc+0.05f;
                        punkty[ptr++] = x1y1.y + x1y12.divf(x1y12d/ii).y + x12y1.divf(x12y1d/jj).y;
                        punkty[ptr++] = 0; punkty[ptr++] = 1; punkty[ptr++] = 0;
                        punkty[ptr++] = jj/x12y1d;
                        punkty[ptr++] = ii/x1y12d;
                        punkty[ptr++] = alpha;
                        
                        wysokosc = Game::terrainLib->getHeight(x, y, x1y1.x + x1y12.divf(x1y12d/i).x + x12y1.divf(x12y1d/jj).x + position[0], ( x1y1.y + x1y12.divf(x1y12d/i).y + x12y1.divf(x12y1d/jj).y + position[2]), addR);
                        punkty[ptr++] = x1y1.x + x1y12.divf(x1y12d/i).x + x12y1.divf(x12y1d/jj).x;
                        punkty[ptr++] = wysokosc+0.05f;
                        punkty[ptr++] = x1y1.y + x1y12.divf(x1y12d/i).y + x12y1.divf(x12y1d/jj).y;
                        punkty[ptr++] = 0; punkty[ptr++] = 1; punkty[ptr++] = 0;
                        punkty[ptr++] = jj/x12y1d;
                        punkty[ptr++] = i/x1y12d;
                        punkty[ptr++] = alpha;
                }
            }
            
        int esdAlternativeTexture = 0x01;
        QString seasonPath;
        if((esdAlternativeTexture & Game::TextureFlags[Game::season]) != 0)
            seasonPath = Game::season.toLower() + "/";

        if(Game::season.toLower() == "winter" || Game::season.toLower() == "autumnsnow" || Game::season.toLower() == "wintersnow" || Game::season.toLower() == "springsnow" ){
            if(esdAlternativeTexture & Game::TextureFlags["snow"] != 0)
                seasonPath = "snow/";
            if(esdAlternativeTexture & Game::TextureFlags["snowtrack"] != 0)
                seasonPath = "snow/";
        }
        
        texturePath = new QString(resPath.toLower()+"/"+seasonPath+texture.toLower());
        shape.setMaterial(texturePath);
        shape.init(punkty, ptr, RenderItem::VNTA, GL_TRIANGLES);
        delete[] punkty;
        init = true;
    }
    
    shape.render(selectionColor);
}

bool TransferObj::getBoxPoints(QVector<float>& points){
    if (!loaded) 
        return false;
    float scale = (float) sqrt(qDirection[0] * qDirection[0] + qDirection[1] * qDirection[1] + qDirection[2] * qDirection[2]);
    float off = ((qDirection[1]+0.000001f)/fabs(scale+0.000001f))*(float)-acos(qDirection[3])*2;
        
            Vector2f x1y1(-width/2,-height/2, off, 0);
            Vector2f x1y2(-width/2,height/2, off, 0);
            Vector2f x2y1(width/2,-height/2, off, 0);
            Vector2f x1y12 = x1y2.subv(x1y1);
            Vector2f x12y1 = x2y1.subv(x1y1);
            float x1y12d = x1y12.getDlugosc();
            float x12y1d = x12y1.getDlugosc();
            float wysokosc = 0;
            float step = 2;
            
            for(float i = 0; i <= x1y12d; i+=x1y12d){
                for(float j = 0; j < x12y1d; j+=step){
                    float jj = j+step;
                    if(jj>x12y1d) jj = x12y1d;          

                    wysokosc = Game::terrainLib->getHeight(x, y, x1y1.x + x1y12.divf(x1y12d/i).x + x12y1.divf(x12y1d/j).x + position[0], ( x1y1.y + x1y12.divf(x1y12d/i).y + x12y1.divf(x12y1d/j).y + position[2]));
                    points << x1y1.x + x1y12.divf(x1y12d/i).x + x12y1.divf(x12y1d/j).x;
                    points << wysokosc+0.5f;
                    points << x1y1.y + x1y12.divf(x1y12d/i).y + x12y1.divf(x12y1d/j).y;
                    wysokosc = Game::terrainLib->getHeight(x, y, x1y1.x + x1y12.divf(x1y12d/i).x + x12y1.divf(x12y1d/jj).x + position[0], ( x1y1.y + x1y12.divf(x1y12d/i).y + x12y1.divf(x12y1d/jj).y + position[2]));
                    points << x1y1.x + x1y12.divf(x1y12d/i).x + x12y1.divf(x12y1d/jj).x;
                    points << wysokosc+0.5f;
                    points << x1y1.y + x1y12.divf(x1y12d/i).y + x12y1.divf(x12y1d/jj).y;
                }
            }
            for(float j = 0; j <= x12y1d; j+=x12y1d){
                for(float i = 0; i < x1y12d; i+=step){
                    float ii = i+step;
                    if(ii>x1y12d) ii = x1y12d;          

                    wysokosc = Game::terrainLib->getHeight(x, y, x1y1.x + x1y12.divf(x1y12d/i).x + x12y1.divf(x12y1d/j).x + position[0], ( x1y1.y + x1y12.divf(x1y12d/i).y + x12y1.divf(x12y1d/j).y + position[2]));
                    points << x1y1.x + x1y12.divf(x1y12d/i).x + x12y1.divf(x12y1d/j).x;
                    points << wysokosc+0.5f;
                    points << x1y1.y + x1y12.divf(x1y12d/i).y + x12y1.divf(x12y1d/j).y;
                    wysokosc = Game::terrainLib->getHeight(x, y, x1y1.x + x1y12.divf(x1y12d/ii).x + x12y1.divf(x12y1d/j).x + position[0], ( x1y1.y + x1y12.divf(x1y12d/ii).y + x12y1.divf(x12y1d/j).y + position[2]));
                    points << x1y1.x + x1y12.divf(x1y12d/ii).x + x12y1.divf(x12y1d/j).x;
                    points << wysokosc+0.5f;
                    points << x1y1.y + x1y12.divf(x1y12d/ii).y + x12y1.divf(x12y1d/j).y;
                }
            }
            return true;
}

int TransferObj::getTexId(){
    return this->shape.getTexId();
}

int TransferObj::getDefaultDetailLevel(){
    return -1;
}

void TransferObj::save(QTextStream* out){
    if (!loaded) return;
    if(Game::useOnlyPositiveQuaternions)
        Quat::makePositive(this->qDirection);
    
*(out) << "	Transfer (\n";
*(out) << "		UiD ( "<<this->UiD<<" )\n";
*(out) << "		Width ( "<<this->width<<" )\n";
*(out) << "		Height ( "<<this->height<<" )\n";
*(out) << "		FileName ( "<<ParserX::AddComIfReq(this->texture)<<" )\n";
*(out) << "		StaticFlags ( "<<ParserX::MakeFlagsString(this->staticFlags)<<" )\n";
*(out) << "		Position ( "<<this->position[0]<<" "<<this->position[1]<<" "<<-this->position[2]<<" )\n";
*(out) << "		QDirection ( "<<this->qDirection[0]<<" "<<this->qDirection[1]<<" "<<this->qDirection[2]<<" "<<this->qDirection[3]<<" )\n";
if(Game::legacySupport)   *(out) << "		VDbId ( " << this->vDbId << " )\n";  // EFO 
if(this->staticDetailLevel > -1)
*(out) << "		StaticDetailLevel ( "<<this->staticDetailLevel<<" )\n";
*(out) << "	)\n";
}