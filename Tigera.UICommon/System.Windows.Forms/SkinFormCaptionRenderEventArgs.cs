using System;
using System.Drawing;
namespace System.Windows.Forms
{
	public class SkinFormCaptionRenderEventArgs : PaintEventArgs
	{
		private SkinForm _skinForm;
		private bool _active;
		public SkinForm SkinForm
		{
			get
			{
				return this._skinForm;
			}
		}
		public bool Active
		{
			get
			{
				return this._active;
			}
		}
		public SkinFormCaptionRenderEventArgs(SkinForm skinForm, Graphics g, Rectangle clipRect, bool active) : base(g, clipRect)
		{
			this._skinForm = skinForm;
			this._active = active;
		}
	}
}
