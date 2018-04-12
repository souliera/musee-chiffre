#include <iostream>
#include <ctime>

#include "image_ppm.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) {
         cout << "Usage: " << argv[0] << " <decryptImg> <whiteImg>" << endl;
         exit(EXIT_FAILURE);
     }

    clock_t begin1 = clock();

    int height, width = 0;

    OCTET* imgIn;
    OCTET* imgOut;

    lire_nb_lignes_colonnes_image_ppm(argv[1], &height, &width);
    int size = height * width;

    allocation_tableau(imgIn, OCTET, size*3);
    lire_image_ppm(argv[1], imgIn, height * width);
    allocation_tableau(imgOut, OCTET, size);

    int* occurenceR = new int[256];
    int* occurenceG = new int[256];
    int* occurenceB = new int[256];
    for(int i = 0; i < 256; i++) {
        occurenceR[i] = 0;
        occurenceG[i] = 0;
        occurenceB[i] = 0;
    }

    for(int i = 0; i < size; i++) {
        occurenceR[imgIn[(i*3)+0]]++;
        occurenceG[imgIn[(i*3)+1]]++;
        occurenceB[imgIn[(i*3)+2]]++;
    }

    int aR = -1;
    int bR = -1;
    int aG = -1;
    int bG = -1;
    int aB = -1;
    int bB = -1;
    int alphaR = -1;
    int betaR = -1;
    int alphaG = -1;
    int betaG = -1;
    int alphaB = -1;
    int betaB = -1;
    int nbPixel = 0;

    for(int i = 0; i <= 255; i++) {
        nbPixel += occurenceR[i];
        if(nbPixel > size * 0.0005) {
            aR = i;
            break;
        }
    }
    nbPixel = 0;
    for(int i = 255; i >= 0; i--) {
        nbPixel += occurenceR[i];
        if(nbPixel > size * 0.0005) {
            bR = i;
            break;
        }
    }

    nbPixel = 0;
    for(int i = 0; i <= 255; i++) {
        nbPixel += occurenceG[i];
        if(nbPixel > size * 0.0005) {
            aG = i;
            break;
        }
    }
    nbPixel = 0;
    for(int i = 255; i >= 0; i--) {
        nbPixel += occurenceG[i];
        if(nbPixel > size * 0.0005) {
            bG = i;
            break;
        }
    }

    nbPixel = 0;
    for(int i = 0; i <= 255; i++) {
        nbPixel += occurenceB[i];
        if(nbPixel > size * 0.0005) {
            aB = i;
            break;
        }
    }
    nbPixel = 0;
    for(int i = 255; i >= 0; i--) {
        nbPixel += occurenceB[i];
        if(nbPixel > size * 0.0005) {
            bB = i;
            break;
        }
    }

    alphaR = (255 * aR) / (bR-aR);
    betaR = 255 / (bR-aR);
    alphaG = (255 * aG) / (bG-aG);
    betaG = 255 / (bG-aG);
    alphaB = (255 * aB) / (bB-aB);
    betaB = 255 / (bB-aB);

    for(int i = 0; i < size*3; i+=3) {
        imgOut[i+0] = alphaR + (betaR * imgIn[i+0]);
        imgOut[i+1] = alphaG + (betaG * imgIn[i+1]);
        imgOut[i+2] = alphaB + (betaB * imgIn[i+2]);
    }

    ecrire_image_ppm(argv[2], imgOut,  height, width);

    delete[] occurenceR;
    delete[] occurenceG;
    delete[] occurenceB;
    free(imgIn);
    free(imgOut);

    return 0;
}
