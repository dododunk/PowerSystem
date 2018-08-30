using System;
using System.IO;
namespace ExcelLibrary.BinaryFileFormat
{
	public class BOOLERR : CellValue
	{
		public byte Value;
		public byte ValueType;
		public object GetValue()
		{
			object result;
			if (this.ValueType == 0)
			{
				result = (this.Value == 1);
			}
			else
			{
				result = ErrorCode.ErrorCodes[this.Value];
			}
			return result;
		}
		public BOOLERR(Record record) : base(record)
		{
		}
		public BOOLERR()
		{
			this.Type = 517;
		}
		public override void Decode()
		{
			MemoryStream input = new MemoryStream(this.Data);
			BinaryReader binaryReader = new BinaryReader(input);
			this.RowIndex = binaryReader.ReadUInt16();
			this.ColIndex = binaryReader.ReadUInt16();
			this.XFIndex = binaryReader.ReadUInt16();
			this.Value = binaryReader.ReadByte();
			this.ValueType = binaryReader.ReadByte();
		}
		public override void Encode()
		{
			MemoryStream memoryStream = new MemoryStream();
			BinaryWriter binaryWriter = new BinaryWriter(memoryStream);
			binaryWriter.Write(this.RowIndex);
			binaryWriter.Write(this.ColIndex);
			binaryWriter.Write(this.XFIndex);
			binaryWriter.Write(this.Value);
			binaryWriter.Write(this.ValueType);
			this.Data = memoryStream.ToArray();
			this.Size = checked((ushort)this.Data.Length);
			base.Encode();
		}
	}
}
