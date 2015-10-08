BIN  := main
SRCS := $(wildcard *.cpp)
CPPFLAGS := -Wall -std=c++11 
OBJS := $(SRCS:%.cpp=%.o)
LIBS := -lcurl
LDFLAGS :=
$(BIN): $(OBJS)
	$(CXX) $(OBJS) $(LIBS) -o $@
%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@
.PHONY: clean
clean:
	-$(RM) $(OBJS) $(BIN)
