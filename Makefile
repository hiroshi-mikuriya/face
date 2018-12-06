CXX       := g++
CXXFLAGS  := -Wall -std=c++0x

TARGET    := face
PROJ_ROOT := $(realpath .)
VPATH     := $(PROJ_ROOT)
SRCS      := $(shell find ./ -name "*.cpp")
LIBS      := -lpthread \
	     -ldl \
	     -lboost_system \
		 `pkg-config opencv --libs` \
	     -lm

OBJS      := $(SRCS:.cpp=.o)

### Rules ######################################################################

.PHONY: all
all: $(TARGET)
.PHONY: make
make: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -v -o $@ $(OBJS) $(LIBS)

.PHONY: clean
clean:
	$(RM) -f $(TARGET) *.o

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $<
