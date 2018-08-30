using QiHe.CodeLib;
using System;
using System.IO;
using System.Text;
namespace ExcelLibrary.BinaryDrawingFormat
{
	public class MsofbtBSE : EscherRecord
	{
		public byte BlipTypeWin32;
		public byte BlipTypeMacOS;
		public Guid UID;
		public ushort Tag;
		public uint BlipSize;
		public int Ref;
		public int Offset;
		public byte Usage;
		public byte NameLength;
		public byte Unused2;
		public byte Unused3;
		public string BlipName;
		public MsofbtBlip BlipRecord;
		public byte[] ImageData;
		public byte[] ExtraData;
		public MsofbtBSE(EscherRecord record) : base(record)
		{
		}
		public MsofbtBSE()
		{
			this.Type = 61447;
		}
		public void decode()
		{
			MemoryStream input = new MemoryStream(this.Data);
			BinaryReader binaryReader = new BinaryReader(input);
			this.BlipTypeWin32 = binaryReader.ReadByte();
			this.BlipTypeMacOS = binaryReader.ReadByte();
			this.UID = new Guid(binaryReader.ReadBytes(16));
			this.Tag = binaryReader.ReadUInt16();
			this.BlipSize = binaryReader.ReadUInt32();
			this.Ref = binaryReader.ReadInt32();
			this.Offset = binaryReader.ReadInt32();
			this.Usage = binaryReader.ReadByte();
			this.NameLength = binaryReader.ReadByte();
			this.Unused2 = binaryReader.ReadByte();
			this.Unused3 = binaryReader.ReadByte();
		}
		public void encode()
		{
			MemoryStream memoryStream = new MemoryStream();
			BinaryWriter binaryWriter = new BinaryWriter(memoryStream);
			binaryWriter.Write(this.BlipTypeWin32);
			binaryWriter.Write(this.BlipTypeMacOS);
			binaryWriter.Write(this.UID.ToByteArray());
			binaryWriter.Write(this.Tag);
			binaryWriter.Write(this.BlipSize);
			binaryWriter.Write(this.Ref);
			binaryWriter.Write(this.Offset);
			binaryWriter.Write(this.Usage);
			binaryWriter.Write(this.NameLength);
			binaryWriter.Write(this.Unused2);
			binaryWriter.Write(this.Unused3);
			this.Data = memoryStream.ToArray();
			this.Size = checked((uint)this.Data.Length);
			base.Encode();
		}
		internal void SetBlipType(ushort imageFormat)
		{
			byte b = BlipType.FromImageFormat(imageFormat);
			base.Instance = (ushort)b;
			this.BlipTypeWin32 = b;
			this.BlipTypeMacOS = b;
			this.BlipRecord.Instance = BlipSignature.FromBlipType(b);
		}
		public override void Decode()
		{
			MemoryStream memoryStream = new MemoryStream(this.Data);
			BinaryReader binaryReader = new BinaryReader(memoryStream);
			this.BlipTypeWin32 = binaryReader.ReadByte();
			this.BlipTypeMacOS = binaryReader.ReadByte();
			this.UID = new Guid(binaryReader.ReadBytes(16));
			this.Tag = binaryReader.ReadUInt16();
			this.BlipSize = binaryReader.ReadUInt32();
			this.Ref = binaryReader.ReadInt32();
			this.Offset = binaryReader.ReadInt32();
			this.Usage = binaryReader.ReadByte();
			this.NameLength = binaryReader.ReadByte();
			this.Unused2 = binaryReader.ReadByte();
			this.Unused3 = binaryReader.ReadByte();
			if (this.NameLength > 0)
			{
				this.BlipName = Encoding.Unicode.GetString(binaryReader.ReadBytes((int)this.NameLength));
			}
			if (memoryStream.Position < memoryStream.Length)
			{
				this.BlipRecord = (EscherRecord.Read(memoryStream) as MsofbtBlip);
				if (this.BlipRecord == null)
				{
					throw new Exception("Image Type Not supported.");
				}
				this.BlipRecord.Decode();
				this.ImageData = this.BlipRecord.ImageData;
			}
			if (memoryStream.Position < memoryStream.Length)
			{
				this.ExtraData = StreamHelper.ReadToEnd(memoryStream);
			}
		}
		public override void Encode()
		{
			this.BlipRecord.Encode();
			checked
			{
				this.BlipSize = this.BlipRecord.Size + 8u;
				if (this.BlipName != null)
				{
					this.NameLength = (byte)this.BlipName.Length;
				}
				MemoryStream memoryStream = new MemoryStream();
				BinaryWriter binaryWriter = new BinaryWriter(memoryStream);
				binaryWriter.Write(this.BlipTypeWin32);
				binaryWriter.Write(this.BlipTypeMacOS);
				binaryWriter.Write(this.UID.ToByteArray());
				binaryWriter.Write(this.Tag);
				binaryWriter.Write(this.BlipSize);
				binaryWriter.Write(this.Ref);
				binaryWriter.Write(this.Offset);
				binaryWriter.Write(this.Usage);
				binaryWriter.Write(this.NameLength);
				binaryWriter.Write(this.Unused2);
				binaryWriter.Write(this.Unused3);
				if (this.NameLength > 0)
				{
					binaryWriter.Write(Encoding.Unicode.GetBytes(this.BlipName));
				}
				this.BlipRecord.Write(binaryWriter);
				this.Data = memoryStream.ToArray();
				this.Size = (uint)((ushort)this.Data.Length);
				base.Encode();
			}
		}
	}
}
