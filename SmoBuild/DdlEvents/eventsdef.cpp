//****************************************************************************
//		Copyright (c) Microsoft Corporation.
//
// @File: eventsdef.cpp
// @Owner: ivanpe, ketandu
// @Test: antonk, sshekar
// 
// Purpose: This file contains all event type definitions. It's main purpose is
// 	to be included in eventsshema.cpp. Several perl scripts are parsing
//	this file in order to get to the event type definitions.
//
// Note: If you are updating this file then you must also update the events.xsd
//  schema, in Sql\Common\xsd\sqlserver\2006\events\events.xsd and
//  published at http://schemas.microsoft.com/sqlserver/2006/11/eventdata/events.xsd
//  with RTM releases of SQL Server.
//
//  A stub for events.xsd can be generated using perl scripts, but must be tweaked 
//  to ensure ensure backwards compatibility.
//
//  Building from sql\ntdbms\sqlwep\dllsrc (from an x86fre razzle) will generate
//  the stub events.xsd in %OBJECT_ROOT%\sql\ntdbms\sqlwep\dllsrc\objfre\i386. 
//  
//  Please refer to http://sqlserver/SQLBU/sqlxsd/default.aspx for instructions on
//  publishing the events.xsd.
//
// @EndHeader@
//****************************************************************************

#define BitCount1(x)\
	(((x&0xAAAAAAAAAAAAAAAA)>>1) + (x&0x5555555555555555))
#define BitCount2(x)\
	(((x&0xCCCCCCCCCCCCCCCC)>>2) + (x&0x3333333333333333))
#define BitCount4(x)\
	(((x&0xF0F0F0F0F0F0F0F0)>>4) + (x&0x0F0F0F0F0F0F0F0F))
#define BitCount8(x)\
	(((x&0xFF00FF00FF00FF00)>>8) + (x&0x00FF00FF00FF00FF))
#define BitCount16(x)\
	(((x&0xFFFF0000FFFF0000)>>16) + (x&0x0000FFFF0000FFFF))
#define BitCount32(x)\
	(((x&0xFFFFFFFF00000000)>>32) + (x&0x00000000FFFFFFFF))

#define BitCount64(x)\
	(BitCount32(BitCount16(BitCount8(BitCount4(BitCount2(BitCount1((x))))))))

        
// The Envelope properties are divided into 3 groups
// The 1st 3 are common for all event types.
// The next 2 are only for non-trace event types.
// The next one is only for event types that are not server level only.
//
//----------------------------------------------------------------
// Event Envelope Instance Schema (instance parameters schema)
//----------------------------------------------------------------

STATIC EVENT_PARAM_INFO_DEF s_rgParamInfoEnvelope[] = 
{
	{ EnvelopeTag_EventType, L"EventType", 0,0,NULL,XVT_VARWSTR,  PrecDefault(XVT_VARWSTR),ScaleDefault(XVT_VARWSTR),x_cbMAXSSWNAME,0},
	{ EnvelopeTag_PostTime, L"PostTime", 0,0,NULL,XVT_SSDATE,  PrecDefault(XVT_SSDATE), ScaleDefault(XVT_SSDATE), LenDefault(XVT_SSDATE),0},
	{ EnvelopeTag_SPID, L"SPID", 0,0,NULL,XVT_I4,  PrecDefault(XVT_I4), ScaleDefault(XVT_I4), LenDefault(XVT_I4), 0},

	//----------------------------------------------------------------
	// Additional Event Envelope Instance Schema for non-trace events (instance parameters schema)
	//----------------------------------------------------------------

	// The server name is of the form "ComputerName\InstanceName"
	{ EnvelopeTag_ServerName, L"ServerName", 0,0,NULL,XVT_VARWSTR,PrecDefault(XVT_VARWSTR),ScaleDefault(XVT_VARWSTR),(x_cwchMAXSSWNAME*2 + 1)*sizeof(WCHAR),EVENT_PARAM_NULLABLE},
	{ EnvelopeTag_LoginName, L"LoginName", 0,0,NULL,XVT_VARWSTR, PrecDefault(XVT_VARWSTR),ScaleDefault(XVT_VARWSTR),x_cbMAXSSWNAME,0},

	//----------------------------------------------------------------
	// Additional Event Envelope Instance Schema for non-server level events (instance parameters schema)
	//----------------------------------------------------------------

	{ EnvelopeTag_UserName, L"UserName", 0,0,NULL,XVT_VARWSTR,PrecDefault(XVT_VARWSTR),ScaleDefault(XVT_VARWSTR),x_cbMAXSSWNAME,0},
};

STATIC ULONG s_cParamInfoEnvelope = NUMELEM(s_rgParamInfoEnvelope);

//=================================================
// Param info for SQLTrace
#include "parinfo.inc"

// The new param info array. We dont need a param info array per event type. We will just
// have a global one that can be shared by the various event types.
//
STATIC EVENT_PARAM_INFO_DEF s_rgParamInfoDDL[] = 
{
	{ EventTag_DatabaseName, L"DatabaseName", 0,0,NULL,XVT_VARWSTR,PrecDefault(XVT_VARWSTR), ScaleDefault(XVT_VARWSTR), x_cbMAXSSWNAME, EVENT_PARAM_NULLABLE},
	{ EventTag_SchemaName, L"SchemaName", 0,0,NULL,XVT_VARWSTR,PrecDefault(XVT_VARWSTR), ScaleDefault(XVT_VARWSTR), x_cbMAXSSWNAME, EVENT_PARAM_NULLABLE},
	{ EventTag_ObjectName, L"ObjectName", 0,0,NULL,XVT_VARWSTR,PrecDefault(XVT_VARWSTR), ScaleDefault(XVT_VARWSTR), x_cbMAXSSWNAME, EVENT_PARAM_NULLABLE},
	{ EventTag_ObjectType, L"ObjectType", 0,0,NULL,XVT_VARWSTR,PrecDefault(XVT_VARWSTR), ScaleDefault(XVT_VARWSTR), x_cbMAXSSWNAME, EVENT_PARAM_NULLABLE},
	{ EventTag_RoleName, L"RoleName", 0,0,NULL,XVT_VARWSTR,PrecDefault(XVT_VARWSTR), ScaleDefault(XVT_VARWSTR), x_cbMAXSSWNAME, EVENT_PARAM_NULLABLE},
	{ EventTag_TSQLCommand, L"TSQLCommand", 0,0,NULL,XVT_VARWSTR,PrecDefault(XVT_VARWSTR), ScaleDefault(XVT_VARWSTR), VARTYPE_UNLIMITED_LENGTH, 0},
	{ EventTag_TargetServerName, L"TargetServerName",0,0,NULL,XVT_VARWSTR,PrecDefault(XVT_VARWSTR),ScaleDefault(XVT_VARWSTR),x_cbMAXSSWNAME,EVENT_PARAM_NULLABLE},
	{ EventTag_TargetDatabaseName, L"TargetDatabaseName", 0,0,NULL,XVT_VARWSTR,PrecDefault(XVT_VARWSTR), ScaleDefault(XVT_VARWSTR), x_cbMAXSSWNAME, EVENT_PARAM_NULLABLE},
	{ EventTag_TargetSchemaName, L"TargetSchemaName", 0,0,NULL,XVT_VARWSTR,PrecDefault(XVT_VARWSTR), ScaleDefault(XVT_VARWSTR), x_cbMAXSSWNAME, EVENT_PARAM_NULLABLE},
	{ EventTag_TargetObjectName, L"TargetObjectName", 0,0,NULL,XVT_VARWSTR,PrecDefault(XVT_VARWSTR), ScaleDefault(XVT_VARWSTR), x_cbMAXSSWNAME, EVENT_PARAM_NULLABLE},
	{ EventTag_TargetObjectType, L"TargetObjectType", 0,0,NULL,XVT_VARWSTR,PrecDefault(XVT_VARWSTR), ScaleDefault(XVT_VARWSTR), x_cbMAXSSWNAME, EVENT_PARAM_NULLABLE},
	{ EventTag_OwnerName, L"OwnerName", 0,0,NULL,XVT_VARWSTR,PrecDefault(XVT_VARWSTR), ScaleDefault(XVT_VARWSTR), x_cbMAXSSWNAME, 0},
	{ EventTag_DefaultLanguage, L"DefaultLanguage", 0,0,NULL,XVT_VARWSTR,PrecDefault( XVT_VARWSTR ), ScaleDefault( XVT_VARWSTR ), x_cbMAXSSWNAME, EVENT_PARAM_NULLABLE},
	{ EventTag_DefaultDatabase, L"DefaultDatabase", 0,0,NULL,XVT_VARWSTR,PrecDefault( XVT_VARWSTR ), ScaleDefault( XVT_VARWSTR ), x_cbMAXSSWNAME, EVENT_PARAM_NULLABLE},
	{ EventTag_LoginType, L"LoginType", 0,0,NULL,XVT_VARWSTR,PrecDefault( XVT_VARWSTR ), ScaleDefault( XVT_VARWSTR ), x_cbMAXSSWNAME, 0},
	{ EventTag_SID, L"SID", 0,0,NULL,CTypeInfo::tiSID.XvtType(), PrecDefault(CTypeInfo::tiSID.XvtType()),ScaleDefault(CTypeInfo::tiSID.XvtType()),x_cbMaxSID,EVENT_PARAM_NULLABLE},
	{ EventTag_RoleSID, L"RoleSID", 0,0,NULL,CTypeInfo::tiSID.XvtType(), PrecDefault(CTypeInfo::tiSID.XvtType()),ScaleDefault(CTypeInfo::tiSID.XvtType()),x_cbMaxSID, EVENT_PARAM_NULLABLE},
	{ EventTag_Grantor, L"Grantor", 0,0,NULL,XVT_VARWSTR,PrecDefault(XVT_VARWSTR), ScaleDefault(XVT_VARWSTR), x_cbMAXSSWNAME, 0},
	{ EventTag_Permissions, L"Permissions", 0,0,NULL,XVT_VARWSTR,PrecDefault(XVT_VARWSTR), ScaleDefault(XVT_VARWSTR), VARTYPE_UNLIMITED_LENGTH, 0},
	{ EventTag_Grantees, L"Grantees", 0,0,NULL,XVT_VARWSTR,PrecDefault(XVT_VARWSTR), ScaleDefault(XVT_VARWSTR), VARTYPE_UNLIMITED_LENGTH, 0},
	{ EventTag_AsGrantor, L"AsGrantor", 0,0,NULL,XVT_VARWSTR,PrecDefault(XVT_VARWSTR), ScaleDefault(XVT_VARWSTR), x_cbMAXSSWNAME, EVENT_PARAM_NULLABLE},
	{ EventTag_GrantOption, L"GrantOption", 0,0,NULL,XVT_BIT, PrecDefault(XVT_BIT), ScaleDefault(XVT_BIT), LenDefault(XVT_BIT),0},
	{ EventTag_CascadeOption, L"CascadeOption", 0,0,NULL,XVT_BIT, PrecDefault(XVT_BIT), ScaleDefault(XVT_BIT), LenDefault(XVT_BIT),0},
	{ EventTag_PrimaryXMLIndexName, L"PrimaryXMLIndexName", 0,0,NULL,XVT_VARWSTR,PrecDefault(XVT_VARWSTR), ScaleDefault(XVT_VARWSTR), x_cbMAXSSWNAME, EVENT_PARAM_NULLABLE},
	{ EventTag_SecondaryXMLIndexType, L"SecondaryXMLIndexType", 0,0,NULL,XVT_SSWSTR,PrecDefault(XVT_SSWSTR), ScaleDefault(XVT_SSWSTR), 2, EVENT_PARAM_NULLABLE},
	{ EventTag_CertificatePath, L"CertificatePath",0,0,NULL,CTypeInfo::tiMaxPathName.XvtType(),PrecDefault(CTypeInfo::tiMaxPathName.XvtType()),
		ScaleDefault(CTypeInfo::tiMaxPathName.XvtType()),sizeof(WCHAR)*MAX_PATH, EVENT_PARAM_NULLABLE},
	{ EventTag_PrivateKeyPath, L"PrivateKeyPath",0,0,NULL,CTypeInfo::tiMaxPathName.XvtType(),PrecDefault(CTypeInfo::tiMaxPathName.XvtType()),
		ScaleDefault(CTypeInfo::tiMaxPathName.XvtType()),sizeof(WCHAR)*MAX_PATH,EVENT_PARAM_NULLABLE},
	{ EventTag_CertificateSubject, L"CertificateSubject", 0,0,NULL,XVT_VARWSTR,PrecDefault(XVT_VARWSTR), ScaleDefault(XVT_VARWSTR), x_cbMAXSSWNAME, EVENT_PARAM_NULLABLE},
	{ EventTag_Function, L"Function", 0,0,NULL,XVT_VARWSTR,PrecDefault(XVT_VARWSTR), ScaleDefault(XVT_VARWSTR), x_cbMAXSSWNAME, 0},
	{ EventTag_DefaultSchema, L"DefaultSchema",0,0,NULL,XVT_VARWSTR,PrecDefault(XVT_VARWSTR),ScaleDefault(XVT_VARWSTR),x_cbMAXSSWNAME, EVENT_PARAM_NULLABLE},
	{ EventTag_ClientHost, L"ClientHost", 0,0,NULL,XVT_VARWSTR,PrecDefault(XVT_VARWSTR), ScaleDefault(XVT_VARWSTR), x_cbMAXSSWNAME, 0},
	{ EventTag_IsPooled, L"IsPooled", 0,0,NULL,XVT_BIT, PrecDefault(XVT_BIT), ScaleDefault(XVT_BIT), LenDefault(XVT_BIT),0},
	{ EventTag_Parameters, L"Parameters", 0,0,NULL,XVT_VARWSTR,PrecDefault(XVT_VARWSTR), ScaleDefault(XVT_VARWSTR), VARTYPE_UNLIMITED_LENGTH, 0},
	{ EventTag_PropertyName, L"PropertyName", 0,0,NULL,XVT_VARWSTR,PrecDefault(XVT_VARWSTR), ScaleDefault(XVT_VARWSTR), x_cbMAXSSWNAME, 0},
	{ EventTag_PropertyValue, L"PropertyValue", 0,0,NULL,XVT_SSVARIANT,PrecDefault(XVT_SSVARIANT), ScaleDefault(XVT_SSVARIANT), SIZEOFSSVARIANT, EVENT_PARAM_NULLABLE},
	{ EventTag_NewObjectName, L"NewObjectName", 0,0,NULL,XVT_VARWSTR,PrecDefault(XVT_VARWSTR), ScaleDefault(XVT_VARWSTR), x_cbMAXSSWNAME, 0},
	{ EventTag_KeyPath, L"KeyPath",0,0,NULL,CTypeInfo::tiMaxPathName.XvtType(),PrecDefault(CTypeInfo::tiMaxPathName.XvtType()),
		ScaleDefault(CTypeInfo::tiMaxPathName.XvtType()),sizeof(WCHAR)*MAX_PATH, EVENT_PARAM_NULLABLE},
	{ EventTag_CounterSignature, L"CounterSignature", 0,0,NULL,XVT_BIT, PrecDefault(XVT_BIT), ScaleDefault(XVT_BIT), LenDefault(XVT_BIT),0},
	{ EventTag_AlterTableActionList, L"AlterTableActionList", 0,0,NULL,XVT_VARWSTR,PrecDefault(XVT_VARWSTR), ScaleDefault(XVT_VARWSTR), VARTYPE_UNLIMITED_LENGTH, 0},
	{ EventTag_AlterDatabaseActionList, L"AlterDatabaseActionList", 0,0,NULL,XVT_VARWSTR,PrecDefault(XVT_VARWSTR), ScaleDefault(XVT_VARWSTR), VARTYPE_UNLIMITED_LENGTH, 0},
};
STATIC ULONG s_cParamInfoDDL = NUMELEM(s_rgParamInfoDDL);

// Extended GROUP enum for SQLTrace
#include "grpenum.inc"
//=================================================

// This array defines groups for all supported synchronous events. The array order should follow 
// the order of the EEventGroup enum defined in events.h.
//
EVENT_GROUP g_rgEventGroup[] = 
{
	//------------------------------------------------------------------------------------------
	//	GROUP ID				GROUP PARENT ID 		Group name			For optimization
	//------------------------------------------------------------------------------------------
	{	EGROUP_ALL, 				EGROUP_INVALID, 			L"ALL_EVENTS",					 x_eet_Group_All,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL, 				EGROUP_ALL, 				L"DDL_EVENTS",					 x_eet_Group_Ddl,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_SERVER_LEVEL,	EGROUP_DDL, 				L"DDL_SERVER_LEVEL_EVENTS", 	 x_eet_Group_Ddl_Server_Level,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_ENDPOINT,		EGROUP_DDL_SERVER_LEVEL,	L"DDL_ENDPOINT_EVENTS", 		 x_eet_Group_Ddl_Endpoint,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_DATABASE,		EGROUP_DDL_SERVER_LEVEL,	L"DDL_DATABASE_EVENTS", 		 x_eet_Group_Ddl_Database,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_SERVER_SECURITY, EGROUP_DDL_SERVER_LEVEL,	L"DDL_SERVER_SECURITY_EVENTS",	 x_eet_Group_Ddl_Server_Security,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_LOGIN,			EGROUP_DDL_SERVER_SECURITY, L"DDL_LOGIN_EVENTS",				 x_eet_Group_Ddl_Login,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_GDR_SERVER,		EGROUP_DDL_SERVER_SECURITY, L"DDL_GDR_SERVER_EVENTS",		 x_eet_Group_Ddl_Gdr_Server,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_AUTH_SERVER, 	EGROUP_DDL_SERVER_SECURITY, L"DDL_AUTHORIZATION_SERVER_EVENTS",  x_eet_Group_Ddl_Auth_Server,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_CREDENTIAL,		EGROUP_DDL_SERVER_SECURITY, 	L"DDL_CREDENTIAL_EVENTS",	x_eet_Group_Ddl_Credential,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_CRYPTOPROV,		EGROUP_DDL_SERVER_SECURITY, 	L"DDL_CRYPTOGRAPHIC_PROVIDER_EVENTS",	x_eet_Group_Ddl_CryptoProv,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_SRVMASTERKEY,	EGROUP_DDL_SERVER_SECURITY, 	L"DDL_SERVICE_MASTER_KEY_EVENTS", x_eet_Group_Ddl_Service_Master_Key,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_SERVERAUDIT,		EGROUP_DDL_SERVER_SECURITY, 	L"DDL_SERVER_AUDIT_EVENTS", x_eet_Group_Ddl_ServerAudit,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_SERVERAUDITSPEC,	EGROUP_DDL_SERVER_SECURITY, 	L"DDL_SERVER_AUDIT_SPECIFICATION_EVENTS", x_eet_Group_Ddl_ServerAuditSpec,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_EXTENDED_PROCEDURE,	EGROUP_DDL_SERVER_LEVEL,	L"DDL_EXTENDED_PROCEDURE_EVENTS",  x_eet_Group_Ddl_Extended_Procedure,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_LINKED_SERVER,	EGROUP_DDL_SERVER_LEVEL,	L"DDL_LINKED_SERVER_EVENTS",  x_eet_Group_Ddl_Linked_Server,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_LINKED_SERVER_LOGIN,	EGROUP_DDL_LINKED_SERVER,	L"DDL_LINKED_SERVER_LOGIN_EVENTS",  x_eet_Group_Ddl_Linked_Server_Login,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_MESSAGE,			EGROUP_DDL_SERVER_LEVEL,	L"DDL_MESSAGE_EVENTS",  x_eet_Group_Ddl_Message,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_REMOTE_SERVER,	EGROUP_DDL_SERVER_LEVEL,	L"DDL_REMOTE_SERVER_EVENTS",  x_eet_Group_Ddl_Remote_Server,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_EVENT_SESSION,	EGROUP_DDL_SERVER_LEVEL,	L"DDL_EVENT_SESSION_EVENTS",  x_eet_Group_Ddl_Event_Session,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_RESOURCE_GOVERNOR,	EGROUP_DDL_SERVER_LEVEL,    L"DDL_RESOURCE_GOVERNOR_EVENTS",x_eet_Group_Ddl_Resource_Governor,  ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_RESOURCE_POOL,   		EGROUP_DDL_RESOURCE_GOVERNOR,L"DDL_RESOURCE_POOL",           x_eet_Group_Ddl_Resource_Pool,      ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_EXTERNAL_RESOURCE_POOL,  EGROUP_DDL_RESOURCE_GOVERNOR,L"DDL_EXTERNAL_RESOURCE_POOL_EVENTS",           x_eet_Group_Ddl_External_Resource_Pool,      ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_RESOURCE_GROUP,  		EGROUP_DDL_RESOURCE_GOVERNOR,L"DDL_WORKLOAD_GROUP",          x_eet_Group_Ddl_Resource_Group,     ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_DATABASE_LEVEL,	EGROUP_DDL, 				L"DDL_DATABASE_LEVEL_EVENTS",	 x_eet_Group_Ddl_Database_Level,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_TABLEVIEW,		EGROUP_DDL_DATABASE_LEVEL,	L"DDL_TABLE_VIEW_EVENTS",		 x_eet_Group_Ddl_Tableview,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_TABLE,			EGROUP_DDL_TABLEVIEW,		L"DDL_TABLE_EVENTS",				 x_eet_Group_Ddl_Table,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_VIEW,			EGROUP_DDL_TABLEVIEW,		L"DDL_VIEW_EVENTS", 			 x_eet_Group_Ddl_View,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_INDEX,			EGROUP_DDL_TABLEVIEW,		L"DDL_INDEX_EVENTS",				 x_eet_Group_Ddl_Index,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_STATS,			EGROUP_DDL_TABLEVIEW,		L"DDL_STATISTICS_EVENTS",		 x_eet_Group_Ddl_Stats,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_SYNONYM, 		EGROUP_DDL_DATABASE_LEVEL,	L"DDL_SYNONYM_EVENTS",			 x_eet_Group_Ddl_Synonym,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_FUNCTION,		EGROUP_DDL_DATABASE_LEVEL,	L"DDL_FUNCTION_EVENTS", 		 x_eet_Group_Ddl_Function,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_STOREDPROC,		EGROUP_DDL_DATABASE_LEVEL,	L"DDL_PROCEDURE_EVENTS",		 x_eet_Group_Ddl_Storedproc,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_TRIGGER, 		EGROUP_DDL_DATABASE_LEVEL,	L"DDL_TRIGGER_EVENTS",			 x_eet_Group_Ddl_Trigger,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_EVTNOTIF,		EGROUP_DDL_DATABASE_LEVEL,	L"DDL_EVENT_NOTIFICATION_EVENTS",  x_eet_Group_Ddl_Evtnotif,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_ASSEMBLY,		EGROUP_DDL_DATABASE_LEVEL,	L"DDL_ASSEMBLY_EVENTS", 		 x_eet_Group_Ddl_Assembly,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_UDT, 			EGROUP_DDL_DATABASE_LEVEL,	L"DDL_TYPE_EVENTS", 			 x_eet_Group_Ddl_Udt,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_SEQUENCE, 		EGROUP_DDL_DATABASE_LEVEL,	L"DDL_SEQUENCE_EVENTS",			 x_eet_Group_Ddl_Sequence,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_LIBRARY,			EGROUP_DDL_DATABASE_LEVEL,	L"DDL_LIBRARY_EVENTS",			 x_eet_Group_Ddl_Library,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_SENSITIVITY,		EGROUP_DDL_DATABASE_LEVEL,	L"DDL_SENSITIVITY_EVENTS",		 x_eet_Group_Ddl_Sensitivity,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_EXTERNAL_LANGUAGE, EGROUP_DDL_DATABASE_LEVEL, L"DDL_EXTERNAL_LANGUAGE_EVENTS",		 x_eet_Group_Ddl_External_Language, ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_DB_SECURITY, 	EGROUP_DDL_DATABASE_LEVEL,	L"DDL_DATABASE_SECURITY_EVENTS", x_eet_Group_Ddl_DB_Security,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_CERTIFICATE, 	EGROUP_DDL_DB_SECURITY, 	L"DDL_CERTIFICATE_EVENTS",		 x_eet_Group_Ddl_Certificate,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_USER,			EGROUP_DDL_DB_SECURITY, 	L"DDL_USER_EVENTS", 			 x_eet_Group_Ddl_User,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_ROLE,			EGROUP_DDL_DB_SECURITY, 	L"DDL_ROLE_EVENTS", 			 x_eet_Group_Ddl_Role,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_APPROLE, 		EGROUP_DDL_DB_SECURITY, 	L"DDL_APPLICATION_ROLE_EVENTS",  x_eet_Group_Ddl_Approle,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_SCHEMA,			EGROUP_DDL_DB_SECURITY, 	L"DDL_SCHEMA_EVENTS",			 x_eet_Group_Ddl_Schema,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_GDR_DATABASE,	EGROUP_DDL_DB_SECURITY, 	L"DDL_GDR_DATABASE_EVENTS", 	 x_eet_Group_Ddl_Gdr_Database,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_AUTH_DATABASE,	EGROUP_DDL_DB_SECURITY, 	L"DDL_AUTHORIZATION_DATABASE_EVENTS",  x_eet_Group_Ddl_Auth_Database,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_OBFUSKEY, 		EGROUP_DDL_DB_SECURITY, 	L"DDL_SYMMETRIC_KEY_EVENTS",	x_eet_Group_Ddl_Symmetric,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_ASYMKEY, 		EGROUP_DDL_DB_SECURITY, 	L"DDL_ASYMMETRIC_KEY_EVENTS",	x_eet_Group_Ddl_Asymmetric,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_CRYPTOSIGN,		EGROUP_DDL_DB_SECURITY, 	L"DDL_CRYPTO_SIGNATURE_EVENTS",	x_eet_Group_Ddl_Crypto_Signature,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_DBMASTERKEY,		EGROUP_DDL_DB_SECURITY, 	L"DDL_MASTER_KEY_EVENTS",	x_eet_Group_Ddl_Master_Key,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_DEK,				EGROUP_DDL_DB_SECURITY, 	L"DDL_DATABASE_ENCRYPTION_KEY_EVENTS",	x_eet_Group_Ddl_DEK,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_DBAUDITSPEC,		EGROUP_DDL_DB_SECURITY, 	L"DDL_DATABASE_AUDIT_SPECIFICATION_EVENTS",	x_eet_Group_Ddl_DbAuditSpec, ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_DBAUDIT,			EGROUP_DDL_DB_SECURITY,		L"DDL_DATABASE_AUDIT_EVENTS",  x_eet_Group_Ddl_DatabaseAudit_Group,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_SSB, 			EGROUP_DDL_DATABASE_LEVEL,	L"DDL_SSB_EVENTS",				 x_eet_Group_Ddl_Ssb,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_MSGTYPE, 		EGROUP_DDL_SSB, 			L"DDL_MESSAGE_TYPE_EVENTS", 	 x_eet_Group_Ddl_Msgtype,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_CONTRACT,		EGROUP_DDL_SSB, 			L"DDL_CONTRACT_EVENTS", 		 x_eet_Group_Ddl_Contract,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_QUEUE,			EGROUP_DDL_SSB, 			L"DDL_QUEUE_EVENTS",				 x_eet_Group_Ddl_Queue,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_SERVICE, 		EGROUP_DDL_SSB, 			L"DDL_SERVICE_EVENTS",			 x_eet_Group_Ddl_Service,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_ROUTE,			EGROUP_DDL_SSB, 			L"DDL_ROUTE_EVENTS",				 x_eet_Group_Ddl_Route,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_BINDING, 		EGROUP_DDL_SSB, 			L"DDL_REMOTE_SERVICE_BINDING_EVENTS",  x_eet_Group_Ddl_Binding,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_PRIORITY,		EGROUP_DDL_SSB, 			L"DDL_BROKER_PRIORITY_EVENTS",		x_eet_Group_Ddl_Priority, ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_XML_SCHEMA_COLLECTION,	EGROUP_DDL_DATABASE_LEVEL,	L"DDL_XML_SCHEMA_COLLECTION_EVENTS",		 x_eet_Group_Ddl_Xml_Schema_Collection,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_PARTITION,		EGROUP_DDL_DATABASE_LEVEL,	L"DDL_PARTITION_EVENTS",			 x_eet_Group_Ddl_Partition,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_PRTFUNCTION, 	EGROUP_DDL_PARTITION,		L"DDL_PARTITION_FUNCTION_EVENTS",  x_eet_Group_Ddl_Prtfunction,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_PRTSCHEME,		EGROUP_DDL_PARTITION,		L"DDL_PARTITION_SCHEME_EVENTS",  x_eet_Group_Ddl_Prtscheme,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_DEFAULT,			EGROUP_DDL_DATABASE_LEVEL,	L"DDL_DEFAULT_EVENTS",  x_eet_Group_Ddl_Default,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_EXTENDED_PROPERTY,	EGROUP_DDL_DATABASE_LEVEL,	L"DDL_EXTENDED_PROPERTY_EVENTS",  x_eet_Group_Ddl_Extended_Property,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_FULLTEXT_CATALOG,	EGROUP_DDL_DATABASE_LEVEL,	L"DDL_FULLTEXT_CATALOG_EVENTS",  x_eet_Group_Ddl_Fulltext_Catalog,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_PLAN_GUIDE,		EGROUP_DDL_DATABASE_LEVEL,	L"DDL_PLAN_GUIDE_EVENTS",  x_eet_Group_Ddl_Plan_Guide,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_RULE,			EGROUP_DDL_DATABASE_LEVEL,	L"DDL_RULE_EVENTS",  x_eet_Group_Ddl_Rule,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_FULLTEXT_STOPLIST,	EGROUP_DDL_DATABASE_LEVEL,	L"DDL_FULLTEXT_STOPLIST_EVENTS",  x_eet_Group_Ddl_Fulltext_StopList,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_PROPERTYLIST,	EGROUP_DDL_DATABASE_LEVEL,	L"DDL_SEARCH_PROPERTY_LIST_EVENTS",  x_eet_Group_Ddl_PropertyList,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_AVAILABILITY_GROUP,	EGROUP_DDL_SERVER_LEVEL,	L"DDL_AVAILABILITY_GROUP_EVENTS",  x_eet_Group_Ddl_Availability_Group,	ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_SECURITY_POLICY,	EGROUP_DDL_DATABASE_LEVEL, 	L"DDL_SECURITY_POLICY_EVENTS",  x_eet_Group_Ddl_SecurityPolicy_Group, ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_COL_MASTER_KEY,	EGROUP_DDL_DATABASE_LEVEL, 	L"DDL_COLUMN_MASTER_KEY_EVENTS",  x_eet_Group_Ddl_Col_Master_Key_Group , ETYP_ON_INVALID, 0, 0, 0 },
	{	EGROUP_DDL_COL_ENCRYPTION_KEY, EGROUP_DDL_DATABASE_LEVEL,	L"DDL_COLUMN_ENCRYPTION_KEY_EVENTS",	x_eet_Group_Ddl_Col_Encryption_Key_Group, ETYP_ON_INVALID, 0, 0, 0 },

// ========= SQLTrace additions.  Do not put anything below!!!==================================
	{	EGROUP_TRCAT_ALL,			EGROUP_ALL, 				L"TRC_ALL_EVENTS",				 x_eet_Group_Traceat_All,	ETYP_ON_INVALID, 0, 0, 0 },
#include "grpdefs.inc" 
//=============================================================================
};

STATIC const ULONG s_cEventGroup = ARRAYSIZE(g_rgEventGroup);

// This array defines schema for all supported synchronous events. The array order should follow 
// the order of the EEventType enum defined in events.h.
//
STATIC EVENT_SCHEMA s_rgEventSchema[] = 
{

////////////////////////////////////////////////////////////////////////////////////////
//	DDL EVENTS
////////////////////////////////////////////////////////////////////////////////////////

	//-----------------------------------------------
	// CREATE TABLE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATETABLE,
	  x_eet_Create_Table,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_TABLE",
	  EventTag_SchemaDDL,
	  NULL,
	  5,
	  EGROUP_DDL_TABLE,
	  0
	},

	//-----------------------------------------------
	// ALTER TABLE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTERTABLE,
	  x_eet_Alter_Table,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_TABLE",
	  EventTag_SchemaDDL | EventTag_Parameters | EventTag_AlterTableActionList,
	  NULL,
	  BitCount64(EventTag_SchemaDDL | EventTag_Parameters | EventTag_AlterTableActionList),
	  EGROUP_DDL_TABLE,
	  0
	},

	//-----------------------------------------------
	// DROP TABLE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROPTABLE,
	  x_eet_Drop_Table,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_TABLE",
	  EventTag_SchemaDDL,
	  NULL,
	  5,
	  EGROUP_DDL_TABLE,
	  0
	},

	//-----------------------------------------------
	// CREATE VIEW Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATEVIEW,
	  x_eet_Create_View,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_VIEW",
	  EventTag_SchemaDDL,
	  NULL,
	  5,
	  EGROUP_DDL_VIEW,
	  0
	},

	//-----------------------------------------------
	// ALTER VIEW Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTERVIEW,
	  x_eet_Alter_View,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_VIEW",
	  EventTag_SchemaDDL,
	  NULL,
	  5,
	  EGROUP_DDL_VIEW,
	  0
	},

	//-----------------------------------------------
	// DROP VIEW Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROPVIEW,
	  x_eet_Drop_View,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_VIEW",
	  EventTag_SchemaDDL,
	  NULL,
	  5,
	  EGROUP_DDL_VIEW,
	  0
	},

	//-----------------------------------------------
	// CREATE SYNONYM Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATESYNONYM,
	  x_eet_Create_Synonym,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_SYNONYM",
	  EventTag_SchemaDDL | EventTag_TargetNames,
	  NULL,
	  9,
	  EGROUP_DDL_SYNONYM,
	  0
	},

	//-----------------------------------------------
	// DROP SYNONYM Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROPSYNONYM,
	  x_eet_Drop_Synonym,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_SYNONYM",
	  EventTag_SchemaDDL | EventTag_TargetNames,
	  NULL,
	  9,
	  EGROUP_DDL_SYNONYM,
	  0
	},

	//-----------------------------------------------
	// CREATE FUNCTION Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATEFUNCTION,
	  x_eet_Create_Function,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_FUNCTION",
	  EventTag_SchemaDDL,
	  NULL,
	  5,
	  EGROUP_DDL_FUNCTION,
	  0
	},

	//-----------------------------------------------
	// ALTER FUNCTION Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTERFUNCTION,
	  x_eet_Alter_Function,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_FUNCTION",
	  EventTag_SchemaDDL,
	  NULL,
	  5,
	  EGROUP_DDL_FUNCTION,
	  0
	},

	//-----------------------------------------------
	// DROP FUNCTION Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROPFUNCTION,
	  x_eet_Drop_Function,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_FUNCTION",
	  EventTag_SchemaDDL,
	  NULL,
	  5,
	  EGROUP_DDL_FUNCTION,
	  0
	},

	//-----------------------------------------------
	// CREATE PROCEDURE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATEPROC,
	  x_eet_Create_Procedure,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_PROCEDURE",
	  EventTag_SchemaDDL,
	  NULL,
	  5,
	  EGROUP_DDL_STOREDPROC,
	  0
	},

	//-----------------------------------------------
	// ALTER PROCEDURE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTERPROC,
	  x_eet_Alter_Procedure,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_PROCEDURE",
	  EventTag_SchemaDDL | EventTag_Parameters,
	  NULL,
	  6,
	  EGROUP_DDL_STOREDPROC,
	  0
	},

	//-----------------------------------------------
	// DROP PROCEDURE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROPPROC,
	  x_eet_Drop_Procedure,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_PROCEDURE",
	  EventTag_SchemaDDL,
	  NULL,
	  5,
	  EGROUP_DDL_STOREDPROC,
	  0
	},

	//-----------------------------------------------
	// CREATE TRIGGER Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATETRIGGER,
	  x_eet_Create_Trigger,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_TRIGGER",
	  EventTag_SchemaTargetDDL,
	  NULL,
	  7,
	  EGROUP_DDL_TRIGGER,
	  0
	},

	//-----------------------------------------------
	// ALTER TRIGGER Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTERTRIGGER,
	  x_eet_Alter_Trigger,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_TRIGGER",
	  EventTag_SchemaTargetDDL | EventTag_Parameters,
	  NULL,
	  8,
	  EGROUP_DDL_TRIGGER,
	  0
	},

	//-----------------------------------------------
	// DROP TRIGGER Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROPTRIGGER,
	  x_eet_Drop_Trigger,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_TRIGGER",
	  EventTag_SchemaTargetDDL,
	  NULL,
	  7,
	  EGROUP_DDL_TRIGGER,
	  0
	},

	//-----------------------------------------------
	// CREATE EVENT NOTIFICATION Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATEEVTNOTIF,
	  x_eet_Create_Event_Notification,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_EVENT_NOTIFICATION",
	  EventTag_SchemaLessFullTargetDDL,
	  NULL,
	  7,
	  EGROUP_DDL_EVTNOTIF,
	  0
	},

	//-----------------------------------------------
	// DROP EVENT NOTIFICATION Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROPEVTNOTIF,
	  x_eet_Drop_Event_Notification,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_EVENT_NOTIFICATION",
	  EventTag_SchemaLessFullTargetDDL,
	  NULL,
	  7,
	  EGROUP_DDL_EVTNOTIF,
	  0
	},

	//-----------------------------------------------
	// CREATE INDEX Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATEINDEX,
	  x_eet_Create_Index,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_INDEX",
	  EventTag_SchemaTargetDDL,
	  NULL,
	  7,
	  EGROUP_DDL_INDEX,
	  0
	},

	//-----------------------------------------------
	// ALTER INDEX Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTERINDEX,
	  x_eet_Alter_Index,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_INDEX",
	  EventTag_SchemaTargetDDL | EventTag_Parameters,
	  NULL,
	  8,
	  EGROUP_DDL_INDEX,
	  0
	},

	//-----------------------------------------------
	// DROP INDEX Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROPINDEX,
	  x_eet_Drop_Index,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_INDEX",
	  EventTag_SchemaTargetDDL,
	  NULL,
	  7,
	  EGROUP_DDL_INDEX,
	  0
	},

	//-----------------------------------------------
	// CREATE STATS Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATESTATS,
	  x_eet_Create_Stats,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_STATISTICS",
	  EventTag_SchemaTargetDDL,
	  NULL,
	  7,
	  EGROUP_DDL_STATS,
	  0
	},

	//-----------------------------------------------
	// UPDATE STATS Event Schema
	//-----------------------------------------------
	{ ETYP_ON_UPDATESTATS,
	  x_eet_Update_Stats,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"UPDATE_STATISTICS",
	  EventTag_DatabaseEvent | EventTag_SchemaName | EventTag_ObjectType | EventTag_TargetObjectName | EventTag_TargetObjectType,
	  NULL,
	  6,
	  EGROUP_DDL_STATS,
	  0
	},

	//-----------------------------------------------
	// DROP STATS Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROPSTATS,
	  x_eet_Drop_Stats,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_STATISTICS",
	  EventTag_SchemaTargetDDL,
	  NULL,
	  7,
	  EGROUP_DDL_STATS,
	  0
	},

	//-----------------------------------------------
	// CREATE DATABASE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATEDATABASE,
	  x_eet_Create_Database,
	  EOBJTYP_SERVER,
	  EFLAG_NEW_TRANS,
	  L"CREATE_DATABASE",
	  EventTag_DatabaseEvent,
	  NULL,
	  2,
	  EGROUP_DDL_DATABASE,
	  0
	},

	//-----------------------------------------------
	// ALTER DATABASE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTERDATABASE,
	  x_eet_Alter_Database,
	  EOBJTYP_SERVER,
	  EFLAG_NEW_TRANS,
	  L"ALTER_DATABASE",
	  EventTag_DatabaseEvent | EventTag_Parameters | EventTag_AlterDatabaseActionList,
	  NULL,
	  BitCount64(EventTag_DatabaseEvent | EventTag_Parameters | EventTag_AlterDatabaseActionList), // 4,
	  EGROUP_DDL_DATABASE,
	  0
	},

	//-----------------------------------------------
	// DROP DATABASE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROPDATABASE,
	  x_eet_Drop_Database,
	  EOBJTYP_SERVER,
	  EFLAG_NEW_TRANS,
	  L"DROP_DATABASE",
	  EventTag_DatabaseEvent,
	  NULL,
	  2,
	  EGROUP_DDL_DATABASE,
	  0
	},

	//-----------------------------------------------
	// CREATE ASSEMBLY Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATEASSEMBLY,
	  x_eet_Create_Assembly,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_ASSEMBLY",
	  EventTag_SchemaLessDDL,
	  NULL,
	  4,
	  EGROUP_DDL_ASSEMBLY,
	  0
	},

	//-----------------------------------------------
	// ALTER ASSEMBLY Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTERASSEMBLY,
	  x_eet_Alter_Assembly,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_ASSEMBLY",
	  EventTag_SchemaLessDDL,
	  NULL,
	  4,
	  EGROUP_DDL_ASSEMBLY,
	  0
	},

	//-----------------------------------------------
	// DROP ASSEMBLY Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROPASSEMBLY,
	  x_eet_Drop_Assembly,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_ASSEMBLY",
	  EventTag_SchemaLessDDL,
	  NULL,
	  4,
	  EGROUP_DDL_ASSEMBLY,
	  0
	},

	//-----------------------------------------------
	// CREATE TYPE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATETYPE,
	  x_eet_Create_Type,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_TYPE",
	  EventTag_SchemaDDL,
	  NULL,
	  5,
	  EGROUP_DDL_UDT,
	  0
	},

	//-----------------------------------------------
	// DROP TYPE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROPTYPE,
	  x_eet_Drop_Type,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_TYPE",
	  EventTag_SchemaDDL,
	  NULL,
	  5,
	  EGROUP_DDL_UDT,
	  0
	},

	//-----------------------------------------------
	// CREATE USER Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATEUSER,
	  x_eet_Create_User,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_USER",
	  EventTag_SchemaLessDDL | EventTag_DefaultSchema | EventTag_SID | EventTag_DefaultLanguage,
	  NULL,
	  7,
	  EGROUP_DDL_USER,
	  0
	},

	//-----------------------------------------------
	// ALTER USER Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTERUSER,
	  x_eet_Alter_User,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_USER",
	  EventTag_SchemaLessDDL | EventTag_DefaultSchema | EventTag_SID | EventTag_Parameters | EventTag_DefaultLanguage,
	  NULL,
	  8,
	  EGROUP_DDL_USER,
	  0
	},

	//-----------------------------------------------
	// DROP USER Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROPUSER,
	  x_eet_Drop_User,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_USER",
	  EventTag_SchemaLessDDL | EventTag_DefaultSchema | EventTag_SID | EventTag_DefaultLanguage,
	  NULL,
	  7,
	  EGROUP_DDL_USER,
	  0
	},


	//-----------------------------------------------
	// ADD ROLE MEMBER (sp_AddRoleMember) Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ADDROLEMEMBER,
	  x_eet_Add_Role_Member,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ADD_ROLE_MEMBER",
	  EventTag_DatabaseName | EventTag_ObjectEvent | EventTag_DefaultSchema | EventTag_SID | EventTag_RoleName | EventTag_TSQLCommand,
	  NULL,
	  BitCount64(EventTag_DatabaseName | EventTag_ObjectEvent | EventTag_DefaultSchema | EventTag_SID | EventTag_RoleName | EventTag_TSQLCommand),
	  EGROUP_DDL_ROLE,
	  0
	},

	//-----------------------------------------------
	// DROP ROLE MEMBER (sp_DropRoleMember) Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROPROLEMEMBER,
	  x_eet_Drop_Role_Member,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_ROLE_MEMBER",
	  EventTag_DatabaseName | EventTag_ObjectEvent | EventTag_DefaultSchema | EventTag_SID | EventTag_RoleName | EventTag_TSQLCommand,
	  NULL,
	  BitCount64(EventTag_DatabaseName | EventTag_ObjectEvent | EventTag_DefaultSchema | EventTag_SID | EventTag_RoleName | EventTag_TSQLCommand),
	  EGROUP_DDL_ROLE,
	  0
	},


	//-----------------------------------------------
	// CREATE ROLE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATEROLE,
	  x_eet_Create_Role,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_ROLE",
	  EventTag_SchemaLessDDL  | EventTag_SID,
	  NULL,
	  5,
	  EGROUP_DDL_ROLE,
	  0
	},
	
	//-----------------------------------------------
	// ALTER ROLE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTERROLE,
	  x_eet_Alter_Role,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_ROLE",
	  EventTag_SchemaLessDDL  | EventTag_SID,
	  NULL,
	  5,
	  EGROUP_DDL_ROLE,
	  0
	},

	//-----------------------------------------------
	// DROP ROLE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROPROLE,
	  x_eet_Drop_Role,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_ROLE",
	  EventTag_SchemaLessDDL  | EventTag_SID,
	  NULL,
	  5,
	  EGROUP_DDL_ROLE,
	  0
	},


	//-----------------------------------------------
	// CREATE APPROLE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATEAPPROLE,
	  x_eet_Create_AppRole,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_APPLICATION_ROLE",
	  EventTag_SchemaLessDDL | EventTag_DefaultSchema  | EventTag_SID,
	  NULL,
	  6,
	  EGROUP_DDL_APPROLE,
	  0
	},
	
	//-----------------------------------------------
	// ALTER APPROLE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTERAPPROLE,
	  x_eet_Alter_AppRole,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_APPLICATION_ROLE",
	  EventTag_SchemaLessDDL | EventTag_DefaultSchema  | EventTag_SID,
	  NULL,
	  6,
	  EGROUP_DDL_APPROLE,
	  0
	},

	//-----------------------------------------------
	// DROP APPROLE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROPAPPROLE,
	  x_eet_Drop_AppRole,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_APPLICATION_ROLE",
	  EventTag_SchemaLessDDL | EventTag_DefaultSchema  | EventTag_SID,
	  NULL,
	  6,
	  EGROUP_DDL_APPROLE,
	  0
	},


	//-----------------------------------------------
	// CREATE SCHEMA Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATESCHEMA,
	  x_eet_Create_Schema,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_SCHEMA",
	  EventTag_DatabaseEvent | EventTag_SchemaName | EventTag_OwnerName | EventTag_ObjectEvent,
	  NULL,
	  6,
	  EGROUP_DDL_SCHEMA,
	  0
	},

	//-----------------------------------------------
	// ALTER SCHEMA Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTERSCHEMA,
	  x_eet_Alter_Schema,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_SCHEMA",
	  EventTag_SchemaDDL,
	  NULL,
	  BitCount64(EventTag_SchemaDDL),
	  EGROUP_DDL_SCHEMA,
	  0
	},

	//-----------------------------------------------
	// DROP SCHEMA Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROPSCHEMA,
	  x_eet_Drop_Schema,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_SCHEMA",
	  EventTag_DatabaseEvent | EventTag_SchemaName | EventTag_OwnerName | EventTag_ObjectEvent,
	  NULL,
	  6,
	  EGROUP_DDL_SCHEMA,
	  0
	},


	//-----------------------------------------------
	// CREATE LOGIN Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATELOGIN,
	  x_eet_Create_Login,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_LOGIN",
	  EventTag_LoginEvent,
	  NULL,
	  7,
	  EGROUP_DDL_LOGIN,
	  0
	},

	//-----------------------------------------------
	// ALTER LOGIN Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTERLOGIN,
	  x_eet_Alter_Login,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_LOGIN",
	  EventTag_LoginEvent,
	  NULL,
	  7,
	  EGROUP_DDL_LOGIN,
	  0
	},

	//-----------------------------------------------
	// DROP LOGIN Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROPLOGIN,
	  x_eet_Drop_Login,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_LOGIN",
	  EventTag_LoginEvent,
	  NULL,
	  7,
	  EGROUP_DDL_LOGIN,
	  0
	},

	//-----------------------------------------------
	// LOGON Event Schema
	//-----------------------------------------------
	{ ETYP_ON_LOGON,
	  x_eet_Logon,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS | EFLAG_SYNC_ONLY,
	  L"LOGON",
	  EventTag_LoginType | EventTag_SID | EventTag_ClientHost | EventTag_IsPooled,
	  NULL,
	  4,
	  EGROUP_ALL,
	  0
	},

	//-----------------------------------------------
	// ADD SERVER ROLE MEMBER (sp_AddSrvRoleMember) Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ADDSRVROLEMEMBER,
	  x_eet_Add_Server_Role_Member,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ADD_SERVER_ROLE_MEMBER",
	  EventTag_LoginEvent | EventTag_RoleEvent | EventTag_TSQLCommand,
	  NULL,
	  BitCount64(EventTag_LoginEvent | EventTag_RoleEvent | EventTag_TSQLCommand),
	  EGROUP_DDL_SERVER_SECURITY,
	  0
	},

	//-----------------------------------------------
	// DROP SERVER ROLE MEMBER (sp_DropSrvRoleMember) Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROPSRVROLEMEMBER,
	  x_eet_Drop_Server_Role_Member,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_SERVER_ROLE_MEMBER",
	  EventTag_LoginEvent | EventTag_RoleEvent | EventTag_TSQLCommand,
	  NULL,
	  BitCount64(EventTag_LoginEvent | EventTag_RoleEvent | EventTag_TSQLCommand),
	  EGROUP_DDL_SERVER_SECURITY,
	  0
	},

	//-----------------------------------------------
	// CREATE SERVERROLE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATESERVERROLE,
	  x_eet_Create_ServerRole,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_SERVER_ROLE",
	  EventTag_ServerEvent | EventTag_SID,
	  NULL,
	  BitCount64(EventTag_ServerEvent | EventTag_SID),
	  EGROUP_DDL_SERVER_SECURITY,
	  0
	},

	//-----------------------------------------------
	// ALTER SERVERROLE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTERSERVERROLE,
	  x_eet_Alter_ServerRole,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_SERVER_ROLE",
	  EventTag_ServerEvent | EventTag_SID,
	  NULL,
	  BitCount64(EventTag_ServerEvent | EventTag_SID),
	  EGROUP_DDL_SERVER_SECURITY,
	  0
	},

	//-----------------------------------------------
	// DROP SERVERROLE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROPSERVERROLE,
	  x_eet_Drop_ServerRole,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_SERVER_ROLE",
	  EventTag_ServerEvent | EventTag_SID,
	  NULL,
	  BitCount64(EventTag_ServerEvent | EventTag_SID),
	  EGROUP_DDL_SERVER_SECURITY,
	  0
	},
	
	//-----------------------------------------------
	// CREATE ENDPOINT Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATE_ENDPOINT,
	  x_eet_Create_Endpoint,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_ENDPOINT",
	  EventTag_ServerEvent,
	  NULL,
	  3,
	  EGROUP_DDL_ENDPOINT,
	  0
	},

	//-----------------------------------------------
	// ALTER ENDPOINT Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTER_ENDPOINT,
	  x_eet_Alter_Endpoint,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_ENDPOINT",
	  EventTag_ServerEvent,
	  NULL,
	  3,
	  EGROUP_DDL_ENDPOINT,
	  0
	},

	//-----------------------------------------------
	// DROP ENDPOINT Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROP_ENDPOINT,
	  x_eet_Drop_Endpoint,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_ENDPOINT",
	  EventTag_ServerEvent,
	  NULL,
	  3,
	  EGROUP_DDL_ENDPOINT,
	  0
	},

	//***********************************************************************
	//	START: Service Broker Events
	//
	//***********************************************************************

	//-----------------------------------------------
	// CREATE MSGTYPE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATEMSGTYPE,
	  x_eet_Create_MsgType,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_MESSAGE_TYPE",
	  EventTag_SchemaLessDDL,
	  NULL,
	  4,
	  EGROUP_DDL_MSGTYPE,
	  0
	},

	//-----------------------------------------------
	// ALTER MSGTYPE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTERMSGTYPE,
	  x_eet_Alter_MsgType,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_MESSAGE_TYPE",
	  EventTag_SchemaLessDDL,
	  NULL,
	  4,
	  EGROUP_DDL_MSGTYPE,
	  0
	},

	//-----------------------------------------------
	// DROP MSGTYPE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROPMSGTYPE,
	  x_eet_Drop_MsgType,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_MESSAGE_TYPE",
	  EventTag_SchemaLessDDL,
	  NULL,
	  4,
	  EGROUP_DDL_MSGTYPE,
	  0
	},


	//-----------------------------------------------
	// CREATE CONTRACT Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATECONTRACT,
	  x_eet_Create_Contract,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_CONTRACT",
	  EventTag_SchemaLessDDL,
	  NULL,
	  4,
	  EGROUP_DDL_CONTRACT,
	  0
	},
	
	//-----------------------------------------------
	// DROP CONTRACT Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROPCONTRACT,
	  x_eet_Drop_Contract,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_CONTRACT",
	  EventTag_SchemaLessDDL,
	  NULL,
	  4,
	  EGROUP_DDL_CONTRACT,
	  0
	},


	//-----------------------------------------------
	// CREATE QUEUE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATEQUEUE,
	  x_eet_Create_Queue,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_QUEUE",
	  EventTag_SchemaDDL,
	  NULL,
	  5,
	  EGROUP_DDL_QUEUE,
	  0
	},

	//-----------------------------------------------
	// ALTER QUEUE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTERQUEUE,
	  x_eet_Alter_Queue,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_QUEUE",
	  EventTag_SchemaDDL,
	  NULL,
	  5,
	  EGROUP_DDL_QUEUE,
	  0
	},

	//-----------------------------------------------
	// DROP QUEUE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROPQUEUE,
	  x_eet_Drop_Queue,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_QUEUE",
	  EventTag_SchemaDDL,
	  NULL,
	  5,
	  EGROUP_DDL_QUEUE,
	  0
	},


	//-----------------------------------------------
	// CREATE SERVICE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATESERVICE,
	  x_eet_Create_Service,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_SERVICE",
	  EventTag_SchemaLessFullTargetDDL,
	  NULL,
	  7,
	  EGROUP_DDL_SERVICE,
	  0
	},

	//-----------------------------------------------
	// ALTER SERVICE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTERSERVICE,
	  x_eet_Alter_Service,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_SERVICE",
	  EventTag_SchemaLessFullTargetDDL,
	  NULL,
	  7,
	  EGROUP_DDL_SERVICE,
	  0
	},

	//-----------------------------------------------
	// DROP SERVICE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROPSERVICE,
	  x_eet_Drop_Service,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_SERVICE",
	  EventTag_SchemaLessFullTargetDDL,
	  NULL,
	  7,
	  EGROUP_DDL_SERVICE,
	  0
	},

	//-----------------------------------------------
	// CREATE ROUTE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATEROUTE,
	  x_eet_Create_Route,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_ROUTE",
	  EventTag_SchemaLessDDL,
	  NULL,
	  4,
	  EGROUP_DDL_ROUTE,
	  0
	},

	//-----------------------------------------------
	// ALTER ROUTE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTERROUTE,
	  x_eet_Alter_Route,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_ROUTE",
	  EventTag_SchemaLessDDL,
	  NULL,
	  4,
	  EGROUP_DDL_ROUTE,
	  0
	},

	//-----------------------------------------------
	// DROP ROUTE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROPROUTE,
	  x_eet_Drop_Route,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_ROUTE",
	  EventTag_SchemaLessDDL,
	  NULL,
	  4,
	  EGROUP_DDL_ROUTE,
	  0
	},

	//-----------------------------------------------
	// CREATE BINDING Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATEBINDING,
	  x_eet_Create_Binding,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_REMOTE_SERVICE_BINDING",
	  EventTag_SchemaLessDDL,
	  NULL,
	  4,
	  EGROUP_DDL_BINDING,
	  0
	},

	//-----------------------------------------------
	// ALTER BINDING Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTERBINDING,
	  x_eet_Alter_Binding,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_REMOTE_SERVICE_BINDING",
	  EventTag_SchemaLessDDL,
	  NULL,
	  4,
	  EGROUP_DDL_BINDING,
	  0
	},

	//-----------------------------------------------
	// DROP BINDING Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROPBINDING,
	  x_eet_Drop_Binding,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_REMOTE_SERVICE_BINDING",
	  EventTag_SchemaLessDDL,
	  NULL,
	  4,
	  EGROUP_DDL_BINDING,
	  0
	},

	//-----------------------------------------------
	// CREATE BROKER PRIORITY Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATEPRIORITY,
	  x_eet_Create_Priority,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_BROKER_PRIORITY",
	  EventTag_SchemaLessDDL,
	  NULL,
	  4,
	  EGROUP_DDL_PRIORITY,
	  0
	},

	//-----------------------------------------------
	// ALTER BROKER PRIORITY Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTERPRIORITY,
	  x_eet_Alter_Priority,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_BROKER_PRIORITY",
	  EventTag_SchemaLessDDL,
	  NULL,
	  4,
	  EGROUP_DDL_PRIORITY,
	  0
	},

	//-----------------------------------------------
	// DROP BROKER PRIORITY Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROPPRIORITY,
	  x_eet_Drop_Priority,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_BROKER_PRIORITY",
	  EventTag_SchemaLessDDL,
	  NULL,
	  4,
	  EGROUP_DDL_PRIORITY,
	  0
	},

	//***********************************************************************
	//	END: Service Broker Events
	//
	//***********************************************************************

	//***********************************************************************
	//	START: Grant Deny Revoke Events
	//
	//***********************************************************************

	//-----------------------------------------------
	// GRANT_SERVER Event Schema
	//-----------------------------------------------
	{ ETYP_ON_GRANT_SERVER,
	  x_eet_Grant_Server,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"GRANT_SERVER",
	  EventTag_GDR,
	  NULL,
	  7,
	  EGROUP_DDL_GDR_SERVER,
	  0
	},

	//-----------------------------------------------
	// DENY_SERVER Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DENY_SERVER,
	  x_eet_Deny_Server,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DENY_SERVER",
	  EventTag_GDR,
	  NULL,
	  7,
	  EGROUP_DDL_GDR_SERVER,
	  0
	},

	//-----------------------------------------------
	// REVOKE_SERVER Event Schema
	//-----------------------------------------------
	{ ETYP_ON_REVOKE_SERVER,
	  x_eet_Revoke_Server,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"REVOKE_SERVER",
	  EventTag_GDR,
	  NULL,
	  7,
	  EGROUP_DDL_GDR_SERVER,
	  0
	},


	//-----------------------------------------------
	// GRANT_DATABASE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_GRANT_DATABASE,
	  x_eet_Grant_Database,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"GRANT_DATABASE",
	  EventTag_GDRDatabase,
	  NULL,
	  11,
	  EGROUP_DDL_GDR_DATABASE,
	  0
	},

	//-----------------------------------------------
	// DENY_DATABASE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DENY_DATABASE,
	  x_eet_Deny_Database,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DENY_DATABASE",
	  EventTag_GDRDatabase,
	  NULL,
	  11,
	  EGROUP_DDL_GDR_DATABASE,
	  0
	},

	//-----------------------------------------------
	// REVOKE_DATABASE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_REVOKE_DATABASE,
	  x_eet_Revoke_Database,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"REVOKE_DATABASE",
	  EventTag_GDRDatabase,
	  NULL,
	  11,
	  EGROUP_DDL_GDR_DATABASE,
	  0
	},


	//***********************************************************************
	//	END: Grant Deny Revoke Events
	//
	//***********************************************************************
	
	//-----------------------------------------------
	// CREATE XML SCHEMA COLLECTION Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATE_XML_SCHEMA_COLLECTION,
	  x_eet_Create_XmlSchemaCollection,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_XML_SCHEMA_COLLECTION",
	  EventTag_SchemaDDL,
	  NULL,
	  5,
	  EGROUP_DDL_XML_SCHEMA_COLLECTION,
	  0
	},

	//-----------------------------------------------
	// ALTER XMLSCHEMA Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTER_XML_SCHEMA_COLLECTION,
	  x_eet_Alter_XmlSchemaCollection,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_XML_SCHEMA_COLLECTION",
	  EventTag_SchemaDDL,
	  NULL,
	  5,
	  EGROUP_DDL_XML_SCHEMA_COLLECTION,
	  0
	},
	
	//-----------------------------------------------
	// DROP XMLSCHEMA Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROP_XML_SCHEMA_COLLECTION,
	  x_eet_Drop_XmlSchemaCollection,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_XML_SCHEMA_COLLECTION",
	  EventTag_SchemaDDL,
	  NULL,
	  5,
	  EGROUP_DDL_XML_SCHEMA_COLLECTION,
	  0
	},


	//-----------------------------------------------
	// CREATE CERTIFICATE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATECERT,
	  x_eet_Create_Cert,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_CERTIFICATE",
	  EventTag_ObjectOwnerKeyEvent | EventTag_CertificatePath | EventTag_PrivateKeyPath | EventTag_CertificateSubject | EventTag_DatabaseEvent,
	  NULL,
	  BitCount64(EventTag_ObjectOwnerKeyEvent | EventTag_CertificatePath | EventTag_PrivateKeyPath | EventTag_CertificateSubject | EventTag_DatabaseEvent),
	  EGROUP_DDL_CERTIFICATE,
	  0
	},
	
	//-----------------------------------------------
	// ALTER CERTIFICATE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTERCERT,
	  x_eet_Alter_Cert,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_CERTIFICATE",
	  EventTag_ObjectOwnerKeyEvent | EventTag_DatabaseEvent,
	  NULL,
	  BitCount64(EventTag_ObjectOwnerKeyEvent | EventTag_DatabaseEvent),
	  EGROUP_DDL_CERTIFICATE,
	  0
	},
	
	//-----------------------------------------------
	// DROP CERTIFICATE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROPCERT,
	  x_eet_Drop_Cert,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_CERTIFICATE",
	  EventTag_ObjectOwnerEvent | EventTag_DatabaseEvent,
	  NULL,
	  BitCount64(EventTag_ObjectOwnerEvent | EventTag_DatabaseEvent),
	  EGROUP_DDL_CERTIFICATE,
	  0
	},

	//-----------------------------------------------
	// CREATE SYMMETRIC KEY Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATEOBFUSKEY,
	  x_eet_Create_ObfusKey,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_SYMMETRIC_KEY",
	  EventTag_ObjectOwnerEvent | EventTag_DatabaseEvent,
	  NULL,
	  BitCount64(EventTag_ObjectOwnerEvent | EventTag_DatabaseEvent),
	  EGROUP_DDL_OBFUSKEY,
	  0
	},
	
	//-----------------------------------------------
	// ALTER SYMMETRIC KEY  Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTEROBFUSKEY,
	  x_eet_Alter_ObfusKey,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_SYMMETRIC_KEY",
	  EventTag_ObjectOwnerEvent | EventTag_DatabaseEvent,
	  NULL,
	  BitCount64(EventTag_ObjectOwnerEvent | EventTag_DatabaseEvent),
	  EGROUP_DDL_OBFUSKEY,
	  0
	},
	
	//-----------------------------------------------
	// DROP SYMMETRIC KEY  Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROPOBFUSKEY,
	  x_eet_Drop_ObfusKey,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_SYMMETRIC_KEY",
	  EventTag_ObjectOwnerEvent | EventTag_DatabaseEvent,
	  NULL,
	  BitCount64(EventTag_ObjectOwnerEvent | EventTag_DatabaseEvent),
	  EGROUP_DDL_OBFUSKEY,
	  0
	},
	
	//-----------------------------------------------
	// CREATE ASYMMETRIC KEY Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATEASYMKEY,
	  x_eet_Create_AsymKey,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_ASYMMETRIC_KEY",
	  EventTag_ObjectOwnerEvent | EventTag_DatabaseEvent | EventTag_KeyPath,
	  NULL,
	  BitCount64(EventTag_ObjectOwnerEvent | EventTag_DatabaseEvent | EventTag_KeyPath),
	  EGROUP_DDL_ASYMKEY,
	  0
	},
	
	//-----------------------------------------------
	// ALTER ASYMMETRIC KEY  Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTERASYMKEY,
	  x_eet_Alter_AsymKey,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_ASYMMETRIC_KEY",
	  EventTag_ObjectOwnerEvent | EventTag_DatabaseEvent,
	  NULL,
	  BitCount64(EventTag_ObjectOwnerEvent | EventTag_DatabaseEvent),
	  EGROUP_DDL_ASYMKEY,
	  0
	},
	
	//-----------------------------------------------
	// DROP ASYMMETRIC KEY  Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROPASYMKEY,
	  x_eet_Drop_AsymKey,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_ASYMMETRIC_KEY",
	  EventTag_ObjectOwnerEvent | EventTag_DatabaseEvent,
	  NULL,
	  BitCount64(EventTag_ObjectOwnerEvent | EventTag_DatabaseEvent),
	  EGROUP_DDL_ASYMKEY,
	  0
	},

	//-----------------------------------------------
	// ALTER SERVICE MASTER KEY Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTERSRVMASTERKEY,
	  x_eet_Alter_SrvMasterKey,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_SERVICE_MASTER_KEY",
	  EventTag_ObjectType | EventTag_TSQLCommand,
	  NULL,
	  BitCount64(EventTag_ObjectType | EventTag_TSQLCommand),
	  EGROUP_DDL_SRVMASTERKEY,
	  0
	},

	//-----------------------------------------------
	// CREATE MASTER KEY Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATEDBMASTERKEY,
	  x_eet_Create_DbMasterKey,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_MASTER_KEY",
	  EventTag_DatabaseEvent | EventTag_ObjectType,
	  NULL,
	  BitCount64(EventTag_DatabaseEvent | EventTag_ObjectType),
	  EGROUP_DDL_DBMASTERKEY,
	  0
	},

	//-----------------------------------------------
	// ALTER MASTER KEY Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTERDBMASTERKEY,
	  x_eet_Alter_DbMasterKey,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_MASTER_KEY",
	  EventTag_DatabaseEvent | EventTag_ObjectType,
	  NULL,
	  BitCount64(EventTag_DatabaseEvent | EventTag_ObjectType),
	  EGROUP_DDL_DBMASTERKEY,
	  0
	},

	//-----------------------------------------------
	// DROP MASTER KEY Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROPDBMASTERKEY,
	  x_eet_Drop_DbMasterKey,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_MASTER_KEY",
	  EventTag_DatabaseEvent | EventTag_ObjectType,
	  NULL,
	  BitCount64(EventTag_DatabaseEvent | EventTag_ObjectType),
	  EGROUP_DDL_DBMASTERKEY,
	  0
	},

	//-----------------------------------------------
	// CREATE DEK Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATEDEK,
	  x_eet_Create_DEK,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_NEW_TRANS,
	  L"CREATE_DATABASE_ENCRYPTION_KEY",
	  EventTag_DatabaseEvent | EventTag_ObjectType,
	  NULL,
	  BitCount64(EventTag_DatabaseEvent | EventTag_ObjectType),
	  EGROUP_DDL_DEK,
	  0
	},

	//-----------------------------------------------
	// ALTER DEK Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTERDEK,
	  x_eet_Alter_DEK,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_NEW_TRANS,
	  L"ALTER_DATABASE_ENCRYPTION_KEY",
	  EventTag_DatabaseEvent | EventTag_ObjectType,
	  NULL,
	  BitCount64(EventTag_DatabaseEvent | EventTag_ObjectType),
	  EGROUP_DDL_DEK,
	  0
	},

	//-----------------------------------------------
	// DROP DEK Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROPDEK,
	  x_eet_Drop_DEK,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_NEW_TRANS,
	  L"DROP_DATABASE_ENCRYPTION_KEY",
	  EventTag_DatabaseEvent | EventTag_ObjectType,
	  NULL,
	  BitCount64(EventTag_DatabaseEvent | EventTag_ObjectType),
	  EGROUP_DDL_DEK,
	  0
	},

	//-----------------------------------------------
	// ADD SIGNATURE  on Schema Object Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ADDSIGN_SCH_OBJ,
	  x_eet_Add_Signature_SchObj,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ADD_SIGNATURE_SCHEMA_OBJECT",
	  EventTag_DatabaseEvent | EventTag_ObjectEvent |EventTag_SchemaName | EventTag_CounterSignature,
	  NULL,
	  BitCount64(EventTag_DatabaseEvent | EventTag_ObjectEvent |EventTag_SchemaName | EventTag_CounterSignature),
	  EGROUP_DDL_CRYPTOSIGN,
	  0
	},

	//-----------------------------------------------
	// DROP SIGNATURE  on Schema Object Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROPSIGN_SCH_OBJ,
	  x_eet_Drop_Signature_SchObj,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_SIGNATURE_SCHEMA_OBJECT",
	  EventTag_DatabaseEvent | EventTag_ObjectEvent |EventTag_SchemaName | EventTag_CounterSignature,
	  NULL,
	  BitCount64(EventTag_DatabaseEvent | EventTag_ObjectEvent |EventTag_SchemaName | EventTag_CounterSignature),
	  EGROUP_DDL_CRYPTOSIGN,
	  0
	},

	//-----------------------------------------------
	// ADD SIGNATURE   Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ADDSIGN,
	  x_eet_Add_Signature,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ADD_SIGNATURE",
	  EventTag_DatabaseEvent | EventTag_ObjectEvent | EventTag_CounterSignature,
	  NULL,
	  BitCount64(EventTag_DatabaseEvent | EventTag_ObjectEvent | EventTag_CounterSignature),
	  EGROUP_DDL_CRYPTOSIGN,
	  0
	},

	//-----------------------------------------------
	// DROP SIGNATURE  Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROPSIGN,
	  x_eet_Drop_Signature,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_SIGNATURE",
	  EventTag_DatabaseEvent | EventTag_ObjectEvent | EventTag_CounterSignature,
	  NULL,
	  BitCount64(EventTag_DatabaseEvent | EventTag_ObjectEvent | EventTag_CounterSignature),
	  EGROUP_DDL_CRYPTOSIGN,
	  0
	},
	
	//-----------------------------------------------
	// CREATE CREDENTIAL Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATECREDENTIAL,
	  x_eet_Create_Credential,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_CREDENTIAL",
	  EventTag_ServerEvent,
	  NULL,
	  BitCount64(EventTag_ServerEvent),
	  EGROUP_DDL_CREDENTIAL,
	  0
	},
	
	//-----------------------------------------------
	// ALTER CREDENTIAL  Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTERCREDENTIAL,
	  x_eet_Alter_Credential,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_CREDENTIAL",
	  EventTag_ServerEvent,
	  NULL,
	  BitCount64(EventTag_ServerEvent),
	  EGROUP_DDL_CREDENTIAL,
	  0
	},
	
	//-----------------------------------------------
	// DROP CREDENTIAL  Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROPCREDENTIAL,
	  x_eet_Drop_Credential,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_CREDENTIAL",
	  EventTag_ServerEvent,
	  NULL,
	  BitCount64(EventTag_ServerEvent),
	  EGROUP_DDL_CREDENTIAL,
	  0
	},

	//-----------------------------------------------
	// CREATE CRYPTO PROVIDER Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATECRYPTOPROV,
	  x_eet_Create_CryptoProv,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_CRYPTOGRAPHIC_PROVIDER",
	  EventTag_ServerEvent,
	  NULL,
	  BitCount64(EventTag_ServerEvent),
	  EGROUP_DDL_CRYPTOPROV,
	  0
	},
	
	//-----------------------------------------------
	// ALTER CRYPTO PROVIDER Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTERCRYPTOPROV,
	  x_eet_Alter_CryptoProv,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_CRYPTOGRAPHIC_PROVIDER",
	  EventTag_ServerEvent,
	  NULL,
	  BitCount64(EventTag_ServerEvent),
	  EGROUP_DDL_CRYPTOPROV,
	  0
	},
	
	//-----------------------------------------------
	// DROP CRYPTO PROVIDER Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROPCRYPTOPROV,
	  x_eet_Drop_CryptoProv,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_CRYPTOGRAPHIC_PROVIDER",
	  EventTag_ServerEvent,
	  NULL,
	  BitCount64(EventTag_ServerEvent),
	  EGROUP_DDL_CRYPTOPROV,
	  0
	},

	//-----------------------------------------------
	// ALTER AUTHORIZATION Server Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTERAUTH_SERVER,
	  x_eet_Alter_Auth_Server,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_AUTHORIZATION_SERVER",
	  EventTag_ObjectOwnerEvent | EventTag_TSQLCommand,
	  NULL,
	  4,
	  EGROUP_DDL_AUTH_SERVER,
	  0
	},

	//-----------------------------------------------
	// ALTER AUTHORIZATION Database Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTERAUTH_DATABASE,
	  x_eet_Alter_Auth_Database,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_AUTHORIZATION_DATABASE",
	  EventTag_SchemaDDL | EventTag_OwnerName,
	  NULL,
	  6,
	  EGROUP_DDL_AUTH_DATABASE,
	  0
	},

	//***********************************************************************
	// START START	-  PARTITION RELATED  -  START START
	//
	//***********************************************************************

	//-----------------------------------------------
	// CREATE PARTITION FUNCTION Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATEPRTFUNCTION,
	  x_eet_Create_Partition_Function,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_PARTITION_FUNCTION",
	  EventTag_SchemaLessDDL,
	  NULL,
	  4,
	  EGROUP_DDL_PRTFUNCTION,
	  0
	},

	//-----------------------------------------------
	// ALTER PARTITION FUNCTION Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTERPRTFUNCTION,
	  x_eet_Alter_Partition_Function,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_PARTITION_FUNCTION",
	  EventTag_SchemaLessDDL,
	  NULL,
	  4,
	  EGROUP_DDL_PRTFUNCTION,
	  0
	},
	
	//-----------------------------------------------
	// DROP PARTITION FUNCTION Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROPPRTFUNCTION,
	  x_eet_Drop_Partition_Function,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_PARTITION_FUNCTION",
	  EventTag_SchemaLessDDL,
	  NULL,
	  4,
	  EGROUP_DDL_PRTFUNCTION,
	  0
	},

	//-----------------------------------------------
	// CREATE PARTITION SCHEME Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATEPRTSCHEME,
	  x_eet_Create_Partition_Scheme,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_PARTITION_SCHEME",
	  EventTag_SchemaLessDDL | EventTag_Function,
	  NULL,
	  5,
	  EGROUP_DDL_PRTSCHEME,
	  0
	},

	//-----------------------------------------------
	// ALTER PARTITION SCHEME Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTERPRTSCHEME,
	  x_eet_Alter_Partition_Scheme,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_PARTITION_SCHEME",
	  EventTag_SchemaLessDDL | EventTag_Function,
	  NULL,
	  5,
	  EGROUP_DDL_PRTSCHEME,
	  0
	},
	
	//-----------------------------------------------
	// DROP PARTITION SCHEME Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROPPRTSCHEME,
	  x_eet_Drop_Partition_Scheme,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_PARTITION_SCHEME",
	  EventTag_SchemaLessDDL | EventTag_Function,
	  NULL,
	  5,
	  EGROUP_DDL_PRTSCHEME,
	  0
	},
	
	//-----------------------------------------------
	// CREATE [PRIMARY] XML INDEX Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATE_XML_INDEX,
	  x_eet_Create_XML_Index,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_XML_INDEX",
	  EventTag_SchemaTargetDDL | EventTag_PrimaryXMLIndexName | EventTag_SecondaryXMLIndexType,
	  NULL,
	  9,
	  EGROUP_DDL_INDEX,
	  0
	},

	//-----------------------------------------------
	// SP_UPDATEEXTENDEDPROPERTY Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTER_EXTENDED_PROPERTY,
	  x_eet_Alter_Extended_Property,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_EXTENDED_PROPERTY",
	  EventTag_SPSchemaTargetDDL | EventTag_ExtendedPropertyEvent,
	  NULL,
	  10,
	  EGROUP_DDL_EXTENDED_PROPERTY,
	  0
	},
	//-----------------------------------------------
	// ALTER FULLTEXT CATALOG Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTER_FULLTEXT_CATALOG,
	  x_eet_Alter_Fulltext_Catalog,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_FULLTEXT_CATALOG",
	  EventTag_SchemaLessDDL,
	  NULL,
	  4,
	  EGROUP_DDL_FULLTEXT_CATALOG,
	  0
	},
	//-----------------------------------------------
	// ALTER FULLTEXT INDEX Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTER_FULLTEXT_INDEX,
	  x_eet_Alter_Fulltext_Index,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_FULLTEXT_INDEX",
	  EventTag_SchemaDDL,
	  NULL,
	  5,
	  EGROUP_DDL_INDEX,
	  0
	},
	//-----------------------------------------------
	// SP_CONFIGURE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTER_INSTANCE,
	  x_eet_Alter_Instance,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_INSTANCE",
	  EventTag_ExtendedPropertyEvent | EventTag_TSQLCommand | EventTag_Parameters,
	  NULL,
	  4,
	  EGROUP_DDL_SERVER_LEVEL,
	  0
	},
	//-----------------------------------------------
	// SP_SERVEROPTION Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTER_LINKED_SERVER,
	  x_eet_Alter_Linked_Server,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_LINKED_SERVER",
	  EventTag_SPObjectEvent,
	  NULL,
	  4,
	  EGROUP_DDL_LINKED_SERVER,
	  0
	},
	//-----------------------------------------------
	// SP_ALTERMESSAGE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTER_MESSAGE,
	  x_eet_Alter_Message,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_MESSAGE",
	  EventTag_SPObjectEvent,
	  NULL,
	  4,
	  EGROUP_DDL_MESSAGE,
	  0
	},
	//-----------------------------------------------
	// SP_CONTROL_PLAN_GUIDE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTER_PLAN_GUIDE,
	  x_eet_Alter_Plan_Guide,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_PLAN_GUIDE",
	  EventTag_SPDatabaseEvent | EventTag_ObjectEvent,
	  NULL,
	  5,
	  EGROUP_DDL_PLAN_GUIDE,
	  0
	},
	//-----------------------------------------------
	// SP_SERVEROPTION Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTER_REMOTE_SERVER,
	  x_eet_Alter_Remote_Server,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_REMOTE_SERVER",
	  EventTag_SPObjectEvent,
	  NULL,
	  4,
	  EGROUP_DDL_REMOTE_SERVER,
	  0
	},
	//-----------------------------------------------
	// SP_BINDEFAULT Event Schema
	//-----------------------------------------------
	{ ETYP_ON_BIND_DEFAULT,
	  x_eet_Bind_Default,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"BIND_DEFAULT",
	  EventTag_SPSchemaDDL,
	  NULL,
	  6,
	  EGROUP_DDL_DEFAULT,
	  0
	},
	//-----------------------------------------------
	// SP_BINDRULE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_BIND_RULE,
	  x_eet_Bind_Rule,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"BIND_RULE",
	  EventTag_SPSchemaDDL,
	  NULL,
	  6,
	  EGROUP_DDL_RULE,
	  0
	},
	//-----------------------------------------------
	// CREATE DEFAULT Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATE_DEFAULT,
	  x_eet_Create_Default,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_DEFAULT",
	  EventTag_SchemaDDL,
	  NULL,
	  5,
	  EGROUP_DDL_DEFAULT,
	  0
	},
	//-----------------------------------------------
	// SP_ADDEXTENDEDPROC Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATE_EXTENDED_PROCEDURE,
	  x_eet_Create_Extended_Procedure,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_EXTENDED_PROCEDURE",
	  EventTag_SPObjectEvent,
	  NULL,
	  4,
	  EGROUP_DDL_EXTENDED_PROCEDURE,
	  0
	},
	//-----------------------------------------------
	// SP_ADDEXTENDEDPROPERTY Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATE_EXTENDED_PROPERTY,
	  x_eet_Create_Extended_Property,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_EXTENDED_PROPERTY",
	  EventTag_SPSchemaTargetDDL | EventTag_ExtendedPropertyEvent,
	  NULL,
	  10,
	  EGROUP_DDL_EXTENDED_PROPERTY,
	  0
	},
	//-----------------------------------------------
	// CREATE FULLTEXT CATALOG Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATE_FULLTEXT_CATALOG,
	  x_eet_Create_Fulltext_Catalog,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_FULLTEXT_CATALOG",
	  EventTag_SchemaLessDDL,
	  NULL,
	  4,
	  EGROUP_DDL_FULLTEXT_CATALOG,
	  0
	},
	//-----------------------------------------------
	// CREATE FULLTEXT INDEX Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATE_FULLTEXT_INDEX,
	  x_eet_Create_Fulltext_Index,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_FULLTEXT_INDEX",
	  EventTag_SchemaDDL,
	  NULL,
	  5,
	  EGROUP_DDL_INDEX,
	  0
	},
	//-----------------------------------------------
	// SP_ADDLINKEDSERVER Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATE_LINKED_SERVER,
	  x_eet_Create_Linked_Server,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_LINKED_SERVER",
	  EventTag_SPObjectEvent,
	  NULL,
	  4,
	  EGROUP_DDL_LINKED_SERVER,
	  0
	},
	//-----------------------------------------------
	// SP_ADDLINKEDSRVLOGIN Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATE_LINKED_SERVER_LOGIN,
	  x_eet_Create_Linked_Server_Login,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_LINKED_SERVER_LOGIN",
	  EventTag_SPObjectTargetEvent,
	  NULL,
	  6,
	  EGROUP_DDL_LINKED_SERVER_LOGIN,
	  0
	},
	//-----------------------------------------------
	// SP_ADDMESSAGE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATE_MESSAGE,
	  x_eet_Create_Message,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_MESSAGE",
	  EventTag_SPObjectEvent,
	  NULL,
	  4,
	  EGROUP_DDL_MESSAGE,
	  0
	},
	//-----------------------------------------------
	// SP_CREATE_PLAN_GUIDE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATE_PLAN_GUIDE,
	  x_eet_Create_Plan_Guide,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_PLAN_GUIDE",
	  EventTag_SPDatabaseEvent | EventTag_ObjectEvent,
	  NULL,
	  5,
	  EGROUP_DDL_PLAN_GUIDE,
	  0
	},
	//-----------------------------------------------
	// SP_ADDSERVER Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATE_REMOTE_SERVER,
	  x_eet_Create_Remote_Server,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_REMOTE_SERVER",
	  EventTag_SPObjectEvent,
	  NULL,
	  4,
	  EGROUP_DDL_REMOTE_SERVER,
	  0
	},
	//-----------------------------------------------
	// CREATE RULE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATE_RULE,
	  x_eet_Create_Rule,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_RULE",
	  EventTag_SchemaDDL,
	  NULL,
	  5,
	  EGROUP_DDL_RULE,
	  0
	},
	//-----------------------------------------------
	// DROP DEFAULT Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROP_DEFAULT,
	  x_eet_Drop_Default,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_DEFAULT",
	  EventTag_SchemaDDL,
	  NULL,
	  5,
	  EGROUP_DDL_DEFAULT,
	  0
	},
	//-----------------------------------------------
	// SP_DROPEXTENDEDPROC Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROP_EXTENDED_PROCEDURE,
	  x_eet_Drop_Extended_Procedure,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_EXTENDED_PROCEDURE",
	  EventTag_SPObjectEvent,
	  NULL,
	  4,
	  EGROUP_DDL_EXTENDED_PROCEDURE,
	  0
	},
	//-----------------------------------------------
	// SP_DROPEXTENDEDPROPERTY Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROP_EXTENDED_PROPERTY,
	  x_eet_Drop_Extended_Property,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_EXTENDED_PROPERTY",
	  EventTag_SPSchemaTargetDDL | EventTag_PropertyName,
	  NULL,
	  9,
	  EGROUP_DDL_EXTENDED_PROPERTY,
	  0
	},
	//-----------------------------------------------
	// DROP FULLTEXT CATALOG Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROP_FULLTEXT_CATALOG,
	  x_eet_Drop_Fulltext_Catalog,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_FULLTEXT_CATALOG",
	  EventTag_SchemaLessDDL,
	  NULL,
	  4,
	  EGROUP_DDL_FULLTEXT_CATALOG,
	  0
	},
	//-----------------------------------------------
	// DROP FULLTEXT INDEX Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROP_FULLTEXT_INDEX,
	  x_eet_Drop_Fulltext_Index,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_FULLTEXT_INDEX",
	  EventTag_SchemaDDL,
	  NULL,
	  5,
	  EGROUP_DDL_INDEX,
	  0
	},
	//-----------------------------------------------
	// SP_DROPSERVER Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROP_LINKED_SERVER,
	  x_eet_Drop_Linked_Server,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_LINKED_SERVER",
	  EventTag_SPObjectEvent,
	  NULL,
	  4,
	  EGROUP_DDL_LINKED_SERVER,
	  0
	},
	//-----------------------------------------------
	// SP_DROPLINKEDSRVLOGIN Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROP_LINKED_SERVER_LOGIN,
	  x_eet_Drop_Linked_Server_Login,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_LINKED_SERVER_LOGIN",
	  EventTag_SPObjectTargetEvent,
	  NULL,
	  6,
	  EGROUP_DDL_LINKED_SERVER_LOGIN,
	  0
	},
	//-----------------------------------------------
	// SP_DROPMESSAGE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROP_MESSAGE,
	  x_eet_Drop_Message,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_MESSAGE",
	  EventTag_SPObjectEvent,
	  NULL,
	  4,
	  EGROUP_DDL_MESSAGE,
	  0
	},
	//-----------------------------------------------
	// SP_CONTROL_PLAN_GUIDE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROP_PLAN_GUIDE,
	  x_eet_Drop_Plan_Guide,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_PLAN_GUIDE",
	  EventTag_SPDatabaseEvent | EventTag_ObjectEvent,
	  NULL,
	  5,
	  EGROUP_DDL_PLAN_GUIDE,
	  0
	},
	//-----------------------------------------------
	// SP_DROPSERVER Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROP_REMOTE_SERVER,
	  x_eet_Drop_Remote_Server,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_REMOTE_SERVER",
	  EventTag_SPObjectEvent,
	  NULL,
	  4,
	  EGROUP_DDL_REMOTE_SERVER,
	  0
	},
	//-----------------------------------------------
	// DROP RULE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROP_RULE,
	  x_eet_Drop_Rule,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_RULE",
	  EventTag_SchemaDDL,
	  NULL,
	  5,
	  EGROUP_DDL_RULE,
	  0
	},
	
	//-----------------------------------------------
	// SP_RENAME Event Schema
	//-----------------------------------------------
	{ ETYP_ON_RENAME,
	  x_eet_Rename,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"RENAME",
	  EventTag_SPSchemaTargetDDL | EventTag_NewObjectName,
	  NULL,
	  9,
	  EGROUP_DDL_DATABASE_LEVEL,
	  0
	},
	//-----------------------------------------------
	// SP_UNBINDEFAULT Event Schema
	//-----------------------------------------------
	{ ETYP_ON_UNBIND_DEFAULT,
	  x_eet_Unbind_Default,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"UNBIND_DEFAULT",
	  EventTag_SPSchemaDDL,
	  NULL,
	  6,
	  EGROUP_DDL_DEFAULT,
	  0
	},
	//-----------------------------------------------
	// SP_UNBINDRULE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_UNBIND_RULE,
	  x_eet_Unbind_Rule,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"UNBIND_RULE",
	  EventTag_SPSchemaDDL,
	  NULL,
	  6,
	  EGROUP_DDL_RULE,
	  0
	},
	//***********************************************************************
	// END END	-  PARTITION RELATED  -  END END
	//
	//***********************************************************************

	//-----------------------------------------------
	// CREATE FULLTEXT STOPLIST Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATE_FULLTEXT_STOPLIST,
	  x_eet_Create_Fulltext_StopList,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_FULLTEXT_STOPLIST",
	  EventTag_SchemaLessDDL,
	  NULL,
	  4,
	  EGROUP_DDL_FULLTEXT_STOPLIST,
	  0
	},
	//-----------------------------------------------
	// ALTER FULLTEXT STOPLIST Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTER_FULLTEXT_STOPLIST,
	  x_eet_Alter_Fulltext_StopList,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_FULLTEXT_STOPLIST",
	  EventTag_SchemaLessDDL,
	  NULL,
	  4,
	  EGROUP_DDL_FULLTEXT_STOPLIST,
	  0
	},
	//-----------------------------------------------
	// DROP FULLTEXT STOPLIST Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROP_FULLTEXT_STOPLIST,
	  x_eet_Drop_Fulltext_StopList,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_FULLTEXT_STOPLIST",
	  EventTag_SchemaLessDDL,
	  NULL,
	  4,
	  EGROUP_DDL_FULLTEXT_STOPLIST,
	  0
	},

    //-----------------------------------------------
	// CREATE PROPERTY LIST Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATE_PROPERTYLIST,
	  x_eet_Create_PropertyList,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_SEARCH_PROPERTY_LIST",
	  EventTag_SchemaLessDDL,
	  NULL,
	  4,
	  EGROUP_DDL_PROPERTYLIST,
	  0
	},
	//-----------------------------------------------
	// ALTER FULLTEXT PROPERTY LIST Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTER_PROPERTYLIST,
	  x_eet_Alter_PropertyList,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_SEARCH_PROPERTY_LIST",
	  EventTag_SchemaLessDDL,
	  NULL,
	  4,
	  EGROUP_DDL_PROPERTYLIST,
	  0
	},
	//-----------------------------------------------
	// DROP FULLTEXT PROPERTY LIST Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROP_PROPERTYLIST,
	  x_eet_Drop_PropertyList,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_SEARCH_PROPERTY_LIST",
	  EventTag_SchemaLessDDL,
	  NULL,
	  4,
	  EGROUP_DDL_PROPERTYLIST,
	  0
	},

	//-----------------------------------------------
	// CREATE_EVENT_SESSION Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATE_EVENT_SESSION,
	  x_eet_Create_Event_Session,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_EVENT_SESSION",
	  EventTag_ServerEvent,
	  NULL,
	  BitCount64(EventTag_ServerEvent),
	  EGROUP_DDL_EVENT_SESSION,
	  0
	},

	//-----------------------------------------------
	// ALTER_EVENT_SESSION Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTER_EVENT_SESSION,
	  x_eet_Alter_Event_Session,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_EVENT_SESSION",
	  EventTag_ServerEvent,
	  NULL,
	  BitCount64(EventTag_ServerEvent),
	  EGROUP_DDL_EVENT_SESSION,
	  0
	},

	//-----------------------------------------------
	// DROP_EVENT_SESSION Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROP_EVENT_SESSION,
	  x_eet_Drop_Event_Session,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_EVENT_SESSION",
	  EventTag_ServerEvent,
	  NULL,
	  BitCount64(EventTag_ServerEvent),
	  EGROUP_DDL_EVENT_SESSION,
	  0
	},

	//-----------------------------------------------
	// CREATE RESOURCE POOL Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATE_RES_POOL,
	  x_eet_Create_Resource_Pool,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_RESOURCE_POOL",
	  EventTag_ServerEvent,
	  NULL,
	  BitCount64(EventTag_ServerEvent),
	  EGROUP_DDL_RESOURCE_POOL,
	  0
	},

	//-----------------------------------------------
	// ALTER RESOURCE POOL Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTER_RES_POOL,
	  x_eet_Alter_Resource_Pool,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_RESOURCE_POOL",
	  EventTag_ServerEvent,
	  NULL,
	  BitCount64(EventTag_ServerEvent),
	  EGROUP_DDL_RESOURCE_POOL,
	  0
	},

	//-----------------------------------------------
	// DROP RESOURCE POOL Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROP_RES_POOL,
	  x_eet_Drop_Resource_Pool,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_RESOURCE_POOL",
	  EventTag_ServerEvent,
	  NULL,
	  BitCount64(EventTag_ServerEvent),
	  EGROUP_DDL_RESOURCE_POOL,
	  0
	},

	//-----------------------------------------------
	// CREATE WORKLOAD GROUP Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATE_RES_GROUP,
	  x_eet_Create_Resource_Group,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_WORKLOAD_GROUP",
	  EventTag_ServerEvent,
	  NULL,
	  BitCount64(EventTag_ServerEvent),
	  EGROUP_DDL_RESOURCE_GROUP,
	  0
	},

	//-----------------------------------------------
	// ALTER WORKLOAD GROUP Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTER_RES_GROUP,
	  x_eet_Alter_Resource_Group,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_WORKLOAD_GROUP",
	  EventTag_ServerEvent,
	  NULL,
	  BitCount64(EventTag_ServerEvent),
	  EGROUP_DDL_RESOURCE_GROUP,
	  0
	},

	//-----------------------------------------------
	// DROP WORKLOAD GROUP Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROP_RES_GROUP,
	  x_eet_Drop_Resource_Group,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_WORKLOAD_GROUP",
	  EventTag_ServerEvent,
	  NULL,
	  BitCount64(EventTag_ServerEvent),
	  EGROUP_DDL_RESOURCE_GROUP,
	  0
	},
	
	//-----------------------------------------------
	// ALTER RESOURCE GOVERNOR CONFIGURATION Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTER_RES_GOVERNOR_CONFIG,
	  x_eet_Alter_Resource_Governor_Config,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_RESOURCE_GOVERNOR_CONFIG",
	  EventTag_ServerEvent,
	  NULL,
	  BitCount64(EventTag_ServerEvent),
	  EGROUP_DDL_RESOURCE_GOVERNOR,
	  0
	},


	//-----------------------------------------------
	// CREATE SPATIAL INDEX Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATE_SPATIAL_INDEX,
	  x_eet_Create_Spatial_Index,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_SPATIAL_INDEX",
	  EventTag_SchemaTargetDDL,
	  NULL,
	  BitCount64(	EventTag_SchemaTargetDDL),
	  EGROUP_DDL_INDEX,
	  0
	},

	// Audit Related Events
	//
	//-----------------------------------------------
	// CREATE SERVER AUDIT Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATE_SERVER_AUDIT,
	  x_eet_Create_ServerAudit,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_SERVER_AUDIT",
	  EventTag_ServerEvent,
	  NULL,
	  BitCount64(EventTag_ServerEvent),
	  EGROUP_DDL_SERVERAUDIT,
	  0
	},

	//-----------------------------------------------
	// ALTER SERVER AUDIT Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTER_SERVER_AUDIT,
	  x_eet_Alter_ServerAudit,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_SERVER_AUDIT",
	  EventTag_ServerEvent,
	  NULL,
	  BitCount64(EventTag_ServerEvent),
	  EGROUP_DDL_SERVERAUDIT,
	  0
	},

	//-----------------------------------------------
	// DROP SERVER AUDIT Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROP_SERVER_AUDIT,
	  x_eet_Drop_ServerAudit,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_SERVER_AUDIT",
	  EventTag_ServerEvent,
	  NULL,
	  BitCount64(EventTag_ServerEvent),
	  EGROUP_DDL_SERVERAUDIT,
	  0
	},

	//-----------------------------------------------
	// CREATE SERVER AUDIT SPEC Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATE_SERVER_AUDIT_SPEC,
	  x_eet_Create_ServerAuditSpec,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_SERVER_AUDIT_SPECIFICATION",
	  EventTag_ServerEvent,
	  NULL,
	  BitCount64(EventTag_ServerEvent),
	  EGROUP_DDL_SERVERAUDITSPEC,
	  0
	},

	//-----------------------------------------------
	// ALTER SERVER AUDIT SPEC Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTER_SERVER_AUDIT_SPEC,
	  x_eet_Alter_ServerAuditSpec,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_SERVER_AUDIT_SPECIFICATION",
	  EventTag_ServerEvent,
	  NULL,
	  BitCount64(EventTag_ServerEvent),
	  EGROUP_DDL_SERVERAUDITSPEC,
	  0
	},

	//-----------------------------------------------
	// DROP SERVER AUDIT SPEC Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROP_SERVER_AUDIT_SPEC,
	  x_eet_Drop_ServerAuditSpec,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_SERVER_AUDIT_SPECIFICATION",
	  EventTag_ServerEvent,
	  NULL,
	  BitCount64(EventTag_ServerEvent),
	  EGROUP_DDL_SERVERAUDITSPEC,
	  0
	},

	//-----------------------------------------------
	// CREATE DB AUDIT SPEC Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATE_DB_AUDIT_SPEC,
	  x_eet_Create_DbAuditSpec,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_DATABASE_AUDIT_SPECIFICATION",
	  EventTag_DatabaseEvent | EventTag_ObjectEvent,
	  NULL,
	  BitCount64(EventTag_DatabaseEvent | EventTag_ObjectEvent),
	  EGROUP_DDL_DBAUDITSPEC,
	  0
	},

	//-----------------------------------------------
	// ALTER DB AUDIT SPEC Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTER_DB_AUDIT_SPEC,
	  x_eet_Alter_DbAuditSpec,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_DATABASE_AUDIT_SPECIFICATION",
	  EventTag_DatabaseEvent | EventTag_ObjectEvent,
	  NULL,
	  BitCount64(EventTag_DatabaseEvent | EventTag_ObjectEvent),
	  EGROUP_DDL_DBAUDITSPEC,
	  0
	},

	//-----------------------------------------------
	// DROP DB AUDIT SPEC Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROP_DB_AUDIT_SPEC,
	  x_eet_Drop_DbAuditSpec,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_DATABASE_AUDIT_SPECIFICATION",
	  EventTag_DatabaseEvent | EventTag_ObjectEvent,
	  NULL,
	  BitCount64(EventTag_DatabaseEvent | EventTag_ObjectEvent),
	  EGROUP_DDL_DBAUDITSPEC,
	  0
	},

	//-----------------------------------------------
	// CREATE SEQUENCE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATE_SEQUENCE,
	  x_eet_Create_Sequence,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_SEQUENCE",
	  EventTag_SchemaDDL,
	  NULL,
	  BitCount64(EventTag_SchemaDDL),
	  EGROUP_DDL_SEQUENCE,
	  0
	},

	//-----------------------------------------------
	// ALTER SEQUENCE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTER_SEQUENCE,
	  x_eet_Alter_Sequence,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_SEQUENCE",
	  EventTag_SchemaDDL,
	  NULL,
	  BitCount64(EventTag_SchemaDDL),
	  EGROUP_DDL_SEQUENCE,
	  0
	},

	//-----------------------------------------------
	// DROP SEQUENCE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROP_SEQUENCE,
	  x_eet_Drop_Sequence,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_SEQUENCE",
	  EventTag_SchemaDDL,
	  NULL,
	  BitCount64(EventTag_SchemaDDL),
	  EGROUP_DDL_SEQUENCE,
	  0
	},

	//-----------------------------------------------
	// CREATE AVAILABILITY GROUP Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATE_AVAILABILITY_GROUP,
	  x_eet_Create_Availability_Group,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_AVAILABILITY_GROUP",
	  EventTag_ServerEvent,
	  NULL,
	  BitCount64(EventTag_ServerEvent),
	  EGROUP_DDL_AVAILABILITY_GROUP,
	  0
	},

	//-----------------------------------------------
	// ALTER AVAILABILITY GROUP Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTER_AVAILABILITY_GROUP,
	  x_eet_Alter_Availability_Group,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_AVAILABILITY_GROUP",
	  EventTag_ServerEvent,
	  NULL,
	  BitCount64(EventTag_ServerEvent),
	  EGROUP_DDL_AVAILABILITY_GROUP,
	  0
	},

	//-----------------------------------------------
	// DROP AVAILABILITY GROUP Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROP_AVAILABILITY_GROUP,
	  x_eet_Drop_Availability_Group,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_AVAILABILITY_GROUP",
	  EventTag_ServerEvent,
	  NULL,
	  BitCount64(EventTag_ServerEvent),
	  EGROUP_DDL_AVAILABILITY_GROUP,
	  0
	},

	//-----------------------------------------------
	// CREATE DATABASE AUDIT Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATE_DATABASE_AUDIT,
	  x_eet_Create_Database_Audit,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_AUDIT",
	  EventTag_DatabaseEvent | EventTag_ObjectEvent,
	  NULL,
	  BitCount64(EventTag_DatabaseEvent | EventTag_ObjectEvent),
	  EGROUP_DDL_DBAUDIT,
	  0
	},

	//-----------------------------------------------
	// DROP DATABASE AUDIT Event Schema
	//-----------------------------------------------
	  { ETYP_ON_DROP_DATABASE_AUDIT,
	  x_eet_Drop_Database_Audit,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_AUDIT",
	  EventTag_DatabaseEvent | EventTag_ObjectEvent,
	  NULL,
	  BitCount64(EventTag_DatabaseEvent | EventTag_ObjectEvent),
	  EGROUP_DDL_DBAUDIT,
	  0
	  },

	//-----------------------------------------------
	// ALTER DATABASE AUDIT Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTER_DATABASE_AUDIT,
	  x_eet_Alter_Database_Audit,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_AUDIT",
	  EventTag_DatabaseEvent | EventTag_ObjectEvent,
	  NULL,
	  BitCount64(EventTag_DatabaseEvent | EventTag_ObjectEvent),
	  EGROUP_DDL_DBAUDIT,
	  0
	},

	//-----------------------------------------------
	// CREATE SECURITY POLICY Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATE_SECURITY_POLICY,
	  x_eet_Create_Security_Policy,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_SECURITY_POLICY",
	  EventTag_SchemaDDL,
	  NULL,
	  BitCount64(EventTag_SchemaDDL),
	  EGROUP_DDL_SECURITY_POLICY,
	  0
	},

	//-----------------------------------------------
	// ALTER SECURITY POLICY Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTER_SECURITY_POLICY,
	  x_eet_Alter_Security_Policy,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_SECURITY_POLICY",
	  EventTag_SchemaDDL,
	  NULL,
	  BitCount64(EventTag_SchemaDDL),
	  EGROUP_DDL_SECURITY_POLICY,
	  0
	},

	//-----------------------------------------------
	// DROP SECURITY POLICY Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROP_SECURITY_POLICY,
	  x_eet_Drop_Security_Policy,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_SECURITY_POLICY",
	  EventTag_SchemaDDL,
	  NULL,
	  BitCount64(EventTag_SchemaDDL),
	  EGROUP_DDL_SECURITY_POLICY,
	  0
	},

	//-----------------------------------------------
	// CREATE COLUMN MASTER KEY Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATE_COL_MASTER_KEY,
	  x_eet_Create_Col_Master_Key,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_COLUMN_MASTER_KEY",
	  EventTag_DatabaseEvent | EventTag_ObjectEvent,
	  NULL,
	  BitCount64(EventTag_DatabaseEvent | EventTag_ObjectEvent),
	  EGROUP_DDL_COL_MASTER_KEY,
	  0
	},

	//-----------------------------------------------
	// DROP COLUMN MASTER KEY Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROP_COL_MASTER_KEY,
	  x_eet_Drop_Col_Master_Key,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_COLUMN_MASTER_KEY",
	  EventTag_DatabaseEvent | EventTag_ObjectEvent,
	  NULL,
	  BitCount64(EventTag_DatabaseEvent | EventTag_ObjectEvent),
	  EGROUP_DDL_COL_MASTER_KEY,
	  0
	},

	//-----------------------------------------------
	// CREATE COLUMN ENCRYPTION KEY Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATE_COL_ENCRYPTION_KEY,
	  x_eet_Create_Col_Encryption_Key,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_COLUMN_ENCRYPTION_KEY",
	  EventTag_DatabaseEvent | EventTag_ObjectEvent,
	  NULL,
	  BitCount64(EventTag_DatabaseEvent | EventTag_ObjectEvent),
	  EGROUP_DDL_COL_ENCRYPTION_KEY,
	  0
	},

	//-----------------------------------------------
	// ALTER COLUMN ENCRYPTION KEY Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTER_COL_ENCRYPTION_KEY,
	  x_eet_Alter_Col_Encryption_Key,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_COLUMN_ENCRYPTION_KEY",
	  EventTag_DatabaseEvent | EventTag_ObjectEvent,
	  NULL,
	  BitCount64(EventTag_DatabaseEvent | EventTag_ObjectEvent),
	  EGROUP_DDL_COL_ENCRYPTION_KEY,
	  0
	},

	//-----------------------------------------------
	// DROP COLUMN ENCRYPTION KEY Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROP_COL_ENCRYPTION_KEY,
	  x_eet_Drop_Col_Encryption_Key,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_COLUMN_ENCRYPTION_KEY",
	  EventTag_DatabaseEvent | EventTag_ObjectEvent,
	  NULL,
	  BitCount64(EventTag_DatabaseEvent | EventTag_ObjectEvent),
	  EGROUP_DDL_COL_ENCRYPTION_KEY,
	  0
	},

	//-----------------------------------------------
	// ALTER DATABASE SCOPED CONFIG Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTER_DB_SCOPED_CONFIG,
	  x_eet_Alter_DB_Scoped_Config,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_DATABASE_SCOPED_CONFIGURATION",
	  EventTag_DatabaseEvent,
	  NULL,
	  BitCount64(EventTag_DatabaseEvent),
	  EGROUP_DDL_DATABASE_LEVEL,
	  0
	},

	//-----------------------------------------------
	// CREATE EXTERNAL RESOURCE POOL Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATE_EXTERNAL_RESOURCE_POOL,
	  x_eet_Create_External_Resource_Pool,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_EXTERNAL_RESOURCE_POOL",
	  EventTag_ServerEvent,
	  NULL,
	  BitCount64(EventTag_ServerEvent),
	  EGROUP_DDL_EXTERNAL_RESOURCE_POOL,
	  0
	},

	//-----------------------------------------------
	// ALTER EXTERNAL RESOURCE POOL Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTER_EXTERNAL_RESOURCE_POOL,
	  x_eet_Alter_External_Resource_Pool,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_EXTERNAL_RESOURCE_POOL",
	  EventTag_ServerEvent,
	  NULL,
	  BitCount64(EventTag_ServerEvent),
	  EGROUP_DDL_EXTERNAL_RESOURCE_POOL,
	  0
	},

	//-----------------------------------------------
	// DROP EXTERNAL RESOURCE POOL Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROP_EXTERNAL_RESOURCE_POOL,
	  x_eet_Drop_External_Resource_Pool,
	  EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_EXTERNAL_RESOURCE_POOL",
	  EventTag_ServerEvent,
	  NULL,
	  BitCount64(EventTag_ServerEvent),
	  EGROUP_DDL_EXTERNAL_RESOURCE_POOL,
	  0
	},

	//-----------------------------------------------
	// CREATE EXTERNAL LIBRARY Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATE_EXTERNAL_LIBRARY,
	  x_eet_Create_External_Library,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"CREATE_EXTERNAL_LIBRARY",
	  EventTag_SchemaLessDDL,
	  NULL,
	  4,
	  EGROUP_DDL_LIBRARY,
	  0
	},

	//-----------------------------------------------
	// ALTER EXTERNAL LIBRARY Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTER_EXTERNAL_LIBRARY,
	  x_eet_Alter_External_Library,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ALTER_EXTERNAL_LIBRARY",
	  EventTag_SchemaLessDDL,
	  NULL,
	  4,
	  EGROUP_DDL_LIBRARY,
	  0
	},

	//-----------------------------------------------
	// DROP EXTERNAL LIBRARY Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROP_EXTERNAL_LIBRARY,
	  x_eet_Drop_External_Library,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_EXTERNAL_LIBRARY",
	  EventTag_SchemaLessDDL,
	  NULL,
	  4,
	  EGROUP_DDL_LIBRARY,
	  0
	},

	//-----------------------------------------------
	// ADD SENSITIVITY CLASSIFICATION Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ADD_SENSITIVITY_CLASSIFICATION,
	  x_eet_Add_Sensitivity_Classification,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"ADD_SENSITIVITY_CLASSIFICATION",
	  EventTag_SchemaDDL,
	  NULL,
	  BitCount64(EventTag_SchemaDDL),
	  EGROUP_DDL_SENSITIVITY,
	  0
	},

	//-----------------------------------------------
	// DROP SENSITIVITY CLASSIFICATION Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROP_SENSITIVITY_CLASSIFICATION,
	  x_eet_Drop_Sensitivity_Classification,
	  EOBJTYP_DATABASE | EOBJTYP_SERVER,
	  EFLAG_SAME_TRANS,
	  L"DROP_SENSITIVITY_CLASSIFICATION",
	  EventTag_SchemaDDL,
	  NULL,
	  BitCount64(EventTag_SchemaDDL),
	  EGROUP_DDL_SENSITIVITY,
	  0
	},

	//-----------------------------------------------
	// CREATE EXTERNAL LANGUAGE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_CREATE_EXTERNAL_LANGUAGE,
	x_eet_Create_External_Language,
	EOBJTYP_DATABASE | EOBJTYP_SERVER,
	EFLAG_SAME_TRANS,
	L"CREATE_EXTERNAL_LANGUAGE",
	EventTag_SchemaLessDDL,
	NULL,
	BitCount64(EventTag_SchemaLessDDL),
	EGROUP_DDL_EXTERNAL_LANGUAGE,
	0
	},

	//-----------------------------------------------
	// ALTER EXTERNAL LANGUAGE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ALTER_EXTERNAL_LANGUAGE,
	x_eet_Alter_External_Language,
	EOBJTYP_DATABASE | EOBJTYP_SERVER,
	EFLAG_SAME_TRANS,
	L"ALTER_EXTERNAL_LANGUAGE",
	EventTag_SchemaLessDDL,
	NULL,
	BitCount64(EventTag_SchemaLessDDL),
	EGROUP_DDL_EXTERNAL_LANGUAGE,
	0
	},

	//-----------------------------------------------
	// DROP EXTERNAL LANGUAGE Event Schema
	//-----------------------------------------------
	{ ETYP_ON_DROP_EXTERNAL_LANGUAGE,
	x_eet_Drop_External_Language,
	EOBJTYP_DATABASE | EOBJTYP_SERVER,
	EFLAG_SAME_TRANS,
	L"DROP_EXTERNAL_LANGUAGE",
	EventTag_SchemaLessDDL,
	NULL,
	BitCount64(EventTag_SchemaLessDDL),
	EGROUP_DDL_EXTERNAL_LANGUAGE,
	0
	},

	//***********************************************************************
	// START  -  NON DDL EVENT TYPES  -  START
	//***********************************************************************

	//-----------------------------------------------
	// SERVICE QUEUE ACTIVATION Event Schema
	//-----------------------------------------------
	{ ETYP_ON_ACTIVATION,
	  x_eet_Activation,
	  EOBJTYP_SVCQ,
	  EFLAG_ASYNC_ONLY,
	  L"QUEUE_ACTIVATION",
	  EventTag_ObjectEvent | EventTag_DatabaseName | EventTag_SchemaName,
	  NULL,
	  4,
	  EGROUP_ALL,
	  0
	},

	//-----------------------------------------------
	// SERVICE QUEUE DISABLED Event Schema
	//-----------------------------------------------
	{ ETYP_ON_QUEUE_DISABLED,
	  x_eet_Queue_Disabled,
	  EOBJTYP_SVCQ,
	  EFLAG_ASYNC_ONLY | EFLAG_DDLADMN_CAD_PERM,
	  L"BROKER_QUEUE_DISABLED",
	  EventTag_ObjectEvent | EventTag_DatabaseName | EventTag_SchemaName,
	  NULL,
	  4,
	  EGROUP_ALL,
	  0
	},

	//-----------------------------------------------
	// ALTER SERVER CONFIGURATION Event Schema
	// ALTER SERVER does not support transactional semantics and does not expose a DDL trigger
	//-----------------------------------------------
	{ ETYP_ON_ALTER_SERVER_CONFIG,
	  x_eet_Alter_Server_Config,
	  EOBJTYP_SERVER,
	  EFLAG_ASYNC_ONLY,	
	  L"ALTER_SERVER_CONFIGURATION",
	  EventTag_ObjectType | EventTag_TSQLCommand,
	  NULL,
	  BitCount64(EventTag_ObjectType | EventTag_TSQLCommand),
	  EGROUP_ALL,
	  0
	},

	//***********************************************************************
	// END	-  NON DDL EVENT TYPES	-  END
	//***********************************************************************

	//-------------------------------------------------
	// SQL Trace events.  Do not add regular events below this!!!
	//-------------------------------------------------
#include "schema.inc"
};

