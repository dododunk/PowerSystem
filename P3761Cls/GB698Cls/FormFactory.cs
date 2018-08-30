using System;
namespace GB698Cls
{
	public class FormFactory
	{
		//private PubFuncHelper gfunc = new PubFuncHelper();
		private iForm giForm = null;
		public bool IsCustomize;
		public string CustomizeItems = string.Empty;
		public string CaptionText = string.Empty;
		public FormFactory()
		{
			this.IsCustomize = false;
		}
		public string CreateForm(string iAFN, string iFN, string iValues)
		{
			string result = string.Empty;
			if (iAFN == "03" && iFN == "0001")
			{
				this.giForm = new AFN03_01();
			}
			if (iAFN == "06" && (iFN == "0001" | iFN == "0002" | iFN == "0003" | iFN == "0004"))
			{
				this.giForm = new AFN06_01();
			}
			if (iAFN == "0E" && (iFN == "0001" | iFN == "0002"))
			{
				this.giForm = new AFN0E_01();
			}
			if (iAFN == "0D" && (iFN == "0001" | iFN == "0002" | iFN == "0003" | iFN == "0004" | iFN == "0005" | iFN == "0006" | iFN == "0007" | iFN == "0008" | iFN == "0009" | iFN == "0010" | iFN == "0011" | iFN == "0012" | iFN == "0013" | iFN == "0014" | iFN == "0015" | iFN == "0016" | iFN == "0017" | iFN == "0018" | iFN == "0019" | iFN == "0020" | iFN == "0021" | iFN == "0022" | iFN == "0023" | iFN == "0024" | iFN == "0025" | iFN == "0026" | iFN == "0027" | iFN == "0028" | iFN == "0029" | iFN == "0030" | iFN == "0031" | iFN == "0032" | iFN == "0033" | iFN == "0034" | iFN == "0035" | iFN == "0036" | iFN == "0037" | iFN == "0038" | iFN == "0039" | iFN == "0040" | iFN == "0051" | iFN == "0052" | iFN == "0053" | iFN == "0054" | iFN == "0055" | iFN == "0056" | iFN == "0057" | iFN == "0058" | iFN == "0059" | iFN == "0060" | iFN == "0061" | iFN == "0062" | iFN == "0063" | iFN == "0064" | iFN == "0065" | iFN == "0066" | iFN == "0113" | iFN == "0114" | iFN == "0115" | iFN == "0116" | iFN == "0117" | iFN == "0118" | iFN == "0119" | iFN == "0120" | iFN == "0121" | iFN == "0122" | iFN == "0123" | iFN == "0124" | iFN == "0125" | iFN == "0126" | iFN == "0127" | iFN == "0128" | iFN == "0129" | iFN == "0130" | iFN == "0154" | iFN == "0155" | iFN == "0156" | iFN == "0157" | iFN == "0158" | iFN == "0159" | iFN == "0160" | iFN == "0161" | iFN == "0162" | iFN == "0163" | iFN == "0164" | iFN == "0165" | iFN == "0166" | iFN == "0167" | iFN == "0168" | iFN == "0169" | iFN == "0170" | iFN == "0171" | iFN == "0172" | iFN == "0173" | iFN == "0174" | iFN == "0175" | iFN == "0176" | iFN == "0177" | iFN == "0178" | iFN == "0179" | iFN == "0180" | iFN == "0181" | iFN == "0182" | iFN == "0183" | iFN == "0184" | iFN == "0185" | iFN == "0186" | iFN == "0187" | iFN == "0188" | iFN == "0189" | iFN == "0190" | iFN == "0191" | iFN == "0192" | iFN == "0193" | iFN == "0194" | iFN == "0195" | iFN == "0196" | iFN == "0197" | iFN == "0198" | iFN == "0199" | iFN == "0200" | iFN == "0201" | iFN == "0202" | iFN == "0203" | iFN == "0204" | iFN == "0205" | iFN == "0206" | iFN == "0207" | iFN == "0208" | iFN == "0209" | iFN == "0210" | iFN == "0211" | iFN == "0212" | iFN == "0213" | iFN == "0214" | iFN == "0215" | iFN == "0216"))
			{
				this.giForm = new AFN0D_01();
			}
			if (iAFN == "0D" && (iFN == "0073" | iFN == "0074" | iFN == "0075" | iFN == "0076" | iFN == "0077" | iFN == "0078" | iFN == "0079" | iFN == "0080" | iFN == "0081" | iFN == "0082" | iFN == "0083" | iFN == "0084" | iFN == "0085" | iFN == "0086" | iFN == "0087" | iFN == "0088" | iFN == "0089" | iFN == "0090" | iFN == "0091" | iFN == "0092" | iFN == "0093" | iFN == "0094" | iFN == "0095" | iFN == "0096" | iFN == "0097" | iFN == "0098" | iFN == "0099" | iFN == "0100" | iFN == "0101" | iFN == "0102" | iFN == "0103" | iFN == "0104" | iFN == "0105" | iFN == "0106" | iFN == "0107" | iFN == "0108" | iFN == "0109" | iFN == "0110" | iFN == "0138" | iFN == "0145" | iFN == "0146" | iFN == "0147" | iFN == "0148" | iFN == "0217" | iFN == "0218"))
			{
				this.giForm = new AFN0D_73();
			}
			if (iAFN == "0B" && iFN == "0002")
			{
				this.giForm = new AFN0B_02();
			}
			if (iAFN == "0A" && iFN == "0010")
			{
				this.giForm = new AFN0A_10();
				this.giForm.Len = 2;
			}
			if (iAFN == "0A" && (iFN == "0011" | iFN == "0013" | iFN == "0014" | iFN == "0015" | iFN == "0033" | iFN == "0034"))
			{
				this.giForm = new AFN0A_10();
				this.giForm.Len = 1;
			}
			if (iAFN == "0A" && (iFN == "0038" | iFN == "0039"))
			{
				this.giForm = new AFN0A_38();
			}
			if (iAFN == "04" && iFN == "0001")
			{
				this.giForm = new AFN04_01();
			}
			if (iAFN == "04" && iFN == "0002")
			{
				this.giForm = new AFN04_02();
			}
			if (iAFN == "04" && iFN == "0003")
			{
				this.giForm = new AFN04_03();
			}
			if (iAFN == "04" && iFN == "0004")
			{
				this.giForm = new AFN04_04();
			}
			if (iAFN == "04" && iFN == "0005")
			{
				this.giForm = new AFN04_05();
			}
			if (iAFN == "04" && iFN == "0006")
			{
				this.giForm = new AFN04_06();
			}
			if (iAFN == "04" && iFN == "0007")
			{
				this.giForm = new AFN04_07();
			}
			if (iAFN == "04" && iFN == "0008")
			{
				this.giForm = new AFN04_08();
			}
			if (iAFN == "04" && iFN == "0009")
			{
				this.giForm = new AFN04_09();
			}
			if (iAFN == "04" && iFN == "0010")
			{
				this.giForm = new AFN04_10();
			}
			if (iAFN == "04" && iFN == "0011")
			{
				this.giForm = new AFN04_11();
			}
			if (iAFN == "04" && iFN == "0012")
			{
				this.giForm = new AFN04_12();
			}
			if (iAFN == "04" && iFN == "0013")
			{
				this.giForm = new AFN04_13();
			}
			if (iAFN == "04" && iFN == "0014")
			{
				this.giForm = new AFN04_14();
			}
			if (iAFN == "04" && iFN == "0015")
			{
				this.giForm = new AFN04_15();
			}
			if (iAFN == "04" && iFN == "0016")
			{
				this.giForm = new AFN04_16();
			}
			if (iAFN == "04" && iFN == "0017")
			{
				this.giForm = new AFN04_17();
			}
			if (iAFN == "04" && iFN == "0018")
			{
				this.giForm = new AFN04_18();
			}
			if (iAFN == "04" && (iFN == "0019" | iFN == "0020"))
			{
				this.giForm = new AFN04_19();
			}
			if (iAFN == "04" && iFN == "0021")
			{
				this.giForm = new AFN04_21();
			}
			if (iAFN == "04" && iFN == "0022")
			{
				this.giForm = new AFN04_22();
			}
			if (iAFN == "04" && iFN == "0023")
			{
				this.giForm = new AFN04_23();
			}
			if (iAFN == "04" && iFN == "0025")
			{
				this.giForm = new AFN04_25();
			}
			if (iAFN == "04" && iFN == "0026")
			{
				this.giForm = new AFN04_26();
			}
			if (iAFN == "04" && iFN == "0027")
			{
				this.giForm = new AFN04_27();
			}
			if (iAFN == "04" && iFN == "0028")
			{
				this.giForm = new AFN04_28();
			}
			if (iAFN == "04" && iFN == "0029")
			{
				this.giForm = new AFN04_29();
			}
			if (iAFN == "04" && iFN == "0030")
			{
				this.giForm = new AFN04_30();
			}
			if (iAFN == "04" && iFN == "0031")
			{
				this.giForm = new AFN04_31();
			}
			if (iAFN == "04" && iFN == "0033")
			{
				this.giForm = new AFN04_33();
			}
			if (iAFN == "04" && iFN == "0034")
			{
				this.giForm = new AFN04_34();
			}
			if (iAFN == "04" && iFN == "0035")
			{
				this.giForm = new AFN04_35();
			}
			if (iAFN == "04" && iFN == "0036")
			{
				this.giForm = new AFN04_36();
			}
			if (iAFN == "04" && iFN == "0037")
			{
				this.giForm = new AFN04_37();
			}
			if (iAFN == "04" && (iFN == "0038" | iFN == "0039"))
			{
				this.giForm = new AFN04_38();
			}
			if (iAFN == "04" && iFN == "0041")
			{
				this.giForm = new AFN04_41();
			}
			if (iAFN == "04" && iFN == "0042")
			{
				this.giForm = new AFN04_42();
			}
			if (iAFN == "04" && iFN == "0043")
			{
				this.giForm = new AFN04_43();
			}
			if (iAFN == "04" && iFN == "0044")
			{
				this.giForm = new AFN04_44();
			}
			if (iAFN == "04" && iFN == "0045")
			{
				this.giForm = new AFN04_45();
			}
			if (iAFN == "04" && iFN == "0046")
			{
				this.giForm = new AFN04_46();
			}
			if (iAFN == "04" && iFN == "0047")
			{
				this.giForm = new AFN04_47();
			}
			if (iAFN == "04" && iFN == "0048")
			{
				this.giForm = new AFN04_48();
			}
			if (iAFN == "04" && iFN == "0049")
			{
				this.giForm = new AFN04_49();
			}
			if (iAFN == "04" && iFN == "0057")
			{
				this.giForm = new AFN04_57();
			}
			if (iAFN == "04" && iFN == "0058")
			{
				this.giForm = new AFN04_58();
			}
			if (iAFN == "04" && iFN == "0059")
			{
				this.giForm = new AFN04_59();
			}
			if (iAFN == "04" && iFN == "0060")
			{
				this.giForm = new AFN04_60();
			}
			if (iAFN == "04" && iFN == "0061")
			{
				this.giForm = new AFN04_61();
			}
			if (iAFN == "04" && (iFN == "0065" | iFN == "0066"))
			{
				this.giForm = new AFN04_65();
			}
			if (iAFN == "04" && (iFN == "0067" | iFN == "0068"))
			{
				this.giForm = new AFN04_67();
			}
			if (iAFN == "04" && iFN == "0073")
			{
				this.giForm = new AFN04_73();
			}
			if (iAFN == "04" && iFN == "0074")
			{
				this.giForm = new AFN04_74();
			}
			if (iAFN == "04" && iFN == "0075")
			{
				this.giForm = new AFN04_75();
			}
			if (iAFN == "04" && iFN == "0076")
			{
				this.giForm = new AFN04_76();
			}
			if (iAFN == "04" && iFN == "0081")
			{
				this.giForm = new AFN04_81();
			}
			if (iAFN == "04" && iFN == "0082")
			{
				this.giForm = new AFN04_81();
			}
			if (iAFN == "04" && iFN == "0083")
			{
				this.giForm = new AFN04_83();
			}
			if (iAFN == "04" && iFN == "0085")
			{
				this.giForm = new AFN04_85();
			}
			if (iAFN == "04" && iFN == "0089")
			{
				this.giForm = new AFN04_89();
			}
			if (iAFN == "05" && iFN == "0001")
			{
				this.giForm = new AFN05_01();
			}
			if (iAFN == "05" && iFN == "0009")
			{
				this.giForm = new AFN05_09();
			}
			if (iAFN == "05" && iFN == "0012")
			{
				this.giForm = new AFN05_12();
			}
			if (iAFN == "05" && iFN == "0025")
			{
				this.giForm = new AFN05_25();
			}
			if (iAFN == "05" && iFN == "0031")
			{
				this.giForm = new AFN05_31();
			}
			if (iAFN == "05" && iFN == "0032")
			{
				this.giForm = new AFN05_32();
			}
			if (iAFN == "05" && (iFN == "0041" | iFN == "0042"))
			{
				this.giForm = new AFN05_41();
			}
			if (iAFN == "05" && (iFN == "0049" | iFN == "0050" | iFN == "0051" | iFN == "0052" | iFN == "0053"))
			{
				this.giForm = new AFN05_49();
			}
			if (iAFN == "05" && iFN == "0059")
			{
				this.giForm = new AFN05_59();
			}
			if (iAFN == "10" && iFN == "0001")
			{
				this.giForm = new AFN10_01();
			}
			if (iAFN == "10" && iFN == "0009")
			{
				this.giForm = new AFN10_09();
			}
			if (iAFN == "10" && iFN == "0010")
			{
				this.giForm = new AFN10_10();
			}
			if (iAFN == "10" && iFN == "0011")
			{
				this.giForm = new AFN10_11();
			}
			if (this.IsCustomize)
			{
				this.giForm = new CustomizeInput();
			}
			if (this.giForm != null)
			{
				if (!string.IsNullOrEmpty(this.CaptionText))
				{
					iForm expr_1825 = this.giForm;
					expr_1825.Text = expr_1825.Text + " " + this.CaptionText;
				}
				this.giForm.AFN = iAFN;
				this.giForm.FN = iFN;
				this.giForm.IsCustomize = this.IsCustomize;
				this.giForm.CustomizeItems = this.CustomizeItems;
				this.giForm.NeedSave = true;
				this.giForm.Data = iValues;
				this.giForm.SetText();
				this.giForm.ShowDialog();
				result = this.giForm.Data;
				this.giForm = null;
			}
			return result;
		}
		public void DisplayR(string iAFN, string iFN, string iValues)
		{
			if (string.IsNullOrEmpty(iValues) | iValues.ToUpper().IndexOf("部分确认") >= 0)
			{
				iValues = iValues.Split(new char[]
				{
					':'
				})[1];
				iAFN = "00";
				iFN = "0003";
				this.giForm = new DataParse();
			}
			else
			{
				if (string.IsNullOrEmpty(iValues) | iValues.ToUpper().IndexOf("ERROR") >= 0 | iValues.ToUpper().IndexOf("确认") >= 0 | iValues.ToUpper().IndexOf("否认") >= 0)
				{
					return;
				}
				if (iAFN == "00" | iFN == "0003")
				{
					this.giForm = new DataParse();
				}
				if (iAFN == "03")
				{
					this.giForm = new DataParse();
				}
				if (iAFN == "06")
				{
					this.giForm = new DataParse();
				}
				if (iAFN == "09")
				{
					this.giForm = new DataParse();
				}
				if (iAFN == "0A" && iFN == "0001")
				{
					this.giForm = new AFN04_01();
				}
				if (iAFN == "0A" && iFN == "0002")
				{
					this.giForm = new AFN04_02();
				}
				if (iAFN == "0A" && iFN == "0003")
				{
					this.giForm = new AFN04_03();
				}
				if (iAFN == "0A" && iFN == "0004")
				{
					this.giForm = new AFN04_04();
				}
				if (iAFN == "0A" && iFN == "0005")
				{
					this.giForm = new AFN04_05();
				}
				if (iAFN == "0A" && iFN == "0006")
				{
					this.giForm = new AFN04_06();
				}
				if (iAFN == "0A" && iFN == "0007")
				{
					this.giForm = new AFN04_07();
				}
				if (iAFN == "0A" && iFN == "0008")
				{
					this.giForm = new AFN04_08();
				}
				if (iAFN == "0A" && iFN == "0009")
				{
					this.giForm = new AFN04_09();
				}
				if (iAFN == "0A" && iFN == "0010")
				{
					this.giForm = new AFN04_10();
				}
				if (iAFN == "0A" && iFN == "0011")
				{
					this.giForm = new AFN04_11();
				}
				if (iAFN == "0A" && iFN == "0012")
				{
					this.giForm = new AFN04_12();
				}
				if (iAFN == "0A" && iFN == "0013")
				{
					this.giForm = new AFN04_13();
				}
				if (iAFN == "0A" && iFN == "0014")
				{
					this.giForm = new AFN04_14();
				}
				if (iAFN == "0A" && iFN == "0015")
				{
					this.giForm = new AFN04_15();
				}
				if (iAFN == "0A" && iFN == "0016")
				{
					this.giForm = new AFN04_16();
				}
				if (iAFN == "0A" && iFN == "0017")
				{
					this.giForm = new AFN04_17();
				}
				if (iAFN == "0A" && iFN == "0018")
				{
					this.giForm = new AFN04_18();
				}
				if (iAFN == "0A" && (iFN == "0019" | iFN == "0020"))
				{
					this.giForm = new AFN04_19();
				}
				if (iAFN == "0A" && iFN == "0021")
				{
					this.giForm = new AFN04_21();
				}
				if (iAFN == "0A" && iFN == "0022")
				{
					this.giForm = new AFN04_22();
				}
				if (iAFN == "0A" && iFN == "0023")
				{
					this.giForm = new AFN04_23();
				}
				if (iAFN == "0A" && iFN == "0025")
				{
					this.giForm = new AFN04_25();
				}
				if (iAFN == "0A" && iFN == "0026")
				{
					this.giForm = new AFN04_26();
				}
				if (iAFN == "0A" && iFN == "0027")
				{
					this.giForm = new AFN04_27();
				}
				if (iAFN == "0A" && iFN == "0028")
				{
					this.giForm = new AFN04_28();
				}
				if (iAFN == "0A" && iFN == "0029")
				{
					this.giForm = new AFN04_29();
				}
				if (iAFN == "0A" && iFN == "0030")
				{
					this.giForm = new AFN04_30();
				}
				if (iAFN == "0A" && iFN == "0031")
				{
					this.giForm = new AFN04_31();
				}
				if (iAFN == "0A" && iFN == "0033")
				{
					this.giForm = new AFN04_33();
				}
				if (iAFN == "0A" && iFN == "0034")
				{
					this.giForm = new AFN04_34();
				}
				if (iAFN == "0A" && iFN == "0035")
				{
					this.giForm = new AFN04_35();
				}
				if (iAFN == "0A" && iFN == "0036")
				{
					this.giForm = new AFN04_36();
				}
				if (iAFN == "0A" && iFN == "0037")
				{
					this.giForm = new AFN04_37();
				}
				if (iAFN == "0A" && (iFN == "0038" | iFN == "0039"))
				{
					this.giForm = new AFN04_38();
				}
				if (iAFN == "0A" && iFN == "0041")
				{
					this.giForm = new AFN04_41();
				}
				if (iAFN == "0A" && iFN == "0042")
				{
					this.giForm = new AFN04_42();
				}
				if (iAFN == "0A" && iFN == "0043")
				{
					this.giForm = new AFN04_43();
				}
				if (iAFN == "0A" && iFN == "0044")
				{
					this.giForm = new AFN04_44();
				}
				if (iAFN == "0A" && iFN == "0045")
				{
					this.giForm = new AFN04_45();
				}
				if (iAFN == "0A" && iFN == "0046")
				{
					this.giForm = new AFN04_46();
				}
				if (iAFN == "0A" && iFN == "0047")
				{
					this.giForm = new AFN04_47();
				}
				if (iAFN == "0A" && iFN == "0048")
				{
					this.giForm = new AFN04_48();
				}
				if (iAFN == "0A" && iFN == "0049")
				{
					this.giForm = new AFN04_49();
				}
				if (iAFN == "0A" && iFN == "0057")
				{
					this.giForm = new AFN04_57();
				}
				if (iAFN == "0A" && iFN == "0058")
				{
					this.giForm = new AFN04_58();
				}
				if (iAFN == "0A" && iFN == "0059")
				{
					this.giForm = new AFN04_59();
				}
				if (iAFN == "0A" && iFN == "0060")
				{
					this.giForm = new AFN04_60();
				}
				if (iAFN == "0A" && iFN == "0061")
				{
					this.giForm = new AFN04_61();
				}
				if (iAFN == "0A" && (iFN == "0065" | iFN == "0066"))
				{
					this.giForm = new AFN04_65();
				}
				if (iAFN == "0A" && (iFN == "0067" | iFN == "0068"))
				{
					this.giForm = new AFN04_67();
				}
				if (iAFN == "0A" && iFN == "0073")
				{
					this.giForm = new AFN04_73();
				}
				if (iAFN == "0A" && iFN == "0074")
				{
					this.giForm = new AFN04_74();
				}
				if (iAFN == "0A" && iFN == "0075")
				{
					this.giForm = new AFN04_75();
				}
				if (iAFN == "0A" && iFN == "0076")
				{
					this.giForm = new AFN04_76();
				}
				if (iAFN == "0A" && iFN == "0081")
				{
					this.giForm = new AFN04_81();
				}
				if (iAFN == "0A" && iFN == "0082")
				{
					this.giForm = new AFN04_81();
				}
				if (iAFN == "0A" && iFN == "0083")
				{
					this.giForm = new AFN04_83();
				}
				if (iAFN == "0A" && iFN == "0085")
				{
					this.giForm = new AFN04_85();
				}
				if (iAFN == "0A" && iFN == "0089")
				{
					this.giForm = new AFN04_89();
				}
				if (iAFN == "0B")
				{
					this.giForm = new DataParse();
				}
				if (iAFN == "0C")
				{
					this.giForm = new DataParse();
				}
				if (iAFN == "0D")
				{
					this.giForm = new DataParse();
				}
				if (iAFN == "0E")
				{
					this.giForm = new DataParse();
				}
				if (iAFN == "10")
				{
					this.giForm = new DataParse();
				}
				if (this.IsCustomize)
				{
					this.giForm = new DataParse();
				}
			}
			if (this.giForm != null)
			{
				if (!string.IsNullOrEmpty(this.CaptionText))
				{
					iForm expr_CBE = this.giForm;
					expr_CBE.Text = expr_CBE.Text + " " + this.CaptionText;
				}
				this.giForm.IsCustomize = this.IsCustomize;
				this.giForm.CustomizeItems = this.CustomizeItems;
				this.giForm.AFN = iAFN;
				this.giForm.FN = iFN;
				this.giForm.Data = iValues;
				this.giForm.NeedSave = false;
				this.giForm.Data = iValues;
				this.giForm.SetText();
				this.giForm.ShowDialog();
				this.giForm = null;
			}
		}
	}
}
