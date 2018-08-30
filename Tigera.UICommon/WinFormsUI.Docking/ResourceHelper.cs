using System;
using System.Resources;
namespace WinFormsUI.Docking
{
	internal static class ResourceHelper
	{
		private static ResourceManager _resourceManager = null;
		private static ResourceManager ResourceManager
		{
			get
			{
				if (ResourceHelper._resourceManager == null)
				{
					ResourceHelper._resourceManager = new ResourceManager("WinFormsUI.Docking.Strings", typeof(ResourceHelper).Assembly);
				}
				return ResourceHelper._resourceManager;
			}
		}
		public static string GetString(string name)
		{
			return ResourceHelper.ResourceManager.GetString(name);
		}
	}
}
