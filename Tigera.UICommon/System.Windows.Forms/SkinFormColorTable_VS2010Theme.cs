using System;
using System.Drawing;
namespace System.Windows.Forms
{
	public class SkinFormColorTable_VS2010Theme : SkinFormColorTable
	{
		private static Color _captionActive = Color.FromArgb(172, 182, 200);
		private static Color _captionDeactive = Color.FromArgb(172, 182, 200);
		private static Color _captionText = Color.FromArgb(40, 111, 152);
		private static Color _border = Color.FromArgb(122, 122, 140);
		private static Color _innerBorder = Color.FromArgb(200, 200, 200);
		private static Color _back = Color.FromArgb(172, 182, 200);
		private static Color _controlBoxActive = Color.FromArgb(102, 112, 140);
		private static Color _controlBoxDeactive = Color.FromArgb(128, 128, 128);
		private static Color _controlBoxHover = Color.FromArgb(43, 43, 43);
		private static Color _controlBoxPressed = Color.FromArgb(27, 84, 111);
		private static Color _controlCloseBoxHover = Color.FromArgb(213, 66, 22);
		private static Color _controlCloseBoxPressed = Color.FromArgb(171, 53, 17);
		private static Color _controlBoxInnerBorder = Color.FromArgb(128, 250, 250, 250);
		public override Color CaptionActive
		{
			get
			{
				return SkinFormColorTable_VS2010Theme._captionActive;
			}
		}
		public override Color CaptionDeactive
		{
			get
			{
				return SkinFormColorTable_VS2010Theme._captionDeactive;
			}
		}
		public override Color CaptionText
		{
			get
			{
				return SkinFormColorTable_VS2010Theme._captionText;
			}
		}
		public override Color Border
		{
			get
			{
				return SkinFormColorTable_VS2010Theme._border;
			}
		}
		public override Color InnerBorder
		{
			get
			{
				return SkinFormColorTable_VS2010Theme._innerBorder;
			}
		}
		public override Color Back
		{
			get
			{
				return SkinFormColorTable_VS2010Theme._back;
			}
		}
		public override Color ControlBoxActive
		{
			get
			{
				return SkinFormColorTable_VS2010Theme._controlBoxActive;
			}
		}
		public override Color ControlBoxDeactive
		{
			get
			{
				return SkinFormColorTable_VS2010Theme._controlBoxDeactive;
			}
		}
		public override Color ControlBoxHover
		{
			get
			{
				return SkinFormColorTable_VS2010Theme._controlBoxHover;
			}
		}
		public override Color ControlBoxPressed
		{
			get
			{
				return SkinFormColorTable_VS2010Theme._controlBoxPressed;
			}
		}
		public override Color ControlCloseBoxHover
		{
			get
			{
				return SkinFormColorTable_VS2010Theme._controlCloseBoxHover;
			}
		}
		public override Color ControlCloseBoxPressed
		{
			get
			{
				return SkinFormColorTable_VS2010Theme._controlCloseBoxPressed;
			}
		}
		public override Color ControlBoxInnerBorder
		{
			get
			{
				return SkinFormColorTable_VS2010Theme._controlBoxInnerBorder;
			}
		}
	}
}
