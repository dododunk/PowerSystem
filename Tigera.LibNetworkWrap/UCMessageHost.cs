using System;
using System.Linq;
using System.Windows.Forms;
using Tigera.LibCommon;
using Tigera.Network;
using Tigera.T_Definition;
using Tigera.LibCodeUtils;
using Tigera.LibBasic.Thread;

namespace Tigera.LibNetworkWrap
{



    public partial class UCMessageHost : UserControl
    {
        const int WM_USER = 0x0400;
        public const int WM_USER_NETMESSAGE = WM_USER + 156;
        public UCMessageHost()
        {
            InitializeComponent();

            //允许跨线程调用UI控件
            Control.CheckForIllegalCrossThreadCalls = false;

            this.textBox_Log.FixLengthCount = 2000;
            SetupUI();
            //todo. 
            FuncDispatcher.SetDispatchHost(this);

            this.textBox_localHost.Items.AddRange( HostNameResolver.GetLocalHostIPs().ToArray());
        }
       
        private void SetupUI()
        {
            textBox_RemoteAddress.Visible = _clientmode;
            textBox_RemotePort.Visible = _clientmode;
            button_Connect.Visible = _clientmode;
            textBox_localHost.Visible = !_clientmode;
            textBox_HostPort.Visible = !_clientmode;
            button_Listen.Visible = !_clientmode;
            
        }

        bool _clientmode = true;
        public bool ClientMode
        {
            get
            {
                return _clientmode;
            }
            set
            {
                if (_clientmode != value)
                {
                    _clientmode = value;
                    SetupUI();
                }
            }
        }

        TcpSocketConnection conn;

        public IntPtr MessageReciever
        {
            set;
            get;

        }

        void Decoder_MessageReceived(object sender, MessageEventArgs e)
        {
            this.textBox_Log.AddString("接收到"+ e.ToString());
            
            Win32API.PostMessage(MessageReciever, WM_USER_NETMESSAGE, 0, 0);
            if (MessageReceived != null)
            {
                MessageReceived(sender, e);
            }
        }


        public event EventHandler<MessageEventArgs> MessageReceived;

        public void SendMessage(byte[] data)
        {
            this.conn.SendData(data);
        }

        void Con_Accepted(object sender, TCPConnectedArgs e)
        {
            this.textBox_Log.AddString("连接成功：" + e.Socket.RemoteEndPoint.ToString());
            var Decoder = Singleton<MessageDecoderPool>.GetInstance().Pop();
            Decoder.MessageReceived += new EventHandler<MessageEventArgs>(Decoder_MessageReceived);
            conn = new TcpSocketConnection(e.Socket, new ConstructableObjectPool<SocketAsyncEventArgsEx>(100, new SocketAsyncEventArgsExFactory()), 1024,Decoder);
            conn.Disconnected += new EventHandler<ConnectionCloseEventArgs>(conn_Disconnected);

            conn.Errored += new EventHandler<TCPErroredArgs>(conn_Errored);
            
        }

        void conn_Errored(object sender, TCPErroredArgs e)
        {
            this.textBox_Log.AddString("网络错误：" + e.Error.ToString());
        }

        void conn_Disconnected(object sender, ConnectionCloseEventArgs e)
        {
            this.textBox_Log.AddString("网络断开：" + e.ToString());
        }




        /// //////////////////////////////////////
        //客户端模型
        TcpSocketConnector _conc;
        private void button_Connect_Click(object sender, EventArgs e)
        {
            int port;
            if (!int.TryParse(this.textBox_RemotePort.Text, out port) || port <= 0)
            {
                MessageBox.Show("请输入有效端口");
                return;
            }
            


            _conc = new TcpSocketConnector();
            _conc.Accepted += new EventHandler<TCPConnectedArgs>(Con_Accepted);
            _conc.Errored += new EventHandler<TCPErroredArgs>(Conc_Errored);

            _conc.Connect(this.textBox_RemoteAddress.Text, int.Parse(this.textBox_RemotePort.Text));
            EnableControls(false);
        }

        void Conc_Errored(object sender, TCPErroredArgs e)
        {
            this.textBox_Log.AddString("无法连接：" + e.Error.ToString());

            EnableControls(true);
            
            if (_conc != null)
            {
                _conc.ClearEvents();
                _conc = null;
            }
            if (_acc != null)
            {
                _acc.ClearEvents();
                _acc = null;
            }
        }




        /// /////////////////////////////////////////
        /// 服务器模型
        TcpSocketAcceptor _acc;
        private void button_Listen_Click(object sender, EventArgs e)
        {
            int port;
            if ( !int.TryParse(this.textBox_HostPort.Text,out port) || port<=0)
            {
                MessageBox.Show("请输入有效端口");
                return;

            }
            _acc = new TcpSocketAcceptor();
            _acc.Accepted += new EventHandler<TCPConnectedArgs>(Con_Accepted);
            _acc.Errored += new EventHandler<TCPErroredArgs>(Conc_Errored);
            if (string.IsNullOrEmpty(this.textBox_localHost.Text))
            {
                _acc.Start(port);
            }
            else
            {
                _acc.Start(port, this.textBox_localHost.Text);
            }

            

            EnableControls(false);

        }


        private void EnableControls(bool en)
        {
             this.textBox_HostPort.Enabled = en;
            this.button_Listen.Enabled = en;

            this.textBox_RemoteAddress.Enabled = en;
            this.textBox_RemotePort.Enabled = en;
            this.button_Connect.Enabled = en;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            OnlineUsersQueryRequest info = new OnlineUsersQueryRequest();
            var data = ESHelper.Pack(ref info);
            this.SendMessage(data);

        }

        private void button2_Click(object sender, EventArgs e)
        {
            P_CMD_Request req = new P_CMD_Request();
            OnlineUsersQueryRequest info = new OnlineUsersQueryRequest();
            var data = ESHelper.Pack(ref req,1);
            BytesBuilder bb = new BytesBuilder();
            bb.Append(data
                ).Append( ESHelper.Pack(ref info));

            this.SendMessage(bb.ToBytes());
        }


    }
}
