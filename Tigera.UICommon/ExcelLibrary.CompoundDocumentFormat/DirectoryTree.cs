using QiHe.CodeLib;
using System;
namespace ExcelLibrary.CompoundDocumentFormat
{
	public class DirectoryTree
	{
		public static void Build(DirectoryEntry rootEntry)
		{
			if (rootEntry.Members.Count > 0)
			{
				rootEntry.MembersTreeNodeDID = DirectoryTree.BuildStorageEntry(rootEntry);
			}
		}
		private static int BuildStorageEntry(DirectoryEntry storageEntry)
		{
			RedBlackTree<DirectoryEntry> redBlackTree = new RedBlackTree<DirectoryEntry>();
			foreach (DirectoryEntry directoryEntry in storageEntry.Members.Values)
			{
				
				redBlackTree.Add(directoryEntry);
			}
			foreach (RedBlackTreeNode<DirectoryEntry> current in redBlackTree.InorderTreeWalk(redBlackTree.Root))
			{
				DirectoryEntry directoryEntry = current.Data;
				directoryEntry.NodeColor = DirectoryTree.GetNodeColor(current.Color);
				directoryEntry.LeftChildDID = DirectoryTree.GetNodeID(current.Left);
				directoryEntry.RightChildDID = DirectoryTree.GetNodeID(current.Right);
				if (directoryEntry.Members.Count > 0)
				{
					directoryEntry.EntryType = 1;
					directoryEntry.MembersTreeNodeDID = DirectoryTree.BuildStorageEntry(directoryEntry);
				}
				else
				{
					directoryEntry.EntryType = 2;
					directoryEntry.MembersTreeNodeDID = -1;
				}
			}
			return redBlackTree.Root.Data.ID;
		}
		private static int GetNodeID(RedBlackTreeNode<DirectoryEntry> node)
		{
			int result;
			if (node == RedBlackTreeNode<DirectoryEntry>.Nil)
			{
				result = -1;
			}
			else
			{
				result = node.Data.ID;
			}
			return result;
		}
		private static byte GetNodeColor(QiHe.CodeLib.NodeColor nodeColor)
		{
			byte result;
			switch (nodeColor)
			{
			case QiHe.CodeLib.NodeColor.Red:
				result = 0;
				break;

			case QiHe.CodeLib.NodeColor.Black:
				result = 1;
				break;

			default:
				throw new ArgumentException();
			}
			return result;
		}
	}
}
