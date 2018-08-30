using QiHe.CodeLib;
using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
namespace ExcelLibrary.CompoundDocumentFormat
{
	public class CompoundDocument
	{
		internal FileHeader Header;
		internal int SectorSize;
		internal int ShortSectorSize;
		private int TotalSectors;
		internal MasterSectorAllocation MasterSectorAllocation;
		internal SectorAllocation SectorAllocation;
		internal ShortSectorAllocation ShortSectorAllocation;
		private MemoryStream ShortStreamContainer;
		private MemoryStream DirectoryStream;
		private Dictionary<int, DirectoryEntry> DirectoryEntries;
		internal Stream FileStorage;
		private BinaryReader Reader;
		private BinaryWriter Writer;
		public DirectoryEntry RootStorage
		{
			get
			{
				return this.DirectoryEntries[0];
			}
		}
		internal CompoundDocument(Stream stream, FileHeader header)
		{
			this.FileStorage = stream;
			this.Reader = new BinaryReader(this.FileStorage);
			this.Writer = new BinaryWriter(this.FileStorage, Encoding.Unicode);
			this.Header = header;
			checked
			{
				this.SectorSize = (int)Math.Pow(2.0, (double)this.Header.SectorSizeInPot);
				this.ShortSectorSize = (int)Math.Pow(2.0, (double)this.Header.ShortSectorSizeInPot);
				this.TotalSectors = ((stream.Length == 0L) ? 0 : ((int)(stream.Length - 512L) / this.SectorSize));
				this.MasterSectorAllocation = new MasterSectorAllocation(this);
				this.SectorAllocation = new SectorAllocation(this);
				this.ShortSectorAllocation = new ShortSectorAllocation(this);
			}
		}
		public static CompoundDocument Create(string file)
		{
			FileStream stream = File.Open(file, FileMode.Create, FileAccess.ReadWrite, FileShare.Read);
			CompoundDocument compoundDocument = new CompoundDocument(stream, new CompoundFileHeader());
			compoundDocument.WriteHeader();
			compoundDocument.MasterSectorAllocation.AllocateSATSector();
			compoundDocument.InitializeDirectoryEntries();
			return compoundDocument;
		}
		public static CompoundDocument Open(string file)
		{
			FileStream fileStream = File.Open(file, FileMode.Open, FileAccess.ReadWrite, FileShare.Read);
			BinaryReader reader = new BinaryReader(fileStream);
			FileHeader header = CompoundDocument.ReadHeader(reader);
			CompoundDocument compoundDocument = new CompoundDocument(fileStream, header);
			CompoundDocument result;
			if (!compoundDocument.CheckHeader())
			{
				result = null;
			}
			else
			{
				compoundDocument.ReadDirectoryEntries();
				result = compoundDocument;
			}
			return result;
		}
		public void Save()
		{
			this.SaveDirectoryEntries();
			this.SaveShortStreams();
			this.WriteHeader();
			this.Writer.Flush();
		}
		public void Close()
		{
			this.FileStorage.Close();
		}
		private bool CheckHeader()
		{
			if (!CompoundDocument.ArrayEqual(this.Header.FileTypeIdentifier, CompoundFileHeader.FileTypeIdentifier))
			{
				throw new Exception("File header not recognized.");
			}
			if (!CompoundDocument.ArrayEqual(this.Header.ByteOrderMark, ByteOrderMarks.LittleEndian))
			{
				throw new Exception("Endian not implemented.");
			}
			return true;
		}
		private void InitializeDirectoryEntries()
		{
			this.Header.FirstSectorIDofDirectoryStream = this.AllocateDataSector();
			this.DirectoryEntries = new Dictionary<int, DirectoryEntry>();
			DirectoryEntry directoryEntry = new DirectoryEntry(this, "Root Entry");
			directoryEntry.EntryType = 5;
			directoryEntry.NodeColor = 1;
			directoryEntry.FirstSectorID = this.AllocateDataSector();
			directoryEntry.StreamLength = 0;
			this.DirectoryEntries.Add(0, directoryEntry);
			this.DirectoryStream = new MemoryStream();
			this.ShortStreamContainer = new MemoryStream();
		}
		private void SaveDirectoryEntries()
		{
			DirectoryTree.Build(this.RootStorage);
			this.DirectoryStream.Position = 0L;
			BinaryWriter writer = new BinaryWriter(this.DirectoryStream, Encoding.Unicode);
			checked
			{
				for (int i = 0; i < this.DirectoryEntries.Count; i++)
				{
					CompoundDocument.WriteDirectoryEntry(writer, this.DirectoryEntries[i]);
				}
				this.WriteStreamData(this.Header.FirstSectorIDofDirectoryStream, this.DirectoryStream.ToArray());
			}
		}
		private void SaveShortStreams()
		{
			this.ShortSectorAllocation.Save();
			this.WriteStreamData(this.RootStorage.FirstSectorID, this.ShortStreamContainer.ToArray());
		}
		internal int ReadInt32(long position)
		{
			this.FileStorage.Position = position;
			return this.Reader.ReadInt32();
		}
		internal int ReadInt32InSector(int secID, int position)
		{
			int sectorOffset = this.GetSectorOffset(secID);
			this.FileStorage.Position = (long)checked(sectorOffset + position);
			return this.Reader.ReadInt32();
		}
		internal void Write(long position, int integer)
		{
			this.FileStorage.Position = position;
			this.Writer.Write(integer);
		}
		internal void WriteInSector(int secID, int position, int integer)
		{
			int sectorOffset = this.GetSectorOffset(secID);
			this.FileStorage.Position = (long)checked(sectorOffset + position);
			this.Writer.Write(integer);
		}
		internal void WriteInSector(int secID, int position, int[] integers)
		{
			int sectorOffset = this.GetSectorOffset(secID);
			this.FileStorage.Position = (long)checked(sectorOffset + position);
			CompoundDocument.WriteArrayOfInt32(this.Writer, integers);
		}
		internal void WriteInSector(int secID, int position, byte[] data, int index, int count)
		{
			int sectorOffset = this.GetSectorOffset(secID);
			this.FileStorage.Position = (long)checked(sectorOffset + position);
			this.Writer.Write(data, index, count);
		}
		internal int AllocateNewSector()
		{
			int totalSectors = this.TotalSectors;
			this.FileStorage.Position = (long)this.GetSectorOffset(totalSectors);
			this.Writer.Write(new byte[this.SectorSize]);
			checked
			{
				this.TotalSectors++;
				return totalSectors;
			}
		}
		internal int AllocateDataSector()
		{
			return this.SectorAllocation.AllocateSector();
		}
		internal int AllocateDataSectorAfter(int sectorID)
		{
			int num = this.SectorAllocation.AllocateSector();
			this.SectorAllocation.LinkSectorID(sectorID, num);
			return num;
		}
		internal int AllocateNewSector(int[] sectorData)
		{
			int totalSectors = this.TotalSectors;
			this.FileStorage.Position = (long)this.GetSectorOffset(totalSectors);
			CompoundDocument.WriteArrayOfInt32(this.Writer, sectorData);
			checked
			{
				this.TotalSectors++;
				return totalSectors;
			}
		}
		internal int AllocateShortSector()
		{
			return this.ShortSectorAllocation.AllocateSector();
		}
		internal void AllocateNewShortSector()
		{
			this.ShortStreamContainer.Position = this.ShortStreamContainer.Length;
			byte[] array = new byte[this.ShortSectorSize];
			checked
			{
				for (int i = 0; i < array.Length; i++)
				{
					array[i] = 255;
				}
				this.ShortStreamContainer.Write(array, 0, this.ShortSectorSize);
				this.RootStorage.StreamLength = (int)this.ShortStreamContainer.Length;
			}
		}
		internal static int[] ReadArrayOfInt32(BinaryReader reader, int count)
		{
			int[] array = new int[count];
			checked
			{
				for (int i = 0; i < array.Length; i++)
				{
					array[i] = reader.ReadInt32();
				}
				return array;
			}
		}
		internal static void WriteArrayOfInt32(BinaryWriter writer, int[] data)
		{
			checked
			{
				for (int i = 0; i < data.Length; i++)
				{
					writer.Write(data[i]);
				}
			}
		}
		public static CompoundDocument Read(string file)
		{
			CompoundDocument compoundDocument = CompoundDocument.Open(file);
			compoundDocument.ReadAllStreamData();
			compoundDocument.Close();
			return compoundDocument;
		}
		private static FileHeader ReadHeader(BinaryReader reader)
		{
			return new FileHeader
			{
				FileTypeIdentifier = reader.ReadBytes(8),
				FileIdentifier = new Guid(reader.ReadBytes(16)),
				RevisionNumber = reader.ReadUInt16(),
				VersionNumber = reader.ReadUInt16(),
				ByteOrderMark = reader.ReadBytes(2),
				SectorSizeInPot = reader.ReadUInt16(),
				ShortSectorSizeInPot = reader.ReadUInt16(),
				UnUsed10 = reader.ReadBytes(10),
				NumberOfSATSectors = reader.ReadInt32(),
				FirstSectorIDofDirectoryStream = reader.ReadInt32(),
				UnUsed4 = reader.ReadBytes(4),
				MinimumStreamSize = reader.ReadInt32(),
				FirstSectorIDofShortSectorAllocationTable = reader.ReadInt32(),
				NumberOfShortSectors = reader.ReadInt32(),
				FirstSectorIDofMasterSectorAllocationTable = reader.ReadInt32(),
				NumberOfMasterSectors = reader.ReadInt32(),
				MasterSectorAllocationTable = CompoundDocument.ReadArrayOfInt32(reader, 109)
			};
		}
		private static DirectoryEntry ReadDirectoryEntry(BinaryReader reader)
		{
			return new DirectoryEntry
			{
				NameBuffer = reader.ReadChars(32),
				NameDataSize = reader.ReadUInt16(),
				EntryType = reader.ReadByte(),
				NodeColor = reader.ReadByte(),
				LeftChildDID = reader.ReadInt32(),
				RightChildDID = reader.ReadInt32(),
				MembersTreeNodeDID = reader.ReadInt32(),
				UniqueIdentifier = new Guid(reader.ReadBytes(16)),
				UserFlags = reader.ReadInt32(),
				CreationTime = DateTime.FromFileTime(reader.ReadInt64()),
				LastModificationTime = DateTime.FromFileTime(reader.ReadInt64()),
				FirstSectorID = reader.ReadInt32(),
				StreamLength = reader.ReadInt32(),
				UnUsed = reader.ReadInt32()
			};
		}
		private static bool ArrayEqual(byte[] bytes1, byte[] bytes2)
		{
			checked
			{
				bool result;
				if (bytes1.Length != bytes2.Length)
				{
					result = false;
				}
				else
				{
					for (int i = 0; i < bytes1.Length; i++)
					{
						if (bytes1[i] != bytes2[i])
						{
							result = false;
							return result;
						}
					}
					result = true;
				}
				return result;
			}
		}
		private void ReadDirectoryEntries()
		{
			this.DirectoryStream = new MemoryStream(this.GetStreamDataAsBytes(this.Header.FirstSectorIDofDirectoryStream));
			BinaryReader reader = new BinaryReader(this.DirectoryStream, Encoding.Unicode);
			this.DirectoryEntries = new Dictionary<int, DirectoryEntry>();
			DirectoryEntry directoryEntry = CompoundDocument.ReadDirectoryEntry(reader);
			directoryEntry.Document = this;
			directoryEntry.ID = 0;
			this.DirectoryEntries.Add(0, directoryEntry);
			this.ShortStreamContainer = new MemoryStream(this.GetStreamDataAsBytes(directoryEntry.FirstSectorID, directoryEntry.StreamLength));
			this.ReadDirectoryEntry(reader, directoryEntry.MembersTreeNodeDID, directoryEntry);
		}
		private void ReadDirectoryEntry(BinaryReader reader, int DID, DirectoryEntry parent)
		{
			if (DID != -1 && !this.DirectoryEntries.ContainsKey(DID))
			{
				reader.BaseStream.Position = (long)checked(DID * 128);
				DirectoryEntry directoryEntry = CompoundDocument.ReadDirectoryEntry(reader);
				directoryEntry.Document = this;
				directoryEntry.ID = DID;
				this.DirectoryEntries[DID] = directoryEntry;
				parent.AddChild(directoryEntry);
				this.ReadDirectoryEntry(reader, directoryEntry.LeftChildDID, parent);
				this.ReadDirectoryEntry(reader, directoryEntry.RightChildDID, parent);
				this.ReadDirectoryEntry(reader, directoryEntry.MembersTreeNodeDID, directoryEntry);
			}
		}
		private void ReadAllStreamData()
		{
			foreach (DirectoryEntry current in this.DirectoryEntries.Values)
			{
				current.Data = this.GetStreamData(current);
			}
		}
		private int GetSectorOffset(int SID)
		{
			return checked(512 + this.SectorSize * SID);
		}
		private int GetShortSectorOffset(int SSID)
		{
			return checked(this.ShortSectorSize * SSID);
		}
		internal int[] ReadSectorDataAsIntegers(int SID)
		{
			int sectorOffset = this.GetSectorOffset(SID);
			this.Reader.BaseStream.Position = (long)sectorOffset;
			return CompoundDocument.ReadArrayOfInt32(this.Reader, this.SectorSize / 4);
		}
		private byte[] ReadSectorDataAsBytes(int SID)
		{
			int sectorOffset = this.GetSectorOffset(SID);
			this.Reader.BaseStream.Position = (long)sectorOffset;
			return this.Reader.ReadBytes(this.SectorSize);
		}
		private byte[] ReadShortSectorDataAsBytes(int SSID)
		{
			int shortSectorOffset = this.GetShortSectorOffset(SSID);
			this.ShortStreamContainer.Seek((long)shortSectorOffset, SeekOrigin.Begin);
			return StreamHelper.ReadBytes(this.ShortStreamContainer, this.ShortSectorSize);
		}
		private byte[] GetStreamDataAsBytes(int StartSID)
		{
			List<int> sIDChain = this.SectorAllocation.GetSIDChain(StartSID);
			List<byte> list = new List<byte>();
			foreach (int current in sIDChain)
			{
				list.AddRange(this.ReadSectorDataAsBytes(current));
			}
			return list.ToArray();
		}
		private byte[] GetStreamDataAsBytes(int StartSID, int length)
		{
			List<int> sIDChain = this.SectorAllocation.GetSIDChain(StartSID);
			List<byte> list = new List<byte>();
			foreach (int current in sIDChain)
			{
				list.AddRange(this.ReadSectorDataAsBytes(current));
			}
			if (list.Count > length)
			{
				list.RemoveRange(length, checked(list.Count - length));
			}
			return list.ToArray();
		}
		internal List<int> GetStreamDataAsIntegers(int StartSID)
		{
			List<int> sIDChain = this.SectorAllocation.GetSIDChain(StartSID);
			List<int> list = new List<int>();
			foreach (int current in sIDChain)
			{
				list.AddRange(this.ReadSectorDataAsIntegers(current));
			}
			return list;
		}
		private byte[] GetShortStreamDataAsBytes(int StartSSID)
		{
			List<int> sIDChain = this.ShortSectorAllocation.GetSIDChain(StartSSID);
			List<byte> list = new List<byte>();
			foreach (int current in sIDChain)
			{
				list.AddRange(this.ReadShortSectorDataAsBytes(current));
			}
			return list.ToArray();
		}
		private byte[] GetShortStreamDataAsBytes(int StartSSID, int length)
		{
			List<int> sIDChain = this.ShortSectorAllocation.GetSIDChain(StartSSID);
			List<byte> list = new List<byte>();
			foreach (int current in sIDChain)
			{
				list.AddRange(this.ReadShortSectorDataAsBytes(current));
			}
			if (list.Count > length)
			{
				list.RemoveRange(length, checked(list.Count - length));
			}
			return list.ToArray();
		}
		public byte[] GetStreamData(DirectoryEntry entry)
		{
			byte[] result;
			if (entry.EntryType == 2)
			{
				if (entry.StreamLength < this.Header.MinimumStreamSize)
				{
					result = this.GetShortStreamDataAsBytes(entry.FirstSectorID, entry.StreamLength);
				}
				else
				{
					result = this.GetStreamDataAsBytes(entry.FirstSectorID, entry.StreamLength);
				}
			}
			else
			{
				result = null;
			}
			return result;
		}
		public DirectoryEntry FindDirectoryEntry(DirectoryEntry entry, string entryName)
		{
			DirectoryEntry result;
			if (entry.Members.ContainsKey(entryName))
			{
				result = entry.Members[entryName];
			}
			else
			{
				using (Dictionary<string, DirectoryEntry>.ValueCollection.Enumerator enumerator = entry.Members.Values.GetEnumerator())
				{
					if (enumerator.MoveNext())
					{
						DirectoryEntry current = enumerator.Current;
						result = this.FindDirectoryEntry(current, entryName);
						return result;
					}
				}
				result = null;
			}
			return result;
		}
		public byte[] GetStreamData(string streamName)
		{
			DirectoryEntry directoryEntry = this.FindDirectoryEntry(this.RootStorage, streamName);
			byte[] result;
			if (directoryEntry != null)
			{
				result = directoryEntry.Data;
			}
			else
			{
				result = null;
			}
			return result;
		}
		private void WriteHeader()
		{
			this.FileStorage.Position = 0L;
			CompoundDocument.WriteHeader(this.Writer, this.Header);
		}
		private static void WriteHeader(BinaryWriter writer, FileHeader header)
		{
			writer.Write(header.FileTypeIdentifier);
			writer.Write(header.FileIdentifier.ToByteArray());
			writer.Write(header.RevisionNumber);
			writer.Write(header.VersionNumber);
			writer.Write(header.ByteOrderMark);
			writer.Write(header.SectorSizeInPot);
			writer.Write(header.ShortSectorSizeInPot);
			writer.Write(header.UnUsed10);
			writer.Write(header.NumberOfSATSectors);
			writer.Write(header.FirstSectorIDofDirectoryStream);
			writer.Write(header.UnUsed4);
			writer.Write(header.MinimumStreamSize);
			writer.Write(header.FirstSectorIDofShortSectorAllocationTable);
			writer.Write(header.NumberOfShortSectors);
			writer.Write(header.FirstSectorIDofMasterSectorAllocationTable);
			writer.Write(header.NumberOfMasterSectors);
			CompoundDocument.WriteArrayOfInt32(writer, header.MasterSectorAllocationTable);
		}
		private static void WriteDirectoryEntry(BinaryWriter writer, DirectoryEntry entry)
		{
			writer.Write(entry.NameBuffer);
			writer.Write(entry.NameDataSize);
			writer.Write(entry.EntryType);
			writer.Write(entry.NodeColor);
			writer.Write(entry.LeftChildDID);
			writer.Write(entry.RightChildDID);
			writer.Write(entry.MembersTreeNodeDID);
			writer.Write(entry.UniqueIdentifier.ToByteArray());
			writer.Write(entry.UserFlags);
			writer.Write(entry.CreationTime.ToFileTime());
			writer.Write(entry.LastModificationTime.ToFileTime());
			writer.Write(entry.FirstSectorID);
			writer.Write(entry.StreamLength);
			writer.Write(entry.UnUsed);
		}
		public void WriteStreamData(string[] streamPath, byte[] data)
		{
			DirectoryEntry orCreateDirectoryEntry = this.GetOrCreateDirectoryEntry(streamPath);
			orCreateDirectoryEntry.EntryType = 2;
			orCreateDirectoryEntry.StreamLength = data.Length;
			if (orCreateDirectoryEntry.StreamLength < this.Header.MinimumStreamSize)
			{
				if (orCreateDirectoryEntry.FirstSectorID == -2)
				{
					orCreateDirectoryEntry.FirstSectorID = this.AllocateShortSector();
				}
				this.WriteShortStreamData(orCreateDirectoryEntry.FirstSectorID, data);
			}
			else
			{
				if (orCreateDirectoryEntry.FirstSectorID == -2)
				{
					orCreateDirectoryEntry.FirstSectorID = this.AllocateDataSector();
				}
				this.WriteStreamData(orCreateDirectoryEntry.FirstSectorID, data);
			}
		}
		internal void WriteStreamData(int startSID, byte[] data)
		{
			int num = -2;
			int num2 = startSID;
			int i = 0;
			while (i < data.Length)
			{
				if (num2 == -2)
				{
					if (num == -2)
					{
						num2 = this.AllocateDataSector();
					}
					else
					{
						num2 = this.AllocateDataSectorAfter(num);
					}
				}
				int sectorOffset = this.GetSectorOffset(num2);
				this.Writer.BaseStream.Position = (long)sectorOffset;
				checked
				{
					if (i + this.SectorSize < data.Length)
					{
						this.Writer.Write(data, i, this.SectorSize);
					}
					else
					{
						this.Writer.Write(data, i, data.Length - i);
					}
					i += this.SectorSize;
					num = num2;
					num2 = this.SectorAllocation.GetNextSectorID(num);
				}
			}
			if (num2 != -2 && num != -2)
			{
				this.SectorAllocation.LinkSectorID(num, -2);
				while (num2 != -2)
				{
					int nextSectorID = this.SectorAllocation.GetNextSectorID(num2);
					this.SectorAllocation.LinkSectorID(num2, -1);
					num2 = nextSectorID;
				}
			}
		}
		private void AppendStreamData(int startSID, int streamLength, byte[] data)
		{
			int num = startSID;
			int num2 = this.SectorAllocation.GetNextSectorID(num);
			int num3 = 0;
			checked
			{
				while (num2 != -2)
				{
					num = num2;
					num2 = this.SectorAllocation.GetNextSectorID(num);
					num3 += this.SectorSize;
				}
				if (num3 < streamLength)
				{
					int num4 = streamLength - num3;
					int num5 = this.SectorSize - num4;
					if (data.Length <= num5)
					{
						this.WriteInSector(num, num4, data, 0, data.Length);
					}
					else
					{
						this.WriteInSector(num, num4, data, 0, num5);
						num2 = this.AllocateDataSectorAfter(num);
						byte[] array = new byte[data.Length - num5];
						Array.Copy(data, num5, array, 0, array.Length);
						this.WriteStreamData(num2, array);
					}
				}
				else
				{
					num2 = this.AllocateDataSectorAfter(num);
					this.WriteStreamData(num2, data);
				}
			}
		}
		internal void WriteShortStreamData(int startSID, byte[] data)
		{
			int num = -2;
			int num2 = startSID;
			int i = 0;
			while (i < data.Length)
			{
				if (num2 == -2)
				{
					if (num == -2)
					{
						num2 = this.ShortSectorAllocation.AllocateSector();
					}
					else
					{
						num2 = this.ShortSectorAllocation.AllocateSectorAfter(num);
					}
				}
				int shortSectorOffset = this.GetShortSectorOffset(num2);
				this.ShortStreamContainer.Position = (long)shortSectorOffset;
				checked
				{
					if (i + this.ShortSectorSize < data.Length)
					{
						this.ShortStreamContainer.Write(data, i, this.ShortSectorSize);
					}
					else
					{
						this.ShortStreamContainer.Write(data, i, data.Length - i);
					}
					i += this.ShortSectorSize;
					num = num2;
					num2 = this.ShortSectorAllocation.GetNextSectorID(num);
				}
			}
			if (num2 != -2 && num != -2)
			{
				this.ShortSectorAllocation.LinkSectorID(num, -2);
				while (num2 != -2)
				{
					int nextSectorID = this.ShortSectorAllocation.GetNextSectorID(num2);
					this.ShortSectorAllocation.LinkSectorID(num2, -1);
					num2 = nextSectorID;
				}
			}
		}
		private DirectoryEntry GetOrCreateDirectoryEntry(string[] streamPath)
		{
			DirectoryEntry directoryEntry = this.RootStorage;
			for (int i = 0; i < streamPath.Length; i++)
			{
				string text = streamPath[i];
				if (!directoryEntry.Members.ContainsKey(text))
				{
					DirectoryEntry directoryEntry2 = new DirectoryEntry(this, text);
					directoryEntry2.ID = this.DirectoryEntries.Count;
					this.DirectoryEntries.Add(directoryEntry2.ID, directoryEntry2);
					directoryEntry.AddChild(directoryEntry2);
				}
				directoryEntry = directoryEntry.Members[text];
			}
			return directoryEntry;
		}
		public void DeleteDirectoryEntry(string[] streamPath)
		{
			DirectoryEntry orCreateDirectoryEntry = this.GetOrCreateDirectoryEntry(streamPath);
			this.DeleteDirectoryEntry(orCreateDirectoryEntry);
		}
		public void DeleteDirectoryEntry(DirectoryEntry entry)
		{
			entry.EntryType = 0;
			entry.StreamLength = 0;
			entry.Parent.Members.Remove(entry.Name);
		}
	}
}
