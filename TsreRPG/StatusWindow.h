/*  This file is part of TSRE5.
 *
 *  TSRE5 - train sim game engine and MSTS/OR Editors. 
 *  Copyright (C) 2016 Piotr Gadecki <pgadecki@gmail.com>
 *
 *  Licensed under GNU General Public License 3.0 or later. 
 *
 *  See LICENSE.md or https://www.gnu.org/licenses/gpl.html
 */

#ifndef STATUSWINDOW_H
#define	STATUSWINDOW_H

#include <QtWidgets>
#include <QMap>

class StatusWindow : public QWidget {
    Q_OBJECT
public:
    StatusWindow(QWidget* parent);
    virtual ~StatusWindow();
    
public slots:

    void recStatus(QString statName, QString statVal );       
    void cameraButtonAction(bool val);
    
    
signals:
    void windowClosed();
    void enableTool(QString name);
    
protected:
    void hideEvent(QHideEvent *e);


    
private:
    /// EFO New
    QLineEdit status0;        
    QLineEdit status1;
    QLineEdit status2;
    QLineEdit status3;
    QLineEdit status4;        
    QLineEdit status5;
    QLineEdit status6;
    QLineEdit status7;
    QLineEdit status8;        
    QLineEdit status9;    
    QLineEdit status10;    
    QLineEdit status11;        
    
    QString statG;
    QString statY;
    QString statS;
    QString statR;
    ///
    
};

#endif	/* STATUSWINDOW_H */

