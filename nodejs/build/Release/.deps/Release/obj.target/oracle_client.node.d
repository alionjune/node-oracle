cmd_Release/obj.target/oracle_client.node := flock ./Release/linker.lock g++ -shared -pthread -rdynamic -m64  -Wl,-soname=oracle_client.node -o Release/obj.target/oracle_client.node -Wl,--start-group Release/obj.target/oracle_client/src/oracle_client.o Release/obj.target/oracle_client/src/Connection.o Release/obj.target/oracle_client/../third_party/CodingConv/encodeutil.o Release/obj.target/oracle_client/../core/plateform_public.o Release/obj.target/oracle_client/src/nodefunction.o Release/obj.target/oracle_client/../core/otlPool.o Release/obj.target/oracle_client/src/ConnctionPool.o Release/obj.target/oracle_client/../un/src/linux/thread.o -Wl,--end-group -lclntsh -lpthread -L /home/zhs/oracle/product/10.2.0/db_2/lib/
