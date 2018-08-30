using System;
namespace ExcelLibrary.BinaryDrawingFormat
{
	public class MsofbtDggContainer : MsofbtContainer
	{
		public MsofbtBstoreContainer BstoreContainer
		{
			get
			{
				MsofbtBstoreContainer result;
				foreach (EscherRecord current in this.EscherRecords)
				{
					if (current.Type == 61441)
					{
						result = (current as MsofbtBstoreContainer);
						return result;
					}
				}
				result = null;
				return result;
			}
		}
		public MsofbtDggContainer(EscherRecord record) : base(record)
		{
		}
		public MsofbtDggContainer()
		{
			this.Type = 61440;
		}
	}
}
