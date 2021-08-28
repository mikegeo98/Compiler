.PHONY: clean default distclean
CXX=c++
CXXFLAGS=-Wall -std=c++11
default: compiler
lexer.cpp: lexer.l lexer.hpp
	flex -s -o lexer.cpp lexer.l
parser.hpp parser.cpp: parser.y
	bison --debug -dv -o parser.cpp parser.y
# Add your dependencies here, e.g.
lexer.o : lexer.hpp lexer.cpp
parser.o: lexer.hpp symbol.hpp parser.cpp ast.hpp ast.cpp parser.hpp 
compiler: lexer.o parser.o 
	$(CXX) $(CXXFLAGS) -o $@ $^
clean:
	$(RM) lexer.cpp parser.cpp parser.hpp parser.output *.o
distclean: clean
	$(RM) compiler