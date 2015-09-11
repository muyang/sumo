EXTRA_DIST = netedit64.ico tlslogo.cpp

XERCES_LIBS = -l$(LIB_XERCES)

if WITH_GUI
GUI_APPS = netedit
endif

if CHECK_MEMORY_LEAKS
MEM_LIBS  = ../foreign/nvwa/libnvwa.a
endif

if TRACI
TRACI_LIBS = ../traci-server/libtraciserver.a
endif

bin_PROGRAMS = $(GUI_APPS)

if WITH_GUI
netedit_SOURCES = netedit_main.cpp \
GNEApplicationWindow.h GNEApplicationWindow.cpp \
GNELoadThread.h GNELoadThread.cpp \
GNENet.h GNENet.cpp \
GNEEdge.h GNEEdge.cpp \
GNELane.h GNELane.cpp \
GNEInternalLane.h GNEInternalLane.cpp \
GNEJunction.h GNEJunction.cpp \
GNEPOI.h GNEPOI.cpp \
GNEPoly.h GNEPoly.cpp \
GNEViewNet.h GNEViewNet.cpp \
GNEViewParent.h GNEViewParent.cpp \
GNEDialog_About.h GNEDialog_About.cpp \
GNEDialog_Wizard.h GNEDialog_Wizard.cpp \
GNEChange.h GNEChange.cpp \
GNEChange_Junction.h GNEChange_Junction.cpp \
GNEChange_Edge.h GNEChange_Edge.cpp \
GNEChange_Lane.h GNEChange_Lane.cpp \
GNEChange_Connection.h GNEChange_Connection.cpp \
GNEChange_Attribute.h GNEChange_Attribute.cpp \
GNEChange_TLS.h GNEChange_TLS.cpp \
GNEChange_Selection.h GNEChange_Selection.cpp \
GNEUndoList.h GNEUndoList.cpp \
GNEAttributeCarrier.h GNEAttributeCarrier.cpp \
GNEInspector.h GNEInspector.cpp \
GNESelector.h GNESelector.cpp \
GNEConnector.h GNEConnector.cpp \
GNETLSEditor.h GNETLSEditor.cpp \
GNEReferenceCounter.h \
GNEEvent_NetworkLoaded.h


netedit_LDADD = ../netimport/libnetimport.a \
../netimport/vissim/libvissimimport.a \
../netimport/vissim/typeloader/libvissimtypeload.a \
../netimport/vissim/tempstructs/libvissimtmpstr.a \
../netbuild/libnetbuild.a \
../netwrite/libnetwrite.a \
../utils/distribution/libdistribution.a \
../foreign/eulerspiral/libeulerspiral.a \
../utils/gui/windows/libguiutilsWindows.a \
../utils/gui/globjects/libguiutilsglobjects.a \
../utils/gui/div/libguiutilsdiv.a \
../utils/gui/settings/libguiutilssettings.a \
../utils/gui/images/libguiutilsimages.a \
../utils/gui/tracker/libguiutilstracker.a \
../utils/foxtools/libfoxtools.a \
../utils/distribution/libdistribution.a \
../foreign/gl2ps/libgl2ps.a \
../foreign/polyfonts/libpolyfonts.a \
../foreign/eulerspiral/libeulerspiral.a \
../utils/geom/libgeom.a \
../utils/shapes/libshapes.a \
../utils/options/liboptions.a \
../utils/common/libcommon.a \
../utils/emissions/libemissions.a \
../utils/xml/libxml.a \
../utils/importio/libimportio.a \
../utils/iodevices/libiodevices.a \
../foreign/tcpip/libtcpip.a \
$(MEM_LIBS) \
$(XERCES_LIBS) \
$(FOX_LDFLAGS) $(XERCES_LDFLAGS) $(PROJ_LDFLAGS) $(GDAL_LDFLAGS) $(X_LDFLAGS)
endif