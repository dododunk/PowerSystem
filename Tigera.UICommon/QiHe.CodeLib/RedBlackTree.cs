using System;
namespace QiHe.CodeLib
{
	public class RedBlackTree<TItem> : BinarySearchTreeBase<TItem, RedBlackTreeNode<TItem>> where TItem : IComparable<TItem>
	{
		public override RedBlackTreeNode<TItem> Nil
		{
			get
			{
				return RedBlackTreeNode<TItem>.Nil;
			}
		}
		public override void Insert(RedBlackTreeNode<TItem> node)
		{
			base.Insert(node);
			node.Color = NodeColor.Red;
			this.FixupAfterInsert(node);
		}
		private void FixupAfterInsert(RedBlackTreeNode<TItem> node)
		{
			while (node.Parent.Color == NodeColor.Red)
			{
				if (node.Parent.IsLeftChild)
				{
					RedBlackTreeNode<TItem> redBlackTreeNode = node.Parent.Parent.Right;
					if (redBlackTreeNode.Color == NodeColor.Red)
					{
						redBlackTreeNode.Color = NodeColor.Black;
						node.Parent.Color = NodeColor.Black;
						node.Parent.Parent.Color = NodeColor.Red;
						node = node.Parent.Parent;
					}
					else
					{
						if (node.IsRightChild)
						{
							node = node.Parent;
							base.RotateLeft(node);
						}
						node.Parent.Color = NodeColor.Black;
						node.Parent.Parent.Color = NodeColor.Red;
						base.RotateRight(node.Parent.Parent);
					}
				}
				else
				{
					RedBlackTreeNode<TItem> redBlackTreeNode = node.Parent.Parent.Left;
					if (redBlackTreeNode.Color == NodeColor.Red)
					{
						redBlackTreeNode.Color = NodeColor.Black;
						node.Parent.Color = NodeColor.Black;
						node.Parent.Parent.Color = NodeColor.Red;
						node = node.Parent.Parent;
					}
					else
					{
						if (node.IsLeftChild)
						{
							node = node.Parent;
							base.RotateRight(node);
						}
						node.Parent.Color = NodeColor.Black;
						node.Parent.Parent.Color = NodeColor.Red;
						base.RotateLeft(node.Parent.Parent);
					}
				}
			}
			this.Root.Color = NodeColor.Black;
		}
		public override RedBlackTreeNode<TItem> Delete(RedBlackTreeNode<TItem> node)
		{
			RedBlackTreeNode<TItem> redBlackTreeNode = base.Delete(node);
			RedBlackTreeNode<TItem> node2 = this.Nil;
			RedBlackTreeNode<TItem> parent = redBlackTreeNode.Parent;
			if (parent != this.Nil)
			{
				node2 = (redBlackTreeNode.IsLeftChild ? parent.Left : parent.Right);
			}
			if (redBlackTreeNode.Color == NodeColor.Black)
			{
				this.FixupAfterDelete(node2);
			}
			return redBlackTreeNode;
		}
		private void FixupAfterDelete(RedBlackTreeNode<TItem> node)
		{
			while (node != this.Root && node.Color == NodeColor.Black)
			{
				if (node.IsLeftChild)
				{
					RedBlackTreeNode<TItem> redBlackTreeNode = node.Parent.Right;
					if (redBlackTreeNode.Color == NodeColor.Red)
					{
						redBlackTreeNode.Color = NodeColor.Black;
						node.Parent.Color = NodeColor.Red;
						base.RotateLeft(node.Parent);
						redBlackTreeNode = node.Parent.Right;
					}
					if (redBlackTreeNode.Left.Color == NodeColor.Black && redBlackTreeNode.Right.Color == NodeColor.Black)
					{
						redBlackTreeNode.Color = NodeColor.Red;
						node = node.Parent;
					}
					else
					{
						if (redBlackTreeNode.Right.Color == NodeColor.Black)
						{
							redBlackTreeNode.Left.Color = NodeColor.Black;
							redBlackTreeNode.Color = NodeColor.Red;
							base.RotateRight(redBlackTreeNode);
							redBlackTreeNode = node.Parent.Right;
						}
						redBlackTreeNode.Color = node.Parent.Color;
						node.Parent.Color = NodeColor.Black;
						redBlackTreeNode.Right.Color = NodeColor.Black;
						base.RotateLeft(node.Parent);
						node = this.Root;
					}
				}
				else
				{
					RedBlackTreeNode<TItem> redBlackTreeNode = node.Parent.Left;
					if (redBlackTreeNode.Color == NodeColor.Red)
					{
						redBlackTreeNode.Color = NodeColor.Black;
						node.Parent.Color = NodeColor.Red;
						base.RotateRight(node.Parent);
						redBlackTreeNode = node.Parent.Left;
					}
					if (redBlackTreeNode.Left.Color == NodeColor.Black && redBlackTreeNode.Right.Color == NodeColor.Black)
					{
						redBlackTreeNode.Color = NodeColor.Red;
						node = node.Parent;
					}
					else
					{
						if (redBlackTreeNode.Left.Color == NodeColor.Black)
						{
							redBlackTreeNode.Right.Color = NodeColor.Black;
							redBlackTreeNode.Color = NodeColor.Red;
							base.RotateLeft(redBlackTreeNode);
							redBlackTreeNode = node.Parent.Left;
						}
						redBlackTreeNode.Color = node.Parent.Color;
						node.Parent.Color = NodeColor.Black;
						redBlackTreeNode.Left.Color = NodeColor.Black;
						base.RotateRight(node.Parent);
						node = this.Root;
					}
				}
			}
			node.Color = NodeColor.Black;
		}
	}
}
