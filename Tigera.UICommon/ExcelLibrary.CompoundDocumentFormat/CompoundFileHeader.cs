using System;
namespace ExcelLibrary.CompoundDocumentFormat
{
	public class CompoundFileHeader : FileHeader
	{
		public new static readonly byte[] FileTypeIdentifier = new byte[]
		{
			208,
			207,
			17,
			224,
			161,
			177,
			26,
			225
		};
		public CompoundFileHeader()
		{
			//this.FileTypeIdentifier = CompoundFileHeader.FileTypeIdentifier;
			this.FileIdentifier = Guid.NewGuid();
			this.RevisionNumber = 62;
			this.VersionNumber = 3;
			this.ByteOrderMark = ByteOrderMarks.LittleEndian;
			this.SectorSizeInPot = 9;
			this.ShortSectorSizeInPot = 6;
			this.UnUsed10 = new byte[10];
			this.UnUsed4 = new byte[4];
			this.MinimumStreamSize = 4096;
			this.FirstSectorIDofShortSectorAllocationTable = -2;
			this.FirstSectorIDofMasterSectorAllocationTable = -2;
			this.FirstSectorIDofDirectoryStream = -2;
			this.MasterSectorAllocationTable = new int[109];
			checked
			{
				for (int i = 0; i < this.MasterSectorAllocationTable.Length; i++)
				{
					this.MasterSectorAllocationTable[i] = -1;
				}
			}
		}
	}
}
