#RULES
CC = g++
CFLAGS = -c
LFLAGS = -g
TARGET = interpreter
OBJECTS = Exceptions.o tokens.o tokenNode.o NumberNode.o StringNode.o VariableNode.o \
OperatorNode.o builtinNode.o ifNode.o whileNode.o forNode.o functionNode.o \
lexer.o parser.o Interpreter.o manager.o main.o

#linking the object code
all: $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o $(TARGET)

#partial compilation of files into object code
main.o: main.cpp manager/manager.h
	$(CC) $(CFLAGS) $(LFLAGS) main.cpp

manager.o: manager/manager.cpp lexer/lexer.h parser/parser.h Interpreterr/Interpreter.h
	$(CC) $(CFLAGS) $(LFLAGS) manager/manager.cpp

Interpreter.o: Interpreterr/Interpreter.cpp Interpreterr/Interpreter.h
	$(CC) $(CFLAGS) $(LFLAGS) Interpreterr/Interpreter.cpp

parser.o: parser/parser.cpp parser/parser.h
	$(CC) $(CFLAGS) $(LFLAGS) parser/parser.cpp

lexer.o: lexer/lexer.cpp lexer/lexer.h
	$(CC) $(CFLAGS) $(LFLAGS) lexer/lexer.cpp

functionNode.o: tokenNode/functionNode/functionNode.cpp tokenNode/functionNode/functionNode.h tokenNode/tokenNode.h
	$(CC) $(CFLAGS) $(LFLAGS) tokenNode/functionNode/functionNode.cpp

forNode.o: tokenNode/forNode/forNode.cpp tokenNode/forNode/forNode.h tokenNode/tokenNode.h
	$(CC) $(CFLAGS) $(LFLAGS) tokenNode/forNode/forNode.cpp

whileNode.o: tokenNode/whileNode/whileNode.cpp tokenNode/whileNode/whileNode.h tokenNode/tokenNode.h
	$(CC) $(CFLAGS) $(LFLAGS) tokenNode/whileNode/whileNode.cpp

ifNode.o: tokenNode/ifNode/ifNode.cpp tokenNode/ifNode/ifNode.h tokenNode/tokenNode.h
	$(CC) $(CFLAGS) $(LFLAGS) tokenNode/ifNode/ifNode.cpp

builtinNode.o: tokenNode/builtinNode/builtinNode.cpp tokenNode/builtinNode/builtinNode.cpp tokenNode/tokenNode.h
	$(CC) $(CFLAGS) $(LFLAGS) tokenNode/builtinNode/builtinNode.cpp

OperatorNode.o: tokenNode/OperatorNode/OperatorNode.cpp tokenNode/tokenNode.h tokenNode/OperatorNode/OperatorNode.h
	$(CC) $(CFLAGS) $(LFLAGS) tokenNode/OperatorNode/OperatorNode.cpp

VariableNode.o: tokenNode/VariableNode/VariableNode.cpp tokenNode/tokenNode.h tokenNode/VariableNode/VariableNode.h
	$(CC) $(CFLAGS) $(LFLAGS) tokenNode/VariableNode/VariableNode.cpp

StringNode.o: tokenNode/StringNode/StringNode.cpp tokenNode/tokenNode.h tokenNode/StringNode/StringNode.h
	$(CC) $(CFLAGS) $(LFLAGS) tokenNode/StringNode/StringNode.cpp

NumberNode.o: tokenNode/NumberNode/NumberNode.cpp tokenNode/tokenNode.h tokenNode/NumberNode/NumberNode.h
	$(CC) $(CFLAGS) $(LFLAGS) tokenNode/NumberNode/NumberNode.cpp

tokenNode.o: tokenNode/tokenNode.cpp tokenNode/tokenNode.h
	$(CC) $(CFLAGS) $(LFLAGS) tokenNode/tokenNode.cpp

tokens.o: tokens/tokens.cpp tokens/tokens.h 
	$(CC) $(CFLAGS) $(LFLAGS) tokens/tokens.cpp

Exceptions.o: Exceptions/Exceptions.cpp Exceptions/Exceptions.h
	$(CC) $(CFLAGS) $(LFLAGS) Exceptions/Exceptions.cpp

#custom commands

#runs the linked object code
run:
	./$(TARGET)

#deletes all object code and tar files whilst using -f to supress any errors
#error: will complain that certain files cant be deleted because they don't exist but can be ignored
clean:
	rm -f *.o *.tar $(TARGET) 

#invokes valgrind for memory leaks checking purposes
valgrind:
	valgrind --tool=memcheck --leak-check=yes ./$(TARGET)

valgrind_more:
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes ./$(TARGET)

#invokes gdb for debugging
debug:
	gdb ./$(TARGET)