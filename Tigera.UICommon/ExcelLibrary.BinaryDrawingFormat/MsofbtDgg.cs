using System;
using System.Collections.Generic;
using System.IO;
namespace ExcelLibrary.BinaryDrawingFormat
{
	public class MsofbtDgg : EscherRecord
	{
		public int MaxShapeID;
		public int NumIDClusters;
		public int NumSavedShapes;
		public int NumSavedDrawings;
		public List<long> IDClusters;
		public Dictionary<int, int> GroupIdClusters = new Dictionary<int, int>();
		public MsofbtDgg(EscherRecord record) : base(record)
		{
		}
		public MsofbtDgg()
		{
			this.Type = 61446;
			this.IDClusters = new List<long>();
		}
		public void decode()
		{
			MemoryStream input = new MemoryStream(this.Data);
			BinaryReader binaryReader = new BinaryReader(input);
			this.MaxShapeID = binaryReader.ReadInt32();
			this.NumIDClusters = binaryReader.ReadInt32();
			this.NumSavedShapes = binaryReader.ReadInt32();
			this.NumSavedDrawings = binaryReader.ReadInt32();
			binaryReader.ReadInt64();
		}
		public void encode()
		{
			MemoryStream memoryStream = new MemoryStream();
			BinaryWriter binaryWriter = new BinaryWriter(memoryStream);
			binaryWriter.Write(this.MaxShapeID);
			binaryWriter.Write(this.NumIDClusters);
			binaryWriter.Write(this.NumSavedShapes);
			binaryWriter.Write(this.NumSavedDrawings);
			foreach (long current in this.IDClusters)
			{
				binaryWriter.Write(current);
			}
			this.Data = memoryStream.ToArray();
			this.Size = checked((uint)this.Data.Length);
			base.Encode();
		}
		public override void Decode()
		{
			MemoryStream memoryStream = new MemoryStream(this.Data);
			BinaryReader binaryReader = new BinaryReader(memoryStream);
			this.MaxShapeID = binaryReader.ReadInt32();
			this.NumIDClusters = binaryReader.ReadInt32();
			this.NumSavedShapes = binaryReader.ReadInt32();
			this.NumSavedDrawings = binaryReader.ReadInt32();
			this.IDClusters = new List<long>();
			while (memoryStream.Position < memoryStream.Length)
			{
				int key = binaryReader.ReadInt32();
				int value = binaryReader.ReadInt32();
				this.GroupIdClusters.Add(key, value);
			}
		}
		public override void Encode()
		{
			MemoryStream memoryStream = new MemoryStream();
			BinaryWriter binaryWriter = new BinaryWriter(memoryStream);
			binaryWriter.Write(this.MaxShapeID);
			binaryWriter.Write(this.GetNumIDClusters());
			binaryWriter.Write(this.NumSavedShapes);
			binaryWriter.Write(this.NumSavedDrawings);
			List<int> list = new List<int>(this.GroupIdClusters.Keys);
			list.Sort();
			foreach (int current in list)
			{
				binaryWriter.Write(current);
				binaryWriter.Write(this.GroupIdClusters[current]);
			}
			this.Data = memoryStream.ToArray();
			this.Size = checked((uint)this.Data.Length);
			base.Encode();
		}
		public int GetNumIDClusters()
		{
			return checked(this.GroupIdClusters.Count + 1);
		}
	}
}
