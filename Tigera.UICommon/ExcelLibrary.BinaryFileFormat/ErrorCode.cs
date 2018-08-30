using System;
using System.Collections.Generic;
namespace ExcelLibrary.BinaryFileFormat
{
	public class ErrorCode
	{
		public byte Code;
		public string Value;
		public static Dictionary<byte, ErrorCode> ErrorCodes;
		private ErrorCode(byte code, string value)
		{
			this.Code = code;
			this.Value = value;
		}
		public override string ToString()
		{
			return this.Value;
		}
		static ErrorCode()
		{
			ErrorCode.ErrorCodes = new Dictionary<byte, ErrorCode>();
			ErrorCode.AddErrorCode(0, "#NULL!");
			ErrorCode.AddErrorCode(7, "#DIV/0!");
			ErrorCode.AddErrorCode(15, "#VALUE!");
			ErrorCode.AddErrorCode(23, "#REF!");
			ErrorCode.AddErrorCode(29, "#NAME?");
			ErrorCode.AddErrorCode(36, "#NUM!");
			ErrorCode.AddErrorCode(42, "#N/A!");
		}
		private static void AddErrorCode(byte code, string value)
		{
			ErrorCode value2 = new ErrorCode(code, value);
			ErrorCode.ErrorCodes.Add(code, value2);
		}
	}
}
