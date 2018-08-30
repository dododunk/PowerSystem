using System;
using System.CodeDom.Compiler;
using System.ComponentModel;
using System.Diagnostics;
using System.Globalization;
using System.Resources;
using System.Runtime.CompilerServices;
namespace WinFormsUI.Docking
{
	[GeneratedCode("System.Resources.Tools.StronglyTypedResourceBuilder", "2.0.0.0"), DebuggerNonUserCode, CompilerGenerated]
	internal class Strings
	{
		private static ResourceManager resourceMan;
		private static CultureInfo resourceCulture;
		[EditorBrowsable(EditorBrowsableState.Advanced)]
		internal static ResourceManager ResourceManager
		{
			get
			{
				if (object.ReferenceEquals(Strings.resourceMan, null))
				{
					ResourceManager resourceManager = new ResourceManager("WinFormsUI.Docking.Strings", typeof(Strings).Assembly);
					Strings.resourceMan = resourceManager;
				}
				return Strings.resourceMan;
			}
		}
		[EditorBrowsable(EditorBrowsableState.Advanced)]
		internal static CultureInfo Culture
		{
			get
			{
				return Strings.resourceCulture;
			}
			set
			{
				Strings.resourceCulture = value;
			}
		}
		internal static string Category_Docking
		{
			get
			{
				return Strings.ResourceManager.GetString("Category_Docking", Strings.resourceCulture);
			}
		}
		internal static string Category_DockingNotification
		{
			get
			{
				return Strings.ResourceManager.GetString("Category_DockingNotification", Strings.resourceCulture);
			}
		}
		internal static string Category_PropertyChanged
		{
			get
			{
				return Strings.ResourceManager.GetString("Category_PropertyChanged", Strings.resourceCulture);
			}
		}
		internal static string DockAreaEditor_FloatCheckBoxText
		{
			get
			{
				return Strings.ResourceManager.GetString("DockAreaEditor_FloatCheckBoxText", Strings.resourceCulture);
			}
		}
		internal static string DockContent_AllowEndUserDocking_Description
		{
			get
			{
				return Strings.ResourceManager.GetString("DockContent_AllowEndUserDocking_Description", Strings.resourceCulture);
			}
		}
		internal static string DockContent_AutoHidePortion_Description
		{
			get
			{
				return Strings.ResourceManager.GetString("DockContent_AutoHidePortion_Description", Strings.resourceCulture);
			}
		}
		internal static string DockContent_CloseButton_Description
		{
			get
			{
				return Strings.ResourceManager.GetString("DockContent_CloseButton_Description", Strings.resourceCulture);
			}
		}
		internal static string DockContent_CloseButtonVisible_Description
		{
			get
			{
				return Strings.ResourceManager.GetString("DockContent_CloseButtonVisible_Description", Strings.resourceCulture);
			}
		}
		internal static string DockContent_Constructor_InvalidForm
		{
			get
			{
				return Strings.ResourceManager.GetString("DockContent_Constructor_InvalidForm", Strings.resourceCulture);
			}
		}
		internal static string DockContent_DockAreas_Description
		{
			get
			{
				return Strings.ResourceManager.GetString("DockContent_DockAreas_Description", Strings.resourceCulture);
			}
		}
		internal static string DockContent_DockStateChanged_Description
		{
			get
			{
				return Strings.ResourceManager.GetString("DockContent_DockStateChanged_Description", Strings.resourceCulture);
			}
		}
		internal static string DockContent_HideOnClose_Description
		{
			get
			{
				return Strings.ResourceManager.GetString("DockContent_HideOnClose_Description", Strings.resourceCulture);
			}
		}
		internal static string DockContent_ShowHint_Description
		{
			get
			{
				return Strings.ResourceManager.GetString("DockContent_ShowHint_Description", Strings.resourceCulture);
			}
		}
		internal static string DockContent_TabPageContextMenu_Description
		{
			get
			{
				return Strings.ResourceManager.GetString("DockContent_TabPageContextMenu_Description", Strings.resourceCulture);
			}
		}
		internal static string DockContent_TabText_Description
		{
			get
			{
				return Strings.ResourceManager.GetString("DockContent_TabText_Description", Strings.resourceCulture);
			}
		}
		internal static string DockContent_ToolTipText_Description
		{
			get
			{
				return Strings.ResourceManager.GetString("DockContent_ToolTipText_Description", Strings.resourceCulture);
			}
		}
		internal static string DockContentHandler_AutoHidePortion_OutOfRange
		{
			get
			{
				return Strings.ResourceManager.GetString("DockContentHandler_AutoHidePortion_OutOfRange", Strings.resourceCulture);
			}
		}
		internal static string DockContentHandler_DockAreas_InvalidValue
		{
			get
			{
				return Strings.ResourceManager.GetString("DockContentHandler_DockAreas_InvalidValue", Strings.resourceCulture);
			}
		}
		internal static string DockContentHandler_DockPane_InvalidValue
		{
			get
			{
				return Strings.ResourceManager.GetString("DockContentHandler_DockPane_InvalidValue", Strings.resourceCulture);
			}
		}
		internal static string DockContentHandler_FloatPane_InvalidValue
		{
			get
			{
				return Strings.ResourceManager.GetString("DockContentHandler_FloatPane_InvalidValue", Strings.resourceCulture);
			}
		}
		internal static string DockContentHandler_IsFloat_InvalidValue
		{
			get
			{
				return Strings.ResourceManager.GetString("DockContentHandler_IsFloat_InvalidValue", Strings.resourceCulture);
			}
		}
		internal static string DockContentHandler_SetDockState_InvalidState
		{
			get
			{
				return Strings.ResourceManager.GetString("DockContentHandler_SetDockState_InvalidState", Strings.resourceCulture);
			}
		}
		internal static string DockContentHandler_SetDockState_NullPanel
		{
			get
			{
				return Strings.ResourceManager.GetString("DockContentHandler_SetDockState_NullPanel", Strings.resourceCulture);
			}
		}
		internal static string DockContentHandler_Show_InvalidBeforeContent
		{
			get
			{
				return Strings.ResourceManager.GetString("DockContentHandler_Show_InvalidBeforeContent", Strings.resourceCulture);
			}
		}
		internal static string DockContentHandler_Show_InvalidDockState
		{
			get
			{
				return Strings.ResourceManager.GetString("DockContentHandler_Show_InvalidDockState", Strings.resourceCulture);
			}
		}
		internal static string DockContentHandler_Show_InvalidPrevPane
		{
			get
			{
				return Strings.ResourceManager.GetString("DockContentHandler_Show_InvalidPrevPane", Strings.resourceCulture);
			}
		}
		internal static string DockContentHandler_Show_NullDockPanel
		{
			get
			{
				return Strings.ResourceManager.GetString("DockContentHandler_Show_NullDockPanel", Strings.resourceCulture);
			}
		}
		internal static string DockContentHandler_Show_NullPane
		{
			get
			{
				return Strings.ResourceManager.GetString("DockContentHandler_Show_NullPane", Strings.resourceCulture);
			}
		}
		internal static string DockContentHandler_ShowHint_InvalidValue
		{
			get
			{
				return Strings.ResourceManager.GetString("DockContentHandler_ShowHint_InvalidValue", Strings.resourceCulture);
			}
		}
		internal static string DockHandler_TabPageContextMenuStrip_Description
		{
			get
			{
				return Strings.ResourceManager.GetString("DockHandler_TabPageContextMenuStrip_Description", Strings.resourceCulture);
			}
		}
		internal static string DockIndicator_ToolTipText
		{
			get
			{
				return Strings.ResourceManager.GetString("DockIndicator_ToolTipText", Strings.resourceCulture);
			}
		}
		internal static string DockPane_ActiveContent_InvalidValue
		{
			get
			{
				return Strings.ResourceManager.GetString("DockPane_ActiveContent_InvalidValue", Strings.resourceCulture);
			}
		}
		internal static string DockPane_Constructor_NullContent
		{
			get
			{
				return Strings.ResourceManager.GetString("DockPane_Constructor_NullContent", Strings.resourceCulture);
			}
		}
		internal static string DockPane_Constructor_NullDockPanel
		{
			get
			{
				return Strings.ResourceManager.GetString("DockPane_Constructor_NullDockPanel", Strings.resourceCulture);
			}
		}
		internal static string DockPane_DockTo_InvalidContainer
		{
			get
			{
				return Strings.ResourceManager.GetString("DockPane_DockTo_InvalidContainer", Strings.resourceCulture);
			}
		}
		internal static string DockPane_DockTo_NoPrevPane
		{
			get
			{
				return Strings.ResourceManager.GetString("DockPane_DockTo_NoPrevPane", Strings.resourceCulture);
			}
		}
		internal static string DockPane_DockTo_NullContainer
		{
			get
			{
				return Strings.ResourceManager.GetString("DockPane_DockTo_NullContainer", Strings.resourceCulture);
			}
		}
		internal static string DockPane_DockTo_NullPrevPane
		{
			get
			{
				return Strings.ResourceManager.GetString("DockPane_DockTo_NullPrevPane", Strings.resourceCulture);
			}
		}
		internal static string DockPane_DockTo_SelfPrevPane
		{
			get
			{
				return Strings.ResourceManager.GetString("DockPane_DockTo_SelfPrevPane", Strings.resourceCulture);
			}
		}
		internal static string DockPane_FloatWindow_InvalidValue
		{
			get
			{
				return Strings.ResourceManager.GetString("DockPane_FloatWindow_InvalidValue", Strings.resourceCulture);
			}
		}
		internal static string DockPane_SetContentIndex_InvalidContent
		{
			get
			{
				return Strings.ResourceManager.GetString("DockPane_SetContentIndex_InvalidContent", Strings.resourceCulture);
			}
		}
		internal static string DockPane_SetContentIndex_InvalidIndex
		{
			get
			{
				return Strings.ResourceManager.GetString("DockPane_SetContentIndex_InvalidIndex", Strings.resourceCulture);
			}
		}
		internal static string DockPane_SetDockState_InvalidState
		{
			get
			{
				return Strings.ResourceManager.GetString("DockPane_SetDockState_InvalidState", Strings.resourceCulture);
			}
		}
		internal static string DockPaneCaption_ToolTipAutoHide
		{
			get
			{
				return Strings.ResourceManager.GetString("DockPaneCaption_ToolTipAutoHide", Strings.resourceCulture);
			}
		}
		internal static string DockPaneCaption_ToolTipClose
		{
			get
			{
				return Strings.ResourceManager.GetString("DockPaneCaption_ToolTipClose", Strings.resourceCulture);
			}
		}
		internal static string DockPaneCaption_ToolTipOptions
		{
			get
			{
				return Strings.ResourceManager.GetString("DockPaneCaption_ToolTipOptions", Strings.resourceCulture);
			}
		}
		internal static string DockPanel_ActiveAutoHideContent_InvalidValue
		{
			get
			{
				return Strings.ResourceManager.GetString("DockPanel_ActiveAutoHideContent_InvalidValue", Strings.resourceCulture);
			}
		}
		internal static string DockPanel_ActiveContentChanged_Description
		{
			get
			{
				return Strings.ResourceManager.GetString("DockPanel_ActiveContentChanged_Description", Strings.resourceCulture);
			}
		}
		internal static string DockPanel_ActiveDocumentChanged_Description
		{
			get
			{
				return Strings.ResourceManager.GetString("DockPanel_ActiveDocumentChanged_Description", Strings.resourceCulture);
			}
		}
		internal static string DockPanel_ActivePaneChanged_Description
		{
			get
			{
				return Strings.ResourceManager.GetString("DockPanel_ActivePaneChanged_Description", Strings.resourceCulture);
			}
		}
		internal static string DockPanel_AllowEndUserDocking_Description
		{
			get
			{
				return Strings.ResourceManager.GetString("DockPanel_AllowEndUserDocking_Description", Strings.resourceCulture);
			}
		}
		internal static string DockPanel_AllowEndUserNestedDocking_Description
		{
			get
			{
				return Strings.ResourceManager.GetString("DockPanel_AllowEndUserNestedDocking_Description", Strings.resourceCulture);
			}
		}
		internal static string DockPanel_ContentAdded_Description
		{
			get
			{
				return Strings.ResourceManager.GetString("DockPanel_ContentAdded_Description", Strings.resourceCulture);
			}
		}
		internal static string DockPanel_ContentRemoved_Description
		{
			get
			{
				return Strings.ResourceManager.GetString("DockPanel_ContentRemoved_Description", Strings.resourceCulture);
			}
		}
		internal static string DockPanel_DefaultFloatWindowSize_Description
		{
			get
			{
				return Strings.ResourceManager.GetString("DockPanel_DefaultFloatWindowSize_Description", Strings.resourceCulture);
			}
		}
		internal static string DockPanel_Description
		{
			get
			{
				return Strings.ResourceManager.GetString("DockPanel_Description", Strings.resourceCulture);
			}
		}
		internal static string DockPanel_DockBottomPortion_Description
		{
			get
			{
				return Strings.ResourceManager.GetString("DockPanel_DockBottomPortion_Description", Strings.resourceCulture);
			}
		}
		internal static string DockPanel_DockLeftPortion_Description
		{
			get
			{
				return Strings.ResourceManager.GetString("DockPanel_DockLeftPortion_Description", Strings.resourceCulture);
			}
		}
		internal static string DockPanel_DockPanelSkin
		{
			get
			{
				return Strings.ResourceManager.GetString("DockPanel_DockPanelSkin", Strings.resourceCulture);
			}
		}
		internal static string DockPanel_DockRightPortion_Description
		{
			get
			{
				return Strings.ResourceManager.GetString("DockPanel_DockRightPortion_Description", Strings.resourceCulture);
			}
		}
		internal static string DockPanel_DockTopPortion_Description
		{
			get
			{
				return Strings.ResourceManager.GetString("DockPanel_DockTopPortion_Description", Strings.resourceCulture);
			}
		}
		internal static string DockPanel_DocumentStyle_Description
		{
			get
			{
				return Strings.ResourceManager.GetString("DockPanel_DocumentStyle_Description", Strings.resourceCulture);
			}
		}
		internal static string DockPanel_DocumentTabStripLocation
		{
			get
			{
				return Strings.ResourceManager.GetString("DockPanel_DocumentTabStripLocation", Strings.resourceCulture);
			}
		}
		internal static string DockPanel_LoadFromXml_AlreadyInitialized
		{
			get
			{
				return Strings.ResourceManager.GetString("DockPanel_LoadFromXml_AlreadyInitialized", Strings.resourceCulture);
			}
		}
		internal static string DockPanel_LoadFromXml_InvalidFormatVersion
		{
			get
			{
				return Strings.ResourceManager.GetString("DockPanel_LoadFromXml_InvalidFormatVersion", Strings.resourceCulture);
			}
		}
		internal static string DockPanel_LoadFromXml_InvalidXmlFormat
		{
			get
			{
				return Strings.ResourceManager.GetString("DockPanel_LoadFromXml_InvalidXmlFormat", Strings.resourceCulture);
			}
		}
		internal static string DockPanel_ParentForm_Invalid
		{
			get
			{
				return Strings.ResourceManager.GetString("DockPanel_ParentForm_Invalid", Strings.resourceCulture);
			}
		}
		internal static string DockPanel_Persistor_XmlFileComment1
		{
			get
			{
				return Strings.ResourceManager.GetString("DockPanel_Persistor_XmlFileComment1", Strings.resourceCulture);
			}
		}
		internal static string DockPanel_Persistor_XmlFileComment2
		{
			get
			{
				return Strings.ResourceManager.GetString("DockPanel_Persistor_XmlFileComment2", Strings.resourceCulture);
			}
		}
		internal static string DockPanel_RightToLeftLayout_Description
		{
			get
			{
				return Strings.ResourceManager.GetString("DockPanel_RightToLeftLayout_Description", Strings.resourceCulture);
			}
		}
		internal static string DockPanel_SetPaneIndex_InvalidIndex
		{
			get
			{
				return Strings.ResourceManager.GetString("DockPanel_SetPaneIndex_InvalidIndex", Strings.resourceCulture);
			}
		}
		internal static string DockPanel_SetPaneIndex_InvalidPane
		{
			get
			{
				return Strings.ResourceManager.GetString("DockPanel_SetPaneIndex_InvalidPane", Strings.resourceCulture);
			}
		}
		internal static string DockPanel_ShowDocumentIcon_Description
		{
			get
			{
				return Strings.ResourceManager.GetString("DockPanel_ShowDocumentIcon_Description", Strings.resourceCulture);
			}
		}
		internal static string DockPaneStrip_ToolTipClose
		{
			get
			{
				return Strings.ResourceManager.GetString("DockPaneStrip_ToolTipClose", Strings.resourceCulture);
			}
		}
		internal static string DockPaneStrip_ToolTipWindowList
		{
			get
			{
				return Strings.ResourceManager.GetString("DockPaneStrip_ToolTipWindowList", Strings.resourceCulture);
			}
		}
		internal static string FloatWindow_Constructor_NullDockPanel
		{
			get
			{
				return Strings.ResourceManager.GetString("FloatWindow_Constructor_NullDockPanel", Strings.resourceCulture);
			}
		}
		internal static string FloatWindow_SetPaneIndex_InvalidIndex
		{
			get
			{
				return Strings.ResourceManager.GetString("FloatWindow_SetPaneIndex_InvalidIndex", Strings.resourceCulture);
			}
		}
		internal static string FloatWindow_SetPaneIndex_InvalidPane
		{
			get
			{
				return Strings.ResourceManager.GetString("FloatWindow_SetPaneIndex_InvalidPane", Strings.resourceCulture);
			}
		}
		internal static string IDockDragSource_DockTo_InvalidPanel
		{
			get
			{
				return Strings.ResourceManager.GetString("IDockDragSource_DockTo_InvalidPanel", Strings.resourceCulture);
			}
		}
		internal Strings()
		{
		}
	}
}
