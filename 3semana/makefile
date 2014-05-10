all: bloc24 bloc25

bloc24: bloc24.o model.h
	g++ -lGLU -lGL -lglut bloc24.o model.o -o bloc24

bloc25: bloc25.o model.h
	g++ -lGLU -lGL -lglut bloc25.o model.o -o bloc25
clean:
	rm -f *.o bloc24 bloc25 *.cpp~
