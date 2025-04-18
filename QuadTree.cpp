/*  This file is part of TSRE5.
 *
 *  TSRE5 - train sim game engine and MSTS/OR Editors. 
 *  Copyright (C) 2016 Piotr Gadecki <pgadecki@gmail.com>
 *
 *  Licensed under GNU General Public License 3.0 or later. 
 *
 *  See LICENSE.md or https://www.gnu.org/licenses/gpl.html
 */

#include "QuadTree.h"
#include "Game.h"
#include "FileBuffer.h"
#include "ParserX.h"
#include "ReadFile.h"
#include <QString>
#include <QDebug>
#include <QFile>
#include "TerrainInfo.h"

QuadTree::QuadTree(bool l) {
    low = l;
}

void QuadTree::load() {

    QString path;
    if(low)
        path = Game::root + "/routes/" + Game::route + "/td/lo_td_idx.dat";
    else
        path = Game::root + "/routes/" + Game::route + "/td/td_idx.dat";
    path.replace("//", "/");

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        if(Game::debugOutput) qDebug() << "quad tree file not exist    " << path;
        return;
    }
    FileBuffer* data = ReadFile::read(&file);
    //qDebug() << "Date:" << data->length;
    //data->off = 0;
    //for(int i = 0; i < 64; i++){
    //    data->off = i;
    //    qDebug() << (char)data->get()<<"-"<<data->get();
    //}
    data->toUtf16();
    ParserX::NextLine(data);
    load(data);
}

void QuadTree::load(FileBuffer *data, bool loadtd){
    QString sh;
    while (!((sh = ParserX::NextTokenInside(data).toLower()) == "")) {
        if (sh == "terrain_desc") {
            while (!((sh = ParserX::NextTokenInside(data).toLower()) == "")) {
                //qDebug() << sh;
                if (sh == "terrain_desc_size") {
                    terrainDescSize = ParserX::GetNumber(data);
                    ParserX::SkipToken(data);
                    continue;
                } else if (sh == "depth") {
                    depth = ParserX::GetNumber(data);
                    ParserX::SkipToken(data);
                    continue;
                } else if (sh == "terrain_desc_tiles") {
                    if(loadtd){
                        while (!((sh = ParserX::NextTokenInside(data).toLower()) == "")) {
                            if (sh == "tdfile") {
                                int x = ParserX::GetNumber(data);
                                int y = ParserX::GetNumber(data);
                                if(Game::debugOutput) qDebug() << sh << " " << x << " " << y;
                                loadTD(x, y);
                                ParserX::SkipToken(data);
                            }
                        }
                    }
                    ParserX::SkipToken(data);
                    continue;
                }
                if(Game::debugOutput) qDebug() << "#QuadTree terrain_desc - undefined token " << sh;
                ParserX::SkipToken(data);
            }
            ParserX::SkipToken(data);
            continue;
        }
        if(Game::debugOutput) qDebug() << "#QuadTree - undefined token " << sh;
        ParserX::SkipToken(data);
    }
}

void QuadTree::createNew(int tileX, int tileY) {
    int qx = floor((float) tileX / 512.0);
    int qy = floor((float) tileY / 512.0);
    if(Game::debugOutput) qDebug() << "td xy " << qx << " " << qy;
    int tx = qx * 512;
    int ty = qy * 512;
    TdFile* ttd = new TdFile();
    ttd->x = tx;
    ttd->y = ty;
    td[ttd->x * 100000 + ttd->y] = ttd;
    ttd->qt = new QuadTile(256, 1, tx, ty);
    int dLevel = 1;
    if(low)
        dLevel = 16;
    ttd->qt->addTile(tileX, tileY, dLevel);
    ttd->modified = true;
    save();
}

void QuadTree::listNames() {
    if(Game::debugOutput) qDebug() << "#QuadTree Populated Terrain Tiles:";
    QHashIterator<int, TdFile*> i2(td);
    while (i2.hasNext()) {
        i2.next();
        i2.value()->qt->listNames();
    }
}

bool QuadTree::isLow(){
    return low;
}

QString QuadTree::getMyName(int tileX, int tileY) {
    int qx = floor((float) tileX / 512.0);
    int qy = floor((float) tileY / 512.0);
    int tx = qx * 512;
    int ty = qy * 512;

    if (td[tx * 100000 + ty] == NULL) {
        return "";
    }
    return td[tx * 100000 + ty]->qt->getMyName(tileX, tileY);
}

unsigned int QuadTree::getMyNameId(int tileX, int tileY) {
    int qx = floor((float) tileX / 512.0);
    int qy = floor((float) tileY / 512.0);
    int tx = qx * 512;
    int ty = qy * 512;

    if (td[tx * 100000 + ty] == NULL) {
        return 0;
    }
    return td[tx * 100000 + ty]->qt->getMyNameId(tileX, tileY);
}

void QuadTree::fillTerrainInfo(int tileX, int tileY, TerrainInfo* info) {
    int qx = floor((float) tileX / 512.0);
    int qy = floor((float) tileY / 512.0);
    int tx = qx * 512;
    int ty = qy * 512;

    if (td[tx * 100000 + ty] == NULL) {
        return;
    }
    td[tx * 100000 + ty]->qt->fillTerrainInfo(tileX, tileY, info);
    info->low = low;
}

void QuadTree::addTile(int tileX, int tileY) {
    int qx = floor((float) tileX / 512.0);
    int qy = floor((float) tileY / 512.0);
    if(Game::debugOutput) qDebug() << "td xy " << qx << " " << qy;
    int tx = qx * 512;
    int ty = qy * 512;

    if (td[tx * 100000 + ty] == NULL) {
        td[tx * 100000 + ty] = new TdFile();
        td[tx * 100000 + ty]->x = tx;
        td[tx * 100000 + ty]->y = ty;
        td[tx * 100000 + ty]->qt = new QuadTile(256, 1, tx, ty);
    }
    int dLevel = 1;
    if(low)
        dLevel = 16;
    if(Game::debugOutput) qDebug() << "dLevel" << dLevel;
    td[tx * 100000 + ty]->qt->addTile(tileX, tileY, dLevel);
    td[tx * 100000 + ty]->modified = true;
    save();
}

int QuadTree::QuadTile::listNames() {
    unsigned int tn;
    unsigned int count = 0;
    unsigned int outCount = 0;
    for (int i = 0; i <= 1; i++)
        for (int j = 0; j <= 1; j++) {
            if (tile[i][j] != NULL) {
                count = tile[i][j]->listNames();
                outCount += count;
            }
            if (populated[i][j] == true) {
                tn = nameId << 2*prefix | !j << (1 + 2*prefix) | !(j^i) << (0 + 2*prefix);
                //qDebug() ;
                outCount++;
                if(count == 0)
                    if(Game::debugOutput) qDebug() << level << prefix << i << j << (i * 2 + (i^j)) << x << y << "[visible] QuadTile name: " << PrefixString[prefix]+QString::number(tn, 16);
                else
                    if(Game::debugOutput) qDebug() << level << prefix << i << j << (i * 2 + (i^j)) << x << y << "[hidden]  QuadTile name: " << PrefixString[prefix]+QString::number(tn, 16);
            }
            
        }
    return outCount;
}

QString QuadTree::QuadTile::getMyName(int tileX, int tileY){
    int px = 0;
    int py = 0;
    if (tileX >= x + level) px = 1;
    if (tileY >= y + level) py = 1;
    
    int pow = 0;
    for(pow = 0; pow < 32; pow++){
        if((level >> pow)&1 == 1)
            break;
    }
    pow = (pow+1) / 2;
    // qDebug() << "level and pow" << level << pow / 2;

    // First check if smaller tile is populated.
    QString tval = "";
    if (tile[px][py] != NULL)
        tval = tile[px][py]->getMyName(tileX, tileY);
    if(tval != "")
        return tval;
    
    if(populated[px][py] == true){
        QString val = QString::number(nameId << 2*prefix | !py << (1 + 2*prefix) | !(py^px) << (0 + 2*prefix), 16);
        int len = 8 - pow - val.length();
        for (int i = 0; i < len; i++)
            val = "0" + val;
        //qDebug() << len << val;
        return PrefixString[prefix]+val;
    } 
    //else if (tile[px][py] != NULL) {
    //    return tile[px][py]->getMyName(tileX, tileY);
    //}
    return "";
}

unsigned int QuadTree::QuadTile::getMyNameId(int tileX, int tileY){
    int px = 0;
    int py = 0;
    if (tileX >= x + level) px = 1;
    if (tileY >= y + level) py = 1;
    
    int pow = 0;
    for(pow = 0; pow < 32; pow++){
        if((level >> pow)&1 == 1)
            break;
    }
    pow = (pow+1) / 2;

    // First check if smaller tile is populated.
    int tval = 0;
    if (tile[px][py] != NULL)
        tval = tile[px][py]->getMyNameId(tileX, tileY);
    if(tval != 0)
        return tval;
    
    if(populated[px][py] == true){
        return (nameId << 2*prefix | !py << (1 + 2*prefix) | !(py^px) << (0 + 2*prefix));
    } //else if (tile[px][py] != NULL) {
    //    return tile[px][py]->getMyNameId(tileX, tileY);
    //}
    return 0;
}

bool QuadTree::QuadTile::fillTerrainInfo(int tileX, int tileY, TerrainInfo* info){
    int px = 0;
    int py = 0;
    if (tileX >= x + level) px = 1;
    if (tileY >= y + level) py = 1;

    int pow = 0;
    for(pow = 0; pow < 32; pow++){
        if((level >> pow)&1 == 1)
            break;
    }
    pow = (pow+1) / 2;
    
    // First check if smaller tile is populated.
    bool tval = false;
    if (tile[px][py] != NULL)
        tval = tile[px][py]->fillTerrainInfo(tileX, tileY, info);
    if(tval == true)
        return true;
    
    if(populated[px][py] == true){
        QString val = QString::number(nameId << 2*prefix | !py << (1 + 2*prefix) | !(py^px) << (0 + 2*prefix), 16);
        int len = 8 - pow - val.length();
        for (int i = 0; i < len; i++)
            val = "0" + val;
        info->name = PrefixString[prefix]+val;        
        info->cx = x + level*px;//  level/2;
        info->cy = y + level*py;// + level/2;
        info->level = level;
        //qDebug() << "info" << tileX << tileY << info->cx << info->cy << info->level << pow;
        return true;
    }// else if (tile[px][py] != NULL) {
    //        tile[px][py]->fillTerrainInfo(tileX, tileY, info);
    //}
    return false;
}

void QuadTree::QuadTile::addTile(int tileX, int tileY, int dLevel) {
    int px = 0;
    int py = 0;
    if (tileX >= x + level) px = 1;
    if (tileY >= y + level) py = 1;
    if (level == dLevel) {
        populated[px][py] = true;
    } else {
        if (tile[px][py] == NULL) {
            tile[px][py] = new QuadTile(level / 2, 1-prefix, x + px*level, y + py*level );
        }
        tile[px][py]->addTile(tileX, tileY, dLevel);
    }
}

/*void QuadTree::loadTD(int x, int y){
    QString sh;
    QString path;
    path = Game::root + "/routes/" + Game::route + "/td/"+ getNameXY(x) + "" + getNameXY(y) +".td";
    path.replace("//", "/");

    QFile *file = new QFile(path);
    if (!file->open(QIODevice::ReadOnly)) {
        qDebug() << "w file not exist    " << path;
        return;
    }
    FileBuffer* data = ReadFile::read(file);
    TdFile* ttd = new TdFile();
    ttd->x = x*512;
    ttd->y = y*512;
    td[ttd->x*10000+ttd->y] = ttd;
    
    for(int i = 0; i < 512; i++)
        memset(ttd->data[i], 0, 512);
    
    data->off = 38;
    
    QString a = "";
    unsigned char aa; 
    std::vector<TreePos*> tree;
    int level = 256;
    TreePos* tp;
    int tx = x*512;
    int ty = y*512;
    while(data->off < data->length){
        //qDebug() << (int)data->get();
        aa = data->get() >> 4;
        a = "";
        int sum = 0;
        tp = new TreePos(level);
        tp->x = tx;
        tp->y = ty;
        if(aa & 0b1000) {
            //tree.push_back(std::make_pair(level, 4));
            tp->sum++;
            tp->tile.push_back(std::make_pair(0, 1));
            a += "1";
        }
        else a += "-";
        if(aa & 0b0100){
            //tree.push_back(std::make_pair(level, 3));
            tp->sum++;
            tp->tile.push_back(std::make_pair(1, 1));
            a += "1";
        }
        else a += "-";
        if(aa & 0b0010){
            //tree.push_back(std::make_pair(level, 2));
            tp->sum++;
            tp->tile.push_back(std::make_pair(1, 0));
            a += "1";
        }
        else a += "-";
        if(aa & 0b0001){
            //tree.push_back(std::make_pair(level, 1));
            tp->sum++;
            tp->tile.push_back(std::make_pair(0, 0));
            a += "1";
        }
        else a += "-";
        
        if(tp->sum > 0)
            tree.push_back(tp);
        
        
        if(a == "----"){
            qDebug() << level <<" "<< a << tx << " " << ty;
            while(tree.size() > 0){
                tree.back()->sum--;
                if(tree.back()->sum == 0){
                    tree.pop_back();
                }else{
                    
                    break;
                }
            }
        }
        if(tree.size() == 0)
            break;
        level = tree.back()->level;
        tx = tree.back()->x + tree.back()->tile[tree.back()->tile.size() - tree.back()->sum].first*level;
        ty = tree.back()->y + tree.back()->tile[tree.back()->tile.size() - tree.back()->sum].second*level;
        level*=0.5;
    }
}*/

void QuadTree::save() {
    QString sh;
    QString path;
    if(!low)
        path = Game::root + "/routes/" + Game::route + "/td/td_idx.dat";
    else
        path = Game::root + "/routes/" + Game::route + "/td/lo_td_idx.dat";
    path.replace("//", "/");
    QFile file(path);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out.setCodec("UTF-16");
    out.setGenerateByteOrderMark(true);
    out << "SIMISA@@@@@@@@@@JINX0D0t______\n";
    out << "\n";
    save(out);
    
    file.close();

    QHashIterator<int, TdFile*> i2(td);
    while (i2.hasNext()) {
        i2.next();
        if(i2.value() == NULL)
            continue;
        if (i2.value()->modified)
            saveTD((float) i2.value()->x / 512.0, (float) i2.value()->y / 512.0);
    }
}

void QuadTree::save(QTextStream& out){
    out << "terrain_desc (\n";
    out << "	terrain_desc_size ( " << this->terrainDescSize << " )\n";
    out << "	Depth ( " << this->depth << " )\n";
    out << "	terrain_desc_tiles ( \n";
    QHashIterator<int, TdFile*> i(td);
    while (i.hasNext()) {
        i.next();
        if(i.value() == NULL)
            continue;
        out << "		TdFile ( " << (i.value()->x / 512) << " " << (i.value()->y / 512) << " )\n";
    }
    out << "	) \n";
    out << ") \n";

}

void QuadTree::loadTD(int x, int y) {
    QString sh;
    QString path;
    if(!low)
        path = Game::root + "/routes/" + Game::route + "/td/" + getNameXY(x) + "" + getNameXY(y) + ".td";
    else
        path = Game::root + "/routes/" + Game::route + "/td/" + getNameXY(x) + "" + getNameXY(y) + ".tdl";
    path.replace("//", "/");

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        if(Game::debugOutput) qDebug() << "w file not exist    " << path;
        return;
    }
    FileBuffer* data = ReadFile::read(&file);
    loadTD(x*512, y*512, data);
    delete data;
}

void QuadTree::loadTD(int x, int y, FileBuffer* data){
    TdFile* ttd = new TdFile();
    ttd->x = x;
    ttd->y = y;
    td[ttd->x * 100000 + ttd->y] = ttd;
    data->off += 38 + 16;
    ttd->qt = new QuadTile(256, 1, ttd->x, ttd->y);
    ttd->qt->load(data);
    //saveTD(x, y);
}

void QuadTree::saveTD(int x, int y) {
    QString sh;
    QString path;
    if(low)
        path = Game::root + "/routes/" + Game::route + "/td/" + getNameXY(x) + "" + getNameXY(y) + ".tdl";
    else
        path = Game::root + "/routes/" + Game::route + "/td/" + getNameXY(x) + "" + getNameXY(y) + ".td";
    path.replace("//", "/");
    QFile *file = new QFile(path);
    if(Game::debugOutput) qDebug() << "zapis .td " << path;
    if (!file->open(QIODevice::WriteOnly)) {
        if(Game::debugOutput) qDebug() << "td write fail";
        return;
    }
    QDataStream out(file);
    out.setByteOrder(QDataStream::LittleEndian);
    out.setFloatingPointPrecision(QDataStream::SinglePrecision);
    x = x * 512;
    y = y * 512;
    int id = x * 100000 + y;
    saveTD(x, y, &out);
    out.unsetDevice();
    file->close();
    td[id]->modified = false;
}

void QuadTree::saveTD(int x, int y, QDataStream* out){
    //write
    const char header[] = {
        0x53, 0x49, 0x4D, 0x49, 0x53, 0x41, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
        0x4A, 0x49, 0x4E, 0x58, 0x30, 0x64, 0x31, 0x62, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x0D, 0x0A
    };
    out->writeRawData(header, 32);
    QVector<unsigned char> treeData;
    int id = x * 100000 + y;
    td[id]->qt->save(treeData);

    *out << (qint32) 0x84;
    *out << (qint32) treeData.size() + 14;
    *out << (qint8) 0;
    *out << (qint32) 0x87;
    *out << (qint32) treeData.size() + 5;
    *out << (qint8) 0;
    *out << (qint32) treeData.size();
    out->writeRawData((char*) &treeData[0], treeData.size());
}

QChar QuadTree::QuadTile::PrefixString[2] = {'_', '-'};

QuadTree::QuadTile::QuadTile(int l, int p, int xx, int yy) {
    level = l;
    prefix = p;
    sum = 0;
    tile[0][0] = NULL;
    tile[1][0] = NULL;
    tile[0][1] = NULL;
    tile[1][1] = NULL;
    populated[0][0] = false;
    populated[1][0] = false;
    populated[0][1] = false;
    populated[1][1] = false;
    x = xx;
    y = yy;
    int offset = 16384;
    xx += offset;
    yy += offset;

    for (int tx = offset, ty = tx, i = tx, sign_xs, sign_ys; i > level; i /= 2, tx += i, ty += i, nameId <<= 2) {
        sign_xs = ((unsigned) (xx - tx) >> 31);
        sign_ys = ((unsigned) (yy - ty) >> 31);
        nameId |= (sign_ys * 2 + !(sign_xs^sign_ys));
        tx -= sign_xs*i;
        ty -= sign_ys*i;
    }
}

void QuadTree::QuadTile::save(QVector<unsigned char> &data) {
    unsigned char isDivided = 0;
    unsigned char isPopulated = 0;

    if (tile[0][1] != 0)
        isDivided = isDivided | 0b1000;
    if (tile[1][1] != 0)
        isDivided = isDivided | 0b0100;
    if (tile[1][0] != 0)
        isDivided = isDivided | 0b0010;
    if (tile[0][0] != 0)
        isDivided = isDivided | 0b0001;
    if (populated[0][1])
        isPopulated = isPopulated | 0b1000;
    if (populated[1][1] != 0)
        isPopulated = isPopulated | 0b0100;
    if (populated[1][0] != 0)
        isPopulated = isPopulated | 0b0010;
    if (populated[0][0] != 0)
        isPopulated = isPopulated | 0b0001;
    isDivided = (isDivided << 4) | isPopulated;
    data.push_back(isDivided);

    if (tile[0][1] != 0)
        tile[0][1]->save(data);
    if (tile[1][1] != 0)
        tile[1][1]->save(data);
    if (tile[1][0] != 0)
        tile[1][0]->save(data);
    if (tile[0][0] != 0)
        tile[0][0]->save(data);
}

void QuadTree::QuadTile::load(FileBuffer* data) {
    unsigned char aaa = data->get();
    unsigned char isDivided = aaa >> 4;
    unsigned char isPopulated = aaa & 0b1111;
    QString a = "";
    int sum = 0;
    int lev = level / 2;

    if (isDivided & 0b1000) {
        sum++;
        tile[0][1] = new QuadTile(lev, 1-prefix, x, y + level);
        a += "1";
    } else a += "-";
    if (isDivided & 0b0100) {
        sum++;
        tile[1][1] = new QuadTile(lev, 1-prefix, x + level, y + level);
        a += "1";
    } else a += "-";
    if (isDivided & 0b0010) {
        sum++;
        tile[1][0] = new QuadTile(lev, 1-prefix, x + level, y);
        a += "1";
    } else a += "-";
    if (isDivided & 0b0001) {
        sum++;
        tile[0][0] = new QuadTile(lev, 1-prefix, x, y);
        a += "1";
    } else a += "-";

    if (isPopulated & 0b1000) {
        populated[0][1] = true;
        //qDebug() << "p" <<" "<< a << x << " " << y + level;
    }
    if (isPopulated & 0b0100) {
        populated[1][1] = true;
        //qDebug() << "p" <<" "<< a << x + level << " " << y + level;
    }
    if (isPopulated & 0b0010) {
        populated[1][0] = true;
        //qDebug() << "p" <<" "<< a << x + level << " " << y;
    }
    if (isPopulated & 0b0001) {
        populated[0][0] = true;
        //qDebug() << "p" <<" "<< a << x << " " << y;
    }

    //qDebug() << level <<" "<< a << x << " " << y;
    if (tile[0][1] != 0)
        tile[0][1]->load(data);
    if (tile[1][1] != 0)
        tile[1][1]->load(data);
    if (tile[1][0] != 0)
        tile[1][0]->load(data);
    if (tile[0][0] != 0)
        tile[0][0]->load(data);

    if (a == "----") {
        //qDebug() << lev <<" "<< a << x << " " << y;
    }
}

QString QuadTree::getNameXY(int e) {
    QString n = "+";
    if (e < 0) {
        n = "-";
        e = -e;
    }
    QString s = "000000" + QString::number(e);
    return n + s.right(5);
}

QuadTree::~QuadTree() {
}

