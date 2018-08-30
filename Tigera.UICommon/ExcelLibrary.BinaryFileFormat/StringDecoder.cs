using System;
using System.IO;
using System.Text;
namespace ExcelLibrary.BinaryFileFormat
{
	public class StringDecoder
	{
		private Record record;
		private BinaryReader reader;
		private int ContinuedIndex = -1;
		public StringDecoder(Record record, BinaryReader reader)
		{
			this.record = record;
			this.reader = reader;
		}
		public string ReadString(int lengthbits)
		{
			checked
			{
				string result;
				if (this.reader.BaseStream.Position == this.reader.BaseStream.Length)
				{
					if (this.ContinuedIndex >= this.record.ContinuedRecords.Count - 1)
					{
						result = null;
						return result;
					}
					this.SwitchToContinuedRecord();
				}
				int num = (int)((lengthbits == 8) ? ((ushort)this.reader.ReadByte()) : this.reader.ReadUInt16());
				byte b = this.reader.ReadByte();
				bool compressed = (b & 1) == 0;
				bool flag = (b & 4) == 4;
				bool flag2 = (b & 8) == 8;
				int num2 = 0;
				int num3 = 0;
				if (flag2)
				{
					num2 = (int)this.reader.ReadUInt16();
				}
				if (flag)
				{
					num3 = this.reader.ReadInt32();
				}
				string text = this.ReadString(num, compressed);
				StringBuilder stringBuilder = new StringBuilder();
				stringBuilder.Append(text);
				if (text.Length < num)
				{
					this.SwitchToContinuedRecord();
					stringBuilder.Append(this.ReadContinuedString(num - text.Length));
				}
				this.ReadBytes(4 * num2 + num3);
				result = stringBuilder.ToString();
				return result;
			}
		}
		private string ReadString(int stringlength, bool compressed)
		{
			checked
			{
				byte[] array2;
				if (compressed)
				{
					byte[] array = this.reader.ReadBytes(stringlength);
					array2 = new byte[array.Length * 2];
					for (int i = 0; i < array.Length; i++)
					{
						array2[i * 2] = array[i];
						array2[i * 2 + 1] = 0;
					}
				}
				else
				{
					array2 = this.reader.ReadBytes(stringlength * 2);
				}
				return Encoding.Unicode.GetString(array2);
			}
		}
		private string ReadContinuedString(int stringlength)
		{
			string result;
			if (this.reader.BaseStream.Position == this.reader.BaseStream.Length)
			{
				result = null;
			}
			else
			{
				byte b = this.reader.ReadByte();
				bool compressed = (b & 1) == 0;
				string text = this.ReadString(stringlength, compressed);
				if (text.Length < stringlength)
				{
					this.SwitchToContinuedRecord();
					StringBuilder stringBuilder = new StringBuilder();
					stringBuilder.Append(text);
					stringBuilder.Append(this.ReadContinuedString(checked(stringlength - text.Length)));
					result = stringBuilder.ToString();
				}
				else
				{
					result = text;
				}
			}
			return result;
		}
		private byte[] ReadBytes(int count)
		{
			byte[] array = this.reader.ReadBytes(count);
			int num = array.Length;
			byte[] result;
			if (num < count)
			{
				this.SwitchToContinuedRecord();
				byte[] array2 = new byte[count];
				byte[] array3 = this.ReadBytes(checked(count - num));
				array.CopyTo(array2, 0);
				array3.CopyTo(array2, num);
				result = array2;
			}
			else
			{
				result = array;
			}
			return result;
		}
		private void SwitchToContinuedRecord()
		{
			checked
			{
				this.ContinuedIndex++;
				MemoryStream input = new MemoryStream(this.record.ContinuedRecords[this.ContinuedIndex].Data);
				this.reader = new BinaryReader(input);
			}
		}
		public string ReadString(int lengthbits, out RichTextFormat rtf)
		{
			checked
			{
				string result;
				if (this.reader.BaseStream.Position == this.reader.BaseStream.Length)
				{
					if (this.ContinuedIndex >= this.record.ContinuedRecords.Count - 1)
					{
						rtf = null;
						result = null;
						return result;
					}
					this.SwitchToContinuedRecord();
				}
				int num = (int)((lengthbits == 8) ? ((ushort)this.reader.ReadByte()) : this.reader.ReadUInt16());
				byte b = this.reader.ReadByte();
				bool compressed = (b & 1) == 0;
				bool flag = (b & 4) == 4;
				bool flag2 = (b & 8) == 8;
				int num2 = 0;
				int num3 = 0;
				if (flag2)
				{
					num2 = (int)this.reader.ReadUInt16();
				}
				if (flag)
				{
					num3 = this.reader.ReadInt32();
				}
				string text = this.ReadString(num, compressed);
				StringBuilder stringBuilder = new StringBuilder();
				stringBuilder.Append(text);
				if (text.Length < num)
				{
					this.SwitchToContinuedRecord();
					stringBuilder.Append(this.ReadContinuedString(num - text.Length));
				}
				if (num > 2000 || text.Length > 2000 || num3 > 2000)
				{
					throw new Exception("invalid size of rich text formatting information");
				}
				byte[] richTextBytes = this.ReadBytes(4 * num2 + num3);
				rtf = this.DecodeRichTextFormatting(richTextBytes, num2);
				result = stringBuilder.ToString();
				return result;
			}
		}
		private RichTextFormat DecodeRichTextFormatting(byte[] richTextBytes, int runs)
		{
			RichTextFormat richTextFormat = new RichTextFormat(runs);
			checked
			{
				for (int i = 0; i < runs; i++)
				{
					richTextFormat.CharIndexes.Add(BitConverter.ToUInt16(richTextBytes, i * 4));
					richTextFormat.FontIndexes.Add(BitConverter.ToUInt16(richTextBytes, i * 4 + 2));
				}
				return richTextFormat;
			}
		}
	}
}
