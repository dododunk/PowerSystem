using System;
using System.ComponentModel;
using System.Globalization;
namespace WinFormsUI.Docking
{
	public class AutoHideStripConverter : ExpandableObjectConverter
	{
		public override bool CanConvertTo(ITypeDescriptorContext context, Type destinationType)
		{
			return destinationType == typeof(AutoHideStripSkin) || base.CanConvertTo(context, destinationType);
		}
		public override object ConvertTo(ITypeDescriptorContext context, CultureInfo culture, object value, Type destinationType)
		{
			object result;
			if (destinationType == typeof(string) && value is AutoHideStripSkin)
			{
				result = "AutoHideStripSkin";
			}
			else
			{
				result = base.ConvertTo(context, culture, value, destinationType);
			}
			return result;
		}
	}
}
