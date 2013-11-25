
#include "Connection.h"
#include "QueryJob.h"
#include "nodefunction.h"
#include <uv.h>
extern uv_mutex_t mutex_t;
extern unsigned int g_curr_thread_count;
Persistent<FunctionTemplate> Connection::constructorTemplate;

void Connection::Init(Handle<Object> target) 
{
	HandleScope scope;
	Local<FunctionTemplate> t = FunctionTemplate::New(New);
	constructorTemplate = Persistent<FunctionTemplate>::New(t);
	constructorTemplate->InstanceTemplate()->SetInternalFieldCount(1);
	constructorTemplate->SetClassName(String::NewSymbol("Connection"));

	/*NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "execute", Execute);
	NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "close", Close);
	NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "isConnected", IsConnected);
	NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "setAutoCommit", SetAutoCommit);
	NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "commit", Commit);
	NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "rollback", Rollback);*/
	NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "close", Close);
	NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "queryHistory", QueryHistory);
	NODE_SET_PROTOTYPE_METHOD(constructorTemplate, "queryTempdata", QueryTempdata);
	target->Set(String::NewSymbol("Connection"), constructorTemplate->GetFunction());
}

Handle<Value> Connection::New(const Arguments& args)
{
	HandleScope scope;

	Connection *connection = new Connection();
	connection->Wrap(args.This());
	return args.This();
}

Connection::Connection() 
{
}

Connection::~Connection() 
{
	closeConnection();
}

//历史数据
Handle<Value>Connection::QueryHistory(const Arguments& args)
{   
	HandleScope scope;
	Connection* pConnection = ObjectWrap::Unwrap<Connection>(args.This());
	string sql = NodeFunc::MergeSql(args);
	//cout<<"ÊÕµœµÄsqlÓïŸä:"<<sql<<std::endl;
	QueryJob* query_job = new QueryJob();
	query_job->sql = sql;
	query_job->js_obj = Persistent<Object>::New(args[args.Length()-1]->ToObject());
	query_job->pConn = pConnection->m_connection;

	//×¢²á»Øµ÷º¯Êý
	uv_async_init(uv_default_loop(),&query_job->main_async,query_asyn_thread_callback);
	//ŽŽœšÏß³Ì
	uv_thread_create(&query_job->worker_thread,query_asyn_thread_work_histroy,query_job);
	return scope.Close(Undefined());


}
void Connection::query_asyn_thread_work_histroy(void* arg)
{
	QueryJob* query_job = static_cast<QueryJob*>(arg);
	//uv_sem_wait(&sem);
	query_job->queryHistoryTricks(query_job);
	//uv_sem_post(&sem);
	query_job->main_async.data = query_job;
	uv_async_send(&query_job->main_async);

}

Handle<Value>Connection::QueryTempdata(const Arguments& args)
{   
	HandleScope scope;
	Connection* pConnection = ObjectWrap::Unwrap<Connection>(args.This());
	string sql = NodeFunc::MergeSql(args);
	//cout<<"ÊÕµœµÄsqlÓïŸä:"<<sql<<std::endl;
	QueryJob* query_job = new QueryJob();
	query_job->sql = sql;
	query_job->js_obj = Persistent<Object>::New(args[args.Length()-1]->ToObject());
	query_job->pConn = pConnection->m_connection;

	//注册回调函数
	uv_async_init(uv_default_loop(),&query_job->main_async,query_asyn_thread_callback);
	//创建线程
	uv_thread_create(&query_job->worker_thread,query_asyn_thread_work_histroy,query_job);
	return scope.Close(Undefined());


}
void Connection::query_asyn_thread_work_tempdata(void* arg)
{
	QueryJob* query_job = static_cast<QueryJob*>(arg);
	//uv_sem_wait(&sem);
	//query_job->query(query_job);
	//uv_sem_post(&sem);
	query_job->main_async.data = query_job;
	uv_async_send(&query_job->main_async);

}

void Connection::query_asyn_thread_callback(uv_async_t* req,int status)
{
	HandleScope scope;
	QueryJob* query_job = static_cast<QueryJob*>(req->data);
	Local<Value>argv[2];
	if(query_job->error !="")
	{
#ifdef OS_WIN32
		argv[0] = String::New(encodeConv::CodingConv::ascii2Utf8(query_job->error.c_str()).c_str());
#else
		argv[0] = String::New(query_job->error.c_str());
#endif
		
		argv[1] = *Undefined();


	}
	else{
		//vector<map<string,string> >&result = query_job->result;
		//typedef vector<map<string,string> >::iterator const_it;
		//Local<Array>array = Array::New(result.size());
		//int j = 0;
		//for (const_it it = result.begin();it != result.end();++it)
		//{

		//	map<string,string>::iterator map_it;
		//	Local<Object>obj = Object::New();
		//	for (map_it =it->begin();map_it!= it->end();++map_it)
		//	{
		//		//cout<<map_it->first<<":"<<map_it->second<<endl;
		//		obj->Set(String::NewSymbol(map_it->first.c_str()), 
		//			String::New(encodeConv::CodingConv::ascii2Utf8(map_it->second.c_str()).c_str()));

		//	}
		//	array->Set(j,obj);
		//	j++;
		//}


		argv[0]=*Undefined();
#ifdef OS_WIN32
		//cout<<"win 32"<<query_job->result<<endl;
		argv[1] = String::New(encodeConv::CodingConv::ascii2Utf8(query_job->result.c_str()).c_str());
#else

		
		//cout<<query_job->result.c_str()<<endl;
		int length = strlen(query_job->result.c_str());
		length = int(length *1.5 ) +1;
		char* buffer = new char[length];
		memset(buffer,0,length);
		int ret = gb2312_to_utf8((char*)query_job->result.c_str(),buffer,length);
		//if(ret !=0)
		//{
				//printf("%s\n",buffer);
		//}
		
		//printf("%s\n",buffer);
	
		argv[1] = String::New(buffer);
		delete []buffer;
//argv[1] = String::New(encodeConv::CodingConv::ascii2Utf8(query_job->result.c_str()).c_str());
#endif
	
	}
	query_job->js_obj->CallAsFunction(Object::New(),2,argv);
	query_job->js_obj.Dispose();
	uv_close((uv_handle_t*)&query_job->main_async,uv_close_func);

	scope.Close(Undefined());

}

void Connection::uv_close_func(uv_handle_t* handle)
{
	
	QueryJob* job_ptr= (QueryJob *)handle->data;
	delete job_ptr;
	job_ptr = NULL;

};

Handle<Value> Connection::Close(const Arguments& args) 
{
	try 
	{
		Connection* connection = ObjectWrap::Unwrap<Connection>(args.This());
		connection->closeConnection();

		return Undefined();
	} 
	catch (const std::exception& ex) 
	{
		printf("Exception: %s\n", ex.what());
		return Undefined();
	}
}

void Connection::setConnection(COTLConn* connection) 
{

	m_connection = connection;
}


void Connection::closeConnection() 
{

	uv_mutex_lock(&mutex_t);
	if( m_connection) 
	{
		m_connection->OTLDisconnect();
		delete m_connection;
		m_connection = NULL;
		g_curr_thread_count--;
	}
	uv_mutex_unlock(&mutex_t);

}
