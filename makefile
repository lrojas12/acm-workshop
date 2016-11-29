filename = students

all: compile run

compile:
	g++ $(filename).cpp -o $(filename).out

run:
	./$(filename).out

clean:
	rm *~
