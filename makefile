run_client:
	g++ client.cxx -o client -Iinclude -L. -lenet -lws2_32 -lwinmm