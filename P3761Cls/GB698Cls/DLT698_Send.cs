using System;
using System.Globalization;
using System.Text;
using Helper;
namespace GB698Cls
{
	public class DLT698_Send
	{
		public struct ItemsInfo
		{
			public string Items;
			public string Values;
			public void Clear()
			{
				this.Items = string.Empty;
				this.Values = string.Empty;
			}
		}
		//private PubFuncHelper gfunc = new PubFuncHelper();
		public DLT698_Send.ItemsInfo Info;
		public string ASCIIToHexStr(string strValue)
		{
			byte[] bytes = Encoding.ASCII.GetBytes(strValue);
			string text = string.Empty;
			checked
			{
				for (int i = 0; i < bytes.Length; i++)
				{
					text += bytes[i].ToString("X2");
				}
				return text;
			}
		}
	
		private int GetIndex(string pText, string[] allitem)
		{
			checked
			{
				int result;
				for (int i = 0; i < allitem.Length; i++)
				{
					if (allitem[i].IndexOf(pText) >= 0)
					{
						result = i;
						return result;
					}
				}
				result = 0;
				return result;
			}
		}
		private string OperaSnd(string Value, int Num, string type)
		{
			string text = string.Empty;
			string text2 = type.ToUpper();
			checked
			{
				switch (text2)
				{
				case "BIN":
					{
						long num2 = long.Parse(Value);
						string arg_174_0 = "X";
						int num = Num * 2;
						string strValue = num2.ToString(arg_174_0 + num.ToString());
						text = DataConvert.ReverseStr(strValue);
						break;
					}

				case "":
				case "BCD":
					text = DataConvert.ReverseStr(Value.PadLeft(Num * 2, '0'));
					break;

				case "HEX":
					text = Value.PadRight(Num * 2, '0');
					break;

				case "BS":
					{
						string text3 = DataConvert.ReverseStr(Value, 1);
						for (int i = 0; i < text3.Length; i += 8)
						{
							text += PubFuncHelper.BinToHex(text3.Substring(i, 8)).ToString("X2");
						}
						this.Info.Values = this.Info.Values + DataConvert.ReverseStr(text);
						break;
					}

				case "ASCII":
					text = this.ASCIIToHexStr(Value).PadRight(Num * 2, '0');
					break;

				case "A1":
					{
						DateTime dateTime = Convert.ToDateTime(Value);
						int num = dateTime.Second;
						text = num.ToString("D2");
						string arg_26D_0 = text;
						num = dateTime.Minute;
						text = arg_26D_0 + num.ToString("D2");
						string arg_289_0 = text;
						num = dateTime.Hour;
						text = arg_289_0 + num.ToString("D2");
						string arg_2A5_0 = text;
						num = dateTime.Day;
						text = arg_2A5_0 + num.ToString("D2");
						int num3 = (int)dateTime.DayOfWeek;
						if (num3 == 0)
						{
							num3 = 7;
						}
						num = dateTime.Month;
						text += (int.Parse(num.ToString(), NumberStyles.HexNumber) | num3 << 5).ToString("X2");
						string arg_316_0 = text;
						num = dateTime.Year;
						text = arg_316_0 + num.ToString("D4").Substring(2, 2);
						break;
					}

				case "A7":
					text = string.Format("{0:000.0}", float.Parse(Value));
					text = text.Replace(".", "");
					text = DataConvert.ReverseStr(text);
					break;

				case "A12":
					text = DataConvert.ReverseStr(Value.PadLeft(12, '0'));
					break;

				case "A15":
					text = DataConvert.ReverseStr(Convert.ToDateTime(Value).ToString("yyMMddHHmm"));
					break;

				case "A20":
					text = DataConvert.ReverseStr(Convert.ToDateTime(Value).ToString("yyMMdd"));
					break;

				case "A21":
					text = DataConvert.ReverseStr(Convert.ToDateTime(Value).ToString("yyMM"));
					break;

				case "A22":
					text = string.Format("{0:0.0}", float.Parse(Value));
					text = text.Replace(".", "");
					text = text.Replace(":", "");
					text = DataConvert.ReverseStr(text);
					break;

				case "A23":
					text = string.Format("{0:00.0000}", float.Parse(Value));
					text = text.Replace(".", "");
					text = text.Replace(":", "");
					text = DataConvert.ReverseStr(text);
					break;

				case "A25":
					{
						text = string.Format("{0:000.000}", float.Parse(Value));
						text = text.Replace(".", "");
						text = text.Replace(":", "");
						text = DataConvert.ReverseStr(text);
						int num4 = int.Parse(text, NumberStyles.HexNumber);
						
						text = num4.ToString("X6");
						break;
					}

				case "A26":
					text = string.Format("{0:0.000}", float.Parse(Value));
					text = text.Replace(".", "");
					text = text.Replace(":", "");
					text = DataConvert.ReverseStr(text);
					break;
				}
				return text;
			}
		}
		public void DoInfo(string AFN, string FN, string Data)
		{
			this.Info.Clear();
			int num = int.Parse(FN);
			if (AFN == "05")
			{
				if (num == 31)
				{
					this.AF05_F31(Data);
				}
			}
			if (AFN == "0D")
			{
				if (num == 1)
				{
					this.AF0D_Td_d(Data);
				}
				else
				{
					if (num == 2)
					{
						this.AF0D_Td_d(Data);
					}
					else
					{
						if (num == 3)
						{
							this.AF0D_Td_d(Data);
						}
						else
						{
							if (num == 4)
							{
								this.AF0D_Td_d(Data);
							}
							else
							{
								if (num == 5)
								{
									this.AF0D_Td_d(Data);
								}
								else
								{
									if (num == 6)
									{
										this.AF0D_Td_d(Data);
									}
									else
									{
										if (num == 7)
										{
											this.AF0D_Td_d(Data);
										}
										else
										{
											if (num == 8)
											{
												this.AF0D_Td_d(Data);
											}
											else
											{
												if (num == 9)
												{
													this.AF0D_Td_d(Data);
												}
												else
												{
													if (num == 10)
													{
														this.AF0D_Td_d(Data);
													}
													else
													{
														if (num == 11)
														{
															this.AF0D_Td_d(Data);
														}
														else
														{
															if (num == 12)
															{
																this.AF0D_Td_d(Data);
															}
															else
															{
																if (num == 17)
																{
																	this.AF0D_Td_m(Data);
																}
																else
																{
																	if (num == 18)
																	{
																		this.AF0D_Td_m(Data);
																	}
																	else
																	{
																		if (num == 19)
																		{
																			this.AF0D_Td_m(Data);
																		}
																		else
																		{
																			if (num == 20)
																			{
																				this.AF0D_Td_m(Data);
																			}
																			else
																			{
																				if (num == 21)
																				{
																					this.AF0D_Td_m(Data);
																				}
																				else
																				{
																					if (num == 22)
																					{
																						this.AF0D_Td_m(Data);
																					}
																					else
																					{
																						if (num == 23)
																						{
																							this.AF0D_Td_m(Data);
																						}
																						else
																						{
																							if (num == 24)
																							{
																								this.AF0D_Td_m(Data);
																							}
																							else
																							{
																								if (num == 25)
																								{
																									this.AF0D_Td_d(Data);
																								}
																								else
																								{
																									if (num == 26)
																									{
																										this.AF0D_Td_d(Data);
																									}
																									else
																									{
																										if (num == 27)
																										{
																											this.AF0D_Td_d(Data);
																										}
																										else
																										{
																											if (num == 28)
																											{
																												this.AF0D_Td_d(Data);
																											}
																											else
																											{
																												if (num == 29)
																												{
																													this.AF0D_Td_d(Data);
																												}
																												else
																												{
																													if (num == 30)
																													{
																														this.AF0D_Td_d(Data);
																													}
																													else
																													{
																														if (num == 31)
																														{
																															this.AF0D_Td_d(Data);
																														}
																														else
																														{
																															if (num == 32)
																															{
																																this.AF0D_Td_d(Data);
																															}
																															else
																															{
																																if (num == 33)
																																{
																																	this.AF0D_Td_m(Data);
																																}
																																else
																																{
																																	if (num == 34)
																																	{
																																		this.AF0D_Td_m(Data);
																																	}
																																	else
																																	{
																																		if (num == 35)
																																		{
																																			this.AF0D_Td_m(Data);
																																		}
																																		else
																																		{
																																			if (num == 36)
																																			{
																																				this.AF0D_Td_m(Data);
																																			}
																																			else
																																			{
																																				if (num == 37)
																																				{
																																					this.AF0D_Td_m(Data);
																																				}
																																				else
																																				{
																																					if (num == 38)
																																					{
																																						this.AF0D_Td_m(Data);
																																					}
																																					else
																																					{
																																						if (num == 39)
																																						{
																																							this.AF0D_Td_m(Data);
																																						}
																																						else
																																						{
																																							if (num == 41)
																																							{
																																								this.AF0D_Td_d(Data);
																																							}
																																							else
																																							{
																																								if (num == 42)
																																								{
																																									this.AF0D_Td_d(Data);
																																								}
																																								else
																																								{
																																									if (num == 43)
																																									{
																																										this.AF0D_Td_d(Data);
																																									}
																																									else
																																									{
																																										if (num == 44)
																																										{
																																											this.AF0D_Td_m(Data);
																																										}
																																										else
																																										{
																																											if (num == 45)
																																											{
																																												this.AF0D_Td_d(Data);
																																											}
																																											else
																																											{
																																												if (num == 46)
																																												{
																																													this.AF0D_Td_m(Data);
																																												}
																																												else
																																												{
																																													if (num == 49)
																																													{
																																														this.AF0D_Td_d(Data);
																																													}
																																													else
																																													{
																																														if (num == 50)
																																														{
																																															this.AF0D_Td_d(Data);
																																														}
																																														else
																																														{
																																															if (num == 51)
																																															{
																																																this.AF0D_Td_m(Data);
																																															}
																																															else
																																															{
																																																if (num == 52)
																																																{
																																																	this.AF0D_Td_m(Data);
																																																}
																																																else
																																																{
																																																	if (num == 53)
																																																	{
																																																		this.AF0D_Td_d(Data);
																																																	}
																																																	else
																																																	{
																																																		if (num == 54)
																																																		{
																																																			this.AF0D_Td_m(Data);
																																																		}
																																																		else
																																																		{
																																																			if (num == 57)
																																																			{
																																																				this.AF0D_Td_d(Data);
																																																			}
																																																			else
																																																			{
																																																				if (num == 58)
																																																				{
																																																					this.AF0D_Td_d(Data);
																																																				}
																																																				else
																																																				{
																																																					if (num == 59)
																																																					{
																																																						this.AF0D_Td_d(Data);
																																																					}
																																																					else
																																																					{
																																																						if (num == 60)
																																																						{
																																																							this.AF0D_Td_m(Data);
																																																						}
																																																						else
																																																						{
																																																							if (num == 61)
																																																							{
																																																								this.AF0D_Td_m(Data);
																																																							}
																																																							else
																																																							{
																																																								if (num == 62)
																																																								{
																																																									this.AF0D_Td_m(Data);
																																																								}
																																																								else
																																																								{
																																																									if (num == 65)
																																																									{
																																																										this.AF0D_Td_m(Data);
																																																									}
																																																									else
																																																									{
																																																										if (num == 66)
																																																										{
																																																											this.AF0D_Td_m(Data);
																																																										}
																																																										else
																																																										{
																																																											if (num == 73)
																																																											{
																																																												this.AF0D_Td_c(Data);
																																																											}
																																																											else
																																																											{
																																																												if (num == 74)
																																																												{
																																																													this.AF0D_Td_c(Data);
																																																												}
																																																												else
																																																												{
																																																													if (num == 75)
																																																													{
																																																														this.AF0D_Td_c(Data);
																																																													}
																																																													else
																																																													{
																																																														if (num == 76)
																																																														{
																																																															this.AF0D_Td_c(Data);
																																																														}
																																																														else
																																																														{
																																																															if (num == 81)
																																																															{
																																																																this.AF0D_Td_c(Data);
																																																															}
																																																															else
																																																															{
																																																																if (num == 82)
																																																																{
																																																																	this.AF0D_Td_c(Data);
																																																																}
																																																																else
																																																																{
																																																																	if (num == 83)
																																																																	{
																																																																		this.AF0D_Td_c(Data);
																																																																	}
																																																																	else
																																																																	{
																																																																		if (num == 84)
																																																																		{
																																																																			this.AF0D_Td_c(Data);
																																																																		}
																																																																		else
																																																																		{
																																																																			if (num == 85)
																																																																			{
																																																																				this.AF0D_Td_c(Data);
																																																																			}
																																																																			else
																																																																			{
																																																																				if (num == 86)
																																																																				{
																																																																					this.AF0D_Td_c(Data);
																																																																				}
																																																																				else
																																																																				{
																																																																					if (num == 87)
																																																																					{
																																																																						this.AF0D_Td_c(Data);
																																																																					}
																																																																					else
																																																																					{
																																																																						if (num == 88)
																																																																						{
																																																																							this.AF0D_Td_c(Data);
																																																																						}
																																																																						else
																																																																						{
																																																																							if (num == 89)
																																																																							{
																																																																								this.AF0D_Td_c(Data);
																																																																							}
																																																																							else
																																																																							{
																																																																								if (num == 90)
																																																																								{
																																																																									this.AF0D_Td_c(Data);
																																																																								}
																																																																								else
																																																																								{
																																																																									if (num == 91)
																																																																									{
																																																																										this.AF0D_Td_c(Data);
																																																																									}
																																																																									else
																																																																									{
																																																																										if (num == 92)
																																																																										{
																																																																											this.AF0D_Td_c(Data);
																																																																										}
																																																																										else
																																																																										{
																																																																											if (num == 93)
																																																																											{
																																																																												this.AF0D_Td_c(Data);
																																																																											}
																																																																											else
																																																																											{
																																																																												if (num == 94)
																																																																												{
																																																																													this.AF0D_Td_c(Data);
																																																																												}
																																																																												else
																																																																												{
																																																																													if (num == 95)
																																																																													{
																																																																														this.AF0D_Td_c(Data);
																																																																													}
																																																																													else
																																																																													{
																																																																														if (num == 97)
																																																																														{
																																																																															this.AF0D_Td_c(Data);
																																																																														}
																																																																														else
																																																																														{
																																																																															if (num == 98)
																																																																															{
																																																																																this.AF0D_Td_c(Data);
																																																																															}
																																																																															else
																																																																															{
																																																																																if (num == 99)
																																																																																{
																																																																																	this.AF0D_Td_c(Data);
																																																																																}
																																																																																else
																																																																																{
																																																																																	if (num == 100)
																																																																																	{
																																																																																		this.AF0D_Td_c(Data);
																																																																																	}
																																																																																	else
																																																																																	{
																																																																																		if (num == 101)
																																																																																		{
																																																																																			this.AF0D_Td_c(Data);
																																																																																		}
																																																																																		else
																																																																																		{
																																																																																			if (num == 102)
																																																																																			{
																																																																																				this.AF0D_Td_c(Data);
																																																																																			}
																																																																																			else
																																																																																			{
																																																																																				if (num == 103)
																																																																																				{
																																																																																					this.AF0D_Td_c(Data);
																																																																																				}
																																																																																				else
																																																																																				{
																																																																																					if (num == 104)
																																																																																					{
																																																																																						this.AF0D_Td_c(Data);
																																																																																					}
																																																																																					else
																																																																																					{
																																																																																						if (num == 105)
																																																																																						{
																																																																																							this.AF0D_Td_c(Data);
																																																																																						}
																																																																																						else
																																																																																						{
																																																																																							if (num == 106)
																																																																																							{
																																																																																								this.AF0D_Td_c(Data);
																																																																																							}
																																																																																							else
																																																																																							{
																																																																																								if (num == 107)
																																																																																								{
																																																																																									this.AF0D_Td_c(Data);
																																																																																								}
																																																																																								else
																																																																																								{
																																																																																									if (num == 108)
																																																																																									{
																																																																																										this.AF0D_Td_c(Data);
																																																																																									}
																																																																																									else
																																																																																									{
																																																																																										if (num == 109)
																																																																																										{
																																																																																											this.AF0D_Td_c(Data);
																																																																																										}
																																																																																										else
																																																																																										{
																																																																																											if (num == 110)
																																																																																											{
																																																																																												this.AF0D_Td_c(Data);
																																																																																											}
																																																																																											else
																																																																																											{
																																																																																												if (num == 113)
																																																																																												{
																																																																																													this.AF0D_Td_d(Data);
																																																																																												}
																																																																																												else
																																																																																												{
																																																																																													if (num == 114)
																																																																																													{
																																																																																														this.AF0D_Td_d(Data);
																																																																																													}
																																																																																													else
																																																																																													{
																																																																																														if (num == 115)
																																																																																														{
																																																																																															this.AF0D_Td_d(Data);
																																																																																														}
																																																																																														else
																																																																																														{
																																																																																															if (num == 116)
																																																																																															{
																																																																																																this.AF0D_Td_d(Data);
																																																																																															}
																																																																																															else
																																																																																															{
																																																																																																if (num == 117)
																																																																																																{
																																																																																																	this.AF0D_Td_d(Data);
																																																																																																}
																																																																																																else
																																																																																																{
																																																																																																	if (num == 118)
																																																																																																	{
																																																																																																		this.AF0D_Td_d(Data);
																																																																																																	}
																																																																																																	else
																																																																																																	{
																																																																																																		if (num == 121)
																																																																																																		{
																																																																																																			this.AF0D_Td_d(Data);
																																																																																																		}
																																																																																																		else
																																																																																																		{
																																																																																																			if (num == 122)
																																																																																																			{
																																																																																																				this.AF0D_Td_d(Data);
																																																																																																			}
																																																																																																			else
																																																																																																			{
																																																																																																				if (num == 123)
																																																																																																				{
																																																																																																					this.AF0D_Td_d(Data);
																																																																																																				}
																																																																																																				else
																																																																																																				{
																																																																																																					if (num == 129)
																																																																																																					{
																																																																																																						this.AF0D_Td_d(Data);
																																																																																																					}
																																																																																																					else
																																																																																																					{
																																																																																																						if (num == 130)
																																																																																																						{
																																																																																																							this.AF0D_Td_m(Data);
																																																																																																						}
																																																																																																						else
																																																																																																						{
																																																																																																							if (num == 138)
																																																																																																							{
																																																																																																								this.AF0D_Td_c(Data);
																																																																																																							}
																																																																																																							else
																																																																																																							{
																																																																																																								if (num == 145)
																																																																																																								{
																																																																																																									this.AF0D_Td_c(Data);
																																																																																																								}
																																																																																																								else
																																																																																																								{
																																																																																																									if (num == 146)
																																																																																																									{
																																																																																																										this.AF0D_Td_c(Data);
																																																																																																									}
																																																																																																									else
																																																																																																									{
																																																																																																										if (num == 147)
																																																																																																										{
																																																																																																											this.AF0D_Td_c(Data);
																																																																																																										}
																																																																																																										else
																																																																																																										{
																																																																																																											if (num == 148)
																																																																																																											{
																																																																																																												this.AF0D_Td_c(Data);
																																																																																																											}
																																																																																																											else
																																																																																																											{
																																																																																																												if (num == 153)
																																																																																																												{
																																																																																																													this.AF0D_Td_d(Data);
																																																																																																												}
																																																																																																												else
																																																																																																												{
																																																																																																													if (num == 154)
																																																																																																													{
																																																																																																														this.AF0D_Td_d(Data);
																																																																																																													}
																																																																																																													else
																																																																																																													{
																																																																																																														if (num == 155)
																																																																																																														{
																																																																																																															this.AF0D_Td_d(Data);
																																																																																																														}
																																																																																																														else
																																																																																																														{
																																																																																																															if (num == 156)
																																																																																																															{
																																																																																																																this.AF0D_Td_d(Data);
																																																																																																															}
																																																																																																															else
																																																																																																															{
																																																																																																																if (num == 157)
																																																																																																																{
																																																																																																																	this.AF0D_Td_m(Data);
																																																																																																																}
																																																																																																																else
																																																																																																																{
																																																																																																																	if (num == 158)
																																																																																																																	{
																																																																																																																		this.AF0D_Td_m(Data);
																																																																																																																	}
																																																																																																																	else
																																																																																																																	{
																																																																																																																		if (num == 159)
																																																																																																																		{
																																																																																																																			this.AF0D_Td_m(Data);
																																																																																																																		}
																																																																																																																		else
																																																																																																																		{
																																																																																																																			if (num == 160)
																																																																																																																			{
																																																																																																																				this.AF0D_Td_m(Data);
																																																																																																																			}
																																																																																																																			else
																																																																																																																			{
																																																																																																																				if (num == 161)
																																																																																																																				{
																																																																																																																					this.AF0D_Td_d(Data);
																																																																																																																				}
																																																																																																																				else
																																																																																																																				{
																																																																																																																					if (num == 162)
																																																																																																																					{
																																																																																																																						this.AF0D_Td_d(Data);
																																																																																																																					}
																																																																																																																					else
																																																																																																																					{
																																																																																																																						if (num == 163)
																																																																																																																						{
																																																																																																																							this.AF0D_Td_d(Data);
																																																																																																																						}
																																																																																																																						else
																																																																																																																						{
																																																																																																																							if (num == 164)
																																																																																																																							{
																																																																																																																								this.AF0D_Td_d(Data);
																																																																																																																							}
																																																																																																																							else
																																																																																																																							{
																																																																																																																								if (num == 165)
																																																																																																																								{
																																																																																																																									this.AF0D_Td_d(Data);
																																																																																																																								}
																																																																																																																								else
																																																																																																																								{
																																																																																																																									if (num == 166)
																																																																																																																									{
																																																																																																																										this.AF0D_Td_d(Data);
																																																																																																																									}
																																																																																																																									else
																																																																																																																									{
																																																																																																																										if (num == 167)
																																																																																																																										{
																																																																																																																											this.AF0D_Td_d(Data);
																																																																																																																										}
																																																																																																																										else
																																																																																																																										{
																																																																																																																											if (num == 168)
																																																																																																																											{
																																																																																																																												this.AF0D_Td_d(Data);
																																																																																																																											}
																																																																																																																											else
																																																																																																																											{
																																																																																																																												if (num == 169)
																																																																																																																												{
																																																																																																																													this.AF0D_Td_d(Data);
																																																																																																																												}
																																																																																																																												else
																																																																																																																												{
																																																																																																																													if (num == 170)
																																																																																																																													{
																																																																																																																														this.AF0D_Td_d(Data);
																																																																																																																													}
																																																																																																																													else
																																																																																																																													{
																																																																																																																														if (num == 171)
																																																																																																																														{
																																																																																																																															this.AF0D_Td_d(Data);
																																																																																																																														}
																																																																																																																														else
																																																																																																																														{
																																																																																																																															if (num == 172)
																																																																																																																															{
																																																																																																																																this.AF0D_Td_d(Data);
																																																																																																																															}
																																																																																																																															else
																																																																																																																															{
																																																																																																																																if (num == 173)
																																																																																																																																{
																																																																																																																																	this.AF0D_Td_d(Data);
																																																																																																																																}
																																																																																																																																else
																																																																																																																																{
																																																																																																																																	if (num == 174)
																																																																																																																																	{
																																																																																																																																		this.AF0D_Td_d(Data);
																																																																																																																																	}
																																																																																																																																	else
																																																																																																																																	{
																																																																																																																																		if (num == 175)
																																																																																																																																		{
																																																																																																																																			this.AF0D_Td_d(Data);
																																																																																																																																		}
																																																																																																																																		else
																																																																																																																																		{
																																																																																																																																			if (num == 176)
																																																																																																																																			{
																																																																																																																																				this.AF0D_Td_d(Data);
																																																																																																																																			}
																																																																																																																																			else
																																																																																																																																			{
																																																																																																																																				if (num == 177)
																																																																																																																																				{
																																																																																																																																					this.AF0D_Td_m(Data);
																																																																																																																																				}
																																																																																																																																				else
																																																																																																																																				{
																																																																																																																																					if (num == 178)
																																																																																																																																					{
																																																																																																																																						this.AF0D_Td_m(Data);
																																																																																																																																					}
																																																																																																																																					else
																																																																																																																																					{
																																																																																																																																						if (num == 179)
																																																																																																																																						{
																																																																																																																																							this.AF0D_Td_m(Data);
																																																																																																																																						}
																																																																																																																																						else
																																																																																																																																						{
																																																																																																																																							if (num == 180)
																																																																																																																																							{
																																																																																																																																								this.AF0D_Td_m(Data);
																																																																																																																																							}
																																																																																																																																							else
																																																																																																																																							{
																																																																																																																																								if (num == 181)
																																																																																																																																								{
																																																																																																																																									this.AF0D_Td_m(Data);
																																																																																																																																								}
																																																																																																																																								else
																																																																																																																																								{
																																																																																																																																									if (num == 182)
																																																																																																																																									{
																																																																																																																																										this.AF0D_Td_m(Data);
																																																																																																																																									}
																																																																																																																																									else
																																																																																																																																									{
																																																																																																																																										if (num == 183)
																																																																																																																																										{
																																																																																																																																											this.AF0D_Td_m(Data);
																																																																																																																																										}
																																																																																																																																										else
																																																																																																																																										{
																																																																																																																																											if (num == 184)
																																																																																																																																											{
																																																																																																																																												this.AF0D_Td_m(Data);
																																																																																																																																											}
																																																																																																																																											else
																																																																																																																																											{
																																																																																																																																												if (num == 185)
																																																																																																																																												{
																																																																																																																																													this.AF0D_Td_d(Data);
																																																																																																																																												}
																																																																																																																																												else
																																																																																																																																												{
																																																																																																																																													if (num == 186)
																																																																																																																																													{
																																																																																																																																														this.AF0D_Td_d(Data);
																																																																																																																																													}
																																																																																																																																													else
																																																																																																																																													{
																																																																																																																																														if (num == 187)
																																																																																																																																														{
																																																																																																																																															this.AF0D_Td_d(Data);
																																																																																																																																														}
																																																																																																																																														else
																																																																																																																																														{
																																																																																																																																															if (num == 188)
																																																																																																																																															{
																																																																																																																																																this.AF0D_Td_d(Data);
																																																																																																																																															}
																																																																																																																																															else
																																																																																																																																															{
																																																																																																																																																if (num == 189)
																																																																																																																																																{
																																																																																																																																																	this.AF0D_Td_d(Data);
																																																																																																																																																}
																																																																																																																																																else
																																																																																																																																																{
																																																																																																																																																	if (num == 190)
																																																																																																																																																	{
																																																																																																																																																		this.AF0D_Td_d(Data);
																																																																																																																																																	}
																																																																																																																																																	else
																																																																																																																																																	{
																																																																																																																																																		if (num == 191)
																																																																																																																																																		{
																																																																																																																																																			this.AF0D_Td_d(Data);
																																																																																																																																																		}
																																																																																																																																																		else
																																																																																																																																																		{
																																																																																																																																																			if (num == 192)
																																																																																																																																																			{
																																																																																																																																																				this.AF0D_Td_d(Data);
																																																																																																																																																			}
																																																																																																																																																			else
																																																																																																																																																			{
																																																																																																																																																				if (num == 193)
																																																																																																																																																				{
																																																																																																																																																					this.AF0D_Td_m(Data);
																																																																																																																																																				}
																																																																																																																																																				else
																																																																																																																																																				{
																																																																																																																																																					if (num == 194)
																																																																																																																																																					{
																																																																																																																																																						this.AF0D_Td_m(Data);
																																																																																																																																																					}
																																																																																																																																																					else
																																																																																																																																																					{
																																																																																																																																																						if (num == 195)
																																																																																																																																																						{
																																																																																																																																																							this.AF0D_Td_m(Data);
																																																																																																																																																						}
																																																																																																																																																						else
																																																																																																																																																						{
																																																																																																																																																							if (num == 196)
																																																																																																																																																							{
																																																																																																																																																								this.AF0D_Td_m(Data);
																																																																																																																																																							}
																																																																																																																																																							else
																																																																																																																																																							{
																																																																																																																																																								if (num == 201)
																																																																																																																																																								{
																																																																																																																																																									this.AF0D_Td_m(Data);
																																																																																																																																																								}
																																																																																																																																																								else
																																																																																																																																																								{
																																																																																																																																																									if (num == 202)
																																																																																																																																																									{
																																																																																																																																																										this.AF0D_Td_m(Data);
																																																																																																																																																									}
																																																																																																																																																									else
																																																																																																																																																									{
																																																																																																																																																										if (num == 203)
																																																																																																																																																										{
																																																																																																																																																											this.AF0D_Td_m(Data);
																																																																																																																																																										}
																																																																																																																																																										else
																																																																																																																																																										{
																																																																																																																																																											if (num == 204)
																																																																																																																																																											{
																																																																																																																																																												this.AF0D_Td_m(Data);
																																																																																																																																																											}
																																																																																																																																																											else
																																																																																																																																																											{
																																																																																																																																																												if (num == 205)
																																																																																																																																																												{
																																																																																																																																																													this.AF0D_Td_m(Data);
																																																																																																																																																												}
																																																																																																																																																												else
																																																																																																																																																												{
																																																																																																																																																													if (num == 206)
																																																																																																																																																													{
																																																																																																																																																														this.AF0D_Td_m(Data);
																																																																																																																																																													}
																																																																																																																																																													else
																																																																																																																																																													{
																																																																																																																																																														if (num == 207)
																																																																																																																																																														{
																																																																																																																																																															this.AF0D_Td_m(Data);
																																																																																																																																																														}
																																																																																																																																																														else
																																																																																																																																																														{
																																																																																																																																																															if (num == 208)
																																																																																																																																																															{
																																																																																																																																																																this.AF0D_Td_m(Data);
																																																																																																																																																															}
																																																																																																																																																															else
																																																																																																																																																															{
																																																																																																																																																																if (num == 209)
																																																																																																																																																																{
																																																																																																																																																																	this.AF0D_Td_d(Data);
																																																																																																																																																																}
																																																																																																																																																																else
																																																																																																																																																																{
																																																																																																																																																																	if (num == 213)
																																																																																																																																																																	{
																																																																																																																																																																		this.AF0D_Td_m(Data);
																																																																																																																																																																	}
																																																																																																																																																																	else
																																																																																																																																																																	{
																																																																																																																																																																		if (num == 214)
																																																																																																																																																																		{
																																																																																																																																																																			this.AF0D_Td_m(Data);
																																																																																																																																																																		}
																																																																																																																																																																		else
																																																																																																																																																																		{
																																																																																																																																																																			if (num == 215)
																																																																																																																																																																			{
																																																																																																																																																																				this.AF0D_Td_m(Data);
																																																																																																																																																																			}
																																																																																																																																																																			else
																																																																																																																																																																			{
																																																																																																																																																																				if (num == 216)
																																																																																																																																																																				{
																																																																																																																																																																					this.AF0D_Td_m(Data);
																																																																																																																																																																				}
																																																																																																																																																																				else
																																																																																																																																																																				{
																																																																																																																																																																					if (num == 217)
																																																																																																																																																																					{
																																																																																																																																																																						this.AF0D_Td_c(Data);
																																																																																																																																																																					}
																																																																																																																																																																					else
																																																																																																																																																																					{
																																																																																																																																																																						if (num == 218)
																																																																																																																																																																						{
																																																																																																																																																																							this.AF0D_Td_c(Data);
																																																																																																																																																																						}
																																																																																																																																																																					}
																																																																																																																																																																				}
																																																																																																																																																																			}
																																																																																																																																																																		}
																																																																																																																																																																	}
																																																																																																																																																																}
																																																																																																																																																															}
																																																																																																																																																														}
																																																																																																																																																													}
																																																																																																																																																												}
																																																																																																																																																											}
																																																																																																																																																										}
																																																																																																																																																									}
																																																																																																																																																								}
																																																																																																																																																							}
																																																																																																																																																						}
																																																																																																																																																					}
																																																																																																																																																				}
																																																																																																																																																			}
																																																																																																																																																		}
																																																																																																																																																	}
																																																																																																																																																}
																																																																																																																																															}
																																																																																																																																														}
																																																																																																																																													}
																																																																																																																																												}
																																																																																																																																											}
																																																																																																																																										}
																																																																																																																																									}
																																																																																																																																								}
																																																																																																																																							}
																																																																																																																																						}
																																																																																																																																					}
																																																																																																																																				}
																																																																																																																																			}
																																																																																																																																		}
																																																																																																																																	}
																																																																																																																																}
																																																																																																																															}
																																																																																																																														}
																																																																																																																													}
																																																																																																																												}
																																																																																																																											}
																																																																																																																										}
																																																																																																																									}
																																																																																																																								}
																																																																																																																							}
																																																																																																																						}
																																																																																																																					}
																																																																																																																				}
																																																																																																																			}
																																																																																																																		}
																																																																																																																	}
																																																																																																																}
																																																																																																															}
																																																																																																														}
																																																																																																													}
																																																																																																												}
																																																																																																											}
																																																																																																										}
																																																																																																									}
																																																																																																								}
																																																																																																							}
																																																																																																						}
																																																																																																					}
																																																																																																				}
																																																																																																			}
																																																																																																		}
																																																																																																	}
																																																																																																}
																																																																																															}
																																																																																														}
																																																																																													}
																																																																																												}
																																																																																											}
																																																																																										}
																																																																																									}
																																																																																								}
																																																																																							}
																																																																																						}
																																																																																					}
																																																																																				}
																																																																																			}
																																																																																		}
																																																																																	}
																																																																																}
																																																																															}
																																																																														}
																																																																													}
																																																																												}
																																																																											}
																																																																										}
																																																																									}
																																																																								}
																																																																							}
																																																																						}
																																																																					}
																																																																				}
																																																																			}
																																																																		}
																																																																	}
																																																																}
																																																															}
																																																														}
																																																													}
																																																												}
																																																											}
																																																										}
																																																									}
																																																								}
																																																							}
																																																						}
																																																					}
																																																				}
																																																			}
																																																		}
																																																	}
																																																}
																																															}
																																														}
																																													}
																																												}
																																											}
																																										}
																																									}
																																								}
																																							}
																																						}
																																					}
																																				}
																																			}
																																		}
																																	}
																																}
																															}
																														}
																													}
																												}
																											}
																										}
																									}
																								}
																							}
																						}
																					}
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
			if (AFN == "0B")
			{
				if (num == 2)
				{
					this.AF0B_F2(Data);
				}
			}
			if (string.IsNullOrEmpty(this.Info.Values))
			{
				this.Info.Values = Data;
			}
		}
		private void AF0D_Td_d(string DATA)
		{
			if (string.IsNullOrEmpty(DATA))
			{
				this.Info.Values = this.OperaSnd(DateTime.Now.ToString(), 6, "A20");
			}
			else
			{
				this.Info.Values = this.OperaSnd(DateTime.Parse(DATA).ToString(), 6, "A20");
			}
		}
		private void AF0D_Td_m(string DATA)
		{
			if (string.IsNullOrEmpty(DATA))
			{
				this.Info.Values = this.OperaSnd(DateTime.Now.ToString(), 6, "A21");
			}
			else
			{
				this.Info.Values = this.OperaSnd(DateTime.Parse(DATA).ToString(), 6, "A21");
			}
		}
		private void AF0D_Td_c(string DATA)
		{
			if (DATA.Trim().Length == 4)
			{
				this.Info.Values = this.OperaSnd(DateTime.Now.ToString(), 6, "A15") + DATA;
			}
			else
			{
				this.Info.Values = DATA;
			}
		}
		private void AF05_F31(string DATA)
		{
			DateTime dateTime;
			if (!string.IsNullOrEmpty(DATA))
			{
				try
				{
					dateTime = DateTime.Parse(DATA);
				}
				catch
				{
					dateTime = DateTime.Now;
				}
			}
			else
			{
				dateTime = DateTime.Now;
			}
			this.Info.Values = this.OperaSnd(dateTime.ToString(), 6, "A1");
		}
		private void AF0B_F2(string DATA)
		{
			DateTime dateTime;
			if (!string.IsNullOrEmpty(DATA))
			{
				try
				{
					dateTime = DateTime.Parse(DATA);
				}
				catch
				{
					dateTime = DateTime.Now;
				}
			}
			else
			{
				dateTime = DateTime.Now;
			}
			this.Info.Values = this.OperaSnd(dateTime.ToString(), 5, "A15");
		}
	}
}
