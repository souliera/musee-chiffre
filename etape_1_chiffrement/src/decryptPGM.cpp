#include <iostream>
#include <cstdlib>
#include <vector>

#include "image_ppm.h"

using namespace std;

int main(int argc, char *argv[]) {
    if(argc != 5) {
        cout << "Usage: " << argv[0] << " <encryptImg> <decryptImg> <nbBlock> <encryptKey>" << endl;
        exit(EXIT_FAILURE);
    }

    int height = 0;
    int width = 0;

    OCTET* imgIn;
    OCTET* imgOut;

    lire_nb_lignes_colonnes_image_pgm(argv[1], &height, &width);
    int size = height * width;

    allocation_tableau(imgIn, OCTET, size);
    lire_image_pgm(argv[1], imgIn, size);
    allocation_tableau(imgOut, OCTET, size);

    srand(atoi(argv[4]));

    vector<int> index;
    for(int i = 0; i < size; i++) {
        index.push_back(i);
    }

    int n = 0;

    for(int i = 0; i < size; i++) {
        int r = rand() % (size - n);
        int oldIndex = index[r];

        imgOut[i] = imgIn[oldIndex];

        index.erase(index.begin()+r);
        n++;
    }

    ecrire_image_pgm(argv[2], imgOut,  height, width);

    delete imgOut;
    delete imgIn;

    return 0;
}
