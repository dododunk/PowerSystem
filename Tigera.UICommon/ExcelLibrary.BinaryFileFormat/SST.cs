using QiHe.CodeLib;
using System;
using System.IO;
namespace ExcelLibrary.BinaryFileFormat
{
	public class SST : Record
	{
		public RichTextFormat[] RichTextFormatting;
		public int TotalOccurance;
		public int NumStrings;
		public UniqueList<string> StringList;
		public override void Decode()
		{
			MemoryStream input = new MemoryStream(this.Data);
			BinaryReader binaryReader = new BinaryReader(input);
			this.TotalOccurance = binaryReader.ReadInt32();
			this.NumStrings = binaryReader.ReadInt32();
			this.StringList = new UniqueList<string>(this.NumStrings);
			this.RichTextFormatting = new RichTextFormat[this.NumStrings];
			StringDecoder stringDecoder = new StringDecoder(this, binaryReader);
			checked
			{
				for (int i = 0; i < this.NumStrings; i++)
				{
					this.StringList.Add(stringDecoder.ReadString(16, out this.RichTextFormatting[i]));
				}
			}
		}
		public override void Encode()
		{
			MemoryStream memoryStream = new MemoryStream();
			BinaryWriter binaryWriter = new BinaryWriter(memoryStream);
			this.NumStrings = this.StringList.Count;
			binaryWriter.Write(this.TotalOccurance);
			binaryWriter.Write(this.NumStrings);
			this.ContinuedRecords.Clear();
			Record record = this;
			checked
			{
				foreach (string text in this.StringList)
				{
					int stringDataLength = Record.GetStringDataLength(text);
					if (memoryStream.Length + unchecked((long)stringDataLength) > 8224L)
					{
						record.Data = memoryStream.ToArray();
						record.Size = (ushort)record.Data.Length;
						memoryStream = new MemoryStream();
						binaryWriter = new BinaryWriter(memoryStream);
						CONTINUE cONTINUE = new CONTINUE();
						this.ContinuedRecords.Add(cONTINUE);
						record = cONTINUE;
					}
					Record.WriteString(binaryWriter, text, 16);
				}
				record.Data = memoryStream.ToArray();
				record.Size = (ushort)record.Data.Length;
			}
		}
		public SST(Record record) : base(record)
		{
		}
		public SST()
		{
			this.Type = 252;
			this.StringList = new UniqueList<string>();
		}
		public void decode()
		{
			MemoryStream input = new MemoryStream(this.Data);
			BinaryReader binaryReader = new BinaryReader(input);
			this.TotalOccurance = binaryReader.ReadInt32();
			this.NumStrings = binaryReader.ReadInt32();
			binaryReader.ReadString();
		}
		public void encode()
		{
			MemoryStream memoryStream = new MemoryStream();
			BinaryWriter binaryWriter = new BinaryWriter(memoryStream);
			binaryWriter.Write(this.TotalOccurance);
			binaryWriter.Write(this.NumStrings);
			foreach (string value in this.StringList)
			{
				binaryWriter.Write(value);
			}
			this.Data = memoryStream.ToArray();
			this.Size = checked((ushort)this.Data.Length);
			base.Encode();
		}
	}
}
