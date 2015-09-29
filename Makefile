all: main.o Any.o Bencode.o sha1.o Torrent.o
	g++ Bencode.o Any.o Torrent.o  main.o sha1.o -std=c++11 -o main
Bencode.o:
	g++ -c Bencode.cpp -std=c++11  
Torrent.o:
	g++ -c Torrent.cpp -std=c++11
clean:
	-rm *.o main
