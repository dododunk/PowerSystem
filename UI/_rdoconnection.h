// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class CrdoTables;
class CrdoPreparedStatements;
class CrdoResultsets;
class C_rdoResultset;
class CrdoPreparedStatement;
class CrdoQueries;
class C_rdoEnvironment;

/////////////////////////////////////////////////////////////////////////////
// C_rdoConnection wrapper class

class C_rdoConnection : public COleDispatchDriver
{
public:
	C_rdoConnection() {}		// Calls COleDispatchDriver default constructor
	C_rdoConnection(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	C_rdoConnection(const C_rdoConnection& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetQueryTimeout();
	void SetQueryTimeout(long nNewValue);
	CrdoTables GetRdoTables();
	CrdoResultsets GetRdoResultsets();
	CString GetConnect();
	void SetConnect(LPCTSTR lpszNewValue);
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	long GetRowsAffected();
	BOOL GetTransactions();
	BOOL GetUpdatable();
	CString GetVersion();
	long GetHDbc();
	BOOL GetStillExecuting();
	long GetAsyncCheckInterval();
	void SetAsyncCheckInterval(long nNewValue);
	void Close();
	void Execute(LPCTSTR Source, const VARIANT& Options);
	C_rdoResultset OpenResultset(LPCTSTR Name, const VARIANT& Type, const VARIANT& LockType, const VARIANT& Options);
	void BeginTrans();
	void CommitTrans();
	void RollbackTrans();
	void Cancel();
	C_rdoResultset GetLastQueryResults();
	long GetCursorDriver();
	void SetCursorDriver(long nNewValue);
	long GetLoginTimeout();
	void SetLoginTimeout(long nNewValue);
	void EstablishConnection(const VARIANT& Prompt, const VARIANT& Readonly, const VARIANT& Options);
	BOOL GetStillConnecting();
	CrdoPreparedStatement CreateQuery(LPCTSTR Name, const VARIANT& SqlString);
	CrdoQueries GetRdoQueries();
	CString GetLogMessages();
	void SetLogMessages(LPCTSTR lpszNewValue);
};