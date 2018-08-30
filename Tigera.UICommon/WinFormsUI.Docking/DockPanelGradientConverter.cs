using System;
using System.ComponentModel;
using System.Globalization;
namespace WinFormsUI.Docking
{
	public class DockPanelGradientConverter : ExpandableObjectConverter
	{
		public override bool CanConvertTo(ITypeDescriptorContext context, Type destinationType)
		{
			return destinationType == typeof(DockPanelGradient) || base.CanConvertTo(context, destinationType);
		}
		public override object ConvertTo(ITypeDescriptorContext context, CultureInfo culture, object value, Type destinationType)
		{
			object result;
			if (destinationType == typeof(string) && value is DockPanelGradient)
			{
				result = "DockPanelGradient";
			}
			else
			{
				result = base.ConvertTo(context, culture, value, destinationType);
			}
			return result;
		}
	}
}
