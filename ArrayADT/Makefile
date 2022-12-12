CC	= g++ -std=c++11

OBJS	= ArrayADT.o
TARGET	= ArrayADT.exe

.phony: all clean

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

%.o: %.cpp
	$(CC) -o $@ -c $<

clean:
	rm -rf $(TARGET) $(OBJS) *.core
