using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace PowerBenchSharpLib.Test
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            //AmmeterDB.InitConnection(@"E:\works\tigera\src\PowerSystem\Debug\powerbench.db");
            //var results = AmmeterDB.LoadAmmInfoFromDatabase();

            //MessageBox.Show(this,results.Count.ToString());
            //this.ammeterInfoControl1.Tree.ClearData();
            //this.ammeterInfoControl1.Tree.AddData(results);
            //this.ammeterInfoControl1.Tree.BuildTree();
            this.ammeterInfoControl1.Tree.NodeMouseDoubleClick += new TreeNodeMouseClickEventHandler(ammeterTree1_NodeMouseDoubleClick);
                //+= new MouseEventHandler(ammeterTree1_MouseDown);
            //this.ammeterTree1.ExpandAll();
            this.ammeterInfoControl1.Tree.OnNodePropertyShow += new EventHandler<NodeEventArgs>(ammeterTree1_OnNodePropertyShow);
            this.ammeterInfoControl1.OnSelect += ammeterInfoControl1_OnSelect;
        }

        void ammeterInfoControl1_OnSelect(object sender, SelectItemEventArgs e)
        {
            this.ucAmmetersOpe1.LoadData(e.Datas);
            //throw new NotImplementedException();
        }

        void ammeterTree1_OnNodePropertyShow(object sender, NodeEventArgs e)
        {
            try
            {
                this.propertyGrid1.SelectedObject = e.Obj;
                this.propertyGrid1.Refresh();
            }
            catch (System.Exception ex)
            {
                Console.WriteLine(ex.ToString());

            }
            //throw new NotImplementedException();
        }

        void ammeterTree1_NodeMouseDoubleClick(object sender, TreeNodeMouseClickEventArgs e)
        {
            //throw new NotImplementedException();
            try
            {
                this.propertyGrid1.SelectedObject =  this.ammeterInfoControl1.Tree.SelectedNode.Tag;
                this.propertyGrid1.Refresh();
            }
            catch (System.Exception ex)
            {
                Console.WriteLine(ex.ToString());

            }
        }

        void ammeterTree1_MouseDown(object sender, MouseEventArgs e)
        {
            //throw new NotImplementedException();
            
        }

        void ammeterTree1_NodeMouseClick(object sender, TreeNodeMouseClickEventArgs e)
        {
            
            
        }

        private void button1_Click(object sender, EventArgs e)
        {
            FormOuterSetting form = new FormOuterSetting();
            form.ShowDialog();

        }
        
        void Button2Click(object sender, EventArgs e)
        {
        	Form2 f = new Form2();
        	f.ShowDialog();
        }
    }
}
