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
    public partial class UCFilterCombo : UserControl
    {
        public UCFilterCombo()
        {
            InitializeComponent();
        }

        public string Title
        {
            set
            {
                this.label1.Text = value; 
            }
        }
        public List<ShowItem> Items
        {

            set
            {
                this.comboBox1.DataSource = value;
                this.comboBox1.DisplayMember = "Display";
                this.comboBox1.ValueMember = "Value";
               // this.comboBox1.SelectedValue
            }
        }
        public object SelectValue
        {
            get
            {
                return this.comboBox1.SelectedValue;
            }
            set
            {
                this.comboBox1.SelectedValue = value; 
            }
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (this.SelectValue != _lastSelectValue && SelectChanged != null)
            {
                _lastSelectValue = this.SelectValue;
                SelectChanged(this, new TiEventArgs<object>(this.SelectValue));
            }
            
        
        }
        public event EventHandler<TiEventArgs<object>> SelectChanged;

        object _lastSelectValue;

    }


    public class ShowItem
    {
        public ShowItem(string d, object v)
        {
            Display = d;
            Value = v;
        }
        public string Display
        {
            get;
            set;
        }
        public object Value
        {
            get;
            set;
        }
    }
    
}
