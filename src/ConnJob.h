#ifndef _CONN_JOB_
#define  _CONN_JOB_
#include "../../core/OTLConn.h"
#include "oracle_bindings.h"
#include <node.h>
#include <v8.h>
using namespace v8;
class ConnJob
{
public:
	ConnJob(void)
	{
		pClient = NULL;
		//error = NULL;
		pConnect = NULL;
	}
	~ConnJob(void){}
public:
	string strDblink;
	string strUserName;
	string strPwd;
	Persistent<Object>js_obj;
	OracleClient* pClient;
	//const char* error;
	string error;
	COTLConn* pConnect;

	uv_work_t req;

};

#endif