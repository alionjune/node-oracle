var oracle = require('./build/Release/oracle_client');

var node_oracle = new oracle.oracle_client();
var node_oracle2 = new oracle.oracle_client();
console.log(node_oracle == node_oracle2);
var conn_pool = node_oracle.create_conn_pool('127.0.0.1:1522/lbs','scott','zhs',12,10);
console.log(conn_pool);
conn_pool.acquire(function(err,conn){
	console.log(err);
	console.log('conn'+conn);
	conn.execute('insert into zhs values(?)',1,function(err){
	
	if(err){
		console.error(err);
	}
		conn.beginTran(function(err){
			
			conn.execute('insert into zhs values(?)',1,function(err){});
			
		});
	
	//var ret = conn_pool.release(conn);
	console.log('xxxxxxxxxxxxxxxxxxx');
	while(1){}
	
	});

	
});

