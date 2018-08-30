using System;
using System.Drawing;
namespace System.Windows.Forms
{
	public class SkinFormBackgroundRenderEventArgs : PaintEventArgs
	{
		private SkinForm _skinForm;
		public SkinForm SkinForm
		{
			get
			{
				return this._skinForm;
			}
		}
		public SkinFormBackgroundRenderEventArgs(SkinForm skinForm, Graphics g, Rectangle clipRect) : base(g, clipRect)
		{
			this._skinForm = skinForm;
		}
	}
}
