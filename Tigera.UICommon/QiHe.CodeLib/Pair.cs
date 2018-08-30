using System;
namespace QiHe.CodeLib
{
	public class Pair<TLeft, TRight> : IEquatable<Pair<TLeft, TRight>>
	{
		public TLeft Left;
		public TRight Right;
		public Pair(TLeft left, TRight right)
		{
			this.Left = left;
			this.Right = right;
		}
		public override string ToString()
		{
			return string.Format("({0},{1})", this.Left, this.Right);
		}
		public override int GetHashCode()
		{
			return checked(this.Left.GetHashCode() + this.Right.GetHashCode());
		}
		public override bool Equals(object obj)
		{
			return obj is Pair<TLeft, TRight> && this.Equals((Pair<TLeft, TRight>)obj);
		}
		public bool Equals(Pair<TLeft, TRight> other)
		{
			return this.Left.Equals(other.Left) && this.Right.Equals(other.Right);
		}
		public static bool operator ==(Pair<TLeft, TRight> one, Pair<TLeft, TRight> other)
		{
			return one.Equals(other);
		}
		public static bool operator !=(Pair<TLeft, TRight> one, Pair<TLeft, TRight> other)
		{
			return !(one == other);
		}
	}
}
