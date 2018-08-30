using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using Tigera.LibNetworkWrap;

namespace Test.Tigera.LibNetworkWrap
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            try
            {
               // Application.en
                Control.CheckForIllegalCrossThreadCalls = false;
                Application.EnableVisualStyles();
                Application.SetCompatibleTextRenderingDefault(false);
                ServerForm serform = new ServerForm();
                ClientForm clientform = new ClientForm();
                serform.Show();
                clientform.Show();
                Application.Run(new Form1());
            }
            catch (System.Exception ex)
            {
                Console.WriteLine(ex.ToString());
            }
            

        }
    }
}
