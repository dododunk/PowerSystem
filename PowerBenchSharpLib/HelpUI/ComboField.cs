using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Tigera.LibCommon;

namespace PowerBenchSharpLib
{
    public partial class ComboField : UserControl
    {
        public ComboField()
        {
            InitializeComponent();
            this.combBox1.LostFocus += new EventHandler(textBox1_LostFocus);
        }
       
        public void SetData(string labeltext, int orignvalue, Type type)
        {
            this.Title = labeltext;
            _orgvalue = orignvalue;
            this.combBox1.DataSource = EnumHelper.GetDataCollection(type);
            this.combBox1.DisplayMember = "Name";
            this.combBox1.ValueMember = "Id";
            this.combBox1.SelectedValue = _orgvalue;
        }
        public void SetData(string labeltext, int orignvalue, List<int> values)
        {
            this.Title = labeltext;
            _orgvalue = orignvalue;
            this.combBox1.DataSource = values;
            this.combBox1.Text = orignvalue.ToString();

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

        
        bool _readonly = false;
        public bool ReadOnly
        {
            get
            {
                return _readonly;
            }
            set
            {
                this.combBox1.Enabled = !_readonly;
            }
        }
       
        int _orgvalue ;

        void textBox1_LostFocus(object sender, EventArgs e)
        {
            if (this.combBox1.SelectedValue == null)
                return;
            if ((int)this.combBox1.SelectedValue != _orgvalue)
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
                return (int)this.combBox1.SelectedValue != _orgvalue;
            }

        }

        public int Result
        {
            get
            {
                if (this.combBox1.SelectedValue == null)
                    return 0;
                return (int)this.combBox1.SelectedValue;
            }
        }
    }
}
