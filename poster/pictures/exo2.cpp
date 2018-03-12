#include <iostream>

#include "image_ppm.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 5) {
         cout << "Usage: ImageIn.ppm ImageOut.ppm Seuil1 Seuil2 Seuil3" << endl;
         exit(EXIT_FAILURE);
     }

    cout << "Hello World" << endl;

    int S1 = atoi(argv[3]);
    int S2 = atoi(argv[4]);

    int M1 = S1/2;
    int M2 = (S1+S2)/2;

    int height, width = 0;

    OCTET *imgIn, *imgOut;

    lire_nb_lignes_colonnes_image_pgm(argv[1], &height, &width);
    int size = height * width;

    allocation_tableau(imgIn, OCTET, size);
    lire_image_pgm(argv[1], imgIn, height * width);
    allocation_tableau(imgOut, OCTET, size);

    if(argc == 5) {
        int M3 = (S2+255)/2;

        for(int i = 0; i < size; i++) {
            if(imgIn[i] < S1) {
                imgOut[i] = M1;
            } else if(imgIn[i] < S2) {
                imgOut[i] = M2;
            } else {
                imgOut[i] = M3;
            }
        }
    } else if(argc == 6) {
        int S3 = atoi(argv[5]);

        int M3 = (S2+S3)/2;
        int M4 = (S3+255)/2;

        for(int i = 0; i < size; i++) {
            if(imgIn[i] < S1) {
                imgOut[i] = M1;
            } else if(imgIn[i] < S2) {
                imgOut[i] = M2;
            } else if(imgIn[i] < S3) {
                imgOut[i] = M3;
            }  else {
                imgOut[i] = M4;
            }
        }
    }

    ecrire_image_pgm(argv[2], imgOut,  height, width);
    free(imgIn);
    free(imgOut);

    cout << "Goodbye World" << endl;

    return 0;
}
