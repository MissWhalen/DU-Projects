all: tcpclient tcpserver

tcpclient: simple_tcp_client.cpp util.cpp
	g++ simple_tcp_client.cpp util.cpp -o tcpclient

tcpserver:
	g++ simple_tcp_server.cpp util.cpp -o tcpserver

