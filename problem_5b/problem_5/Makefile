CXX=g++
CXXFLAGS=-Wall -std=c++11 -g

all:
	$(CXX) $(CXXFLAGS) -o mergeTime mergeTime.cpp
	$(CXX) $(CXXFLAGS) -o insertTime insertTime.cpp

clean:
	@rm -f mergeTime
	@rm -f insertTime
	@rm -f *.o
format:
	clang-format --verbose --sort-includes -i *.cpp *.hpp
