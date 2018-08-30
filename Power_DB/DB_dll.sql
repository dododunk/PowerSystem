-- This script was created using WinSQL Professional
-- Timestamp: 2012-4-3 16:05:25

-- Total Objects:    27
-- Total Tables:     27
-- Total Views:      0
-- Total Procedures: 0
use Power_DB
go

--Object: Table: dbo.dtproperties - Script Date: 2012-4-3 16:05:25
if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[dtproperties]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[dtproperties]
GO

CREATE TABLE [dbo].[dtproperties](
     [id] [int] IDENTITY(1,1)  NOT NULL ,
     [objectid] [int] NULL ,
     [property] [varchar](64) COLLATE Chinese_PRC_CI_AS NOT NULL ,
     [value] [varchar](255) COLLATE Chinese_PRC_CI_AS NULL ,
     [uvalue] [nvarchar](510) COLLATE Chinese_PRC_CI_AS NULL ,
     [lvalue] [image] NULL ,
     [version] [int] DEFAULT (0)  NOT NULL 
) ON [PRIMARY]

GO

ALTER TABLE [dbo].[dtproperties] WITH NOCHECK
    ADD CONSTRAINT [pk_dtproperties] 
    PRIMARY KEY (id, property)
    ON [PRIMARY]

GO




--Object: Table: dbo.TB_AMMETER - Script Date: 2012-4-3 16:05:25
if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[TB_AMMETER]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[TB_AMMETER]
GO

CREATE TABLE [dbo].[TB_AMMETER](
     [AMMETER_TYPE] [char](10) COLLATE Chinese_PRC_CI_AS NOT NULL ,
     [AMMETER_MANUFACTURER] [char](10) COLLATE Chinese_PRC_CI_AS NULL ,
     [AMMETER_IMPULSE] [int] NOT NULL ,
     [AMMETER_REMARK] [char](30) COLLATE Chinese_PRC_CI_AS NULL 
) ON [PRIMARY]

GO

ALTER TABLE [dbo].[TB_AMMETER] WITH NOCHECK
    ADD CONSTRAINT [PK__TB_AMMETER__6EC0713C] 
    PRIMARY KEY (AMMETER_TYPE)
    ON [PRIMARY]

GO




--Object: Table: dbo.TB_Auto - Script Date: 2012-4-3 16:05:25
if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[TB_Auto]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[TB_Auto]
GO

CREATE TABLE [dbo].[TB_Auto](
     [Auto_Parameter1] [tinyint] NULL ,
     [Auto_Parameter2] [tinyint] NULL ,
     [Auto_Parameter3] [tinyint] NULL ,
     [Auto_Parameter4] [tinyint] NULL ,
     [Auto_Parameter5] [tinyint] NULL ,
     [Auto_Parameter6] [tinyint] NULL ,
     [Auto_Parameter7] [tinyint] NULL ,
     [Auto_Parameter8] [tinyint] NULL ,
     [Auto_Parameter9] [tinyint] NULL ,
     [Auto_Parameter10] [tinyint] NULL ,
     [Auto_Parameter11] [tinyint] NULL ,
     [Auto_Parameter12] [tinyint] NULL ,
     [Auto_Parameter13] [tinyint] NULL ,
     [Auto_Parameter14] [tinyint] NULL ,
     [Auto_Parameter15] [tinyint] NULL ,
     [Auto_Parameter16] [tinyint] NULL ,
     [Auto_Parameter17] [tinyint] NULL ,
     [Auto_Parameter18] [tinyint] NULL ,
     [Auto_Parameter19] [tinyint] NULL ,
     [Auto_Parameter20] [tinyint] NULL ,
     [Auto_Parameter21] [tinyint] NULL ,
     [Auto_Parameter22] [tinyint] NULL ,
     [Auto_Parameter23] [tinyint] NULL ,
     [Auto_Parameter24] [tinyint] NULL ,
     [Auto_Parameter25] [tinyint] NULL ,
     [Auto_Parameter26] [tinyint] NULL ,
     [Auto_Parameter27] [tinyint] NULL ,
     [Auto_Parameter28] [tinyint] NULL ,
     [Auto_Parameter29] [tinyint] NULL ,
     [Auto_Parameter30] [tinyint] NULL ,
     [Auto_Parameter31] [tinyint] NULL ,
     [Auto_Parameter32] [tinyint] NULL ,
     [Auto_Parameter33] [tinyint] NULL ,
     [Auto_Parameter34] [tinyint] NULL ,
     [Auto_Parameter35] [tinyint] NULL ,
     [Auto_Parameter36] [tinyint] NULL ,
     [Auto_Parameter37] [tinyint] NULL ,
     [Auto_Parameter38] [tinyint] NULL ,
     [Auto_Parameter39] [tinyint] NULL ,
     [Auto_Parameter40] [tinyint] NULL ,
     [Auto_Parameter41] [tinyint] NULL ,
     [Auto_Parameter42] [tinyint] NULL ,
     [Auto_Parameter43] [tinyint] NULL ,
     [Auto_Parameter44] [tinyint] NULL ,
     [Auto_Parameter45] [tinyint] NULL ,
     [Auto_Parameter46] [tinyint] NULL ,
     [Auto_Parameter47] [tinyint] NULL ,
     [Auto_Parameter48] [tinyint] NULL ,
     [Auto_Parameter49] [tinyint] NULL ,
     [Auto_Parameter50] [tinyint] NULL ,
     [Auto_Parameter51] [tinyint] NULL ,
     [Auto_Parameter52] [tinyint] NULL ,
     [Auto_Parameter53] [tinyint] NULL ,
     [Auto_Parameter54] [tinyint] NULL ,
     [Auto_Parameter55] [tinyint] NULL ,
     [Auto_Parameter56] [tinyint] NULL ,
     [Auto_Parameter57] [tinyint] NULL ,
     [Auto_Parameter58] [tinyint] NULL ,
     [Auto_Parameter59] [tinyint] NULL ,
     [Auto_Parameter60] [tinyint] NULL ,
     [Auto_Parameter61] [tinyint] NULL ,
     [Auto_Parameter62] [tinyint] NULL ,
     [Auto_Parameter63] [tinyint] NULL ,
     [Auto_Parameter64] [tinyint] NULL ,
     [Auto_Parameter65] [tinyint] NULL ,
     [Auto_Parameter66] [tinyint] NULL ,
     [Auto_Parameter67] [tinyint] NULL ,
     [Auto_Parameter68] [tinyint] NULL ,
     [Auto_Parameter69] [tinyint] NULL ,
     [Auto_Parameter70] [tinyint] NULL ,
     [Auto_Parameter71] [tinyint] NULL ,
     [Auto_Parameter72] [tinyint] NULL ,
     [Auto_Parameter73] [tinyint] NULL ,
     [Auto_Parameter74] [tinyint] NULL ,
     [Auto_Parameter75] [tinyint] NULL ,
     [Auto_Parameter76] [tinyint] NULL ,
     [Auto_Parameter77] [tinyint] NULL ,
     [Auto_Parameter78] [tinyint] NULL ,
     [Auto_Parameter79] [tinyint] NULL ,
     [Auto_Parameter80] [tinyint] NULL ,
     [Auto_Parameter81] [tinyint] NULL ,
     [Auto_Parameter82] [tinyint] NULL ,
     [Auto_Parameter83] [tinyint] NULL ,
     [Auto_Parameter84] [tinyint] NULL ,
     [Auto_Parameter85] [tinyint] NULL ,
     [Auto_Parameter86] [tinyint] NULL ,
     [Auto_Parameter87] [tinyint] NULL ,
     [Auto_Parameter88] [tinyint] NULL ,
     [Auto_Parameter89] [tinyint] NULL ,
     [Auto_Parameter90] [tinyint] NULL ,
     [Auto_Parameter91] [tinyint] NULL ,
     [Auto_Parameter92] [tinyint] NULL ,
     [Auto_Parameter93] [tinyint] NULL ,
     [Auto_Parameter94] [tinyint] NULL ,
     [Auto_Parameter95] [tinyint] NULL ,
     [Auto_Parameter96] [tinyint] NULL ,
     [Auto_Parameter97] [tinyint] NULL ,
     [Auto_Parameter98] [tinyint] NULL ,
     [Auto_Parameter99] [tinyint] NULL ,
     [Auto_Parameter100] [tinyint] NULL ,
     [Auto_Parameter101] [tinyint] NULL ,
     [Auto_Parameter102] [tinyint] NULL ,
     [Auto_Parameter103] [tinyint] NULL ,
     [Auto_Parameter104] [tinyint] NULL ,
     [Auto_Parameter105] [tinyint] NULL ,
     [Auto_Parameter106] [tinyint] NULL ,
     [Auto_Parameter107] [tinyint] NULL ,
     [Auto_Parameter108] [tinyint] NULL ,
     [Auto_Parameter109] [tinyint] NULL ,
     [Auto_Parameter110] [tinyint] NULL 
) ON [PRIMARY]

GO

-- No primary keys defined on [dbo].[TB_Auto]

GO



--Object: Index: TB_AutoINDEX - Script Date: 2012-4-3 16:05:25
CREATE INDEX [TB_AutoINDEX]
    ON [dbo].[TB_Auto] ([Auto_Parameter1]) ON [PRIMARY]

GO




--Object: Table: dbo.TB_CHANGEAMMETER - Script Date: 2012-4-3 16:05:25
if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[TB_CHANGEAMMETER]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[TB_CHANGEAMMETER]
GO

CREATE TABLE [dbo].[TB_CHANGEAMMETER](
     [CHANGEAMMETER_MODULENOOLD] [bigint] NOT NULL ,
     [CHANGEAMMETER_MODULENO] [bigint] NOT NULL ,
     [CHANGEAMMETER_NOOLD] [char](10) COLLATE Chinese_PRC_CI_AS NULL ,
     [CHANGEAMMETER_NO] [char](16) COLLATE Chinese_PRC_CI_AS NULL ,
     [CHANGEAMMETER_WORKDEGREEOLD] [char](16) COLLATE Chinese_PRC_CI_AS NOT NULL ,
     [CHANGEAMMETER_WORKDEGREE] [float] NOT NULL ,
     [CHANGEAMMETER_WORKDEGREETOTALOLD] [float] NULL ,
     [CHANGEAMMETER_WORKDEGREETOTAL] [float] NULL ,
     [CHANGEAMMETER_LOSEDEGREEOLD] [float] NOT NULL ,
     [CHANGEAMMETER_LOSEDEGREE] [float] NOT NULL ,
     [CHANGEAMMETER_LOSEDEGREETOTALOLD] [float] NULL ,
     [CHANGEAMMETER_LOSEDEGREETOTAL] [float] NULL ,
     [CHANGEAMMETER_JFDLOLD] [float] NOT NULL ,
     [CHANGEAMMETER_JFDL] [float] NOT NULL ,
     [CHANGEAMMETER_FDLOLD] [float] NOT NULL ,
     [CHANGEAMMETER_FDL] [float] NOT NULL ,
     [CHANGEAMMETER_PDLOLD] [float] NOT NULL ,
     [CHANGEAMMETER_PDL] [float] NOT NULL ,
     [CHANGEAMMETER_GDLOLD] [float] NOT NULL ,
     [CHANGEAMMETER_GDL] [float] NOT NULL ,
     [CHANGEAMMETER_UPDATETIME] [datetime] NOT NULL ,
     [CHANGEAMMETER_NAME] [char](20) COLLATE Chinese_PRC_CI_AS NOT NULL 
) ON [PRIMARY]

GO

-- No primary keys defined on [dbo].[TB_CHANGEAMMETER]

GO



--Object: Index: TB_CHANGEAMMETERINDEX - Script Date: 2012-4-3 16:05:26
CREATE INDEX [TB_CHANGEAMMETERINDEX]
    ON [dbo].[TB_CHANGEAMMETER] ([CHANGEAMMETER_MODULENO]) ON [PRIMARY]

GO



--Object: Table: dbo.TB_COMINFORMATION - Script Date: 2012-4-3 16:05:26
if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[TB_COMINFORMATION]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[TB_COMINFORMATION]
GO

CREATE TABLE [dbo].[TB_COMINFORMATION](
     [COMINFORMATION_COM] [smallint] NULL ,
     [COMINFORMATION_BITS] [smallint] NULL ,
     [COMINFORMATION_CHECKBIT] [smallint] NULL ,
     [COMINFORMATION_DATABIT] [smallint] NULL ,
     [COMINFORMATION_STOPBIT] [smallint] NULL ,
     [COMINFORMATION_AUTOREPLY] [tinyint] NULL 
) ON [PRIMARY]

GO

-- No primary keys defined on [dbo].[TB_COMINFORMATION]

GO




--Object: Table: dbo.TB_DateAuto - Script Date: 2012-4-3 16:05:26
if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[TB_DateAuto]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[TB_DateAuto]
GO

CREATE TABLE [dbo].[TB_DateAuto](
     [Auto_Parameter1] [tinyint] NULL ,
     [Auto_Parameter2] [tinyint] NULL ,
     [Auto_Parameter3] [tinyint] NULL ,
     [Auto_Parameter4] [tinyint] NULL ,
     [Auto_Parameter5] [tinyint] NULL ,
     [Auto_Parameter6] [tinyint] NULL ,
     [Auto_Parameter7] [tinyint] NULL ,
     [Auto_Parameter8] [tinyint] NULL ,
     [Auto_Parameter9] [tinyint] NULL ,
     [Auto_Parameter10] [tinyint] NULL ,
     [Auto_Parameter11] [tinyint] NULL ,
     [Auto_Parameter12] [tinyint] NULL ,
     [Auto_Parameter13] [tinyint] NULL ,
     [Auto_Parameter14] [tinyint] NULL ,
     [Auto_Parameter15] [tinyint] NULL ,
     [Auto_Parameter16] [tinyint] NULL ,
     [Auto_Parameter17] [tinyint] NULL ,
     [Auto_Parameter18] [tinyint] NULL ,
     [Auto_Parameter19] [tinyint] NULL ,
     [Auto_Parameter20] [tinyint] NULL ,
     [Auto_Parameter21] [tinyint] NULL ,
     [Auto_Parameter22] [tinyint] NULL ,
     [Auto_Parameter23] [tinyint] NULL ,
     [Auto_Parameter24] [tinyint] NULL ,
     [Auto_Parameter25] [tinyint] NULL ,
     [Auto_Parameter26] [tinyint] NULL ,
     [Auto_Parameter27] [tinyint] NULL ,
     [Auto_Parameter28] [tinyint] NULL ,
     [Auto_Parameter29] [tinyint] NULL ,
     [Auto_Parameter30] [tinyint] NULL ,
     [Auto_Parameter31] [tinyint] NULL ,
     [Auto_Parameter32] [tinyint] NULL ,
     [Auto_Parameter33] [tinyint] NULL ,
     [Auto_Parameter34] [tinyint] NULL ,
     [Auto_Parameter35] [tinyint] NULL ,
     [Auto_Parameter36] [tinyint] NULL ,
     [Auto_Parameter37] [tinyint] NULL ,
     [Auto_Parameter38] [tinyint] NULL ,
     [Auto_Parameter39] [tinyint] NULL ,
     [Auto_Parameter40] [tinyint] NULL ,
     [Auto_Parameter41] [tinyint] NULL ,
     [Auto_Parameter42] [tinyint] NULL ,
     [Auto_Parameter43] [tinyint] NULL ,
     [Auto_Parameter44] [tinyint] NULL ,
     [Auto_Parameter45] [tinyint] NULL ,
     [Auto_Parameter46] [tinyint] NULL ,
     [Auto_Parameter47] [tinyint] NULL ,
     [Auto_Parameter48] [tinyint] NULL ,
     [Auto_Parameter49] [tinyint] NULL ,
     [Auto_Parameter50] [tinyint] NULL ,
     [Auto_Parameter51] [tinyint] NULL ,
     [Auto_Parameter52] [tinyint] NULL ,
     [Auto_Parameter53] [tinyint] NULL ,
     [Auto_Parameter54] [tinyint] NULL ,
     [Auto_Parameter55] [tinyint] NULL ,
     [Auto_Parameter56] [tinyint] NULL ,
     [Auto_Parameter57] [tinyint] NULL ,
     [Auto_Parameter58] [tinyint] NULL ,
     [Auto_Parameter59] [tinyint] NULL ,
     [Auto_Parameter60] [tinyint] NULL ,
     [Auto_Parameter61] [tinyint] NULL ,
     [Auto_Parameter62] [tinyint] NULL ,
     [Auto_Parameter63] [tinyint] NULL ,
     [Auto_Parameter64] [tinyint] NULL ,
     [Auto_Parameter65] [tinyint] NULL ,
     [Auto_Parameter66] [tinyint] NULL ,
     [Auto_Parameter67] [tinyint] NULL 
) ON [PRIMARY]

GO

-- No primary keys defined on [dbo].[TB_DateAuto]

GO



--Object: Index: TB_DateAutoINDEX - Script Date: 2012-4-3 16:05:26
CREATE INDEX [TB_DateAutoINDEX]
    ON [dbo].[TB_DateAuto] ([Auto_Parameter1]) ON [PRIMARY]

GO




--Object: Table: dbo.TB_DWELLERACCOUNT - Script Date: 2012-4-3 16:05:26
if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[TB_DWELLERACCOUNT]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[TB_DWELLERACCOUNT]
GO

CREATE TABLE [dbo].[TB_DWELLERACCOUNT](
     [用户号] [char](12) COLLATE Chinese_PRC_CI_AS NULL ,
     [用户名] [char](40) COLLATE Chinese_PRC_CI_AS NULL ,
     [表号] [char](15) COLLATE Chinese_PRC_CI_AS NULL ,
     [上月指针] [float] NULL ,
     [本月指针] [float] NULL ,
     [电量] [float] NULL ,
     [优待电量] [float] NULL ,
     [优待电费] [float] NULL ,
     [电价] [float] NULL ,
     [合计] [float] NULL 
) ON [PRIMARY]

GO

-- No primary keys defined on [dbo].[TB_DWELLERACCOUNT]

GO




--Object: Table: dbo.TB_ELECTRICITY - Script Date: 2012-4-3 16:05:26
if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[TB_ELECTRICITY]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[TB_ELECTRICITY]
GO

CREATE TABLE [dbo].[TB_ELECTRICITY](
     [ELECTRICITY_NO] [tinyint] NOT NULL ,
     [ELECTRICITY_KIND] [char](16) COLLATE Chinese_PRC_CI_AS NOT NULL ,
     [ELECTRICITY_PRICE] [float] NOT NULL ,
     [ELECTRICITY_REMARK] [char](30) COLLATE Chinese_PRC_CI_AS NULL 
) ON [PRIMARY]

GO

ALTER TABLE [dbo].[TB_ELECTRICITY] WITH NOCHECK
    ADD CONSTRAINT [PK__TB_ELECTRICITY__7849DB76] 
    PRIMARY KEY (ELECTRICITY_NO)
    ON [PRIMARY]

GO




--Object: Table: dbo.TB_ELECTRICITYLOSS - Script Date: 2012-4-3 16:05:26
if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[TB_ELECTRICITYLOSS]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[TB_ELECTRICITYLOSS]
GO

CREATE TABLE [dbo].[TB_ELECTRICITYLOSS](
     [变台名称] [char](26) COLLATE Chinese_PRC_CI_AS NULL ,
     [容量] [int] NULL ,
     [户数] [int] NULL ,
     [本月供电量] [float] NULL ,
     [本月售电量] [float] NULL ,
     [损失电量] [float] NULL ,
     [线损率] [float] NULL 
) ON [PRIMARY]

GO

-- No primary keys defined on [dbo].[TB_ELECTRICITYLOSS]

GO




--Object: Table: dbo.TB_ELECTRICITYTOTAL - Script Date: 2012-4-3 16:05:26
if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[TB_ELECTRICITYTOTAL]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[TB_ELECTRICITYTOTAL]
GO

CREATE TABLE [dbo].[TB_ELECTRICITYTOTAL](
     [变台名称] [char](20) COLLATE Chinese_PRC_CI_AS NULL ,
     [电能表编号] [char](15) COLLATE Chinese_PRC_CI_AS NULL ,
     [上月读数] [float] NULL ,
     [本月读数] [float] NULL ,
     [倍率] [int] NULL ,
     [电量] [float] NULL 
) ON [PRIMARY]

GO

-- No primary keys defined on [dbo].[TB_ELECTRICITYTOTAL]

GO




--Object: Table: dbo.TB_EXCERPTION - Script Date: 2012-4-3 16:05:26
if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[TB_EXCERPTION]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[TB_EXCERPTION]
GO

CREATE TABLE [dbo].[TB_EXCERPTION](
     [变台名称] [char](40) COLLATE Chinese_PRC_CI_AS NULL ,
     [用户编号] [char](10) COLLATE Chinese_PRC_CI_AS NULL ,
     [姓名] [char](40) COLLATE Chinese_PRC_CI_AS NULL ,
     [原户号] [char](10) COLLATE Chinese_PRC_CI_AS NULL ,
     [模块号] [bigint] NULL ,
     [计量表编号] [char](15) COLLATE Chinese_PRC_CI_AS NULL ,
     [用电类别] [char](30) COLLATE Chinese_PRC_CI_AS NULL ,
     [类型] [char](10) COLLATE Chinese_PRC_CI_AS NULL ,
     [上次读数] [float] NULL ,
     [本次读数] [float] NULL ,
     [倍率] [int] NULL ,
     [电量] [float] NULL ,
     [电价] [float] NULL ,
     [金额] [float] NULL 
) ON [PRIMARY]

GO

-- No primary keys defined on [dbo].[TB_EXCERPTION]

GO




--Object: Table: dbo.TB_GARRISON - Script Date: 2012-4-3 16:05:27
if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[TB_GARRISON]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[TB_GARRISON]
GO

CREATE TABLE [dbo].[TB_GARRISON](
     [GARRISON_MODULENO] [bigint] NOT NULL ,
     [GARRISON_WORKDEGREE] [float] NULL ,
     [GARRISON_WORKDEGREETOTAL] [float] NULL ,
     [GARRISON_LOSEDEGREE] [float] NULL ,
     [GARRISON_LOSEDEGREETOTAL] [float] NULL ,
     [GARRISON_ACURRENT] [float] NULL ,
     [GARRISON_BCURRENT] [float] NULL ,
     [GARRISON_CCURRENT] [float] NULL ,
     [GARRISON_AVOLTAGE] [float] NULL ,
     [GARRISON_BVOLTAGE] [float] NULL ,
     [GARRISON_CVOLTAGE] [float] NULL ,
     [GARRISON_JFDL] [float] NULL ,
     [GARRISON_FDL] [float] NULL ,
     [GARRISON_PDL] [float] NULL ,
     [GARRISON_GDL] [float] NULL ,
     [GARRISON_GLYS] [float] NULL ,
     [GARRISON_TRANSCRIBETIME] [char](19) COLLATE Chinese_PRC_CI_AS NULL ,
     [GARRISON_PROTOCOL] [smallint] NOT NULL ,
     [GARRISON_HALTTIME] [char](19) COLLATE Chinese_PRC_CI_AS NULL 
) ON [PRIMARY]

GO

-- No primary keys defined on [dbo].[TB_GARRISON]

GO



--Object: Index: TB_GARRISONINDEX - Script Date: 2012-4-3 16:05:27
CREATE INDEX [TB_GARRISONINDEX]
    ON [dbo].[TB_GARRISON] ([GARRISON_MODULENO]) ON [PRIMARY]

GO


--Object: Index: TB_GARRISONINDEX - Script Date: 2012-4-3 16:05:27
CREATE INDEX [TB_GARRISONINDEX]
    ON [dbo].[TB_GARRISON] ([GARRISON_MODULENO]) ON [PRIMARY]

GO

--Object: Table: dbo.TB_GARRISONBAK - Script Date: 2012-4-3 16:05:27
if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[TB_GARRISONBAK]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[TB_GARRISONBAK]
GO

CREATE TABLE [dbo].[TB_GARRISONBAK](
     [GARRISON_MODULENO] [bigint] NOT NULL ,
     [GARRISON_WORKDEGREE] [float] NULL ,
     [GARRISON_WORKDEGREETOTAL] [float] NULL ,
     [GARRISON_LOSEDEGREE] [float] NULL ,
     [GARRISON_LOSEDEGREETOTAL] [float] NULL ,
     [GARRISON_ACURRENT] [float] NULL ,
     [GARRISON_BCURRENT] [float] NULL ,
     [GARRISON_CCURRENT] [float] NULL ,
     [GARRISON_AVOLTAGE] [float] NULL ,
     [GARRISON_BVOLTAGE] [float] NULL ,
     [GARRISON_CVOLTAGE] [float] NULL ,
     [GARRISON_JFDL] [float] NULL ,
     [GARRISON_FDL] [float] NULL ,
     [GARRISON_PDL] [float] NULL ,
     [GARRISON_GDL] [float] NULL ,
     [GARRISON_GLYS] [float] NULL ,
     [GARRISON_TRANSCRIBETIME] [char](19) COLLATE Chinese_PRC_CI_AS NULL ,
     [GARRISON_PROTOCOL] [smallint] NOT NULL ,
     [GARRISON_HALTTIME] [char](19) COLLATE Chinese_PRC_CI_AS NULL 
) ON [PRIMARY]

GO

-- No primary keys defined on [dbo].[TB_GARRISONBAK]

GO




--Object: Table: dbo.TB_HALTTIME - Script Date: 2012-4-3 16:05:27
if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[TB_HALTTIME]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[TB_HALTTIME]
GO

CREATE TABLE [dbo].[TB_HALTTIME](
     [HALTTIME_TIME] [char](19) COLLATE Chinese_PRC_CI_AS NOT NULL 
) ON [PRIMARY]

GO

-- No primary keys defined on [dbo].[TB_HALTTIME]

GO



--Object: Index: TB_HALTTIMEINDEX - Script Date: 2012-4-3 16:05:27
CREATE INDEX [TB_HALTTIMEINDEX]
    ON [dbo].[TB_HALTTIME] ([HALTTIME_TIME]) ON [PRIMARY]

GO



--Object: Table: dbo.TB_HAND - Script Date: 2012-4-3 16:05:27
if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[TB_HAND]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[TB_HAND]
GO

CREATE TABLE [dbo].[TB_HAND](
     [HAND_NO] [tinyint] NULL ,
     [HAND_STATIONNAME] [char](30) COLLATE Chinese_PRC_CI_AS NULL ,
     [HAND_STATUS] [tinyint] NULL 
) ON [PRIMARY]

GO

-- No primary keys defined on [dbo].[TB_HAND]

GO



--Object: Index: TB_HANDINDEX - Script Date: 2012-4-3 16:05:27
CREATE INDEX [TB_HANDINDEX]
    ON [dbo].[TB_HAND] ([HAND_NO]) ON [PRIMARY]

GO


--Object: Index: TB_HANDINDEX - Script Date: 2012-4-3 16:05:27
CREATE INDEX [TB_HANDINDEX]
    ON [dbo].[TB_HAND] ([HAND_NO]) ON [PRIMARY]

GO

--Object: Table: dbo.TB_IP - Script Date: 2012-4-3 16:05:27
if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[TB_IP]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[TB_IP]
GO

CREATE TABLE [dbo].[TB_IP](
     [IP_ADDRESS] [char](15) COLLATE Chinese_PRC_CI_AS NULL ,
     [IP_COMPUTER] [char](30) COLLATE Chinese_PRC_CI_AS NULL 
) ON [PRIMARY]

GO

-- No primary keys defined on [dbo].[TB_IP]

GO




--Object: Table: dbo.TB_LINEERROR - Script Date: 2012-4-3 16:05:27
if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[TB_LINEERROR]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[TB_LINEERROR]
GO

CREATE TABLE [dbo].[TB_LINEERROR](
     [LINEERROR_MODULE] [bigint] NULL ,
     [LINEERROR_READTIME] [char](19) COLLATE Chinese_PRC_CI_AS NULL ,
     [LINEERROR_HALTTIME] [char](19) COLLATE Chinese_PRC_CI_AS NULL ,
     [LINEERROR_KINDS] [tinyint] NULL 
) ON [PRIMARY]

GO

-- No primary keys defined on [dbo].[TB_LINEERROR]

GO




--Object: Table: dbo.TB_PHONE - Script Date: 2012-4-3 16:05:28
if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[TB_PHONE]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[TB_PHONE]
GO

CREATE TABLE [dbo].[TB_PHONE](
     [PHONE_NO] [char](16) COLLATE Chinese_PRC_CI_AS NULL ,
     [PHONE_NAME] [char](20) COLLATE Chinese_PRC_CI_AS NULL ,
     [PHONE_PASSWORD] [varchar](8) COLLATE Chinese_PRC_CI_AS NULL 
) ON [PRIMARY]

GO

-- No primary keys defined on [dbo].[TB_PHONE]

GO




--Object: Table: dbo.TB_REALTIME - Script Date: 2012-4-3 16:05:28
if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[TB_REALTIME]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[TB_REALTIME]
GO

CREATE TABLE [dbo].[TB_REALTIME](
     [REALTIME_MODULENO] [bigint] NOT NULL ,
     [REALTIME_WORKDEGREE] [float] NULL ,
     [REALTIME_WORKDEGREETOTAL] [float] NULL ,
     [REALTIME_LOSEDEGREE] [float] NULL ,
     [REALTIME_LOSEDEGREETOTAL] [float] NULL ,
     [REALTIME_ACURRENT] [float] NULL ,
     [REALTIME_BCURRENT] [float] NULL ,
     [REALTIME_CCURRENT] [float] NULL ,
     [REALTIME_AVOLTAGE] [float] NULL ,
     [REALTIME_BVOLTAGE] [float] NULL ,
     [REALTIME_CVOLTAGE] [float] NULL ,
     [REALTIME_JFDL] [float] NULL ,
     [REALTIME_FDL] [float] NULL ,
     [REALTIME_PDL] [float] NULL ,
     [REALTIME_GDL] [float] NULL ,
     [REALTIME_GLYS] [float] NULL ,
     [REALTIME_TRANSCRIBETIME] [char](19) COLLATE Chinese_PRC_CI_AS NULL ,
     [REALTIME_PROTOCOL] [smallint] NOT NULL 
) ON [PRIMARY]

GO

-- No primary keys defined on [dbo].[TB_REALTIME]

GO



--Object: Index: TB_REALTIMEINDEX - Script Date: 2012-4-3 16:05:28
CREATE INDEX [TB_REALTIMEINDEX]
    ON [dbo].[TB_REALTIME] ([REALTIME_MODULENO]) ON [PRIMARY]

GO


--Object: Index: TB_REALTIMEINDEX - Script Date: 2012-4-3 16:05:28
CREATE INDEX [TB_REALTIMEINDEX]
    ON [dbo].[TB_REALTIME] ([REALTIME_MODULENO]) ON [PRIMARY]

GO

--Object: Table: dbo.TB_REFRESHTIME - Script Date: 2012-4-3 16:05:28
if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[TB_REFRESHTIME]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[TB_REFRESHTIME]
GO

CREATE TABLE [dbo].[TB_REFRESHTIME](
     [USER_REFRESHTIME] [char](19) COLLATE Chinese_PRC_CI_AS NOT NULL 
) ON [PRIMARY]

GO

-- No primary keys defined on [dbo].[TB_REFRESHTIME]

GO



--Object: Index: TB_REFRESHTIMEINDEX - Script Date: 2012-4-3 16:05:28
CREATE INDEX [TB_REFRESHTIMEINDEX]
    ON [dbo].[TB_REFRESHTIME] ([USER_REFRESHTIME]) ON [PRIMARY]

GO


--Object: Index: TB_REFRESHTIMEINDEX - Script Date: 2012-4-3 16:05:28
CREATE INDEX [TB_REFRESHTIMEINDEX]
    ON [dbo].[TB_REFRESHTIME] ([USER_REFRESHTIME]) ON [PRIMARY]

GO

--Object: Table: dbo.TB_TOTAL - Script Date: 2012-4-3 16:05:28
if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[TB_TOTAL]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[TB_TOTAL]
GO

CREATE TABLE [dbo].[TB_TOTAL](
     [变台名称] [char](40) COLLATE Chinese_PRC_CI_AS NULL ,
     [用户编号] [char](10) COLLATE Chinese_PRC_CI_AS NULL ,
     [用户姓名] [char](40) COLLATE Chinese_PRC_CI_AS NULL ,
     [原用户编号] [char](10) COLLATE Chinese_PRC_CI_AS NULL ,
     [模块号] [bigint] NULL ,
     [倍率] [int] NULL ,
     [用电名称] [char](16) COLLATE Chinese_PRC_CI_AS NULL ,
     [上次有功] [float] NULL ,
     [本次有功] [float] NULL ,
     [有功差值] [float] NULL ,
     [上次无功] [float] NULL ,
     [本次无功] [float] NULL ,
     [无功差值] [float] NULL 
) ON [PRIMARY]

GO

-- No primary keys defined on [dbo].[TB_TOTAL]

GO




--Object: Table: dbo.TB_TRANSFORMER - Script Date: 2012-4-3 16:05:28
if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[TB_TRANSFORMER]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[TB_TRANSFORMER]
GO

CREATE TABLE [dbo].[TB_TRANSFORMER](
     [TRANSFORMER_NO] [char](40) COLLATE Chinese_PRC_CI_AS NOT NULL ,
     [TRANSFORMER_TYPE] [char](10) COLLATE Chinese_PRC_CI_AS NULL ,
     [TRANSFORMER_CAPACITY] [int] NULL ,
     [TRANSFORMER_INSTALLTIME] [datetime] NULL ,
     [TRANSFORMER_POSITION] [char](30) COLLATE Chinese_PRC_CI_AS NULL ,
     [TRANSFORMER_OWNERSHIP] [char](10) COLLATE Chinese_PRC_CI_AS NULL ,
     [TRANSFORMER_CONNECTFORM] [tinyint] NULL 
) ON [PRIMARY]

GO

-- No primary keys defined on [dbo].[TB_TRANSFORMER]

GO



--Object: Index: TB_TRANSFORMERINDEX - Script Date: 2012-4-3 16:05:28
CREATE INDEX [TB_TRANSFORMERINDEX]
    ON [dbo].[TB_TRANSFORMER] ([TRANSFORMER_NO]) ON [PRIMARY]

GO



--Object: Table: dbo.TB_TRANSFORMERTMP - Script Date: 2012-4-3 16:05:28
if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[TB_TRANSFORMERTMP]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[TB_TRANSFORMERTMP]
GO

CREATE TABLE [dbo].[TB_TRANSFORMERTMP](
     [TRANSFORMER_NO] [char](40) COLLATE Chinese_PRC_CI_AS NOT NULL ,
     [TRANSFORMER_TYPE] [char](10) COLLATE Chinese_PRC_CI_AS NULL ,
     [TRANSFORMER_CAPACITY] [int] NULL ,
     [TRANSFORMER_INSTALLTIME] [datetime] NULL ,
     [TRANSFORMER_POSITION] [char](30) COLLATE Chinese_PRC_CI_AS NULL ,
     [TRANSFORMER_OWNERSHIP] [char](10) COLLATE Chinese_PRC_CI_AS NULL ,
     [TRANSFORMER_CONNECTFORM] [tinyint] NULL 
) ON [PRIMARY]

GO

-- No primary keys defined on [dbo].[TB_TRANSFORMERTMP]

GO




--Object: Table: dbo.TB_USER - Script Date: 2012-4-3 16:05:28
if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[TB_USER]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[TB_USER]
GO

CREATE TABLE [dbo].[TB_USER](
     [USER_COMPANY] [char](30) COLLATE Chinese_PRC_CI_AS NULL ,
     [USER_STATIONNO] [char](5) COLLATE Chinese_PRC_CI_AS NULL ,
     [USER_STATIONNAME] [char](20) COLLATE Chinese_PRC_CI_AS NULL ,
     [USER_MOTHERLINE] [int] NULL ,
     [USER_BAKMOTHERLINE] [int] NULL ,
     [USER_LINENO] [int] NULL ,
     [USER_BAKLINENO] [int] NULL ,
     [USER_LINENAME] [char](20) COLLATE Chinese_PRC_CI_AS NULL ,
     [USER_TRANSFORMERNO] [char](40) COLLATE Chinese_PRC_CI_AS NULL ,
     [USER_MODULENO] [bigint] NOT NULL ,
     [USER_PHASE] [tinyint] NULL ,
     [USER_NAME] [char](40) COLLATE Chinese_PRC_CI_AS NULL ,
     [USER_NO] [char](10) COLLATE Chinese_PRC_CI_AS NULL ,
     [USER_OLDNO] [char](10) COLLATE Chinese_PRC_CI_AS NULL ,
     [USER_ADDRESS] [char](60) COLLATE Chinese_PRC_CI_AS NULL ,
     [USER_PHONE] [char](60) COLLATE Chinese_PRC_CI_AS NULL ,
     [USER_ELECTRICITYKIND] [tinyint] NULL ,
     [USER_AMMETERNO] [char](16) COLLATE Chinese_PRC_CI_AS NULL ,
     [USER_AMMETERKIND] [tinyint] NULL ,
     [USER_INSTALLTIME] [datetime] NULL ,
     [USER_SUPPLYMODE] [tinyint] NULL ,
     [USER_INITIALVALUE] [float] NULL ,
     [USER_MULTIPLE] [int] NULL ,
     [USER_PROTOCOL] [tinyint] NULL ,
     [USER_DESCRIBE] [char](60) COLLATE Chinese_PRC_CI_AS NULL ,
     [USER_READLABEL] [char](15) COLLATE Chinese_PRC_CI_AS NULL ,
     [USER_TIMELABEL] [char](15) COLLATE Chinese_PRC_CI_AS NULL ,
     [USER_ETSTATUS] [char](12) COLLATE Chinese_PRC_CI_AS NULL ,
     [USER_IDNO] [int] NULL ,
     [USER_AMMETERTYPE] [varchar](10) COLLATE Chinese_PRC_CI_AS NULL ,
     [USER_SENDANGLE] [tinyint] NULL ,
     [USER_DOWNVALUE] [int] NULL ,
     [USER_UPVALUE] [int] NULL ,
     [USER_RUNSTATUS] [tinyint] NULL ,
     [USER_ZHULABEL] [char](93) COLLATE Chinese_PRC_CI_AS NULL ,
     [USER_BILLNO] [char](30) COLLATE Chinese_PRC_CI_AS NULL 
) ON [PRIMARY]

GO

-- No primary keys defined on [dbo].[TB_USER]

GO



--Object: Index: TB_USERINDEX - Script Date: 2012-4-3 16:05:29
CREATE INDEX [TB_USERINDEX]
    ON [dbo].[TB_USER] ([USER_MODULENO]) ON [PRIMARY]

GO


--Object: Index: TB_USERINDEX - Script Date: 2012-4-3 16:05:29
CREATE INDEX [TB_USERINDEX]
    ON [dbo].[TB_USER] ([USER_MODULENO]) ON [PRIMARY]

GO

--Object: Table: dbo.TB_WGUPDOWN - Script Date: 2012-4-3 16:05:29
if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[TB_WGUPDOWN]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[TB_WGUPDOWN]
GO

CREATE TABLE [dbo].[TB_WGUPDOWN](
     [WGUPDOWN_UP] [int] NOT NULL ,
     [WGUPDOWN_DOWN] [int] NOT NULL ,
     [WGUPDOWN_EVERYTIME] [smallint] NULL 
) ON [PRIMARY]

GO

-- No primary keys defined on [dbo].[TB_WGUPDOWN]

GO




--Object: Table: dbo.TB_WUGONG - Script Date: 2012-4-3 16:05:29
if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[TB_WUGONG]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[TB_WUGONG]
GO

CREATE TABLE [dbo].[TB_WUGONG](
     [WUGONG_MODULE] [bigint] NOT NULL ,
     [WUGONG_SPACE] [int] NOT NULL 
) ON [PRIMARY]

GO

-- No primary keys defined on [dbo].[TB_WUGONG]

GO




--Object: Table: dbo.TB_ZXACCOUNT - Script Date: 2012-4-3 16:05:29
if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[TB_ZXACCOUNT]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[TB_ZXACCOUNT]
GO

CREATE TABLE [dbo].[TB_ZXACCOUNT](
     [用户号] [char](10) COLLATE Chinese_PRC_CI_AS NULL ,
     [用户名] [char](40) COLLATE Chinese_PRC_CI_AS NULL ,
     [电量合计] [float] NULL ,
     [电费合计] [float] NULL ,
     [表计号] [char](10) COLLATE Chinese_PRC_CI_AS NULL ,
     [安装类型] [char](10) COLLATE Chinese_PRC_CI_AS NULL ,
     [电费类别] [char](10) COLLATE Chinese_PRC_CI_AS NULL ,
     [表计倍率] [int] NULL ,
     [上月表码] [float] NULL ,
     [本月表码] [float] NULL ,
     [表计电量] [float] NULL ,
     [分类项目] [char](20) COLLATE Chinese_PRC_CI_AS NULL ,
     [电量] [float] NULL ,
     [电价] [float] NULL ,
     [电费] [float] NULL ,
     [税金] [float] NULL ,
     [合计] [float] NULL 
) ON [PRIMARY]

GO

-- No primary keys defined on [dbo].[TB_ZXACCOUNT]

GO



