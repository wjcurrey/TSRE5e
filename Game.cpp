/*  This file is part of TSRE5.
 *
 *  TSRE5 - train sim game engine and MSTS/OR Editors. 
 *  Copyright (C) 2016 Piotr Gadecki <pgadecki@gmail.com>
 *
 *  Licensed under GNU General Public License 3.0 or later. 
 *
 *  See LICENSE.md or https://www.gnu.org/licenses/gpl.html
 */

#include "Game.h"
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QString>
#include <QEventLoop>
//#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
//#include <QUrl>
//#include <QUrlQuery>
//#include "RouteEditorWindow.h"
//#include "LoadWindow.h"
//#include "CELoadWindow.h"
#include "SoundList.h"
#include "ShapeLib.h"
#include "EngLib.h"
#include <QtWidgets>
#include <QColor>
#include "TarFile.h"
#include "Renderer.h"
#include "RouteEditorWindow.h"
#include "NaviWindow.h"
#include "StatusWindow.h"
#include "Camera.h"

bool Game::ServerMode = false;
QString Game::serverLogin = "";
QString Game::serverAuth = "";
RouteEditorClient *Game::serverClient = NULL;
GeoWorldCoordinateConverter *Game::GeoCoordConverter = NULL;
TDB *Game::trackDB = NULL;
TDB *Game::roadDB = NULL;    
SoundList *Game::soundList = NULL;    
TerrainLib *Game::terrainLib = NULL;   

bool Game::UseWorkingDir = false;
QString Game::AppName = "TSRE5";
QString Game::AppVersion = "Trainsim.Com Fork v0.8.004c ";
QString Game::AppDataVersion = "0.697";
QString Game::root = "";
QString Game::route = "";
QString Game::routeName = "";
QString Game::trkName = "";
QString Game::season = "";
//QString Game::route = "traska";
//QString Game::route = "cmk";
QString Game::mainWindowLayout = "PWT";
QString Game::ceWindowLayout = "C1";
QString Game::ActivityToPlay = "";
Renderer *Game::currentRenderer = NULL;
bool Game::playerMode = false;
bool Game::useNetworkEng = false;
bool Game::useQuadTree = false;
bool Game::useTdbEmptyItems = true;
int Game::allowObjLag = 1000;
int Game::maxObjLag = 10;
bool Game::ignoreLoadLimits = false;
int Game::startTileX = 0;
int Game::startTileY = 0;
float Game::objectLod = 3000;
float Game::distantLod = 100000;
int Game::tileLod = 1;
int Game::start = 0;
bool Game::ignoreMissingGlobalShapes = false;
bool Game::deleteTrWatermarks = false;
bool Game::deleteViewDbSpheres = false;
bool Game::createNewRoutes = false;
bool Game::writeEnabled = false;
bool Game::writeTDB = false;
bool Game::systemTheme = false;
bool Game::toolsHidden = false;
bool Game::usenNumPad = false;
float Game::cameraFov = 55.0f;
float Game::cameraSpeedMin = 1.0;
float Game::cameraSpeedStd = 3.0;
float Game::cameraSpeedMax = 40.0;
float Game::mouseSpeed = 1.0;
bool Game::cameraStickToTerrain = false;
bool Game::mstsShadows = false;

bool Game::viewWorldGrid = true;
bool Game::viewTileGrid = true;
bool Game::viewTerrainGrid = false;
bool Game::viewTerrainShape = true;
bool Game::viewInteractives = true;
bool Game::viewTrackDbLines = true;
bool Game::viewTsectionLines = true;
bool Game::viewPointer3d = true;
bool Game::viewMarkers = false;
bool Game::viewSnapable = false;
bool Game::viewCompass = false;
bool Game::warningBox = false;
bool Game::leaveTrackShapeAfterDelete = false;
bool Game::renderTrItems = false;
int Game::newRouteX = -5000;
int Game::newRouteZ = 15000;

bool Game::consoleOutput = false;
int Game::fpsLimit = 0;
bool Game::ortsEngEnable = true;
bool Game::sortTileObjects = true;
int Game::oglDefaultLineWidth = 1;
bool Game::showWorldObjPivotPoints = false;
int Game::shadowMapSize = 2048;
int Game::shadowLowMapSize = 1024;
int Game::shadowsEnabled = 1;
float Game::sunLightDirection[] = {-1.0,2.0,1.0};
int Game::textureQuality = 1;
float Game::snapableRadius = 20;
bool Game::snapableOnlyRot = false;
float Game::trackElevationMaxPm = 700.0;
bool Game::proceduralTracks = false;
bool Game::fullscreen = false;
bool Game::hudEnabled = false;
float Game::hudScale = 1.0;
bool Game::markerLines = false;

bool Game::loadAllWFiles = false;
bool Game::autoFix = false;
bool Game::gui = true;

QString Game::geoPath = "hgst";

//RouteEditorWindow* Game::window = NULL;
//LodWindow* Game::loadWindow = NULL;
ShapeLib *Game::currentShapeLib = NULL;
EngLib *Game::currentEngLib = NULL;
Route *Game::currentRoute = NULL;
GameObj *Game::currentSelectedGameObj = NULL;
QColor *Game::colorConView = NULL;
QColor *Game::colorShapeView = NULL;

QString Game::StyleMainLabel = "#770000";
QString Game::StyleGreenButton = "#55FF55";
QString Game::StyleRedButton = "#FF5555";
QString Game::StyleYellowButton = "#FFFF55";
QString Game::StyleGreenText = "#009900";
QString Game::StyleRedText = "#990000";

QString Game::imageMapsUrl;
int Game::mapImageResolution = 4096;

bool Game::autoNewTiles = false;
bool Game::autoGeoTerrain = false;

bool Game::useSuperelevation = false;

bool Game::soundEnabled = false;

int Game::AASamples = 0;
bool Game::AARemoveBorder = false;
float Game::PixelRatio = 1.0;

float Game::fogDensity = 0.7;
float Game::shadow1Res = 2000.0;
float Game::shadow1Bias = 0.0025;
float Game::shadow2Res = 4000.0;
float Game::shadow2Bias = 0.002;
//float fogColor[4]{0.5, 0.75, 1.0, 1.0};
float Game::fogColor[4] = {230.0/255.0,248.0/255,255.0/255.0, 1.0};
float Game::skyColor[4] = {230.0/255.0,248.0/255,255.0/255.0, 1.0};

int Game::DefaultElevationBox = 0;
float Game::DefaultMoveStep = 0.25;

bool Game::seasonalEditing = false;
int Game::numRecentItems = 11;
bool Game::useOnlyPositiveQuaternions = false;

QStringList Game::objectsToRemove;
QString Game::routeMergeString;

// EFO added 
float Game::wireLineHeight = 3;
float Game::sectionLineHeight = 2.8;
float Game::terrainTools[] = {1,5,5,9,1,10};
int   Game::selectedWidth = 2;
int   Game::selectedTerrWidth = 2;
bool  Game::lockCamera = false;
QColor *Game::selectedColor = new QColor("#FF0000");       /// EFO default red
QColor *Game::selectedTerrColor = new QColor("#FF0000");   /// EFO default red

QString Game::mainPos;   /// EFO Null handling exists
QString Game::statusPos;  /// EFO Null handling exists
QString Game::naviPos;  /// EFO Null handling exists

bool  Game::debugOutput = false;
bool  Game::legacySupport = false; 
bool  Game::newSymbols = true;
int   Game::pointerIn = 4;
int   Game::pointerOut = 3;
int   Game::pyramid = 5;
int   Game::maxAutoPlacement = 999;
int   Game::imageMapsZoomOffset = 0;
float Game::railProfile[] = {0.7175, 0.7895};
float Game::convertHeight = 1;  /// EFO will set to feet = 3.28084 if useImperial is set to true;
QString Game::convertUnit = "m";
int   Game::markerHeight = 30;
int   Game::markerText = 16;
float Game::lastElev = 0.0;
float Game::sigOffset = 0;
QStringList Game::markerFiles;
bool Game::reload;
QString Game::MapAPIKey = "";
bool Game::imageSubstitution = true;
bool Game::imageUpgrade = true;
int Game::convertThreshold = 999;
int Game::convertDivisor = 2000;


QHash<QString, int> Game::TextureFlags {
        {"none", 0x0},
        {"snow", 0x1},
        {"snowtrack", 0x2},
        {"spring", 0x4},
        {"autumn", 0x8},
        {"winter", 0x10},
        {"springsnow", 0x20},
        {"autumnsnow", 0x40},
        {"wintersnow", 0x80},
        {"night", 0x100},
        {"underground", 0x40000000}
    };

void Game::InitAssets() {
    QString path;
    bool newInstallation = false;
    path = "./tsre_assets/";
    QFile appFile3(path);
    if (!appFile3.exists()){
        QDir().mkdir(path);
    }
    
    path = "./tsre_appdata/";
    
    QFile appFile1(path);
    if (!appFile1.exists()){
        newInstallation = true;
        QMessageBox msgBox;
        msgBox.setWindowTitle("TSRE");
        msgBox.setText("Welcome in TSRE!\n\nThis is experimental version.\nUsing it may seriously damage your data."
                       "\nMake backup first!\n\n\nNow TSRE will download app data.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
        QDir().mkdir(path);
    }
    
    path += Game::AppDataVersion;
    
    QFile appFile2(path);
    if (!appFile2.exists()){
        qDebug() << "no appdata";
        DownloadAppData(path);
    }
    if (!appFile2.exists()){
        qDebug() << "appdata failed to load";
        return;
    }
}

void Game::load() {
    
    QString sh;
    QString path;
    
    path = "settings.txt";
    QFile file(path);
    
    if (!file.exists()){
        qDebug() << "creating new settings file";
        CreateNewSettingsFile();
    }
    
    if (!file.open(QIODevice::ReadOnly)){
        qDebug() << "settings file fails to open";
        return;
    }
    
    if(Game::debugOutput) qDebug() << path;

    QTextStream in(&file);
    in.setCodec("UTF-8");
    QString line;
    QStringList args;
    QString setval;
    QString setname; 
    QString skipped;   // save what's being skipped for output later

    qDebug() << "Debug: " << Game::debugOutput;
    
    if(Game::reload) qDebug() << "Limited Reload In Progress";
    
    while (!in.atEnd()) {
        line = in.readLine();
        
       //qDebug() << line;
       
        // EFO  Partial comment stripper if "//" is found after arguments
        if (line.indexOf("//") >= 0 && line.indexOf("://") <= 0) {
            skipped = line.mid(line.indexOf("//"),99);
            line = line.left(line.indexOf("//"));
        }
       
       // EFO Main comment stripper
       if(line.startsWith("#", Qt::CaseInsensitive)) {  if(Game::debugOutput) qDebug() << "Skip#   : " << skipped;  ; continue;}
       if(line.startsWith("//", Qt::CaseInsensitive)){  if(Game::debugOutput) qDebug() << "Skip  //: " << skipped; ; continue;}
        
        //args = line.split("=");
        args.clear();
        args.push_back(line.section('=', 0, 0));
        args.push_back(line.section('=', 1));
        //if(Game::debugOutput) qDebug() << args[0] << args[1];
        
        
        if(args.count() < 2) continue;
        setname = args[0].trimmed().toLower();       
        setval = args[1].trimmed().toLower();
        setval = setval.replace("\"","");
        
        if(setname.length()==0) continue;
        
        if(Game::debugOutput) qDebug() << "Args    : " << args[0].trimmed() << " "<< args[1].trimmed();
        if(Game::debugOutput) qDebug() << "Sets    : " << setname << "=" << setval;        
        
        //// These are protected and should never be reloaded
        if(Game::reload == false)
        {
            if(setname =="gameroot") 
                root = setval;

            if(setname =="routename")
                route = setval;

            if(setname =="starttilex"){
                Game::start++;
                startTileX = setval.toInt();
            }
            if(setname =="starttiley"){
                Game::start++;
                startTileY = setval.toInt();
            }                        

            if(setname =="writeenabled"){
                if((setval == "true") or (setval == "1") or (setval == "on"))
                    writeEnabled = true;
                else
                    writeEnabled = false;
            }
            if(setname =="writetdb"){
                if((setval == "true") or (setval == "1") or (setval == "on"))
                    writeTDB = true;
                else
                    writeTDB = false;
            }

            if(setname =="tilelod"){
                tileLod = setval.toInt();
            }
            if(setname =="objectlod"){
                objectLod = setval.toInt();
            }
            if(setname =="maxobjlag"){
                maxObjLag = setval.toInt();
            }
            if(setname =="allowobjlag"){
                allowObjLag = setval.toInt();
            }
            if(setname =="fpslimit"){
                fpsLimit = setval.toInt();
            }
            if(setname =="camerafov"){
                cameraFov = setval.toFloat();
            }
            if(setname =="warningbox"){
                if((setval == "true") or (setval == "1") or (setval == "on"))
                    warningBox = true;
                else
                    warningBox = false;
            }
            if(setname =="leavetrackshapeafterdelete"){
                if((setval == "true") or (setval == "1") or (setval == "on"))
                    leaveTrackShapeAfterDelete = true;
                else
                    leaveTrackShapeAfterDelete = false;
            }

            // EFO configure yellow line display height
            if(setname =="wirelineheight"){
                wireLineHeight = setval.toFloat();
            }

            // EFO configure grey line display height
            if(setname =="sectionlineheight"){
                sectionLineHeight = setval.toFloat();
            }

            if(setname =="ogldefaultlinewidth"){
                oglDefaultLineWidth = setval.toInt();
            }        

            if(setname =="aasamples"){
                AASamples = setval.toInt();
            }

            if(setname =="proceduraltracks"){
                if((setval == "true") or (setval == "1") or (setval == "on"))
                    proceduralTracks = true;
                else
                    proceduralTracks = false; 
            }
            if(setname =="fullscreen"){
                if((setval == "true") or (setval == "1") or (setval == "on"))
                    fullscreen = true;
                else
                    fullscreen = false; 
            }

            if(setname =="usetdbemptyitems"){
                if((setval == "true") or (setval == "1") or (setval == "on"))
                    useTdbEmptyItems = true;
                else
                    useTdbEmptyItems = false; 
            }
            if(setname =="useworkingdir"){
                if((setval == "true") or (setval == "1") or (setval == "on"))
                    UseWorkingDir = true;
                else
                    UseWorkingDir = false; 
            }
            if(setname =="numrecentitems"){
                numRecentItems = setval.toInt();
            }

            if(setname =="loadallwfiles"){
                if((setval == "true") or (setval == "1") or (setval == "on"))
                    loadAllWFiles = true;
                else
                    loadAllWFiles = false; 
            }
            if(setname =="autofix"){
                if((setval == "true") or (setval == "1") or (setval == "on"))
                    autoFix = true;
                else
                    autoFix = false; 
            }
            if(setname =="useonlypositivequaternions"){
                if((setval == "true") or (setval == "1") or (setval == "on"))
                    useOnlyPositiveQuaternions = true;
                else
                    useOnlyPositiveQuaternions = false; 
            }
            if(setname =="routemergestring")
                routeMergeString = setval;
            if(setname =="objectsToRemove")
                objectsToRemove = setval.split(":");
            if(setname =="serverlogin"){
                serverLogin = args[1].trimmed();
            }
            if(setname =="serverauth"){
                serverAuth = args[1].trimmed();
            }

            // EFO Configure WindowPos
            if(setname =="mainwindow") {
                mainPos = setval;
            }

            if(setname =="naviwindow") {
                naviPos = setval;
            }      

            if(setname =="statuswindow") {
                statusPos = setval;
            }

            if(setname == "markerheight"){
                    markerHeight = setval.toInt();
            }       

            if(setname == "markertext"){
                    markerText = setval.toFloat();
            }       

            if(setname == "sigoffset"){
                sigOffset = setval.toFloat();
            }
            
        }
        
        //// These should be reload safe
        
        if(setname =="consoleoutput"){
            if((setval == "true") or (setval == "1") or (setval == "on")) 
                Game::consoleOutput = true;
            else
                Game::consoleOutput = false;
        }
        
        if(setname =="debugoutput"){
            if((setval == "true") or (setval == "1") or (setval == "on"))
                Game::debugOutput = true;
            else if(setval == "ext")
            {
                qSetMessagePattern("%{file}:%{function}:%{line}: \t%{message}");
                Game::debugOutput = true;
                qDebug() << "Expanded Debugging Enabled";
                
            }
            else
                Game::debugOutput = false;
        }        
        
        if(setname =="legacysupport"){
            if((setval == "true") or (setval == "1") or (setval == "on"))
                Game::legacySupport = true;
        }
        
        if(setname =="deletetrwatermarks"){
            if((setval == "true") or (setval == "1") or (setval == "on"))
                deleteTrWatermarks = true;
            else
                deleteTrWatermarks = false;
        }
        if(setname =="deleteviewdbspheres"){
            if((setval == "true") or (setval == "1") or (setval == "on"))
                deleteViewDbSpheres = true;
            else
                deleteViewDbSpheres = false;
        }
        if(setname =="createnewifnotexist"){
            if((setval == "true") or (setval == "1") or (setval == "on"))
                createNewRoutes = true;
            else
                createNewRoutes = false;
        }
        
        if(setname =="systemtheme"){
            if((setval == "true") or (setval == "1") or (setval == "on"))
                systemTheme = true;
            else
                systemTheme = false;
        }
        if(setname =="toolshidden"){
            if((setval == "true") or (setval == "1") or (setval == "on"))
                toolsHidden = true;
            else
                toolsHidden = false;
        }
        if(setname =="usennumpad"){
            if((setval == "true") or (setval == "1") or (setval == "on"))
                usenNumPad = true;
            else
                usenNumPad = false;
        }

        if(setname =="rendertritems"){
            if((setval == "true") or (setval == "1") or (setval == "on"))
                renderTrItems = true;
            else
                renderTrItems = false;
        }


        
        // EFO configure selectedTerrWidth
        if(setname =="selectedterrwidth"){
            selectedTerrWidth = setval.toInt();
        }

                // EFO configure selectedTerrWidth
        if(setname =="selectedwidth"){
            selectedWidth = setval.toInt();
        }

        
        if(setname =="selectedcolor"){
            selectedColor = new QColor(setval);
        }
        
        if(setname =="selectedterrcolor"){
            selectedTerrColor = new QColor(setval);
        }
        
        // EFO Configure Terrain Tools
        if(setname =="terrainsize") {
            terrainTools[0] = setval.toInt();
        }
        if(setname =="terrainembankment") {
            terrainTools[1] = setval.toInt();
        }
        if(setname =="terraincut") {
            terrainTools[2] = setval.toInt();
        }
        if(setname =="terrainradius") {
            terrainTools[3] = setval.toInt();
        }
        if(setname =="terrainbrushsize") {
            terrainTools[4] = setval.toInt();
        }
        if(setname =="terrainbrushintensity") {
            terrainTools[5] = setval.toInt();
        }
        // END EFO Configure Terrain Tools
        
        
        if(setname =="geopath")
            geoPath = setval;
        if(setname =="colorconview")
            colorConView = new QColor(setval);
        if(setname =="colorshapeview")
            colorShapeView = new QColor(setval);
        if(setname =="ortsengenable"){
            if((setval == "true") or (setval == "1") or (setval == "on"))
                ortsEngEnable = true;
            else
                ortsEngEnable = false;
        }
        if(setname =="sorttileobjects"){
            if((setval == "true") or (setval == "1") or (setval == "on"))
                sortTileObjects = true;
            else
                sortTileObjects = false;
        }
        
        if(setname =="ignoremissingglobalshapes"){
            if((setval == "true") or (setval == "1") or (setval == "on"))
                ignoreMissingGlobalShapes = true;
            else
                ignoreMissingGlobalShapes = false;
        }
        if(setname =="snapableonlyrot"){
            if((setval == "true") or (setval == "1") or (setval == "on"))
                snapableOnlyRot = true;
            else
                snapableOnlyRot = false; 
        }
        
        
        if(setname =="shadowsenabled"){
          if((setval == "true") or (setval == "1") or (setval == "on"))  
            shadowsEnabled = 1;
        }
        if(setname =="shadowmapsize"){
            shadowMapSize = setval.toInt();
            if(shadowMapSize == 8192){
                shadow1Res = 3000.0;
                shadow1Bias = 0.0004;
            }
            if(shadowMapSize == 4096){
                shadow1Res = 2500.0;
                shadow1Bias = 0.0007;
            }
        }
        if(setname =="shadowlowmapsize"){
            shadowLowMapSize = setval.toInt();
            if(shadowLowMapSize >= 2048){
                shadow2Res = 4000.0;
                shadow2Bias = 0.001;
            }
        }
        
        if(setname =="texturequality"){
            textureQuality = setval.toInt();
        }
        if(setname =="imagemapsurl"){
            imageMapsUrl = args[1].trimmed();
        }        
        
        if(setname =="imagemapszoomoffset"){
            imageMapsZoomOffset = setval.toInt();
        }
        
        
        
        if(setname =="mapimageresolution"){
            mapImageResolution = setval.toInt();
        }
 
        if(setname =="camerasticktoterrain"){
            if((setval == "true") or (setval == "1") or (setval == "on"))
                cameraStickToTerrain = true;
            else
                cameraStickToTerrain = false; 
        }

        if(setname =="soundenabled"){
            if((setval == "true") or (setval == "1") or (setval == "on"))
                soundEnabled = true;
            else
                soundEnabled = false; 
        }
        
        if(setname =="cameraspeedmin"){
            cameraSpeedMin = setval.toFloat();
        }
        if(setname =="cameraspeedstd"){
            cameraSpeedStd = setval.toFloat();
        }
        if(setname =="cameraspeedmax"){
            cameraSpeedMax = setval.toFloat();
        }
        if(setname =="mousespeed"){
            mouseSpeed = setval.toFloat();
        }
        if(setname =="trackelevationmaxpm"){
            trackElevationMaxPm = setval.toFloat();
        }
        if(setname =="mainwindowlayout"){
            mainWindowLayout = setval;
        }
        if(setname =="cewindowlayout"){
            ceWindowLayout = setval;
        }
        if(setname =="usequadtree"){
            if((setval == "true") or (setval == "1") or (setval == "on"))
                useQuadTree = true;
            else
                useQuadTree = false; 
        }
        if(setname =="playermode"){
            if((setval == "true") or (setval == "1") or (setval == "on"))
                playerMode = true;
            else
                playerMode = false; 
        }
        if(setname =="usenetworkeng"){
            if((setval == "true") or (setval == "1") or (setval == "on"))
                useNetworkEng = true;
            else
                useNetworkEng = false; 
        }
        if(setname =="fogdensity"){
            fogDensity = setval.toFloat();
        }
        if(setname =="fogcolor"){
            QColor tcolor(setval);
            fogColor[0] = tcolor.redF();
            fogColor[1] = tcolor.greenF();
            fogColor[2] = tcolor.blueF();
        }
        if(setname =="skycolor"){
            QColor tcolor(setval);
            skyColor[0] = tcolor.redF();
            skyColor[1] = tcolor.greenF();
            skyColor[2] = tcolor.blueF();
        }
        if(setname =="defaultelevationbox"){
            DefaultElevationBox = setval.toInt();
        }
        if(setname =="defaultmovestep"){
            DefaultMoveStep = setval.toFloat();
        }
        if(setname =="hudenabled"){
            if((setval == "true") or (setval == "1") or (setval == "on"))
                hudEnabled = true;
            else
                hudEnabled = false; 
        }
        if(setname =="hudscale"){
            hudScale = setval.toFloat();
        }

        if(setname =="season"){
            season = setval;
        }
        if(setname =="markerlines"){
            if((setval == "true") or (setval == "1") or (setval == "on"))
                markerLines = true;
            else
                markerLines = false; 
        }
        if(setname =="seasonalediting"){
            if((setval == "true") or (setval == "1") or (setval == "on"))
                seasonalEditing = true;
            else
                seasonalEditing = false; 
        }

        
        if(setname =="maxautoplacement") {
            maxAutoPlacement = setval.toInt();
        }

        if(setname =="lockcamera") {
             if((setval == "true") or (setval == "1") or (setval == "on"))
                 lockCamera = true;
            else
                 lockCamera = false;
        }       

        if(setname =="newsymbols") {
             if((setval == "true") or (setval == "1") or (setval == "on"))
             {
                 newSymbols = true;
                 pointerIn = 4;
                 pointerOut = 3;
                 pyramid = 5;
                 qDebug() << "Symbol = true";
             }
            else
             {   
                 newSymbols = false;
                 pointerIn = 2;
                 pointerOut = 2;
                 pyramid = 0;
                 qDebug() << "Symbol = false";
             }
        }       
        if(setname =="railprofile")
        {             
                QStringList railList = setval.split(",");
                railProfile[0] = railList[0].toDouble();
                railProfile[1] = railList[1].toDouble();
        }
        
        if(setname =="useimperial"){
                convertHeight = 3.28084;
                convertUnit = "ft";

        }

        if(setname == "viewcompass"){
             if((setval == "true") or (setval == "1") or (setval == "on"))
                 viewCompass = true;
            else
                 viewCompass = false;
        }       

        if(setname == "viewmarkers"){
             if((setval == "true") or (setval == "1") or (setval == "on"))
                 viewMarkers = true;
            else
                 viewMarkers = false;
        }       

        if(setname =="mapapikey"){
                MapAPIKey = args[1].trimmed();
                
        }

        if(setname == "imagesubstitution"){
             if((setval == "true") or (setval == "1") or (setval == "on"))
                 imageSubstitution = true;
            else
                 imageSubstitution = false;
        }       
        
        if(setname == "imageupgrade"){
             if((setval == "true") or (setval == "1") or (setval == "on"))
                 imageUpgrade = true;
            else
                 imageUpgrade = false;
        }       
        
        
        
        
        
        
        if(Game::debugOutput) qDebug() << "Skip: " << skipped;
        skipped.clear();               
    }
    
    qDebug() <<  Game::AppVersion ;
    
    

}
/*
bool Game::loadRouteEditor(){
    
    window = new RouteEditorWindow();
    if(Game::fullscreen){
        window->setWindowFlags(Qt::CustomizeWindowHint);
        window->setWindowState(Qt::WindowMaximized);
    } else {
        window->resize(1280, 800);
    }
    
    loadWindow = new LoadWindow();
    QObject::connect(window, SIGNAL(exitNow()),
                      loadWindow, SLOT(exitNow()));
    
    QObject::connect(loadWindow, SIGNAL(showMainWindow()),
                      window, SLOT(show()));
    
    if(Game::checkRoot(Game::root) && (Game::checkRoute(Game::route) || Game::createNewRoutes)){
        Game::window->show();
    } else {
        Game::loadWindow->show();
    }
}

bool Game::loadConEditor(){
    //if(Game::warningBox){
    //    QMessageBox msgBox;
    //    msgBox.setText("This is experimental version.\nUsing it may seriously damage your consists."
    //                   "\nMake backup first!\n\nTo disable this window, set 'warningBox = false' in settings.txt.");
    //    msgBox.setIcon(QMessageBox::Warning);
    //    msgBox.exec();
    //}
    CELoadWindow* ceLoadWindow = new CELoadWindow();
    ceLoadWindow->show();
    //ConEditorWindow* cwindow = new ConEditorWindow();
    //cwindow->resize(1280, 720);
    //cwindow->show();
}
*/
bool Game::checkRoot(QString dir){
    QString path;
    path = dir + "/routes";
    path.replace("//", "/");
    QFile file(path);
    if (!file.exists()) {
        qDebug () << "/routes not exist: "<< dir <<  file.fileName();
        return false;
    }
    path = dir + "/global";
    path.replace("//", "/");
    file.setFileName(path);
    if (!file.exists()) {
        qDebug () << "/global not exist: "<< file.fileName();
        return false;
    }
    path = dir + "/global/tsection.dat";
    path.replace("//", "/");
    file.setFileName(path);
    if (!file.exists()) {
        qDebug () << "/global/tsection.dat not exist: "<< file.fileName();
        return false;
    }
    
    return true;
}

bool Game::checkCERoot(QString dir){
    QString path;
    path = dir + "/trains";
    path.replace("//", "/");
    QFile file(path);
    if (!file.exists()) {
        qDebug () << "/trains not exist: "<< file.fileName();
        return false;
    }
    path = dir + "/trains/trainset";
    path.replace("//", "/");
    file.setFileName(path);
    if (!file.exists()) {
        qDebug () << "/trains/trainset not exist: " << file.fileName();
        return false;
    }
    path = dir + "/trains/consists";
    path.replace("//", "/");
    file.setFileName(path);
    if (!file.exists()) {
        qDebug () << "/trains/consists not exist: " << file.fileName();
        return false;
    }
    
    return true;
}

bool Game::checkRoute(QString dir){
    QFile file;
    file.setFileName(Game::root+"/routes/"+dir+"/"+dir+".trk");
    if(file.exists()){
        Game::trkName = dir;
        return true;
    }
    QDir folder(Game::root+"/routes/"+dir+"/");
    folder.setNameFilters(QStringList() << "*.trk");
    folder.setFilter(QDir::Files);
    foreach(QString dirFile, folder.entryList()){
        Game::trkName = dirFile.split(".")[0];
        //qDebug() << Game::trkName;
        return true;
    }
    
    //qDebug() << file.fileName();
    //qDebug() << file.exists();
    return false;
}

bool Game::checkRemoteRoute(QString dir){
    QFile file;
    file.setFileName(Game::root+"/routes/"+dir);
    if(file.exists()){
        //Game::trkName = dir;
        return true;
    }
    return false;
}

template<class T>
void Game::check_coords(T&& x, T&& z, float* p) {
    if (p[0] >= 1024) {
        p[0] -= 2048;
        x++;
    }
    if (p[0] < -1024) {
        p[0] += 2048;
        x--;
    }
    if (p[2] >= 1024) {
        p[2] -= 2048;
        z++;
    }
    if (p[2] < -1024) {
        p[2] += 2048;
        z--;
    }
}
template void Game::check_coords(int& x, int& z, float* p);
template void Game::check_coords(float& x, float& z, float* p);

template<class T, class K>
void Game::check_coords(T&& x, T&& z, K&& px, K&& pz) {
    if (px >= 1024) {
        px -= 2048;
        x++;
    }
    if (px < -1024) {
        px += 2048;
        x--;
    }
    if (pz >= 1024) {
        pz -= 2048;
        z++;
    }
    if (pz < -1024) {
        pz += 2048;
        z--;
    }
}
template void Game::check_coords(int& x, int& z, int& px, int& pz);
template void Game::check_coords(int& x, int& z, float& px, float& pz);
template void Game::check_coords(float& x, float& z, float& px, float& pz);

void Game::CreateNewSettingsFile(){
    QFile file;
    QTextStream out;
    QString filepath;

    filepath = "./settings.txt";
    file.setFileName(filepath);
    //qDebug() << filepath;
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    out.setDevice(&file);
    out << "consoleOutput = false\n";
    out << "\n";
    out << "# main directory of your game data\n";
    out << "gameRoot = F:/train simulator\n";
    out << "\n";
    out << "# route directory name to load on startup by default\n";
    out << "routeName = asdasasdasd1233\n";
    out << "\n";
    out << "# optional start tile\n";
    out << "#startTileX = -5306\n";
    out << "#startTileY = 14961\n";
    out << "\n";
    out << "# route edit\n";
    out << "#createNewIfNotExist = true\n";
    out << "writeEnabled = true\n";
    out << "writeTDB = true\n";
    out << "#deleteTrWatermarks = true\n";
    out << "#deleteViewDbSpheres = true\n";
    out << "\n";
    out << "# geo data\n";
    out << "geoPath = F:/hgst\n";
    out << "\n";
    out << "# misc\n";
    out << "#systemTheme = true\n";
    out << "#colorConView = #FF0000\n";
    out << "#colorShapeView = #00FF00\n";
    out << "#toolsHidden = true\n";
    out << "usenNumPad = true\n";
    out << "tileLod = 1\n";
    out << "objectLod = 4000\n";
    out << "maxObjLag = 10\n";
    out << "allowObjLag = 1000\n";
    out << "#cameraFov = 20.0\n";
    out << "leaveTrackShapeAfterDelete = false\n";
    out << "#renderTrItems = true\n";
    out << "#useImperial = false\n";
    out << "#ortsEngEnable = false\n";
    out << "#oglDefaultLineWidth = 2\n";
    out << "shadowsEnabled = 1\n";
    out << "#shadowMapSize = 8192\n";
    out << "#textureQuality = 4\n";
    out << "ignoreMissingGlobalShapes = true\n";
    out << "snapableOnlyRot = false\n";
    out << "#imageMapsUrl = \n";
    out << "#MapAPIKey = \n";
    out << "#AASamples = 16\n";
    out << "#mapImageResolution = 2048\n";
    out << "#cameraStickToTerrain = true\n";
    out << "#mouseSpeed = 0.1\n";
    out << "#mainWindowLayout = W\n";
    out << "#ceindowLayout = CU1\n";
    out << "#useQuadTree = false\n";
    out << "#fogColor = #D0D0FF\n";
    out << "#fogDensity = 0.5\n";
    out << "#defaultElevationBox = 0\n";
    out << "#defaultMoveStep = 0.25\n";
    out << "#ActivityToPlay = \"\"\n";
    out << "#autoFix = false\n";
    out << "#cameraSpeedMax = 40.0\n";
    out << "#cameraSpeedMin = 1.0\n";
    out << "#cameraSpeedStd = 3.0\n";
    out << "#debugOutput = false\n";
    out << "#fpsLimit=0\n";
    out << "#fullscreen = false\n";
    out << "#hudEnabled = false\n";
    out << "#hudScale = 1.0\n";
    out << "#ignoreLoadLimits = false\n";
    out << "#imageMapsZoomOffset = 0\n";
    out << "#legacySypport = false\n";
    out << "#loadAllWFiles = false\n";
    out << "#lockCamera = false\n";
    out << "#mainWindow = 200,200\n";
    out << "#naviWindow = 0,200\n";
    out << "#markerLines = false\n";
    out << "#maxAutoPlacement = 999\n";
    out << "#mstsShadows = false\n";
    out << "#newSymbols = true\n";
    out << "#numRecentItems=11\n";
    out << "#objectsToRemove=\"\"\n";
    out << "#playerMode=false\n";
    out << "#proceduralTracks=false\n";
    out << "#routeMergeString=\"\"\n";
    out << "#season=\"\"\n";
    out << "#seasonalEditing=false\n";
    out << "#sectionLineHeight=2.8\n";
    out << "#selectedTerrWidth=2\n";
    out << "#selectedColor=#BBBB00\n";
    out << "#selectedTerrColor=#FF2000\n";
    out << "#selectedWidth=2\n";
    out << "#serverAuth=\"\"\n";
    out << "#serverLogin=\"\"\n";
    out << "#shadoLowMapSize=1024\n";
    out << "#snapableRadius=20\n";
    out << "#sortTileObjects=true\n";
    out << "#soundEnabled=false\n";
    out << "#statusWindow=0,100\n";
    out << "#terrainTools = \"1,5,5,9,1,10\"\n";
    out << "#trackElevationPm=700\n";
    out << "#useNetworkingEng=false\n";
    out << "#useOnlyPositiveQuaternions=false\n";
    out << "#useSuperelevation=false\n";
    out << "#viewCompass = false\n";
    out << "wireLineHeight = 3\n";
    out << "#";
            
    out.flush();
    file.close();
}

void Game::CheckForOpenAl(){
    
    QString openalfilename;
    QString Url;
    
    QFile file("./"+openalfilename);
    if(file.exists())
        return;
    
#ifdef Q_PROCESSOR_X86_64
    openalfilename = "OpenAL32.dll";
    Url = "http://koniec.org/tsre5/data/openal/Win64/soft_oal.dll";
#endif

#ifdef Q_PROCESSOR_X86_32
    openalfilename = "openal32.dll";
    Url = "http://koniec.org/tsre5/data/openal/Win32/soft_oal.dll";
#endif
    
    QNetworkAccessManager* mgr = new QNetworkAccessManager();
    //connect(mgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(isData(QNetworkReply*)));
    qDebug() << "Wait ..";

    QNetworkRequest req;
    req.setUrl(QUrl(Url));
    qDebug() << req.url();
    QNetworkReply* r = mgr->get(req);
    QEventLoop loop;
    QObject::connect(r, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    qDebug() << "Network Reply Loop End";
    QByteArray data = r->readAll();

    file.open(QIODevice::WriteOnly);
    file.write(data);
    file.close();
}

void Game::DownloadAppData(QString path){
    QDir().mkdir(path);
    
    // Download and extract AppData
    QNetworkAccessManager* mgr = new QNetworkAccessManager();
    qDebug() << "Wait ..";
    QString Url = "http://koniec.org/tsre5/data/appdata/"+ Game::AppDataVersion + ".tar";
    qDebug() << Url;
    QNetworkRequest req;//(QUrl(Url));
    req.setUrl(QUrl(Url));
    qDebug() << req.url();
    QNetworkReply* r = mgr->get(req);
    QEventLoop loop;
    QObject::connect(r, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    
    qDebug() << "Network Reply Loop End";
    QByteArray data = r->readAll();
    FileBuffer *fileData = new FileBuffer((unsigned char*)data.data(), data.length());
    TarFile tarFile(fileData);
    tarFile.extractTo("./tsre_appdata/");
    
    // Create bat file for Consist Editor.
    QString conBatFile = QFileInfo(QCoreApplication::applicationFilePath()).fileName()+" --conedit";
    QFile file1("./ConsistEditor.bat");
    file1.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out;
    out.setDevice(&file1);
    out << conBatFile;
    out.flush();
    file1.close();
    
    // Create bat file for Shape Viewer.
    conBatFile = QFileInfo(QCoreApplication::applicationFilePath()).fileName()+" --shapeview";
    QFile file2("./ShapeViewer.bat");
    file2.open(QIODevice::WriteOnly | QIODevice::Text);
    out.setDevice(&file2);
    out << conBatFile;
    out.flush();
    file2.close();
}