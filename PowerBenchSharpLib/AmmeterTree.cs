using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Tigera.T_Definition;
using System.Windows.Forms;
using System.Drawing;
using Tigera.LibCommon;

namespace PowerBenchSharpLib
{

    public class AmmeterTree : System.Windows.Forms.TreeView
    {
        private List<P_AmmeterInfo> _list = new List<P_AmmeterInfo>();
        private ImageList _imagelist = new ImageList();


        public List<P_AmmeterInfo> GetSelected()
        {   
            List<P_AmmeterInfo> _info = new List<P_AmmeterInfo>();
            getLeafNode(this.TopNode, _info);
            return _info;
        }


        /// <summary>
        /// 利用递归获取一个节点的所有叶子
        /// </summary>
        /// <param _name="tn">TreeNode</param>
        /// <param _name="al">指针数组</param>
        private void getLeafNode(TreeNode myTn, List<P_AmmeterInfo> result)
        {

            for (int i = 0; i < myTn.Nodes.Count; i++)
            {
                if (myTn.Nodes[i].Nodes.Count == 0)//叶节点
                {
                    if (myTn.Nodes[i].Checked && myTn.Nodes[i].Tag is P_AmmeterInfo)
                    {
                        result.Add((P_AmmeterInfo)myTn.Nodes[i].Tag);
                    }

                }
                else
                {
                    getLeafNode(myTn.Nodes[i], result);
                }
            }

        }


        public AmmeterTree()
        {
            _imagelist.Images.Add(Resource.company);
            _imagelist.Images.Add(Resource.station);
            _imagelist.Images.Add(Resource.bus);
            _imagelist.Images.Add(Resource.line);
            _imagelist.Images.Add(Resource.transformer);
            _imagelist.Images.Add(Resource.module);
            _imagelist.Images.Add(Resource.ammetter);

            this.ShowNodeToolTips = true;
            this.ImageList = _imagelist;
            this.CheckBoxes = true;
            this.NodeMouseClick += new TreeNodeMouseClickEventHandler(AmmeterTree_NodeMouseClick);
            this.MouseDoubleClick += new MouseEventHandler(AmmeterTree_MouseDoubleClick);
            this.AfterCheck += new TreeViewEventHandler(AmmeterTree_AfterCheck);

        }

        void AmmeterTree_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            menuItem_Property_Click(this, EventArgs.Empty);            
        }

        void AmmeterTree_NodeMouseClick(object sender, TreeNodeMouseClickEventArgs e)
        {
            ContextMenu menu = new ContextMenu();
            if (e.Button == MouseButtons.Right)
            {


                MenuItem menuItem_Property = new MenuItem("属性");
                menuItem_Property.Click += new EventHandler(menuItem_Property_Click);
                menu.MenuItems.Add(menuItem_Property);

                MenuItem menuItem_Modify = new MenuItem("修改");
                menuItem_Modify.Click += new EventHandler(menuItem_Modify_Click);
                menu.MenuItems.Add(menuItem_Modify);


                MenuItem menuItem_Del = new MenuItem("删除");
                menuItem_Del.Click += new EventHandler(menuItem_Modify_Del);
                menu.MenuItems.Add(menuItem_Del);


            }

            this.ContextMenu = menu;
        }
         void menuItem_Modify_Del(object sender, EventArgs e)
        {
            OpeNode(DataOpeMode.Del);
        }
        
        void menuItem_Modify_Click(object sender, EventArgs e)
        {
            OpeNode(DataOpeMode.Mod);

        }

        private void OpeNode(DataOpeMode ope)
        {

            if (this.SelectedNode != null)
            {
                var groupnode = this.SelectedNode.Tag as LevelBase;
                if (groupnode != null)
                {
                    FormNodeModifyDelete form = new FormNodeModifyDelete();
                    form.Ope = ope;
                    form.Info = this.SelectedNode.Tag as LevelBase;
                    if (form.ShowDialog() == DialogResult.OK)
                    {
                        this.LoadData(AmmeterDB.LoadAmmInfoFromDatabase());
                    }
                }
                else
                {
                    FormAmmMod form = new FormAmmMod();

                    form.CurrentData = (P_AmmeterInfo)this.SelectedNode.Tag;
                    form.ShowDialog(this);
                }
            }
        }



        void menuItem_Property_Click(object sender, EventArgs e)
        {
            if (this.SelectedNode != null)
            {
                
                if (OnNodePropertyShow != null)
                {
                    OnNodePropertyShow(this, new NodeEventArgs(this.SelectedNode.Tag));
                }
            }
        }
        //event EventHandler<TCPConnectedArgs> Accepted;
        public event EventHandler<NodeEventArgs> OnNodePropertyShow;



        void AmmeterTree_AfterCheck(object sender, TreeViewEventArgs e)
        {
            this.BeginUpdate();
            if (e.Action != TreeViewAction.Unknown)
            {
                if (e.Node.Nodes.Count > 0)
                {
                    /* Calls the CheckAllChildNodes method, passing in the current 
                     * Checked value of the TreeNode whose checked state changed. */
                    this.CheckAllChildNodes(e.Node, e.Node.Checked);
                }
            }
            this.EndUpdate();
        }
        private void CheckAllChildNodes(TreeNode treeNode, bool nodeChecked)
        {
            foreach (TreeNode node in treeNode.Nodes)
            {
                node.Checked = nodeChecked;
                if (node.Nodes.Count > 0)
                {
                    this.CheckAllChildNodes(node, nodeChecked);
                }
            }
        }

        public void LoadData(List<P_AmmeterInfo> datas)
        {
            ClearData();
            _list.AddRange(datas);
            BuildTree();
        }

        public void AddData(List<P_AmmeterInfo> datas)
        {
            _list.AddRange(datas);
        }

        public void ClearData()
        {
            this.Nodes.Clear();
            _list.Clear();
        }




        public void BuildTree()
        {
            this.BeginUpdate();
            this.Nodes.Clear();



            var companys = from amm in _list group amm by amm.USER_COMPANY into company orderby company.Key select company;


            foreach (var company in companys)//0-局
            {
                var companynode = this.Nodes.Add(company.Key);
                companynode.Tag = new Level0Company(company);
                companynode.ToolTipText = "局:" + company.Key;
                companynode.ImageIndex = companynode.SelectedImageIndex = 0;

                var stations = from amm in company group amm by amm.USER_STATION into station orderby station.Key select station;

                foreach (var station in stations)//1-站
                {
                    var stationnode = companynode.Nodes.Add(station.Key);
                    stationnode.Tag = new Level1station(station);
                    stationnode.ToolTipText = "站:" + station.Key;
                    stationnode.ImageIndex = stationnode.SelectedImageIndex = 1;

                    var buses = from amm in station group amm by amm.USER_BUS.ToString() into bus orderby bus.Key select bus;

                    foreach (var bus in buses) //2- 段/bus
                    {
                        var busnode = stationnode.Nodes.Add(bus.Key.ToString());
                        busnode.Tag = new Level2Bus(bus);
                        busnode.ToolTipText = "段(母线):" + bus.Key;
                        busnode.ImageIndex = busnode.SelectedImageIndex = 2;

                        var lines = from amm in bus group amm by amm.USER_LINENAME into line orderby line.Key select line;

                        foreach (var line in lines)//3-线
                        {
                            var linenode = busnode.Nodes.Add(line.Key);
                            linenode.Tag = new Level3Line(line);
                            linenode.ToolTipText = "线:" + line.Key;
                            linenode.ImageIndex = linenode.SelectedImageIndex = 3;

                            var transfromers = from amm in line group amm by amm.USER_TRANSFORMER into tranformer orderby tranformer.Key select tranformer;

                            foreach (var tranformer in transfromers)//4-变压器
                            {
                                var tranformernode = linenode.Nodes.Add(tranformer.Key);
                                tranformernode.Tag = new Level4Trans( tranformer);
                                tranformernode.ToolTipText = "变压器:" + tranformer.Key;
                                tranformernode.ImageIndex = tranformernode.SelectedImageIndex = 4;

                                var modules = from amm in tranformer group amm by amm.USER_MODULE into module orderby module.Key select module;


                                foreach (var module in modules)//5-模块
                                {
                                    var modulenode = tranformernode.Nodes.Add(module.Key);
                                    modulenode.Tag = new Level5Module( module);
                                    modulenode.ToolTipText = "模块:" + module.Key;
                                    modulenode.ImageIndex = modulenode.SelectedImageIndex = 5;

                                    var subammeters = from amm in module group amm by amm.USER_NO into subammeter orderby subammeter.Key select subammeter;

                                    foreach (var subammeter in subammeters)//6-子表
                                    {
                                        var subammeternode = modulenode.Nodes.Add(subammeter.Key);// + subammeter.First(0).USER_VIRTUALADDR);
                                        var amm = subammeter.First();
                                        subammeternode.Tag = amm;
                                        subammeternode.ToolTipText = "子表:" + subammeter.Key;
                                        subammeternode.ImageIndex = subammeternode.SelectedImageIndex = 6;
                                        //subammeternode.ContextMenu = null;
                                    }

                                }
                            }
                        }
                    }
                }
            }//end of for
            //this.ExpandAll();
            if (this.Focused)
            {
                this.SelectedNode = this.TopNode;
            }

            this.EndUpdate();
            // 
            //this.se
        }
    }
    
}
