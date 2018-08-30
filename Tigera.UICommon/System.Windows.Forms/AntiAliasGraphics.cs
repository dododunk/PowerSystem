using System;
using System.Drawing;
using System.Drawing.Drawing2D;
namespace System.Windows.Forms
{
	public class AntiAliasGraphics : IDisposable
	{
		private SmoothingMode _oldMode;
		private Graphics _graphics;
		public AntiAliasGraphics(Graphics graphics)
		{
			this._graphics = graphics;
			this._oldMode = graphics.SmoothingMode;
			graphics.SmoothingMode = SmoothingMode.AntiAlias;
		}
		public void Dispose()
		{
			this._graphics.SmoothingMode = this._oldMode;
		}
	}
}
