# Microsoft Developer Studio Project File - Name="guisim" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=guisim - Win32 Debug
!MESSAGE Dies ist kein g�ltiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und f�hren Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "guisim.mak".
!MESSAGE 
!MESSAGE Sie k�nnen beim Ausf�hren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "guisim.mak" CFG="guisim - Win32 Debug"
!MESSAGE 
!MESSAGE F�r die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "guisim - Win32 Release" (basierend auf  "Win32 (x86) Console Application")
!MESSAGE "guisim - Win32 Debug" (basierend auf  "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "guisim - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "$(NEWFOX)\include" /I "$(XERCES)\include" /I "$(XERCES)\include\xercesc" /I "..\..\..\src" /D "NDEBUG" /D "FOXDLL" /D "_CONSOLE" /D "WIN32" /D "_MBCS" /D "HAVE_MESOSIM" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 opengl32.lib $(XERCES)\lib\xerces-c_2.lib $(NEWFOX)\lib\FOXDLL-1.4.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /machine:I386
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=mkdir ..\..\..\bin	copy Release\guisim.exe ..\..\..\bin\guisim.exe	..\..\add-ins\incBuildNumber.pl guisim
# End Special Build Tool

!ELSEIF  "$(CFG)" == "guisim - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "$(NEWFOX)\include" /I "$(XERCES)\include" /I "$(XERCES)\include\xercesc" /I "..\..\..\src" /D "_DEBUG" /D "ABS_DEBUG" /D "FOXDLL" /D "_CONSOLE" /D "WIN32" /D "_MBCS" /D "HAVE_MESOSIM" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 opengl32.lib $(XERCES)\lib\xerces-c_2D.lib $(NEWFOX)\lib\FOXDLLD-1.4.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /nodefaultlib:"nafxcwd.lib" /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=mkdir ..\..\..\bin	copy Debug\guisim.exe ..\..\..\bin\guisimD.exe
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "guisim - Win32 Release"
# Name "guisim - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\src\guisim.rc
# End Source File
# Begin Source File

SOURCE=..\..\..\src\guisim_main.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\helpers\PreStartInitialised.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\helpers\SimpleCommand.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\sumo_version.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\sumo_only\SUMOFrame.cpp
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\src\helpers\Command.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\helpers\Counter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\helpers\Dictionary.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\helpers\gcc_NullType.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\helpers\gcc_Typelist.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\helpers\gcc_TypeManip.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\helpers\gcc_TypeTraits.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\guisim_build.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\guisim_help.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\utils\common\HelpPrinter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\microsim\MSExtendedTrafficLightLogic.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\helpers\msvc6_NullType.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\helpers\msvc6_static_check.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\helpers\msvc6_Typelist.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\helpers\msvc6_TypeManip.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\helpers\msvc6_TypeTraits.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\helpers\OneArgumentCommand.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\helpers\PreStartInitialised.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\helpers\SimpleCommand.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\helpers\SingletonDictionary.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\sumo_version.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\sumo_only\SUMOFrame.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\helpers\ValueRetriever.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\helpers\ValueSource.h
# End Source File
# End Group
# Begin Group "Ressourcendateien"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
