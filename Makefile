TARGET = iotest
OBJS   = iotest.o

# Assume GCC
CPPFLAGS += -DNDEBUG
CXXFLAGS += -O2 -Wall -Wextra -Wno-deprecated-declarations # We want to use gets
LDFLAGS  += -s

.PHONY: all clean
.DELETE_ON_ERROR:

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CPPFLAGS) $(CXXFLAGS)

clean:
	$(RM) $(TARGET) $(OBJS)
