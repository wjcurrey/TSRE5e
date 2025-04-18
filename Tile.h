/*  This file is part of TSRE5.
 *
 *  TSRE5 - train sim game engine and MSTS/OR Editors. 
 *  Copyright (C) 2016 Piotr Gadecki <pgadecki@gmail.com>
 *
 *  Licensed under GNU General Public License 3.0 or later. 
 *
 *  See LICENSE.md or https://www.gnu.org/licenses/gpl.html
 */

#ifndef TILE_H
#define	TILE_H

#include <QString>
#include <unordered_map>
#include "WorldObj.h"
#include "Ref.h"

class GroupObj;

class Tile {
public:
    struct ViewDbSphere {
        int vDbId;
	float position[3];
	float radius;
        QVector<ViewDbSphere> viewDbSphere;
        void set(int sh, FileBuffer* data);
        void set(QString sh, FileBuffer* data);
        void save(QTextStream* out, const QString offset);
    };
    int vDbIdCount;
    QVector<ViewDbSphere> viewDbSphere;
    int loaded;
    bool inUse;
    
    int x;
    int z;
    //obiekty = new Array();
    int jestObiektow = 0;
    //int jestObiektowWS = 0;
    int jestHiddenObj = 0;
    std::unordered_map<int, WorldObj*> obiekty;
    //std::unordered_map<int, WorldObj*> obiektyWS;
    Tile();
    Tile(int xx, int zz);
    Tile(int xx, int zz, FileBuffer *data);
    Tile(const Tile& orig);
    virtual ~Tile();
    static void saveEmpty(int x, int z);
    static QString getNameXY(int e);
    void load();
    void loadUtf16Data(FileBuffer *data);
    void loadInit();
    void replaceWorldObj(WorldObj *nowy);
    void selectObjectsByXYRange(QVector<GameObj*> &objects, int minx, int maxx, int minz, int maxz);
    void updateTrackSectionInfo(QHash<unsigned int, unsigned int> shapes, QHash<unsigned int, unsigned int> sect);
    void loadWS();
    bool isModified();
    void setModified(bool value);
    WorldObj* getObj(int id);
    WorldObj* findNearestObj(float *pos);
    void deleteObject(WorldObj* obj);
    WorldObj* placeObject(WorldObj* obj);
    WorldObj* placeObject(float* p, Ref::RefItem* itemData);
    WorldObj* placeObject(float* p, float* q, Ref::RefItem* itemData, float* tpos = NULL);
    void fillWorldObjectsByTrackItemId(QVector<WorldObj*> &objects, int tdbId, int id);
    void fillWorldObjectsByTrackItemIds(QHash<int, QVector<WorldObj*>> &objects, int tdbId);
    void transalteObj(float px, float py, float pz, int uid);
    void initNew();
    void updateTerrainObjects();
    float getNearestSnapablePosition(float *pos, float *quat, int uid = -1);
    void updateSim(float deltaTime);
    void findSimilar(WorldObj* obj, GroupObj* group);
    void checkForErrors();
    void render();
    void pushRenderItems(float *  playerT, float* playerW, float* target, float fov, int renderMode);
    void render(float *  playerT, float* playerW, float* target, float fov, int renderMode);
    //void renderWS(float *  playerT, float* playerW, float* target, float fov, int renderMode);
    void save();
    void saveToStream(QTextStream &out);
    WorldObj* CheckObj;
    
private:
    int maxUiD = 0;
    int maxUiDWS = 100000;    
    bool modified;
    QString* viewDbSphereRaw = NULL;
    void wczytajObiekty();
    void saveWS();
    Route* route = NULL;

};

#endif	/* TILE_H */

