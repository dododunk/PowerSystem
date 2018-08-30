using System;
using System.Collections.Generic;
using System.Net.Sockets;
namespace SocketUdpCore
{
	public class BufferManager
	{
		private int numBytes;
		private byte[] buffer;
		private Stack<int> freeIndexPool;
		private int currentIndex;
		private int bufferSize;
		private Random random;
		public BufferManager(int totalBytes, int bufferSize)
		{
			this.numBytes = totalBytes;
			this.currentIndex = 0;
			this.bufferSize = bufferSize;
			this.freeIndexPool = new Stack<int>();
			this.random = new Random();
		}
		public void InitBuffer()
		{
			this.buffer = new byte[this.numBytes];
			this.random.NextBytes(this.buffer);
		}
		public bool SetBuffer(SocketAsyncEventArgs args)
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
					if (this.numBytes - this.bufferSize < this.currentIndex)
					{
						result = false;
						return result;
					}
					args.UserToken = this.currentIndex;
					args.SetBuffer(this.buffer, this.currentIndex, this.bufferSize);
					this.currentIndex += this.bufferSize;
				}
				result = true;
				return result;
			}
		}
		public void SetBufferValue(SocketAsyncEventArgs args, byte[] value)
		{
			int num = (int)args.UserToken;
			checked
			{
				for (int i = num; i < this.bufferSize + num; i++)
				{
					if (i >= value.Length)
					{
						break;
					}
					this.buffer[i] = value[i - num];
				}
			}
		}
		public void FreeBuffer(SocketAsyncEventArgs args)
		{
			this.freeIndexPool.Push(args.Offset);
			args.SetBuffer(null, 0, 0);
		}
	}
}
