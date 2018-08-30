using System;
using System.IO;
namespace ExcelLibrary.BinaryDrawingFormat
{
	public class EscherRecord
	{
		public ushort Prop;
		public ushort Type;
		public uint Size;
		public byte[] Data;
		public ushort Instance
		{
			get
			{
				return checked((ushort)(this.Prop >> 4));
			}
			set
			{
				this.Prop = checked((ushort)((int)this.Version | (int)value << 4));
			}
		}
		public byte Version
		{
			get
			{
				return checked((byte)(this.Prop & 15));
			}
			set
			{
				this.Prop |= (ushort)(value & 15);
			}
		}
		public EscherRecord()
		{
		}
		public EscherRecord(EscherRecord record)
		{
			this.Prop = record.Prop;
			this.Type = record.Type;
			this.Size = record.Size;
			this.Data = record.Data;
		}
		public virtual void Decode()
		{
		}
		public virtual void Encode()
		{
		}
		public static EscherRecord ReadBase(Stream stream)
		{
			BinaryReader binaryReader = new BinaryReader(stream);
			EscherRecord escherRecord = new EscherRecord();
			escherRecord.Prop = binaryReader.ReadUInt16();
			escherRecord.Type = binaryReader.ReadUInt16();
			escherRecord.Size = binaryReader.ReadUInt32();
			escherRecord.Data = binaryReader.ReadBytes(checked((int)escherRecord.Size));
			return escherRecord;
		}
		public void Write(BinaryWriter writer)
		{
			if (this is MsofbtContainer)
			{
				this.Version = 15;
			}
			writer.Write(this.Prop);
			writer.Write(this.Type);
			writer.Write(this.Size);
			if (this.Size > 0u)
			{
				writer.Write(this.Data);
			}
		}
		public static EscherRecord Read(Stream stream)
		{
			EscherRecord escherRecord = EscherRecord.ReadBase(stream);
			ushort type = escherRecord.Type;
			EscherRecord result;
			switch (type)
			{
			case 61440:
				result = new MsofbtDggContainer(escherRecord);
				return result;

			case 61441:
				result = new MsofbtBstoreContainer(escherRecord);
				return result;

			case 61442:
				result = new MsofbtDgContainer(escherRecord);
				return result;

			case 61443:
				result = new MsofbtSpgrContainer(escherRecord);
				return result;

			case 61444:
				result = new MsofbtSpContainer(escherRecord);
				return result;

			case 61445:
				result = new MsofbtSolverContainer(escherRecord);
				return result;

			case 61446:
				result = new MsofbtDgg(escherRecord);
				return result;

			case 61447:
				result = new MsofbtBSE(escherRecord);
				return result;

			case 61448:
				result = new MsofbtDg(escherRecord);
				return result;

			case 61449:
				result = new MsofbtSpgr(escherRecord);
				return result;

			case 61450:
				result = new MsofbtSp(escherRecord);
				return result;

			case 61451:
				result = new MsofbtOPT(escherRecord);
				return result;

			case 61452:
				result = new MsofbtTextbox(escherRecord);
				return result;

			case 61453:
				result = new MsofbtClientTextbox(escherRecord);
				return result;

			case 61454:
				result = new MsofbtAnchor(escherRecord);
				return result;

			case 61455:
				result = new MsofbtChildAnchor(escherRecord);
				return result;

			case 61456:
				result = new MsofbtClientAnchor(escherRecord);
				return result;

			case 61457:
				result = new MsofbtClientData(escherRecord);
				return result;

			case 61458:
				result = new MsofbtConnectorRule(escherRecord);
				return result;

			case 61459:
				result = new MsofbtAlignRule(escherRecord);
				return result;

			case 61460:
				result = new MsofbtArcRule(escherRecord);
				return result;

			case 61461:
				result = new MsofbtClientRule(escherRecord);
				return result;

			case 61462:
				result = new MsofbtCLSID(escherRecord);
				return result;

			case 61463:
				result = new MsofbtCalloutRule(escherRecord);
				return result;

			case 61464:
				result = new MsofbtBlipStart(escherRecord);
				return result;

			case 61465:
				break;

			case 61466:
				result = new MsofbtBlipMetafileEMF(escherRecord);
				return result;

			case 61467:
				result = new MsofbtBlipMetafileWMF(escherRecord);
				return result;

			case 61468:
				result = new MsofbtBlipMetafilePICT(escherRecord);
				return result;

			case 61469:
				result = new MsofbtBlipBitmapJPEG(escherRecord);
				return result;

			case 61470:
				result = new MsofbtBlipBitmapPNG(escherRecord);
				return result;

			case 61471:
				result = new MsofbtBlipBitmapDIB(escherRecord);
				return result;

			default:
				switch (type)
				{
				case 61719:
					result = new MsofbtBlipEnd(escherRecord);
					return result;

				case 61720:
					result = new MsofbtRegroupItems(escherRecord);
					return result;

				case 61721:
					result = new MsofbtSelection(escherRecord);
					return result;

				case 61722:
					result = new MsofbtColorMRU(escherRecord);
					return result;

				case 61725:
					result = new MsofbtDeletedPspl(escherRecord);
					return result;

				case 61726:
					result = new MsofbtSplitMenuColors(escherRecord);
					return result;

				case 61727:
					result = new MsofbtOleObject(escherRecord);
					return result;

				case 61728:
					result = new MsofbtColorScheme(escherRecord);
					return result;
				}
				break;
			}
			result = escherRecord;
			return result;
		}
	}
}
