CC = g++
CFLAGS = -std=c++17
SRCS = main.cpp Statistics.cpp Sorting.cpp Car.cpp

main: $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f main
