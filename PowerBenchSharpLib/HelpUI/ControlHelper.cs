using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace PowerBenchSharpLib
{
    static class ControlHelper
    {
        public static int GetLength(this Control control, string text)
        {
            using (var g = control.CreateGraphics())
            {
                var size = g.MeasureString(text, control.Font);
                return (int)size.Width+1;                
            }
        }

        public static void SetControlsTabIndex(params Control[] controls)
        {
            int startindex = 0;
            foreach (var item in controls)
            {
                item.TabIndex = startindex++; 
            }
 
        }
    }
}
