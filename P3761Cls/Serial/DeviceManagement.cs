using System;
using System.Collections;
using System.Collections.Specialized;
using System.Management;
namespace GB698Cls
{
	public class DeviceManagement
	{
		public enum WMIPath
		{
			Win32_Processor,
			Win32_PhysicalMemory,
			Win32_Keyboard,
			Win32_PointingDevice,
			Win32_FloppyDrive,
			Win32_DiskDrive,
			Win32_CDROMDrive,
			Win32_BaseBoard,
			Win32_BIOS,
			Win32_ParallelPort,
			Win32_SerialPort,
			Win32_SerialPortConfiguration,
			Win32_SoundDevice,
			Win32_SystemSlot,
			Win32_USBController,
			Win32_NetworkAdapter,
			Win32_NetworkAdapterConfiguration,
			Win32_Printer,
			Win32_PrinterConfiguration,
			Win32_PrintJob,
			Win32_TCPIPPrinterPort,
			Win32_POTSModem,
			Win32_POTSModemToSerialPort,
			Win32_DesktopMonitor,
			Win32_DisplayConfiguration,
			Win32_DisplayControllerConfiguration,
			Win32_VideoController,
			Win32_VideoSettings,
			Win32_TimeZone,
			Win32_SystemDriver,
			Win32_DiskPartition,
			Win32_LogicalDisk,
			Win32_LogicalDiskToPartition,
			Win32_LogicalMemoryConfiguration,
			Win32_PageFile,
			Win32_PageFileSetting,
			Win32_BootConfiguration,
			Win32_ComputerSystem,
			Win32_OperatingSystem,
			Win32_StartupCommand,
			Win32_Service,
			Win32_Group,
			Win32_GroupUser,
			Win32_UserAccount,
			Win32_Process,
			Win32_Thread,
			Win32_Share,
			Win32_NetworkClient,
			Win32_NetworkProtocol
		}
		public class WMI
		{
			private ArrayList mocs;
			private StringDictionary names;
			public int Count
			{
				get
				{
					return this.mocs.Count;
				}
			}
			public object this[int index, string propertyName]
			{
				get
				{
					object result;
					try
					{
						string key = this.names[propertyName.Trim()];
						Hashtable hashtable = (Hashtable)this.mocs[index];
						result = hashtable[key];
					}
					catch
					{
						result = null;
					}
					return result;
				}
			}
			public string[] PropertyNames(int index)
			{
				string[] result;
				try
				{
					Hashtable hashtable = (Hashtable)this.mocs[index];
					string[] array = new string[hashtable.Keys.Count];
					hashtable.Keys.CopyTo(array, 0);
					Array.Sort<string>(array);
					result = array;
				}
				catch
				{
					result = null;
				}
				return result;
			}
			public WMI(string path)
			{
				this.names = new StringDictionary();
				this.mocs = new ArrayList();
				try
				{
					ManagementClass managementClass = new ManagementClass(path);
					ManagementObjectCollection instances = managementClass.GetInstances();
					bool flag = false;
					using (ManagementObjectCollection.ManagementObjectEnumerator enumerator = instances.GetEnumerator())
					{
						while (enumerator.MoveNext())
						{
							ManagementObject managementObject = (ManagementObject)enumerator.Current;
							Hashtable hashtable = new Hashtable();
							this.mocs.Add(hashtable);
							foreach (PropertyData current in managementObject.Properties)
							{
								hashtable.Add(current.Name, current.Value);
								if (!flag)
								{
									this.names.Add(current.Name, current.Name);
								}
							}
							flag = true;
							managementObject.Dispose();
						}
					}
					instances.Dispose();
				}
				catch (Exception ex)
				{
					throw new Exception(ex.Message);
				}
			}
			public WMI(DeviceManagement.WMIPath path) : this(path.ToString())
			{
			}
		}
	}
}
