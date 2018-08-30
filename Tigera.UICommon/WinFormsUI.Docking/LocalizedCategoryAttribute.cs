using System;
using System.ComponentModel;
namespace WinFormsUI.Docking
{
	[AttributeUsage(AttributeTargets.All)]
	internal sealed class LocalizedCategoryAttribute : CategoryAttribute
	{
		public LocalizedCategoryAttribute(string key) : base(key)
		{
		}
		protected override string GetLocalizedString(string key)
		{
			return ResourceHelper.GetString(key);
		}
	}
}
