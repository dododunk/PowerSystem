using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace PowerBenchSharpLib
{
    public  class AutoToolStrip : ToolStrip
    {
        public AutoToolStrip()
        {
            
        }
        Dictionary<string, EventHandler> _handlermap = new Dictionary<string, EventHandler>();
        System.Windows.Forms.ToolStripSplitButton _splitbutton;
        public void AddMenuItem(string text, EventHandler callback)
        {
            Debug.Assert(!_handlermap.Keys.Contains(text));

            _handlermap[text] = callback;
            if (_handlermap.Count == 1)
            {
                _splitbutton = new System.Windows.Forms.ToolStripSplitButton();
                _splitbutton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
                _splitbutton.Text = text;
                _splitbutton.ButtonClick += new EventHandler(button_Click);
                this.Items.Add(_splitbutton);
            }
            else
            {
                System.Windows.Forms.ToolStripMenuItem item = new System.Windows.Forms.ToolStripMenuItem();
                item.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
                item.Text = text;
                item.Click += new EventHandler(item_Click);
                this._splitbutton.DropDownItems.Add(item);

            }
        }
        public void SetCurrentButton(string text)
        {
            throw new NotImplementedException();
        }


        void item_Click(object sender, EventArgs e)
        {
            ToolStripMenuItem item = (ToolStripMenuItem)sender;
            var tmp = item.Text;
            item.Text = this._splitbutton.Text;
            this._splitbutton.Text = tmp;           
        }

        void button_Click(object sender, EventArgs e)
        {
            _handlermap[this._splitbutton.Text](this, EventArgs.Empty);
        }
    }
}
