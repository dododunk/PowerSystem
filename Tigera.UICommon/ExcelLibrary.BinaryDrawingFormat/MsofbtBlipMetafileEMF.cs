using System;
using System.IO;
namespace ExcelLibrary.BinaryDrawingFormat
{
	public class MsofbtBlipMetafileEMF : MsofbtBlip
	{
		public MsofbtBlipMetafileEMF(EscherRecord record) : base(record)
		{
		}
		public MsofbtBlipMetafileEMF()
		{
			this.Type = 61466;
		}
		public override void Decode()
		{
			MemoryStream memoryStream = new MemoryStream(this.Data);
			BinaryReader binaryReader = new BinaryReader(memoryStream);
			this.UID = new Guid(binaryReader.ReadBytes(16));
			this.Marker = binaryReader.ReadByte();
			this.ImageData = binaryReader.ReadBytes(checked((int)(memoryStream.Length - memoryStream.Position)));
		}
		public override void Encode()
		{
			MemoryStream memoryStream = new MemoryStream();
			BinaryWriter binaryWriter = new BinaryWriter(memoryStream);
			binaryWriter.Write(this.UID.ToByteArray());
			binaryWriter.Write(this.Marker);
			binaryWriter.Write(this.ImageData);
			this.Data = memoryStream.ToArray();
			this.Size = checked((uint)this.Data.Length);
			base.Encode();
		}
	}
}
