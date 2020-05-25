all: evalArithmeticExpression

CPPFLAGS= -std=c++11
OBJS=Tokenizer.o Evaluator.o main.o
ALLHEADERS=Tokenizer.hpp Evaluator.hpp

evalArithmeticExpression: $(OBJS)
	g++ -g $(OBJS) -o $@

Tokenizer.o: Tokenizer.cpp $(ALLHEADERS)
	g++ -c $(CPPFLAGS) Tokenizer.cpp

Evaluator.o: Evaluator.cpp $(ALLHEADERS)
	g++ -c $(CPPFLAGS) Evaluator.cpp

main.o: main.cpp $(ALLHEADERS)
	g++ -c $(CPPFLAGS) main.cpp

%.o : %.cpp %.hpp
	g++ -c $(CPPFLAGS) $< -o $@

clean:
	rm -f *.o evalArithmeticExpression
