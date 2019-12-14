# Microsoft Developer Studio Project File - Name="VL1" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=VL1 - Win32 Debug Cubase
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VL1.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VL1.mak" CFG="VL1 - Win32 Debug Cubase"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VL1 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "VL1 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "VL1 - Win32 Debug Cubase" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/VL1", BAAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "VL1 - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release\Obj"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 Comdlg32.lib Shell32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386

!ELSEIF  "$(CFG)" == "VL1 - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug\Obj"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Comdlg32.lib Shell32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# Begin Special Build Tool
TargetPath=.\Debug\VL1.dll
SOURCE="$(InputPath)"
PostBuild_Cmds=Echo On	copy $(TargetPath) "c:\Program Files\Steinberg\Cubase SX\Vstplugins\"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "VL1 - Win32 Debug Cubase"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "VL1___Win32_Debug_Cubase"
# PROP BASE Intermediate_Dir "VL1___Win32_Debug_Cubase"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug\Obj"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FR /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 Comdlg32.lib Shell32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Comdlg32.lib Shell32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# Begin Special Build Tool
TargetPath=.\Debug\VL1.dll
SOURCE="$(InputPath)"
PostBuild_Cmds=Echo On	copy $(TargetPath) "c:\Program Files\Steinberg\Cubase SX\Vstplugins\"
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "VL1 - Win32 Release"
# Name "VL1 - Win32 Debug"
# Name "VL1 - Win32 Debug Cubase"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ADSR.cpp
# End Source File
# Begin Source File

SOURCE=.\aeffguieditor.cpp
# End Source File
# Begin Source File

SOURCE=.\AudioEffect.cpp
# End Source File
# Begin Source File

SOURCE=.\audioeffectx.cpp
# End Source File
# Begin Source File

SOURCE=.\calculator.cpp
# End Source File
# Begin Source File

SOURCE=.\Clock.cpp
# End Source File
# Begin Source File

SOURCE=.\EnvelopeShaper.cpp
# End Source File
# Begin Source File

SOURCE=.\EventManager.cpp
# End Source File
# Begin Source File

SOURCE=.\FFTReal.cpp
# End Source File
# Begin Source File

SOURCE=.\Filters.cpp
# End Source File
# Begin Source File

SOURCE=.\GlobalData.cpp
# End Source File
# Begin Source File

SOURCE=.\Lcd.cpp
# End Source File
# Begin Source File

SOURCE=.\LFO.cpp
# End Source File
# Begin Source File

SOURCE=.\LineInTime.cpp
# End Source File
# Begin Source File

SOURCE=.\Noise.cpp
# End Source File
# Begin Source File

SOURCE=.\Rhythm.cpp
# End Source File
# Begin Source File

SOURCE=.\Sequencer.cpp
# End Source File
# Begin Source File

SOURCE=.\Utils.cpp
# End Source File
# Begin Source File

SOURCE=.\VL1.cpp
# End Source File
# Begin Source File

SOURCE=.\VL1defs.cpp
# End Source File
# Begin Source File

SOURCE=.\VL1Edit.cpp
# End Source File
# Begin Source File

SOURCE=.\VL1EditMain.cpp
# End Source File
# Begin Source File

SOURCE=.\VL1Editor.cpp
# End Source File
# Begin Source File

SOURCE=.\Vl1String.cpp
# End Source File
# Begin Source File

SOURCE=.\Voice.cpp
# End Source File
# Begin Source File

SOURCE=.\VoiceManager.cpp
# End Source File
# Begin Source File

SOURCE=.\vstcontrols.cpp
# End Source File
# Begin Source File

SOURCE=.\vstgui.cpp
# End Source File
# Begin Source File

SOURCE=.\Wave.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ADSR.h
# End Source File
# Begin Source File

SOURCE=.\AEffect.h
# End Source File
# Begin Source File

SOURCE=.\aeffectx.h
# End Source File
# Begin Source File

SOURCE=.\AEffEditor.hpp
# End Source File
# Begin Source File

SOURCE=.\aeffguieditor.h
# End Source File
# Begin Source File

SOURCE=.\AudioEffect.hpp
# End Source File
# Begin Source File

SOURCE=.\audioeffectx.h
# End Source File
# Begin Source File

SOURCE=.\calculator.h
# End Source File
# Begin Source File

SOURCE=.\Clock.h
# End Source File
# Begin Source File

SOURCE=.\CriticalSection.h
# End Source File
# Begin Source File

SOURCE=.\DemoSong.h
# End Source File
# Begin Source File

SOURCE=.\EnvelopeShaper.h
# End Source File
# Begin Source File

SOURCE=.\EventManager.h
# End Source File
# Begin Source File

SOURCE=.\FFTReal.h
# End Source File
# Begin Source File

SOURCE=.\Filters.h
# End Source File
# Begin Source File

SOURCE=.\GlobalData.h
# End Source File
# Begin Source File

SOURCE=.\Lcd.h
# End Source File
# Begin Source File

SOURCE=.\LFO.h
# End Source File
# Begin Source File

SOURCE=.\LineInTime.h
# End Source File
# Begin Source File

SOURCE=.\MidiDefs.h
# End Source File
# Begin Source File

SOURCE=.\Noise.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\Rhythm.h
# End Source File
# Begin Source File

SOURCE=.\Sequencer.h
# End Source File
# Begin Source File

SOURCE=.\Utils.h
# End Source File
# Begin Source File

SOURCE=.\VL1.h
# End Source File
# Begin Source File

SOURCE=.\VL1defs.h
# End Source File
# Begin Source File

SOURCE=.\VL1Edit.h
# End Source File
# Begin Source File

SOURCE=.\VL1Editor.h
# End Source File
# Begin Source File

SOURCE=.\VL1Program.h
# End Source File
# Begin Source File

SOURCE=.\VL1String.h
# End Source File
# Begin Source File

SOURCE=.\Voice.h
# End Source File
# Begin Source File

SOURCE=.\VoiceManager.h
# End Source File
# Begin Source File

SOURCE=.\vstcontrols.h
# End Source File
# Begin Source File

SOURCE=.\vstgui.h
# End Source File
# Begin Source File

SOURCE=.\Wave.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\resources\add.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\autoplay.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\balanceBody.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\balanceHandle.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\casio_vl1_big.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\chars.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\del.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\div.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\dot.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\down.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\e.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\k.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\key0.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\key1.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\key2.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\key3.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\key4.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\key5.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\key6.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\key7.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\key8.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\key9.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\keyA0s.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\keyA1s.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\keyA2s.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\keyAdd.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\keyC1s.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\keyC2s.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\keyD1s.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\keyD2s.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\keyDiv.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\keyDot.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\keyEqual.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\keyF1s.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\keyF2s.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\keyG0s.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\keyG1s.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\keyG2s.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\keyMul.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\keyPlusMin.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\keySub.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\m.bmp
# End Source File
# Begin Source File

SOURCE=".\resources\ml-c.bmp"
# End Source File
# Begin Source File

SOURCE=.\resources\mode.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\mul.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\music.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\octave.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\one_key_play_dot.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\one_key_play_dot_dot.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\progsel2.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\reset.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\rhythm.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\sharp1.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\sharp2.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\sharp3.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\sub.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\up.bmp
# End Source File
# Begin Source File

SOURCE=.\VL1EditGUI.rc
# End Source File
# Begin Source File

SOURCE=.\resources\volumeBody.bmp
# End Source File
# Begin Source File

SOURCE=.\resources\volumeHandle.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ToDo.txt
# End Source File
# Begin Source File

SOURCE=.\VL1editgui.def
# End Source File
# End Target
# End Project
