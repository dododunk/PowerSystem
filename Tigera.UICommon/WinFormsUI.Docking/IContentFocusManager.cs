using System;
namespace WinFormsUI.Docking
{
	internal interface IContentFocusManager
	{
		void Activate(IDockContent content);
		void GiveUpFocus(IDockContent content);
		void AddToList(IDockContent content);
		void RemoveFromList(IDockContent content);
	}
}
