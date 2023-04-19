CPP = g++
CPPFLAGS = -lssl -lcrypto -pthread
CPPSTD = -std=gnu++20

EXECUTABLES = server_ex client1_ex client2_ex client3_ex test_ex

compile2:
	$(CPP) $(CPPSTD) -o server_ex server.cpp $(CPPFLAGS)
	$(CPP) $(CPPSTD) -o client1_ex client1.cpp $(CPPFLAGS)

compile3:
	$(CPP) $(CPPSTD) -o server_ex server.cpp $(CPPFLAGS)
	$(CPP) $(CPPSTD) -o client1_ex client1.cpp $(CPPFLAGS)
	$(CPP) $(CPPSTD) -o client2_ex client2.cpp $(CPPFLAGS)

compile:
	$(CPP) $(CPPSTD) -o server_ex server.cpp $(CPPFLAGS)
	$(CPP) $(CPPSTD) -o client1_ex client1.cpp $(CPPFLAGS)
	$(CPP) $(CPPSTD) -o client2_ex client2.cpp $(CPPFLAGS)
	$(CPP) $(CPPSTD) -o client3_ex client3.cpp $(CPPFLAGS)

test:
	$(CPP) -o test_ex test.cpp $(CPPFLAGS)

clean:
	/bin/rm -rf *.o $(EXECUTABLES)

server:
	./server_ex

client1:
	./client1_ex

client2:
	./client2_ex

client3:
	./client3_ex

