CPP = g++
CPPFLAGS = -lssl -lcrypto -pthread
CPPSTD = -std=gnu++20

EXECUTABLES = server client1 client2 client3 test

compile2:
	$(CPP) $(CPPSTD) -o server server.cpp $(CPPFLAGS)
	$(CPP) -o client1 client1.cpp $(CPPFLAGS)

compile:
	$(CPP) -o server server.cpp $(CPPFLAGS)
	$(CPP) -o client1 client1.cpp $(CPPFLAGS)
	$(CPP) -o client2 client2.cpp $(CPPFLAGS)
	$(CPP) -o client3 client3.cpp $(CPPFLAGS)

test:
	$(CPP) -o test test.cpp $(CPPFLAGS)

clean:
	/bin/rm -rf *.o $(EXECUTABLES)