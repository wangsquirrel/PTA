BIN  := main
SRCS := $(wildcard *.cpp)
CPPFLAGS :=  -g -Wall -std=c++11 
OBJS := $(SRCS:%.cpp=%.o)
LIBS := -lcurl 
LDFLAGS := -L./third_party/tinyxpath/lib -ltinyxpath
INCLUDE := -I./third_party/tinyxpath/include
#INCLUDE := 
#LDFLAGS := 
$(BIN): $(OBJS)
	$(CXX) $(CPPFLAGS) $(OBJS) $(LDFLAGS) $(LIBS) -o $@
%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(INCLUDE) -c $< -o $@
.PHONY: clean
clean:
	-$(RM) $(OBJS) $(BIN)
