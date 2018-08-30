using System;
using System.Drawing;
namespace EasyRender_VS2010Theme
{
	public class IToolstripControls : IDisposable
	{
		private Color _sepDark = Color.FromArgb(168, 173, 180);
		private Color _sepLight = Color.FromArgb(220, 225, 230);
		private int _sepHeight = 8;
		private Color _gripTop = Color.FromArgb(188, 193, 200);
		private Color _gripBottom = Color.White;
		private GripType _gripStyle = GripType.Dotted;
		private int _gripDistance = 4;
		private Size _gripSize = new Size(2, 2);
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
		public int SeperatorHeight
		{
			get
			{
				return this._sepHeight;
			}
			set
			{
				this._sepHeight = value;
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
		public Color GripShadow
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
		public GripType GripStyle
		{
			get
			{
				return this._gripStyle;
			}
			set
			{
				this._gripStyle = value;
			}
		}
		public int GripDistance
		{
			get
			{
				return this._gripDistance;
			}
			set
			{
				this._gripDistance = value;
			}
		}
		public Size GripSize
		{
			get
			{
				return this._gripSize;
			}
			set
			{
				this._gripSize = value;
			}
		}
		public void Dispose()
		{
			GC.SuppressFinalize(this);
		}
		public void Apply(IToolstripControls Import)
		{
			this._sepDark = Import._sepDark;
			this._sepLight = Import._sepLight;
			this._sepHeight = Import._sepHeight;
			this._gripTop = Import._gripTop;
			this._gripBottom = Import._gripBottom;
			this._gripDistance = Import._gripDistance;
			this._gripStyle = Import._gripStyle;
			this._gripSize = Import._gripSize;
		}
	}
}
