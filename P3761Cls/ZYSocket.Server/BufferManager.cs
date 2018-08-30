using System;
using System.Collections.Generic;
using System.Net.Sockets;
namespace ZYSocket.Server
{
	internal sealed class BufferManager
	{
		private byte[] buffer;
		private int bufferSize;
		private int numSize;
		private int currentIndex;
		private Stack<int> freeIndexPool;
		public BufferManager(int numsize, int buffersize)
		{
			this.numSize = numsize;
			this.bufferSize = buffersize;
		}
		public void Inint()
		{
			this.buffer = new byte[this.numSize];
			this.freeIndexPool = new Stack<int>(this.numSize / this.bufferSize);
		}
		internal void FreeBuffer(SocketAsyncEventArgs args)
		{
			this.freeIndexPool.Push(args.Offset);
			args.SetBuffer(null, 0, 0);
		}
		internal bool SetBuffer(SocketAsyncEventArgs args)
		{
			checked
			{
				bool result;
				if (this.freeIndexPool.Count > 0)
				{
					args.SetBuffer(this.buffer, this.freeIndexPool.Pop(), this.bufferSize);
				}
				else
				{
					if (this.numSize - this.bufferSize < this.currentIndex)
					{
						result = false;
						return result;
					}
					args.SetBuffer(this.buffer, this.currentIndex, this.bufferSize);
					this.currentIndex += this.bufferSize;
				}
				result = true;
				return result;
			}
		}
	}
}
