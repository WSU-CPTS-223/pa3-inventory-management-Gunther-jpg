TARGET = PA3
SOURCE = $(wildcard *.cpp)

$(TARGET): $(SOURCE)
	g++ -std=c++11 -Wall -g $(SOURCE) -o $(TARGET)
clean:
	rm -f $(TARGET)
