using GB698Cls;
using System;
using System.ComponentModel;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using WinFormsUI.Docking;
using GB698Cls.GB698Cls;
namespace GB698Ctl
{
	public class UCFrameParse: UserControl
	{
		private DLT698_Recv gAS = new DLT698_Recv();
		private IContainer components = null;
		private ToolStripMenuItem 清空ToolStripMenuItem;
		private ContextMenuStrip contextMenuStrip1;
		private DataGridViewEx DataGridView1;
		private SplitContainer splitContainer1;
		private Button button1;
		private TextBox textBox2;
		private Label label2;
		private TextBox textBox1;
		private Label label1;
		private DataGridViewTextBoxColumn Column1;
		private DataGridViewTextBoxColumn Column2;
		public UCFrameParse()
		{
			this.InitializeComponent();
			this.DataGridView1.AllowUserToAddRows = false;
			this.DataGridView1.BorderStyle = BorderStyle.Fixed3D;
			this.textBox2.BorderStyle = BorderStyle.Fixed3D;
			this.DataGridView1.CellMouseDoubleClick += new DataGridViewCellMouseEventHandler(this.DataGridView1CellMouseClick);
            this.textBox1.Text = 
            "68 56 00 56 00 68 4B 73 08 10 00 0C 0D E3 02 01 01 00 29 11 11 00 22 35 01 30 00 A9 16";
		}
		private void Button1Click(object sender, EventArgs e)
		{
			this.textBox1.Text = this.ByteToHexStr(this.HexStrToByte(this.textBox1.Text));
			this.DoParse(this.textBox1.Text);
		}
		private void 清空ToolStripMenuItemClick(object sender, EventArgs e)
		{
			this.textBox1.Text = "";
		}
		public string ByteToHexStr(byte[] data)
		{
			StringBuilder stringBuilder = new StringBuilder(checked(data.Length * 3));
			for (int i = 0; i < data.Length; i++)
			{
				byte value = data[i];
				stringBuilder.Append(Convert.ToString(value, 16).PadLeft(2, '0').PadRight(3, ' '));
			}
			return stringBuilder.ToString().Trim().ToUpper();
		}
		private string ByteToHexStr_16(byte[] data)
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
		public byte[] HexStrToByte(string s)
		{
			s = s.Replace("\n", "").Replace("\r", "").Replace(" ", "");
			string text = "~!@#$%^&*()_+-={}|[ ]\\;':,.<>?/，。；“”、‘";
			checked
			{
				for (int i = 0; i < text.Length; i++)
				{
					s = s.Replace(text.Substring(i, 1), "");
				}
				int length = s.Length;
                if (length % 2 == 1)
                {
                    MessageBox.Show(this,"输入的16进制串长度错误length = " + s.Length.ToString() + "（应该为偶数长度）","错误",MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return new byte[0];
                }
				byte[] array = new byte[length / 2];
				for (int i = 0; i < s.Length; i += 2)
				{
					array[i / 2] = Convert.ToByte(s.Substring(i, 2), 16);
				}
				return array;
			}
		}
		public void DoParse(string val)
		{
			this.textBox1.Text = val;
			this.textBox2.Text = "";
			DLT698Message dLT = new DLT698Message();
			DLT698Message.FrameInfo gFrame = default(DLT698Message.FrameInfo);
			if (!string.IsNullOrEmpty(val))
			{
				byte[] array = this.HexStrToByte(val.Trim());
				if (dLT.Assert_Basic(array))
				{
					dLT.ParseData(array, array.Length, ref gFrame);
					this.textBox2.Text = "帧信息:\r\n";
					TextBox expr_7E = this.textBox2;
					expr_7E.Text += this.ByteToHexStr_16(array);
					TextBox expr_9C = this.textBox2;
					expr_9C.Text += "\r\n";
					TextBox expr_B8 = this.textBox2;
					expr_B8.Text += "-----------------------------------------------";
					TextBox expr_D4 = this.textBox2;
					expr_D4.Text += "\r\n\r\n";
					TextBox expr_F0 = this.textBox2;
					expr_F0.Text += DlT698MessageLogHelper.Print_ShowFrameInfo(gFrame,dLT);
					if (gFrame.DIR == "1")
					{
						this.SetText(gFrame.AFN, gFrame.FN, gFrame.Data);
					}
				}
				else
				{
					MessageBox.Show("帧格式错误");
				}
			}
		}
		public void SetText(string AFN, string FN, string Data)
		{
			checked
			{
				if (!string.IsNullOrEmpty(Data))
				{
					string customizeItems = Program.gFaDataBase.GetCustomizeItems(AFN, FN);
					bool isCustomize = customizeItems.Split(new char[]
					{
						'|'
					}).Length > 1;
					this.gAS.DoInfo(AFN, FN, Data, isCustomize, customizeItems);
					this.DataGridView1.Rows.Clear();
					for (int i = 0; i < this.gAS.ItemData.Count; i++)
					{
						if (!string.IsNullOrEmpty(this.gAS.ItemData[i].Items))
						{
							this.DataGridView1.Rows.Add();
							this.DataGridView1.Rows[i].Cells[0].Value = this.gAS.ItemData[i].Items;
							this.DataGridView1.Rows[i].Cells[1].Value = this.gAS.ItemData[i].Values;
						}
					}
				}
			}
		}
		private void DataGridView1CellMouseClick(object sender, DataGridViewCellMouseEventArgs e)
		{
			if (e.ColumnIndex == 1)
			{
				iForm iForm = new ShowTxt();
				if (iForm != null)
				{
					iForm.NeedSave = false;
					iForm.Data = Convert.ToString(this.DataGridView1.Rows[e.RowIndex].Cells[1].Value);
					iForm.SetText();
					iForm.ShowDialog();
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
			this.components = new Container();
			DataGridViewCellStyle dataGridViewCellStyle = new DataGridViewCellStyle();
			DataGridViewCellStyle dataGridViewCellStyle2 = new DataGridViewCellStyle();
			this.label1 = new Label();
			this.textBox1 = new TextBox();
			this.contextMenuStrip1 = new ContextMenuStrip(this.components);
			this.清空ToolStripMenuItem = new ToolStripMenuItem();
			this.label2 = new Label();
			this.button1 = new Button();
			this.splitContainer1 = new SplitContainer();
			this.textBox2 = new TextBox();
			this.DataGridView1 = new DataGridViewEx();
			this.Column1 = new DataGridViewTextBoxColumn();
			this.Column2 = new DataGridViewTextBoxColumn();
			this.contextMenuStrip1.SuspendLayout();
			((ISupportInitialize)this.splitContainer1).BeginInit();
			this.splitContainer1.Panel1.SuspendLayout();
			this.splitContainer1.Panel2.SuspendLayout();
			this.splitContainer1.SuspendLayout();
			((ISupportInitialize)this.DataGridView1).BeginInit();
			base.SuspendLayout();
			this.label1.AutoSize = true;
			this.label1.Location = new Point(13, 13);
			this.label1.Name = "label1";
			this.label1.Size = new Size(41, 12);
			this.label1.TabIndex = 0;
			this.label1.Text = "帧信息";
			this.textBox1.Anchor = (AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right);
			this.textBox1.ContextMenuStrip = this.contextMenuStrip1;
			this.textBox1.Location = new Point(72, 10);
			this.textBox1.Multiline = true;
			this.textBox1.Name = "textBox1";
			this.textBox1.ScrollBars = ScrollBars.Both;
			this.textBox1.Size = new Size(808, 53);
			this.textBox1.TabIndex = 1;
			this.contextMenuStrip1.Items.AddRange(new ToolStripItem[]
			{
				this.清空ToolStripMenuItem
			});
			this.contextMenuStrip1.Name = "contextMenuStrip1";
			this.contextMenuStrip1.Size = new Size(95, 26);
			this.清空ToolStripMenuItem.Name = "清空ToolStripMenuItem";
			this.清空ToolStripMenuItem.Size = new Size(94, 22);
			this.清空ToolStripMenuItem.Text = "清空";
			this.清空ToolStripMenuItem.Click += new EventHandler(this.清空ToolStripMenuItemClick);
			this.label2.AutoSize = true;
			this.label2.Location = new Point(13, 70);
			this.label2.Name = "label2";
			this.label2.Size = new Size(53, 12);
			this.label2.TabIndex = 2;
			this.label2.Text = "详细信息";
			this.button1.Anchor = (AnchorStyles.Top | AnchorStyles.Right);
			this.button1.Location = new Point(886, 10);
			this.button1.Name = "button1";
			this.button1.Size = new Size(58, 39);
			this.button1.TabIndex = 4;
			this.button1.Text = "解析";
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new EventHandler(this.Button1Click);
			this.splitContainer1.Anchor = (AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right);
			this.splitContainer1.Cursor = Cursors.Default;
			this.splitContainer1.Location = new Point(72, 68);
			this.splitContainer1.Name = "splitContainer1";
			this.splitContainer1.Panel1.Controls.Add(this.textBox2);
			this.splitContainer1.Panel1MinSize = 0;
			this.splitContainer1.Panel2.Controls.Add(this.DataGridView1);
			this.splitContainer1.Panel2MinSize = 0;
			this.splitContainer1.Size = new Size(872, 502);
			this.splitContainer1.SplitterDistance = 438;
			this.splitContainer1.SplitterWidth = 3;
			this.splitContainer1.TabIndex = 6;
			this.textBox2.Dock = DockStyle.Fill;
			this.textBox2.Location = new Point(0, 0);
			this.textBox2.Multiline = true;
			this.textBox2.Name = "textBox2";
			this.textBox2.ScrollBars = ScrollBars.Both;
			this.textBox2.Size = new Size(438, 502);
			this.textBox2.TabIndex = 6;
			dataGridViewCellStyle.BackColor = Color.FromArgb(240, 240, 240);
			this.DataGridView1.AlternatingRowsDefaultCellStyle = dataGridViewCellStyle;
			this.DataGridView1.BackgroundColor = Color.White;
			
			this.DataGridView1.ColumnHeaderColor = SystemColors.Control;
			dataGridViewCellStyle2.Alignment = DataGridViewContentAlignment.MiddleCenter;
			dataGridViewCellStyle2.BackColor = SystemColors.Control;
			dataGridViewCellStyle2.Font = new Font("宋体", 9f, FontStyle.Regular, GraphicsUnit.Point, 134);
			dataGridViewCellStyle2.ForeColor = SystemColors.WindowText;
			dataGridViewCellStyle2.SelectionBackColor = SystemColors.Highlight;
			dataGridViewCellStyle2.SelectionForeColor = SystemColors.HighlightText;
			dataGridViewCellStyle2.WrapMode = DataGridViewTriState.True;
			this.DataGridView1.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle2;
			this.DataGridView1.ColumnHeadersHeight = 28;
			this.DataGridView1.Columns.AddRange(new DataGridViewColumn[]
			{
				this.Column1,
				this.Column2
			});
			this.DataGridView1.Dock = DockStyle.Fill;
			this.DataGridView1.GridColor = SystemColors.ActiveBorder;
			this.DataGridView1.Location = new Point(0, 0);
			this.DataGridView1.MultiSelect = false;
			this.DataGridView1.Name = "DataGridView1";
			this.DataGridView1.RowHeaderColor = SystemColors.Control;
			this.DataGridView1.RowTemplate.Height = 23;
			this.DataGridView1.SelectionMode = DataGridViewSelectionMode.CellSelect;
			this.DataGridView1.Size = new Size(431, 502);
			this.DataGridView1.TabIndex = 7;
			this.Column1.HeaderText = "字段名";
			this.Column1.Name = "Column1";
			this.Column1.ReadOnly = true;
			this.Column1.Width = 250;
			this.Column2.HeaderText = "内容";
			this.Column2.Name = "Column2";
			this.Column2.ReadOnly = true;
			this.Column2.Width = 200;
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			this.BackColor = Color.FromArgb(239, 237, 226);
			base.ClientSize = new Size(950, 575);
			base.Controls.Add(this.splitContainer1);
			base.Controls.Add(this.button1);
			base.Controls.Add(this.label2);
			base.Controls.Add(this.textBox1);
			base.Controls.Add(this.label1);
			this.Font = new Font("宋体", 9f, FontStyle.Regular, GraphicsUnit.Point, 134);
			base.Name = "FrameParse";
			//base.StartPosition = FormStartPosition.CenterScreen;
			this.Text = "报文解析";
			this.contextMenuStrip1.ResumeLayout(false);
			this.splitContainer1.Panel1.ResumeLayout(false);
			this.splitContainer1.Panel1.PerformLayout();
			this.splitContainer1.Panel2.ResumeLayout(false);
			((ISupportInitialize)this.splitContainer1).EndInit();
			this.splitContainer1.ResumeLayout(false);
			((ISupportInitialize)this.DataGridView1).EndInit();
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}


