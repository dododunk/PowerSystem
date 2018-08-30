using System;
using System.Collections.Generic;
namespace ExcelLibrary.CompoundDocumentFormat
{
	public class MasterSectorAllocation
	{
		private CompoundDocument Document;
		private int NumberOfSecIDs;
		private int CurrentMSATSector;
		private int SecIDCapacity;
		private List<int> MasterSectorAllocationTable;
		public MasterSectorAllocation(CompoundDocument document)
		{
			this.Document = document;
			this.NumberOfSecIDs = document.Header.NumberOfSATSectors;
			this.CurrentMSATSector = document.Header.FirstSectorIDofMasterSectorAllocationTable;
			this.SecIDCapacity = checked(document.SectorSize / 4 - 1);
			this.InitializeMasterSectorAllocationTable();
		}
		private void InitializeMasterSectorAllocationTable()
		{
			this.MasterSectorAllocationTable = new List<int>(this.NumberOfSecIDs);
			this.SelectSIDs(this.Document.Header.MasterSectorAllocationTable);
			int[] array;
			for (int num = this.Document.Header.FirstSectorIDofMasterSectorAllocationTable; num != -2; num = array[checked(array.Length - 1)])
			{
				this.CurrentMSATSector = num;
				array = this.Document.ReadSectorDataAsIntegers(num);
				this.SelectSIDs(array);
			}
		}
		private void SelectSIDs(int[] SIDs)
		{
			checked
			{
				for (int i = 0; i < SIDs.Length; i++)
				{
					int item = SIDs[i];
					if (this.MasterSectorAllocationTable.Count >= this.NumberOfSecIDs)
					{
						break;
					}
					this.MasterSectorAllocationTable.Add(item);
				}
			}
		}
		public int GetSATSectorID(int SATSectorIndex)
		{
			int result;
			if (SATSectorIndex < this.NumberOfSecIDs)
			{
				result = this.MasterSectorAllocationTable[SATSectorIndex];
			}
			else
			{
				if (SATSectorIndex != this.NumberOfSecIDs)
				{
					throw new ArgumentOutOfRangeException("SATSectorIndex");
				}
				result = this.AllocateSATSector();
			}
			return result;
		}
		public int AllocateSATSector()
		{
			int[] array = new int[this.SecIDCapacity];
			checked
			{
				for (int i = 0; i < array.Length; i++)
				{
					array[i] = -1;
				}
				int num = this.Document.AllocateNewSector(array);
				if (this.NumberOfSecIDs < 109)
				{
					this.Document.Header.MasterSectorAllocationTable[this.NumberOfSecIDs] = num;
					this.Document.Write(unchecked((long)checked(76 + this.NumberOfSecIDs * 4)), num);
				}
				else
				{
					if (this.CurrentMSATSector == -2)
					{
						this.CurrentMSATSector = this.AllocateMSATSector();
						this.Document.Header.FirstSectorIDofMasterSectorAllocationTable = this.CurrentMSATSector;
					}
					int num2 = (this.NumberOfSecIDs - 109) % this.SecIDCapacity;
					this.Document.WriteInSector(this.CurrentMSATSector, num2 * 4, num);
					if (num2 == this.SecIDCapacity - 1)
					{
						int num3 = this.AllocateMSATSector();
						this.Document.WriteInSector(this.CurrentMSATSector, this.SecIDCapacity * 4, num3);
						this.CurrentMSATSector = num3;
					}
				}
				this.MasterSectorAllocationTable.Add(num);
				this.NumberOfSecIDs++;
				this.Document.SectorAllocation.LinkSectorID(num, -3);
				this.Document.Header.NumberOfSATSectors++;
				return num;
			}
		}
		public int AllocateMSATSector()
		{
			checked
			{
				int[] array = new int[this.SecIDCapacity + 1];
				for (int i = 0; i < this.SecIDCapacity; i++)
				{
					array[i] = -1;
				}
				array[this.SecIDCapacity] = -2;
				int num = this.Document.AllocateNewSector();
				this.Document.WriteInSector(num, 0, array);
				this.Document.SectorAllocation.LinkSectorID(num, -4);
				this.Document.Header.NumberOfMasterSectors++;
				return num;
			}
		}
	}
}
