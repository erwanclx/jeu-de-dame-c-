TARGET = jeuDeDame

SRC_DIR = src

SRCS = $(wildcard $(SRC_DIR)/*.cpp)

CXX = g++
CXXFLAGS = -I$(SRC_DIR)

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) -o $@ $^

clean:
	rm -f $(TARGET)

.PHONY: all clean
