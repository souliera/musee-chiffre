#include <iostream>
#include <cmath>

#include "image_ppm.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
         cout << "Usage: " << argv[0] << " <grayScaleImg.pgm>" << endl;
         exit(EXIT_FAILURE);
     }

    int height = 0;
    int width = 0;

    OCTET *imgIn;

    lire_nb_lignes_colonnes_image_pgm(argv[1], &height, &width);
    int size = height * width;

    allocation_tableau(imgIn, OCTET, size);
    lire_image_pgm(argv[1], imgIn, height * width);

    int* occurence = new int[256];
    for(int i = 0; i < 256; i++) {
        occurence[i] = 0;
    }

    for(int i = 0; i < size; i++) {
        occurence[imgIn[i]]++;
    }

    int total = 0;

    for(int i = 0; i < 256; i++) {
        total += occurence[i];
        if(total >= (height * width) * 0.4) {
            cout << i << endl;
            break;
        }
    }

    FILE* file = fopen("profil.dat", "w");

    for(int i = 0; i < 256; i++) {
        fprintf(file, "%d %d\n", i, occurence[i]);
    }

    fclose(file);
    delete[] occurence;
    delete imgIn;

    return 0;
}
