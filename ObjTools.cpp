/*  This file is part of TSRE5.
 *
 *  TSRE5 - train sim game engine and MSTS/OR Editors. 
 *  Copyright (C) 2016 Piotr Gadecki <pgadecki@gmail.com>
 *
 *  Licensed under GNU General Public License 3.0 or later. 
 *
 *  See LICENSE.md or https://www.gnu.org/licenses/gpl.html
 */

#include "TSectionDAT.h"
#include "ObjTools.h"
#include "Route.h"
#include "Game.h"
#include "SigCfg.h"
#include "SignalShape.h"
#include "ForestObj.h"
#include "SpeedPost.h"
#include "SpeedPostDAT.h"
#include "SoundList.h"
#include "TRitem.h"
#include <QMapIterator>

ObjTools::ObjTools(QString name)
    : QWidget(){
    //QRadioButton *radio1 = new QRadioButton(tr("&Radio button 1"));
    //QRadioButton *radio2 = new QRadioButton(tr("R&adio button 2"));
    //QRadioButton *radio3 = new QRadioButton(tr("Ra&dio button 3"));
    setFixedWidth(250);
    buttonTools["selectTool"] = new QPushButton("Select", this);
    buttonTools["placeTool"] = new QPushButton("Place New", this);
    buttonTools["autoPlaceSimpleTool"] = new QPushButton("Auto Placement", this);
    QMapIterator<QString, QPushButton*> i(buttonTools);
    while (i.hasNext()) {
        i.next();
        i.value()->setCheckable(true);
    }
    
    QPushButton *advancedPlacenentButton = new QPushButton("...", this);
    advancedPlacenentButton->setCheckable(true);
    QObject::connect(advancedPlacenentButton, SIGNAL(toggled(bool)), this, SLOT(advancedPlacementButtonEnabled(bool)));
    QPushButton *resetRotationButton = new QPushButton("Reset Place Rot", this);
    QPushButton *autoPlacementDeleteLast = new QPushButton("Delete last placed objects", this);
    QObject::connect(autoPlacementDeleteLast, SIGNAL(released()), this, SLOT(autoPlacementDeleteLastEnabled()));
    
    //searchBox = new QLineEdit(this);
    //radio1->setChecked(true);
    
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->setSpacing(2);
    vbox->setContentsMargins(0,1,1,1);
    QLabel *label1 = new QLabel("Objects:");
    label1->setStyleSheet(QString("QLabel { color : ")+Game::StyleMainLabel+"; }");
    label1->setContentsMargins(3,0,0,0);
    vbox->addWidget(label1);
    QFormLayout *vlist = new QFormLayout;
    vlist->setSpacing(2);
    vlist->setContentsMargins(3,0,3,0);
    vlist->addRow("Ref file:",&refClass);
    vlist->addRow("Tracks:",&refTrack);
    vlist->addRow("Roads:",&refRoad);
    vlist->addRow("Other:",&refOther);
    vlist->addRow("Search:",&searchBox);
    vbox->addItem(vlist);
    vbox->addWidget(&refList);
    QGridLayout *vlist3 = new QGridLayout;
    vlist3->setSpacing(2);
    vlist3->setContentsMargins(3,0,1,0);    
    int row = 0;
    vlist3->addWidget(buttonTools["selectTool"],row,0);
    vlist3->addWidget(buttonTools["placeTool"],row++,1,1,3);
    vlist3->addWidget(&stickToTDB,row,0);
    vlist3->addWidget(resetRotationButton,row++,1,1,3);
    vlist3->addWidget(buttonTools["autoPlaceSimpleTool"],row,0);
    vlist3->addWidget(&autoPlacementLength,row,1);
    autoPlacementLength.setText("50");
//    QDoubleValidator* doubleValidator = new QDoubleValidator(-999, 999, 6, this); 
//    QDoubleValidator* doubleValidator1 = new QDoubleValidator(1, 999, 6, this); 
    QDoubleValidator* doubleValidator = new QDoubleValidator(-Game::maxAutoPlacement, Game::maxAutoPlacement, 6, this); 
    QDoubleValidator* doubleValidator1 = new QDoubleValidator(1, Game::maxAutoPlacement, 6, this); 
    doubleValidator->setNotation(QDoubleValidator::StandardNotation);
    doubleValidator1->setNotation(QDoubleValidator::StandardNotation);
    autoPlacementLength.setValidator(doubleValidator1);
    QObject::connect(&autoPlacementLength, SIGNAL(textEdited(QString)), this, SLOT(autoPlacementLengthEnabled(QString)));
    vlist3->addWidget(new QLabel("m"),row,2);
    vlist3->addWidget(advancedPlacenentButton,row++,3);
    vbox->addItem(vlist3);
    
    vlist3 = new QGridLayout;
    vlist3->setSpacing(2);
    vlist3->setContentsMargins(3,0,1,0);    
    row = 0;
    vlist3->addWidget(new QLabel("Rotation Type:"),row,0,1,1);
    vlist3->addWidget(&autoPlacementRotType,row++,1,1,6);
    QObject::connect(&autoPlacementRotType, SIGNAL(activated(QString)),
                      this, SLOT(autoPlacementRotTypeSelected(QString)));
    autoPlacementRotType.setStyleSheet("combobox-popup: 0;");
    autoPlacementRotType.addItem("Two Point Rotation");
    autoPlacementRotType.addItem("One Point Rotation");
    vlist3->addWidget(new QLabel("Target:"),row,0,1,1);
    vlist3->addWidget(&autoPlacementTarget,row++,1,1,6);
    QObject::connect(&autoPlacementTarget, SIGNAL(activated(QString)),
                      this, SLOT(autoPlacementTargetSelected(QString)));
    autoPlacementTarget.setStyleSheet("combobox-popup: 0;");
    autoPlacementTarget.addItem("Tracks");
    autoPlacementTarget.addItem("Roads");
    autoPlacementTarget.addItem("Tracks & Roads");
    autoPlacementTarget.addItem("Snapable");
    vlist3->addWidget(new QLabel("Translate Offset"),row,0);
    vlist3->addWidget(new QLabel("X:"),row,1);
    vlist3->addWidget(&autoPlacementPosX,row,2);
    QObject::connect(&autoPlacementPosX, SIGNAL(textEdited(QString)), this, SLOT(autoPlacementOffsetEnabled(QString)));
    autoPlacementPosX.setText("0");
    vlist3->addWidget(new QLabel("Y:"),row,3);
    vlist3->addWidget(&autoPlacementPosY,row,4);
    QObject::connect(&autoPlacementPosY, SIGNAL(textEdited(QString)), this, SLOT(autoPlacementOffsetEnabled(QString)));
    autoPlacementPosY.setText("0");
    vlist3->addWidget(new QLabel("Z:"),row,5);
    vlist3->addWidget(&autoPlacementPosZ,row++,6);    
    QObject::connect(&autoPlacementPosZ, SIGNAL(textEdited(QString)), this, SLOT(autoPlacementOffsetEnabled(QString)));
    autoPlacementPosZ.setText("0");
    vlist3->addWidget(new QLabel("Rotate Offset"),row,0);
    vlist3->addWidget(new QLabel("X:"),row,1);
    vlist3->addWidget(&autoPlacementRotX,row,2);
    QObject::connect(&autoPlacementRotX, SIGNAL(textEdited(QString)), this, SLOT(autoPlacementOffsetEnabled(QString)));
    autoPlacementRotX.setText("0");
    vlist3->addWidget(new QLabel("Y:"),row,3);
    vlist3->addWidget(&autoPlacementRotY,row,4);
    QObject::connect(&autoPlacementRotY, SIGNAL(textEdited(QString)), this, SLOT(autoPlacementOffsetEnabled(QString)));
    autoPlacementRotY.setText("0");
    vlist3->addWidget(new QLabel("Z:"),row,5);
    vlist3->addWidget(&autoPlacementRotZ,row++,6);    
    QObject::connect(&autoPlacementRotZ, SIGNAL(textEdited(QString)), this, SLOT(autoPlacementOffsetEnabled(QString)));
    autoPlacementRotZ.setText("0");
    vlist3->addWidget(new QLabel("Snapable max radius:"),row,0,1,1);
    vlist3->addWidget(&autoSnapableRadius,row,1,1,3);
    QObject::connect(&autoSnapableRadius, SIGNAL(textEdited(QString)), this, SLOT(autoSnapableRadiusEnabled(QString)));
    autoSnapableRadius.setText(QString::number(Game::snapableRadius));
    autoSnapableRadius.setValidator(doubleValidator1);
    QCheckBox *chSnapableOnlyRotation = new QCheckBox("Only Rot ");
    vlist3->addWidget(chSnapableOnlyRotation,row++,4,1,3);
    chSnapableOnlyRotation->setChecked(Game::snapableOnlyRot);
    QObject::connect(chSnapableOnlyRotation, SIGNAL(stateChanged(int)), this, SLOT(chSnapableOnlyRotation(int)));
    vlist3->addWidget(autoPlacementDeleteLast,row++,0,1,7);
    autoPlacementPosX.setValidator(doubleValidator);
    autoPlacementPosY.setValidator(doubleValidator);
    autoPlacementPosZ.setValidator(doubleValidator);
    autoPlacementRotX.setValidator(doubleValidator);
    autoPlacementRotY.setValidator(doubleValidator);
    autoPlacementRotZ.setValidator(doubleValidator);
    advancedPlacementWidget.setLayout(vlist3);
    vbox->addWidget(&advancedPlacementWidget);
    advancedPlacementWidget.hide();
    
    stickToTDB.setText("Stick To Target");
    stickToTDB.setChecked(false);
    //vbox->addWidget(&stickToTDB);
    QLabel *label2 = new QLabel("Recent items:");
    label2->setStyleSheet(QString("QLabel { color : ")+Game::StyleMainLabel+"; }");
    label2->setContentsMargins(3,0,0,0);
    //refClasssetMargin(0);
    //refTrack->sets >setMargin(0);
    //refRoad->setMargin(0);
    //label1->setMargin(0);
    vbox->addWidget(label2);
    vbox->addWidget(&lastItems);

    lastItems.setMinimumHeight(Game::numRecentItems*16);
    lastItems.setMaximumHeight(Game::numRecentItems*16);
    //QSizePolicy* sizePolicy = new QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    //astItems.setSizePolicy(*sizePolicy);
    //) QSizePolicy::MinimumExpanding);
    //lastItems.setMaximumHeight(999);
    refList.setMinimumHeight(250);
    refList.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    refClass.setStyleSheet("combobox-popup: 0;");
    refTrack.setStyleSheet("combobox-popup: 0;");
    refRoad.setStyleSheet("combobox-popup: 0;");
    refOther.setStyleSheet("combobox-popup: 0;");
    
    //vbox->addStretch(1);
    this->setLayout(vbox);
    
    QObject::connect(&refClass, SIGNAL(activated(QString)),
                      this, SLOT(refClassSelected(QString)));
    
    QObject::connect(&refTrack, SIGNAL(activated(QString)),
                      this, SLOT(refTrackSelected(QString)));
    
    QObject::connect(&refRoad, SIGNAL(activated(QString)),
                      this, SLOT(refTrackSelected(QString)));
    
    QObject::connect(&refOther, SIGNAL(activated(QString)),
                      this, SLOT(refOtherSelected(QString)));
    
    QObject::connect(&searchBox, SIGNAL(textEdited(QString)),
                      this, SLOT(refSearchSelected(QString)));
    
    QObject::connect(&refList, SIGNAL(itemClicked(QListWidgetItem*)),
                      this, SLOT(refListSelected(QListWidgetItem*)));
    
    QObject::connect(&lastItems, SIGNAL(itemClicked(QListWidgetItem*)),
                      this, SLOT(lastItemsListSelected(QListWidgetItem*)));
    
    lastItems.setContextMenuPolicy(Qt::CustomContextMenu);
    QObject::connect(&lastItems, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showLastItemsContextMenu(QPoint)));
    
    QObject::connect(buttonTools["selectTool"], SIGNAL(toggled(bool)),
                      this, SLOT(selectToolEnabled(bool)));
    
    QObject::connect(buttonTools["placeTool"], SIGNAL(toggled(bool)),
                      this, SLOT(placeToolEnabled(bool)));
    
    QObject::connect(buttonTools["autoPlaceSimpleTool"], SIGNAL(toggled(bool)),
                      this, SLOT(autoPlacementButtonEnabled(bool)));
    
    QObject::connect(resetRotationButton, SIGNAL(released()),
                      this, SLOT(resetRotationButtonEnabled()));
    
    QObject::connect(&stickToTDB, SIGNAL(stateChanged(int)),
                      this, SLOT(stickToTDBEnabled(int)));
}

ObjTools::~ObjTools() {
}

void ObjTools::refreshObjLists(){
    if(route == NULL)
        return;
    
    refList.clear();
    lastItems.clear();
    refClass.clear();
    refTrack.clear();
    refRoad.clear();
    refOther.clear();
    lastItemsPtr.clear();
    currentItemList.clear();
    
    routeLoaded(route);
}

void ObjTools::routeLoaded(Route* a){
    this->route = a;           
    autoPlacementTarget.setCurrentIndex(2);
    route->placementAutoTargetType = 2;
    route->snapableOnlyRotation = Game::snapableOnlyRot;
       
    QStringList hash;
    QStringList hash2;
    QMapIterator<QString, QVector<Ref::RefItem>> i(route->ref->refItems);
    while (i.hasNext()) {
        i.next();
        hash.append(i.key());
    }
    hash.sort(Qt::CaseInsensitive);
    hash.removeDuplicates();
    refClass.addItems(hash);
    refClass.setMaxVisibleItems(35);
    refClass.view()->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    TrackShape * track;

    hash.clear();
    hash2.clear();

    QDir globalShapes(Game::root+"/global/shapes");
    QStringList globalShapesList;
    if(Game::ignoreMissingGlobalShapes)
        globalShapesList = globalShapes.entryList();
    if(route->tsection->shape.size() > 0)
    for (auto it = route->tsection->shape.begin(); it != route->tsection->shape.end(); ++it ){
        track = it->second;
        //hash = track->filename.left(3).toStdString();
        if(track == NULL) continue;
        if(track->dyntrack) continue;
        if(Game::ignoreMissingGlobalShapes)
            if(!globalShapesList.contains(track->filename, Qt::CaseInsensitive)) continue;
        if(track->roadshape){
            hash2.append(track->filename.left(3).toLower());
        } else {
            //i++;
            //if(track->filename.left(3).toLower() == "a1t")
            //    a1ti = i;
            hash.append(track->filename.left(3).toLower());
        }
        Ref::RefItem item;
        item.filename.push_back(track->filename);
        item.description = track->filename;
        item.clas = "";
        item.type = "trackobj";
        item.value = track->id;
        route->ref->refItems[QString("#TDB#")+track->filename.left(3).toLower()].push_back(item);
        //qDebug() << QString::fromStdString(it->first) << " " << it->second.size();
        //if(types[hash] != 1){
        //    refTrack.addItem(QString::fromStdString(hash));//, QVariant(QString::fromStdString(hash)));
            //types[hash] = 1;
        //}
      //std::cout << " " << it->first << ":" << it->second;
    }
    hash.sort(Qt::CaseInsensitive);
    hash.removeDuplicates();    
    refTrack.addItems(hash);
    refTrack.setMaxVisibleItems(35);
    refTrack.view()->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    hash2.sort(Qt::CaseInsensitive);
    hash2.removeDuplicates();
    refRoad.addItems(hash2);
    refRoad.setMaxVisibleItems(35);
    refRoad.view()->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    //refTrack.s .sortItems(Qt::AscendingOrder);
        
    refTrack.setCurrentText("a1t");
    refTrackSelected("a1t");

    if(Game::trackDB->loaded)  ///  EFO wrapping this in an IF because the TDB not existing causes a dump without warning
    {
        
        qDebug() << "ObjTools build Signals";
    
        SignalShape * signal;    

        QHashIterator<QString, SignalShape*> i2(Game::trackDB->sigCfg->signalShape);        
        // if(Game::trackDB->sigCfg->signalShape.size() > 0)   /// EFO un-commenting what was commented out
        while (i2.hasNext()) {
            i2.next();
            signal = i2.value();
            if(signal == NULL) continue;
            Ref::RefItem item;
            item.filename.push_back(signal->desc);
            item.description = signal->desc;
            item.clas = "signals";
            item.type = "signal";
            item.value = signal->listId;
            route->ref->refItems[QString("#TSRE#")+"signals"].push_back(item);
        }
        
        for (int i = 0; i < Game::trackDB->speedPostDAT->speedPost.size(); i++){
            if(Game::trackDB->speedPostDAT->speedPost[i]->speedSignShapeCount <= 0)
                continue;
            Ref::RefItem item;
            item.filename.push_back(Game::trackDB->speedPostDAT->speedPost[i]->name);
            item.description = Game::trackDB->speedPostDAT->speedPost[i]->name;
            item.clas = "speedsign";
            item.type = "speedpost";
            item.value = i*1000+TRitem::SIGN;
            route->ref->refItems[QString("#TSRE#")+"speedsign"].push_back(item);
        }
        for (int i = 0; i < Game::trackDB->speedPostDAT->speedPost.size(); i++){
            if(Game::trackDB->speedPostDAT->speedPost[i]->speedResumeSignShapeCount <= 0)
                continue;
            Ref::RefItem item;
            item.filename.push_back(Game::trackDB->speedPostDAT->speedPost[i]->name);
            item.description = Game::trackDB->speedPostDAT->speedPost[i]->name;
            item.clas = "speedresume";
            item.type = "speedpost";
            item.value = i*1000+TRitem::RESUME;
            route->ref->refItems[QString("#TSRE#")+"speedresume"].push_back(item);
        }
        for (int i = 0; i < Game::trackDB->speedPostDAT->speedPost.size(); i++){
            if(Game::trackDB->speedPostDAT->speedPost[i]->speedWarningSignShapeCount <= 0)
                continue;
            Ref::RefItem item;
            item.filename.push_back(Game::trackDB->speedPostDAT->speedPost[i]->name);
            item.description = Game::trackDB->speedPostDAT->speedPost[i]->name;
            item.clas = "speedwarning";
            item.type = "speedpost";
            item.value = i*1000+TRitem::WARNING;
            route->ref->refItems[QString("#TSRE#")+"speedwarning"].push_back(item);
        }
        for (int i = 0; i < Game::trackDB->speedPostDAT->speedPost.size(); i++){
            if(Game::trackDB->speedPostDAT->speedPost[i]->milepostShapeCount <= 0)
                continue;
            Ref::RefItem item;
            item.filename.push_back(Game::trackDB->speedPostDAT->speedPost[i]->name);
            item.description = Game::trackDB->speedPostDAT->speedPost[i]->name;
            item.clas = "milepost";
            item.type = "speedpost";
            item.value = i*1000+TRitem::MILEPOST;
            route->ref->refItems[QString("#TSRE#")+"milepost"].push_back(item);
        }    
    } else {
      qWarning() << "No Track Database Found, will create at Route Save, and some loading functions have been skipped";
    }
    
    if(!Game::roadDB->loaded) qWarning() << "No Road Database Found, will create at Route Save";

    for (int i = 0; i < ForestObj::forestList.size(); i++){
        Ref::RefItem item;
        item.filename.push_back(ForestObj::forestList[i].name);
        item.description = ForestObj::forestList[i].name;
        item.clas = "forests";
        item.type = "forest";
        item.value = i;
        route->ref->refItems[QString("#TSRE#")+"forests"].push_back(item);
    }
    
    foreach (SoundListItem* it, route->soundList->sources){
   //for (auto it = route->soundList->sources.constBegin(); it != route->soundList->sources.constEnd(); ++it ){
        Ref::RefItem item;
        item.filename.push_back(it->name);
        item.description = it->name;
        item.clas = "sound sources";
        item.type = "soundsource";
        item.value = it->id;
        route->ref->refItems[QString("#TSRE#")+"sound sources"].push_back(item);
    }
    foreach (SoundListItem* it, route->soundList->regions){
    //for (auto it = route->soundList->regions.begin(); it != route->soundList->regions.end(); ++it ){
        Ref::RefItem item;
        item.filename.push_back(it->name);
        item.description = it->name;
        item.clas = "sound regions";
        item.type = "soundregion";
        item.value = it->id;
        route->ref->refItems[QString("#TSRE#")+"sound regions"].push_back(item);
    }
    
    Ref::RefItem item;
    item.filename.push_back("");
    item.description = "Ruler";
    item.clas = "tsre tools";
    item.type = "ruler";
    route->ref->refItems[QString("#TSRE#")+"tsre tools"].push_back(item);
    
    refOther.addItem("Signals");
    refOther.addItem("Forests");
    refOther.addItem("Sound Sources");
    refOther.addItem("Sound Regions");    
    refOther.addItem("SpeedSign");
    refOther.addItem("SpeedResume");
    refOther.addItem("SpeedWarning");
    refOther.addItem("Milepost");
    refOther.addItem("Route/Shapes Directory");
    refOther.addItem("TSRE Tools");
    refOther.setMaxVisibleItems(35);
    
    /// EFO add un-indexed shapes
    
    hash.clear();

    QDir routeShapes(Game::root + "/routes/" + Game::route + "/shapes" );
    routeShapes.setFilter(QDir::Files);          
    
    if(!routeShapes.exists()) qDebug() << "No Route Shapes Directory Found";
    
    foreach(QString dirFile, routeShapes.entryList()){
        if(dirFile.endsWith(".s", Qt::CaseInsensitive))                {
          
            Ref::RefItem item;
            item.filename.push_back(dirFile);
            item.description = dirFile;
            item.clas = "non-indexed";
            item.type = "static";
            route->ref->refItems[QString("#TSRE#")+"route/shapes directory"].push_back(item);
            Route::shapesList.append(dirFile.toLower());
        }
    }

        if((Game::listFiles == true) && (Game::loadAllWFiles == true))
        {    
            /// Compare loaded to shapes directory
            QFile file("./" + Game::route + "_filesNotUsed.txt");    
            if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(&file);
                QStringList sortedShapeList = Route::shapesList;
                sortedShapeList.sort();
                for (const QString& fileName : sortedShapeList) {
                    if ((Route::fileList.contains(fileName, Qt::CaseInsensitive) == false) && (Route::trackList.contains(fileName, Qt::CaseInsensitive) == false))
                    {
                       out << fileName << " \n";
//                       qDebug() << fileName << " not used";
                    }
//                    else
  //                      qDebug() << fileName << " is used";
                      // out << fileName << " --- NOT USED \n";                                
                }
                file.close();
            }
        }
    
}

void ObjTools::refClassSelected(const QString & text){
    refList.clear();
    currentItemList.clear();
    for (int it = 0; it < route->ref->refItems[text].size(); ++it ){
        new QListWidgetItem ( route->ref->refItems[text][it].description, &refList, it );
        currentItemList.push_back(&route->ref->refItems[text][it]);
    }
    refList.sortItems(Qt::AscendingOrder);
}

void ObjTools::refSearchSelected(const QString & text){
    refList.clear();
    currentItemList.clear();
    QMapIterator<QString, QVector<Ref::RefItem>> i(route->ref->refItems);
    int idx = 0;
    while (i.hasNext()) {
        i.next();
        for (int it = 0; it < i.value().size(); ++it ){
            if(i.value()[it].description.contains(text, Qt::CaseInsensitive)){
                new QListWidgetItem ( i.value()[it].description, &refList, idx++ );
                currentItemList.push_back((Ref::RefItem*)&i.value()[it]);
            }
        }
    }
    refList.sortItems(Qt::AscendingOrder);
}

void ObjTools::refTrackSelected(const QString & text){

    refList.clear();
    currentItemList.clear();
    for (int it = 0; it < route->ref->refItems[QString("#TDB#")+text].size(); ++it ){
        new QListWidgetItem ( route->ref->refItems[QString("#TDB#")+text][it].description, &refList, it );
        currentItemList.push_back(&route->ref->refItems[QString("#TDB#")+text][it]);
    }
    refList.sortItems(Qt::AscendingOrder);
}

void ObjTools::refOtherSelected(const QString & text){

    refList.clear();
    currentItemList.clear();
    for (int it = 0; it < route->ref->refItems[QString("#TSRE#")+text.toLower()].size(); ++it ){
        new QListWidgetItem ( route->ref->refItems[QString("#TSRE#")+text.toLower()][it].description, &refList, it );
        currentItemList.push_back(&route->ref->refItems[QString("#TSRE#")+text.toLower()][it]);
    }
    refList.sortItems(Qt::AscendingOrder);
}

void ObjTools::refListSelected(QListWidgetItem * item){
    try {
        route->ref->selected = currentItemList[item->type()];//&route->ref->refItems[refClass.currentText().toStdString()][refList.currentRow()];
        emit sendMsg("engItemSelected");
        itemSelected((Ref::RefItem*)route->ref->selected);
    } catch(const std::out_of_range& oor){
        route->ref->selected = NULL;
    }
    lastItems.clearSelection();
}

void ObjTools::lastItemsListSelected(QListWidgetItem * item){
    refList.clearSelection();
    if(Game::debugOutput) qDebug() << "ObjTools506:" << item->type() << " " << item->text();
    route->ref->selected = lastItemsPtr[item->type()];
}

void ObjTools::selectToolEnabled(bool val){
    if(val)
    {
        emit enableTool("selectTool");
        emit updStatus(QString("Stat3"), QString(""));       /// EFO Added to 
    }
    else
        emit enableTool("");
}

void ObjTools::placeToolEnabled(bool val){
    if(val)
    {
        emit enableTool("placeTool");
        emit updStatus(QString("Stat3"), QString(""));        /// EFO Added to 
    }
    else
        emit enableTool("");
}

void ObjTools::autoPlacementButtonEnabled(bool val){
    if(val)
        emit enableTool("autoPlaceSimpleTool");
    else
        emit enableTool("");
}

void ObjTools::resetRotationButtonEnabled(){
    emit sendMsg("resetPlaceRotation");
}

void ObjTools::autoPlacementDeleteLastEnabled(){
    emit sendMsg("autoPlacementDeleteLast");
}

void ObjTools::itemSelected(Ref::RefItem* item){     /// EFO Item selected on the list
    if(Game::debugOutput)
    {QString selectedFilename = item->currentFilename;
    if(Game::debugOutput) qDebug() << "ObjTools548:" << "selected: " << selectedFilename;    
    }   
    QString text;
    if(item->description.length() > 1) 
        text = item->description;
    else if (item->getShapeName().length() > 1)
        text = item->getShapeName();
    else
        text = item->type;
    
    //Avoid duplicates
    QList<QListWidgetItem*> found = lastItems.findItems(text, Qt::MatchExactly);
       if(Game::debugOutput)  qDebug() << "ObjTools560:" << "found : "<< found.length();
    
    if ((found.length() == 0)   ){    //// Added a check for placed=true    && (item->placed)

    // here's where it gets put on the recent list    
        
    lastItemsPtr.push_back(item);  
    
    /// calculating the item age and order
    new QListWidgetItem ( text, &lastItems, lastItemsPtr.size() - 1 );
    if(lastItems.count() > Game::numRecentItems){
        int val = 2147483646;
        int itID = -1;
        for(int i = 0; i < lastItems.count(); i++){
            if(lastItems.item(i)->type() < val){
                val = lastItems.item(i)->type();
                itID = i;
            }
        }
        if(itID != -1)
            delete lastItems.takeItem(itID);
    }
    
    lastItems.sortItems();
	}
}

void ObjTools::stickToTDBEnabled(int state){
    if(state == Qt::Checked)
        this->sendMsg("stickToTDB", true);
    else
        this->sendMsg("stickToTDB", false);
}

void ObjTools::autoPlacementLengthEnabled(QString val){
    bool ok = false;
    float v = val.toFloat(&ok);
    if(!ok) return;
    
    sendMsg("autoPlacementLength", v);
}

void ObjTools::advancedPlacementButtonEnabled(bool val){
    this->advancedPlacementWidget.setVisible(val);
}

void ObjTools::msg(QString text){
}

void ObjTools::msg(QString text, bool val){
}

void ObjTools::msg(QString text, int val){
}

void ObjTools::msg(QString text, float val){
}

void ObjTools::msg(QString text, QString val){
    if(text == "toolEnabled"){
        QMapIterator<QString, QPushButton*> i(buttonTools);
        while (i.hasNext()) {
            i.next();
            if(i.value() == NULL)
                continue;
            i.value()->blockSignals(true);
            i.value()->setChecked(false);
        }
        if(buttonTools[val] != NULL)
            buttonTools[val]->setChecked(true);
        i.toFront();
        while (i.hasNext()) {
            i.next();
            if(i.value() == NULL)
                continue;
            i.value()->blockSignals(false);
        }
    }
}

void ObjTools::autoPlacementRotTypeSelected(QString val){
    if(autoPlacementRotType.currentIndex() == 0)
        this->route->placementAutoTwoPointRot = true;
    else
        this->route->placementAutoTwoPointRot = false;
}

void ObjTools::autoPlacementTargetSelected(QString val){
    this->route->placementAutoTargetType = autoPlacementTarget.currentIndex();
}

void ObjTools::autoSnapableRadiusEnabled(QString val){
    float v;
    bool ok = false;
    v = val.toFloat(&ok);
    if(Game::debugOutput) qDebug() << "ObjTools655:" << "Game::snapableRadius"<<v;
    if(ok)
        Game::snapableRadius = v;
}


void ObjTools::chSnapableOnlyRotation(int val){
    if(val == 2)
         this->route->snapableOnlyRotation = true;
    else
         this->route->snapableOnlyRotation = false;
}

void ObjTools::autoPlacementOffsetEnabled(QString val){
    float v;
    bool ok = false;
    v = this->autoPlacementPosX.text().toFloat(&ok);
    if(ok)
        this->route->placementAutoTranslationOffset[0] = v;
    v = this->autoPlacementPosY.text().toFloat(&ok);
    if(ok)
        this->route->placementAutoTranslationOffset[1] = v;
    v = this->autoPlacementPosZ.text().toFloat(&ok);
    if(ok)
        this->route->placementAutoTranslationOffset[2] = v;
    

    v = this->autoPlacementRotX.text().toFloat(&ok);
    if(ok)
        this->route->placementAutoRotationOffset[0] = v;
    v = this->autoPlacementRotY.text().toFloat(&ok);
    if(ok)
        this->route->placementAutoRotationOffset[1] = v;
    v = this->autoPlacementRotZ.text().toFloat(&ok);
    if(ok)
        this->route->placementAutoRotationOffset[2] = v;
}

void ObjTools::showLastItemsContextMenu(QPoint val){
    QPoint globalPos = lastItems.mapToGlobal(val);

    QMenu myMenu;
    myMenu.addAction("Find similar", this, SLOT(lastItemsMenuFindSimilar()));

    myMenu.exec(globalPos);
}

void ObjTools::lastItemsMenuFindSimilar(){
    this->searchBox.setText(lastItems.currentItem()->text().left(6));
    refSearchSelected((const QString)lastItems.currentItem()->text().left(6));
}
