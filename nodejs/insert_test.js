var oracle = require('./build/Release/oracle_client');

var node_oracle = new oracle.oracle_client();
var conn_pool = node_oracle.create_conn_pool('127.0.0.1:1522/lbs','scott','zhs',12,10);
conn_pool.acquire(function(err,conn){

		conn.execute("insert into zhs values(1,'郑华山')",function(err){
			if(err){
				console.log(err);
			}
		});
});

