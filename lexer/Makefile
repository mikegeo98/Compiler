.PHONY: clean distclean

CXX=c++
CXXFLAGS=-Wall -std=c++11

#default: tony

lexer.cpp: lexer.l
	flex -s -o lexer.cpp lexer.l

lexer.o: lexer.cpp 

#parser.hpp parser.cpp: parser.y
#	bison -dv -o parser.cpp parser.y

#parser.o: parser.cpp lexer.hpp ast.hpp

tony: lexer.o
	$(CXX) $(CXXFLAGS) -o tony lexer.o

%.o: %.s
	$(AS) $(ASFLAGS) -o $@ $^

#libminibasic.a: writeString.o writeInteger.o formatInteger.o
#	$(AR) $(ARFLAGS) $@ $^

clean:
	$(RM) lexer.cpp *.o

distclean: clean
	$(RM) tony
