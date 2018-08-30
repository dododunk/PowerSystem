using System;
using System.IO;
namespace ExcelLibrary.BinaryFileFormat
{
	public class WINDOW1 : Record
	{
		public ushort HorizontalPosition;
		public ushort VerticalPosition;
		public ushort WindowWidth;
		public ushort WindowHeight;
		public ushort OptionFlags;
		public ushort ActiveWorksheet;
		public ushort FirstVisibleTab;
		public ushort SelecteWorksheets;
		public ushort TabBarWidth;
		public WINDOW1(Record record) : base(record)
		{
		}
		public WINDOW1()
		{
			this.Type = 61;
		}
		public override void Decode()
		{
			MemoryStream input = new MemoryStream(this.Data);
			BinaryReader binaryReader = new BinaryReader(input);
			this.HorizontalPosition = binaryReader.ReadUInt16();
			this.VerticalPosition = binaryReader.ReadUInt16();
			this.WindowWidth = binaryReader.ReadUInt16();
			this.WindowHeight = binaryReader.ReadUInt16();
			this.OptionFlags = binaryReader.ReadUInt16();
			this.ActiveWorksheet = binaryReader.ReadUInt16();
			this.FirstVisibleTab = binaryReader.ReadUInt16();
			this.SelecteWorksheets = binaryReader.ReadUInt16();
			this.TabBarWidth = binaryReader.ReadUInt16();
		}
		public override void Encode()
		{
			MemoryStream memoryStream = new MemoryStream();
			BinaryWriter binaryWriter = new BinaryWriter(memoryStream);
			binaryWriter.Write(this.HorizontalPosition);
			binaryWriter.Write(this.VerticalPosition);
			binaryWriter.Write(this.WindowWidth);
			binaryWriter.Write(this.WindowHeight);
			binaryWriter.Write(this.OptionFlags);
			binaryWriter.Write(this.ActiveWorksheet);
			binaryWriter.Write(this.FirstVisibleTab);
			binaryWriter.Write(this.SelecteWorksheets);
			binaryWriter.Write(this.TabBarWidth);
			this.Data = memoryStream.ToArray();
			this.Size = checked((ushort)this.Data.Length);
			base.Encode();
		}
	}
}
