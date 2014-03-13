all: kiss_fft kiss_fftr transform
	
kiss_fft:
	g++ -c kiss_fft.h kiss_fft.c _kiss_fft_guts.h
kiss_fftr:
	g++ -c kiss_fftr.h kiss_fftr.c
transform:
	g++ -c Transforms.hpp Transforms.cpp
clean:
	rm -f *~ *.o *.gch
