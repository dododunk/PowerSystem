using System;
using System.Collections.Generic;
using System.IO;
namespace ExcelLibrary.CompoundDocumentFormat
{
	public class ShortSectorAllocation
	{
		private CompoundDocument Document;
		private List<int> ShortSectorAllocationTable;
		public ShortSectorAllocation(CompoundDocument document)
		{
			this.Document = document;
			this.ShortSectorAllocationTable = document.GetStreamDataAsIntegers(document.Header.FirstSectorIDofShortSectorAllocationTable);
			checked
			{
				while (this.ShortSectorAllocationTable.Count > 0 && this.ShortSectorAllocationTable[this.ShortSectorAllocationTable.Count - 1] == -1)
				{
					this.ShortSectorAllocationTable.RemoveAt(this.ShortSectorAllocationTable.Count - 1);
				}
			}
		}
		public int AllocateSector()
		{
			int count = this.ShortSectorAllocationTable.Count;
			this.LinkSectorID(count, -2);
			this.Document.AllocateNewShortSector();
			checked
			{
				this.Document.Header.NumberOfShortSectors++;
				return count;
			}
		}
		public int AllocateSectorAfter(int sectorID)
		{
			int num = this.AllocateSector();
			this.LinkSectorID(sectorID, num);
			return num;
		}
		public void LinkSectorID(int sectorID, int newSectorID)
		{
			if (sectorID < this.ShortSectorAllocationTable.Count)
			{
				this.ShortSectorAllocationTable[sectorID] = newSectorID;
			}
			else
			{
				if (sectorID != this.ShortSectorAllocationTable.Count)
				{
					throw new ArgumentOutOfRangeException("sectorID");
				}
				this.ShortSectorAllocationTable.Add(newSectorID);
			}
		}
		public int GetNextSectorID(int sectorID)
		{
			int result;
			if (sectorID < this.ShortSectorAllocationTable.Count)
			{
				result = this.ShortSectorAllocationTable[sectorID];
			}
			else
			{
				result = -2;
			}
			return result;
		}
		public List<int> GetSIDChain(int StartSID)
		{
			List<int> list = new List<int>();
			for (int num = StartSID; num != -2; num = this.GetNextSectorID(num))
			{
				list.Add(num);
			}
			return list;
		}
		public void Save()
		{
			checked
			{
				if (this.ShortSectorAllocationTable.Count > 0)
				{
					if (this.Document.Header.FirstSectorIDofShortSectorAllocationTable == -2)
					{
						int num = this.Document.SectorSize / 4;
						int[] array = new int[num];
						for (int i = 0; i < array.Length; i++)
						{
							array[i] = -1;
						}
						this.Document.Header.FirstSectorIDofShortSectorAllocationTable = this.Document.AllocateDataSector();
						this.Document.WriteInSector(this.Document.Header.FirstSectorIDofShortSectorAllocationTable, 0, array);
					}
					MemoryStream memoryStream = new MemoryStream(this.ShortSectorAllocationTable.Count * 4);
					CompoundDocument.WriteArrayOfInt32(new BinaryWriter(memoryStream), this.ShortSectorAllocationTable.ToArray());
					this.Document.WriteStreamData(this.Document.Header.FirstSectorIDofShortSectorAllocationTable, memoryStream.ToArray());
				}
			}
		}
	}
}
