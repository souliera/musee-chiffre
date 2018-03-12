all: grayScale.cpp binary.cpp closing.cpp opening.cpp findAngle.cpp histo.cpp transform.cpp decrypt.cpp
	g++ -o grayScale.out grayScale.cpp -Wall -Wextra -g
	g++ -o binary.out binary.cpp -Wall -Wextra -g
	g++ -o closing.out closing.cpp -Wall -Wextra -g
	g++ -o opening.out opening.cpp -Wall -Wextra -g
	g++ -o findAngle.out findAngle.cpp -Wall -Wextra -g
	g++ -o histo.out histo.cpp -Wall -Wextra -g
	g++ -o transform.out transform.cpp -Wall -Wextra -g
	g++ -o decrypt.out decrypt.cpp -Wall -Wextra -g

gray: grayScale.cpp
	g++ -o grayScale.out grayScale.cpp -Wall -Wextra -g

binary: binary.cpp
	g++ -o binary.out binary.cpp -Wall -Wextra -g

closing: closing.cpp
	g++ -o closing.out closing.cpp -Wall -Wextra -g

opening: opening.cpp
	g++ -o opening.out opening.cpp -Wall -Wextra -g

findAngle: findAngle.cpp
	g++ -o findAngle.out findAngle.cpp -Wall -Wextra -g

histo: histo.cpp
	g++ -o histo.out histo.cpp -Wall -Wextra -g

transform: transform.cpp
	g++ -o transform.out transform.cpp -Wall -Wextra -g

decrypt: decrypt.cpp
	g++ -o decrypt.out decrypt.cpp -Wall -Wextra -g

clean:
	rm -f *.o
	rm -f *.gch

mrproper: clean
	rm -f *.out
