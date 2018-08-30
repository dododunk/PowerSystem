using System;
using System.IO;
namespace ExcelLibrary.BinaryFileFormat
{
	public class SubRecord : Record
	{
		public SubRecord()
		{
		}
		public SubRecord(SubRecord record) : base(record)
		{
		}
		public new static SubRecord ReadBase(Stream stream)
		{
			BinaryReader binaryReader = new BinaryReader(stream);
			SubRecord subRecord = new SubRecord();
			subRecord.Type = binaryReader.ReadUInt16();
			subRecord.Size = binaryReader.ReadUInt16();
			subRecord.Data = binaryReader.ReadBytes((int)subRecord.Size);
			return subRecord;
		}
		public new static SubRecord Read(Stream stream)
		{
			SubRecord subRecord = SubRecord.ReadBase(stream);
			ushort type = subRecord.Type;
			SubRecord result;
			if (type != 0)
			{
				switch (type)
				{
				case 6:
					result = new GroupMarker(subRecord);
					break;

				case 7:
					result = new ClipboardFormat(subRecord);
					break;

				case 8:
					result = new PictureOption(subRecord);
					break;

				default:
					if (type != 21)
					{
						result = subRecord;
					}
					else
					{
						result = new CommonObjectData(subRecord);
					}
					break;
				}
			}
			else
			{
				result = new End(subRecord);
			}
			return result;
		}
	}
}
