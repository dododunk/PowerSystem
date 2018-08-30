using System;
using System.ComponentModel;
using System.Globalization;
namespace WinFormsUI.Docking
{
	public class DockPanelSkinConverter : ExpandableObjectConverter
	{
		public override bool CanConvertTo(ITypeDescriptorContext context, Type destinationType)
		{
			return destinationType == typeof(DockPanelSkin) || base.CanConvertTo(context, destinationType);
		}
		public override object ConvertTo(ITypeDescriptorContext context, CultureInfo culture, object value, Type destinationType)
		{
			object result;
			if (destinationType == typeof(string) && value is DockPanelSkin)
			{
				result = "DockPanelSkin";
			}
			else
			{
				result = base.ConvertTo(context, culture, value, destinationType);
			}
			return result;
		}
	}
}
