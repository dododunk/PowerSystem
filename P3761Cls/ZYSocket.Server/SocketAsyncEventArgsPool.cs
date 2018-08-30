using System;
using System.Collections.Generic;
using System.Net.Sockets;
namespace ZYSocket.Server
{
	internal sealed class SocketAsyncEventArgsPool
	{
		private Stack<SocketAsyncEventArgs> pool;
		internal int Count
		{
			get
			{
				return this.pool.Count;
			}
		}
		internal SocketAsyncEventArgsPool(int capacity)
		{
			this.pool = new Stack<SocketAsyncEventArgs>(capacity);
		}
		internal SocketAsyncEventArgs Pop()
		{
			SocketAsyncEventArgs result;
			lock (this.pool)
			{
				result = this.pool.Pop();
			}
			return result;
		}
		internal void Push(SocketAsyncEventArgs item)
		{
			if (item == null)
			{
				throw new ArgumentNullException("Items added to a SocketAsyncEventArgsPool cannot be null");
			}
			lock (this.pool)
			{
				this.pool.Push(item);
			}
		}
	}
}
