using System;
namespace ExcelLibrary.CompoundDocumentFormat
{
	public class FileHeader
	{
		public byte[] FileTypeIdentifier;
		public Guid FileIdentifier;
		public ushort RevisionNumber;
		public ushort VersionNumber;
		public byte[] ByteOrderMark;
		public ushort SectorSizeInPot;
		public ushort ShortSectorSizeInPot;
		public byte[] UnUsed10;
		public int NumberOfSATSectors;
		public int FirstSectorIDofDirectoryStream;
		public byte[] UnUsed4;
		public int MinimumStreamSize;
		public int FirstSectorIDofShortSectorAllocationTable;
		public int NumberOfShortSectors;
		public int FirstSectorIDofMasterSectorAllocationTable;
		public int NumberOfMasterSectors;
		public int[] MasterSectorAllocationTable;
	}
}
