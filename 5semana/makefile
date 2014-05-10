all: bloc3 bloc32

bloc3: bloc3.o model.h
	g++ -lGLU -lGL -lglut bloc3.o model.o -o bloc3
bloc32: bloc32.o model.h
	g++ -lGLU -lGL -lglut bloc32.o model.o -o bloc32

clean:
	rm -f *.o bloc3 bloc32 *.cpp~
