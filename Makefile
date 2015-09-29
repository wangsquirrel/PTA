SRCS := main.cpp Any.cpp Bencode.cpp sha1.cpp Torrent.cpp HttpSender.cpp utils.cpp
OBJS := $(SRCS:%.cpp=%.o)
main: $(OBJS)
	$(CXX)  $(OBJS)   -lcurl -o $@
Bencode.o:
	$(CXX) -c  Bencode.cpp -std=c++11
Torrent.o:
	$(CXX) -c Torrent.cpp -std=c++11
HttpSender.o:
	$(CXX) -c HttpSender.cpp  -std=c++11
.PHONY: clean
clean:
	-$(RM) *.o main
