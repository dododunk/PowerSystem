using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms.VisualStyles;
namespace System.Windows.Forms
{
	public class IPTextBox : UserControl
	{
		private Color _backColor;
		private Color _borderColor = Color.FromArgb(0, 60, 116);
		private InputType _inputType;
		private Color _orgColor;
		private bool _showErrorFlag;
		private string _text = "";
		private HorizontalAlignment _textAlign = HorizontalAlignment.Center;
		private IContainer components;
		private ContextMenuStrip contextMenuStrip1;
		private ErrorProvider errVerify;
		private Label label1;
		private Label label2;
		private Label label3;
		private ToolStripMenuItem mnuCopy;
		private ToolStripMenuItem mnuDelete;
		private ToolStripMenuItem mnuPaste;
		private ToolStripMenuItem mnuSelectAll;
		private Panel panel1;
		private TextBox textBox1;
		private TextBox textBox2;
		private TextBox textBox3;
		private TextBox textBox4;
		private ToolStripSeparator toolStripSeparator1;
		[DefaultValue(typeof(Color), "Window")]
		public override Color BackColor
		{
			get
			{
				return this._backColor;
			}
			set
			{
				this._backColor = value;
				base.BackColor = value;
				this.SetBackColor(this._backColor);
			}
		}
		[DefaultValue(typeof(Color), "0, 60, 116"), Description("获取或设置边框颜色")]
		public Color BorderColor
		{
			get
			{
				return this._borderColor;
			}
			set
			{
				this._borderColor = value;
				base.Invalidate();
			}
		}
		[DefaultValue(typeof(InputType), "IPAddress"), Description("选择输入的类型")]
		public InputType InputType
		{
			get
			{
				return this._inputType;
			}
			set
			{
				this._inputType = value;
			}
		}
		[Browsable(false)]
		public bool IsValidate
		{
			get
			{
				return this.isValidateValue();
			}
		}
		[DefaultValue(false), Description("获取或设置是否显示出错标志")]
		public bool ShowErrorFlag
		{
			get
			{
				return this._showErrorFlag;
			}
			set
			{
				this._showErrorFlag = value;
			}
		}
		[DefaultValue(typeof(HorizontalAlignment), "Center"), Description("获取或设置文本的对齐方式")]
		public HorizontalAlignment TextAlign
		{
			get
			{
				return this._textAlign;
			}
			set
			{
				this._textAlign = value;
				if (this._textAlign == HorizontalAlignment.Left)
				{
					this.panel1.Dock = DockStyle.Left;
				}
				else
				{
					if (this._textAlign == HorizontalAlignment.Right)
					{
						this.panel1.Dock = DockStyle.Right;
					}
					else
					{
						this.panel1.Dock = DockStyle.None;
						this.SetCenter();
					}
				}
				this.Refresh();
			}
		}
		[Browsable(true), DefaultValue(""), Description("IP 地址的值")]
		public string Value
		{
			get
			{
				string text;
				if (this.textBox1.Text == "" || this.textBox2.Text == "" || this.textBox3.Text == "" || this.textBox4.Text == "")
				{
					this._text = "";
					text = this._text;
				}
				else
				{
					this._text = string.Concat(new string[]
					{
						Convert.ToInt32(this.textBox1.Text).ToString(),
						".",
						Convert.ToInt32(this.textBox2.Text).ToString(),
						".",
						Convert.ToInt32(this.textBox3.Text).ToString(),
						".",
						Convert.ToInt32(this.textBox4.Text).ToString()
					});
					text = this._text;
				}
				return text;
			}
			set
			{
				this._text = value;
				if (this._text != null && this._text != "")
				{
					string[] array = value.Split(new char[]
					{
						'.'
					});
					if (array.Length < 4 && this._showErrorFlag)
					{
						this.errVerify.SetError(this, "指定了一个无效的 IP 地址!");
					}
					this.SetTextBox(array);
				}
				else
				{
					this._text = "";
					this.SetIPEmptyValue();
				}
			}
		}
		public IPTextBox()
		{
			this.InitializeComponent();
			this.BackColor = SystemColors.Window;
			this._orgColor = this.BackColor;
		}
		private void contextMenuStrip1_Opening(object sender, CancelEventArgs e)
		{
			TextBox textBox = (sender as ContextMenuStrip).SourceControl as TextBox;
			this.mnuCopy.Enabled = (this.mnuDelete.Enabled = (textBox.SelectionLength > 0));
			this.mnuSelectAll.Enabled = (textBox.TextLength > 0);
			this.mnuPaste.Enabled = Clipboard.ContainsText(TextDataFormat.Text);
		}
		protected override void Dispose(bool disposing)
		{
			if (disposing && this.components != null)
			{
				this.components.Dispose();
			}
			base.Dispose(disposing);
		}
		private void InitializeComponent()
		{
			this.components = new Container();
			this.panel1 = new Panel();
			this.textBox4 = new TextBox();
			this.contextMenuStrip1 = new ContextMenuStrip(this.components);
			this.mnuCopy = new ToolStripMenuItem();
			this.mnuPaste = new ToolStripMenuItem();
			this.mnuDelete = new ToolStripMenuItem();
			this.toolStripSeparator1 = new ToolStripSeparator();
			this.mnuSelectAll = new ToolStripMenuItem();
			this.label3 = new Label();
			this.textBox3 = new TextBox();
			this.label2 = new Label();
			this.textBox2 = new TextBox();
			this.label1 = new Label();
			this.textBox1 = new TextBox();
			this.errVerify = new ErrorProvider(this.components);
			this.panel1.SuspendLayout();
			this.contextMenuStrip1.SuspendLayout();
			((ISupportInitialize)this.errVerify).BeginInit();
			base.SuspendLayout();
			this.panel1.Controls.Add(this.textBox4);
			this.panel1.Controls.Add(this.label3);
			this.panel1.Controls.Add(this.textBox3);
			this.panel1.Controls.Add(this.label2);
			this.panel1.Controls.Add(this.textBox2);
			this.panel1.Controls.Add(this.label1);
			this.panel1.Controls.Add(this.textBox1);
			this.panel1.Location = new Point(1, 1);
			this.panel1.Name = "panel1";
			this.panel1.Size = new Size(137, 17);
			this.panel1.TabIndex = 1;
			this.textBox4.BorderStyle = BorderStyle.None;
			this.textBox4.ContextMenuStrip = this.contextMenuStrip1;
			this.textBox4.ImeMode = ImeMode.Disable;
			this.textBox4.Location = new Point(112, 3);
			this.textBox4.MaxLength = 3;
			this.textBox4.Name = "textBox4";
			this.textBox4.ShortcutsEnabled = false;
			this.textBox4.Size = new Size(20, 14);
			this.textBox4.TabIndex = 3;
			this.textBox4.TextAlign = HorizontalAlignment.Center;
			this.textBox4.KeyPress += new KeyPressEventHandler(this.textBox4_KeyPress);
			this.contextMenuStrip1.Items.AddRange(new ToolStripItem[]
			{
				this.mnuCopy,
				this.mnuPaste,
				this.mnuDelete,
				this.toolStripSeparator1,
				this.mnuSelectAll
			});
			this.contextMenuStrip1.Name = "contextMenuStrip1";
			this.contextMenuStrip1.Size = new Size(101, 98);
			this.contextMenuStrip1.Opening += new CancelEventHandler(this.contextMenuStrip1_Opening);
			this.mnuCopy.Name = "mnuCopy";
			this.mnuCopy.ShowShortcutKeys = false;
			this.mnuCopy.Size = new Size(75, 22);
			this.mnuCopy.Text = "复制";
			this.mnuCopy.Click += new EventHandler(this.mnuCopy_Click);
			this.mnuPaste.Name = "mnuPaste";
			this.mnuPaste.Size = new Size(75, 22);
			this.mnuPaste.Text = "粘贴";
			this.mnuPaste.Click += new EventHandler(this.mnuPaste_Click);
			this.mnuDelete.Name = "mnuDelete";
			this.mnuDelete.Size = new Size(75, 22);
			this.mnuDelete.Text = "删除";
			this.mnuDelete.Click += new EventHandler(this.mnuDelete_Click);
			this.toolStripSeparator1.Name = "toolStripSeparator1";
			this.toolStripSeparator1.Size = new Size(72, 6);
			this.mnuSelectAll.Name = "mnuSelectAll";
			this.mnuSelectAll.Size = new Size(75, 22);
			this.mnuSelectAll.Text = "全选";
			this.mnuSelectAll.Click += new EventHandler(this.mnuSelectAll_Click);
			this.label3.BackColor = SystemColors.Window;
			this.label3.Font = new Font("宋体", 9f, FontStyle.Bold, GraphicsUnit.Point, 134);
			this.label3.Location = new Point(29, 3);
			this.label3.Name = "label3";
			this.label3.Size = new Size(8, 14);
			this.label3.TabIndex = 1;
			this.label3.Text = ".";
			this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			this.textBox3.BorderStyle = BorderStyle.None;
			this.textBox3.ContextMenuStrip = this.contextMenuStrip1;
			this.textBox3.ImeMode = ImeMode.Disable;
			this.textBox3.Location = new Point(77, 3);
			this.textBox3.MaxLength = 3;
			this.textBox3.Name = "textBox3";
			this.textBox3.ShortcutsEnabled = false;
			this.textBox3.Size = new Size(20, 14);
			this.textBox3.TabIndex = 2;
			this.textBox3.TextAlign = HorizontalAlignment.Center;
			this.textBox3.KeyPress += new KeyPressEventHandler(this.textBox3_KeyPress);
			this.label2.BackColor = SystemColors.Window;
			this.label2.Font = new Font("宋体", 9f, FontStyle.Bold, GraphicsUnit.Point, 134);
			this.label2.Location = new Point(65, 3);
			this.label2.Name = "label2";
			this.label2.Size = new Size(8, 14);
			this.label2.TabIndex = 2;
			this.label2.Text = ".";
			this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			this.textBox2.BorderStyle = BorderStyle.None;
			this.textBox2.ContextMenuStrip = this.contextMenuStrip1;
			this.textBox2.ImeMode = ImeMode.Disable;
			this.textBox2.Location = new Point(41, 3);
			this.textBox2.MaxLength = 3;
			this.textBox2.Name = "textBox2";
			this.textBox2.ShortcutsEnabled = false;
			this.textBox2.Size = new Size(20, 14);
			this.textBox2.TabIndex = 1;
			this.textBox2.TextAlign = HorizontalAlignment.Center;
			this.textBox2.KeyPress += new KeyPressEventHandler(this.textBox2_KeyPress);
			this.label1.BackColor = SystemColors.Window;
			this.label1.Font = new Font("宋体", 9f, FontStyle.Bold, GraphicsUnit.Point, 134);
			this.label1.Location = new Point(101, 3);
			this.label1.Name = "label1";
			this.label1.Size = new Size(8, 14);
			this.label1.TabIndex = 3;
			this.label1.Text = ".";
			this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			this.textBox1.BorderStyle = BorderStyle.None;
			this.textBox1.ContextMenuStrip = this.contextMenuStrip1;
			this.textBox1.ImeMode = ImeMode.Disable;
			this.textBox1.Location = new Point(5, 3);
			this.textBox1.MaxLength = 3;
			this.textBox1.Name = "textBox1";
			this.textBox1.ShortcutsEnabled = false;
			this.textBox1.Size = new Size(20, 14);
			this.textBox1.TabIndex = 0;
			this.textBox1.TextAlign = HorizontalAlignment.Center;
			this.textBox1.KeyPress += new KeyPressEventHandler(this.textBox1_KeyPress);
			this.textBox1.Validating += new CancelEventHandler(this.textBox1_Validating);
			this.errVerify.ContainerControl = this;
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			base.AutoScaleMode = AutoScaleMode.Font;
			this.BackColor = Color.White;
			base.Controls.Add(this.panel1);
			this.MaximumSize = new Size(150, 24);
			this.MinimumSize = new Size(140, 21);
			base.Name = "IPTextBox";
			base.Padding = new Padding(1);
			base.Size = new Size(140, 21);
			base.Validated += new EventHandler(this.IPBox_Validated);
			this.panel1.ResumeLayout(false);
			this.panel1.PerformLayout();
			this.contextMenuStrip1.ResumeLayout(false);
			((ISupportInitialize)this.errVerify).EndInit();
			base.ResumeLayout(false);
		}
		private void IPBox_Validated(object sender, EventArgs e)
		{
			this.errVerify.SetError(this, "");
		}
		private static bool IsNumeric(string str)
		{
			bool result;
			for (int i = 0; i < str.Length; i++)
			{
				char c = str[i];
				if (!char.IsDigit(c))
				{
					result = false;
					return result;
				}
			}
			result = true;
			return result;
		}
		private bool isValidateValue()
		{
			bool flag = true;
			bool result;
			if (this.textBox1.Text.Trim() == "" || this.textBox2.Text.Trim() == "" || this.textBox3.Text.Trim() == "" || this.textBox4.Text.Trim() == "")
			{
				result = false;
			}
			else
			{
				int num = int.Parse(this.textBox1.Text.Trim());
				if (this._inputType == InputType.IPAddress)
				{
					if (num < 1 || num > 233)
					{
						flag = false;
					}
				}
				else
				{
					if (num < 1 || num > 233)
					{
						flag = false;
					}
				}
				if (flag)
				{
					flag = this.VerifyForIP(this.textBox2);
				}
				if (flag)
				{
					flag = this.VerifyForIP(this.textBox3);
				}
				if (flag)
				{
					flag = this.VerifyForIP(this.textBox4);
				}
				result = flag;
			}
			return result;
		}
		private void MaskIpAddr(TextBox textBox, KeyPressEventArgs e)
		{
			int length = textBox.Text.Length;
			this.errVerify.SetError(this, "");
			if (char.IsDigit(e.KeyChar) || e.KeyChar == '.' || e.KeyChar == '\b')
			{
				if (e.KeyChar == '\b')
				{
					if (textBox.Name == "textBox1")
					{
						bool flag = textBox.Text == "";
					}
					if (textBox.Name == "textBox2" && textBox.Text == "")
					{
						this.textBox1.Focus();
						this.textBox1.SelectionStart = this.textBox1.Text.Length;
					}
					if (textBox.Name == "textBox3" && textBox.Text == "")
					{
						this.textBox2.Focus();
						this.textBox2.SelectionStart = this.textBox2.Text.Length;
					}
					if (textBox.Name == "textBox4" && textBox.Text == "")
					{
						this.textBox3.Focus();
						this.textBox3.SelectionStart = this.textBox3.Text.Length;
					}
					e.Handled = false;
				}
				else
				{
					if (length == 2 && e.KeyChar != '.')
					{
						int num = 255;
						if (this._inputType == InputType.Gateway)
						{
							num = 255;
						}
						string text = textBox.Text + e.KeyChar;
						if (textBox.Name == "textBox1")
						{
							if (int.Parse(text) > num)
							{
								textBox.Text = num.ToString();
								textBox.Focus();
								if (this._showErrorFlag)
								{
									this.errVerify.SetError(this, "请指定一个介于 1 和 255 之间的数值。");
								}
								else
								{
									MessageBox.Show(text + " 不是一个有效项目。请指定一个介于 1 和 255 之间的数值。", "出错", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
								}
								e.Handled = true;
								return;
							}
							this.textBox2.Focus();
							this.textBox2.SelectAll();
						}
						else
						{
							if (textBox.Name == "textBox2")
							{
								if (int.Parse(text) > 255)
								{
									textBox.Text = "255";
									textBox.Focus();
									if (this._showErrorFlag)
									{
										this.errVerify.SetError(this, "请指定一个介于 1 和 255 之间的数值。");
									}
									else
									{
										MessageBox.Show(text + " 不是一个有效项目。请指定一个介于 1 和 255 之间的数值。", "出错", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
									}
									e.Handled = true;
									return;
								}
								this.textBox3.Focus();
								this.textBox3.SelectAll();
							}
							else
							{
								if (textBox.Name == "textBox3")
								{
									if (int.Parse(text) > 255)
									{
										textBox.Text = "255";
										textBox.Focus();
										if (this._showErrorFlag)
										{
											this.errVerify.SetError(this, "请指定一个介于 1 和 255 之间的数值。");
										}
										else
										{
											MessageBox.Show(text + " 不是一个有效项目。请指定一个介于 1 和 255 之间的数值。", "出错", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
										}
										e.Handled = true;
										return;
									}
									this.textBox4.Focus();
									this.textBox4.SelectAll();
								}
								else
								{
									if (textBox.Name == "textBox4" && int.Parse(text) > 255)
									{
										textBox.Text = "255";
										textBox.Focus();
										if (this._showErrorFlag)
										{
											this.errVerify.SetError(this, "请指定一个介于 1 和 255 之间的数值。");
										}
										else
										{
											MessageBox.Show(text + " 不是一个有效项目。请指定一个介于 1 和 255 之间的数值。", "出错", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
										}
										e.Handled = true;
										return;
									}
								}
							}
						}
					}
					if (e.KeyChar == '.')
					{
						if (textBox.Name == "textBox1" && textBox.Text != "")
						{
							this.textBox2.Focus();
							this.textBox2.SelectAll();
						}
						if (textBox.Name == "textBox2" && textBox.Text != "")
						{
							this.textBox3.Focus();
							this.textBox3.SelectAll();
						}
						if (textBox.Name == "textBox3" && textBox.Text != "")
						{
							this.textBox4.Focus();
							this.textBox4.SelectAll();
						}
						if (textBox.Name == "textBox4")
						{
							bool flag2 = textBox.Text != "";
						}
						e.Handled = true;
					}
				}
			}
			else
			{
				e.Handled = true;
			}
		}
		private void mnuCopy_Click(object sender, EventArgs e)
		{
			Clipboard.SetText((((sender as ToolStripMenuItem).Owner as ContextMenuStrip).SourceControl as TextBox).SelectedText);
		}
		private void mnuDelete_Click(object sender, EventArgs e)
		{
			(((sender as ToolStripMenuItem).Owner as ContextMenuStrip).SourceControl as TextBox).SelectedText = "";
		}
		private void mnuPaste_Click(object sender, EventArgs e)
		{
			string text = Clipboard.GetText(TextDataFormat.Text);
			if (IPTextBox.IsNumeric(text))
			{
				if (int.Parse(text) > 255)
				{
					if (this._showErrorFlag)
					{
						this.errVerify.SetError(this, "你正试图粘贴错误格式的IP地址！");
					}
					else
					{
						MessageBox.Show("你正试图粘贴错误格式的IP地址！", "错误", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
					}
				}
				else
				{
					TextBox textBox = ((sender as ToolStripMenuItem).Owner as ContextMenuStrip).SourceControl as TextBox;
					int num = 255;
					if (this._inputType == InputType.Gateway)
					{
						num = 255;
					}
					if (textBox.Name == "textBox1")
					{
						if (int.Parse(text) > num)
						{
							textBox.Text = num.ToString();
							textBox.Focus();
							if (this._showErrorFlag)
							{
								this.errVerify.SetError(this, "请指定一个介于 1 和 255 之间的数值。");
							}
							else
							{
								MessageBox.Show(text + " 不是一个有效项目。请指定一个介于 1 和 255 之间的数值。", "出错", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
							}
						}
						else
						{
							textBox.Text = text;
							this.textBox2.Focus();
							this.textBox2.SelectAll();
						}
					}
					else
					{
						if (textBox.Name == "textBox2")
						{
							if (int.Parse(text) > 255)
							{
								textBox.Text = "255";
								textBox.Focus();
								if (this._showErrorFlag)
								{
									this.errVerify.SetError(this, "请指定一个介于 1 和 255 之间的数值。");
								}
								else
								{
									MessageBox.Show(text + " 不是一个有效项目。请指定一个介于 1 和 255 之间的数值。", "出错", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
								}
							}
							else
							{
								textBox.Text = text;
								this.textBox3.Focus();
								this.textBox3.SelectAll();
							}
						}
						else
						{
							if (textBox.Name == "textBox3")
							{
								if (int.Parse(text) > 255)
								{
									textBox.Text = "255";
									textBox.Focus();
									if (this._showErrorFlag)
									{
										this.errVerify.SetError(this, "请指定一个介于 1 和 255 之间的数值。");
									}
									else
									{
										MessageBox.Show(text + " 不是一个有效项目。请指定一个介于 1 和 255 之间的数值。", "出错", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
									}
								}
								else
								{
									textBox.Text = text;
									this.textBox4.Focus();
									this.textBox4.SelectAll();
								}
							}
							else
							{
								if (textBox.Name == "textBox4")
								{
									if (int.Parse(text) > 255)
									{
										textBox.Text = "255";
										textBox.Focus();
										if (this._showErrorFlag)
										{
											this.errVerify.SetError(this, "请指定一个介于 1 和 255 之间的数值。");
										}
										else
										{
											MessageBox.Show(text + " 不是一个有效项目。请指定一个介于 1 和 255 之间的数值。", "出错", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
										}
									}
									else
									{
										textBox.Text = text;
									}
								}
							}
						}
					}
				}
			}
			else
			{
				if (this._showErrorFlag)
				{
					this.errVerify.SetError(this, "你正试图粘贴错误格式的IP地址！");
				}
				else
				{
					MessageBox.Show("你正试图粘贴错误格式的IP地址！", "错误", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
				}
			}
		}
		private void mnuSelectAll_Click(object sender, EventArgs e)
		{
			(((sender as ToolStripMenuItem).Owner as ContextMenuStrip).SourceControl as TextBox).SelectAll();
		}
		protected override void OnEnabledChanged(EventArgs e)
		{
			if (!base.DesignMode)
			{
				if (base.Enabled)
				{
					this.BackColor = this._orgColor;
				}
				else
				{
					this._orgColor = this.BackColor;
					this.BackColor = SystemColors.Control;
				}
			}
			base.OnEnabledChanged(e);
		}
		protected override void OnPaint(PaintEventArgs e)
		{
			base.OnPaintBackground(e);
			checked
			{
				if (base.BorderStyle == BorderStyle.FixedSingle)
				{
					ControlPaint.DrawBorder(e.Graphics, new Rectangle(0, 0, base.ClientRectangle.Width - 1, base.ClientRectangle.Height - 1), this._borderColor, ButtonBorderStyle.Solid);
				}
				else
				{
					if (VisualStyleRenderer.IsSupported && Application.RenderWithVisualStyles)
					{
						ControlPaint.DrawVisualStyleBorder(e.Graphics, new Rectangle(0, 0, base.ClientRectangle.Width - 1, base.ClientRectangle.Height - 1));
					}
					else
					{
						ControlPaint.DrawBorder3D(e.Graphics, new Rectangle(0, 0, base.ClientRectangle.Width - 1, base.ClientRectangle.Height - 1), Border3DStyle.Sunken);
					}
				}
			}
		}
		protected override void OnResize(EventArgs e)
		{
			if (base.Width < 140)
			{
				base.Width = 140;
			}
			base.Height = 21;
			base.OnResize(e);
			this.SetCenter();
			base.Invalidate();
		}
		protected override void OnValidating(CancelEventArgs e)
		{
			if (this._showErrorFlag)
			{
				if (this.isValidateValue())
				{
					this.errVerify.SetError(this, "");
				}
				else
				{
					this.errVerify.SetError(this, "无效的 IP 地址。");
				}
			}
			base.OnValidating(e);
		}
		private void SetBackColor(Color color)
		{
			this.panel1.BackColor = color;
			this.textBox1.BackColor = color;
			this.label1.BackColor = color;
			this.textBox2.BackColor = color;
			this.label2.BackColor = color;
			this.textBox3.BackColor = color;
			this.label3.BackColor = color;
			this.textBox4.BackColor = color;
		}
		private void SetCenter()
		{
			int num = checked(base.Width - this.panel1.Width - base.Padding.Left - base.Padding.Right) / 2;
			int num2 = 1;
			if (!VisualStyleRenderer.IsSupported || !Application.RenderWithVisualStyles)
			{
				num2 = 2;
			}
			if (num < num2)
			{
				num = num2;
			}
			this.panel1.Left = num;
			this.panel1.Top = num2;
		}
		private void SetIPEmptyValue()
		{
			this.textBox1.Text = "";
			this.textBox2.Text = "";
			this.textBox3.Text = "";
			this.textBox4.Text = "";
		}
		private void SetTextBox(string[] nums)
		{
			checked
			{
				for (int i = 0; i < nums.Length; i++)
				{
					string text = nums[i];
					if (IPTextBox.IsNumeric(text))
					{
						int num = int.Parse(text);
						if (i == 0)
						{
							if (this._inputType == InputType.IPAddress)
							{
								if (num < 1 && num > 233 && this._showErrorFlag)
								{
									this.errVerify.SetError(this, "无效的 IP 地址。");
								}
							}
							else
							{
								if (num < 0 && num > 255 && this._showErrorFlag)
								{
									this.errVerify.SetError(this, "无效的 IP 地址。");
								}
							}
							this.textBox1.Text = num.ToString();
						}
						if (i > 0)
						{
							if (num < 0 && num > 255 && this._showErrorFlag)
							{
								this.errVerify.SetError(this, "无效的 IP 地址。");
							}
							switch (i)
							{
							case 1:
								this.textBox2.Text = num.ToString();
								break;

							case 2:
								this.textBox3.Text = num.ToString();
								break;

							default:
								this.textBox4.Text = num.ToString();
								break;
							}
						}
					}
				}
			}
		}
		private void textBox1_KeyPress(object sender, KeyPressEventArgs e)
		{
			this.MaskIpAddr(this.textBox1, e);
		}
		private void textBox1_Validating(object sender, CancelEventArgs e)
		{
			string text = this.textBox1.Text;
			if (this._inputType == InputType.IPAddress && text.Trim() != "" && text == "0")
			{
				string text2 = "0 不是一个有效项目。请指定一个介于 1 和 223 之间的数值。";
				if (this._showErrorFlag)
				{
					this.errVerify.SetError(this, text2);
				}
				else
				{
					MessageBox.Show(text2, "错误", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
				}
				this.textBox1.Text = "1";
			}
		}
		private void textBox2_KeyPress(object sender, KeyPressEventArgs e)
		{
			this.MaskIpAddr(this.textBox2, e);
		}
		private void textBox3_KeyPress(object sender, KeyPressEventArgs e)
		{
			this.MaskIpAddr(this.textBox3, e);
		}
		private void textBox4_KeyPress(object sender, KeyPressEventArgs e)
		{
			this.MaskIpAddr(this.textBox4, e);
		}
		private bool VerifyForIP(TextBox box)
		{
			bool flag = true;
			int num = int.Parse(box.Text.Trim());
			return num >= 0 && num <= 255 && flag;
		}
	}
}
