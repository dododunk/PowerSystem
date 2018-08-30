using GB698Cls;
//using Prot645;
using System;
using System.ComponentModel;
using System.Data.OleDb;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Ctl
{
	public class DLT645Prot : iForm
	{
		//private Out giP = new Out();
		private string Path;
		private OleDbConnection myConn;
		private iSearch isearch;
		private DLT645 dlt645 = new DLT645();
		private DLT698Opera dlt = new DLT698Opera();
		private PubFunction pf = new PubFunction();
		private string gy_lb;
		private string gy_bz;
		private string gy_gs;
		private string gy_zjs;
		private string gy_sjbm;
		private string gy_knr;
		private IContainer components = null;
		private RadioButton radioButton4;
		private RadioButton radioButton3;
		private Button button1;
		private TextBox textBox1;
		private CheckBox checkBox1;
		private Label label3;
		private ComboBox comboBox3;
		private ComboBox comboBox4;
		private ListView listView1;
		public DLT645Prot()
		{
			this.InitializeComponent();
			this.Path = Program.SysPath;
			//this.giP.OutPut(this.Path);
			this.InitSys();
			this.LoadType();
			this.isearch = new iSearch(this.Path);
			this.isearch.myConn = this.myConn;
			this.isearch.iListView = this.listView1;
			this.isearch.InitListView();
		}
		private void InitSys()
		{
			try
			{
				string connectionString = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + this.Path + "Prot645.mdb;User Id=admin;Password=;";
				this.myConn = new OleDbConnection(connectionString);
				this.myConn.Open();
			}
			catch
			{
			}
		}
		private void LoadType()
		{
			this.comboBox3.Items.Clear();
			string cmdText = "select DISTINCT(大类) from 规约";
			OleDbCommand oleDbCommand = new OleDbCommand(cmdText, this.myConn);
			OleDbDataReader oleDbDataReader = oleDbCommand.ExecuteReader();
			while (oleDbDataReader.Read())
			{
				this.comboBox3.Items.Add(oleDbDataReader["大类"].ToString());
			}
			oleDbDataReader.Close();
		}
		private void LoadSubType(string dalei)
		{
			this.comboBox4.Items.Clear();
			string cmdText = "select DISTINCT(中类) from 规约 where 大类='" + dalei + "'";
			OleDbCommand oleDbCommand = new OleDbCommand(cmdText, this.myConn);
			OleDbDataReader oleDbDataReader = oleDbCommand.ExecuteReader();
			while (oleDbDataReader.Read())
			{
				this.comboBox4.Items.Add(oleDbDataReader["中类"].ToString());
			}
			oleDbDataReader.Close();
		}
		private void ComboBox3SelectedIndexChanged(object sender, EventArgs e)
		{
			this.LoadSubType(this.comboBox3.Text);
		}
		private void ComboBox4SelectedIndexChanged(object sender, EventArgs e)
		{
			this.isearch.SearhData(this.comboBox3.Text, this.comboBox4.Text);
		}
		private void Button1Click(object sender, EventArgs e)
		{
			string dalei = string.Empty;
			string empty = string.Empty;
			if (this.checkBox1.Checked)
			{
				dalei = this.comboBox3.Text;
			}
			else
			{
				dalei = "";
			}
			if (this.radioButton4.Checked)
			{
				this.isearch.SearhData(dalei, true, this.textBox1.Text.Trim());
			}
			else
			{
				this.isearch.SearhData(dalei, false, this.textBox1.Text.Trim());
			}
		}
		protected override void GetText()
		{
			try
			{
				this.gy_lb = this.listView1.SelectedItems[0].Text;
				this.gy_bz = this.listView1.SelectedItems[0].SubItems[2].Text;
				this.gy_gs = this.listView1.SelectedItems[0].SubItems[3].Text;
				this.gy_zjs = this.listView1.SelectedItems[0].SubItems[4].Text;
				this.gy_sjbm = this.listView1.SelectedItems[0].SubItems[5].Text;
				this.gy_knr = this.listView1.SelectedItems[0].SubItems[6].Text;
			}
			catch
			{
			}
			this.Data = "";
			this.Data += this.gy_bz;
			this.Data += "?";
			this.Data += this.gy_gs;
			this.Data += "?";
			this.Data += this.gy_zjs;
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
			ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof(DLT645Prot));
			this.listView1 = new ListView();
			this.comboBox4 = new ComboBox();
			this.comboBox3 = new ComboBox();
			this.label3 = new Label();
			this.checkBox1 = new CheckBox();
			this.textBox1 = new TextBox();
			this.button1 = new Button();
			this.radioButton3 = new RadioButton();
			this.radioButton4 = new RadioButton();
			base.SuspendLayout();
			this.listView1.Activation = ItemActivation.OneClick;
			this.listView1.Dock = DockStyle.Bottom;
			this.listView1.FullRowSelect = true;
			this.listView1.GridLines = true;
			this.listView1.HideSelection = false;
			this.listView1.Location = new Point(0, 34);
			this.listView1.MultiSelect = false;
			this.listView1.Name = "listView1";
			this.listView1.Size = new Size(749, 378);
			this.listView1.TabIndex = 133;
			this.listView1.UseCompatibleStateImageBehavior = false;
			this.comboBox4.FormattingEnabled = true;
			this.comboBox4.Location = new Point(205, 7);
			this.comboBox4.Name = "comboBox4";
			this.comboBox4.Size = new Size(169, 20);
			this.comboBox4.TabIndex = 131;
			this.comboBox4.SelectedIndexChanged += new EventHandler(this.ComboBox4SelectedIndexChanged);
			this.comboBox3.FormattingEnabled = true;
			this.comboBox3.Location = new Point(62, 7);
			this.comboBox3.Name = "comboBox3";
			this.comboBox3.Size = new Size(96, 20);
			this.comboBox3.TabIndex = 129;
			this.comboBox3.SelectedIndexChanged += new EventHandler(this.ComboBox3SelectedIndexChanged);
			this.label3.AutoSize = true;
			this.label3.Location = new Point(168, 11);
			this.label3.Name = "label3";
			this.label3.Size = new Size(35, 12);
			this.label3.TabIndex = 132;
			this.label3.Text = "子类:";
			this.checkBox1.AutoSize = true;
			this.checkBox1.Checked = true;
			this.checkBox1.CheckState = CheckState.Checked;
			this.checkBox1.Location = new Point(9, 9);
			this.checkBox1.Name = "checkBox1";
			this.checkBox1.Size = new Size(54, 16);
			this.checkBox1.TabIndex = 130;
			this.checkBox1.Text = "大类:";
			this.checkBox1.UseVisualStyleBackColor = true;
			this.textBox1.Location = new Point(541, 7);
			this.textBox1.Name = "textBox1";
			this.textBox1.Size = new Size(174, 21);
			this.textBox1.TabIndex = 125;
			this.button1.Image = (Image)componentResourceManager.GetObject("button1.Image");
			
			this.button1.Location = new Point(716, 6);
			this.button1.Name = "button1";
			this.button1.Size = new Size(24, 23);
			this.button1.TabIndex = 128;
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new EventHandler(this.Button1Click);
			this.radioButton3.AutoSize = true;
			this.radioButton3.ImeMode = ImeMode.NoControl;
			this.radioButton3.Location = new Point(467, 10);
			this.radioButton3.Name = "radioButton3";
			this.radioButton3.Size = new Size(71, 16);
			this.radioButton3.TabIndex = 127;
			this.radioButton3.Text = "字段名称";
			this.radioButton3.UseVisualStyleBackColor = true;
			this.radioButton4.AutoSize = true;
			this.radioButton4.Checked = true;
			this.radioButton4.ImeMode = ImeMode.NoControl;
			this.radioButton4.Location = new Point(390, 10);
			this.radioButton4.Name = "radioButton4";
			this.radioButton4.Size = new Size(71, 16);
			this.radioButton4.TabIndex = 126;
			this.radioButton4.TabStop = true;
			this.radioButton4.Text = "标识编码";
			this.radioButton4.UseVisualStyleBackColor = true;
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			this.BackColor = Color.FromArgb(239, 237, 226);
			base.ClientSize = new Size(749, 412);
			base.Controls.Add(this.listView1);
			base.Controls.Add(this.comboBox4);
			base.Controls.Add(this.comboBox3);
			base.Controls.Add(this.label3);
			base.Controls.Add(this.checkBox1);
			base.Controls.Add(this.textBox1);
			base.Controls.Add(this.button1);
			base.Controls.Add(this.radioButton3);
			base.Controls.Add(this.radioButton4);
			base.Name = "DLT645Prot";
			this.Text = "DLT645规约";
			base.ResumeLayout(false);
			base.PerformLayout();
		}
	}
}
