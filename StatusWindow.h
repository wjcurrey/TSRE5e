/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   StatusWindow.h
 * Author: E
 *
 * Created on February 23, 2024, 6:42 PM
 */

#ifndef STATUSWINDOW_H
#define STATUSWINDOW_H

#include <QtWidgets>
#include <QBasicTimer>


class StatusWindow : public QWidget {
    Q_OBJECT
public:
    StatusWindow(QWidget* parent);
    
        QLabel *status1;
        QLabel status2;
        QLabel status3;
        QLabel status4;
        QLabel status5;
        QLabel status6;
        QLabel status7;
        QLabel status8;
        QLabel status9;
        QLabel status10;
        QLabel status11;
        QLabel status12;
        QLabel status13;
        QLabel status14;
        QLabel status15;
        QLabel status16;
        QLabel status17;    
        QLabel status18;
        QLabel status19;
        QLabel *status20;    
        
private slots:
    
        void recStatus(QString statVal );       
        void statusRotateOn();

};



#endif /* STATUSWINDOW_H */

