all: grayScale.out binary.out closing.out opening.out findAngle.out histo.out transform.out decrypt.out white.out

gray.out: grayScale.cpp
	g++ -o grayScale.out grayScale.cpp -Wall -Wextra -g

binary.out: binary.cpp
	g++ -o binary.out binary.cpp -Wall -Wextra -g

closing.out: closing.cpp
	g++ -o closing.out closing.cpp -Wall -Wextra -g

opening.out: opening.cpp
	g++ -o opening.out opening.cpp -Wall -Wextra -g

findAngle.out: findAngle.cpp
	g++ -o findAngle.out findAngle.cpp -Wall -Wextra -g

histo.out: histo.cpp
	g++ -o histo.out histo.cpp -Wall -Wextra -g

transform.out: transform.cpp
	g++ -o transform.out transform.cpp -Wall -Wextra -g

decrypt.out: decrypt.cpp
	g++ -o decrypt.out decrypt.cpp -Wall -Wextra -g

white.out: white.cpp
	g++ -o white.out white.cpp -Wall -Wextra -g

clean:
	rm -f *.o
	rm -f *.gch

mrproper: clean
	rm -f *.out
