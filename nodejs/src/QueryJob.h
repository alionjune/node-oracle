#ifndef _QUERY_JOB_H_
#define _QUERY_JOB_H_

#include <node.h>
#include <v8.h>
using namespace v8;
#include "../../core/OTLConn.h"



class QueryJob
{
public:
	string sql; //sql½Å±¾
	Persistent<Object>js_obj;
	uv_async_t main_async;
	uv_work_t work_pool;
	//uv_loop_t* loop;
	uv_thread_t worker_thread;
	//Local<Array> array;
	//const char* error;//´íÎó
	string error;
	COTLConn* pConn;
	string result; //½á¹û

public:
	//static void query(string sql,OCIConnection* pConn,vector<map<string,string> >&result);
	static void queryTempdata(QueryJob* query_job);
	static void queryHistoryTricks(QueryJob* query_job);


	QueryJob(){pConn = NULL;}
	~QueryJob(){};


};
#endif

