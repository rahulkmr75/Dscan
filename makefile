params=`pkg-config --cflags --libs opencv`
objects= load.o matIP.o  nn.o fmat.o

a.out: $(objects)
	g++ -w $(objects) $(params)
load.o: load.cpp mat.h matIP.h
	g++ -c -w load.cpp $(params)
matIP.o: matIP.cpp matIP.h mat.h
	g++ -c -w matIP.cpp $(params)
nn.o:nn.cpp nn.h mat.h fmat.h
	g++ -c -w nn.cpp
fmat.o:fmat.cpp fmat.h mat.h
	g++ -c -w fmat.cpp
cleanobj:
	rm *.o

clean:
	make cleanobj
	rm a.out
