
#ifndef  _ORACLE_BINDINGS_
#define _ORACLE_BINDINGS_

#include <v8.h>
#include <node.h>
using namespace node;
using namespace v8;



class OracleClient : public ObjectWrap
{
public:
	static void Init(Handle<Object> target);
	static Handle<Value> New(const Arguments& args);
	static Handle<Value> Connect(const Arguments& args);
	static void EIO_Connect(uv_work_t* req);
	static void EIO_AfterConnect(uv_work_t* req, int status);

	OracleClient();
	~OracleClient();
	//static OCIConPool *_pool;
	//unsigned int max_thread_count;
	//unsigned int current_thread_count;


private:
	static Persistent<FunctionTemplate> s_ct;
	
};
#endif