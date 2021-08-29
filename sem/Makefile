.PHONY: clean default distclean
CXX=c++
CXXFLAGS=-Wall -std=c++11
default: compiler
lexer.cpp: lexer.l 
	flex -s -o lexer.cpp lexer.l
lexer.o : lexer.cpp lexer.hpp parser.hpp ast.hpp symbol.hpp
parser.hpp parser.cpp: parser.y
	bison -dv -o parser.cpp parser.y
# Add your dependencies here, e.g.
parser.o: parser.cpp lexer.hpp ast.hpp ast.cpp symbol.hpp 
compiler: lexer.o parser.o 
	$(CXX) $(CXXFLAGS) -o compiler lexer.o parser.o
clean:
	$(RM) lexer.cpp parser.cpp parser.hpp parser.output *.o
distclean: clean
	$(RM) compiler