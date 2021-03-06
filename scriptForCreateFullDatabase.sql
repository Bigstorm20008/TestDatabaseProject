USE [master]
GO
/****** Object:  Database [Malinka]    Script Date: 04.02.2018 19:28:34 ******/
CREATE DATABASE [Malinka]
 CONTAINMENT = NONE
 ON  PRIMARY 
( NAME = N'Malinka', FILENAME = N'C:\Program Files\Microsoft SQL Server\MSSQL14.MSSQLSERVER\MSSQL\DATA\Malinka.mdf' , SIZE = 73728KB , MAXSIZE = UNLIMITED, FILEGROWTH = 65536KB )
 LOG ON 
( NAME = N'Malinka_log', FILENAME = N'C:\Program Files\Microsoft SQL Server\MSSQL14.MSSQLSERVER\MSSQL\DATA\Malinka_log.ldf' , SIZE = 532480KB , MAXSIZE = 2048GB , FILEGROWTH = 65536KB )
GO
ALTER DATABASE [Malinka] SET COMPATIBILITY_LEVEL = 140
GO
IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled'))
begin
EXEC [Malinka].[dbo].[sp_fulltext_database] @action = 'enable'
end
GO
ALTER DATABASE [Malinka] SET ANSI_NULL_DEFAULT OFF 
GO
ALTER DATABASE [Malinka] SET ANSI_NULLS OFF 
GO
ALTER DATABASE [Malinka] SET ANSI_PADDING OFF 
GO
ALTER DATABASE [Malinka] SET ANSI_WARNINGS OFF 
GO
ALTER DATABASE [Malinka] SET ARITHABORT OFF 
GO
ALTER DATABASE [Malinka] SET AUTO_CLOSE OFF 
GO
ALTER DATABASE [Malinka] SET AUTO_SHRINK OFF 
GO
ALTER DATABASE [Malinka] SET AUTO_UPDATE_STATISTICS ON 
GO
ALTER DATABASE [Malinka] SET CURSOR_CLOSE_ON_COMMIT OFF 
GO
ALTER DATABASE [Malinka] SET CURSOR_DEFAULT  GLOBAL 
GO
ALTER DATABASE [Malinka] SET CONCAT_NULL_YIELDS_NULL OFF 
GO
ALTER DATABASE [Malinka] SET NUMERIC_ROUNDABORT OFF 
GO
ALTER DATABASE [Malinka] SET QUOTED_IDENTIFIER OFF 
GO
ALTER DATABASE [Malinka] SET RECURSIVE_TRIGGERS OFF 
GO
ALTER DATABASE [Malinka] SET  DISABLE_BROKER 
GO
ALTER DATABASE [Malinka] SET AUTO_UPDATE_STATISTICS_ASYNC OFF 
GO
ALTER DATABASE [Malinka] SET DATE_CORRELATION_OPTIMIZATION OFF 
GO
ALTER DATABASE [Malinka] SET TRUSTWORTHY OFF 
GO
ALTER DATABASE [Malinka] SET ALLOW_SNAPSHOT_ISOLATION OFF 
GO
ALTER DATABASE [Malinka] SET PARAMETERIZATION SIMPLE 
GO
ALTER DATABASE [Malinka] SET READ_COMMITTED_SNAPSHOT OFF 
GO
ALTER DATABASE [Malinka] SET HONOR_BROKER_PRIORITY OFF 
GO
ALTER DATABASE [Malinka] SET RECOVERY FULL 
GO
ALTER DATABASE [Malinka] SET  MULTI_USER 
GO
ALTER DATABASE [Malinka] SET PAGE_VERIFY CHECKSUM  
GO
ALTER DATABASE [Malinka] SET DB_CHAINING OFF 
GO
ALTER DATABASE [Malinka] SET FILESTREAM( NON_TRANSACTED_ACCESS = OFF ) 
GO
ALTER DATABASE [Malinka] SET TARGET_RECOVERY_TIME = 60 SECONDS 
GO
ALTER DATABASE [Malinka] SET DELAYED_DURABILITY = DISABLED 
GO
EXEC sys.sp_db_vardecimal_storage_format N'Malinka', N'ON'
GO
ALTER DATABASE [Malinka] SET QUERY_STORE = OFF
GO
USE [Malinka]
GO
ALTER DATABASE SCOPED CONFIGURATION SET IDENTITY_CACHE = ON;
GO
ALTER DATABASE SCOPED CONFIGURATION SET LEGACY_CARDINALITY_ESTIMATION = OFF;
GO
ALTER DATABASE SCOPED CONFIGURATION FOR SECONDARY SET LEGACY_CARDINALITY_ESTIMATION = PRIMARY;
GO
ALTER DATABASE SCOPED CONFIGURATION SET MAXDOP = 0;
GO
ALTER DATABASE SCOPED CONFIGURATION FOR SECONDARY SET MAXDOP = PRIMARY;
GO
ALTER DATABASE SCOPED CONFIGURATION SET PARAMETER_SNIFFING = ON;
GO
ALTER DATABASE SCOPED CONFIGURATION FOR SECONDARY SET PARAMETER_SNIFFING = PRIMARY;
GO
ALTER DATABASE SCOPED CONFIGURATION SET QUERY_OPTIMIZER_HOTFIXES = OFF;
GO
ALTER DATABASE SCOPED CONFIGURATION FOR SECONDARY SET QUERY_OPTIMIZER_HOTFIXES = PRIMARY;
GO
USE [Malinka]
GO
/****** Object:  User [Zhmenka]    Script Date: 04.02.2018 19:28:34 ******/
CREATE USER [Zhmenka] FOR LOGIN [Zhmenka] WITH DEFAULT_SCHEMA=[dbo]
GO
/****** Object:  DatabaseRole [CashDesk]    Script Date: 04.02.2018 19:28:34 ******/
CREATE ROLE [CashDesk]
GO
ALTER ROLE [CashDesk] ADD MEMBER [Zhmenka]
GO
/****** Object:  Schema [Security]    Script Date: 04.02.2018 19:28:34 ******/
CREATE SCHEMA [Security]
GO
/****** Object:  Table [dbo].[AllCashIn]    Script Date: 04.02.2018 19:28:34 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[AllCashIn](
	[ClientID] [smallint] NOT NULL,
	[CashInDate] [date] NOT NULL,
	[CashinTime] [time](3) NOT NULL,
	[CashInValue] [int] NOT NULL
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[AllCashOut]    Script Date: 04.02.2018 19:28:34 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[AllCashOut](
	[ClientID] [smallint] NOT NULL,
	[CashOutDate] [date] NOT NULL,
	[CashOutTime] [time](3) NOT NULL,
	[CashOutValue] [int] NOT NULL
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[CasinoStatus]    Script Date: 04.02.2018 19:28:34 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[CasinoStatus](
	[CasinoState] [bit] NOT NULL,
	[DateInCasino] [date] NOT NULL
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Clients]    Script Date: 04.02.2018 19:28:35 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Clients](
	[Nickname] [nvarchar](20) NOT NULL,
	[Фамилия] [nvarchar](20) NULL,
	[Имя] [nvarchar](20) NULL,
	[Отчество] [nvarchar](20) NULL,
	[ImageLocation] [nvarchar](150) NULL,
	[Дата рождения] [date] NULL,
	[Статус] [tinyint] NULL,
	[ClientID] [smallint] IDENTITY(1,1) NOT NULL,
	[ClientState] [bit] NULL,
	[LastVisit] [date] NULL,
	[AdditionalInfoAboutClient] [nvarchar](250) NULL,
 CONSTRAINT [PK_Clients] PRIMARY KEY CLUSTERED 
(
	[ClientID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[ClientsPhoneNumbers]    Script Date: 04.02.2018 19:28:35 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ClientsPhoneNumbers](
	[ClientID] [smallint] NOT NULL,
	[PhoneNumber] [nchar](10) NOT NULL
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Drop]    Script Date: 04.02.2018 19:28:35 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Drop](
	[ClientID] [smallint] NOT NULL,
	[DropValue] [numeric](18, 2) NOT NULL,
	[DropDate] [date] NOT NULL
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Employees]    Script Date: 04.02.2018 19:28:35 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Employees](
	[EmployeeID] [tinyint] NOT NULL,
	[Lastname] [nvarchar](20) NOT NULL,
	[Firstname] [nvarchar](20) NOT NULL,
	[Patronymicname] [nvarchar](20) NOT NULL,
	[PostID] [tinyint] NOT NULL,
	[ImageLocation] [nvarchar](150) NULL,
 CONSTRAINT [PK_Employees] PRIMARY KEY CLUSTERED 
(
	[EmployeeID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[ExchangeRates]    Script Date: 04.02.2018 19:28:35 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ExchangeRates](
	[CurrencyID] [tinyint] NOT NULL,
	[CurrencyRateValue] [numeric](5, 2) NOT NULL,
	[DateOfCurrencyRate] [date] NOT NULL
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Posts]    Script Date: 04.02.2018 19:28:35 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Posts](
	[PostID] [tinyint] NOT NULL,
	[Должность] [nvarchar](21) NOT NULL,
 CONSTRAINT [PK_Должности] PRIMARY KEY CLUSTERED 
(
	[PostID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Result]    Script Date: 04.02.2018 19:28:35 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Result](
	[ClientID] [smallint] NOT NULL,
	[ResultValue] [int] NOT NULL,
	[ResultDate] [date] NOT NULL
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Status]    Script Date: 04.02.2018 19:28:35 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Status](
	[StatusID] [tinyint] IDENTITY(1,1) NOT NULL,
	[Статус] [nvarchar](10) NOT NULL,
 CONSTRAINT [PK_Status] PRIMARY KEY CLUSTERED 
(
	[StatusID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Наименование валют]    Script Date: 04.02.2018 19:28:35 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Наименование валют](
	[CurrencyID] [tinyint] IDENTITY(1,1) NOT NULL,
	[CurrencyName] [nvarchar](50) NOT NULL,
	[CurrencyAbbreviation] [nvarchar](10) NOT NULL,
 CONSTRAINT [PK_Наименование валют_1] PRIMARY KEY CLUSTERED 
(
	[CurrencyID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Расходы]    Script Date: 04.02.2018 19:28:35 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Расходы](
	[expenditureID] [smallint] NOT NULL,
	[expenditureValue] [numeric](18, 2) NOT NULL,
	[Кто выдал] [smallint] NOT NULL,
	[Кому выдал] [smallint] NOT NULL,
	[Дата выдачи] [date] NOT NULL,
	[Время выдачи] [time](3) NOT NULL
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Статьи расходов]    Script Date: 04.02.2018 19:28:35 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Статьи расходов](
	[expenditureID] [smallint] IDENTITY(1,1) NOT NULL,
	[expenditureName] [nvarchar](100) NOT NULL,
 CONSTRAINT [PK_Статьи расходов_1] PRIMARY KEY CLUSTERED 
(
	[expenditureID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Index [IX_Сотрудники]    Script Date: 04.02.2018 19:28:35 ******/
CREATE UNIQUE NONCLUSTERED INDEX [IX_Сотрудники] ON [dbo].[Employees]
(
	[EmployeeID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
GO
ALTER TABLE [dbo].[AllCashIn] ADD  CONSTRAINT [DF_AllCashIn_CashInDate]  DEFAULT (CONVERT([date],sysdatetime())) FOR [CashInDate]
GO
ALTER TABLE [dbo].[AllCashIn] ADD  CONSTRAINT [DF_AllCashIn_CashinTime]  DEFAULT (CONVERT([time],sysdatetime())) FOR [CashinTime]
GO
ALTER TABLE [dbo].[AllCashOut] ADD  CONSTRAINT [DF_AllCashOut_CashOutDate]  DEFAULT (CONVERT([date],sysdatetime())) FOR [CashOutDate]
GO
ALTER TABLE [dbo].[AllCashOut] ADD  CONSTRAINT [DF_AllCashOut_CashOutTime]  DEFAULT (CONVERT([time],sysdatetime())) FOR [CashOutTime]
GO
ALTER TABLE [dbo].[Clients] ADD  CONSTRAINT [DF_Clients_Фамилия]  DEFAULT ('') FOR [Фамилия]
GO
ALTER TABLE [dbo].[Clients] ADD  CONSTRAINT [DF_Clients_Имя]  DEFAULT ('') FOR [Имя]
GO
ALTER TABLE [dbo].[Clients] ADD  CONSTRAINT [DF_Clients_Отчество]  DEFAULT ('') FOR [Отчество]
GO
ALTER TABLE [dbo].[Clients] ADD  CONSTRAINT [DF_Clients_ImageLocation]  DEFAULT (N'D:\\Clients\\Безымянный2.bmp') FOR [ImageLocation]
GO
ALTER TABLE [dbo].[Clients] ADD  CONSTRAINT [DF_Clients_Дата рождения]  DEFAULT (NULL) FOR [Дата рождения]
GO
ALTER TABLE [dbo].[Clients] ADD  CONSTRAINT [DF_Clients_Статус]  DEFAULT ((1)) FOR [Статус]
GO
ALTER TABLE [dbo].[Clients] ADD  CONSTRAINT [DF_Clients_ClientState]  DEFAULT ((0)) FOR [ClientState]
GO
ALTER TABLE [dbo].[Clients] ADD  CONSTRAINT [DF_Clients_LastVisit]  DEFAULT (CONVERT([date],sysdatetime())) FOR [LastVisit]
GO
ALTER TABLE [dbo].[Clients] ADD  CONSTRAINT [DF_Clients_AdditionalInfoAboutClient]  DEFAULT ('') FOR [AdditionalInfoAboutClient]
GO
ALTER TABLE [dbo].[Employees] ADD  CONSTRAINT [DF_Employees_ImageLocation]  DEFAULT (N'D:\Clients\Безымянный2.bmp') FOR [ImageLocation]
GO
ALTER TABLE [dbo].[Result] ADD  CONSTRAINT [DF_Result_ResultDate]  DEFAULT (CONVERT([date],sysdatetime())) FOR [ResultDate]
GO
ALTER TABLE [dbo].[Расходы] ADD  CONSTRAINT [DF_Расходы_Кто выдал]  DEFAULT (suser_id(user_name())) FOR [Кто выдал]
GO
ALTER TABLE [dbo].[Расходы] ADD  CONSTRAINT [DF_Расходы_Дата выдачи]  DEFAULT (CONVERT([date],sysdatetime())) FOR [Дата выдачи]
GO
ALTER TABLE [dbo].[Расходы] ADD  CONSTRAINT [DF_Расходы_Время выдачи]  DEFAULT (CONVERT([time],sysdatetime())) FOR [Время выдачи]
GO
ALTER TABLE [dbo].[AllCashIn]  WITH CHECK ADD  CONSTRAINT [FK_AllCashIn_Clients] FOREIGN KEY([ClientID])
REFERENCES [dbo].[Clients] ([ClientID])
GO
ALTER TABLE [dbo].[AllCashIn] CHECK CONSTRAINT [FK_AllCashIn_Clients]
GO
ALTER TABLE [dbo].[AllCashOut]  WITH CHECK ADD  CONSTRAINT [FK_AllCashOut_Clients] FOREIGN KEY([ClientID])
REFERENCES [dbo].[Clients] ([ClientID])
GO
ALTER TABLE [dbo].[AllCashOut] CHECK CONSTRAINT [FK_AllCashOut_Clients]
GO
ALTER TABLE [dbo].[Clients]  WITH CHECK ADD  CONSTRAINT [FK_Clients_Status] FOREIGN KEY([Статус])
REFERENCES [dbo].[Status] ([StatusID])
GO
ALTER TABLE [dbo].[Clients] CHECK CONSTRAINT [FK_Clients_Status]
GO
ALTER TABLE [dbo].[ClientsPhoneNumbers]  WITH CHECK ADD  CONSTRAINT [FK_ClientsPhoneNumbers_Clients] FOREIGN KEY([ClientID])
REFERENCES [dbo].[Clients] ([ClientID])
GO
ALTER TABLE [dbo].[ClientsPhoneNumbers] CHECK CONSTRAINT [FK_ClientsPhoneNumbers_Clients]
GO
ALTER TABLE [dbo].[Drop]  WITH CHECK ADD  CONSTRAINT [FK_Drop_Clients] FOREIGN KEY([ClientID])
REFERENCES [dbo].[Clients] ([ClientID])
GO
ALTER TABLE [dbo].[Drop] CHECK CONSTRAINT [FK_Drop_Clients]
GO
ALTER TABLE [dbo].[Employees]  WITH CHECK ADD  CONSTRAINT [FK_Employees_Posts] FOREIGN KEY([PostID])
REFERENCES [dbo].[Posts] ([PostID])
GO
ALTER TABLE [dbo].[Employees] CHECK CONSTRAINT [FK_Employees_Posts]
GO
ALTER TABLE [dbo].[ExchangeRates]  WITH CHECK ADD  CONSTRAINT [FK_ExchangeRates_Наименование валют] FOREIGN KEY([CurrencyID])
REFERENCES [dbo].[Наименование валют] ([CurrencyID])
GO
ALTER TABLE [dbo].[ExchangeRates] CHECK CONSTRAINT [FK_ExchangeRates_Наименование валют]
GO
ALTER TABLE [dbo].[Result]  WITH CHECK ADD  CONSTRAINT [FK_Result_Clients] FOREIGN KEY([ClientID])
REFERENCES [dbo].[Clients] ([ClientID])
GO
ALTER TABLE [dbo].[Result] CHECK CONSTRAINT [FK_Result_Clients]
GO
ALTER TABLE [dbo].[Расходы]  WITH CHECK ADD  CONSTRAINT [FK_Расходы_Статьи расходов] FOREIGN KEY([expenditureID])
REFERENCES [dbo].[Статьи расходов] ([expenditureID])
GO
ALTER TABLE [dbo].[Расходы] CHECK CONSTRAINT [FK_Расходы_Статьи расходов]
GO
EXEC sys.sp_addextendedproperty @name=N'fgfg', @value=N'ghghg' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'Employees', @level2type=N'COLUMN',@level2name=N'Lastname'
GO
USE [master]
GO
ALTER DATABASE [Malinka] SET  READ_WRITE 
GO
