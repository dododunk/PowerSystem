using System;
using System.Collections.Generic;
using System.Net.Sockets;
namespace SocketUdpCore
{
	public class SocketAsyncEventArgsPool
	{
		private Stack<SocketAsyncEventArgs> m_pool;
		private static readonly object thislock = new object();
		public int Count
		{
			get
			{
				return this.m_pool.Count;
			}
		}
		public SocketAsyncEventArgsPool(int capacity)
		{
			this.m_pool = new Stack<SocketAsyncEventArgs>(capacity);
		}
		public void Push(SocketAsyncEventArgs item)
		{
			if (item == null)
			{
				throw new ArgumentNullException("Items不能为 Null");
			}
			lock (SocketAsyncEventArgsPool.thislock)
			{
				this.m_pool.Push(item);
			}
		}
		public SocketAsyncEventArgs Pop()
		{
			SocketAsyncEventArgs result;
			lock (SocketAsyncEventArgsPool.thislock)
			{
				result = this.m_pool.Pop();
			}
			return result;
		}
	}
}
