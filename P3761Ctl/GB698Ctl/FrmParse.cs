using GB698Cls;
using System;
using System.ComponentModel;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using GB698Cls.GB698Cls;
namespace GB698Ctl
{
	public class FrmParse : Form
	{
		private TextBox textbox = new TextBox();
		private TextBox textbox2 = new TextBox();
		private IContainer components = null;
		private SplitContainer splitContainer1;
		public FrmParse()
		{
			this.InitializeComponent();
			this.textbox.Parent = this.splitContainer1.Panel1;
			this.textbox.Multiline = true;
			this.textbox.ScrollBars = ScrollBars.Both;
			this.textbox.Dock = DockStyle.Fill;
			this.textbox2.Parent = this.splitContainer1.Panel2;
			this.textbox2.Multiline = true;
			this.textbox2.ScrollBars = ScrollBars.Both;
			this.textbox2.Dock = DockStyle.Fill;
		}
		private byte[] HexStrToByte(string s)
		{
			s = s.Replace("\n", "").Replace("\r", "").Replace(" ", "");
			string text = "~!@#$%^&*()_+-={}|[ ]\\;':,.<>?/，。；“”、‘";
			checked
			{
				for (int i = 0; i < text.Length; i++)
				{
					s = s.Replace(text.Substring(i, 1), "");
				}
				byte[] array = new byte[s.Length / 2];
				for (int i = 0; i < s.Length; i += 2)
				{
					array[i / 2] = Convert.ToByte(s.Substring(i, 2), 16);
				}
				return array;
			}
		}
		private string ByteToHexStr(byte[] data)
		{
			StringBuilder stringBuilder = new StringBuilder(checked(data.Length * 3));
			int num = 0;
			for (int i = 0; i < data.Length; i++)
			{
				byte value = data[i];
				checked
				{
					num++;
					stringBuilder.Append(Convert.ToString(value, 16).PadLeft(2, '0').PadRight(3, ' '));
					if (num == 16)
					{
						num = 0;
						stringBuilder.Append("\r\n");
					}
				}
			}
			return stringBuilder.ToString().Trim().ToUpper();
		}
		public void DoParse(string val)
		{
			DLT698Message dLT = new DLT698Message();
			DLT698Message.FrameInfo gFrame = default(DLT698Message.FrameInfo);
			if (!string.IsNullOrEmpty(val))
			{
				byte[] array = this.HexStrToByte(val.Trim());
				if (dLT.Assert_Basic(array))
				{
					dLT.ParseData(array, array.Length, ref gFrame);
					this.textbox.Text = this.ByteToHexStr(array);
					this.textbox2.Text = DlT698MessageLogHelper.Print_ShowFrameInfo(gFrame,dLT);
				}
				else
				{
					MessageBox.Show("帧格式错误");
				}
			}
		}
		protected override void Dispose(bool disposing)
		{
			if (disposing)
			{
				if (this.components != null)
				{
					this.components.Dispose();
				}
			}
			base.Dispose(disposing);
		}
		private void InitializeComponent()
		{
            base.SuspendLayout();
			this.splitContainer1 = new SplitContainer();
			((ISupportInitialize)this.splitContainer1).BeginInit();
			this.splitContainer1.SuspendLayout();

			this.splitContainer1.BackColor = Color.FromArgb(239, 237, 226);
			this.splitContainer1.Dock = DockStyle.Fill;
			this.splitContainer1.Location = new Point(0, 0);
			this.splitContainer1.Name = "splitContainer1";
			this.splitContainer1.Orientation = Orientation.Horizontal;
			this.splitContainer1.Size = new Size(447, 487);
			this.splitContainer1.SplitterDistance = 66;
			this.splitContainer1.SplitterWidth = 2;
			this.splitContainer1.TabIndex = 0;
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			this.BackColor = Color.FromArgb(239, 237, 226);
			base.ClientSize = new Size(447, 487);
			base.Controls.Add(this.splitContainer1);
			
			base.MaximizeBox = false;
			base.MinimizeBox = false;
			base.Name = "FrmParse";
			base.StartPosition = FormStartPosition.CenterScreen;
			this.Text = "帧解析";
			((ISupportInitialize)this.splitContainer1).EndInit();
			this.splitContainer1.ResumeLayout(false);
			base.ResumeLayout(false);
		}
	}
}
