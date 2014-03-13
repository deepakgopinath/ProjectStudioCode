all: fft pitch
	g++ -c main.cpp ../audioread/*.hpp
	g++ -o main *.o ../fft/*.o

fft:
	cd ../fft/ && make
pitch: bank
	g++ -c PitchChroma.h PitchChroma.cpp
bank:
	g++ -c FilterBank.h FilterBank.cpp
	
clean:
	rm -f *~ *.o *.gch main
	cd ../fft/ && make clean
