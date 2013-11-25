#include "oracle_bindings.h"
#include "Connection.h"
#include "ConnJob.h"
#include "nodefunction.h"

uv_mutex_t mutex_t; 
Persistent<FunctionTemplate> OracleClient::s_ct;

unsigned int g_max_thread_count = 20;
unsigned int g_curr_thread_count = 0;



OracleClient::OracleClient(){}
OracleClient::~OracleClient(){}
void OracleClient::Init(Handle<Object> target)
{
	HandleScope scope;

	Local<FunctionTemplate> t = FunctionTemplate::New(New);
	s_ct = Persistent<FunctionTemplate>::New(t);
	s_ct->InstanceTemplate()->SetInternalFieldCount(1);
	s_ct->SetClassName(String::NewSymbol("OracleClient"));
	NODE_SET_PROTOTYPE_METHOD(s_ct, "connect", Connect);
	target->Set(String::NewSymbol("OracleClient"), s_ct->GetFunction());
	uv_mutex_init(&mutex_t);
	 //uv_rwlock_init(&numlock);
	//uv_sem_init(&sem,N);
}

Handle<Value> OracleClient::New(const Arguments& args) {
	HandleScope scope;
	OracleClient *client = new OracleClient();
	unsigned int count = args[0]->IsUndefined()? 20 : args[0]->Uint32Value();	
	if (count > g_max_thread_count)
	{
		g_max_thread_count = count;
	}
	g_curr_thread_count = 0;
	client->Wrap(args.This());
	return args.This();
}


Handle<Value> OracleClient::Connect(const Arguments& args) {
	OracleClient* client = ObjectWrap::Unwrap<OracleClient>(args.This());
	HandleScope scope;
	uv_mutex_lock(&mutex_t);
	if(g_curr_thread_count >= g_max_thread_count)
	{
		cout<<"error"<<"too many connect"<<endl;
		Handle<Value> argv[2];
		Persistent<Object> call = Persistent<Object>::New(args[args.Length()-1]->ToObject());
		argv[0]= String::New("too many connect");
		argv[1] = Undefined();

		call->CallAsFunction(Object::New(),2,argv);
		uv_mutex_unlock(&mutex_t);
		return Undefined();
	}
	g_curr_thread_count++;
	uv_mutex_unlock(&mutex_t);
	String::Utf8Value strDblink(args[0]);
	String::Utf8Value strUserName(args[1]);
	String::Utf8Value strPwd(args[2]);
	ConnJob* connJob = new ConnJob();
	connJob->strDblink = NodeFunc::ToCString(strDblink);
	connJob->strUserName = NodeFunc::ToCString(strUserName);
	connJob->strPwd = NodeFunc::ToCString(strPwd);
	connJob->js_obj = Persistent<Object>::New(args[args.Length()-1]->ToObject());
	connJob->pClient = client;
	connJob->req.data = connJob;
	client->Ref();
	uv_queue_work(uv_default_loop(), &connJob->req, EIO_Connect, (uv_after_work_cb)EIO_AfterConnect);

	return Undefined();
}

void OracleClient::EIO_Connect(uv_work_t* req) {
	ConnJob* connJob = static_cast<ConnJob*>(req->data);
		try
		{
			COTLConn* pConn = new COTLConn();
			if (pConn == NULL)
			{
				cout<<"too many connect"<<endl;
				throw ("new OCIConnection fail");
			}
		
			bool b = pConn->OTLConnect(connJob->strUserName,connJob->strPwd,connJob->strDblink);
			if (b != true)
			{
				delete pConn;
				throw pConn->OTLGetLastError().c_str();
			}
			else
			{
				
				connJob->pConnect = pConn;
			}

		}
		catch(const char* e)
		{
			connJob->error = e;
			uv_mutex_lock(&mutex_t);
			g_curr_thread_count--;
			uv_mutex_unlock(&mutex_t);

		}
		catch(exception e )
		{
			
			connJob->error = e.what();
			uv_mutex_lock(&mutex_t);
			g_curr_thread_count--;
			uv_mutex_unlock(&mutex_t);
		}
		catch (...)
		{
			
			uv_mutex_lock(&mutex_t);
			g_curr_thread_count--;
			uv_mutex_unlock(&mutex_t);
			
		}
		
	
	
}

void OracleClient::EIO_AfterConnect(uv_work_t* req, int status) {
	HandleScope scope;
	ConnJob* connJob = static_cast<ConnJob*>(req->data);
	connJob->pClient->Unref();
	Handle<Value> argv[2];
	if(connJob->error !="")
	{
		if (connJob->pConnect)
		{
			delete connJob->pConnect;
		}
		
#ifdef OS_WIN32
		connJob->error = encodeConv::CodingConv::ascii2Utf8(connJob->error.c_str());
#endif
		argv[0] = String::New(connJob->error.c_str());	
		argv[1] = Undefined();
	} 
	else 
	{
		argv[0] = Undefined();
		Handle<Object> connection = Connection::constructorTemplate->GetFunction()->NewInstance();
		(node::ObjectWrap::Unwrap<Connection>(connection))->setConnection(connJob->pConnect);
		argv[1] = connection;
	}

	v8::TryCatch tryCatch;
	connJob->js_obj->CallAsFunction(Object::New(),2,argv);
	if (tryCatch.HasCaught()) 
	{
		node::FatalException(tryCatch);
	}
	connJob->js_obj.Dispose();
	delete connJob;
	connJob = NULL;
	scope.Close(Undefined());
}

extern "C" {
	static void init(Handle<Object> target) {
		OracleClient::Init(target);
		Connection::Init(target);
		//OutParam::Init(target);
	}

	NODE_MODULE(oracle_bindings, init);
}
