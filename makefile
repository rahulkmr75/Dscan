params=`pkg-config --cflags --libs opencv`
objects= load.o matIP.o

a.out: $(objects)
	g++ -w $(objects) $(params)
load.o: load.cpp mat.h matIP.h
	g++ -c -w load.cpp $(params)
matIP.o: matIP.cpp matIP.h mat.h
	g++ -c -w matIP.cpp $(params)

cleanobj:
	rm *.o

cleanall:
	make cleanobj
	rm a.out
