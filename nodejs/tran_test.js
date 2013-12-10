var oracle = require('./build/Release/oracle_client');

var node_oracle = new oracle.oracle_client();

var conn_pool = node_oracle.create_conn_pool('127.0.0.1:1522/lbs','scott','zhs',12,10);
conn_pool.acquire(function(err,conn){
	if(err){
		console.error(err);
	}
	conn.beginTran(function(err){
		if(err){
			console.error(err);
			return;
		}
		conn.execute('insert into zhs values(?)',10,function(err){
			if(err){
					console.log(err);
				conn.rollback(function(err){});
			}else{
			conn.commit(function(err){
			conn.execute('insert into zhs values(?)',100,function(err){
				//conn.commit(function(err){})
			});
					
			});
			}
		
		});
		
	});
});
	


