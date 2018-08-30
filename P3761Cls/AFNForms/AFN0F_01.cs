using System;
using System.ComponentModel;
using System.Drawing;
using System.Net.Sockets;
using System.Text;
using System.Windows.Forms;
using Helper;
namespace GB698Cls
{
    public enum ComunicationType
    {
        Serial = 0,
        TCPMyisClient=2,
        TCPMyisServer=1,
        UDP = 3

    }
	public class AFN0F_01 : iForm
	{
		private bool UpFile = false;
		public Socket m_Socket = null;
		public int gComPort;
		public string gCommSetting;
		public string gIP;
		public int gPort;
		public int gDelay;
        public ComunicationType gType;
		public string CID;
		public string PW;
		public string Tp;
		public string Flag;
		private DLT698Opera dlt = new DLT698Opera();
		private byte[] pbyte = new byte[0];
		private string sysfile;
		private int framenum = 0;
		private int bytelen = 0;
		private string PN;
		private IContainer components = null;
		private Label label8;
		private TextBox A1;
		private Label label9;
		private TextBox A2;
		private Button button4;
		private Label label7;
		private ComboBox textBox3;
		private Label label6;
		private OpenFileDialog openFileDialog1;
		private Button button3;
		private Button button2;
		private Label label5;
		private Label label4;
		private Label label3;
		private Label label2;
		private Button button1;
		private TextBox textBox1;
		private Label label1;
		public AFN0F_01()
		{
			this.InitializeComponent();
			this.textBox3.SelectedIndex = 1;
			this.AFN = "0F";
			this.FN = "0001";
			this.PN = "0000";
		}
		private void Button1Click(object sender, EventArgs e)
		{
			this.pbyte = new byte[0];
			this.openFileDialog1.Filter = "Hex文件|*.hex|Bin文件|*.bin|所有文件|*.*";
			this.openFileDialog1.FileName = "";
			this.openFileDialog1.ShowDialog();
			if (!string.IsNullOrEmpty(this.openFileDialog1.FileName))
			{
				this.textBox1.Text = this.openFileDialog1.FileName;
				this.sysfile = this.openFileDialog1.FileName;
				this.pbyte = stream.StreamToBytes(stream.FileToStream(this.sysfile));
				decimal d = this.pbyte.Length;
				this.label4.Text = Math.Ceiling(d / this.bytelen).ToString();
				this.framenum = int.Parse(this.label4.Text);
			}
		}
		private void Button3Click(object sender, EventArgs e)
		{
			base.Close();
		}
		private void Button4Click(object sender, EventArgs e)
		{
			this.UpFile = false;
		}
		private void Button2Click(object sender, EventArgs e)
		{
			this.button2.Enabled = false;
			this.UpFile = true;
			Application.DoEvents();
			this.dlt.A1 = this.A1.Text;
			this.dlt.A2 = this.A2.Text;
			this.dlt.AFN = this.AFN;
			this.dlt.FN = this.FN;
			this.dlt.PN = this.PN;
			this.dlt.OperType = this.gType;
			int port;
			string temp;
            if (this.gType == ComunicationType.Serial)
			{
				this.dlt.FrameDelay = 5;
				this.dlt.Delay = this.gDelay;
				port = this.gComPort;
				temp = this.gCommSetting;
			}
			else
			{
				this.dlt.FrameDelay = this.gDelay;
				this.dlt.Delay = this.gDelay;
				this.dlt.m_Port = this.m_Socket;
				port = this.gPort;
				temp = this.gIP;
			}
			this.dlt.CID = this.CID;
			this.dlt.Tp = this.Tp;
			this.dlt.PW = this.PW;
			this.dlt.Flag = this.Flag;
			bool flag = this.dlt.Open(port, temp);
			byte biaozhi = 0;
			byte shuxing = 0;
			byte zhiling = 0;
			long num = 0L;
			checked
			{
				for (int i = 0; i < this.framenum; i++)
				{
					if (this.UpFile)
					{
						this.SendData(this.GetUserData(biaozhi, shuxing, zhiling, num, i));
						num += unchecked((long)this.bytelen);
						this.label3.Text = (i + 1).ToString();
						Application.DoEvents();
					}
				}
				this.button2.Enabled = true;
				MessageBox.Show("完成");
			}
		}
		private int framelenth(long begin)
		{
			long num = (long)this.pbyte.Length;
			checked
			{
				int result;
				if (begin + unchecked((long)this.bytelen) > num)
				{
					result = (int)(num - begin);
				}
				else
				{
					result = this.bytelen;
				}
				return result;
			}
		}
		private string GetUserData(byte biaozhi, byte shuxing, byte zhiling, long begin, int ii)
		{
			string str = string.Empty;
			str += biaozhi.ToString("X2");
			str += shuxing.ToString("X2");
			str += zhiling.ToString("X2");
			str += DataConvert.ReverseStr(this.framenum.ToString("X4"));
			str += DataConvert.ReverseStr(ii.ToString("X8"));
			int num = this.framelenth(begin);
			str += DataConvert.ReverseStr(num.ToString("X4"));
			byte[] array = new byte[num];
			Array.Copy(this.pbyte, begin, array, 0L, (long)num);
			return str + this.ByteToHexStr(array);
		}
		private string ByteToHexStr(byte[] data)
		{
			StringBuilder stringBuilder = new StringBuilder(checked(data.Length * 2));
			for (int i = 0; i < data.Length; i++)
			{
				byte value = data[i];
				stringBuilder.Append(Convert.ToString(value, 16).PadLeft(2, '0'));
			}
			return stringBuilder.ToString().Trim().ToUpper();
		}
		private void TextBox3SelectedIndexChanged(object sender, EventArgs e)
		{
			this.bytelen = int.Parse(this.textBox3.Text);
			decimal d = this.pbyte.Length;
			this.label4.Text = Math.Ceiling(d / this.bytelen).ToString();
			this.framenum = int.Parse(this.label4.Text);
		}
		private void SendData(string strdata)
		{
			this.dlt.SendMSG = strdata;
			this.dlt.SendData();
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
			ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof(AFN0F_01));
			this.label1 = new Label();
			this.textBox1 = new TextBox();
			this.button1 = new Button();
			this.label2 = new Label();
			this.label3 = new Label();
			this.label4 = new Label();
			this.label5 = new Label();
			this.button2 = new Button();
			this.button3 = new Button();
			this.openFileDialog1 = new OpenFileDialog();
			this.label6 = new Label();
			this.textBox3 = new ComboBox();
			this.label7 = new Label();
			this.button4 = new Button();
			this.A2 = new TextBox();
			this.label9 = new Label();
			this.A1 = new TextBox();
			this.label8 = new Label();
			base.SuspendLayout();
			this.label1.AutoSize = true;
			this.label1.Location = new Point(29, 56);
			this.label1.Name = "label1";
			this.label1.Size = new Size(71, 12);
			this.label1.TabIndex = 25;
			this.label1.Text = "需传输文件:";
			this.textBox1.Location = new Point(110, 52);
			this.textBox1.Name = "textBox1";
			this.textBox1.Size = new Size(248, 21);
			this.textBox1.TabIndex = 26;
			this.button1.Image = (Image)componentResourceManager.GetObject("button1.Image");
			this.button1.Location = new Point(360, 51);
			this.button1.Name = "button1";
			this.button1.Size = new Size(23, 23);
			this.button1.TabIndex = 27;
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new EventHandler(this.Button1Click);
			this.label2.AutoSize = true;
			this.label2.Location = new Point(29, 115);
			this.label2.Name = "label2";
			this.label2.Size = new Size(59, 12);
			this.label2.TabIndex = 28;
			this.label2.Text = "当前帧数:";
			this.label3.AutoSize = true;
			this.label3.Location = new Point(110, 115);
			this.label3.Name = "label3";
			this.label3.Size = new Size(11, 12);
			this.label3.TabIndex = 29;
			this.label3.Text = "0";
			this.label4.AutoSize = true;
			this.label4.Location = new Point(110, 140);
			this.label4.Name = "label4";
			this.label4.Size = new Size(11, 12);
			this.label4.TabIndex = 31;
			this.label4.Text = "0";
			this.label5.AutoSize = true;
			this.label5.Location = new Point(29, 140);
			this.label5.Name = "label5";
			this.label5.Size = new Size(59, 12);
			this.label5.TabIndex = 30;
			this.label5.Text = "总共帧数:";
			this.button2.Location = new Point(173, 176);
			this.button2.Name = "button2";
			this.button2.Size = new Size(66, 23);
			this.button2.TabIndex = 32;
			this.button2.Text = "发送";
			this.button2.UseVisualStyleBackColor = true;
			this.button2.Click += new EventHandler(this.Button2Click);
			this.button3.Location = new Point(317, 176);
			this.button3.Name = "button3";
			this.button3.Size = new Size(66, 23);
			this.button3.TabIndex = 33;
			this.button3.Text = "退出";
			this.button3.UseVisualStyleBackColor = true;
			this.button3.Click += new EventHandler(this.Button3Click);
			this.openFileDialog1.FileName = "openFileDialog1";
			this.openFileDialog1.Filter = "*.xml|*.xml";
			this.label6.AutoSize = true;
			this.label6.Location = new Point(29, 84);
			this.label6.Name = "label6";
			this.label6.Size = new Size(71, 12);
			this.label6.TabIndex = 34;
			this.label6.Text = "每帧数据长:";
			this.textBox3.DropDownStyle = ComboBoxStyle.DropDownList;
			this.textBox3.FormattingEnabled = true;
			this.textBox3.Items.AddRange(new object[]
			{
				"128",
				"256",
				"512",
				"1024"
			});
			this.textBox3.Location = new Point(110, 80);
			this.textBox3.Name = "textBox3";
			this.textBox3.Size = new Size(69, 20);
			this.textBox3.TabIndex = 35;
			this.textBox3.SelectedIndexChanged += new EventHandler(this.TextBox3SelectedIndexChanged);
			this.label7.AutoSize = true;
			this.label7.Location = new Point(182, 85);
			this.label7.Name = "label7";
			this.label7.Size = new Size(29, 12);
			this.label7.TabIndex = 36;
			this.label7.Text = "字节";
			this.button4.Location = new Point(245, 176);
			this.button4.Name = "button4";
			this.button4.Size = new Size(66, 23);
			this.button4.TabIndex = 119;
			this.button4.Text = "停止";
			this.button4.UseVisualStyleBackColor = true;
			this.button4.Click += new EventHandler(this.Button4Click);
			
			this.A2.Location = new Point(238, 15);
			this.A2.Name = "A2";
			this.A2.Size = new Size(42, 21);
			this.A2.TabIndex = 123;
			this.A2.Text = "0001";
			this.label9.AutoSize = true;
			this.label9.BackColor = Color.Transparent;
			this.label9.Location = new Point(167, 18);
			this.label9.Name = "label9";
			this.label9.Size = new Size(65, 12);
			this.label9.TabIndex = 122;
			this.label9.Text = "终端地址A2";
			
			this.A1.Location = new Point(110, 15);
			this.A1.Name = "A1";
			this.A1.Size = new Size(42, 21);
			this.A1.TabIndex = 121;
			this.A1.Text = "1200";
			this.label8.AutoSize = true;
			this.label8.BackColor = Color.Transparent;
			this.label8.Location = new Point(29, 18);
			this.label8.Name = "label8";
			this.label8.Size = new Size(77, 12);
			this.label8.TabIndex = 120;
			this.label8.Text = "行政区划码A1";
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			base.ClientSize = new Size(409, 220);
			base.Controls.Add(this.A2);
			base.Controls.Add(this.label9);
			base.Controls.Add(this.A1);
			base.Controls.Add(this.label8);
			base.Controls.Add(this.button4);
			base.Controls.Add(this.label7);
			base.Controls.Add(this.textBox3);
			base.Controls.Add(this.label6);
			base.Controls.Add(this.button3);
			base.Controls.Add(this.button2);
			base.Controls.Add(this.label4);
			base.Controls.Add(this.label5);
			base.Controls.Add(this.label3);
			base.Controls.Add(this.label2);
			base.Controls.Add(this.button1);
			base.Controls.Add(this.textBox1);
			base.Controls.Add(this.label1);
			base.Name = "AFN0F_01";
			this.Text = "文件传输";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
