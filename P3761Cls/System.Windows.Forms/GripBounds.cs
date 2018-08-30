using System;
using System.Drawing;
namespace System.Windows.Forms
{
	internal struct GripBounds
	{
		private const int GripSize = 6;
		private const int CornerGripSize = 12;
		private Rectangle clientRectangle;
		public Rectangle ClientRectangle
		{
			get
			{
				return this.clientRectangle;
			}
		}
		public Rectangle Bottom
		{
			get
			{
				Rectangle result = this.ClientRectangle;
				result.Y = checked(result.Bottom - 6 + 1);
				result.Height = 6;
				return result;
			}
		}
		public Rectangle BottomRight
		{
			get
			{
				Rectangle result = this.ClientRectangle;
				checked
				{
					result.Y = result.Bottom - 12 + 1;
					result.Height = 12;
					result.X = result.Width - 12 + 1;
					result.Width = 12;
					return result;
				}
			}
		}
		public Rectangle Top
		{
			get
			{
				Rectangle result = this.ClientRectangle;
				result.Height = 6;
				return result;
			}
		}
		public Rectangle TopRight
		{
			get
			{
				Rectangle result = this.ClientRectangle;
				result.Height = 12;
				result.X = checked(result.Width - 12 + 1);
				result.Width = 12;
				return result;
			}
		}
		public Rectangle Left
		{
			get
			{
				Rectangle result = this.ClientRectangle;
				result.Width = 6;
				return result;
			}
		}
		public Rectangle BottomLeft
		{
			get
			{
				Rectangle result = this.ClientRectangle;
				result.Width = 12;
				result.Y = checked(result.Height - 12 + 1);
				result.Height = 12;
				return result;
			}
		}
		public Rectangle Right
		{
			get
			{
				Rectangle result = this.ClientRectangle;
				result.X = checked(result.Right - 6 + 1);
				result.Width = 6;
				return result;
			}
		}
		public Rectangle TopLeft
		{
			get
			{
				Rectangle result = this.ClientRectangle;
				result.Width = 12;
				result.Height = 12;
				return result;
			}
		}
		public GripBounds(Rectangle clientRectangle)
		{
			this.clientRectangle = clientRectangle;
		}
	}
}
