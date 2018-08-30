using System;
using System.Collections.Generic;
namespace ExcelLibrary.CompoundDocumentFormat
{
	public class SectorAllocation
	{
		private CompoundDocument Document;
		private int SecIDCapacity;
		public SectorAllocation(CompoundDocument document)
		{
			this.Document = document;
			this.SecIDCapacity = document.SectorSize / 4;
		}
		public int AllocateSector()
		{
			int num = this.Document.AllocateNewSector();
			this.LinkSectorID(num, -2);
			return num;
		}
		public void LinkSectorID(int sectorID, int newSectorID)
		{
			if (sectorID < 0)
			{
				throw new ArgumentOutOfRangeException("sectorID");
			}
			int sATSectorIndex = sectorID / this.SecIDCapacity;
			int num = sectorID % this.SecIDCapacity;
			int sATSectorID = this.Document.MasterSectorAllocation.GetSATSectorID(sATSectorIndex);
			this.Document.WriteInSector(sATSectorID, checked(num * 4), newSectorID);
		}
		public int GetNextSectorID(int sectorID)
		{
			if (sectorID < 0)
			{
				throw new ArgumentOutOfRangeException("sectorID");
			}
			int sATSectorIndex = sectorID / this.SecIDCapacity;
			int num = sectorID % this.SecIDCapacity;
			int sATSectorID = this.Document.MasterSectorAllocation.GetSATSectorID(sATSectorIndex);
			return this.Document.ReadInt32InSector(sATSectorID, checked(num * 4));
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
	}
}
