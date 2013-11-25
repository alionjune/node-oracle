#ifndef _CONNECTION_H_
#define  _CONNECTION_H_
#include <v8.h>
#include <node.h>
using namespace node;
using namespace v8;
#include "../../core/OTLConn.h"

//#include "../../third_party/CodingConv/encodeutil.h"

class Connection : public ObjectWrap
{
public:
	//typedef tuple< Connection*,string,string,Persistent<Function>,Local<Array>   > BUNDLE;   //传递参数的数据结构 
public:
	static void Init(Handle<Object> target);
	static Handle<Value> New(const Arguments& args);
	static Persistent<FunctionTemplate> constructorTemplate;
	static Handle<Value> Close(const Arguments& args);
	static Handle<Value> QueryTempdata(const Arguments& args);
	static Handle<Value> QueryHistory(const Arguments& args);

	//static void EIO_Query(uv_work_t* req);
	//static void EIO_AfterQuery(uv_work_t* req);

	void closeConnection();
	Connection();
	~Connection();
	void setConnection(COTLConn*connection);
private:
	COTLConn* m_connection;

private:
	static void query_asyn_thread_work_tempdata(void* arg);
	static void query_asyn_thread_work_histroy(void* arg);
	static void query_asyn_thread_callback(uv_async_t* req,int status);

	static void uv_close_func(uv_handle_t* handle);
	
};

#endif
