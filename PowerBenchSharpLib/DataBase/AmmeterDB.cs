using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Tigera.T_Definition;
using System.Data.SqlClient;
using System.Data.OleDb;
using System.Data.Common;
using System.IO;
using System.Windows.Forms;
using System.Data;
using System.Data.SQLite;

namespace PowerBenchSharpLib
{
    public enum DataOpeMode
    {
        Add,
        Mod,
        Del
    }

    public static class AmmeterDB
    {
      
        public static bool ExcuteSql(string sql)
        {
            SQLiteCommand cmd = new SQLiteCommand(sql, _conn as SQLiteConnection);
            cmd.ExecuteNonQuery();
            return true;
        }


        public static void InitConnection(String dbfilepath = "PowerBench.db")
        {
            //access.
            string fname = dbfilepath;
            if (_conn != null)
                return;

            if (!File.Exists(fname))
            {
                MessageBox.Show("无法找到数据库文件");
                OpenFileDialog dlg = new OpenFileDialog();
                if (dlg.ShowDialog() != DialogResult.OK)
                    throw new Exception("没有设置数据连接!");
                fname = dlg.FileName;


            }
            if (_conn == null)
            {
                _conn = new SQLiteConnection("Data Source=" + fname + ";");
                _conn.Open();
            }        
        }




        public static DataSet LoadAmmeterUsage(string filter = "")
        {
            try
            {
                string sql = @"SELECT 
a.USER_NO as [用户编号],
a.USER_NAME as [用户],
c.USER_KINDNAME as [用户类别], 
b.CHECK_TIME as [时间],
b.CHECK_VALUE as [用电量],
a.USER_MODULE as [模块],  
a.USER_COMPANY as [公司] ,
a.USER_STATION as [站],  
a.USER_BUS as [段], 
a.USER_LINENAME  as [线], 
a.USER_TRANSFORMER as [变压器], 
a.USER_VIRTUALADDR as [虚拟地址], 
a.USER_A1 as [A1], 
a.USER_A2 as [A2]
 
FROM AMMETERINFO a,AMMETERUSAGE b ,DICUSERKIND c
WHERE a.USER_NO = b.USER_NO and a.USER_KIND = c.USER_KIND 
ORDER BY b.USER_NO ,b.CHECK_TIME

".Replace(Environment.NewLine, " ");
                ForwardLogger.Log(sql);

                SQLiteCommand cmd = new SQLiteCommand(sql, _conn as SQLiteConnection);
                cmd.CommandType = CommandType.Text;

                SQLiteDataAdapter adapter = new SQLiteDataAdapter();
                adapter.SelectCommand = cmd;
                DataSet ds = new DataSet("usage");
                adapter.Fill(ds);

                return ds;
            }
            catch (Exception e)
            {
                ForwardLogger.Log(e.Message);
            }
            return null;
        }
        public static bool WriteAmmeterUsage(AmmeterUsage info)
        {
            try
            {
                var sql = string.Format("Insert into AMMETERUSAGE(USER_NO,CHECK_TIME,CHECK_VALUE) values('{0}',{1},{2})", info.USER_NO, info.CHECK_TIME, info.CHECK_VALUE);
                ForwardLogger.Log(sql);
                SQLiteCommand cmd = new SQLiteCommand(sql, _conn);
                cmd.ExecuteNonQuery();
                return true;
            }
            catch (Exception e)
            {
                ForwardLogger.Log(e.Message);
                return false;
            }
            
        }


        static SQLiteConnection _conn;

        public static List<P_AmmeterInfo> LoadAmmInfoFromDatabase()
        {
            var sql = "SELECT *,rowid from AMMETERINFO";
            ForwardLogger.Log(sql);
            SQLiteCommand cmd = new SQLiteCommand(sql, _conn as SQLiteConnection);
            
            var reader = cmd.ExecuteReader();
            List<P_AmmeterInfo> results = new List<P_AmmeterInfo>();

            while (reader.Read())
            {
                P_AmmeterInfo info = new P_AmmeterInfo();
                info.USER_COMPANY = DbDataConvert.ToString(reader["USER_COMPANY"]);

                info.USER_STATION = DbDataConvert.ToString(reader["USER_STATION"]);

                info.USER_LINE = DbDataConvert.ToInt32(reader["USER_LINE"]);

                info.USER_BACKLINE = DbDataConvert.ToInt32(reader["USER_BACKLINE"]);

                info.USER_LINENAME = DbDataConvert.ToString(reader["USER_LINENAME"]);

                info.USER_TRANSFORMER = DbDataConvert.ToString(reader["USER_TRANSFORMER"]);

                //info.USER_PHASE = DbDataConvert.ToInt16(reader["USER_PHASE"]);

                info.USER_NAME = DbDataConvert.ToString(reader["USER_NAME"]);

                info.USER_NO = DbDataConvert.ToString(reader["USER_NO"]);

                info.USER_INITIALVAL = DbDataConvert.ToSingle(reader["USER_INITIALVAL"]);

                info.USER_BUS = DbDataConvert.ToInt32(reader["USER_BUS"]);

                info.USER_MODULE = DbDataConvert.ToString(reader["USER_MODULE"]);

                info.USER_VIRTUALADDR = DbDataConvert.ToInt32(reader["USER_VIRTUALADDR"]);

                info.USER_A1 = DbDataConvert.ToString(reader["USER_A1"]);

                info.USER_A2 = DbDataConvert.ToString(reader["USER_A2"]);

                info.USER_CDMA = (Tigera.T_Definition.P_AmmeterInfo.CDMA_TYPE)DbDataConvert.ToInt32(reader["USER_CDMA"]);

                info.USER_KIND = (Tigera.T_Definition.P_AmmeterInfo.USER_KINDTYPE)DbDataConvert.ToInt32(reader["USER_KIND"]);

                info.USER_SUBAMM = DbDataConvert.ToInt32(reader["USER_SUBAMM"]);

                info.USER_SUBAMMMAC = DbDataConvert.ToInt32(reader["USER_SUBAMMMAC"]);

                info.USER_CHANNEL = DbDataConvert.ToInt32(reader["USER_CHANNEL"]);

                info.USER_PHASE = (Tigera.T_Definition.P_AmmeterInfo.Phase)DbDataConvert.ToInt32(reader["USER_PHASE"]);

                info.USER_DEC_CNL = DbDataConvert.ToInt32(reader["USER_DEC_CNL"]);

                info.ROWID = DbDataConvert.ToInt32(reader["ROWID"]);

                results.Add(info);


            }
            return results;

        }
    }
}
