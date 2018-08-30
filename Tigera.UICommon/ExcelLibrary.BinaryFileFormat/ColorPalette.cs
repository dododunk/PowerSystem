using System;
using System.Collections.Generic;
using System.Drawing;
namespace ExcelLibrary.BinaryFileFormat
{
	public class ColorPalette
	{
		public Dictionary<int, Color> Palette = new Dictionary<int, Color>();
		public Color this[int index]
		{
			get
			{
				Color result;
				if (this.Palette.ContainsKey(index))
				{
					result = this.Palette[index];
				}
				else
				{
					result = Color.White;
				}
				return result;
			}
			set
			{
				this.Palette[index] = value;
			}
		}
		public ColorPalette()
		{
			this.Palette.Add(0, Color.Black);
			this.Palette.Add(1, Color.White);
			this.Palette.Add(2, Color.Red);
			this.Palette.Add(3, Color.Green);
			this.Palette.Add(4, Color.Blue);
			this.Palette.Add(5, Color.Yellow);
			this.Palette.Add(6, Color.Magenta);
			this.Palette.Add(7, Color.Cyan);
			this.Palette.Add(31, Color.FromArgb(204, 204, 255));
			this.Palette.Add(64, SystemColors.Window);
			this.Palette.Add(65, SystemColors.WindowText);
			this.Palette.Add(67, SystemColors.WindowFrame);
			this.Palette.Add(77, SystemColors.ControlText);
			this.Palette.Add(78, SystemColors.Control);
			this.Palette.Add(79, Color.Black);
			this.Palette.Add(80, SystemColors.Info);
			this.Palette.Add(81, SystemColors.InfoText);
			this.Palette.Add(32767, SystemColors.WindowText);
		}
	}
}
