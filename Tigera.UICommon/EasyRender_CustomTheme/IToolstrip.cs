using System;
using System.Drawing;
using System.Drawing.Drawing2D;
namespace EasyRender_CustomTheme
{
	public class IToolstrip : IDisposable
	{
		private int _curve = 2;
		private Color _borderTop = Color.Transparent;
		private Color _borderBottom = Color.FromArgb(154, 162, 171);
		private Blend _borderBlend = null;
		private float _borderAngle = 90f;
		private Color _backTop = Color.FromArgb(215, 223, 231);
		private Color _backBottom = Color.FromArgb(193, 210, 238);
		private Blend _backBlend = null;
		private float _backAngle = 90f;
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
		public IToolstrip()
		{
			this.DefaultBlending();
		}
		public IToolstrip(IToolstrip Import)
		{
			this.DefaultBlending();
			this.Apply(Import);
		}
		public void Dispose()
		{
			GC.SuppressFinalize(this);
		}
		public void Apply(IToolstrip Import)
		{
			this._backTop = Import._borderTop;
			this._backBottom = Import._borderBottom;
			this._backAngle = Import._borderAngle;
			this._backBlend = Import._backBlend;
			this._borderTop = Import._borderTop;
			this._borderBottom = Import._borderBottom;
			this._borderAngle = Import._borderAngle;
			this._borderBlend = Import._borderBlend;
			this._curve = Import._curve;
		}
		public void DefaultBlending()
		{
			this._borderBlend = new Blend();
			this._borderBlend.Positions = new float[]
			{
				0f,
				0.1f,
				0.2f,
				0.3f,
				0.4f,
				0.5f,
				0.6f,
				0.7f,
				0.8f,
				0.9f,
				1f
			};
			this._borderBlend.Factors = new float[]
			{
				0.1f,
				0.2f,
				0.3f,
				0.3f,
				0.3f,
				0.4f,
				0.4f,
				0.4f,
				0.5f,
				0.7f,
				0.7f
			};
			this._backBlend = new Blend();
			this._backBlend.Positions = new float[]
			{
				0f,
				0.3f,
				0.5f,
				0.8f,
				1f
			};
			this._backBlend.Factors = new float[]
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
