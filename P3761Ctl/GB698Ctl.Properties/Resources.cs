using System;
using System.CodeDom.Compiler;
using System.ComponentModel;
using System.Diagnostics;
using System.Drawing;
using System.Globalization;
using System.Resources;
using System.Runtime.CompilerServices;
namespace GB698Ctl.Properties
{
	[GeneratedCode("System.Resources.Tools.StronglyTypedResourceBuilder", "2.0.0.0"), DebuggerNonUserCode, CompilerGenerated]
	internal class Resources
	{
		private static ResourceManager resourceMan;
		private static CultureInfo resourceCulture;
		[EditorBrowsable(EditorBrowsableState.Advanced)]
		internal static ResourceManager ResourceManager
		{
			get
			{
				if (object.ReferenceEquals(Resources.resourceMan, null))
				{
					ResourceManager resourceManager = new ResourceManager("GB698Ctl.Properties.Resources", typeof(Resources).Assembly);
					Resources.resourceMan = resourceManager;
				}
				return Resources.resourceMan;
			}
		}
		[EditorBrowsable(EditorBrowsableState.Advanced)]
		internal static CultureInfo Culture
		{
			get
			{
				return Resources.resourceCulture;
			}
			set
			{
				Resources.resourceCulture = value;
			}
		}
		internal static Bitmap NONE
		{
			get
			{
				object @object = Resources.ResourceManager.GetObject("NONE", Resources.resourceCulture);
				return (Bitmap)@object;
			}
		}
		internal static Bitmap RIGHT
		{
			get
			{
				object @object = Resources.ResourceManager.GetObject("RIGHT", Resources.resourceCulture);
				return (Bitmap)@object;
			}
		}
		internal static Bitmap WRONG
		{
			get
			{
				object @object = Resources.ResourceManager.GetObject("WRONG", Resources.resourceCulture);
				return (Bitmap)@object;
			}
		}
		internal static byte[] CONFIG
		{
			get
			{
				object @object = Resources.ResourceManager.GetObject("Config", Resources.resourceCulture);
				return (byte[])@object;
			}
		}
		internal static byte[] sn
		{
			get
			{
				object @object = Resources.ResourceManager.GetObject("sn", Resources.resourceCulture);
				return (byte[])@object;
			}
		}
		internal static byte[] busy
		{
			get
			{
				object @object = Resources.ResourceManager.GetObject("busy", Resources.resourceCulture);
				return (byte[])@object;
			}
		}
		internal static Bitmap minus
		{
			get
			{
				object @object = Resources.ResourceManager.GetObject("minus", Resources.resourceCulture);
				return (Bitmap)@object;
			}
		}
		internal static Bitmap plus
		{
			get
			{
				object @object = Resources.ResourceManager.GetObject("plus", Resources.resourceCulture);
				return (Bitmap)@object;
			}
		}
		internal static Bitmap VS2010ThemeBackground
		{
			get
			{
				object @object = Resources.ResourceManager.GetObject("VS2010ThemeBackground", Resources.resourceCulture);
				return (Bitmap)@object;
			}
		}
		internal Resources()
		{
		}
	}
}
