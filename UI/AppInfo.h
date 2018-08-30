#pragma once
class AppInfo
{
public:
	BOOL          m_WhichKind;  //选择版本     TRUE 变电站版本           FALSE 电局版
	BOOL          m_2000Users;  //2000用户     TRUE 2000用户             FALSE 用户数不受限制
	BOOL          m_AutoRunning;//是否一启动就自动运行
	BOOL          m_SingleBB;   //是否是单一版本
	BOOL            m_YanShi;   //是否是演示版本
	static AppInfo& Instance()
	{
		static AppInfo intance;
		return intance;
	}

};