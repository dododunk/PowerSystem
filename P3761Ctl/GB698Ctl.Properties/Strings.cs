using System;
using System.CodeDom.Compiler;
using System.ComponentModel;
using System.Diagnostics;
using System.Globalization;
using System.Resources;
using System.Runtime.CompilerServices;
namespace GB698Ctl.Properties
{
	[GeneratedCode("System.Resources.Tools.StronglyTypedResourceBuilder", "4.0.0.0"), DebuggerNonUserCode, CompilerGenerated]
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
					ResourceManager resourceManager = new ResourceManager("GB698Ctl.Properties.Strings", typeof(Strings).Assembly);
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
		internal static string Description
		{
			get
			{
				return Strings.ResourceManager.GetString("Description", Strings.resourceCulture);
			}
		}
		internal Strings()
		{
		}
	}
}
