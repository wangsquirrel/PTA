all: main.o Any.o Bencode.o sha1.o Torrent.o HttpSender.o
	g++ Bencode.o Any.o Torrent.o HttpSender.o  main.o sha1.o -std=c++11 -lcurl -o main
Bencode.o:
	g++ -c Bencode.cpp -std=c++11  
Torrent.o:
	g++ -c Torrent.cpp -std=c++11
HttpSender.o:
	g++ -c HttpSender.cpp  -std=c++11
clean:
	-rm *.o main
