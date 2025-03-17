CXX = clang++
LLVM_CONFIG = llvm-config
CXXFLAGS = `$(LLVM_CONFIG) --cxxflags` -std=c++17 -g -Wall
LDFLAGS = `$(LLVM_CONFIG) --ldflags --libs core native` -lpthread

SRC = main.cpp
OUT = program

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

run: $(OUT)
	./$(OUT)

clean:
	rm -f $(OUT)
