using System;
using System.Drawing.Imaging;
using System.Windows.Forms;
namespace QiHe.CodeLib
{
	public static class FileSelector
	{
		public static string TitleSingleFile;
		public static string TitleMultiFile;
		public static string Filter;
		public static OpenFileDialog OFD;
		public static SaveFileDialog SFD;
		public static FileType FileExtension
		{
			set
			{
				switch (value)
				{
				case FileType.Txt:
					FileSelector.Filter = "Text files (*.txt)|*.txt|All files (*.*)|*.*";
					break;

				case FileType.Rtf:
					FileSelector.Filter = "Rtf files (*.rtf)|*.rtf|All files (*.*)|*.*";
					break;

				case FileType.Html:
					FileSelector.Filter = "Html files (*.htm;*.html)|*.htm;*.html|All files (*.*)|*.*";
					break;

				case FileType.Xml:
					FileSelector.Filter = "XML files (*.xml)|*.xml|Config files (*.config)|*.config|All files (*.*)|*.*";
					break;

				case FileType.PDF:
					FileSelector.Filter = "PDF files (*.pdf)|*.pdf|PDF form files (*.fdf)|*.fdf|All files (*.*)|*.*";
					break;

				case FileType.Bin:
					FileSelector.Filter = "Application files(*.exe;*.dll)|*.exe;*.dll|Binary files (*.bin)|*.bin|All files (*.*)|*.*";
					break;

				case FileType.Zip:
					FileSelector.Filter = "Zip files (*.zip)|*.zip|All files (*.*)|*.*";
					break;

				case FileType.Img:
					FileSelector.Filter = "Gif(*.gif)|*.gif|Jpeg(*.jpg)|*.jpg|Emf(*.emf)|*.emf|Bmp(*.bmp)|*.bmp|Png(*.png)|*.png";
					break;

				case FileType.Excel97:
					FileSelector.Filter = "Excel files (*.xls)|*.xls|All files (*.*)|*.*";
					break;

				case FileType.Excel2007:
					FileSelector.Filter = "Excel files (*.xlsx)|*.xlsx|All files (*.*)|*.*";
					break;

				case FileType.All:
					FileSelector.Filter = "All files (*.*)|*.*";
					break;
				}
			}
		}
		public static ImageFormat ImageFormat
		{
			get
			{
				ImageFormat result;
				switch (FileSelector.SFD.FilterIndex)
				{
				case 1:
					result = ImageFormat.Gif;
					break;

				case 2:
					result = ImageFormat.Jpeg;
					break;

				case 3:
					result = ImageFormat.Emf;
					break;

				case 4:
					result = ImageFormat.Bmp;
					break;

				case 5:
					result = ImageFormat.Png;
					break;

				default:
					result = ImageFormat.Png;
					break;
				}
				return result;
			}
		}
		public static string InitialPath
		{
			get
			{
				return FileSelector.OFD.InitialDirectory;
			}
			set
			{
				FileSelector.OFD.InitialDirectory = value;
				FileSelector.SFD.InitialDirectory = value;
			}
		}
		public static string FileName
		{
			get
			{
				return FileSelector.OFD.FileName;
			}
			set
			{
				FileSelector.OFD.FileName = value;
				FileSelector.SFD.FileName = value;
			}
		}
		static FileSelector()
		{
			FileSelector.TitleSingleFile = "Please choose a file";
			FileSelector.TitleMultiFile = "Please choose files";
			FileSelector.Filter = "Text files (*.txt)|*.txt|All files (*.*)|*.*";
			FileSelector.OFD = new OpenFileDialog();
			FileSelector.SFD = new SaveFileDialog();
			FileSelector.OFD.RestoreDirectory = false;
		}
		public static string BrowseFile()
		{
			FileSelector.OFD.Title = FileSelector.TitleSingleFile;
			FileSelector.OFD.Filter = FileSelector.Filter;
			FileSelector.OFD.Multiselect = false;
			string result;
			if (FileSelector.OFD.ShowDialog() == DialogResult.OK)
			{
				result = FileSelector.OFD.FileName;
			}
			else
			{
				result = null;
			}
			return result;
		}
		public static string[] BrowseFiles()
		{
			FileSelector.OFD.Title = FileSelector.TitleMultiFile;
			FileSelector.OFD.Filter = FileSelector.Filter;
			FileSelector.OFD.Multiselect = true;
			string[] result;
			if (FileSelector.OFD.ShowDialog() == DialogResult.OK)
			{
				result = FileSelector.OFD.FileNames;
			}
			else
			{
				result = null;
			}
			return result;
		}
		public static string BrowseFileForSave()
		{
			FileSelector.SFD.Title = FileSelector.TitleSingleFile;
			FileSelector.SFD.Filter = FileSelector.Filter;
			string result;
			if (FileSelector.SFD.ShowDialog() == DialogResult.OK)
			{
				result = FileSelector.SFD.FileName;
			}
			else
			{
				result = null;
			}
			return result;
		}
		public static string BrowseFile(FileType type)
		{
			FileSelector.FileExtension = type;
			return FileSelector.BrowseFile();
		}
		public static string BrowseFile(string filter)
		{
			FileSelector.Filter = filter;
			return FileSelector.BrowseFile();
		}
		public static string[] BrowseFiles(FileType type)
		{
			FileSelector.FileExtension = type;
			return FileSelector.BrowseFiles();
		}
		public static string[] BrowseFiles(string filter)
		{
			FileSelector.Filter = filter;
			return FileSelector.BrowseFiles();
		}
		public static string BrowseFileForSave(FileType type)
		{
			FileSelector.FileExtension = type;
			return FileSelector.BrowseFileForSave();
		}
		public static string BrowseFileForSave(string filter)
		{
			FileSelector.Filter = filter;
			return FileSelector.BrowseFileForSave();
		}
	}
}
