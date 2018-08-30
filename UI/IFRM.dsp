# Microsoft Developer Studio Project File - Name="IFRM" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=IFRM - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "IFRM.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "IFRM.mak" CFG="IFRM - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "IFRM - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "IFRM - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "IFRM - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "IFRM - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 TAPI32.LIB PCI-Dask.LIB mpr.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "IFRM - Win32 Release"
# Name "IFRM - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\_rdocolumn.cpp
# End Source File
# Begin Source File

SOURCE=.\_rdoconnection.cpp
# End Source File
# Begin Source File

SOURCE=.\_rdoengine.cpp
# End Source File
# Begin Source File

SOURCE=.\_rdoenvironment.cpp
# End Source File
# Begin Source File

SOURCE=.\_rdoresultset.cpp
# End Source File
# Begin Source File

SOURCE=.\Ametter.cpp
# End Source File
# Begin Source File

SOURCE=.\AmetterRecordset.cpp
# End Source File
# Begin Source File

SOURCE=.\AMMETERRANGER.cpp
# End Source File
# Begin Source File

SOURCE=.\AngleSet.cpp
# End Source File
# Begin Source File

SOURCE=.\AutoDateReadModule.cpp
# End Source File
# Begin Source File

SOURCE=.\AutoFont.cpp
# End Source File
# Begin Source File

SOURCE=.\BreadSetting.cpp
# End Source File
# Begin Source File

SOURCE=.\BTNST.CPP
# End Source File
# Begin Source File

SOURCE=.\CHANGEAMMETER.cpp
# End Source File
# Begin Source File

SOURCE=.\CHANGEAMMETERDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildStation.cpp
# End Source File
# Begin Source File

SOURCE=.\CntrItem.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorButton.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorStatic.cpp
# End Source File
# Begin Source File

SOURCE=.\Condtions.cpp
# End Source File
# Begin Source File

SOURCE=.\Credits.cpp
# End Source File
# Begin Source File

SOURCE=.\DataBaseSet.cpp
# End Source File
# Begin Source File

SOURCE=.\DataInfoRecordSet.cpp
# End Source File
# Begin Source File

SOURCE=.\DataInformation.cpp
# End Source File
# Begin Source File

SOURCE=.\DataInto.cpp
# End Source File
# Begin Source File

SOURCE=.\DIBAPI.CPP
# End Source File
# Begin Source File

SOURCE=.\DIBSectionLite.cpp
# End Source File
# Begin Source File

SOURCE=.\ELECTDEAL.cpp
# End Source File
# Begin Source File

SOURCE=.\ELKind.cpp
# End Source File
# Begin Source File

SOURCE=.\EveryTimes.cpp
# End Source File
# Begin Source File

SOURCE=.\Expandingdialog.cpp
# End Source File
# Begin Source File

SOURCE=.\FENGBEISET.cpp
# End Source File
# Begin Source File

SOURCE=.\font.cpp
# End Source File
# Begin Source File

SOURCE=.\FTPGetData.cpp
# End Source File
# Begin Source File

SOURCE=.\Garrison.cpp
# End Source File
# Begin Source File

SOURCE=.\GarrisonRecordSet.cpp
# End Source File
# Begin Source File

SOURCE=.\GridCell.cpp
# End Source File
# Begin Source File

SOURCE=.\GridCellBase.cpp
# End Source File
# Begin Source File

SOURCE=.\GridCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\GridDropTarget.cpp
# End Source File
# Begin Source File

SOURCE=.\HoverEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\HyperLink.cpp
# End Source File
# Begin Source File

SOURCE=.\IFRM.cpp
# End Source File
# Begin Source File

SOURCE=.\hlp\IFRM.hpj

!IF  "$(CFG)" == "IFRM - Win32 Release"

# PROP Ignore_Default_Tool 1
USERDEP__IFRM_="hlp\AfxCore.rtf"	"hlp\AfxPrint.rtf"	"hlp\$(TargetName).hm"	
# Begin Custom Build - Making help file...
OutDir=.\Release
TargetName=IFRM
InputPath=.\hlp\IFRM.hpj
InputName=IFRM

"$(OutDir)\$(InputName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	start /wait hcw /C /E /M "hlp\$(InputName).hpj" 
	if errorlevel 1 goto :Error 
	if not exist "hlp\$(InputName).hlp" goto :Error 
	copy "hlp\$(InputName).hlp" $(OutDir) 
	goto :done 
	:Error 
	echo hlp\$(InputName).hpj(1) : error: 
	type "hlp\$(InputName).log" 
	:done 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "IFRM - Win32 Debug"

# PROP Ignore_Default_Tool 1
USERDEP__IFRM_="hlp\AfxCore.rtf"	"hlp\AfxPrint.rtf"	"hlp\$(TargetName).hm"	
# Begin Custom Build - Making help file...
OutDir=.\Debug
TargetName=IFRM
InputPath=.\hlp\IFRM.hpj
InputName=IFRM

"$(OutDir)\$(InputName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	start /wait hcw /C /E /M "hlp\$(InputName).hpj" 
	if errorlevel 1 goto :Error 
	if not exist "hlp\$(InputName).hlp" goto :Error 
	copy "hlp\$(InputName).hlp" $(OutDir) 
	goto :done 
	:Error 
	echo hlp\$(InputName).hpj(1) : error: 
	type "hlp\$(InputName).log" 
	:done 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\IFRM.odl
# End Source File
# Begin Source File

SOURCE=.\IFRM.rc
# End Source File
# Begin Source File

SOURCE=.\IFRMDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\IFRMView.cpp
# End Source File
# Begin Source File

SOURCE=.\InitDialogBar.cpp
# End Source File
# Begin Source File

SOURCE=.\InPlaceEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\IpFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\Label.cpp
# End Source File
# Begin Source File

SOURCE=.\LineLoss.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Message.cpp
# End Source File
# Begin Source File

SOURCE=.\mschart.cpp
# End Source File
# Begin Source File

SOURCE=.\mscomm.cpp
# End Source File
# Begin Source File

SOURCE=.\msdgridctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\mswinsockcontrol.cpp
# End Source File
# Begin Source File

SOURCE=.\MutiTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\MyDialogBar.cpp
# End Source File
# Begin Source File

SOURCE=.\MyDialogDataBar.cpp
# End Source File
# Begin Source File

SOURCE=.\MyListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\OWEMONEY.cpp
# End Source File
# Begin Source File

SOURCE=.\Parameter.cpp
# End Source File
# Begin Source File

SOURCE=.\PassWord.cpp
# End Source File
# Begin Source File

SOURCE=.\PhaseTest.cpp
# End Source File
# Begin Source File

SOURCE=.\Phone.cpp
# End Source File
# Begin Source File

SOURCE=.\picture.cpp
# End Source File
# Begin Source File

SOURCE=.\PictureEx.cpp
# End Source File
# Begin Source File

SOURCE=.\PriceSet.cpp
# End Source File
# Begin Source File

SOURCE=.\ProgDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Protcoldlg.cpp
# End Source File
# Begin Source File

SOURCE=.\rdc.cpp
# End Source File
# Begin Source File

SOURCE=.\rdocolumns.cpp
# End Source File
# Begin Source File

SOURCE=.\rdoconnections.cpp
# End Source File
# Begin Source File

SOURCE=.\rdoenvironments.cpp
# End Source File
# Begin Source File

SOURCE=.\rdoerror.cpp
# End Source File
# Begin Source File

SOURCE=.\rdoerrors.cpp
# End Source File
# Begin Source File

SOURCE=.\rdoparameter.cpp
# End Source File
# Begin Source File

SOURCE=.\rdoparameters.cpp
# End Source File
# Begin Source File

SOURCE=.\rdopreparedstatement.cpp
# End Source File
# Begin Source File

SOURCE=.\rdopreparedstatements.cpp
# End Source File
# Begin Source File

SOURCE=.\rdoqueries.cpp
# End Source File
# Begin Source File

SOURCE=.\rdoresultsets.cpp
# End Source File
# Begin Source File

SOURCE=.\rdotable.cpp
# End Source File
# Begin Source File

SOURCE=.\rdotables.cpp
# End Source File
# Begin Source File

SOURCE=.\ReadNoValueDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\READRANGLE.cpp
# End Source File
# Begin Source File

SOURCE=.\Registry.cpp
# End Source File
# Begin Source File

SOURCE=.\ReplaceData.cpp
# End Source File
# Begin Source File

SOURCE=.\Search.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectTable.cpp
# End Source File
# Begin Source File

SOURCE=.\ShowData.cpp
# End Source File
# Begin Source File

SOURCE=.\ShowInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\SrvrItem.cpp
# End Source File
# Begin Source File

SOURCE=.\sstabctl.cpp
# End Source File
# Begin Source File

SOURCE=.\StationCommun.cpp
# End Source File
# Begin Source File

SOURCE=.\StatusbarAnimate.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TAPILine.cpp
# End Source File
# Begin Source File

SOURCE=.\TestComm.cpp
# End Source File
# Begin Source File

SOURCE=.\TimeCheck.cpp
# End Source File
# Begin Source File

SOURCE=.\TimeSelect.cpp
# End Source File
# Begin Source File

SOURCE=.\TitleTip.cpp
# End Source File
# Begin Source File

SOURCE=.\Transformer.cpp
# End Source File
# Begin Source File

SOURCE=.\TRansformerdisppear.cpp
# End Source File
# Begin Source File

SOURCE=.\TransformRecordset.cpp
# End Source File
# Begin Source File

SOURCE=.\UseInfoRecordSet.cpp
# End Source File
# Begin Source File

SOURCE=.\UserInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\vcaxis.cpp
# End Source File
# Begin Source File

SOURCE=.\vcaxisgrid.cpp
# End Source File
# Begin Source File

SOURCE=.\vcaxisscale.cpp
# End Source File
# Begin Source File

SOURCE=.\vcaxistitle.cpp
# End Source File
# Begin Source File

SOURCE=.\vcbackdrop.cpp
# End Source File
# Begin Source File

SOURCE=.\vcbrush.cpp
# End Source File
# Begin Source File

SOURCE=.\vccategoryscale.cpp
# End Source File
# Begin Source File

SOURCE=.\vccolor.cpp
# End Source File
# Begin Source File

SOURCE=.\vccoor.cpp
# End Source File
# Begin Source File

SOURCE=.\vcdatagrid.cpp
# End Source File
# Begin Source File

SOURCE=.\vcdatapoint.cpp
# End Source File
# Begin Source File

SOURCE=.\vcdatapointlabel.cpp
# End Source File
# Begin Source File

SOURCE=.\vcdatapoints.cpp
# End Source File
# Begin Source File

SOURCE=.\vcfill.cpp
# End Source File
# Begin Source File

SOURCE=.\vcfont.cpp
# End Source File
# Begin Source File

SOURCE=.\vcfootnote.cpp
# End Source File
# Begin Source File

SOURCE=.\vcframe.cpp
# End Source File
# Begin Source File

SOURCE=.\vcintersection.cpp
# End Source File
# Begin Source File

SOURCE=.\vclabel.cpp
# End Source File
# Begin Source File

SOURCE=.\vclabels.cpp
# End Source File
# Begin Source File

SOURCE=.\vclcoor.cpp
# End Source File
# Begin Source File

SOURCE=.\vclegend.cpp
# End Source File
# Begin Source File

SOURCE=.\vclight.cpp
# End Source File
# Begin Source File

SOURCE=.\vclightsource.cpp
# End Source File
# Begin Source File

SOURCE=.\vclightsources.cpp
# End Source File
# Begin Source File

SOURCE=.\vclocation.cpp
# End Source File
# Begin Source File

SOURCE=.\vcmarker.cpp
# End Source File
# Begin Source File

SOURCE=.\vcpen.cpp
# End Source File
# Begin Source File

SOURCE=.\vcplot.cpp
# End Source File
# Begin Source File

SOURCE=.\vcplotbase.cpp
# End Source File
# Begin Source File

SOURCE=.\vcrect.cpp
# End Source File
# Begin Source File

SOURCE=.\vcseries.cpp
# End Source File
# Begin Source File

SOURCE=.\vcseriescollection.cpp
# End Source File
# Begin Source File

SOURCE=.\vcseriesmarker.cpp
# End Source File
# Begin Source File

SOURCE=.\vcseriesposition.cpp
# End Source File
# Begin Source File

SOURCE=.\vcshadow.cpp
# End Source File
# Begin Source File

SOURCE=.\vcstatline.cpp
# End Source File
# Begin Source File

SOURCE=.\vctextlayout.cpp
# End Source File
# Begin Source File

SOURCE=.\vctick.cpp
# End Source File
# Begin Source File

SOURCE=.\vctitle.cpp
# End Source File
# Begin Source File

SOURCE=.\vcvaluescale.cpp
# End Source File
# Begin Source File

SOURCE=.\vcview3d.cpp
# End Source File
# Begin Source File

SOURCE=.\vcwall.cpp
# End Source File
# Begin Source File

SOURCE=.\vcweighting.cpp
# End Source File
# Begin Source File

SOURCE=.\WuGongDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\WuGongSpace.cpp
# End Source File
# Begin Source File

SOURCE=.\XPButton.cpp
# End Source File
# Begin Source File

SOURCE=.\ZHULIUTIMESELECT.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\_rdocolumn.h
# End Source File
# Begin Source File

SOURCE=.\_rdoconnection.h
# End Source File
# Begin Source File

SOURCE=.\_rdoengine.h
# End Source File
# Begin Source File

SOURCE=.\_rdoenvironment.h
# End Source File
# Begin Source File

SOURCE=.\_rdoresultset.h
# End Source File
# Begin Source File

SOURCE=.\Ametter.h
# End Source File
# Begin Source File

SOURCE=.\AmetterRecordset.h
# End Source File
# Begin Source File

SOURCE=.\AMMETERRANGER.h
# End Source File
# Begin Source File

SOURCE=.\AngleSet.h
# End Source File
# Begin Source File

SOURCE=.\AutoDateReadModule.h
# End Source File
# Begin Source File

SOURCE=.\AutoFont.h
# End Source File
# Begin Source File

SOURCE=.\BreadSetting.h
# End Source File
# Begin Source File

SOURCE=.\BTNST.H
# End Source File
# Begin Source File

SOURCE=.\CHANGEAMMETER.h
# End Source File
# Begin Source File

SOURCE=.\CHANGEAMMETERDLG.h
# End Source File
# Begin Source File

SOURCE=.\ChildStation.h
# End Source File
# Begin Source File

SOURCE=.\CntrItem.h
# End Source File
# Begin Source File

SOURCE=.\Color.cpp
# End Source File
# Begin Source File

SOURCE=.\Color.h
# End Source File
# Begin Source File

SOURCE=.\ColorButton.h
# End Source File
# Begin Source File

SOURCE=.\ColorStatic.h
# End Source File
# Begin Source File

SOURCE=.\Condtions.h
# End Source File
# Begin Source File

SOURCE=.\CRC.H
# End Source File
# Begin Source File

SOURCE=.\Credits.h
# End Source File
# Begin Source File

SOURCE=.\Dask.h
# End Source File
# Begin Source File

SOURCE=.\DataBaseSet.h
# End Source File
# Begin Source File

SOURCE=.\DataInfoRecordSet.h
# End Source File
# Begin Source File

SOURCE=.\DataInformation.h
# End Source File
# Begin Source File

SOURCE=.\DataInto.h
# End Source File
# Begin Source File

SOURCE=.\res\Devior.smf
# End Source File
# Begin Source File

SOURCE=.\DIBAPI.H
# End Source File
# Begin Source File

SOURCE=.\DIBSectionLite.h
# End Source File
# Begin Source File

SOURCE=.\ELECTDEAL.h
# End Source File
# Begin Source File

SOURCE=.\ELKind.h
# End Source File
# Begin Source File

SOURCE=.\EnBitmap.cpp
# End Source File
# Begin Source File

SOURCE=.\EnBitmap.h
# End Source File
# Begin Source File

SOURCE=.\EveryTimes.h
# End Source File
# Begin Source File

SOURCE=.\Expandingdialog.h
# End Source File
# Begin Source File

SOURCE=.\FENGBEISET.h
# End Source File
# Begin Source File

SOURCE=.\font.h
# End Source File
# Begin Source File

SOURCE=.\FTPGetData.h
# End Source File
# Begin Source File

SOURCE=.\Garrison.h
# End Source File
# Begin Source File

SOURCE=.\GarrisonRecordSet.h
# End Source File
# Begin Source File

SOURCE=.\global.h
# End Source File
# Begin Source File

SOURCE=.\GridCell.h
# End Source File
# Begin Source File

SOURCE=.\GridCellBase.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrl.h
# End Source File
# Begin Source File

SOURCE=.\GridDropTarget.h
# End Source File
# Begin Source File

SOURCE=.\HoverEdit.h
# End Source File
# Begin Source File

SOURCE=.\HyperLink.h
# End Source File
# Begin Source File

SOURCE=.\IFRM.h
# End Source File
# Begin Source File

SOURCE=.\IFRMDoc.h
# End Source File
# Begin Source File

SOURCE=.\IFRMView.h
# End Source File
# Begin Source File

SOURCE=.\InitDialogBar.h
# End Source File
# Begin Source File

SOURCE=.\InPlaceEdit.h
# End Source File
# Begin Source File

SOURCE=.\IpFrame.h
# End Source File
# Begin Source File

SOURCE=.\Label.h
# End Source File
# Begin Source File

SOURCE=.\LineLoss.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MakeArray.h
# End Source File
# Begin Source File

SOURCE=.\Message.h
# End Source File
# Begin Source File

SOURCE=.\mschart.h
# End Source File
# Begin Source File

SOURCE=.\mscomm.h
# End Source File
# Begin Source File

SOURCE=.\msdgridctrl.h
# End Source File
# Begin Source File

SOURCE=.\mswinsockcontrol.h
# End Source File
# Begin Source File

SOURCE=.\MutiTreeCtrl.h
# End Source File
# Begin Source File

SOURCE=.\MyDialogBar.h
# End Source File
# Begin Source File

SOURCE=.\MyDialogDataBar.h
# End Source File
# Begin Source File

SOURCE=.\MyListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\OWEMONEY.h
# End Source File
# Begin Source File

SOURCE=.\Parameter.h
# End Source File
# Begin Source File

SOURCE=.\PassWord.h
# End Source File
# Begin Source File

SOURCE=.\PhaseTest.h
# End Source File
# Begin Source File

SOURCE=.\Phone.h
# End Source File
# Begin Source File

SOURCE=.\picture.h
# End Source File
# Begin Source File

SOURCE=.\PictureEx.h
# End Source File
# Begin Source File

SOURCE=.\PriceSet.h
# End Source File
# Begin Source File

SOURCE=.\ProgDlg.h
# End Source File
# Begin Source File

SOURCE=.\Protcoldlg.h
# End Source File
# Begin Source File

SOURCE=.\Ranger.h
# End Source File
# Begin Source File

SOURCE=.\rdc.h
# End Source File
# Begin Source File

SOURCE=.\rdocolumns.h
# End Source File
# Begin Source File

SOURCE=.\rdoconnections.h
# End Source File
# Begin Source File

SOURCE=.\rdoenvironments.h
# End Source File
# Begin Source File

SOURCE=.\rdoerror.h
# End Source File
# Begin Source File

SOURCE=.\rdoerrors.h
# End Source File
# Begin Source File

SOURCE=.\rdoparameter.h
# End Source File
# Begin Source File

SOURCE=.\rdoparameters.h
# End Source File
# Begin Source File

SOURCE=.\rdopreparedstatement.h
# End Source File
# Begin Source File

SOURCE=.\rdopreparedstatements.h
# End Source File
# Begin Source File

SOURCE=.\rdoqueries.h
# End Source File
# Begin Source File

SOURCE=.\rdoresultsets.h
# End Source File
# Begin Source File

SOURCE=.\rdotable.h
# End Source File
# Begin Source File

SOURCE=.\rdotables.h
# End Source File
# Begin Source File

SOURCE=.\ReadNoValueDlg.h
# End Source File
# Begin Source File

SOURCE=.\READRANGLE.h
# End Source File
# Begin Source File

SOURCE=.\Registry.h
# End Source File
# Begin Source File

SOURCE=.\ReplaceData.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h

!IF  "$(CFG)" == "IFRM - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help include file...
TargetName=IFRM
InputPath=.\Resource.h

"hlp\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "IFRM - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help include file...
TargetName=IFRM
InputPath=.\Resource.h

"hlp\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Search.h
# End Source File
# Begin Source File

SOURCE=.\SelectTable.h
# End Source File
# Begin Source File

SOURCE=.\ShowData.h
# End Source File
# Begin Source File

SOURCE=.\ShowInfo.h
# End Source File
# Begin Source File

SOURCE=.\SrvrItem.h
# End Source File
# Begin Source File

SOURCE=.\sstabctl.h
# End Source File
# Begin Source File

SOURCE=.\StationCommun.h
# End Source File
# Begin Source File

SOURCE=.\StatusbarAnimate.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TAPILine.h
# End Source File
# Begin Source File

SOURCE=.\TestComm.h
# End Source File
# Begin Source File

SOURCE=.\TimeCheck.h
# End Source File
# Begin Source File

SOURCE=.\TimeSelect.h
# End Source File
# Begin Source File

SOURCE=.\TitleTip.h
# End Source File
# Begin Source File

SOURCE=.\TrackControl.h
# End Source File
# Begin Source File

SOURCE=.\Transformer.h
# End Source File
# Begin Source File

SOURCE=.\TRansformerdisppear.h
# End Source File
# Begin Source File

SOURCE=.\TransformRecordset.h
# End Source File
# Begin Source File

SOURCE=.\UseInfoRecordSet.h
# End Source File
# Begin Source File

SOURCE=.\UserInfo.h
# End Source File
# Begin Source File

SOURCE=.\vcaxis.h
# End Source File
# Begin Source File

SOURCE=.\vcaxisgrid.h
# End Source File
# Begin Source File

SOURCE=.\vcaxisscale.h
# End Source File
# Begin Source File

SOURCE=.\vcaxistitle.h
# End Source File
# Begin Source File

SOURCE=.\vcbackdrop.h
# End Source File
# Begin Source File

SOURCE=.\vcbrush.h
# End Source File
# Begin Source File

SOURCE=.\vccategoryscale.h
# End Source File
# Begin Source File

SOURCE=.\vccolor.h
# End Source File
# Begin Source File

SOURCE=.\vccoor.h
# End Source File
# Begin Source File

SOURCE=.\vcdatagrid.h
# End Source File
# Begin Source File

SOURCE=.\vcdatapoint.h
# End Source File
# Begin Source File

SOURCE=.\vcdatapointlabel.h
# End Source File
# Begin Source File

SOURCE=.\vcdatapoints.h
# End Source File
# Begin Source File

SOURCE=.\vcfill.h
# End Source File
# Begin Source File

SOURCE=.\vcfont.h
# End Source File
# Begin Source File

SOURCE=.\vcfootnote.h
# End Source File
# Begin Source File

SOURCE=.\vcframe.h
# End Source File
# Begin Source File

SOURCE=.\vcintersection.h
# End Source File
# Begin Source File

SOURCE=.\vclabel.h
# End Source File
# Begin Source File

SOURCE=.\vclabels.h
# End Source File
# Begin Source File

SOURCE=.\vclcoor.h
# End Source File
# Begin Source File

SOURCE=.\vclegend.h
# End Source File
# Begin Source File

SOURCE=.\vclight.h
# End Source File
# Begin Source File

SOURCE=.\vclightsource.h
# End Source File
# Begin Source File

SOURCE=.\vclightsources.h
# End Source File
# Begin Source File

SOURCE=.\vclocation.h
# End Source File
# Begin Source File

SOURCE=.\vcmarker.h
# End Source File
# Begin Source File

SOURCE=.\vcpen.h
# End Source File
# Begin Source File

SOURCE=.\vcplot.h
# End Source File
# Begin Source File

SOURCE=.\vcplotbase.h
# End Source File
# Begin Source File

SOURCE=.\vcrect.h
# End Source File
# Begin Source File

SOURCE=.\vcseries.h
# End Source File
# Begin Source File

SOURCE=.\vcseriescollection.h
# End Source File
# Begin Source File

SOURCE=.\vcseriesmarker.h
# End Source File
# Begin Source File

SOURCE=.\vcseriesposition.h
# End Source File
# Begin Source File

SOURCE=.\vcshadow.h
# End Source File
# Begin Source File

SOURCE=.\vcstatline.h
# End Source File
# Begin Source File

SOURCE=.\vctextlayout.h
# End Source File
# Begin Source File

SOURCE=.\vctick.h
# End Source File
# Begin Source File

SOURCE=.\vctitle.h
# End Source File
# Begin Source File

SOURCE=.\vcvaluescale.h
# End Source File
# Begin Source File

SOURCE=.\vcview3d.h
# End Source File
# Begin Source File

SOURCE=.\vcwall.h
# End Source File
# Begin Source File

SOURCE=.\vcweighting.h
# End Source File
# Begin Source File

SOURCE=.\WuGongDlg.h
# End Source File
# Begin Source File

SOURCE=.\WuGongSpace.h
# End Source File
# Begin Source File

SOURCE=.\XPButton.h
# End Source File
# Begin Source File

SOURCE=.\ZHULIUTIMESELECT.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\012.gif
# End Source File
# Begin Source File

SOURCE=.\res\114.BMP
# End Source File
# Begin Source File

SOURCE=.\res\116.BMP
# End Source File
# Begin Source File

SOURCE=.\res\amkind.bmp
# End Source File
# Begin Source File

SOURCE=.\res\AMMETER.bmp
# End Source File
# Begin Source File

SOURCE=.\res\AMMETERTITLE.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ammetter.ico
# End Source File
# Begin Source File

SOURCE=.\res\amters.bmp
# End Source File
# Begin Source File

SOURCE=.\res\angle.ico
# End Source File
# Begin Source File

SOURCE=.\res\AR_MYDOC.ICO
# End Source File
# Begin Source File

SOURCE=.\res\BACK.BMP
# End Source File
# Begin Source File

SOURCE=.\res\back2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\back3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\backgrou.bmp
# End Source File
# Begin Source File

SOURCE=.\res\background.bmp
# End Source File
# Begin Source File

SOURCE=.\res\backgrounds.bmp
# End Source File
# Begin Source File

SOURCE=.\res\backs.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bird.ico
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_s.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BKbmp.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00004.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00005.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00006.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00007.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00008.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00009.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00010.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ButtonsWin3000.bmp
# End Source File
# Begin Source File

SOURCE=.\res\company.bmp
# End Source File
# Begin Source File

SOURCE=.\res\COMPANY.ico
# End Source File
# Begin Source File

SOURCE=.\res\compensa.ico
# End Source File
# Begin Source File

SOURCE=.\res\computer.bmp
# End Source File
# Begin Source File

SOURCE=.\res\conf.ico
# End Source File
# Begin Source File

SOURCE=.\res\connect.bmp
# End Source File
# Begin Source File

SOURCE=.\res\connect.ico
# End Source File
# Begin Source File

SOURCE=.\res\cursor.ico
# End Source File
# Begin Source File

SOURCE=.\res\devices.ico
# End Source File
# Begin Source File

SOURCE=.\res\dingchec.ico
# End Source File
# Begin Source File

SOURCE=.\res\DINGSHI.ico
# End Source File
# Begin Source File

SOURCE=.\res\dingshinnull.ico
# End Source File
# Begin Source File

SOURCE=.\res\disconnect.bmp
# End Source File
# Begin Source File

SOURCE=.\res\doWnButton.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ELECT.ico
# End Source File
# Begin Source File

SOURCE=.\res\eyes.gif
# End Source File
# Begin Source File

SOURCE=.\res\ftp.ico
# End Source File
# Begin Source File

SOURCE=.\res\Girdback.bmp
# End Source File
# Begin Source File

SOURCE=.\res\HLINE.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hyperlink.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_main.ico
# End Source File
# Begin Source File

SOURCE=.\res\IFRM.ico
# End Source File
# Begin Source File

SOURCE=.\res\IFRM.rc2
# End Source File
# Begin Source File

SOURCE=.\res\IFRMDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\img.bmp
# End Source File
# Begin Source File

SOURCE=.\res\IToolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Key.ico
# End Source File
# Begin Source File

SOURCE=.\res\light.ico
# End Source File
# Begin Source File

SOURCE=.\res\LINE.bmp
# End Source File
# Begin Source File

SOURCE=.\res\line.ico
# End Source File
# Begin Source File

SOURCE=.\res\line3.ico
# End Source File
# Begin Source File

SOURCE=.\res\linemode.ico
# End Source File
# Begin Source File

SOURCE=.\res\linemodu.ico
# End Source File
# Begin Source File

SOURCE=.\res\link.ICO
# End Source File
# Begin Source File

SOURCE=.\res\LIST.bmp
# End Source File
# Begin Source File

SOURCE=.\res\list.ico
# End Source File
# Begin Source File

SOURCE=.\res\Listdata.ico
# End Source File
# Begin Source File

SOURCE=.\res\lsalemod.ico
# End Source File
# Begin Source File

SOURCE=.\res\mainfram.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mainframe.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MISC.ICO
# End Source File
# Begin Source File

SOURCE=.\res\MODEM.ico
# End Source File
# Begin Source File

SOURCE=.\res\modules.ico
# End Source File
# Begin Source File

SOURCE=.\res\MSDTX.ICO
# End Source File
# Begin Source File

SOURCE=".\res\Nanotech Warning.ico"
# End Source File
# Begin Source File

SOURCE=.\res\Network.ico
# End Source File
# Begin Source File

SOURCE=.\res\NEWSAT.ICO
# End Source File
# Begin Source File

SOURCE=.\res\paramete.ico
# End Source File
# Begin Source File

SOURCE=.\res\parameter.ico
# End Source File
# Begin Source File

SOURCE=.\res\pass.ico
# End Source File
# Begin Source File

SOURCE=.\res\PLUG.ICO
# End Source File
# Begin Source File

SOURCE=.\res\power.ico
# End Source File
# Begin Source File

SOURCE=.\res\PRICETITLE.bmp
# End Source File
# Begin Source File

SOURCE=.\res\radar.gif
# End Source File
# Begin Source File

SOURCE=.\res\run.ico
# End Source File
# Begin Source File

SOURCE=.\res\salemodu.ico
# End Source File
# Begin Source File

SOURCE=.\Debug\SCDCNCLL.ICO
# End Source File
# Begin Source File

SOURCE=.\res\Set.ico
# End Source File
# Begin Source File

SOURCE=.\res\Setup.ico
# End Source File
# Begin Source File

SOURCE=.\res\splite.bmp
# End Source File
# Begin Source File

SOURCE=.\res\sql.ico
# End Source File
# Begin Source File

SOURCE=.\res\sub.ico
# End Source File
# Begin Source File

SOURCE=.\res\sub1.ico
# End Source File
# Begin Source File

SOURCE=.\res\submodul.ico
# End Source File
# Begin Source File

SOURCE=.\res\subtotal.ico
# End Source File
# Begin Source File

SOURCE=.\res\TABLEWIZ.ICO
# End Source File
# Begin Source File

SOURCE=.\res\task.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tb24.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TIMER.ico
# End Source File
# Begin Source File

SOURCE=.\res\title.ico
# End Source File
# Begin Source File

SOURCE=.\res\tolmodul.ico
# End Source File
# Begin Source File

SOURCE=.\res\tolmodule.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbox.ico
# End Source File
# Begin Source File

SOURCE=.\res\TOOLS.ICO
# End Source File
# Begin Source File

SOURCE=.\res\total.ICO
# End Source File
# Begin Source File

SOURCE=.\res\trans2.ico
# End Source File
# Begin Source File

SOURCE=.\res\trans3.ico
# End Source File
# Begin Source File

SOURCE=.\res\transfor.ico
# End Source File
# Begin Source File

SOURCE=.\res\TRANSFORMER.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TRANSFORMERTITLE.bmp
# End Source File
# Begin Source File

SOURCE=.\res\type.gif
# End Source File
# Begin Source File

SOURCE=.\res\usertitle.bmp
# End Source File
# Begin Source File

SOURCE=.\res\usetitle.bmp
# End Source File
# Begin Source File

SOURCE=.\res\VIEW.ICO
# End Source File
# Begin Source File

SOURCE=.\res\zhuliutitle.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ZSTITLE.bmp
# End Source File
# End Group
# Begin Group "Help Files"

# PROP Default_Filter "cnt;rtf"
# Begin Source File

SOURCE=.\hlp\AfxCore.rtf
# End Source File
# Begin Source File

SOURCE=.\hlp\AfxOleCl.rtf
# End Source File
# Begin Source File

SOURCE=.\hlp\AfxOleSv.rtf
# End Source File
# Begin Source File

SOURCE=.\hlp\AfxPrint.rtf
# End Source File
# Begin Source File

SOURCE=.\hlp\AppExit.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Bullet.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\CurArw2.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\CurArw4.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\CurHelp.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditCopy.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditCut.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditPast.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditUndo.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileNew.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileOpen.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FilePrnt.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileSave.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\HlpSBar.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\HlpTBar.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\IFRM.cnt

!IF  "$(CFG)" == "IFRM - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Copying contents file...
OutDir=.\Release
InputPath=.\hlp\IFRM.cnt
InputName=IFRM

"$(OutDir)\$(InputName).cnt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "hlp\$(InputName).cnt" $(OutDir)

# End Custom Build

!ELSEIF  "$(CFG)" == "IFRM - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Copying contents file...
OutDir=.\Debug
InputPath=.\hlp\IFRM.cnt
InputName=IFRM

"$(OutDir)\$(InputName).cnt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "hlp\$(InputName).cnt" $(OutDir)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\RecFirst.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecLast.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecNext.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecPrev.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Scmax.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\ScMenu.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Scmin.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=".\PCI-Dask.dll"
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\res\sample.avi
# End Source File
# Begin Source File

SOURCE=".\PCI-Dask.lib"
# End Source File
# End Target
# End Project
# Section IFRM : {E9E074E6-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcFootnote
# 	2:10:HeaderFile:vcfootnote.h
# 	2:8:ImplFile:vcfootnote.cpp
# End Section
# Section IFRM : {E9E074CD-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcRect
# 	2:10:HeaderFile:vcrect.h
# 	2:8:ImplFile:vcrect.cpp
# End Section
# Section IFRM : {E9E07502-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcSeriesPosition
# 	2:10:HeaderFile:vcseriesposition.h
# 	2:8:ImplFile:vcseriesposition.cpp
# End Section
# Section IFRM : {E9E074D6-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcLocation
# 	2:10:HeaderFile:vclocation.h
# 	2:8:ImplFile:vclocation.cpp
# End Section
# Section IFRM : {7BF80981-BF32-101A-8BBB-00AA00300CAB}
# 	2:5:Class:CPicture
# 	2:10:HeaderFile:picture.h
# 	2:8:ImplFile:picture.cpp
# End Section
# Section IFRM : {3A2B370A-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CMSChart
# 	2:10:HeaderFile:mschart.h
# 	2:8:ImplFile:mschart.cpp
# End Section
# Section IFRM : {2E746492-6ED1-11CE-9223-08002B369A33}
# 	2:5:Class:CrdoColumns
# 	2:10:HeaderFile:rdocolumns.h
# 	2:8:ImplFile:rdocolumns.cpp
# End Section
# Section IFRM : {E9E074D1-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcPen
# 	2:10:HeaderFile:vcpen.h
# 	2:8:ImplFile:vcpen.cpp
# End Section
# Section IFRM : {E9E07506-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcStatLine
# 	2:10:HeaderFile:vcstatline.h
# 	2:8:ImplFile:vcstatline.cpp
# End Section
# Section IFRM : {5E71F04E-551F-11CF-8152-00AA00A40C25}
# 	2:5:Class:C_rdoColumn
# 	2:10:HeaderFile:_rdocolumn.h
# 	2:8:ImplFile:_rdocolumn.cpp
# End Section
# Section IFRM : {E9E0751D-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcIntersection
# 	2:10:HeaderFile:vcintersection.h
# 	2:8:ImplFile:vcintersection.cpp
# End Section
# Section IFRM : {2E746496-6ED1-11CE-9223-08002B369A33}
# 	2:5:Class:CrdoResultsets
# 	2:10:HeaderFile:rdoresultsets.h
# 	2:8:ImplFile:rdoresultsets.cpp
# End Section
# Section IFRM : {E9E074D5-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcTextLayout
# 	2:10:HeaderFile:vctextlayout.h
# 	2:8:ImplFile:vctextlayout.cpp
# End Section
# Section IFRM : {5E71F052-551F-11CF-8152-00AA00A40C25}
# 	2:5:Class:CrdoParameter
# 	2:10:HeaderFile:rdoparameter.h
# 	2:8:ImplFile:rdoparameter.cpp
# End Section
# Section IFRM : {43478D73-78E0-11CF-8E78-00A0D100038E}
# 	2:21:DefaultSinkHeaderFile:rdc.h
# 	2:16:DefaultSinkClass:CRdc
# End Section
# Section IFRM : {E9E074DC-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcShadow
# 	2:10:HeaderFile:vcshadow.h
# 	2:8:ImplFile:vcshadow.cpp
# End Section
# Section IFRM : {E9E074FC-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcWall
# 	2:10:HeaderFile:vcwall.h
# 	2:8:ImplFile:vcwall.cpp
# End Section
# Section IFRM : {E9E074EC-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcLightSource
# 	2:10:HeaderFile:vclightsource.h
# 	2:8:ImplFile:vclightsource.cpp
# End Section
# Section IFRM : {E9E07511-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcSeries
# 	2:10:HeaderFile:vcseries.h
# 	2:8:ImplFile:vcseries.cpp
# End Section
# Section IFRM : {E9E07521-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcAxisScale
# 	2:10:HeaderFile:vcaxisscale.h
# 	2:8:ImplFile:vcaxisscale.cpp
# End Section
# Section IFRM : {E9E074E0-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcFrame
# 	2:10:HeaderFile:vcframe.h
# 	2:8:ImplFile:vcframe.cpp
# End Section
# Section IFRM : {E9E074F0-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcLight
# 	2:10:HeaderFile:vclight.h
# 	2:8:ImplFile:vclight.cpp
# End Section
# Section IFRM : {B541C03D-63BC-11CE-920C-08002B369A33}
# 	2:5:Class:CrdoTable
# 	2:10:HeaderFile:rdotable.h
# 	2:8:ImplFile:rdotable.cpp
# End Section
# Section IFRM : {00028C00-0000-0000-0000-000000000046}
# 	2:21:DefaultSinkHeaderFile:msdgridctrl.h
# 	2:16:DefaultSinkClass:CMsDgridCtrl
# End Section
# Section IFRM : {E9E07525-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcAxis
# 	2:10:HeaderFile:vcaxis.h
# 	2:8:ImplFile:vcaxis.cpp
# End Section
# Section IFRM : {5E71F051-551F-11CF-8152-00AA00A40C25}
# 	2:5:Class:C_rdoEnvironment
# 	2:10:HeaderFile:_rdoenvironment.h
# 	2:8:ImplFile:_rdoenvironment.cpp
# End Section
# Section IFRM : {E9E07515-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcAxisTitle
# 	2:10:HeaderFile:vcaxistitle.h
# 	2:8:ImplFile:vcaxistitle.cpp
# End Section
# Section IFRM : {5E71F04D-551F-11CF-8152-00AA00A40C25}
# 	2:5:Class:C_rdoConnection
# 	2:10:HeaderFile:_rdoconnection.h
# 	2:8:ImplFile:_rdoconnection.cpp
# End Section
# Section IFRM : {E9E074C9-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcCoor
# 	2:10:HeaderFile:vccoor.h
# 	2:8:ImplFile:vccoor.cpp
# End Section
# Section IFRM : {E6E17E90-DF38-11CF-8E74-00A0C90F26F8}
# 	2:5:Class:CMSComm
# 	2:10:HeaderFile:mscomm.h
# 	2:8:ImplFile:mscomm.cpp
# End Section
# Section IFRM : {E9E074CB-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcLCoor
# 	2:10:HeaderFile:vclcoor.h
# 	2:8:ImplFile:vclcoor.cpp
# End Section
# Section IFRM : {E9E074F4-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcPlotBase
# 	2:10:HeaderFile:vcplotbase.h
# 	2:8:ImplFile:vcplotbase.cpp
# End Section
# Section IFRM : {E9E074E4-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcTitle
# 	2:10:HeaderFile:vctitle.h
# 	2:8:ImplFile:vctitle.cpp
# End Section
# Section IFRM : {E9E0750C-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcDataPointLabel
# 	2:10:HeaderFile:vcdatapointlabel.h
# 	2:8:ImplFile:vcdatapointlabel.cpp
# End Section
# Section IFRM : {648A5600-2C6E-101B-82B6-000000000014}
# 	2:21:DefaultSinkHeaderFile:mscomm.h
# 	2:16:DefaultSinkClass:CMSComm
# End Section
# Section IFRM : {2E746495-6ED1-11CE-9223-08002B369A33}
# 	2:5:Class:CrdoParameters
# 	2:10:HeaderFile:rdoparameters.h
# 	2:8:ImplFile:rdoparameters.cpp
# End Section
# Section IFRM : {2E7464A0-6ED1-11CE-9223-08002B369A33}
# 	2:5:Class:CrdoErrors
# 	2:10:HeaderFile:rdoerrors.h
# 	2:8:ImplFile:rdoerrors.cpp
# End Section
# Section IFRM : {E9E074CF-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcColor
# 	2:10:HeaderFile:vccolor.h
# 	2:8:ImplFile:vccolor.cpp
# End Section
# Section IFRM : {2E746494-6ED1-11CE-9223-08002B369A33}
# 	2:5:Class:CrdoConnections
# 	2:10:HeaderFile:rdoconnections.h
# 	2:8:ImplFile:rdoconnections.cpp
# End Section
# Section IFRM : {5D545B93-97CA-11CF-8171-00AA00A40C25}
# 	2:5:Class:CrdoPreparedStatements
# 	2:10:HeaderFile:rdopreparedstatements.h
# 	2:8:ImplFile:rdopreparedstatements.cpp
# End Section
# Section IFRM : {E9E0751B-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcAxisGrid
# 	2:10:HeaderFile:vcaxisgrid.h
# 	2:8:ImplFile:vcaxisgrid.cpp
# End Section
# Section IFRM : {5E71F050-551F-11CF-8152-00AA00A40C25}
# 	2:5:Class:CrdoPreparedStatement
# 	2:10:HeaderFile:rdopreparedstatement.h
# 	2:8:ImplFile:rdopreparedstatement.cpp
# End Section
# Section IFRM : {E9E07504-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcSeriesMarker
# 	2:10:HeaderFile:vcseriesmarker.h
# 	2:8:ImplFile:vcseriesmarker.cpp
# End Section
# Section IFRM : {E9E074D8-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcFont
# 	2:10:HeaderFile:vcfont.h
# 	2:8:ImplFile:vcfont.cpp
# End Section
# Section IFRM : {E9E074E8-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcLegend
# 	2:10:HeaderFile:vclegend.h
# 	2:8:ImplFile:vclegend.cpp
# End Section
# Section IFRM : {E9E074EA-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcDataGrid
# 	2:10:HeaderFile:vcdatagrid.h
# 	2:8:ImplFile:vcdatagrid.cpp
# End Section
# Section IFRM : {43478D71-78E0-11CF-8E78-00A0D100038E}
# 	2:5:Class:CRdc
# 	2:10:HeaderFile:rdc.h
# 	2:8:ImplFile:rdc.cpp
# End Section
# Section IFRM : {E9E074DA-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcBrush
# 	2:10:HeaderFile:vcbrush.h
# 	2:8:ImplFile:vcbrush.cpp
# End Section
# Section IFRM : {E9E074D3-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcMarker
# 	2:10:HeaderFile:vcmarker.h
# 	2:8:ImplFile:vcmarker.cpp
# End Section
# Section IFRM : {3A2B370C-BA0A-11D1-B137-0000F8753F5D}
# 	2:21:DefaultSinkHeaderFile:mschart.h
# 	2:16:DefaultSinkClass:CMSChart
# End Section
# Section IFRM : {E9E07508-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcLabel
# 	2:10:HeaderFile:vclabel.h
# 	2:8:ImplFile:vclabel.cpp
# End Section
# Section IFRM : {B541C034-63BC-11CE-920C-08002B369A33}
# 	2:5:Class:CrdoError
# 	2:10:HeaderFile:rdoerror.h
# 	2:8:ImplFile:rdoerror.cpp
# End Section
# Section IFRM : {E9E074FA-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcWeighting
# 	2:10:HeaderFile:vcweighting.h
# 	2:8:ImplFile:vcweighting.cpp
# End Section
# Section IFRM : {248DD892-BB45-11CF-9ABC-0080C7E7B78D}
# 	2:5:Class:CMSWinsockControl
# 	2:10:HeaderFile:mswinsockcontrol.h
# 	2:8:ImplFile:mswinsockcontrol.cpp
# End Section
# Section IFRM : {E9E0751F-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcTick
# 	2:10:HeaderFile:vctick.h
# 	2:8:ImplFile:vctick.cpp
# End Section
# Section IFRM : {2A4FCCB0-DFF1-11CF-8E74-00A0C90F26F8}
# 	2:5:Class:CSSTabCtl
# 	2:10:HeaderFile:sstabctl.h
# 	2:8:ImplFile:sstabctl.cpp
# End Section
# Section IFRM : {E9E07513-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcSeriesCollection
# 	2:10:HeaderFile:vcseriescollection.h
# 	2:8:ImplFile:vcseriescollection.cpp
# End Section
# Section IFRM : {5E71F04B-551F-11CF-8152-00AA00A40C25}
# 	2:5:Class:C_rdoEngine
# 	2:10:HeaderFile:_rdoengine.h
# 	2:8:ImplFile:_rdoengine.cpp
# End Section
# Section IFRM : {2E746498-6ED1-11CE-9223-08002B369A33}
# 	2:5:Class:CrdoQueries
# 	2:10:HeaderFile:rdoqueries.h
# 	2:8:ImplFile:rdoqueries.cpp
# End Section
# Section IFRM : {E9E074EE-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcLightSources
# 	2:10:HeaderFile:vclightsources.h
# 	2:8:ImplFile:vclightsources.cpp
# End Section
# Section IFRM : {E9E074E2-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcBackdrop
# 	2:10:HeaderFile:vcbackdrop.h
# 	2:8:ImplFile:vcbackdrop.cpp
# End Section
# Section IFRM : {E9E0752A-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcDataPoints
# 	2:10:HeaderFile:vcdatapoints.h
# 	2:8:ImplFile:vcdatapoints.cpp
# End Section
# Section IFRM : {E9E07523-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcValueScale
# 	2:10:HeaderFile:vcvaluescale.h
# 	2:8:ImplFile:vcvaluescale.cpp
# End Section
# Section IFRM : {2E746493-6ED1-11CE-9223-08002B369A33}
# 	2:5:Class:CrdoTables
# 	2:10:HeaderFile:rdotables.h
# 	2:8:ImplFile:rdotables.cpp
# End Section
# Section IFRM : {E9E0750A-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcLabels
# 	2:10:HeaderFile:vclabels.h
# 	2:8:ImplFile:vclabels.cpp
# End Section
# Section IFRM : {E9E074DE-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcFill
# 	2:10:HeaderFile:vcfill.h
# 	2:8:ImplFile:vcfill.cpp
# End Section
# Section IFRM : {E9E074F2-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcView3d
# 	2:10:HeaderFile:vcview3d.h
# 	2:8:ImplFile:vcview3d.cpp
# End Section
# Section IFRM : {248DD896-BB45-11CF-9ABC-0080C7E7B78D}
# 	2:21:DefaultSinkHeaderFile:mswinsockcontrol.h
# 	2:16:DefaultSinkClass:CMSWinsockControl
# End Section
# Section IFRM : {BDC217C5-ED16-11CD-956C-0000C04E4C0A}
# 	2:21:DefaultSinkHeaderFile:sstabctl.h
# 	2:16:DefaultSinkClass:CSSTabCtl
# End Section
# Section IFRM : {BEF6E003-A874-101A-8BBA-00AA00300CAB}
# 	2:5:Class:COleFont
# 	2:10:HeaderFile:font.h
# 	2:8:ImplFile:font.cpp
# End Section
# Section IFRM : {E9E07517-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcCategoryScale
# 	2:10:HeaderFile:vccategoryscale.h
# 	2:8:ImplFile:vccategoryscale.cpp
# End Section
# Section IFRM : {E9E0750E-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcDataPoint
# 	2:10:HeaderFile:vcdatapoint.h
# 	2:8:ImplFile:vcdatapoint.cpp
# End Section
# Section IFRM : {5E71F053-551F-11CF-8152-00AA00A40C25}
# 	2:5:Class:CrdoEnvironments
# 	2:10:HeaderFile:rdoenvironments.h
# 	2:8:ImplFile:rdoenvironments.cpp
# End Section
# Section IFRM : {E9E07527-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcPlot
# 	2:10:HeaderFile:vcplot.h
# 	2:8:ImplFile:vcplot.cpp
# End Section
# Section IFRM : {00028C02-0000-0000-0000-000000000046}
# 	2:5:Class:CMsDgridCtrl
# 	2:10:HeaderFile:msdgridctrl.h
# 	2:8:ImplFile:msdgridctrl.cpp
# End Section
# Section IFRM : {5E71F04F-551F-11CF-8152-00AA00A40C25}
# 	2:5:Class:C_rdoResultset
# 	2:10:HeaderFile:_rdoresultset.h
# 	2:8:ImplFile:_rdoresultset.cpp
# End Section
