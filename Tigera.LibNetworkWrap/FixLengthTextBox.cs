using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Tigera.LibCommon;

namespace Tigera.LibNetworkWrap
{
    class FixLengthTextBox : System.Windows.Forms.TextBox 
    {
        public FixLengthTextBox()
        {
            this.Multiline = true;
        }

        int _fixlength = int.MaxValue;
        public int FixLengthCount
        {
            set
            {
                _fixlength = value;
            }
        }
        public void AddString(string msg)
        {
            msg += System.Environment.NewLine;

            if(_fixlength > msg.Length)
            {
                if(this.Text.Length+ msg.Length < _fixlength)
                {
                    this.Text += msg;
                }
                else
                {
                    this.Text = this.Text.Substring(this.Text.Length - _fixlength+msg.Length) + msg;
                }
            }
            else
            {
                this.Text = msg;

            }
            
        }
        public void ClearData()
        {
            
            this.Text = string.Empty;
        }

        
    }
}
