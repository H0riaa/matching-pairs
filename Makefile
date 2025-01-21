clean:
	del main
all:
	g++ main.cpp -o main.exe
run:
	./main.exe