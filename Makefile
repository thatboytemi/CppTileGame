CC = g++
CCFLAGS = -std=c++20

driver : driver.o TileManager.o
	$(CC) driver.o TileManager.o -o driver $(CCFLAGS)

.cpp.o: 
	$(CC) -c $< $(CCFLAGS)

clean:
	rm -f *.o driver.exe