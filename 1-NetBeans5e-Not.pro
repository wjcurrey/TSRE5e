
TEMPLATE = app
PKGCONFIG +=
QT += core gui widgets network opengl websockets

TARGET = TSRE5f


SOURCES += \
main.cpp \
AboutWindow.cpp \
AceLib.cpp \
ActLib.cpp \
ActionChooseDialog.cpp \
Activity.cpp \
ActivityEvent.cpp \
ActivityEventProperties.cpp \
ActivityEventWindow.cpp \
ActivityObject.cpp \
ActivityServiceProperties.cpp \
ActivityServiceWindow.cpp \
ActivityTimetable.cpp \
ActivityTimetableProperties.cpp \
ActivityTimetableWindow.cpp \
ActivityTools.cpp \
ActivityTrafficProperties.cpp \
ActivityTrafficWindow.cpp \
Brush.cpp CELoadWindow.cpp \
Camera.cpp \
CameraConsist.cpp \
CameraFree.cpp \
CameraRot.cpp \
CarSpawnerObj.cpp \
ChooseFileDialog.cpp \
ClickableLabel.cpp \
ClientInfo.cpp \
ClientUsersWindow.cpp \
ComplexLine.cpp \
ConEditorWindow.cpp \
ConInfoWidget.cpp \
ConLib.cpp \
ConListWidget.cpp \
ConUnitsWidget.cpp \
Consist.cpp \
ContentHierarchyInfo.cpp \
Coords.cpp CoordsGpx.cpp \
CoordsKml.cpp \
CoordsMkr.cpp \
CoordsRoutePlaces.cpp \
DynTrackObj.cpp \
EditFileNameDialog.cpp \
Eng.cpp \
EngInfoWidget.cpp \
EngLib.cpp \
EngListWidget.cpp \
Environment.cpp \
ErrorMessage.cpp \
ErrorMessageProperties.cpp \
ErrorMessagesLib.cpp \
ErrorMessagesWindow.cpp \
FileBuffer.cpp \
FileFunctions.cpp \
Flex.cpp \
ForestObj.cpp \
GLH.cpp \
GLMatrix.cpp \
GLUU.cpp \
Game.cpp \
GameObj.cpp \
GeoCoordinates.cpp \
GeoHgtFile.cpp \
GeoTerrainFile.cpp \
GeoTiffFile.cpp \
GeoTools.cpp \
GlobalDefinitions.cpp \
GroupObj.cpp \
GuiFunct.cpp \
GuiGlCompass.cpp \
HazardObj.cpp \
HeightWindow.cpp \
ImageLib.cpp \
Intersections.cpp \
LevelCrObj.cpp \
LoadWindow.cpp \
MapData.cpp \
MapDataOSM.cpp \
MapDataUrlImage.cpp \
MapLib.cpp \
MapWindow.cpp \
MstsSoundDefinition.cpp \
NaviBox.cpp \
NaviWindow.cpp \
NewRouteWindow.cpp \
OSMFeatures.cpp \
ObjFile.cpp \
ObjTools.cpp \
OglObj.cpp \
OpenGL3Renderer.cpp \
OrtsWeatherChange.cpp \
OverwriteDialog.cpp \
PaintTexLib.cpp \
ParserX.cpp \
Path.cpp \
PickupObj.cpp \
PlatformObj.cpp \
PlayActivitySelectWindow.cpp \
Pointer3d.cpp \
PoleObj.cpp \
PolyForestObj.cpp \
ProceduralMstsDyntrack.cpp \
ProceduralShape.cpp \
PropertiesAbstract.cpp \
PropertiesActivityObject.cpp \
PropertiesActivityPath.cpp \
PropertiesCarspawner.cpp \
PropertiesConsist.cpp \
PropertiesDyntrack.cpp \
PropertiesForest.cpp \
PropertiesGroup.cpp \
PropertiesHazard.cpp \
PropertiesLevelCr.cpp \
PropertiesPickup.cpp \
PropertiesPlatform.cpp \
PropertiesRuler.cpp \
PropertiesSiding.cpp \
PropertiesSignal.cpp \
PropertiesSoundRegion.cpp \
PropertiesSoundSource.cpp \
PropertiesSpeedpost.cpp \
PropertiesStatic.cpp \
PropertiesTerrain.cpp \
PropertiesTrackItem.cpp \
PropertiesTrackObj.cpp \
PropertiesTransfer.cpp \
PropertiesUndefined.cpp \
QuadTree.cpp \
RandomConsist.cpp \
RandomTransformWorldObjDialog.cpp \
ReadFile.cpp \
Ref.cpp \
RenderItem.cpp \
Renderer.cpp \
Route.cpp \
RouteClient.cpp \
RouteEditorClient.cpp \
RouteEditorGLWidget.cpp \
RouteEditorServer.cpp \
RouteEditorWindow.cpp \
RouteMergeDialog.cpp \
Ruch.cpp \
RulerObj.cpp \
SFile.cpp SFileC.cpp \
SFileX.cpp \
Service.cpp \
Shader.cpp \
ShapeHierarchyInfo.cpp \
ShapeHierarchyWindow.cpp \
ShapeInfoWidget.cpp \
ShapeLib.cpp \
ShapeTemplates.cpp \
ShapeTextureInfo.cpp \
ShapeTexturesWindow.cpp \
ShapeViewWindow.cpp \
ShapeViewerGLWidget.cpp \
ShapeViewerNavigatorWidget.cpp \
ShapeViewerWindow.cpp \
SigCfg.cpp \
SignalObj.cpp \
SignalShape.cpp \
SignalType.cpp \
SignalWindow.cpp \
SignalWindowLink.cpp \
SimpleHud.cpp \
Skydome.cpp \
SoundLib.cpp \
SoundList.cpp \
SoundManager.cpp \
SoundRegionObj.cpp \
SoundSource.cpp \
SoundSourceObj.cpp \
SoundVariables.cpp \
SpeedPost.cpp \
SpeedPostDAT.cpp \
SpeedpostObj.cpp \
StaticObj.cpp \
StatusWindow.cpp \
TDB.cpp \
TDBClient.cpp \
TFile.cpp \
TRitem.cpp \
TRnode.cpp \
TS.cpp \
TSection.cpp \
TSectionDAT.cpp \
TarFile.cpp \
Terrain.cpp \
TerrainClient.cpp \
TerrainInfo.cpp \
TerrainLib.cpp \
TerrainLibQt.cpp \
TerrainLibQtClient.cpp \
TerrainLibSimple.cpp \
TerrainTools.cpp \
TerrainTreeWindow.cpp \
TerrainWaterWindow.cpp \
TerrainWaterWindow2.cpp \
TexLib.cpp \
TextEditDialog.cpp \
TextObj.cpp \
Texture.cpp \
Tile.cpp \
TrWatermarkObj.cpp \
TrackItemObj.cpp \
TrackObj.cpp \
TrackShape.cpp \
Traffic.cpp \
TrainNetworkEng.cpp \
TransferObj.cpp \
TransformWorldObjDialog.cpp \
Trk.cpp TrkWindow.cpp \
Undo.cpp \
UnsafeModeDialog.cpp \
UnsavedDialog.cpp \
UriImageDrawThread.cpp \
Vector2f.cpp \
Vector2i.cpp \
Vector3f.cpp \
Vector4f.cpp \
WorldObj.cpp


HEADERS += \
AboutWindow.h \
AceLib.h \
ActLib.h \
ActionChooseDialog.h \
Activity.h ActivityEvent.h \
ActivityEventProperties.h \
ActivityEventWindow.h \
ActivityObject.h \
ActivityServiceProperties.h \
ActivityServiceWindow.h \
ActivityTimetable.h \
ActivityTimetableProperties.h \
ActivityTimetableWindow.h \
ActivityTools.h \
ActivityTrafficProperties.h \
ActivityTrafficWindow.h \
Brush.h \
CELoadWindow.h \
Camera.h \
CameraConsist.h \
CameraFree.h \
CameraRot.h \
CarSpawnerObj.h \
ChooseFileDialog.h \
ClickableLabel.h \
ClientInfo.h \
ClientUsersWindow.h \
ComplexLine.h \
ConEditorWindow.h \
ConInfoWidget.h \
ConLib.h \
ConListWidget.h \
ConUnitsWidget.h \
Consist.h \
ContentHierarchyInfo.h \
Coords.h \
CoordsGpx.h \
CoordsKml.h \
CoordsMkr.h \
CoordsRoutePlaces.h \
DynTrackObj.h \
EditFileNameDialog.h \
Eng.h \
EngInfoWidget.h \
EngLib.h \
EngListWidget.h \
Environment.h \
ErrorMessage.h \
ErrorMessageProperties.h \
ErrorMessagesLib.h \
ErrorMessagesWindow.h \
FileBuffer.h \
FileFunctions.h \
Flex.h \
ForestObj.h \
GLH.h \
GLMatrix.h \
GLUU.h \
Game.h \
GameObj.h \
GeoCoordinates.h \
GeoHgtFile.h \
GeoTerrainFile.h \
GeoTiffFile.h \
GeoTools.h \
GlobalDefinitions.h \
GroupObj.h \
GuiFunct.h \
GuiGlCompass.h \
HazardObj.h \
HeightWindow.h \
ImageLib.h \
Intersections.h \
LevelCrObj.h \
LoadWindow.h \
MapData.h \
MapDataOSM.h \
MapDataUrlImage.h \
MapLib.h \
MapWindow.h \
MstsSoundDefinition.h \
NaviBox.h \
NaviWindow.h \
NewRouteWindow.h \
OSMFeatures.h \
ObjFile.h \
ObjTools.h \
OglObj.h \
OpenGL3Renderer.h \
OrtsWeatherChange.h \
OverwriteDialog.h \
PaintTexLib.h \
ParserX.h \
Path.h \
PickupObj.h \
PlatformObj.h \
PlayActivitySelectWindow.h \
Pointer3d.h \
PoleObj.h \
PolyForestObj.h \
ProceduralMstsDyntrack.h \
ProceduralShape.h \
PropertiesAbstract.h \
PropertiesActivityObject.h \
PropertiesActivityPath.h \
PropertiesCarspawner.h \
PropertiesConsist.h \
PropertiesDyntrack.h \
PropertiesForest.h \
PropertiesGroup.h \
PropertiesHazard.h \
PropertiesLevelCr.h \
PropertiesPickup.h \
PropertiesPlatform.h \
PropertiesRuler.h \
PropertiesSiding.h \
PropertiesSignal.h \
PropertiesSoundRegion.h \
PropertiesSoundSource.h \
PropertiesSpeedpost.h \
PropertiesStatic.h \
PropertiesTerrain.h \
PropertiesTrackItem.h \
PropertiesTrackObj.h \
PropertiesTransfer.h \
PropertiesUndefined.h \
QuadTree.h \
RandomConsist.h \
RandomTransformWorldObjDialog.h \
ReadFile.h \
Ref.h \
RenderItem.h \
Renderer.h \
Route.h \
RouteClient.h \
RouteEditorClient.h \
RouteEditorGLWidget.h \
RouteEditorServer.h \
RouteEditorWindow.h \
RouteMergeDialog.h \
Ruch.h \
RulerObj.h \
SFile.h \
SFileC.h \
SFileX.h \
Service.h \
Shader.h \
ShapeHierarchyInfo.h \
ShapeHierarchyWindow.h \
ShapeInfoWidget.h \
ShapeLib.h \
ShapeTemplates.h \
ShapeTextureInfo.h \
ShapeTexturesWindow.h \
ShapeViewWindow.h \
ShapeViewerGLWidget.h \
ShapeViewerNavigatorWidget.h \
ShapeViewerWindow.h \
SigCfg.h \
SignalObj.h \
SignalShape.h \
SignalType.h \
SignalWindow.h \
SignalWindowLink.h \
SimpleHud.h \
Skydome.h \
SoundLib.h \
SoundList.h \
SoundManager.h \
SoundRegionObj.h \
SoundSource.h \
SoundSourceObj.h \
SoundVariables.h \
SpeedPost.h \
SpeedPostDAT.h \
SpeedpostObj.h \
StaticObj.h \
StatusWindow.h \
TDB.h \
TDBClient.h \
TFile.h \
TRitem.h \
TRnode.h \
TS.h \
TSection.h \
TSectionDAT.h \
TarFile.h \
Terrain.h \
TerrainClient.h \
TerrainInfo.h \
TerrainLib.h \
TerrainLibQt.h \
TerrainLibSimple.h \
TerrainTools.h \
TerrainTreeWindow.h \
TerrainWaterWindow.h \
TerrainWaterWindow2.h \
TexLib.h TextEditDialog.h \
TextObj.h \
Texture.h \
Tile.h \
TrWatermarkObj.h \
TrackItemObj.h \
TrackObj.h \
TrackShape.h \
Traffic.h \
TrainNetworkEng.h \
TransferObj.h \
TransformWorldObjDialog.h \
Trk.h \
TrkWindow.h \
Undo.h \
UnsafeModeDialog.h \
UnsavedDialog.h \
UriImageDrawThread.h \
Vector2f.h \
Vector2i.h \
Vector3f.h \
Vector4f.h \
WorldObj.h


FORMS +=
RESOURCES +=
TRANSLATIONS +=
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
DEFINES += 

LIBS += -lopengl32

INCLUDEPATH += C:\openal-soft-1.18.2-bin\include
LIBS += C:\openal-soft-1.18.2-bin\libs\Win64\libOpenAL32.dll.a

# Generate 64 bit release file. Switch to release on clean build
# Other wise there will be a large *.exe. Which may not be uploaded to Github
win32 {
DESTDIR = $$PWD/Dest
QMAKE_POST_LINK =  windeployqt $$shell_path($$DESTDIR/$${TARGET}.exe)
}






