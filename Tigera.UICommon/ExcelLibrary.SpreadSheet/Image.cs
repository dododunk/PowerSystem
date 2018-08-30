using System;
using System.IO;
namespace ExcelLibrary.SpreadSheet
{
	public class Image
	{
		public ushort Format;
		public byte[] Data;
		public string FileExtension
		{
			get
			{
				return Image.GetImageFileExtension(this.Format);
			}
		}
		public Image(byte[] data, ushort imageFormat)
		{
			this.Data = data;
			this.Format = imageFormat;
		}
		public static Image FromFile(string filepath)
		{
			byte[] data = File.ReadAllBytes(filepath);
			ushort imageFormat = Image.JudgeFromFileExtension(Path.GetExtension(filepath));
			return new Image(data, imageFormat);
		}
		public static string GetImageFileExtension(ushort imageForamt)
		{
			string result;
			switch (imageForamt)
			{
			case 61466:
				result = ".emf";
				return result;

			case 61467:
				result = ".wmf";
				return result;

			case 61469:
				result = ".jpeg";
				return result;

			case 61470:
				result = ".png";
				return result;

			case 61471:
				result = ".bmp";
				return result;
			}
			result = "unknown";
			return result;
		}
		private static ushort JudgeFromFileExtension(string ext)
		{
			string text = ext.ToLower();
			ushort result;
			if (text != null)
			{
				if (text == ".emf")
				{
					result = 61466;
					return result;
				}
				if (text == ".wmf")
				{
					result = 61467;
					return result;
				}
				if (text == ".jpeg")
				{
					result = 61469;
					return result;
				}
				if (text == ".png")
				{
					result = 61470;
					return result;
				}
				if (text == ".bmp")
				{
					result = 61471;
					return result;
				}
			}
			result = 0;
			return result;
		}
	}
}
