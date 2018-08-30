using System;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Drawing2D;
namespace EasyRender_CustomTheme
{
	public class IMenustrip : IDisposable
	{
		private Color _menuBorderDark = Color.FromArgb(193, 210, 238);
		private Color _menuBorderLight = Color.Transparent;
		private InheritenceType _menuBackInh = InheritenceType.FromContentPanel;
		private Color _menuBackTop = Color.FromArgb(225, 233, 241);
		private Color _menuBackBottom = Color.White;
		private Blend _menuBackBlend = null;
		private Color _menuStripBtnBackground = Color.White;
		private Color _menuStripBtnBorder = Color.FromArgb(193, 210, 238);
		private IButton _buttons = null;
		private Color _marginLeft = Color.FromArgb(193, 210, 238);
		private Color _marginRight = Color.FromArgb(241, 244, 248);
		private Color _marginBorder = Color.FromArgb(162, 191, 227);
		private Color _sepDark = Color.FromArgb(215, 223, 231);
		private Color _sepLight = Color.FromArgb(241, 244, 248);
		private int _sepInset = 30;
		public Color MenuBorderDark
		{
			get
			{
				return this._menuBorderDark;
			}
			set
			{
				this._menuBorderDark = value;
			}
		}
		public Color MenuBorderLight
		{
			get
			{
				return this._menuBorderLight;
			}
			set
			{
				this._menuBorderLight = value;
			}
		}
		public InheritenceType BackgroundInheritence
		{
			get
			{
				return this._menuBackInh;
			}
			set
			{
				this._menuBackInh = value;
			}
		}
		public Color BackgroundTop
		{
			get
			{
				return this._menuBackTop;
			}
			set
			{
				this._menuBackTop = value;
			}
		}
		public Color BackgroundBottom
		{
			get
			{
				return this._menuBackBottom;
			}
			set
			{
				this._menuBackBottom = value;
			}
		}
		public Blend BackgroundBlend
		{
			get
			{
				return this._menuBackBlend;
			}
			set
			{
				this._menuBackBlend = value;
			}
		}
		public Color MarginLeft
		{
			get
			{
				return this._marginLeft;
			}
			set
			{
				this._marginLeft = value;
			}
		}
		public Color MarginRight
		{
			get
			{
				return this._marginRight;
			}
			set
			{
				this._marginRight = value;
			}
		}
		public Color MarginBorder
		{
			get
			{
				return this._marginBorder;
			}
			set
			{
				this._marginBorder = value;
			}
		}
		public Color MenustripButtonBackground
		{
			get
			{
				return this._menuStripBtnBackground;
			}
			set
			{
				this._menuStripBtnBackground = value;
			}
		}
		public Color MenustripButtonBorder
		{
			get
			{
				return this._menuStripBtnBorder;
			}
			set
			{
				this._menuStripBtnBorder = value;
			}
		}
		public Color SeperatorDark
		{
			get
			{
				return this._sepDark;
			}
			set
			{
				this._sepDark = value;
			}
		}
		public Color SeperatorLight
		{
			get
			{
				return this._sepLight;
			}
			set
			{
				this._sepLight = value;
			}
		}
		public int SeperatorInset
		{
			get
			{
				return this._sepInset;
			}
			set
			{
				this._sepInset = value;
			}
		}
		[ReadOnly(true)]
		public IButton Items
		{
			get
			{
				return this._buttons;
			}
		}
		public IMenustrip()
		{
			this._buttons = new IButton();
			this.DefaultBlending();
		}
		public IMenustrip(IMenustrip Import)
		{
			this._buttons = new IButton();
			this.DefaultBlending();
			this.Apply(Import);
		}
		public void Dispose()
		{
			GC.SuppressFinalize(this);
		}
		public void Apply(IMenustrip Import)
		{
			this._menuBackInh = Import._menuBackInh;
			this._menuBackTop = Import._menuBackTop;
			this._menuBackBottom = Import._menuBackBottom;
			this._menuBorderDark = Import._menuBorderDark;
			this._menuBorderLight = Import._menuBorderLight;
			this._menuBackBlend = Import._menuBackBlend;
			this._buttons = Import._buttons;
		}
		public void DefaultBlending()
		{
			this._menuBackBlend = new Blend();
			this._menuBackBlend.Positions = new float[]
			{
				0f,
				0.3f,
				0.5f,
				0.8f,
				1f
			};
			this._menuBackBlend.Factors = new float[]
			{
				0f,
				0f,
				0f,
				0.5f,
				1f
			};
		}
	}
}
