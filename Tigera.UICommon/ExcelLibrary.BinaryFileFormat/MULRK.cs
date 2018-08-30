using System;
using System.Collections.Generic;
using System.IO;
namespace ExcelLibrary.BinaryFileFormat
{
	public class MULRK : Record
	{
		public List<uint> RKList;
		public List<ushort> XFList;
		public ushort RowIndex;
		public ushort FirstColIndex;
		public List<uint> XFRKList;
		public short LastColIndex;
		public override void Decode()
		{
			MemoryStream input = new MemoryStream(this.Data);
			BinaryReader binaryReader = new BinaryReader(input);
			this.RowIndex = binaryReader.ReadUInt16();
			this.FirstColIndex = binaryReader.ReadUInt16();
			checked
			{
				int num = (int)((this.Size - 6) / 6);
				this.RKList = new List<uint>(num);
				this.XFList = new List<ushort>(num);
				for (int i = 0; i < num; i++)
				{
					ushort item = binaryReader.ReadUInt16();
					uint item2 = binaryReader.ReadUInt32();
					this.XFList.Add(item);
					this.RKList.Add(item2);
				}
				this.LastColIndex = binaryReader.ReadInt16();
			}
		}
		public MULRK(Record record) : base(record)
		{
		}
		public MULRK()
		{
			this.Type = 189;
			this.XFRKList = new List<uint>();
		}
		public void decode()
		{
			MemoryStream input = new MemoryStream(this.Data);
			BinaryReader binaryReader = new BinaryReader(input);
			this.RowIndex = binaryReader.ReadUInt16();
			this.FirstColIndex = binaryReader.ReadUInt16();
			binaryReader.ReadUInt32();
			this.LastColIndex = binaryReader.ReadInt16();
		}
		public void encode()
		{
			MemoryStream memoryStream = new MemoryStream();
			BinaryWriter binaryWriter = new BinaryWriter(memoryStream);
			binaryWriter.Write(this.RowIndex);
			binaryWriter.Write(this.FirstColIndex);
			foreach (uint current in this.XFRKList)
			{
				binaryWriter.Write(current);
			}
			binaryWriter.Write(this.LastColIndex);
			this.Data = memoryStream.ToArray();
			this.Size = checked((ushort)this.Data.Length);
			base.Encode();
		}
	}
}
