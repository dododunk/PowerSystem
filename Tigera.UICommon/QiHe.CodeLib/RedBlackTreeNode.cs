using System;
namespace QiHe.CodeLib
{
	public class RedBlackTreeNode<TItem> : BinaryTreeNodeBase<TItem, RedBlackTreeNode<TItem>>
	{
		public NodeColor Color;
		public static readonly RedBlackTreeNode<TItem> Nil = new RedBlackTreeNode<TItem>();
		public RedBlackTreeNode()
		{
			this.Parent = RedBlackTreeNode<TItem>.Nil;
			this.Left = RedBlackTreeNode<TItem>.Nil;
			this.Right = RedBlackTreeNode<TItem>.Nil;
			this.Color = NodeColor.Black;
		}
	}
}
