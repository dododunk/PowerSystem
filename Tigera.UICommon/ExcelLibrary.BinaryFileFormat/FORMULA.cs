using System;
using System.IO;
namespace ExcelLibrary.BinaryFileFormat
{
	public class FORMULA : Record
	{
		public STRING StringRecord;
		public ushort RowIndex;
		public ushort ColIndex;
		public ushort XFIndex;
		public ulong Result;
		public ushort OptionFlags;
		public uint Unused;
		public byte[] FormulaData;
		public object DecodeResult()
		{
			byte[] bytes = BitConverter.GetBytes(this.Result);
			object result;
			if (bytes[6] == 255 && bytes[7] == 255)
			{
				switch (bytes[0])
				{
				case 0:
					if (this.StringRecord != null)
					{
						result = this.StringRecord.Value;
						return result;
					}
					break;

				case 1:
					result = Convert.ToBoolean(bytes[2]);
					return result;

				case 2:
					result = ErrorCode.ErrorCodes[bytes[2]];
					return result;

				case 3:
					result = string.Empty;
					return result;
				}
			}
			result = BitConverter.ToDouble(bytes, 0);
			return result;
		}
		public FORMULA(Record record) : base(record)
		{
		}
		public FORMULA()
		{
			this.Type = 6;
		}
		public override void Decode()
		{
			MemoryStream memoryStream = new MemoryStream(this.Data);
			BinaryReader binaryReader = new BinaryReader(memoryStream);
			this.RowIndex = binaryReader.ReadUInt16();
			this.ColIndex = binaryReader.ReadUInt16();
			this.XFIndex = binaryReader.ReadUInt16();
			this.Result = binaryReader.ReadUInt64();
			this.OptionFlags = binaryReader.ReadUInt16();
			this.Unused = binaryReader.ReadUInt32();
			this.FormulaData = binaryReader.ReadBytes(checked((int)(memoryStream.Length - memoryStream.Position)));
		}
		public override void Encode()
		{
			MemoryStream memoryStream = new MemoryStream();
			BinaryWriter binaryWriter = new BinaryWriter(memoryStream);
			binaryWriter.Write(this.RowIndex);
			binaryWriter.Write(this.ColIndex);
			binaryWriter.Write(this.XFIndex);
			binaryWriter.Write(this.Result);
			binaryWriter.Write(this.OptionFlags);
			binaryWriter.Write(this.Unused);
			binaryWriter.Write(this.FormulaData);
			this.Data = memoryStream.ToArray();
			this.Size = checked((ushort)this.Data.Length);
			base.Encode();
		}
	}
}
