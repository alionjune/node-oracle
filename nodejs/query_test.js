var oracle = require('./build/Release/oracle_client');

var node_oracle = new oracle.oracle_client();
var node_oracle2 = new oracle.oracle_client();
console.log(node_oracle == node_oracle2);
var conn_pool = node_oracle.create_conn_pool('127.0.0.1:1522/lbs','scott','zhs',12,10);
console.log(conn_pool);
conn_pool.acquire(function(err,conn){

	conn.query("select * from zhs where name=?",'郑华山',function(err,result){
		console.error(err);
		console.log(result);
		console.log(result[0]['AGE']);
	})
});

