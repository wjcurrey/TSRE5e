/*  This file is part of TSRE5.
 *
 *  TSRE5 - train sim game engine and MSTS/OR Editors. 
 *  Copyright (C) 2016 Piotr Gadecki <pgadecki@gmail.com>
 *
 *  Licensed under GNU General Public License 3.0 or later. 
 *
 *  See LICENSE.md or https://www.gnu.org/licenses/gpl.html
 */

#include "PropertiesSpeedpost.h"
#include "SpeedpostObj.h"
#include "TRitem.h"
#include "Game.h"
#include "GLMatrix.h"

PropertiesSpeedpost::PropertiesSpeedpost() {
    
    QDoubleValidator* doubleValidator = new QDoubleValidator(-10000, 10000, 6, this); 
    doubleValidator->setNotation(QDoubleValidator::StandardNotation);
    QDoubleValidator* doubleValidator2 = new QDoubleValidator(-10000, 10000, 2, this); 
    doubleValidator2->setNotation(QDoubleValidator::StandardNotation);
    
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->setSpacing(2);
    vbox->setContentsMargins(0,1,1,1);
    infoLabel = new QLabel("SpeedPost:");
    infoLabel->setStyleSheet(QString("QLabel { color : ")+Game::StyleMainLabel+"; }");
    infoLabel->setContentsMargins(3,0,0,0);
    vbox->addWidget(infoLabel);
    QFormLayout *vlist = new QFormLayout;
    vlist->setSpacing(2);
    vlist->setContentsMargins(3,0,3,0);
    this->uid.setDisabled(true);
    this->tX.setDisabled(true);
    this->tY.setDisabled(true);
    vlist->addRow("Type:",&this->speedpostType);
    speedpostType.setDisabled(true);
    vlist->addRow("UiD:",&this->uid);
    vlist->addRow("Tile X:",&this->tX);
    vlist->addRow("Tile Z:",&this->tY);
    vbox->addItem(vlist);
    
    QLabel * label = new QLabel("Position:");
    label->setStyleSheet(QString("QLabel { color : ")+Game::StyleMainLabel+"; }");
    label->setContentsMargins(3,0,0,0);
    vbox->addWidget(label);
    vlist = new QFormLayout;
    vlist->setSpacing(2);
    vlist->setContentsMargins(3,0,3,0);
    vlist->addRow("X:",&this->posX);
    vlist->addRow("Y:",&this->posY);
    vlist->addRow("Z:",&this->posZ);
    vbox->addItem(vlist);
    speedlabel = new QLabel("Speed:");
    speedlabel->setStyleSheet(QString("QLabel { color : ")+Game::StyleMainLabel+"; }");
    speedlabel->setContentsMargins(3,0,0,0);
    chCustomSpeed.setText("Speed instead of Number");
    vbox->addWidget(speedlabel);
    vbox->addWidget(&chCustomSpeed);
    vbox->addWidget(&speed);
    vbox->addWidget(&kmm);
    kmm.setStyleSheet("combobox-popup: 0;");
    kmm.addItem("Kilometers");
    kmm.addItem("Miles");
    lSpeedFor = new QLabel("Speed for:");
    lSpeedFor->setContentsMargins(3,0,0,0);
    vbox->addWidget(lSpeedFor);
    vbox->addWidget(&ptb);
    ptb.addItem("Passenger");
    ptb.addItem("Freight");
    ptb.addItem("Both");
    ptb.setStyleSheet("combobox-popup: 0;");
    numberlabel = new QLabel("Number:");
    numberlabel->setStyleSheet(QString("QLabel { color : ")+Game::StyleMainLabel+"; }");
    numberlabel->setContentsMargins(3,0,0,0);
    chCustomNumber.setText("Number instead of Speed");
    vbox->addWidget(numberlabel);
    vbox->addWidget(&chCustomNumber);
    vbox->addWidget(&number);
    number.setValidator(doubleValidator2);
    chNumberDot.setText("Show Dot");
    vbox->addWidget(&chNumberDot);

    label = new QLabel("Track Items:");
    label->setStyleSheet(QString("QLabel { color : ")+Game::StyleMainLabel+"; }");
    label->setContentsMargins(3,0,0,0);
    vbox->addWidget(label);
    QPushButton *button = new QPushButton("Flip", this);
    vbox->addWidget(button);
    connect(button, SIGNAL(released()), this, SLOT(flipSignal()));
    chFlipShape.setText("Flip Shape");
    chFlipShape.setChecked(true);
    vbox->addWidget(&chFlipShape);
    QPushButton *bDeleteSelected = new QPushButton("Delete Selected");
    vbox->addWidget(bDeleteSelected);
    QObject::connect(bDeleteSelected, SIGNAL(released()),
                      this, SLOT(bDeleteSelectedEnabled()));
    QPushButton *bExpandSelected = new QPushButton("Expand");
    vbox->addWidget(bExpandSelected);
    QObject::connect(bExpandSelected, SIGNAL(released()),
                      this, SLOT(bExpandEnabled()));
    
    label = new QLabel("Global settings:");
    label->setStyleSheet(QString("QLabel { color : ")+Game::StyleMainLabel+"; }");
    label->setContentsMargins(3,0,0,0);
    vbox->addWidget(label);
    vbox->addWidget(new QLabel("Max placing radius:"));
    vbox->addWidget(&eMaxPlacingDistance);
    eMaxPlacingDistance.setValidator(doubleValidator);
    QObject::connect(&eMaxPlacingDistance, SIGNAL(textEdited(QString)), this, SLOT(eMaxPlacingDistanceEnabled(QString)));
    
    label = new QLabel("Advanced:");
    label->setStyleSheet(QString("QLabel { color : ")+Game::StyleMainLabel+"; }");
    label->setContentsMargins(3,0,0,0);
    vbox->addWidget(label);
    
    
    
    
    QPushButton *hacks = new QPushButton("Hacks", this);
    QObject::connect(hacks, SIGNAL(released()),
                      this, SLOT(hacksButtonEnabled()));
    vbox->addWidget(hacks);
    
    QObject::connect(&speed, SIGNAL(textEdited(QString)),
                      this, SLOT(speedEnabled(QString)));
    QObject::connect(&number, SIGNAL(textEdited(QString)),
                      this, SLOT(numberEnabled(QString)));
    QObject::connect(&chNumberDot, SIGNAL(stateChanged(int)),
                      this, SLOT(numberDotEnabled(int)));
    QObject::connect(&chCustomNumber, SIGNAL(stateChanged(int)),
                      this, SLOT(chCustomNumberEnabled(int)));
    QObject::connect(&chCustomSpeed, SIGNAL(stateChanged(int)),
                      this, SLOT(chCustomSpeedEnabled(int)));
    QObject::connect(&kmm, SIGNAL(activated(int)),
        this, SLOT(kmmListSelected(int)));
    QObject::connect(&ptb, SIGNAL(activated(int)),
        this, SLOT(ptbListSelected(int)));
    
    vbox->addStretch(1);
    this->setLayout(vbox);
}

PropertiesSpeedpost::~PropertiesSpeedpost() {
}

void PropertiesSpeedpost::speedEnabled(QString val){
    if(sobj == NULL) return;
    bool ok = false;
    int speedval = this->speed.text().toInt(&ok);
    if(!ok)
        return;
    Undo::StateBegin();
    Undo::PushGameObjData(worldObj);
    Undo::PushTrackDB(Game::trackDB);
    sobj->setSpeed(speedval);
    Undo::StateEnd();
}

void PropertiesSpeedpost::numberEnabled(QString val){
    if(sobj == NULL) return;
    bool ok = false;
    float numberval = this->number.text().toFloat(&ok);
    if(!ok)
        return;
    Undo::StateBegin();
    Undo::PushGameObjData(worldObj);
    Undo::PushTrackDB(Game::trackDB);
    sobj->setNumber(numberval);
    Undo::StateEnd();
}

void PropertiesSpeedpost::numberDotEnabled(int val){
    if(sobj == NULL) return;
    if(Game::debugOutput) qDebug()<<"aaa";
    Undo::StateBegin();
    Undo::PushGameObjData(worldObj);
    Undo::PushTrackDB(Game::trackDB, false);
    if(val == 2)
        sobj->setNumberDot(true);
    else
        sobj->setNumberDot(false);
    Undo::StateEnd();
}

void PropertiesSpeedpost::chCustomNumberEnabled(int val){
    if(sobj == NULL) return;
    if(Game::debugOutput) qDebug()<<"aaa";
    Undo::StateBegin();
    Undo::PushGameObjData(worldObj);
    Undo::PushTrackDB(Game::trackDB, false);
    if(val == 2){
        sobj->setNumberInsteadSpeed(true);
        this->number.show();
        this->chNumberDot.show();
        this->numberlabel->show();
    }else{
        sobj->setNumberInsteadSpeed(false);
        this->number.hide();
        this->chNumberDot.hide();
        this->numberlabel->hide();
    }
    Undo::StateEnd();
}

void PropertiesSpeedpost::chCustomSpeedEnabled(int val){
    if(sobj == NULL) return;
    if(Game::debugOutput) qDebug()<<"aaa";
    Undo::StateBegin();
    Undo::PushGameObjData(worldObj);
    Undo::PushTrackDB(Game::trackDB, false);
    if(val == 2){
        sobj->setSpeedInsteadNumber(true);
        this->speedlabel->show();
        this->speed.show();
        this->kmm.show();
    }else{
        sobj->setSpeedInsteadNumber(false);
        this->speedlabel->hide();
        this->speed.hide();
        this->kmm.hide();
    }
    Undo::StateEnd();
}

void PropertiesSpeedpost::kmmListSelected(int val){
    if(sobj == NULL) return;
    Undo::StateBegin();
    Undo::PushGameObjData(worldObj);
    Undo::PushTrackDB(Game::trackDB);
    sobj->setSpeedUnitId(val);
    Undo::StateEnd();
}

void PropertiesSpeedpost::ptbListSelected(int val){
    if(sobj == NULL) return;
    Undo::StateBegin();
    Undo::PushGameObjData(worldObj);
    sobj->setTrainType(ptb.currentIndex());
    Undo::StateEnd();
}

void PropertiesSpeedpost::flipSignal(){
    if(sobj == NULL)
        return;
    Undo::StateBegin();
    Undo::PushGameObjData(worldObj);
    Undo::PushTrackDB(Game::trackDB);
    sobj->flip(chFlipShape.isChecked());
    
    if(Game::sigOffset)
    {       
            if(Game::debugOutput)  qDebug() << "Filename: " << sobj->fileName.toLower() ;

            if(Game::debugOutput)  qDebug() << __FILE__ << " " << __LINE__ << ":" <<"1:P "<<sobj->firstPosition[0]<<" "<<sobj->firstPosition[1]<<" "<<sobj->firstPosition[2]<<" Q" <<sobj->qDirection[1]<<" "<<sobj->qDirection[3] ;            
            float thisOffset = 0;
            if(sobj->fileName.toLower().contains("gantry") == false) thisOffset = Game::sigOffset;
                
            sobj->position[0] = sobj->firstPosition[0];   /// (reset to the TrItemObj coordinates)
            // sobj->position[1] = sobj->firstPosition[1];
            sobj->position[2] = sobj->firstPosition[2];
            float pos[3];
            
            pos[0] = thisOffset;
            pos[1] = 0;
            pos[2] = 0;
            Vec3::transformQuat((float*)pos, (float*)pos, (float*)sobj->qDirection);
            sobj->translate(pos[0], pos[1], pos[2]);
            sobj->modified = true;
            sobj->setMartix(); 
            if(Game::debugOutput)  qDebug() << __FILE__ << " " << __LINE__ << ":" <<"2:P "<<sobj->position[0]<<" "<<sobj->position[1]<<" "<<sobj->position[2]<<" Q" <<sobj->qDirection[1]<<" "<<sobj->qDirection[3] ;                        
    }

    
    Undo::StateEnd();
}

void PropertiesSpeedpost::showObj(GameObj* obj){
    if(obj == NULL){
        infoLabel->setText("NULL");
        return;
    }
    worldObj = (WorldObj*)obj;
    sobj = (SpeedpostObj*)obj;
    QString stype = sobj->getSpeedpostType();
    this->infoLabel->setText("Object: "+sobj->type);
    this->speedpostType.setText(stype);
    this->uid.setText(QString::number(sobj->UiD, 10));
    this->tX.setText(QString::number(sobj->x, 10));
    this->tY.setText(QString::number(-sobj->y, 10));
    this->posX.setText(QString::number(sobj->position[0], 'G', 6));
    this->posY.setText(QString::number(sobj->position[1], 'G', 6));
    this->posZ.setText(QString::number(-sobj->position[2], 'G', 6));
    this->quat.setText(
            QString::number(sobj->qDirection[0], 'G', 4) + " " +
            QString::number(sobj->qDirection[1], 'G', 4) + " " +
            QString::number(-sobj->qDirection[2], 'G', 4) + " " +
            QString::number(sobj->qDirection[3], 'G', 4)
            );
    
    this->chCustomNumber.blockSignals(true);
    this->chCustomSpeed.blockSignals(true);
    this->chNumberDot.blockSignals(true);
    
    this->ptb.setCurrentIndex(sobj->getTrainType());
    this->eMaxPlacingDistance.setText(QString::number(sobj->MaxPlacingDistance));
    this->speed.setText(QString::number(sobj->getSpeed(), 'G', 4));
    this->number.setText(QString::number(sobj->getNumber(), 'G', 4));
    this->kmm.setCurrentIndex(sobj->getSpeedUnitId());
    this->chNumberDot.setChecked(sobj->isNumberDot());
    this->chCustomSpeed.setChecked(sobj->getSpeedInsteadNumber());
    this->chCustomNumber.setChecked(sobj->getNumberInsteadSpeed());
    this->chCustomSpeed.hide();
    this->speed.hide();
    this->kmm.hide();
    this->chCustomNumber.hide();
    this->number.hide();
    this->chNumberDot.hide();
    this->speedlabel->hide();
    this->numberlabel->hide();
    this->lSpeedFor->hide();
    this->ptb.hide();
    

    
    if(stype == "milepost"){
        if(sobj->getSpeedInsteadNumber()){
            this->speedlabel->show();
            this->speed.show();
            this->kmm.show();
        }
        this->chCustomSpeed.show();
        this->number.show();
        this->chNumberDot.show();
        this->numberlabel->show();
    }
    if(stype == "warning" || stype == "speedsign"){
        this->speed.show();
        this->kmm.show();
        if(sobj->getNumberInsteadSpeed()){
            this->number.show();
            this->chNumberDot.show();
            this->numberlabel->show();
        }
        this->chCustomNumber.show();
        this->speedlabel->show();
        this->lSpeedFor->show();
        this->ptb.show();
    }
    if(stype == "resume"){
        if(sobj->getNumberInsteadSpeed()){
            this->number.show();
            this->chNumberDot.show();
            this->numberlabel->show();
        }
        this->chCustomNumber.show();
    }
    this->chNumberDot.blockSignals(false);
    this->chCustomNumber.blockSignals(false);
    this->chCustomSpeed.blockSignals(false);
}

void PropertiesSpeedpost::updateObj(GameObj* obj){
    if(obj == NULL){
        return;
    }
    sobj = (SpeedpostObj*)obj;
    if(!posX.hasFocus() && !posY.hasFocus() && !posZ.hasFocus() && !quat.hasFocus()){
        this->uid.setText(QString::number(sobj->UiD, 10));
        this->tX.setText(QString::number(sobj->x, 10));
        this->tY.setText(QString::number(-sobj->y, 10));
        this->posX.setText(QString::number(sobj->position[0], 'G', 6));
        this->posY.setText(QString::number(sobj->position[1], 'G', 6));
        this->posZ.setText(QString::number(-sobj->position[2], 'G', 6));
        this->quat.setText(
                QString::number(sobj->qDirection[0], 'G', 4) + " " +
                QString::number(sobj->qDirection[1], 'G', 4) + " " +
                QString::number(-sobj->qDirection[2], 'G', 4) + " " +
                QString::number(sobj->qDirection[3], 'G', 4)
                );
    }
    

}

bool PropertiesSpeedpost::support(GameObj* obj){
    if(obj == NULL)
        return false;
    if(obj->typeObj != GameObj::worldobj)
        return false;
    if(((WorldObj*)obj)->type == "speedpost")
        return true;
    return false;
}

void PropertiesSpeedpost::eMaxPlacingDistanceEnabled(QString val){
    if(sobj == NULL){
        return;
    }
    bool ok = false;
    float fval = val.toFloat(&ok);
    if(ok){
        if(fval > 0)
            sobj->MaxPlacingDistance = fval;
    }
}

void PropertiesSpeedpost::bDeleteSelectedEnabled(){
    if(sobj == NULL)
        return;
    Undo::StateBegin();
    Undo::PushGameObjData(worldObj);
    Undo::PushTrackDB(Game::trackDB, false);
    sobj->deleteSelectedTrItem();
    Undo::StateEnd();
}

void PropertiesSpeedpost::bExpandEnabled(){
    if(sobj == NULL)
        return;
    Undo::StateBegin();
    Undo::PushGameObjData(worldObj);
    Undo::PushTrackDB(Game::trackDB, false);
    sobj->expandTrItems();
    Undo::StateEnd();
}

void PropertiesSpeedpost::hacksButtonEnabled(){
    if(sobj == NULL){
        return;
    }
    
    QDialog d;
    d.setMinimumWidth(400);
    d.setWindowTitle("SpeedpostObj Hacks");
    QVBoxLayout *vbox = new QVBoxLayout;
    QLabel *label = new QLabel("Use only if you know what you are doing.");
    label->setContentsMargins(3,0,0,0);
    vbox->addWidget(label);
    label->setWordWrap(true);
    QPushButton *haxRemoveTDBVector = new QPushButton("Remove broken Track Items and Expand", this);
    QObject::connect(haxRemoveTDBVector, SIGNAL(released()),
                      this, SLOT(haxFixTrackItemsEnabled()));
    vbox->addWidget(haxRemoveTDBVector);

    vbox->setSpacing(2);
    vbox->setContentsMargins(3,3,3,3);
    vbox->addStretch(1);
    d.setLayout(vbox);
    d.exec();
}

void PropertiesSpeedpost::haxFixTrackItemsEnabled(){
    if(sobj == NULL){
        return;
    }

    int res = sobj->fixTrackItems();
    QMessageBox dialog;
    if(res == -1)
        dialog.setText("Speedpost broken, can't fix.");
    else if(res == 0)
        dialog.setText("No need for fix.");
    else
        dialog.setText("Fixed "+QString::number(res)+"Track Items.");
    dialog.exec();
}