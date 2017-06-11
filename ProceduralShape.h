/*  This file is part of TSRE5.
 *
 *  TSRE5 - train sim game engine and MSTS/OR Editors. 
 *  Copyright (C) 2016 Piotr Gadecki <pgadecki@gmail.com>
 *
 *  Licensed under GNU General Public License 3.0 or later. 
 *
 *  See LICENSE.md or https://www.gnu.org/licenses/gpl.html
 */

#ifndef PROCEDURALSHAPE_H
#define	PROCEDURALSHAPE_H

#include <QMap>
#include <QString>
#include "OglObj.h"
#include "TSection.h"

class ObjFile;

class ProceduralShape {

public:
    static QMap<QString, ObjFile*> Files;
    static void GenShape(QVector<OglObj*> &shape, QVector<TSection> &sections);
private:
    static float Alpha;
    static void PushShapePart(float* &ptr, ObjFile* tFile, float* matrix);
};

#endif	/* PROCEDURALSHAPE_H */
