using System;
using System.Collections.Generic;
namespace QiHe.CodeLib
{
	public class BinarySearchTreeBase<TItem, TTreeNode> where TItem : IComparable<TItem> where TTreeNode : BinaryTreeNodeBase<TItem, TTreeNode>, new()
	{
		public TTreeNode Root;
		private int count;
		public virtual TTreeNode Nil
		{
			get
			{
				return default(TTreeNode);
			}
		}
		public int Size
		{
			get
			{
				return this.count;
			}
		}
		public BinarySearchTreeBase()
		{
			this.Root = this.Nil;
		}
		public IEnumerable<TItem> InorderTreeWalk()
		{
			foreach (TTreeNode current in this.InorderTreeWalk(this.Root))
			{
				yield return current.Data;
			}
			yield break;
		}
		public bool Contains(TItem item)
		{
			return this.Search(this.Root, item) != this.Nil;
		}
		public TTreeNode Find(TItem item)
		{
			return this.Search(this.Root, item);
		}
		public void Add(TItem item)
		{
			TTreeNode tTreeNode = Activator.CreateInstance<TTreeNode>();
			tTreeNode.Data = item;
			this.Insert(tTreeNode);
		}
		public void Remove(TItem item)
		{
			TTreeNode tTreeNode = this.Search(this.Root, item);
			if (tTreeNode != this.Nil)
			{
				this.Delete(tTreeNode);
			}
		}
		public void Clear()
		{
			this.Root = this.Nil;
			this.count = 0;
		}
		public IEnumerable<TTreeNode> InorderTreeWalk(TTreeNode node)
		{
			if (node != this.Nil)
			{
				foreach (TTreeNode current in this.InorderTreeWalk(node.Left))
				{
					yield return current;
				}
				yield return node;
				foreach (TTreeNode current2 in this.InorderTreeWalk(node.Right))
				{
					yield return current2;
				}
			}
			yield break;
		}
		public TTreeNode Search(TTreeNode node, TItem item)
		{
			TTreeNode result;
			if (node == this.Nil || node.Data.CompareTo(item) == 0)
			{
				result = node;
			}
			else
			{
				if (item.CompareTo(node.Data) < 0)
				{
					result = this.Search(node.Left, item);
				}
				else
				{
					result = this.Search(node.Right, item);
				}
			}
			return result;
		}
		public TTreeNode Minimum(TTreeNode node)
		{
			TTreeNode result;
			if (node == this.Nil)
			{
				result = this.Nil;
			}
			else
			{
				TTreeNode tTreeNode = node;
				while (tTreeNode.Left != this.Nil)
				{
					tTreeNode = tTreeNode.Left;
				}
				result = tTreeNode;
			}
			return result;
		}
		public TTreeNode Maximum(TTreeNode node)
		{
			TTreeNode result;
			if (node == this.Nil)
			{
				result = this.Nil;
			}
			else
			{
				TTreeNode tTreeNode = node;
				while (tTreeNode.Right != this.Nil)
				{
					tTreeNode = tTreeNode.Right;
				}
				result = tTreeNode;
			}
			return result;
		}
		protected TTreeNode Successor(TTreeNode node)
		{
			TTreeNode result;
			if (node.Right != this.Nil)
			{
				result = this.Minimum(node.Right);
			}
			else
			{
				TTreeNode parent = node.Parent;
				while (parent != this.Nil && node == parent.Right)
				{
					node = parent;
					parent = parent.Parent;
				}
				result = parent;
			}
			return result;
		}
		protected TTreeNode Predecessor(TTreeNode node)
		{
			TTreeNode result;
			if (node.Left != this.Nil)
			{
				result = this.Maximum(node.Left);
			}
			else
			{
				TTreeNode parent = node.Parent;
				while (parent != this.Nil && node == parent.Left)
				{
					node = parent;
					parent = parent.Parent;
				}
				result = parent;
			}
			return result;
		}
		protected void RotateLeft(TTreeNode x)
		{
			TTreeNode right = x.Right;
			x.Right = right.Left;
			if (right.Left != this.Nil)
			{
				right.Left.Parent = x;
			}
			if (right != this.Nil)
			{
				right.Parent = x.Parent;
			}
			if (x.Parent != this.Nil)
			{
				if (x.IsLeftChild)
				{
					x.Parent.Left = right;
				}
				else
				{
					x.Parent.Right = right;
				}
			}
			else
			{
				this.Root = right;
			}
			right.Left = x;
			if (x != this.Nil)
			{
				x.Parent = right;
			}
		}
		protected void RotateRight(TTreeNode x)
		{
			TTreeNode left = x.Left;
			x.Left = left.Right;
			if (left.Right != this.Nil)
			{
				left.Right.Parent = x;
			}
			if (left != this.Nil)
			{
				left.Parent = x.Parent;
			}
			if (x.Parent != this.Nil)
			{
				if (x.IsRightChild)
				{
					x.Parent.Right = left;
				}
				else
				{
					x.Parent.Left = left;
				}
			}
			else
			{
				this.Root = left;
			}
			left.Right = x;
			if (x != this.Nil)
			{
				x.Parent = left;
			}
		}
		public virtual void Insert(TTreeNode node)
		{
			TTreeNode tTreeNode = this.Nil;
			TTreeNode tTreeNode2 = this.Root;
			while (tTreeNode2 != this.Nil)
			{
				tTreeNode = tTreeNode2;
				if (node.Data.CompareTo(tTreeNode2.Data) < 0)
				{
					tTreeNode2 = tTreeNode2.Left;
				}
				else
				{
					tTreeNode2 = tTreeNode2.Right;
				}
			}
			node.Parent = tTreeNode;
			if (tTreeNode == this.Nil)
			{
				this.Root = node;
			}
			else
			{
				if (node.Data.CompareTo(tTreeNode.Data) < 0)
				{
					tTreeNode.Left = node;
				}
				else
				{
					tTreeNode.Right = node;
				}
			}
			checked
			{
				this.count++;
			}
		}
		public virtual TTreeNode Delete(TTreeNode node)
		{
			TTreeNode tTreeNode;
			if (node.Left == this.Nil || node.Right == this.Nil)
			{
				tTreeNode = node;
			}
			else
			{
				tTreeNode = this.Successor(node);
			}
			TTreeNode tTreeNode2;
			if (tTreeNode.Left != this.Nil)
			{
				tTreeNode2 = tTreeNode.Left;
			}
			else
			{
				tTreeNode2 = tTreeNode.Right;
			}
			if (tTreeNode2 != this.Nil)
			{
				tTreeNode2.Parent = tTreeNode.Parent;
			}
			TTreeNode parent = tTreeNode.Parent;
			if (parent == this.Nil)
			{
				this.Root = tTreeNode2;
			}
			else
			{
				if (tTreeNode.IsLeftChild)
				{
					parent.Left = tTreeNode2;
				}
				else
				{
					parent.Right = tTreeNode2;
				}
			}
			if (tTreeNode != node)
			{
				node.Data = tTreeNode.Data;
			}
			checked
			{
				this.count--;
				return tTreeNode;
			}
		}
	}
}
