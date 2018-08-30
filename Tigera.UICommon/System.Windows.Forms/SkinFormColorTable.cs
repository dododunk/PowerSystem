using System;
using System.Drawing;
namespace System.Windows.Forms
{
	public class SkinFormColorTable
	{
		public virtual Color CaptionActive
		{
			get;
			private set;
		}
		public virtual Color CaptionDeactive
		{
			get;
			private set;
		}
		public virtual Color CaptionText
		{
			get;
			private set;
		}
		public virtual Color Border
		{
			get;
			private set;
		}
		public virtual Color InnerBorder
		{
			get;
			private set;
		}
		public virtual Color Back
		{
			get;
			private set;
		}
		public virtual Color ControlBoxActive
		{
			get;
			private set;
		}
		public virtual Color ControlBoxDeactive
		{
			get;
			private set;
		}
		public virtual Color ControlBoxHover
		{
			get;
			private set;
		}
		public virtual Color ControlBoxPressed
		{
			get;
			private set;
		}
		public virtual Color ControlCloseBoxHover
		{
			get;
			private set;
		}
		public virtual Color ControlCloseBoxPressed
		{
			get;
			private set;
		}
		public virtual Color ControlBoxInnerBorder
		{
			get;
			private set;
		}
	}
}
