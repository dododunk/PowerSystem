using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using System.IO;

namespace PowerBenchSharpLib.Test
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            var dir = Path.GetDirectoryName(Application.ExecutablePath);
            Directory.SetCurrentDirectory(dir);
            AmmeterDB.InitConnection(@".\powerbench_smalltest.db");
            //var form = new FormContainer<UCAmmeterUsage>();
            
            //form.ShowDialog();
            Application.Run(new Form1());
        }
    }
}
