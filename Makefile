CXXFLAGS =

CXXINCLUDES = .

.PHONY: clean

main.exe: main.o Multiset.gch ClasseIterators.gch
	g++ $(CXXFLAGS) -o $@ main.o

main.o: main.cpp
	g++ $(CXXFLAGS) -o $@ -c $^

Multiset.gch: Multiset.hpp
	g++ $(CXXFLAGS) -o $@ -c $^

ClasseIterators.gch: ClasseIterators.hpp
	g++ $(CXXFLAGS) -o $@ -c $^

clean: 
	rm -rf *.o *.gch *.exe main