all:
	g++ -o encryptPGM.out encryptPGM.cpp -Wall -Wextra -g
	g++ -o decryptPGM.out decryptPGM.cpp -Wall -Wextra -g
	g++ -o encrypt.out encrypt.cpp -Wall -Wextra -g
	g++ -o decrypt.out decrypt.cpp -Wall -Wextra -g
	g++ -o encryptBlockPGM.out encryptBlockPGM.cpp -Wall -Wextra -g
	g++ -o decryptBlockPGM.out decryptBlockPGM.cpp -Wall -Wextra -g
	g++ -o encryptBlock.out encryptBlock.cpp -Wall -Wextra -g
	g++ -o decryptBlock.out decryptBlock.cpp -Wall -Wextra -g

clean:
	rm -f *.o
	rm -f *.gch

mrproper: clean
	rm -f *.out
