USE [qq]
GO
/****** Object:  Table [dbo].[usermessage]    Script Date: 04/09/2015 19:26:27 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[usermessage](
	[qq] [char](10) NOT NULL,
	[nickname] [varchar](10) NOT NULL,
	[realname] [varchar](10) NULL,
	[age] [tinyint] NULL,
	[sex] [tinyint] NULL,
 CONSTRAINT [IX_usermessage] UNIQUE NONCLUSTERED 
(
	[qq] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[user]    Script Date: 04/09/2015 19:26:27 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[user](
	[qq] [char](10) NOT NULL,
	[pass] [varchar](20) NOT NULL,
 CONSTRAINT [PK_user] PRIMARY KEY CLUSTERED 
(
	[qq] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[messagetable]    Script Date: 04/09/2015 19:26:27 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[messagetable](
	[sender] [char](10) NOT NULL,
	[receiver] [char](10) NOT NULL,
	[mid] [bigint] IDENTITY(1,1) NOT NULL,
	[classid] [tinyint] NULL,
	[message] [varchar](max) NULL,
	[messagetime] [datetime] NOT NULL,
	[status] [tinyint] NOT NULL,
 CONSTRAINT [PK_messagetable] PRIMARY KEY CLUSTERED 
(
	[mid] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[friend]    Script Date: 04/09/2015 19:26:27 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[friend](
	[me] [char](10) NOT NULL,
	[groupid] [smallint] NOT NULL,
	[groupname] [char](10) NOT NULL,
	[you] [char](10) NOT NULL
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Default [DF_messagetable_messagetime]    Script Date: 04/09/2015 19:26:27 ******/
ALTER TABLE [dbo].[messagetable] ADD  CONSTRAINT [DF_messagetable_messagetime]  DEFAULT (getdate()) FOR [messagetime]
GO
