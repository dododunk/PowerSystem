using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
namespace GB698Ctl
{
	public class mForm : Form
	{
		public bool IsCustomize;
		public string CustomizeItems = string.Empty;
		private string _A1;
		private string _A2;
		private string _TName;
		private string _Mode;
		private IContainer components = null;
		public string A1
		{
			get
			{
				return this._A1;
			}
			set
			{
				this._A1 = value;
			}
		}
		public string A2
		{
			get
			{
				return this._A2;
			}
			set
			{
				this._A2 = value;
			}
		}
		public string TName
		{
			get
			{
				return this._TName;
			}
			set
			{
				this._TName = value;
			}
		}
		public string Mode
		{
			get
			{
				return this._Mode;
			}
			set
			{
				this._Mode = value;
			}
		}
		public mForm()
		{
			this.InitializeComponent();
		}
		public virtual void SetText()
		{
		}
		protected virtual void GetText()
		{
		}
		private void MFormFormClosing(object sender, FormClosingEventArgs e)
		{
			this.GetText();
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
			base.AutoScaleDimensions = new SizeF(6f, 12f);
			
			
			base.ClientSize = new Size(292, 266);
			base.Name = "mForm";
			this.Text = "mForm";
			base.FormClosing += new FormClosingEventHandler(this.MFormFormClosing);
			base.ResumeLayout(false);
		}
	}
}
