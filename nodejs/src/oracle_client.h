
#ifndef  _ORACLE_CLIENT_H
#define _ORACLE_CLIENT_H
#include <v8.h>
#include <node.h>
using namespace node;
using namespace v8;


class OracleClient : public ObjectWrap
{
public:
	static void Init(Handle<Object> target);
	static Handle<Value> New(const Arguments& args);
	/*static Handle<Value> Connect(const Arguments& args);*/
	static Handle<Value> CreateConnPool(const Arguments& args);//创建数据库连接池
// private:
// 	static void EIO_Connect(uv_work_t* req);
// 	static void EIO_AfterConnect(uv_work_t* req, int status); //回调函数
public:
	OracleClient();
	~OracleClient();
public:
	static Persistent<FunctionTemplate> s_ct; //FunctionTemplate 用以将 C++ 函数暴露给脚本环境
	
};
#endif