main:
	g++ -o main main.cpp

test:
	g++ -o test parser_uat.cpp

clean:
	rm -rf main
	rm -rf test