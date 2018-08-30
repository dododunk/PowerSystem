using System;
using System.Collections.Generic;
namespace ExcelLibrary.CompoundDocumentFormat
{
	public class DirectoryEntry : IComparable<DirectoryEntry>
	{
		public char[] NameBuffer;
		public ushort NameDataSize;
		public byte EntryType;
		public byte NodeColor;
		public int LeftChildDID;
		public int RightChildDID;
		public int MembersTreeNodeDID;
		public Guid UniqueIdentifier;
		public int UserFlags;
		public DateTime CreationTime;
		public DateTime LastModificationTime;
		public int FirstSectorID;
		public int StreamLength;
		public int UnUsed;
		public int ID = -1;
		public CompoundDocument Document;
		public DirectoryEntry Parent;
		public Dictionary<string, DirectoryEntry> Members = new Dictionary<string, DirectoryEntry>();
		private byte[] data;
		private string name;
		public byte[] Data
		{
			get
			{
				if (this.data == null)
				{
					this.data = this.Document.GetStreamData(this);
				}
				return this.data;
			}
			set
			{
				this.data = value;
			}
		}
		public string Name
		{
			get
			{
				if (this.name == null)
				{
					int num = (int)checked(this.NameDataSize / 2 - 1);
					if (num == 1)
					{
						this.name = string.Empty;
					}
					else
					{
						this.name = new string(this.NameBuffer, 0, num);
					}
				}
				return this.name;
			}
			set
			{
				if (value.Length > 31)
				{
					throw new Exception("Directory Entry Name exceeds 31 chars.");
				}
				value.ToCharArray().CopyTo(this.NameBuffer, 0);
				this.NameBuffer[value.Length] = '\0';
				this.NameDataSize = checked((ushort)((value.Length + 1) * 2));
				this.name = value;
			}
		}
		internal DirectoryEntry()
		{
		}
		public DirectoryEntry(string name)
		{
			this.NameBuffer = new char[32];
			this.Name = name;
			this.CreationTime = DateTime.Now;
			this.LastModificationTime = this.CreationTime;
			this.LeftChildDID = -1;
			this.RightChildDID = -1;
			this.MembersTreeNodeDID = -1;
			this.FirstSectorID = -2;
		}
		public DirectoryEntry(CompoundDocument document, string name) : this(name)
		{
			this.Document = document;
		}
		public void AddChild(DirectoryEntry entry)
		{
			if (entry.Parent != null)
			{
				throw new ArgumentException("DirectoryEntry already has a parent.");
			}
			entry.Parent = this;
			this.Members.Add(entry.Name, entry);
		}
		public override string ToString()
		{
			return this.Name;
		}
		public int CompareTo(DirectoryEntry other)
		{
			return DirectoryEntry.CompareString(this.Name, other.Name);
		}
		private static int CompareString(string strA, string strB)
		{
			int result;
			if (strA != null && strB != null)
			{
				if (strA.Length < strB.Length)
				{
					result = -1;
					return result;
				}
				if (strA.Length > strB.Length)
				{
					result = 1;
					return result;
				}
			}
			result = string.Compare(strA, strB, StringComparison.OrdinalIgnoreCase);
			return result;
		}
	}
}
