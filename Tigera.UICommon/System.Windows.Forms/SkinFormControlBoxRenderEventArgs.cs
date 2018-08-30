using System;
using System.Drawing;
namespace System.Windows.Forms
{
	public class SkinFormControlBoxRenderEventArgs : PaintEventArgs
	{
		private SkinForm _form;
		private bool _active;
		private ControlBoxState _controlBoxState;
		private ControlBoxStyle _controlBoxStyle;
		public SkinForm Form
		{
			get
			{
				return this._form;
			}
		}
		public bool Active
		{
			get
			{
				return this._active;
			}
		}
		public ControlBoxStyle ControlBoxStyle
		{
			get
			{
				return this._controlBoxStyle;
			}
		}
		public ControlBoxState ControlBoxtate
		{
			get
			{
				return this._controlBoxState;
			}
		}
		public SkinFormControlBoxRenderEventArgs(SkinForm form, Graphics graphics, Rectangle clipRect, bool active, ControlBoxStyle controlBoxStyle, ControlBoxState controlBoxState) : base(graphics, clipRect)
		{
			this._form = form;
			this._active = active;
			this._controlBoxState = controlBoxState;
			this._controlBoxStyle = controlBoxStyle;
		}
	}
}
