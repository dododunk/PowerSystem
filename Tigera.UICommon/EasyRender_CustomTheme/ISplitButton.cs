using System;
using System.Drawing;
using System.Drawing.Drawing2D;
namespace EasyRender_CustomTheme
{
	public class ISplitButton : IDisposable
	{
		private Color _borderTop = Color.FromArgb(157, 183, 217);
		private Color _borderBottom = Color.FromArgb(157, 183, 217);
		private Color _borderInner = Color.FromArgb(255, 247, 185);
		private Blend _borderBlend = null;
		private float _borderAngle = 90f;
		private Color _hoverBackTop = Color.FromArgb(255, 249, 218);
		private Color _hoverBackBottom = Color.FromArgb(237, 189, 62);
		private Color _clickBackTop = Color.FromArgb(245, 207, 57);
		private Color _clickBackBottom = Color.FromArgb(245, 225, 124);
		private float _backAngle = 90f;
		private Blend _backBlend = null;
		private ArrowDisplay _arrowDisplay = ArrowDisplay.Always;
		private Color _arrowColor = Color.Black;
		private BlendRender _blendRender = BlendRender.Check;
		private int _curve = 1;
		public Color HoverBackgroundTop
		{
			get
			{
				return this._hoverBackTop;
			}
			set
			{
				this._hoverBackTop = value;
			}
		}
		public Color HoverBackgroundBottom
		{
			get
			{
				return this._hoverBackBottom;
			}
			set
			{
				this._hoverBackBottom = value;
			}
		}
		public Color ClickBackgroundTop
		{
			get
			{
				return this._clickBackTop;
			}
			set
			{
				this._clickBackTop = value;
			}
		}
		public Color ClickBackgroundBottom
		{
			get
			{
				return this._clickBackBottom;
			}
			set
			{
				this._clickBackBottom = value;
			}
		}
		public Blend BackgroundBlend
		{
			get
			{
				return this._backBlend;
			}
			set
			{
				this._backBlend = value;
			}
		}
		public float BackgroundAngle
		{
			get
			{
				return this._backAngle;
			}
			set
			{
				this._backAngle = value;
			}
		}
		public Color BorderTop
		{
			get
			{
				return this._borderTop;
			}
			set
			{
				this._borderTop = value;
			}
		}
		public Color BorderBottom
		{
			get
			{
				return this._borderBottom;
			}
			set
			{
				this._borderBottom = value;
			}
		}
		public Blend BorderBlend
		{
			get
			{
				return this._borderBlend;
			}
			set
			{
				this._borderBlend = value;
			}
		}
		public float BorderAngle
		{
			get
			{
				return this._borderAngle;
			}
			set
			{
				this._borderAngle = value;
			}
		}
		public Color InnerBorder
		{
			get
			{
				return this._borderInner;
			}
			set
			{
				this._borderInner = value;
			}
		}
		public BlendRender BlendOptions
		{
			get
			{
				return this._blendRender;
			}
			set
			{
				this._blendRender = value;
			}
		}
		public int Curve
		{
			get
			{
				return this._curve;
			}
			set
			{
				this._curve = value;
			}
		}
		public ArrowDisplay ArrowDisplay
		{
			get
			{
				return this._arrowDisplay;
			}
			set
			{
				this._arrowDisplay = value;
			}
		}
		public Color ArrowColor
		{
			get
			{
				return this._arrowColor;
			}
			set
			{
				this._arrowColor = value;
			}
		}
		public ISplitButton()
		{
			this.DefaultBlending();
		}
		public void Dispose()
		{
			GC.SuppressFinalize(this);
		}
		public void Apply(ISplitButton Import)
		{
			this._borderTop = Import._borderTop;
			this._borderBottom = Import._borderBottom;
			this._borderAngle = Import._borderAngle;
			this._borderBlend = Import._borderBlend;
			this._hoverBackTop = Import._hoverBackTop;
			this._hoverBackBottom = Import._hoverBackBottom;
			this._clickBackTop = Import._clickBackTop;
			this._clickBackBottom = Import._clickBackBottom;
			this._backAngle = Import._backAngle;
			this._backBlend = Import._backBlend;
			this._blendRender = Import._blendRender;
			this._curve = Import._curve;
			this._arrowDisplay = Import._arrowDisplay;
			this._arrowColor = Import._arrowColor;
		}
		public void DefaultBlending()
		{
			this._borderBlend = null;
			this._backBlend = new Blend();
			this._backBlend.Positions = new float[]
			{
				0f,
				0.5f,
				0.5f,
				1f
			};
			this._backBlend.Factors = new float[]
			{
				0f,
				0.2f,
				1f,
				0.3f
			};
		}
	}
}
