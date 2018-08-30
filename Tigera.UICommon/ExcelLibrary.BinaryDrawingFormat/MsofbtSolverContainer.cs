using System;
namespace ExcelLibrary.BinaryDrawingFormat
{
	public class MsofbtSolverContainer : MsofbtContainer
	{
		public MsofbtSolverContainer(EscherRecord record) : base(record)
		{
		}
		public MsofbtSolverContainer()
		{
			this.Type = 61445;
		}
	}
}
