using System;
using System.Reflection;
using System.Runtime.InteropServices;
namespace System.Windows.Forms
{
	public class RichTextBoxEx : RichTextBox
	{
		private NativeMethods.RECT borderRect;
		protected override CreateParams CreateParams
		{
			get
			{
				CreateParams createParams = base.CreateParams;
				if (this.RenderWithVisualStyles() && (createParams.ExStyle & 512) == 512)
				{
					createParams.ExStyle ^= 512;
				}
				return createParams;
			}
		}
		protected override void WndProc(ref Message m)
		{
			int msg = m.Msg;
			switch (msg)
			{
			case 131:
				this.WmNccalcsize(ref m);
				return;

			case 132:
				break;

			case 133:
				this.WmNcpaint(ref m);
				return;

			default:
				if (msg == 794)
				{
					base.UpdateStyles();
					return;
				}
				break;
			}
			base.WndProc(ref m);
		}
		private void WmNccalcsize(ref Message m)
		{
			base.WndProc(ref m);
			if (this.RenderWithVisualStyles())
			{
				NativeMethods.NCCALCSIZE_PARAMS nCCALCSIZE_PARAMS = default(NativeMethods.NCCALCSIZE_PARAMS);
				NativeMethods.RECT rECT;
				if (m.WParam == IntPtr.Zero)
				{
					rECT = (NativeMethods.RECT)Marshal.PtrToStructure(m.LParam, typeof(NativeMethods.RECT));
				}
				else
				{
					nCCALCSIZE_PARAMS = (NativeMethods.NCCALCSIZE_PARAMS)Marshal.PtrToStructure(m.LParam, typeof(NativeMethods.NCCALCSIZE_PARAMS));
					rECT = nCCALCSIZE_PARAMS.rgrc0;
				}
				IntPtr windowDC = NativeMethods.GetWindowDC(base.Handle);
				IntPtr hTheme = NativeMethods.OpenThemeData(base.Handle, "EDIT");
				NativeMethods.RECT rECT2;
				if (NativeMethods.GetThemeBackgroundContentRect(hTheme, windowDC, 1, 1, ref rECT, out rECT2) == 0)
				{
					rECT2.Inflate(-1, -1);
					this.borderRect = checked(new NativeMethods.RECT(rECT2.Left - rECT.Left, rECT2.Top - rECT.Top, rECT.Right - rECT2.Right, rECT.Bottom - rECT2.Bottom));
					if (m.WParam == IntPtr.Zero)
					{
						Marshal.StructureToPtr(rECT2, m.LParam, false);
					}
					else
					{
						nCCALCSIZE_PARAMS.rgrc0 = rECT2;
						Marshal.StructureToPtr(nCCALCSIZE_PARAMS, m.LParam, false);
					}
					m.Result = new IntPtr(768);
				}
				NativeMethods.CloseThemeData(hTheme);
				NativeMethods.ReleaseDC(base.Handle, windowDC);
			}
		}
		private void WmNcpaint(ref Message m)
		{
			base.WndProc(ref m);
			checked
			{
				if (this.RenderWithVisualStyles())
				{
					int iPartId = 1;
					int iStateId;
					if (base.Enabled)
					{
						if (base.ReadOnly)
						{
							iStateId = 6;
						}
						else
						{
							iStateId = 1;
						}
					}
					else
					{
						iStateId = 4;
					}
					NativeMethods.RECT rECT;
					NativeMethods.GetWindowRect(base.Handle, out rECT);
					rECT.Right -= rECT.Left;
					rECT.Bottom -= rECT.Top;
					rECT.Top = (rECT.Left = 0);
					IntPtr windowDC = NativeMethods.GetWindowDC(base.Handle);
					NativeMethods.RECT rECT2 = rECT;
					rECT2.Left += this.borderRect.Left;
					rECT2.Top += this.borderRect.Top;
					rECT2.Right -= this.borderRect.Right;
					rECT2.Bottom -= this.borderRect.Bottom;
					NativeMethods.ExcludeClipRect(windowDC, rECT2.Left, rECT2.Top, rECT2.Right, rECT2.Bottom);
					IntPtr hTheme = NativeMethods.OpenThemeData(base.Handle, "EDIT");
					if (NativeMethods.IsThemeBackgroundPartiallyTransparent(hTheme, 1, 1) != 0)
					{
						NativeMethods.DrawThemeParentBackground(base.Handle, windowDC, ref rECT);
					}
					NativeMethods.DrawThemeBackground(hTheme, windowDC, iPartId, iStateId, ref rECT, IntPtr.Zero);
					NativeMethods.CloseThemeData(hTheme);
					NativeMethods.ReleaseDC(base.Handle, windowDC);
					m.Result = IntPtr.Zero;
				}
			}
		}
		private bool VisualStylesEnabled()
		{
			Type typeFromHandle = typeof(Application);
			PropertyInfo property = typeFromHandle.GetProperty("RenderWithVisualStyles");
			bool result;
			if (property == null)
			{
				OperatingSystem oSVersion = Environment.OSVersion;
				if (oSVersion.Platform == PlatformID.Win32NT && ((oSVersion.Version.Major == 5 && oSVersion.Version.Minor >= 1) || oSVersion.Version.Major > 5))
				{
					NativeMethods.DLLVersionInfo dLLVersionInfo = default(NativeMethods.DLLVersionInfo);
					dLLVersionInfo.cbSize = Marshal.SizeOf(typeof(NativeMethods.DLLVersionInfo));
					if (NativeMethods.DllGetVersion(ref dLLVersionInfo) == 0)
					{
						result = (dLLVersionInfo.dwMajorVersion > 5 && NativeMethods.IsThemeActive() && NativeMethods.IsAppThemed());
						return result;
					}
				}
				result = false;
			}
			else
			{
				bool flag = (bool)property.GetValue(null, null);
				result = flag;
			}
			return result;
		}
		private bool RenderWithVisualStyles()
		{
			return base.BorderStyle == BorderStyle.Fixed3D && this.VisualStylesEnabled();
		}
	}
}
