using System;
using System.Drawing;
namespace System.Windows.Forms
{
	public class SkinFormColorTable_CustomTheme : SkinFormColorTable
	{
		private static readonly Color _captionActive = Color.FromArgb(180, 200, 222);
		private static readonly Color _captionDeactive = Color.FromArgb(180, 200, 222);
		private static readonly Color _captionText = Color.FromArgb(40, 111, 152);
		private static readonly Color _border = Color.FromArgb(93, 110, 138);
		private static readonly Color _innerBorder = Color.FromArgb(158, 250, 250, 250);
		private static readonly Color _back = Color.FromArgb(180, 200, 222);
		private static readonly Color _controlBoxActive = Color.FromArgb(112, 141, 177);
		private static readonly Color _controlBoxDeactive = Color.FromArgb(171, 200, 247);
		private static readonly Color _controlBoxHover = Color.FromArgb(37, 114, 151);
		private static readonly Color _controlBoxPressed = Color.FromArgb(27, 84, 111);
		private static readonly Color _controlCloseBoxHover = Color.FromArgb(213, 66, 22);
		private static readonly Color _controlCloseBoxPressed = Color.FromArgb(171, 53, 17);
		private static readonly Color _controlBoxInnerBorder = Color.FromArgb(128, 250, 250, 250);
		public override Color CaptionActive
		{
			get
			{
				return SkinFormColorTable_CustomTheme._captionActive;
			}
		}
		public override Color CaptionDeactive
		{
			get
			{
				return SkinFormColorTable_CustomTheme._captionDeactive;
			}
		}
		public override Color CaptionText
		{
			get
			{
				return SkinFormColorTable_CustomTheme._captionText;
			}
		}
		public override Color Border
		{
			get
			{
				return SkinFormColorTable_CustomTheme._border;
			}
		}
		public override Color InnerBorder
		{
			get
			{
				return SkinFormColorTable_CustomTheme._innerBorder;
			}
		}
		public override Color Back
		{
			get
			{
				return SkinFormColorTable_CustomTheme._back;
			}
		}
		public override Color ControlBoxActive
		{
			get
			{
				return SkinFormColorTable_CustomTheme._controlBoxActive;
			}
		}
		public override Color ControlBoxDeactive
		{
			get
			{
				return SkinFormColorTable_CustomTheme._controlBoxDeactive;
			}
		}
		public override Color ControlBoxHover
		{
			get
			{
				return SkinFormColorTable_CustomTheme._controlBoxHover;
			}
		}
		public override Color ControlBoxPressed
		{
			get
			{
				return SkinFormColorTable_CustomTheme._controlBoxPressed;
			}
		}
		public override Color ControlCloseBoxHover
		{
			get
			{
				return SkinFormColorTable_CustomTheme._controlCloseBoxHover;
			}
		}
		public override Color ControlCloseBoxPressed
		{
			get
			{
				return SkinFormColorTable_CustomTheme._controlCloseBoxPressed;
			}
		}
		public override Color ControlBoxInnerBorder
		{
			get
			{
				return SkinFormColorTable_CustomTheme._controlBoxInnerBorder;
			}
		}
	}
}
