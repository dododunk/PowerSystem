using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace PowerBenchSharpLib
{
    public partial class EditField : UserControl
    {
        public EditField()
        {
            InitializeComponent();
            this.Edit1.TextChanged += new EventHandler(textBox1_TextChanged);
        }
        public TextBox Input
        {
            get
            {
                return this.Edit1;
            }
        }

        public int PropertyLableLen
        {
            get;
            set;
        }
        public void SetData(string labeltext,string orignvalue,int length = int.MaxValue)
        {
            Title = labeltext;
            _orgvalue = orignvalue;
            this.Edit1.Text = orignvalue;
        }
        public string Title
        {
            set
            {
                int len = value.Length;
                string text = value;
                for (int i = 0; i < 8 - len; i++)
                    text += " ";

                this.label_Property.Text = text;

            }
        }
        public bool EnableEmpty
        {
            get;
            set;
        }

        public string Result
        {
            get { return this.Edit1.Text; }
        }
       

        bool _readonly = false;
        public bool ReadOnly
        {
            get
            {
                return _readonly;
            }
            set
            {
                this.Edit1.Enabled = !_readonly;
            }
        }
       
        string _orgvalue = string.Empty;

        void textBox1_TextChanged(object sender, EventArgs e)
        {
            if (this.Edit1.Text != _orgvalue)
            {
                this.label_ChangedNotify.Text = "★";
            }
            else
            {
                this.label_ChangedNotify.Text = string.Empty;
            }
        }


        public bool Changed
        {
            get
            {
                return this.Edit1.Text != _orgvalue;
            }

        }

        private void textBox1_MouseHover(object sender, EventArgs e)
        {
            var tooltip = new ToolTip();
            tooltip.ToolTipTitle = "原始值:" + this._orgvalue;
            tooltip.Show("", this);
        }
    }
}
