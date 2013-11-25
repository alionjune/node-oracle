#ifndef  _OTLPOOL_H_
#define  _OTLPOOL_H_

#define	OTL_ORA10G
#define  OTL_STL
#include "un.h"
#include "otlv4.h"
#include <map>
#include <string>
#include <exception>
#include <ctime>

/************************************************************************/
/* OTL���ӳص���ģʽ												    */
/************************************************************************/
typedef std::map<otl_connect*, int >otl_con_list; //��������
#define  DEFAULT_CON_COUNT 2   //ȱʡ�����Ӹ���
#define  REFRESH_INTER_MINUTE		1   //ÿ��REFRESH_INTER����ˢ�����ӳص����ӷ�ֹ�����ݿ�ϵ�
#define  REFRESH_INTER_SENCOND  (2 * REFRESH_INTER_MINUTE)
#define  PRINT_POOL_TIME			10	//ÿ��һ��ʱ���ӡ���ӳص�ʹ�����

class otlPool
{
private:
	otlPool(void);
	~otlPool(void);
public:
	int init_pool(std::string user_name,std::string pwd,std::string tns,unsigned int max_conn, unsigned int min_conn );
	otl_connect* get_connect();
	int release_conn(otl_connect* pconn,bool is_delete_conn=false);
	void otl_destroy();
	static otlPool* create_conn_pool();
	
private:
	void otl_lock();
	void otl_unlock();
	int otl_malloc_conn();
	bool otl_check_conn(otl_connect* pconn);
	static void otl_refresh_pool(void * arg); //�̴߳�����ˢ�����ӳ�
	static void otl_thread_fun(void* arg);//�̺߳���

private:
	unsigned int max_con_count; //������Ӹ���
	unsigned int min_con_count; //��С���Ӹ���
	static unsigned int total_con_cout;	//�ܹ����������Ӹ���
	otl_con_list* p_con_list;
	static otlPool* p_conn_pool;
	std::string user_name;
	std::string pwd;
	std::string tns;
	std::string conn_str;
	un_mutex_t mutex;
	bool b_startup;//�Ƿ�����


};




#endif