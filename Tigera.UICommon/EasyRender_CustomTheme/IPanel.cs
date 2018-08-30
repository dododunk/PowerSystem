using System;
using System.Drawing;
using System.Drawing.Drawing2D;
namespace EasyRender_CustomTheme
{
	public class IPanel : IDisposable
	{
		private Color _cPanelTop = Color.FromArgb(215, 223, 231);
		private Color _cPanelBottom = Color.FromArgb(193, 210, 238);
		private float _cPanelAngle = 90f;
		private Blend _cPanelBlend = null;
		private SmoothingMode _mode = SmoothingMode.HighSpeed;
		private bool _panelsInherit = false;
		public Color ContentPanelTop
		{
			get
			{
				return this._cPanelTop;
			}
			set
			{
				this._cPanelTop = value;
			}
		}
		public Color ContentPanelBottom
		{
			get
			{
				return this._cPanelBottom;
			}
			set
			{
				this._cPanelBottom = value;
			}
		}
		public bool PanelInheritance
		{
			get
			{
				return this._panelsInherit;
			}
			set
			{
				this._panelsInherit = value;
			}
		}
		public float BackgroundAngle
		{
			get
			{
				return this._cPanelAngle;
			}
			set
			{
				this._cPanelAngle = value;
			}
		}
		public Blend BackgroundBlend
		{
			get
			{
				return this._cPanelBlend;
			}
			set
			{
				this._cPanelBlend = value;
			}
		}
		public SmoothingMode Mode
		{
			get
			{
				return this._mode;
			}
			set
			{
				this._mode = value;
			}
		}
		public void Dispose()
		{
			GC.SuppressFinalize(this);
		}
	}
}
