using System;
using System.Windows.Forms;
namespace GB698Cls
{
	public class InputPN
	{
		public static string GetData(string AFN, string FN)
		{
			iForm iForm = null;
			string text = AFN.ToUpper();
			string text2 = FN.ToUpper();
			string result = string.Empty;
			if (text == "03" && text2 == "0001")
			{
				iForm = new AFN03_01();
			}
			if (text == "06" && (text2 == "0001" | text2 == "0002" | text2 == "0003" | text2 == "0004"))
			{
				iForm = new AFN06_01();
			}
			if (text == "0E" && (text2 == "0001" | text2 == "0002"))
			{
				iForm = new AFN0E_01();
			}
			if (text == "0D" && (text2 == "0001" | text2 == "0002" | text2 == "0003" | text2 == "0004" | text2 == "0005" | text2 == "0006" | text2 == "0007" | text2 == "0008" | text2 == "0009" | text2 == "0010" | text2 == "0011" | text2 == "0012" | text2 == "0013" | text2 == "0014" | text2 == "0015" | text2 == "0016" | text2 == "0017" | text2 == "0018" | text2 == "0019" | text2 == "0020" | text2 == "0021" | text2 == "0022" | text2 == "0023" | text2 == "0024" | text2 == "0025" | text2 == "0026" | text2 == "0027" | text2 == "0028" | text2 == "0029" | text2 == "0030" | text2 == "0031" | text2 == "0032" | text2 == "0033" | text2 == "0034" | text2 == "0035" | text2 == "0036" | text2 == "0037" | text2 == "0038" | text2 == "0039" | text2 == "0040" | text2 == "0051" | text2 == "0052" | text2 == "0053" | text2 == "0054" | text2 == "0055" | text2 == "0056" | text2 == "0057" | text2 == "0058" | text2 == "0059" | text2 == "0060" | text2 == "0061" | text2 == "0062" | text2 == "0063" | text2 == "0064" | text2 == "0065" | text2 == "0066" | text2 == "0113" | text2 == "0114" | text2 == "0115" | text2 == "0116" | text2 == "0117" | text2 == "0118" | text2 == "0119" | text2 == "0120" | text2 == "0121" | text2 == "0122" | text2 == "0123" | text2 == "0124" | text2 == "0125" | text2 == "0126" | text2 == "0127" | text2 == "0128" | text2 == "0129" | text2 == "0130" | text2 == "0154" | text2 == "0155" | text2 == "0156" | text2 == "0157" | text2 == "0158" | text2 == "0159" | text2 == "0160" | text2 == "0161" | text2 == "0162" | text2 == "0163" | text2 == "0164" | text2 == "0165" | text2 == "0166" | text2 == "0167" | text2 == "0168" | text2 == "0169" | text2 == "0170" | text2 == "0171" | text2 == "0172" | text2 == "0173" | text2 == "0174" | text2 == "0175" | text2 == "0176" | text2 == "0177" | text2 == "0178" | text2 == "0179" | text2 == "0180" | text2 == "0181" | text2 == "0182" | text2 == "0183" | text2 == "0184" | text2 == "0185" | text2 == "0186" | text2 == "0187" | text2 == "0188" | text2 == "0189" | text2 == "0190" | text2 == "0191" | text2 == "0192" | text2 == "0193" | text2 == "0194" | text2 == "0195" | text2 == "0196" | text2 == "0197" | text2 == "0198" | text2 == "0199" | text2 == "0200" | text2 == "0201" | text2 == "0202" | text2 == "0203" | text2 == "0204" | text2 == "0205" | text2 == "0206" | text2 == "0207" | text2 == "0208" | text2 == "0209" | text2 == "0210" | text2 == "0211" | text2 == "0212" | text2 == "0213" | text2 == "0214" | text2 == "0215" | text2 == "0216"))
			{
				iForm = new AFN0D_01();
			}
			if (text == "0D" && (text2 == "0073" | text2 == "0074" | text2 == "0075" | text2 == "0076" | text2 == "0077" | text2 == "0078" | text2 == "0079" | text2 == "0080" | text2 == "0081" | text2 == "0082" | text2 == "0083" | text2 == "0084" | text2 == "0085" | text2 == "0086" | text2 == "0087" | text2 == "0088" | text2 == "0089" | text2 == "0090" | text2 == "0091" | text2 == "0092" | text2 == "0093" | text2 == "0094" | text2 == "0095" | text2 == "0096" | text2 == "0097" | text2 == "0098" | text2 == "0099" | text2 == "0100" | text2 == "0101" | text2 == "0102" | text2 == "0103" | text2 == "0104" | text2 == "0105" | text2 == "0106" | text2 == "0107" | text2 == "0108" | text2 == "0109" | text2 == "0110" | text2 == "0138" | text2 == "0145" | text2 == "0146" | text2 == "0147" | text2 == "0148" | text2 == "0217" | text2 == "0218"))
			{
				iForm = new AFN0D_73();
			}
			if (text == "0A" && text2 == "0010")
			{
				iForm = new AFN0A_10();
				iForm.Len = 2;
			}
			if (text == "0A" && (text2 == "0011" | text2 == "0013" | text2 == "0014" | text2 == "0015" | text2 == "0033" | text2 == "0034"))
			{
				iForm = new AFN0A_10();
				iForm.Len = 1;
			}
			if (text == "0A" && (text2 == "0038" | text2 == "0039"))
			{
				iForm = new AFN0A_38();
			}
			if (text == "04" && text2 == "0001")
			{
				iForm = new AFN04_01();
			}
			if (text == "04" && text2 == "0002")
			{
				iForm = new AFN04_02();
			}
			if (text == "04" && text2 == "0003")
			{
				iForm = new AFN04_03();
			}
			if (text == "04" && text2 == "0004")
			{
				iForm = new AFN04_04();
			}
			if (text == "04" && text2 == "0005")
			{
				iForm = new AFN04_05();
			}
			if (text == "04" && text2 == "0006")
			{
				iForm = new AFN04_06();
			}
			if (text == "04" && text2 == "0007")
			{
				iForm = new AFN04_07();
			}
			if (text == "04" && text2 == "0008")
			{
				iForm = new AFN04_08();
			}
			if (text == "04" && text2 == "0009")
			{
				iForm = new AFN04_09();
			}
			if (text == "04" && text2 == "0010")
			{
				iForm = new AFN04_10();
			}
			if (text == "04" && text2 == "0011")
			{
				iForm = new AFN04_11();
			}
			if (text == "04" && text2 == "0012")
			{
				iForm = new AFN04_12();
			}
			if (text == "04" && text2 == "0013")
			{
				iForm = new AFN04_13();
			}
			if (text == "04" && text2 == "0014")
			{
				iForm = new AFN04_14();
			}
			if (text == "04" && text2 == "0015")
			{
				iForm = new AFN04_15();
			}
			if (text == "04" && text2 == "0016")
			{
				iForm = new AFN04_16();
			}
			if (text == "04" && text2 == "0017")
			{
				iForm = new AFN04_17();
			}
			if (text == "04" && text2 == "0018")
			{
				iForm = new AFN04_18();
			}
			if (text == "04" && (text2 == "0019" | text2 == "0020"))
			{
				iForm = new AFN04_19();
			}
			if (text == "04" && text2 == "0021")
			{
				iForm = new AFN04_21();
			}
			if (text == "04" && text2 == "0022")
			{
				iForm = new AFN04_22();
			}
			if (text == "04" && text2 == "0023")
			{
				iForm = new AFN04_23();
			}
			if (text == "04" && text2 == "0025")
			{
				iForm = new AFN04_25();
			}
			if (text == "04" && text2 == "0026")
			{
				iForm = new AFN04_26();
			}
			if (text == "04" && text2 == "0027")
			{
				iForm = new AFN04_27();
			}
			if (text == "04" && text2 == "0028")
			{
				iForm = new AFN04_28();
			}
			if (text == "04" && text2 == "0029")
			{
				iForm = new AFN04_29();
			}
			if (text == "04" && text2 == "0030")
			{
				iForm = new AFN04_30();
			}
			if (text == "04" && text2 == "0031")
			{
				iForm = new AFN04_31();
			}
			if (text == "04" && text2 == "0033")
			{
				iForm = new AFN04_33();
			}
			if (text == "04" && text2 == "0034")
			{
				iForm = new AFN04_34();
			}
			if (text == "04" && text2 == "0035")
			{
				iForm = new AFN04_35();
			}
			if (text == "04" && text2 == "0036")
			{
				iForm = new AFN04_36();
			}
			if (text == "04" && text2 == "0037")
			{
				iForm = new AFN04_37();
			}
			if (text == "04" && (text2 == "0038" | text2 == "0039"))
			{
				iForm = new AFN04_38();
			}
			if (text == "04" && text2 == "0041")
			{
				iForm = new AFN04_41();
			}
			if (text == "04" && text2 == "0042")
			{
				iForm = new AFN04_42();
			}
			if (text == "04" && text2 == "0043")
			{
				iForm = new AFN04_43();
			}
			if (text == "04" && text2 == "0044")
			{
				iForm = new AFN04_44();
			}
			if (text == "04" && text2 == "0045")
			{
				iForm = new AFN04_45();
			}
			if (text == "04" && text2 == "0046")
			{
				iForm = new AFN04_46();
			}
			if (text == "04" && text2 == "0047")
			{
				iForm = new AFN04_47();
			}
			if (text == "04" && text2 == "0048")
			{
				iForm = new AFN04_48();
			}
			if (text == "04" && text2 == "0049")
			{
				iForm = new AFN04_49();
			}
			if (text == "04" && text2 == "0057")
			{
				iForm = new AFN04_57();
			}
			if (text == "04" && text2 == "0058")
			{
				iForm = new AFN04_58();
			}
			if (text == "04" && text2 == "0059")
			{
				iForm = new AFN04_59();
			}
			if (text == "04" && text2 == "0060")
			{
				iForm = new AFN04_60();
			}
			if (text == "04" && text2 == "0061")
			{
				iForm = new AFN04_61();
			}
			if (text == "04" && (text2 == "0065" | text2 == "0066"))
			{
				iForm = new AFN04_65();
			}
			if (text == "04" && (text2 == "0067" | text2 == "0068"))
			{
				iForm = new AFN04_67();
			}
			if (text == "04" && text2 == "0073")
			{
				iForm = new AFN04_73();
			}
			if (text == "04" && text2 == "0074")
			{
				iForm = new AFN04_74();
			}
			if (text == "04" && text2 == "0075")
			{
				iForm = new AFN04_75();
			}
			if (text == "04" && text2 == "0076")
			{
				iForm = new AFN04_76();
			}
			if (text == "04" && text2 == "0081")
			{
				iForm = new AFN04_81();
			}
			if (text == "04" && text2 == "0082")
			{
				iForm = new AFN04_81();
			}
			if (text == "04" && text2 == "0083")
			{
				iForm = new AFN04_83();
			}
			if (text == "04" && text2 == "0085")
			{
				iForm = new AFN04_85();
			}
			if (text == "04" && text2 == "0089")
			{
				iForm = new AFN04_89();
			}
			if (text == "05" && text2 == "0001")
			{
				iForm = new AFN05_01();
			}
			if (text == "05" && text2 == "0009")
			{
				iForm = new AFN05_09();
			}
			if (text == "05" && text2 == "0012")
			{
				iForm = new AFN05_12();
			}
			if (text == "05" && text2 == "0025")
			{
				iForm = new AFN05_25();
			}
			if (text == "05" && text2 == "0032")
			{
				iForm = new AFN05_32();
			}
			if (text == "05" && (text2 == "0041" | text2 == "0042"))
			{
				iForm = new AFN05_41();
			}
			if (text == "05" && (text2 == "0049" | text2 == "0050" | text2 == "0051" | text2 == "0052" | text2 == "0053"))
			{
				iForm = new AFN05_49();
			}
			if (text == "05" && text2 == "0059")
			{
				iForm = new AFN05_59();
			}
			if (text == "10" && text2 == "0001")
			{
				iForm = new AFN10_01();
			}
			if (text == "10" && text2 == "0009")
			{
				iForm = new AFN10_09();
			}
			if (text == "10" && text2 == "0010")
			{
				iForm = new AFN10_10();
			}
			if (text == "10" && text2 == "0011")
			{
				iForm = new AFN10_11();
			}
			if (iForm != null)
			{
				iForm.AFN = text;
				iForm.FN = text2;
				iForm.NeedSave = true;
				iForm.SetText();
				iForm.ShowDialog();
				result = iForm.Data;
			}
			return result;
		}
		public static string GetPN(string AFN, string FN)
		{
			string caption = "AFN=" + AFN + ",FN=" + FN;
			string text = string.Empty;
			AFN = AFN.ToUpper();
			if (AFN == "00")
			{
				text = "0000";
			}
			if (AFN == "01")
			{
				text = "0000";
			}
			if (AFN == "02")
			{
				text = "0000";
			}
			if (AFN == "03")
			{
				text = "0000";
			}
			if (AFN == "04")
			{
				int num = int.Parse(FN);
				if (num >= 1 & num <= 24)
				{
					text = "0000";
				}
				else
				{
					if (num >= 25 & num <= 31)
					{
						text = InputPN.InputBox(caption, "测量点号", "0001");
					}
					else
					{
						if (num >= 33 & num <= 40)
						{
							text = "0000";
						}
						else
						{
							if (num >= 41 & num <= 48)
							{
								text = InputPN.InputBox(caption, "总加组号", "0001");
							}
							else
							{
								if (num == 49)
								{
									text = InputPN.InputBox(caption, "控制轮次", "0001");
								}
								else
								{
									if (num >= 57 & num <= 64)
									{
										text = "0000";
									}
									else
									{
										if (num >= 65 & num <= 68)
										{
											text = InputPN.InputBox(caption, "任务号", "0001");
										}
										else
										{
											if (num >= 73 & num <= 80)
											{
												text = InputPN.InputBox(caption, "测量点号", "0001");
											}
											else
											{
												if (num >= 81 & num <= 83)
												{
													text = InputPN.InputBox(caption, "直流模拟量端口号", "0001");
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
			if (AFN == "05")
			{
				int num = int.Parse(FN);
				if (num >= 1 & num <= 2)
				{
					text = InputPN.InputBox(caption, "控制轮次", "0001");
				}
				else
				{
					if (num >= 9 & num <= 24)
					{
						text = InputPN.InputBox(caption, "总加组号", "0001");
					}
					else
					{
						if (num >= 25 & num <= 39)
						{
							text = "0000";
						}
						else
						{
							if (num >= 41 & num <= 42)
							{
								text = InputPN.InputBox(caption, "测量点号", "0001");
							}
							else
							{
								if (num >= 49 & num <= 53)
								{
									text = "0000";
								}
								else
								{
									if (num == 59)
									{
										text = "0000";
									}
								}
							}
						}
					}
				}
			}
			if (AFN == "06")
			{
				text = "0000";
			}
			if (AFN == "08")
			{
				text = "0000";
			}
			if (AFN == "09")
			{
				text = "0000";
			}
			if (AFN == "0A")
			{
				int num = int.Parse(FN);
				if (num >= 1 & num <= 24)
				{
					text = "0000";
				}
				else
				{
					if (num >= 25 & num <= 31)
					{
						text = InputPN.InputBox(caption, "测量点号", "0001");
					}
					else
					{
						if (num >= 33 & num <= 40)
						{
							text = "0000";
						}
						else
						{
							if (num >= 41 & num <= 48)
							{
								text = InputPN.InputBox(caption, "总加组号", "0001");
							}
							else
							{
								if (num == 49)
								{
									text = InputPN.InputBox(caption, "控制轮次", "0001");
								}
								else
								{
									if (num >= 57 & num <= 64)
									{
										text = "0000";
									}
									else
									{
										if (num >= 65 & num <= 68)
										{
											text = InputPN.InputBox(caption, "任务号", "0001");
										}
										else
										{
											if (num >= 73 & num <= 80)
											{
												text = InputPN.InputBox(caption, "测量点号", "0001");
											}
											else
											{
												if (num >= 81 & num <= 83)
												{
													text = InputPN.InputBox(caption, "直流模拟量端口号", "0001");
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
				text = InputPN.InputBox(caption, "任务号", "0001");
			}
			if (AFN == "0C")
			{
				int num = int.Parse(FN);
				if (num >= 1 & num <= 16)
				{
					text = "0000";
				}
				else
				{
					if (num >= 17 & num <= 24)
					{
						text = InputPN.InputBox(caption, "总加组号", "0001");
					}
					else
					{
						if (num >= 25 & num <= 72)
						{
							text = InputPN.InputBox(caption, "测量点号", "0001");
						}
						else
						{
							if (num == 73)
							{
								text = InputPN.InputBox(caption, "直流模拟量端口号", "0001");
							}
							else
							{
								if (num >= 81 & num <= 84)
								{
									text = InputPN.InputBox(caption, "总加组号", "0001");
								}
								else
								{
									if (num >= 89 & num <= 116)
									{
										text = InputPN.InputBox(caption, "测量点号", "0001");
									}
									else
									{
										if (num == 121)
										{
											text = InputPN.InputBox(caption, "直流模拟量端口号", "0001");
										}
										else
										{
											if (num >= 129 & num <= 248)
											{
												text = InputPN.InputBox(caption, "测量点号", "0001");
											}
										}
									}
								}
							}
						}
					}
				}
			}
			if (AFN == "0D")
			{
				int num = int.Parse(FN);
				if (num >= 1 & num <= 46)
				{
					text = InputPN.InputBox(caption, "测量点号", "0001");
				}
				else
				{
					if (num >= 49 & num <= 54)
					{
						text = "0000";
					}
					else
					{
						if (num >= 57 & num <= 76)
						{
							text = InputPN.InputBox(caption, "总加组号", "0001");
						}
						else
						{
							if (num >= 81 & num <= 128)
							{
								text = InputPN.InputBox(caption, "测量点号", "0001");
							}
							else
							{
								if (num >= 129 & num <= 130)
								{
									text = InputPN.InputBox(caption, "直流模拟量端口号", "0001");
								}
								else
								{
									if (num >= 137 & num <= 138)
									{
										text = InputPN.InputBox(caption, "直流模拟量端口号", "0001");
									}
									else
									{
										if (num >= 145 & num <= 216)
										{
											text = InputPN.InputBox(caption, "测量点号", "0001");
										}
										else
										{
											if (num >= 217 & num <= 218)
											{
												text = "0000";
											}
										}
									}
								}
							}
						}
					}
				}
			}
			if (AFN == "0E")
			{
				text = "0000";
			}
			if (AFN == "0E")
			{
				text = "0000";
			}
			if (AFN == "10")
			{
				text = "0000";
			}
			if (string.IsNullOrEmpty(text))
			{
				text = InputPN.InputBox(caption, "PN输入", "0000");
			}
			return text.PadLeft(4, '0');
		}
		public static string InputBox(string Caption, string Hint, string Default)
		{
			int num = 5;
			Form form = new Form();
			form.MinimizeBox = false;
			form.MaximizeBox = false;
			form.StartPosition = FormStartPosition.CenterScreen;
			form.FormBorderStyle = FormBorderStyle.FixedDialog;
			form.Width = 220;
			form.Height = 140;
			form.Text = Caption;
			Label label = new Label();
			label.Text = Hint;
			label.Left = 15;
			checked
			{
				label.Top = 10 + num;
				label.Parent = form;
				label.AutoSize = true;
				TextBox textBox = new TextBox();
				textBox.Left = 20;
				textBox.Top = 30 + num;
				textBox.Width = 175;
				textBox.Parent = form;
				textBox.Text = Default;
				textBox.SelectAll();
				Button button = new Button();
				button.Left = 20;
				button.Top = 60 + num;
				button.Parent = form;
				button.Text = "确定";
				form.AcceptButton = button;
				button.DialogResult = DialogResult.OK;
				Button button2 = new Button();
				button2.Left = 120;
				button2.Top = 60 + num;
				button2.Parent = form;
				button2.Text = "取消";
				button2.DialogResult = DialogResult.Cancel;
				string result;
				try
				{
					if (form.ShowDialog() == DialogResult.OK)
					{
						result = textBox.Text;
					}
					else
					{
						result = Default;
					}
				}
				finally
				{
					form.Dispose();
				}
				return result;
			}
		}
	}
}
