using GB698Cls;
using System;
using System.ComponentModel;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using WinFormsUI.Docking;
namespace GB698Ctl
{
    public class FrameParse : DockContent
    {
        private UCFrameParse frameParseUserControl1;

        public FrameParse()
        {
            this.InitializeComponent();
        }

        private void InitializeComponent()
        {
            this.frameParseUserControl1 = new UCFrameParse();
            this.SuspendLayout();
            // 
            // frameParseUserControl1
            // 
            this.frameParseUserControl1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(239)))), ((int)(((byte)(237)))), ((int)(((byte)(226)))));
            this.frameParseUserControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.frameParseUserControl1.Font = new System.Drawing.Font("SimSun", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.frameParseUserControl1.Location = new System.Drawing.Point(0, 0);
            this.frameParseUserControl1.Name = "frameParseUserControl1";
            this.frameParseUserControl1.Size = new System.Drawing.Size(950, 575);
            this.frameParseUserControl1.TabIndex = 0;
            // 
            // FrameParse
            // 
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(239)))), ((int)(((byte)(237)))), ((int)(((byte)(226)))));
            this.ClientSize = new System.Drawing.Size(950, 575);
            this.Controls.Add(this.frameParseUserControl1);
            this.Font = new System.Drawing.Font("SimSun", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Name = "FrameParse";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "报文解析";
            this.ResumeLayout(false);

        }
    }










}
