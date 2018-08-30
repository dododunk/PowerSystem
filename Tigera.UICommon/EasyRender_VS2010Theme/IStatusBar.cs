using System;
using System.Drawing;
using System.Drawing.Drawing2D;
namespace EasyRender_VS2010Theme
{
	public class IStatusBar : IDisposable
	{
		private Color _backTop = Color.FromArgb(41, 57, 85);
		private Color _backBottom = Color.FromArgb(41, 57, 85);
		private Blend _backBlend = null;
		private float _backAngle = 90f;
		private Color _borderDark = Color.FromArgb(41, 57, 85);
		private Color _borderLight = Color.FromArgb(41, 57, 85);
		private Blend _borderBlend = new Blend();
		private Color _gripTop = Color.FromArgb(114, 152, 204);
		private Color _gripBottom = Color.FromArgb(248, 248, 248);
		private int _gripSpacing = 4;
		public Color BackgroundTop
		{
			get
			{
				return this._backTop;
			}
			set
			{
				this._backTop = value;
			}
		}
		public Color BackgroundBottom
		{
			get
			{
				return this._backBottom;
			}
			set
			{
				this._backBottom = value;
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
		public Color DarkBorder
		{
			get
			{
				return this._borderDark;
			}
			set
			{
				this._borderDark = value;
			}
		}
		public Color LightBorder
		{
			get
			{
				return this._borderLight;
			}
			set
			{
				this._borderLight = value;
			}
		}
		public Color GripTop
		{
			get
			{
				return this._gripTop;
			}
			set
			{
				this._gripTop = value;
			}
		}
		public Color GripBottom
		{
			get
			{
				return this._gripBottom;
			}
			set
			{
				this._gripBottom = value;
			}
		}
		public int GripSpacing
		{
			get
			{
				return this._gripSpacing;
			}
			set
			{
				this._gripSpacing = value;
			}
		}
		public IStatusBar()
		{
			this.DefaultBlending();
		}
		public void Dispose()
		{
			GC.SuppressFinalize(this);
		}
		public void Apply(IStatusBar Import)
		{
			this._borderDark = Import._borderDark;
			this._borderLight = Import._borderLight;
			this._backTop = Import._backTop;
			this._backBottom = Import._backBottom;
			this._backAngle = Import._backAngle;
			this._backBlend = Import._backBlend;
		}
		public void DefaultBlending()
		{
			this._borderBlend = null;
			this._backBlend = new Blend();
			this._backBlend.Positions = new float[]
			{
				0f,
				0.25f,
				0.25f,
				0.57f,
				0.86f,
				1f
			};
			this._backBlend.Factors = new float[]
			{
				0.1f,
				0.6f,
				1f,
				0.4f,
				0f,
				0.95f
			};
		}
	}
}
