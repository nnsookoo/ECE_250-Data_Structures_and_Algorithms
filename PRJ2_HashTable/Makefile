all: openhttest unorderedhttest

openhttest: openhttest.cpp
	g++ -std=c++11 -o openhttest openhttest.cpp HashNodeOpen.h HashNodeOpen.cpp HashTableOpen.h HashTableOpen.cpp

unorderedhttest: unorderedhttest.cpp
	g++ -std=c++11 -o unorderedhttest unorderedhttest.cpp HashNodeChain.h HashNodeChain.cpp HashTableChain.h HashTableChain.cpp

clean:
	rm *.o openhttest unorderedhttest