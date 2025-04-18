/*  This file is part of TSRE5.
 *
 *  TSRE5 - train sim game engine and MSTS/OR Editors. 
 *  Copyright (C) 2016 Piotr Gadecki <pgadecki@gmail.com>
 *
 *  Licensed under GNU General Public License 3.0 or later. 
 *
 *  See LICENSE.md or https://www.gnu.org/licenses/gpl.html
 */

#ifndef TERRAIN_H
#define	TERRAIN_H
#include <QString>
#include "GLUU.h"
#include "TFile.h"
#include "Vector3f.h"
#include "OglObj.h"
#include "GameObj.h"

class Brush;
class TerrainInfo;
class FileBuffer;
class QDataStream;

class Terrain : public GameObj {
    Q_OBJECT
public:
    static Brush* DefaultBrush;
    int loaded = false;
    float **terrainData;
    bool inUse = true;
    bool showBlob = false;
    float mojex = 0;
    float mojez = 0;
    QString name;
    bool lowTile = false;
    Terrain();
    Terrain(TerrainInfo *ti);
    Terrain(float x, float y);
    Terrain(const Terrain& orig);
    virtual void saveTfileToStream(QDataStream &out);
    virtual void saveRAWfileToStream(QDataStream &out);
    virtual void saveRAWfileToStreamFloat(QDataStream &out);
    virtual void saveFfileToStream(QDataStream &out);
    virtual void loadTFile(FileBuffer *data);
    virtual void loadRAWFile(FileBuffer *data);
    virtual void loadFFile(FileBuffer *data);
    virtual void updateTFile();
    virtual ~Terrain();
    static void SaveEmpty(QString name, int samples = 256, int sampleSize = 8, int patches = 16, bool low = false);
    static QString getTileName(int x, int y);
    static QString getTileNameExperimental(int x, int y);
    static QString getTileNameExperimental2(int x, int y);
    QString getTileName();
    bool isXYinside(int x, int y);
    int getPatchSize();
    int getSampleSize();
    void getLocalCoords(int x, int z, float &posx, float &posz);
    void getPatchCoords(int &x, int &z, float &posx, float &posz);
    void getCornerCoordsXY(int &x, int &z, int ox, int oz);
    void fillTerrainDataX(Terrain* adjacent);
    void fillTerrainDataY(Terrain* adjacent);
    void fillTerrainDataXY(Terrain* adjacent);
    void save();
    void refresh();
    bool isModified();
    void setModified(bool value = true);
    void getLowCornerTileXY(int &X, int &Y);
    int getSampleCount();
    float setHeight(int x, int z, float posx, float posz, float val, bool add = false);
    void setFixedHeight(float val);
    void paintTexture(Brush* brush, int x, int z, float posx, float posz);
    void lockTexture(Brush* brush, int x, int z, float posx, float posz);
    void setTexture(Brush* brush, int x, int z, float posx, float posz);
    void setTexture(Brush* brush, int u);
    void setTexture(QString textureName, int x, int z, float posx, float posz, QString transformation = "");
    void toggleWaterDraw(int x, int z, float posx, float posz, float direction);
    void setWaterLevelGui();
    void setWaterLevel(float nw, float ne, float sw, float se);
    float getAvgVaterLevel();
    void getWaterLevels(float *w);
    float getWaterLevelNW();
    float getWaterLevelNE();
    float getWaterLevelSW();
    float getWaterLevelSE();
    void setWaterLevelNW(float val);
    void setWaterLevelNE(float val);
    void setWaterLevelSW(float val);
    void setWaterLevelSE(float val);
    void setAvgWaterLevel(float val);
    void getAdjacentWaterLevels(float *w);
    void setAdjacentWaterLevels(float *w);
    void toggleDraw(int x, int z, float posx, float posz);
    void setWaterDraw();
    void setDraw();
    void hideWaterDraw();
    void hideDraw();
    void toggleDraw();
    void toggleWaterDraw();
    void setDrawAdjacent();
    void rotatePatchTexture();
    void mirrorXPatchTexture();
    void mirrorYPatchTexture();
    float getPatchScaleTex();
    float getPatchScaleTexX();
    float getPatchScaleTexY();
    QString getPatchRotationName();
    void scalePatchTexCoords(float val);
    void scalePatchTexCoordsX(float val);
    void scalePatchTexCoordsY(float val);
    QString getPatchTexTransformString();
    QString getPatchTexTransformString(int u);
    QString getPatchTexTransformString(int x, int z, float posx, float posz);
    void setPatchTexTransform(QString val);
    void setPatchTexTransform(QString val, int u);
    void removeAllGaps();
    void toggleGaps(int x, int z, float posx, float posz, float direction);
    void setErrorBias(int x, int z, float posx, float posz, float val);
    float getErrorBias();
    void getWTileIds(QSet<int> &ids);
    void setErrorBias(float val);
    void setTileBlob();
    void makeTextureFromMap();
    void removeTextureFromMap();
    void fillHeightMap(float *data);
    int getTexture(int x, int z, float posx, float posz);
    int getSelectedPathId();
    int getSelectedShaderId();
    QString getPatchMainTextureName();
    QString getPatchMainTextureName(int u);
    QString getPatchMainTextureName(int x, int z, float posx, float posz);
    int getPatchFlags(int x, int z, float posx, float posz);
    void setPatchFlags(int x, int z, float posx, float posz, int val);
    bool select(int value);
    bool select(int value, bool oneMore);
    bool unselect();
    void resetPatchTexCoords(int uu = -1);
    void pushContextMenuActions(QMenu *menu);
    void pushRenderItem(float lodx, float lodz, int tileX, int tileY, float* playerW, float* target, float fov, int selectionColor);
    void pushRenderItemWater(float lodx, float lodz, float tileX, float tileY, float* playerW, float* target, float fov, int layer, int selectionColor = 0);
    void render(float lodx, float lodz, int tileX, int tileY, float* playerW, float* target, float fov, int selectionColor);
    void renderWater(float lodx, float lodz, float tileX, float tileY, float* playerW, float* target, float fov, int layer, int selectionColor = 0);
    void refreshWaterShapes();
    void getRotation(float *rot, int x, int z, int posx, int posz);
    float getHeight(int x, int z, float posx, float posz, bool addR);
 
    
public slots:
    void menuToggleWater();
    void menuToggleDraw();
    void menuPutTexture();
    void menuSelectObjects();
    
protected:
    static QString TileDir[2];
    
    unsigned char **fData;
    bool jestF = false;
    bool modifiedF = false;
    bool isOgl = false;
    bool modified = false;
    QString texturepath;
    QString rootTexturepath;
    Vector3f **vertexData;//[257][257];
    Vector3f **normalData;//[257][257];
    bool hidden[256];
    bool uniqueTex[256];
    int texid[256];
    int texid2[256];
    bool texModified[256];
    bool texLocked[256];
    bool selectedPatchs[256];
    QOpenGLBuffer *VBO = NULL;
    QOpenGLVertexArrayObject *VAO = NULL;

    OglObj lines;
    OglObj mlines;
    OglObj slines;
    OglObj ulines;
    OglObj lockedlines;
    OglObj selectedlines;
    
    struct WaterTile {
        OglObj w[256];
    };
    QMap<int, WaterTile*> water;
    //OglObj water[256];
    
    
    OglObj terrainBlob;
    //QOpenGLBuffer wVBO[256];
    //QOpenGLVertexArrayObject wVAO[256];
    //bool jestW[256];
    int wTexid = -1;
    TFile* tfile;
    //int selectedPathId = -1;
    
    void saveRAW(QString name);
    void saveRAW(QDataStream &write);
    void saveRAWFloat(QDataStream &write);
    bool readRAW(QString fSfile);
    void readRAW(FileBuffer *data);
    void readRAWFloat(FileBuffer *data);
    bool readF(QString fSfile);
    void readF(FileBuffer *data);
    void saveF(QString name);
    void saveF(QDataStream &write);
    void newF();
    void vertexInit();
    void normalInit();
    void oglInit();
    void initBlob();
    void rotateTex(int idx);
    void mirrorXTex(int idx);
    void mirrorYTex(int idx);
    void scaleTex(int idx, float val);
    void scaleTexX(int idx, float val);
    void scaleTexY(int idx, float val);
    float getScaleTexY(int idx);
    float getScaleTexX(int idx);
    float getScaleTex(int idx);
    void convertTexToDefaultCoords(int idx);
    void paintTextureOnTile(Brush* brush, int y, int u, float x, float z);
    void reloadLines();
    
    virtual void load();
    
private:
    int terrWidth = 1;
    
};

#endif	/* TERRAIN_H */

