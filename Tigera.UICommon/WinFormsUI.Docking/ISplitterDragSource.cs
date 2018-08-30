using System;
using System.Drawing;
namespace WinFormsUI.Docking
{
	internal interface ISplitterDragSource : IDragSource
	{
		bool IsVertical
		{
			get;
		}
		Rectangle DragLimitBounds
		{
			get;
		}
		void BeginDrag(Rectangle rectSplitter);
		void EndDrag();
		void MoveSplitter(int offset);
	}
}
