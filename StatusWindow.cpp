/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

#include "StatusWindow.h"
#include <QtWidgets>
#include <QDebug>
#include "Game.h"


StatusWindow::StatusWindow(QWidget* parent) : QWidget(parent) {

    
    this->setWindowFlags(Qt::WindowType::Tool);
    this->setFixedWidth(300);
    this->setFixedHeight(180);
    this->setWindowTitle(tr("Status Window"));
    QStringList winPos = Game::statusPos.split(","); 
    this->move( winPos[0].trimmed().toInt(), winPos[1].trimmed().toInt());

    // Define Status tag defaults  -- removed * for testing
    QLabel *status1 = new QLabel ("Something1: Off", this);
/*
    QLabel status2 = new QLabel("Something2: On", this);
    QLabel status3 = new QLabel("Something3: Locked", this);
    QLabel status4 = new QLabel("Something4: Off", this);
    QLabel status5 = new QLabel("Something5: Status", this);
    QLabel status6 = new QLabel("Something6: Unlocked", this);
    QLabel status7 = new QLabel("Something7: Off", this);
    QLabel status8 = new QLabel("Something8: On", this);
    QLabel status9 = new QLabel("Something9: Locked", this);
    QLabel status10 = new QLabel("Something10: Off", this);
    QLabel status11 = new QLabel("Something11: Status", this);
    QLabel status12 = new QLabel("Something12: Unlocked", this);
    QLabel status13 = new QLabel("Something13: Off", this);
    QLabel status14 = new QLabel("Something14: On", this);
    QLabel status15 = new QLabel("Something15: Locked", this);
    QLabel status16 = new QLabel("Something16: Off", this);
    QLabel status17 = new QLabel("Something17: Status", this);
    QLabel status18 = new QLabel("Something18: Unlocked", this);
    QLabel status19 = new QLabel("Something17: Status", this);
    QLabel status20 = new QLabel("Something18: Unlocked", this);
  */   

    // Outer container
    QVBoxLayout *vv = new QVBoxLayout;
    vv->setSpacing(2);
    vv->setContentsMargins(0,1,1,1);

    /// Grid within the outer container
    QGridLayout *vvbox = new QGridLayout;
    vvbox->setSpacing(2);
    vvbox->setContentsMargins(3,0,1,0);    

    /// Add individual STATUS tags
    
    vvbox->addWidget( status1, 1,0);
/*
    vbox->addWidget( status2, 2,0);
    vbox->addWidget( status3, 3,0);
    vbox->addWidget( status4, 4,0);
    vbox->addWidget( status5, 5,0);
    vbox->addWidget( status6, 6,0);
    vbox->addWidget( status7, 7,0);
    vbox->addWidget( status8, 8,0);
    vbox->addWidget( status9, 9,0);
    vbox->addWidget(status10,10,0);
    vbox->addWidget(status11, 1,1);
    vbox->addWidget(status12, 2,1);
    vbox->addWidget(status13, 3,1);
    vbox->addWidget(status14, 4,1);
    vbox->addWidget(status15, 5,1);
    vbox->addWidget(status16, 6,1);
    vbox->addWidget(status17, 7,1);
    vbox->addWidget(status18, 8,1);
    vbox->addWidget(status19, 9,1);
    vbox->addWidget(status20,10,1);
  */    
    
    // add the grid to the container
    vv->addItem(vvbox);

    //   status1->setText("R off");
 //   status2->setText("/ off");
 //   status3->setText("Camera unlocked");
 //   status4->setText("Height off");
 //   status5->setText("Something off");
 //   status6->setText("Something off");

    this->setLayout(vv);
    
    
 
}

void StatusWindow::recStatus(QString statVal ){   
    // qDebug() << "status: " << statVal;
    // this->status1->setText(QString(statVal));

    if(statVal.contains("Rotate")) { statusRotateOn(); }    
    //if(statVal.contains("Transform")) status2->setText(statVal);
    //if(statVal.contains("Resize")) status3->setText(statVal);

}
    
void StatusWindow::statusRotateOn()
{
      qDebug() << "I see this: " ; 
      //this->status1->setText("Rotate on");
}
    