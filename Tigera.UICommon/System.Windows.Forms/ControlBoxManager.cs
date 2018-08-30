using System;
using System.Drawing;
namespace System.Windows.Forms
{
	internal class ControlBoxManager : IDisposable
	{
		private SkinForm _owner;
		private bool _mouseDown;
		private ControlBoxState _closBoxState;
		private ControlBoxState _minimizeBoxState;
		private ControlBoxState _maximizeBoxState;
		public bool CloseBoxVisibale
		{
			get
			{
				return this._owner.ControlBox;
			}
		}
		public bool MaximizeBoxVisibale
		{
			get
			{
				return this._owner.ControlBox && this._owner.MaximizeBox;
			}
		}
		public bool MinimizeBoxVisibale
		{
			get
			{
				return this._owner.ControlBox && this._owner.MinimizeBox;
			}
		}
		public Rectangle CloseBoxRect
		{
			get
			{
				Rectangle result;
				if (this.CloseBoxVisibale)
				{
					Point controlBoxOffset = this.ControlBoxOffset;
					Size closeBoxSize = this._owner.CloseBoxSize;
					result = new Rectangle(checked(this._owner.Width - controlBoxOffset.X - closeBoxSize.Width), controlBoxOffset.Y, closeBoxSize.Width, closeBoxSize.Height);
				}
				else
				{
					result = Rectangle.Empty;
				}
				return result;
			}
		}
		public Rectangle MaximizeBoxRect
		{
			get
			{
				Rectangle result;
				if (this.MaximizeBoxVisibale)
				{
					Point controlBoxOffset = this.ControlBoxOffset;
					Size maximizeBoxSize = this._owner.MaximizeBoxSize;
					result = new Rectangle(checked(this.CloseBoxRect.X - this.ControlBoxSpace - maximizeBoxSize.Width), controlBoxOffset.Y, maximizeBoxSize.Width, maximizeBoxSize.Height);
				}
				else
				{
					result = Rectangle.Empty;
				}
				return result;
			}
		}
		public Rectangle MinimizeBoxRect
		{
			get
			{
				Rectangle result;
				if (this.MinimizeBoxVisibale)
				{
					Point controlBoxOffset = this.ControlBoxOffset;
					Size minimizeBoxSize = this._owner.MinimizeBoxSize;
					int x = checked(this.MaximizeBoxVisibale ? (this.MaximizeBoxRect.X - this.ControlBoxSpace - minimizeBoxSize.Width) : (this.CloseBoxRect.X - this.ControlBoxSpace - minimizeBoxSize.Width));
					result = new Rectangle(x, controlBoxOffset.Y, minimizeBoxSize.Width, minimizeBoxSize.Height);
				}
				else
				{
					result = Rectangle.Empty;
				}
				return result;
			}
		}
		public ControlBoxState CloseBoxState
		{
			get
			{
				return this._closBoxState;
			}
			protected set
			{
				if (this._closBoxState != value)
				{
					this._closBoxState = value;
					if (this._owner != null)
					{
						this.Invalidate(this.CloseBoxRect);
					}
				}
			}
		}
		public ControlBoxState MinimizeBoxState
		{
			get
			{
				return this._minimizeBoxState;
			}
			protected set
			{
				if (this._minimizeBoxState != value)
				{
					this._minimizeBoxState = value;
					if (this._owner != null)
					{
						this.Invalidate(this.MinimizeBoxRect);
					}
				}
			}
		}
		public ControlBoxState MaximizeBoxState
		{
			get
			{
				return this._maximizeBoxState;
			}
			protected set
			{
				if (this._maximizeBoxState != value)
				{
					this._maximizeBoxState = value;
					if (this._owner != null)
					{
						this.Invalidate(this.MaximizeBoxRect);
					}
				}
			}
		}
		internal Point ControlBoxOffset
		{
			get
			{
				return this._owner.ControlBoxOffset;
			}
		}
		internal int ControlBoxSpace
		{
			get
			{
				return this._owner.ControlBoxSpace;
			}
		}
		public ControlBoxManager(SkinForm owner)
		{
			this._owner = owner;
		}
		public void ProcessMouseOperate(Point mousePoint, MouseOperate operate)
		{
			if (this._owner.ControlBox)
			{
				Rectangle closeBoxRect = this.CloseBoxRect;
				Rectangle minimizeBoxRect = this.MinimizeBoxRect;
				Rectangle maximizeBoxRect = this.MaximizeBoxRect;
				bool closeBoxVisibale = this.CloseBoxVisibale;
				bool minimizeBoxVisibale = this.MinimizeBoxVisibale;
				bool maximizeBoxVisibale = this.MaximizeBoxVisibale;
				switch (operate)
				{
				case MouseOperate.Move:
					this.ProcessMouseMove(mousePoint, closeBoxRect, minimizeBoxRect, maximizeBoxRect, closeBoxVisibale, minimizeBoxVisibale, maximizeBoxVisibale);
					break;

				case MouseOperate.Down:
					this.ProcessMouseDown(mousePoint, closeBoxRect, minimizeBoxRect, maximizeBoxRect, closeBoxVisibale, minimizeBoxVisibale, maximizeBoxVisibale);
					break;

				case MouseOperate.Up:
					this.ProcessMouseUP(mousePoint, closeBoxRect, minimizeBoxRect, maximizeBoxRect, closeBoxVisibale, minimizeBoxVisibale, maximizeBoxVisibale);
					break;

				case MouseOperate.Leave:
					this.ProcessMouseLeave(closeBoxVisibale, minimizeBoxVisibale, maximizeBoxVisibale);
					break;
				}
			}
		}
		private void ProcessMouseMove(Point mousePoint, Rectangle closeBoxRect, Rectangle minimizeBoxRect, Rectangle maximizeBoxRect, bool closeBoxVisibale, bool minimizeBoxVisibale, bool maximizeBoxVisibale)
		{
			string text = string.Empty;
			bool flag = true;
			if (closeBoxVisibale)
			{
				if (closeBoxRect.Contains(mousePoint))
				{
					flag = false;
					if (!this._mouseDown)
					{
						if (this.CloseBoxState != ControlBoxState.Hover)
						{
							text = "关闭";
						}
						this.CloseBoxState = ControlBoxState.Hover;
					}
					else
					{
						if (this.CloseBoxState == ControlBoxState.PressedLeave)
						{
							this.CloseBoxState = ControlBoxState.Pressed;
						}
					}
				}
				else
				{
					if (!this._mouseDown)
					{
						this.CloseBoxState = ControlBoxState.Normal;
					}
					else
					{
						if (this.CloseBoxState == ControlBoxState.Pressed)
						{
							this.CloseBoxState = ControlBoxState.PressedLeave;
						}
					}
				}
			}
			if (minimizeBoxVisibale)
			{
				if (minimizeBoxRect.Contains(mousePoint))
				{
					flag = false;
					if (!this._mouseDown)
					{
						if (this.MinimizeBoxState != ControlBoxState.Hover)
						{
							text = "最小化";
						}
						this.MinimizeBoxState = ControlBoxState.Hover;
					}
					else
					{
						if (this.MinimizeBoxState == ControlBoxState.PressedLeave)
						{
							this.MinimizeBoxState = ControlBoxState.Pressed;
						}
					}
				}
				else
				{
					if (!this._mouseDown)
					{
						this.MinimizeBoxState = ControlBoxState.Normal;
					}
					else
					{
						if (this.MinimizeBoxState == ControlBoxState.Pressed)
						{
							this.MinimizeBoxState = ControlBoxState.PressedLeave;
						}
					}
				}
			}
			if (maximizeBoxVisibale)
			{
				if (maximizeBoxRect.Contains(mousePoint))
				{
					flag = false;
					if (!this._mouseDown)
					{
						if (this.MaximizeBoxState != ControlBoxState.Hover)
						{
							text = ((this._owner.WindowState == FormWindowState.Maximized) ? "还原" : "最大化");
						}
						this.MaximizeBoxState = ControlBoxState.Hover;
					}
					else
					{
						if (this.MaximizeBoxState == ControlBoxState.PressedLeave)
						{
							this.MaximizeBoxState = ControlBoxState.Pressed;
						}
					}
				}
				else
				{
					if (!this._mouseDown)
					{
						this.MaximizeBoxState = ControlBoxState.Normal;
					}
					else
					{
						if (this.MaximizeBoxState == ControlBoxState.Pressed)
						{
							this.MaximizeBoxState = ControlBoxState.PressedLeave;
						}
					}
				}
			}
			if (text != string.Empty)
			{
				this.HideToolTip();
				this.ShowTooTip(text);
			}
			if (flag)
			{
				this.HideToolTip();
			}
		}
		private void ProcessMouseDown(Point mousePoint, Rectangle closeBoxRect, Rectangle minimizeBoxRect, Rectangle maximizeBoxRect, bool closeBoxVisibale, bool minimizeBoxVisibale, bool maximizeBoxVisibale)
		{
			this._mouseDown = true;
			if (closeBoxVisibale)
			{
				if (closeBoxRect.Contains(mousePoint))
				{
					this.CloseBoxState = ControlBoxState.Pressed;
					return;
				}
			}
			if (minimizeBoxVisibale)
			{
				if (minimizeBoxRect.Contains(mousePoint))
				{
					this.MinimizeBoxState = ControlBoxState.Pressed;
					return;
				}
			}
			if (maximizeBoxVisibale)
			{
				if (maximizeBoxRect.Contains(mousePoint))
				{
					this.MaximizeBoxState = ControlBoxState.Pressed;
				}
			}
		}
		private void ProcessMouseUP(Point mousePoint, Rectangle closeBoxRect, Rectangle minimizeBoxRect, Rectangle maximizeBoxRect, bool closeBoxVisibale, bool minimizeBoxVisibale, bool maximizeBoxVisibale)
		{
			this._mouseDown = false;
			if (closeBoxVisibale)
			{
				if (closeBoxRect.Contains(mousePoint))
				{
					if (this.CloseBoxState == ControlBoxState.Pressed)
					{
						this._owner.Close();
						this.CloseBoxState = ControlBoxState.Normal;
						return;
					}
				}
				this.CloseBoxState = ControlBoxState.Normal;
			}
			if (minimizeBoxVisibale)
			{
				if (minimizeBoxRect.Contains(mousePoint))
				{
					if (this.MinimizeBoxState == ControlBoxState.Pressed)
					{
						this._owner.WindowState = FormWindowState.Minimized;
						this.MinimizeBoxState = ControlBoxState.Normal;
						return;
					}
				}
				this.MinimizeBoxState = ControlBoxState.Normal;
			}
			if (maximizeBoxVisibale)
			{
				if (maximizeBoxRect.Contains(mousePoint))
				{
					if (this.MaximizeBoxState == ControlBoxState.Pressed)
					{
						bool flag = this._owner.WindowState == FormWindowState.Maximized;
						if (flag)
						{
							this._owner.WindowState = FormWindowState.Normal;
						}
						else
						{
							this._owner.WindowState = FormWindowState.Maximized;
						}
						this.MaximizeBoxState = ControlBoxState.Normal;
						return;
					}
				}
				this.MaximizeBoxState = ControlBoxState.Normal;
			}
		}
		private void ProcessMouseLeave(bool closeBoxVisibale, bool minimizeBoxVisibale, bool maximizeBoxVisibale)
		{
			if (closeBoxVisibale)
			{
				if (this.CloseBoxState == ControlBoxState.Pressed)
				{
					this.CloseBoxState = ControlBoxState.PressedLeave;
				}
				else
				{
					this.CloseBoxState = ControlBoxState.Normal;
				}
			}
			if (minimizeBoxVisibale)
			{
				if (this.MinimizeBoxState == ControlBoxState.Pressed)
				{
					this.MinimizeBoxState = ControlBoxState.PressedLeave;
				}
				else
				{
					this.MinimizeBoxState = ControlBoxState.Normal;
				}
			}
			if (maximizeBoxVisibale)
			{
				if (this.MaximizeBoxState == ControlBoxState.Pressed)
				{
					this.MaximizeBoxState = ControlBoxState.PressedLeave;
				}
				else
				{
					this.MaximizeBoxState = ControlBoxState.Normal;
				}
			}
			this.HideToolTip();
		}
		private void Invalidate(Rectangle rect)
		{
			this._owner.Invalidate(rect);
		}
		private void ShowTooTip(string toolTipText)
		{
			if (this._owner != null)
			{
				this._owner.ToolTip.Active = true;
				this._owner.ToolTip.SetToolTip(this._owner, toolTipText);
			}
		}
		private void HideToolTip()
		{
			if (this._owner != null)
			{
				this._owner.ToolTip.Active = false;
			}
		}
		public void Dispose()
		{
			this._owner = null;
		}
	}
}
