using System;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Windows.Forms;
namespace EasyRender_VS2010Theme
{
	public class EasyRender : ToolStripProfessionalRenderer
	{
		private IToolstrip _tsManager = null;
		private IButton _btnManager = null;
		private IToolstripControls _tsCtrlManager = null;
		private IPanel _pManager = null;
		private ISplitButton _sBtnManager = null;
		private IStatusBar _sBarManager = null;
		private IMenustrip _mnuManager = null;
		private IDropDownButton _dBtnManager = null;
		private bool _smoothText = true;
		private Color _overrideColor = Color.FromArgb(23, 23, 23);
		private bool _overrideText = true;
		[ReadOnly(true)]
		public IToolstrip Toolstrip
		{
			get
			{
				return this._tsManager;
			}
		}
		[ReadOnly(true)]
		public IButton ToolstripButton
		{
			get
			{
				return this._btnManager;
			}
		}
		[ReadOnly(true)]
		public IToolstripControls ToolstripControls
		{
			get
			{
				return this._tsCtrlManager;
			}
		}
		[ReadOnly(true)]
		public IPanel Panels
		{
			get
			{
				return this._pManager;
			}
		}
		[ReadOnly(true)]
		public ISplitButton SplitButton
		{
			get
			{
				return this._sBtnManager;
			}
		}
		[ReadOnly(true)]
		public IStatusBar StatusBar
		{
			get
			{
				return this._sBarManager;
			}
		}
		public bool SmoothText
		{
			get
			{
				return this._smoothText;
			}
			set
			{
				this._smoothText = value;
			}
		}
		public Color OverrideColor
		{
			get
			{
				return this._overrideColor;
			}
			set
			{
				this._overrideColor = value;
			}
		}
		public bool AlterColor
		{
			get
			{
				return this._overrideText;
			}
			set
			{
				this._overrideText = value;
			}
		}
		public EasyRender()
		{
			this._tsManager = new IToolstrip();
			this._btnManager = new IButton();
			this._dBtnManager = new IDropDownButton();
			this._tsCtrlManager = new IToolstripControls();
			this._pManager = new IPanel();
			this._sBtnManager = new ISplitButton();
			this._sBarManager = new IStatusBar();
			this._mnuManager = new IMenustrip();
		}
		private GraphicsPath CreateDrawingPath(Rectangle Area, float Curve)
		{
			GraphicsPath graphicsPath = new GraphicsPath();
			graphicsPath.AddLine((float)Area.Left + Curve, (float)Area.Top, (float)Area.Right - Curve, (float)Area.Top);
			graphicsPath.AddLine((float)Area.Right - Curve, (float)Area.Top, (float)Area.Right, (float)Area.Top + Curve);
			graphicsPath.AddLine((float)Area.Right, (float)Area.Top + Curve, (float)Area.Right, (float)Area.Bottom - Curve);
			graphicsPath.AddLine((float)Area.Right, (float)Area.Bottom - Curve, (float)Area.Right - Curve, (float)Area.Bottom);
			graphicsPath.AddLine((float)Area.Right - Curve, (float)Area.Bottom, (float)Area.Left + Curve, (float)Area.Bottom);
			graphicsPath.AddLine((float)Area.Left + Curve, (float)Area.Bottom, (float)Area.Left, (float)Area.Bottom - Curve);
			graphicsPath.AddLine((float)Area.Left, (float)Area.Bottom - Curve, (float)Area.Left, (float)Area.Top + Curve);
			graphicsPath.AddLine((float)Area.Left, (float)Area.Top + Curve, (float)Area.Left + Curve, (float)Area.Top);
			return graphicsPath;
		}
		private GraphicsPath CreateTrianglePath(Rectangle Bounds, int Size, ArrowDirection Direction)
		{
			GraphicsPath graphicsPath = new GraphicsPath();
			checked
			{
				int num;
				int num2;
				int num3;
				int num4;
				if (Direction == ArrowDirection.Left || Direction == ArrowDirection.Right)
				{
					num = Bounds.Right - (Bounds.Width - Size) / 2;
					num2 = Bounds.Y + Bounds.Height / 2;
					num3 = Size;
					num4 = 0;
				}
				else
				{
					num = Bounds.X + Bounds.Width / 2;
					num2 = Bounds.Bottom - (Bounds.Height - (Size - 1)) / 2;
					num3 = Size - 1;
					num4 = Size - 2;
				}
				if (Direction != ArrowDirection.Left)
				{
					switch (Direction)
					{
					case ArrowDirection.Right:
						graphicsPath.AddLine(num, num2, num - num3, num2 - num3);
						graphicsPath.AddLine(num - num3, num2 - num3, num - num3, num2 + num3);
						graphicsPath.AddLine(num - num3, num2 + num3, num, num2);
						break;

					case ArrowDirection.Down:
						graphicsPath.AddLine(num + num4, num2 - num4, num - num4, num2 - num4);
						graphicsPath.AddLine(num - num4, num2 - num4, num, num2);
						graphicsPath.AddLine(num, num2, num + num4, num2 - num4);
						break;
					}
				}
				else
				{
					graphicsPath.AddLine(num - num3, num2, num, num2 - num3);
					graphicsPath.AddLine(num, num2 - num3, num, num2 + num3);
					graphicsPath.AddLine(num, num2 + num3, num - num3, num2);
				}
				return graphicsPath;
			}
		}
		private Color[] GetButtonBackColor(ToolStripButton Item, ButtonType Type)
		{
			Color[] array = new Color[2];
			if (!Item.Selected && !Item.Pressed && !Item.Checked)
			{
				array[0] = Color.Transparent;
				array[1] = Color.Transparent;
			}
			else
			{
				if (Item.Selected && !Item.Pressed && !Item.Checked)
				{
					array[0] = this._btnManager.HoverBackgroundTop;
					array[1] = this._btnManager.HoverBackgroundBottom;
				}
				else
				{
					array[0] = this._btnManager.ClickBackgroundTop;
					array[1] = this._btnManager.ClickBackgroundBottom;
				}
			}
			return array;
		}
		private Color[] GetButtonBackColor(ToolStripSplitButton Item, ButtonType Type)
		{
			Color[] array = new Color[2];
			if (!Item.Selected && !Item.ButtonPressed && !Item.DropDownButtonPressed)
			{
				array[0] = Color.Transparent;
				array[1] = Color.Transparent;
			}
			else
			{
				if (Item.Selected && !Item.ButtonPressed && !Item.DropDownButtonPressed)
				{
					array[0] = this._sBtnManager.HoverBackgroundTop;
					array[1] = this._sBtnManager.HoverBackgroundBottom;
				}
				else
				{
					if (Item.ButtonPressed)
					{
						array[0] = this._sBtnManager.ClickBackgroundTop;
						array[1] = this._sBtnManager.ClickBackgroundBottom;
					}
					else
					{
						if (Item.DropDownButtonPressed)
						{
							array[0] = this._mnuManager.MenustripButtonBackground;
							array[1] = this._mnuManager.MenustripButtonBackground;
						}
					}
				}
			}
			return array;
		}
		private Color[] GetButtonBackColor(ToolStripMenuItem Item, ButtonType Type)
		{
			Color[] array = new Color[2];
			if (!Item.Selected && !Item.Pressed && !Item.Checked)
			{
				array[0] = Color.Transparent;
				array[1] = Color.Transparent;
			}
			else
			{
				if ((Item.Selected || Item.Pressed) && !Item.Checked)
				{
					if (Item.Pressed && Item.OwnerItem == null)
					{
						array[0] = this._mnuManager.MenustripButtonBackground;
						array[1] = this._mnuManager.MenustripButtonBackground;
					}
					else
					{
						array[0] = this._mnuManager.Items.HoverBackgroundTop;
						array[1] = this._mnuManager.Items.HoverBackgroundBottom;
					}
				}
				else
				{
					array[0] = this._mnuManager.Items.ClickBackgroundTop;
					array[1] = this._mnuManager.Items.ClickBackgroundBottom;
				}
			}
			return array;
		}
		private Color[] GetButtonBackColor(ToolStripDropDownButton Item, ButtonType Type)
		{
			Color[] array = new Color[2];
			if (!Item.Selected && !Item.Pressed)
			{
				array[0] = Color.Transparent;
				array[1] = Color.Transparent;
			}
			else
			{
				if (Item.Selected && !Item.Pressed)
				{
					array[0] = this._dBtnManager.HoverBackgroundTop;
					array[1] = this._dBtnManager.HoverBackgroundBottom;
				}
				else
				{
					array[0] = this._mnuManager.MenustripButtonBackground;
					array[1] = this._mnuManager.MenustripButtonBackground;
				}
			}
			return array;
		}
		private Blend GetBlend(ToolStripItem TSItem, ButtonType Type)
		{
			Blend result = null;
			if (Type == ButtonType.NormalButton)
			{
				ToolStripButton toolStripButton = (ToolStripButton)TSItem;
				if (toolStripButton.Selected && !toolStripButton.Checked && !toolStripButton.Pressed && (this._btnManager.BlendOptions & BlendRender.Hover) == BlendRender.Hover)
				{
					result = this._btnManager.BackgroundBlend;
				}
				else
				{
					if (toolStripButton.Pressed && !toolStripButton.Checked && (this._btnManager.BlendOptions & BlendRender.Click) == BlendRender.Click)
					{
						result = this._btnManager.BackgroundBlend;
					}
					else
					{
						if (toolStripButton.Checked && (this._btnManager.BlendOptions & BlendRender.Check) == BlendRender.Check)
						{
							result = this._btnManager.BackgroundBlend;
						}
					}
				}
			}
			if (Type == ButtonType.DropDownButton)
			{
				ToolStripDropDownButton toolStripDropDownButton = (ToolStripDropDownButton)TSItem;
				if (toolStripDropDownButton.Selected && !toolStripDropDownButton.Pressed && (this._btnManager.BlendOptions & BlendRender.Hover) == BlendRender.Hover)
				{
					result = this._btnManager.BackgroundBlend;
				}
			}
			else
			{
				if (Type == ButtonType.MenuItem)
				{
					ToolStripMenuItem toolStripMenuItem = (ToolStripMenuItem)TSItem;
					if (toolStripMenuItem.Selected && !toolStripMenuItem.Checked && !toolStripMenuItem.Pressed && (this._btnManager.BlendOptions & BlendRender.Hover) == BlendRender.Hover)
					{
						result = this._mnuManager.Items.BackgroundBlend;
					}
					else
					{
						if (toolStripMenuItem.Pressed && !toolStripMenuItem.Checked && (this._btnManager.BlendOptions & BlendRender.Click) == BlendRender.Click)
						{
							result = this._mnuManager.Items.BackgroundBlend;
						}
						else
						{
							if (toolStripMenuItem.Checked && (this._btnManager.BlendOptions & BlendRender.Check) == BlendRender.Check)
							{
								result = this._mnuManager.Items.BackgroundBlend;
							}
						}
					}
				}
				else
				{
					if (Type == ButtonType.SplitButton)
					{
						ToolStripSplitButton toolStripSplitButton = (ToolStripSplitButton)TSItem;
						if (toolStripSplitButton.Selected && !toolStripSplitButton.ButtonPressed && !toolStripSplitButton.DropDownButtonPressed && (this._sBtnManager.BlendOptions & BlendRender.Hover) == BlendRender.Hover)
						{
							result = this._sBtnManager.BackgroundBlend;
						}
						else
						{
							if (toolStripSplitButton.ButtonPressed && !toolStripSplitButton.DropDownButtonPressed && (this._sBtnManager.BlendOptions & BlendRender.Click) == BlendRender.Click)
							{
								result = this._sBtnManager.BackgroundBlend;
							}
						}
					}
				}
			}
			return result;
		}
		public void PaintBackground(Graphics Link, Rectangle Boundary, Brush Brush)
		{
			Link.FillRectangle(Brush, Boundary);
		}
		public void PaintBackground(Graphics Link, Rectangle Boundary, Color Top, Color Bottom)
		{
			this.PaintBackground(Link, Boundary, Top, Bottom, 90f, null);
		}
		public void PaintBackground(Graphics Link, Rectangle Boundary, Color Top, Color Bottom, float Angle)
		{
			this.PaintBackground(Link, Boundary, Top, Bottom, Angle, null);
		}
		public void PaintBackground(Graphics Link, Rectangle Boundary, Color Top, Color Bottom, float Angle, Blend Blend)
		{
			if (Angle == 0f)
			{
				Angle = 90f;
			}
			using (LinearGradientBrush linearGradientBrush = new LinearGradientBrush(Boundary, Top, Bottom, Angle))
			{
				if (Blend != null)
				{
					linearGradientBrush.Blend = Blend;
				}
				Link.FillRectangle(linearGradientBrush, Boundary);
				linearGradientBrush.Dispose();
			}
		}
		public void PaintBorder(Graphics Link, GraphicsPath Path, Brush Brush)
		{
			Link.DrawPath(new Pen(Brush), Path);
		}
		public void PaintBorder(Graphics Link, GraphicsPath Path, Rectangle Area, Color Top, Color Bottom)
		{
			this.PaintBorder(Link, Path, Area, Top, Bottom, 90f, null);
		}
		public void PaintBorder(Graphics Link, GraphicsPath Path, Rectangle Area, Color Top, Color Bottom, float Angle)
		{
			this.PaintBorder(Link, Path, Area, Top, Bottom, Angle, null);
		}
		public void PaintBorder(Graphics Link, GraphicsPath Path, Rectangle Area, Color Top, Color Bottom, float Angle, Blend Blend)
		{
			if (Angle == 0f)
			{
				Angle = 90f;
			}
			using (LinearGradientBrush linearGradientBrush = new LinearGradientBrush(Area, Top, Bottom, Angle))
			{
				if (Blend != null)
				{
					linearGradientBrush.Blend = Blend;
				}
				Link.DrawPath(new Pen(linearGradientBrush), Path);
				linearGradientBrush.Dispose();
			}
		}
		public void IDrawToolstripButton(ToolStripButton Item, Graphics Link, ToolStrip Parent)
		{
			Rectangle rectangle = new Rectangle(new Point(0, 0), checked(new Size(Item.Bounds.Size.Width - 1, Item.Bounds.Size.Height - 1)));
			Blend blend = this.GetBlend(Item, ButtonType.NormalButton);
			Color[] buttonBackColor = this.GetButtonBackColor(Item, ButtonType.NormalButton);
			using (GraphicsPath graphicsPath = this.CreateDrawingPath(rectangle, (float)this._btnManager.Curve))
			{
				Link.SetClip(graphicsPath);
				this.PaintBackground(Link, rectangle, buttonBackColor[0], buttonBackColor[1], this._btnManager.BackgroundAngle, blend);
				Link.ResetClip();
				Link.SmoothingMode = SmoothingMode.AntiAlias;
				using (GraphicsPath graphicsPath2 = this.CreateDrawingPath(rectangle, (float)this._btnManager.Curve))
				{
					this.PaintBorder(Link, graphicsPath2, rectangle, this._btnManager.BorderTop, this._btnManager.BorderBottom, this._btnManager.BorderAngle, this._btnManager.BorderBlend);
					graphicsPath2.Dispose();
				}
				rectangle.Inflate(-1, -1);
				using (GraphicsPath graphicsPath3 = this.CreateDrawingPath(rectangle, (float)this._btnManager.Curve))
				{
					using (SolidBrush solidBrush = new SolidBrush(this._btnManager.InnerBorder))
					{
						this.PaintBorder(Link, graphicsPath3, solidBrush);
						solidBrush.Dispose();
					}
				}
				Link.SmoothingMode = SmoothingMode.Default;
			}
		}
		public void IDrawDropDownButton(ToolStripDropDownButton Item, Graphics Link, ToolStrip Parent)
		{
			Rectangle rectangle = new Rectangle(new Point(0, 0), checked(new Size(Item.Bounds.Size.Width - 1, Item.Bounds.Size.Height - 1)));
			Blend blend = this.GetBlend(Item, ButtonType.DropDownButton);
			Color[] buttonBackColor = this.GetButtonBackColor(Item, ButtonType.DropDownButton);
			using (GraphicsPath graphicsPath = this.CreateDrawingPath(rectangle, (float)this._btnManager.Curve))
			{
				Link.SetClip(graphicsPath);
				this.PaintBackground(Link, rectangle, buttonBackColor[0], buttonBackColor[1], this._btnManager.BackgroundAngle, blend);
				Link.ResetClip();
				Link.SmoothingMode = SmoothingMode.AntiAlias;
				using (GraphicsPath graphicsPath2 = this.CreateDrawingPath(rectangle, (float)this._btnManager.Curve))
				{
					this.PaintBorder(Link, graphicsPath2, rectangle, this._btnManager.BorderTop, this._btnManager.BorderBottom, this._btnManager.BorderAngle, this._btnManager.BorderBlend);
					graphicsPath2.Dispose();
				}
				if (!Item.Pressed)
				{
					rectangle.Inflate(-1, -1);
					using (GraphicsPath graphicsPath3 = this.CreateDrawingPath(rectangle, (float)this._dBtnManager.Curve))
					{
						using (SolidBrush solidBrush = new SolidBrush(this._dBtnManager.InnerBorder))
						{
							this.PaintBorder(Link, graphicsPath3, solidBrush);
							solidBrush.Dispose();
						}
					}
				}
				Link.SmoothingMode = SmoothingMode.Default;
			}
		}
		public void IDrawToolstripBackground(ToolStrip Item, Graphics Link, Rectangle Bounds)
		{
			Rectangle rectangle = checked(new Rectangle(0, 0, Bounds.Width - 1, Bounds.Height - 1));
			Link.SmoothingMode = SmoothingMode.None;
			using (GraphicsPath graphicsPath = this.CreateDrawingPath(rectangle, (float)this._tsManager.Curve))
			{
				Link.SetClip(graphicsPath);
				this.PaintBackground(Link, rectangle, this._tsManager.BackgroundTop, this._tsManager.BackgroundBottom, this._tsManager.BackgroundAngle, this._tsManager.BackgroundBlend);
				Link.ResetClip();
				graphicsPath.Dispose();
			}
		}
		public void IDrawToolstripSplitButton(ToolStripSplitButton Item, Graphics Link, ToolStrip Parent)
		{
			checked
			{
				if (Item.Selected || Item.DropDownButtonPressed || Item.ButtonPressed)
				{
					Rectangle rectangle = new Rectangle(new Point(0, 0), new Size(Item.Bounds.Size.Width - 1, Item.Bounds.Size.Height - 1));
					Blend blend = this.GetBlend(Item, ButtonType.SplitButton);
					Color[] array = new Color[]
					{
						this._sBtnManager.HoverBackgroundTop,
						this._sBtnManager.HoverBackgroundBottom
					};
					Color[] buttonBackColor = this.GetButtonBackColor(Item, ButtonType.SplitButton);
					using (GraphicsPath graphicsPath = this.CreateDrawingPath(rectangle, (float)this._sBtnManager.Curve))
					{
						Link.SetClip(graphicsPath);
						if (!Item.DropDownButtonPressed)
						{
							this.PaintBackground(Link, rectangle, array[0], array[1], this._sBtnManager.BackgroundAngle, blend);
						}
						else
						{
							this.PaintBackground(Link, rectangle, buttonBackColor[0], buttonBackColor[1]);
						}
						if (Item.ButtonPressed)
						{
							Rectangle boundary = new Rectangle(new Point(0, 0), new Size(Item.ButtonBounds.Width, Item.ButtonBounds.Height - 1));
							this.PaintBackground(Link, boundary, buttonBackColor[0], buttonBackColor[1], this._sBtnManager.BackgroundAngle, this._sBtnManager.BackgroundBlend);
						}
						Link.ResetClip();
						Link.SmoothingMode = SmoothingMode.AntiAlias;
						using (GraphicsPath graphicsPath2 = this.CreateDrawingPath(rectangle, (float)this._sBtnManager.Curve))
						{
							Color top = Item.DropDownButtonPressed ? this._mnuManager.MenustripButtonBorder : this._sBtnManager.BorderTop;
							Color bottom = Item.DropDownButtonPressed ? this._mnuManager.MenustripButtonBorder : this._sBtnManager.BorderBottom;
							this.PaintBorder(Link, graphicsPath2, rectangle, top, bottom, this._sBtnManager.BorderAngle, this._sBtnManager.BorderBlend);
							graphicsPath2.Dispose();
						}
						if (!Item.DropDownButtonPressed)
						{
							rectangle.Inflate(-1, -1);
							using (GraphicsPath graphicsPath3 = this.CreateDrawingPath(rectangle, (float)this._sBtnManager.Curve))
							{
								using (SolidBrush solidBrush = new SolidBrush(this._sBtnManager.InnerBorder))
								{
									this.PaintBorder(Link, graphicsPath3, solidBrush);
									Link.DrawRectangle(new Pen(this._sBtnManager.InnerBorder), new Rectangle(Item.ButtonBounds.Width, 1, 2, Item.ButtonBounds.Height - 3));
									solidBrush.Dispose();
								}
							}
							using (LinearGradientBrush linearGradientBrush = new LinearGradientBrush(new Rectangle(0, 0, 1, Item.Height), this._sBtnManager.BorderTop, this._sBtnManager.BorderBottom, this._sBtnManager.BackgroundAngle))
							{
								if (this._sBtnManager.BackgroundBlend != null)
								{
									linearGradientBrush.Blend = this._sBtnManager.BackgroundBlend;
								}
								Link.DrawLine(new Pen(linearGradientBrush), Item.ButtonBounds.Width + 1, 0, Item.ButtonBounds.Width + 1, Item.Height - 1);
								linearGradientBrush.Dispose();
							}
						}
						Link.SmoothingMode = SmoothingMode.Default;
					}
				}
				int num = 5;
				if (this._sBtnManager.ArrowDisplay == ArrowDisplay.Always || (this._sBtnManager.ArrowDisplay == ArrowDisplay.Hover && Item.Selected))
				{
					using (GraphicsPath graphicsPath4 = this.CreateTrianglePath(new Rectangle(Item.DropDownButtonBounds.Left + num / 2 - 1, Item.DropDownButtonBounds.Height / 2 - num / 2 - 3, num * 2, num * 2), num, ArrowDirection.Down))
					{
						Link.FillPath(new SolidBrush(this._sBtnManager.ArrowColor), graphicsPath4);
						graphicsPath4.Dispose();
					}
				}
			}
		}
		public void IDrawStatusbarBackground(StatusStrip Item, Graphics Link, Rectangle Bounds)
		{
			this.PaintBackground(Link, Bounds, this._sBarManager.BackgroundTop, this._sBarManager.BackgroundBottom, this._sBarManager.BackgroundAngle, this._sBarManager.BackgroundBlend);
			Link.DrawLine(new Pen(this._sBarManager.DarkBorder), 0, 0, Bounds.Width, 0);
			Link.DrawLine(new Pen(this._sBarManager.LightBorder), 0, 1, Bounds.Width, 1);
		}
		public void IDrawMenustripItem(ToolStripMenuItem Item, Graphics Link, ToolStrip Parent)
		{
			checked
			{
				Rectangle rectangle = new Rectangle(new Point(0, 0), new Size(Item.Bounds.Size.Width - 1, Item.Bounds.Size.Height - 1));
				if (Item.OwnerItem != null)
				{
					rectangle.X += 2;
					rectangle.Width -= 3;
				}
				Blend blend = this.GetBlend(Item, ButtonType.MenuItem);
				Color[] buttonBackColor = this.GetButtonBackColor(Item, ButtonType.MenuItem);
				using (GraphicsPath graphicsPath = this.CreateDrawingPath(rectangle, (float)this._btnManager.Curve))
				{
					Link.SetClip(graphicsPath);
					this.PaintBackground(Link, rectangle, buttonBackColor[0], buttonBackColor[1], this._btnManager.BackgroundAngle, blend);
					Link.ResetClip();
					Link.SmoothingMode = SmoothingMode.AntiAlias;
					using (GraphicsPath graphicsPath2 = this.CreateDrawingPath(rectangle, (float)this._btnManager.Curve))
					{
						this.PaintBorder(Link, graphicsPath2, rectangle, this._mnuManager.MenustripButtonBorder, this._mnuManager.MenustripButtonBorder, this._btnManager.BorderAngle, this._btnManager.BorderBlend);
						graphicsPath2.Dispose();
					}
					if (!Item.Pressed)
					{
						rectangle.Inflate(-1, -1);
						using (GraphicsPath graphicsPath3 = this.CreateDrawingPath(rectangle, (float)this._btnManager.Curve))
						{
							using (SolidBrush solidBrush = new SolidBrush(this._btnManager.InnerBorder))
							{
								this.PaintBorder(Link, graphicsPath3, solidBrush);
								solidBrush.Dispose();
							}
						}
					}
					Link.SmoothingMode = SmoothingMode.Default;
				}
			}
		}
		protected override void OnRenderButtonBackground(ToolStripItemRenderEventArgs e)
		{
			if (e.ToolStrip is ContextMenuStrip || e.ToolStrip is ToolStripDropDownMenu || e.ToolStrip is MenuStrip)
			{
				ToolStripMenuItem toolStripMenuItem = (ToolStripMenuItem)e.Item;
				if (toolStripMenuItem.Selected || toolStripMenuItem.Checked || toolStripMenuItem.Pressed)
				{
					this.IDrawMenustripItem(toolStripMenuItem, e.Graphics, e.ToolStrip);
				}
			}
			else
			{
				if (!(e.ToolStrip is StatusStrip))
				{
					ToolStripButton toolStripButton = (ToolStripButton)e.Item;
					if (toolStripButton.Selected || toolStripButton.Checked || toolStripButton.Pressed)
					{
						this.IDrawToolstripButton(toolStripButton, e.Graphics, e.ToolStrip);
					}
				}
			}
		}
		protected override void OnRenderDropDownButtonBackground(ToolStripItemRenderEventArgs e)
		{
			if (e.Item.Selected || e.Item.Pressed)
			{
				this.IDrawDropDownButton((ToolStripDropDownButton)e.Item, e.Graphics, e.ToolStrip);
			}
		}
		protected override void OnRenderImageMargin(ToolStripRenderEventArgs e)
		{
			checked
			{
				Rectangle boundary = new Rectangle(2, 2, e.AffectedBounds.Width, e.AffectedBounds.Height - 4);
				this.PaintBackground(e.Graphics, boundary, this._mnuManager.MarginLeft, this._mnuManager.MarginRight, 0f);
				e.Graphics.DrawLine(new Pen(this._mnuManager.MenuBorderDark), e.AffectedBounds.Width + 1, 2, e.AffectedBounds.Width + 1, e.AffectedBounds.Height - 3);
			}
		}
		protected override void OnRenderItemText(ToolStripItemTextRenderEventArgs e)
		{
			if (e.ToolStrip is MenuStrip || e.ToolStrip != null || e.ToolStrip is ContextMenuStrip || e.ToolStrip is ToolStripDropDownMenu)
			{
				if (!e.Item.Enabled)
				{
					e.TextColor = Color.FromArgb(167, 167, 167);
				}
				else
				{
					if (e.ToolStrip is MenuStrip && !e.Item.Pressed && !e.Item.Selected)
					{
						e.TextColor = Color.FromArgb(21, 66, 139);
					}
					else
					{
						if (e.ToolStrip is StatusStrip && !e.Item.Pressed && !e.Item.Selected)
						{
							e.TextColor = Color.White;
						}
						else
						{
							e.TextColor = Color.FromArgb(21, 66, 139);
						}
					}
				}
			}
			base.OnRenderItemText(e);
		}
		protected override void OnRenderMenuItemBackground(ToolStripItemRenderEventArgs e)
		{
			ToolStripMenuItem toolStripMenuItem = (ToolStripMenuItem)e.Item;
			if ((toolStripMenuItem.Selected || toolStripMenuItem.Checked || toolStripMenuItem.Pressed) && toolStripMenuItem.Enabled)
			{
				if (e.ToolStrip is MenuStrip || e.ToolStrip is ToolStripDropDownMenu || e.ToolStrip is ContextMenuStrip)
				{
					this.IDrawMenustripItem(toolStripMenuItem, e.Graphics, e.ToolStrip);
				}
			}
		}
		protected override void OnRenderSeparator(ToolStripSeparatorRenderEventArgs e)
		{
			checked
			{
				if (e.ToolStrip is ContextMenuStrip || e.ToolStrip is ToolStripDropDownMenu)
				{
					e.Graphics.DrawLine(new Pen(this._mnuManager.SeperatorDark), this._mnuManager.SeperatorInset, 3, e.Item.Width + 1, 3);
					e.Graphics.DrawLine(new Pen(this._mnuManager.SeperatorLight), this._mnuManager.SeperatorInset, 4, e.Item.Width + 1, 4);
				}
				else
				{
					if (e.Vertical)
					{
						e.Graphics.DrawLine(new Pen(this._tsCtrlManager.SeperatorDark), 3, 5, 3, e.Item.Height - 6);
						e.Graphics.DrawLine(new Pen(this._tsCtrlManager.SeperatorLight), 4, 6, 4, e.Item.Height - 6);
					}
					else
					{
						e.Graphics.DrawLine(new Pen(this._tsCtrlManager.SeperatorDark), 8, 0, e.Item.Width - 6, 0);
						e.Graphics.DrawLine(new Pen(this._tsCtrlManager.SeperatorLight), 9, 1, e.Item.Width - 6, 1);
					}
				}
			}
		}
		protected override void OnRenderSplitButtonBackground(ToolStripItemRenderEventArgs e)
		{
			ToolStripSplitButton item = (ToolStripSplitButton)e.Item;
			this.IDrawToolstripSplitButton(item, e.Graphics, e.ToolStrip);
		}
		protected override void OnRenderStatusStripSizingGrip(ToolStripRenderEventArgs e)
		{
			checked
			{
				using (SolidBrush solidBrush = new SolidBrush(this._sBarManager.GripTop))
				{
					using (SolidBrush solidBrush2 = new SolidBrush(this._sBarManager.GripBottom))
					{
						int gripSpacing = this._sBarManager.GripSpacing;
						int num = e.AffectedBounds.Bottom - gripSpacing * 4;
						for (int i = 1; i < 4; i++)
						{
							num += gripSpacing;
							int num2 = 1;
							while (i >= num2)
							{
								int num3 = e.AffectedBounds.Right - gripSpacing * num2;
								e.Graphics.FillRectangle(solidBrush2, num3 + 1, num + 1, 2, 2);
								e.Graphics.FillRectangle(solidBrush, num3, num, 2, 2);
								num2++;
							}
						}
					}
				}
			}
		}
		protected override void OnRenderToolStripBackground(ToolStripRenderEventArgs e)
		{
			checked
			{
				if (e.ToolStrip is ContextMenuStrip || e.ToolStrip is ToolStripDropDownMenu)
				{
					this.PaintBackground(e.Graphics, e.AffectedBounds, this._mnuManager.BackgroundTop, this._mnuManager.BackgroundBottom, 90f, this._mnuManager.BackgroundBlend);
					Rectangle area = new Rectangle(0, 0, e.AffectedBounds.Width - 1, e.AffectedBounds.Height - 1);
					using (GraphicsPath graphicsPath = this.CreateDrawingPath(area, 0f))
					{
						e.Graphics.ExcludeClip(new Rectangle(1, 0, e.ConnectedArea.Width, e.ConnectedArea.Height - 1));
						this.PaintBorder(e.Graphics, graphicsPath, new SolidBrush(this._mnuManager.MenuBorderDark));
						e.Graphics.ResetClip();
						graphicsPath.Dispose();
					}
				}
				else
				{
					if (e.ToolStrip is MenuStrip)
					{
						Rectangle affectedBounds = e.AffectedBounds;
						this.PaintBackground(e.Graphics, affectedBounds, new SolidBrush(this._pManager.ContentPanelTop));
					}
					else
					{
						if (e.ToolStrip is StatusStrip)
						{
							this.IDrawStatusbarBackground((StatusStrip)e.ToolStrip, e.Graphics, e.AffectedBounds);
						}
						else
						{
							e.ToolStrip.BackColor = Color.Transparent;
							this.IDrawToolstripBackground(e.ToolStrip, e.Graphics, e.AffectedBounds);
						}
					}
				}
			}
		}
		protected override void OnRenderToolStripBorder(ToolStripRenderEventArgs e)
		{
			if (!(e.ToolStrip is ContextMenuStrip) && !(e.ToolStrip is ToolStripDropDownMenu))
			{
				if (!(e.ToolStrip is StatusStrip))
				{
					if (!(e.ToolStrip is MenuStrip))
					{
						Rectangle area = checked(new Rectangle(0, -2, e.AffectedBounds.Width - 2, e.AffectedBounds.Height + 1));
						using (GraphicsPath graphicsPath = this.CreateDrawingPath(area, (float)this._tsManager.Curve))
						{
							this.PaintBorder(e.Graphics, graphicsPath, e.AffectedBounds, this._tsManager.BorderTop, this._tsManager.BorderBottom, this._tsManager.BorderAngle, this._tsManager.BorderBlend);
							graphicsPath.Dispose();
						}
					}
				}
			}
		}
		protected override void OnRenderToolStripContentPanelBackground(ToolStripContentPanelRenderEventArgs e)
		{
			if (e.ToolStripContentPanel.ClientRectangle.Width >= 3 && e.ToolStripContentPanel.ClientRectangle.Height >= 3)
			{
				e.Handled = true;
				e.Graphics.SmoothingMode = this._pManager.Mode;
				this.PaintBackground(e.Graphics, e.ToolStripContentPanel.ClientRectangle, this._pManager.ContentPanelTop, this._pManager.ContentPanelBottom, this._pManager.BackgroundAngle, this._pManager.BackgroundBlend);
			}
		}
		protected override void OnRenderToolStripPanelBackground(ToolStripPanelRenderEventArgs e)
		{
			if (e.ToolStripPanel.ClientRectangle.Width >= 3 && e.ToolStripPanel.ClientRectangle.Height >= 3)
			{
				e.Handled = true;
				switch (e.ToolStripPanel.Dock)
				{
				case DockStyle.Top:
					this.PaintBackground(e.Graphics, e.ToolStripPanel.ClientRectangle, new SolidBrush(this._pManager.ContentPanelTop));
					break;

				case DockStyle.Bottom:
					this.PaintBackground(e.Graphics, e.ToolStripPanel.ClientRectangle, new SolidBrush(this._pManager.ContentPanelBottom));
					break;

				case DockStyle.Left:
				case DockStyle.Right:
					this.PaintBackground(e.Graphics, e.ToolStripPanel.ClientRectangle, this._pManager.ContentPanelTop, this._pManager.ContentPanelBottom, this._pManager.BackgroundAngle, this._pManager.BackgroundBlend);
					break;
				}
			}
		}
		public void Apply()
		{
			ToolStripManager.Renderer = this;
		}
	}
}
