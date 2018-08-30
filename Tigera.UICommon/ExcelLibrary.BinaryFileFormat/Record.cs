using QiHe.CodeLib;
using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
namespace ExcelLibrary.BinaryFileFormat
{
	public class Record
	{
		public const ushort MaxContentLength = 8224;
		public ushort Type;
		public ushort Size;
		public byte[] Data;
		public List<Record> ContinuedRecords;
		public int FullSize
		{
			get
			{
				checked
				{
					int num = (int)(4 + this.Size);
					foreach (Record current in this.ContinuedRecords)
					{
						num += (int)(4 + current.Size);
					}
					return num;
				}
			}
		}
		public int TotalSize
		{
			get
			{
				int num = (int)this.Size;
				checked
				{
					foreach (Record current in this.ContinuedRecords)
					{
						num += (int)current.Size;
					}
					return num;
				}
			}
		}
		public byte[] AllData
		{
			get
			{
				byte[] result;
				if (this.ContinuedRecords.Count == 0)
				{
					result = this.Data;
				}
				else
				{
					List<byte> list = new List<byte>(this.TotalSize);
					list.AddRange(this.Data);
					foreach (Record current in this.ContinuedRecords)
					{
						list.AddRange(current.AllData);
					}
					result = list.ToArray();
				}
				return result;
			}
		}
		public Record()
		{
			this.ContinuedRecords = new List<Record>();
		}
		public Record(Record record)
		{
			this.Type = record.Type;
			this.Size = record.Size;
			this.Data = record.Data;
			this.ContinuedRecords = record.ContinuedRecords;
		}
		public virtual void Decode()
		{
		}
		public virtual void Encode()
		{
			this.ContinuedRecords.Clear();
			checked
			{
				if (this.Size > 0 && this.Data.Length > 8224)
				{
					int num;
					for (int i = 8224; i < this.Data.Length; i += num)
					{
						CONTINUE cONTINUE = new CONTINUE();
						num = Math.Min(8224, this.Data.Length - i);
						cONTINUE.Data = Algorithm.ArraySection(this.Data, i, num);
						cONTINUE.Size = (ushort)num;
						this.ContinuedRecords.Add(cONTINUE);
					}
					this.Size = 8224;
					this.Data = Algorithm.ArraySection(this.Data, 0, 8224);
				}
			}
		}
		public static Record ReadBase(Stream stream)
		{
			BinaryReader binaryReader = new BinaryReader(stream);
			Record record = new Record();
			record.Type = binaryReader.ReadUInt16();
			record.Size = binaryReader.ReadUInt16();
			record.Data = binaryReader.ReadBytes((int)record.Size);
			return record;
		}
		public static object DecodeRK(uint value)
		{
			bool flag = (value & 1u) == 1u;
			bool flag2 = (value & 2u) == 0u;
			object result;
			if (flag2)
			{
				ulong data = (ulong)(value & 4294967292u) << 32;
				double num = Record.TreatUInt64AsDouble(data);
				if (flag)
				{
					num /= 100.0;
				}
				result = num;
			}
			else
			{
				int num2 = checked((int)(value & 4294967292u)) >> 2;
				if (flag)
				{
					result = num2 / 100m;
				}
				else
				{
					result = num2;
				}
			}
			return result;
		}
		public static double TreatUInt64AsDouble(ulong data)
		{
			byte[] bytes = BitConverter.GetBytes(data);
			return BitConverter.ToDouble(bytes, 0);
		}
		public void Write(BinaryWriter writer)
		{
			writer.Write(this.Type);
			writer.Write(this.Size);
			if (this.Size > 0)
			{
				writer.Write(this.Data);
				if (this.ContinuedRecords.Count > 0)
				{
					foreach (Record current in this.ContinuedRecords)
					{
						writer.Write(current.Type);
						writer.Write(current.Size);
						writer.Write(current.Data);
					}
				}
			}
		}
		public string ReadString(BinaryReader reader, int lengthbits)
		{
			StringDecoder stringDecoder = new StringDecoder(this, reader);
			return stringDecoder.ReadString(lengthbits);
		}
		public static void WriteString(BinaryWriter writer, string text, int lengthbits)
		{
			checked
			{
				if (lengthbits == 8)
				{
					writer.Write((byte)text.Length);
				}
				else
				{
					if (lengthbits != 16)
					{
						throw new ArgumentException("Invalid lengthbits, must be 8 or 16.");
					}
					writer.Write((ushort)text.Length);
				}
				if (TextEncoding.FitsInASCIIEncoding(text))
				{
					writer.Write(0);
					writer.Write(Encoding.ASCII.GetBytes(text));
				}
				else
				{
					writer.Write(1);
					writer.Write(Encoding.Unicode.GetBytes(text));
				}
			}
		}
		public static int GetStringDataLength(string text)
		{
			checked
			{
				int result;
				if (TextEncoding.FitsInASCIIEncoding(text))
				{
					result = Encoding.ASCII.GetByteCount(text) + 3;
				}
				else
				{
					result = text.Length * 2 + 3;
				}
				return result;
			}
		}
		public static void EncodeRecords(List<Record> records)
		{
			foreach (Record current in records)
			{
				current.Encode();
			}
		}
		public static int CountDataLength(List<Record> records)
		{
			int num = 0;
			checked
			{
				foreach (Record current in records)
				{
					num += current.FullSize;
				}
				return num;
			}
		}
		public static Record Read(Stream stream)
		{
			Record record = Record.ReadBase(stream);
			ushort type = record.Type;
			Record result;
			if (type <= 146)
			{
				if (type <= 49)
				{
					if (type <= 13)
					{
						if (type == 6)
						{
							result = new FORMULA(record);
							return result;
						}
						switch (type)
						{
						case 10:
							result = new EOF(record);
							return result;

						case 12:
							result = new CALCCOUNT(record);
							return result;

						case 13:
							result = new CALCMODE(record);
							return result;
						}
					}
					else
					{
						if (type == 34)
						{
							result = new DATEMODE(record);
							return result;
						}
						if (type == 41)
						{
							result = new BOTTOMMARGIN(record);
							return result;
						}
						if (type == 49)
						{
							result = new FONT(record);
							return result;
						}
					}
				}
				else
				{
					if (type <= 93)
					{
						switch (type)
						{
						case 60:
							result = new CONTINUE(record);
							return result;

						case 61:
							result = new WINDOW1(record);
							return result;

						case 62:
						case 63:
						case 65:
							break;

						case 64:
							result = new BACKUP(record);
							return result;

						case 66:
							result = new CODEPAGE(record);
							return result;

						default:
							if (type == 85)
							{
								result = new DEFCOLWIDTH(record);
								return result;
							}
							if (type == 93)
							{
								result = new OBJ(record);
								return result;
							}
							break;
						}
					}
					else
					{
						if (type == 125)
						{
							result = new COLINFO(record);
							return result;
						}
						if (type == 133)
						{
							result = new BOUNDSHEET(record);
							return result;
						}
						if (type == 146)
						{
							result = new PALETTE(record);
							return result;
						}
					}
				}
			}
			else
			{
				if (type <= 237)
				{
					if (type <= 190)
					{
						if (type == 153)
						{
							result = new STANDARDWIDTH(record);
							return result;
						}
						switch (type)
						{
						case 189:
							result = new MULRK(record);
							return result;

						case 190:
							result = new MULBLANK(record);
							return result;
						}
					}
					else
					{
						switch (type)
						{
						case 214:
							result = new RSTRING(record);
							return result;

						case 215:
							result = new DBCELL(record);
							return result;

						case 216:
						case 217:
							break;

						case 218:
							result = new BOOKBOOL(record);
							return result;

						default:
							if (type == 224)
							{
								result = new XF(record);
								return result;
							}
							switch (type)
							{
							case 233:
								result = new BITMAP(record);
								return result;

							case 235:
								result = new MSODRAWINGGROUP(record);
								return result;

							case 236:
								result = new MSODRAWING(record);
								return result;

							case 237:
								result = new MSODRAWINGSELECTION(record);
								return result;
							}
							break;
						}
					}
				}
				else
				{
					if (type <= 545)
					{
						switch (type)
						{
						case 252:
							result = new SST(record);
							return result;

						case 253:
							result = new LABELSST(record);
							return result;

						case 254:
							break;

						case 255:
							result = new EXTSST(record);
							return result;

						default:
							switch (type)
							{
							case 512:
								result = new DIMENSIONS(record);
								return result;

							case 513:
								result = new BLANK(record);
								return result;

							case 514:
							case 516:
							case 518:
								break;

							case 515:
								result = new NUMBER(record);
								return result;

							case 517:
								result = new BOOLERR(record);
								return result;

							case 519:
								result = new STRING(record);
								return result;

							case 520:
								result = new ROW(record);
								return result;

							default:
								if (type == 545)
								{
									result = new ARRAY(record);
									return result;
								}
								break;
							}
							break;
						}
					}
					else
					{
						if (type == 638)
						{
							result = new RK(record);
							return result;
						}
						if (type == 1054)
						{
							result = new FORMAT(record);
							return result;
						}
						if (type == 2057)
						{
							result = new BOF(record);
							return result;
						}
					}
				}
			}
			result = record;
			return result;
		}
	}
}
