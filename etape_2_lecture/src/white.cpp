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
    allocation_tableau(imgOut, OCTET, size*3);

    clock_t begin2 = clock();

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

    int minR = -1;
    int maxR = -1;
    int minG = -1;
    int maxG = -1;
    int minB = -1;
    int maxB = -1;
    int nbPixel = 0;

    for(int i = 0; i <= 255; i++) {
        nbPixel += occurenceR[i];
        if(nbPixel > size * 0.0005) {
            minR = i;
            break;
        }
    }
    nbPixel = 0;
    for(int i = 255; i >= 0; i--) {
        nbPixel += occurenceR[i];
        if(nbPixel > size * 0.0005) {
            maxR = i;
            break;
        }
    }

    nbPixel = 0;
    for(int i = 0; i <= 255; i++) {
        nbPixel += occurenceG[i];
        if(nbPixel > size * 0.0005) {
            minG = i;
            break;
        }
    }
    nbPixel = 0;
    for(int i = 255; i >= 0; i--) {
        nbPixel += occurenceG[i];
        if(nbPixel > size * 0.0005) {
            maxG = i;
            break;
        }
    }

    nbPixel = 0;
    for(int i = 0; i <= 255; i++) {
        nbPixel += occurenceB[i];
        if(nbPixel > size * 0.0005) {
            minB = i;
            break;
        }
    }
    nbPixel = 0;
    for(int i = 255; i >= 0; i--) {
        nbPixel += occurenceB[i];
        if(nbPixel > size * 0.0005) {
            maxB = i;
            break;
        }
    }

    for(int i = 0; i < size*3; i+=3) {
        imgOut[i+0] = ((imgIn[i+0] - minR) * 255) / (maxR - minR);
        imgOut[i+1] = ((imgIn[i+1] - minG) * 255) / (maxG - minG);
        imgOut[i+2] = ((imgIn[i+2] - minB) * 255) / (maxB - minB);
    }

    clock_t end2 = clock();

    ecrire_image_ppm(argv[2], imgOut,  height, width);

    delete[] occurenceR;
    delete[] occurenceG;
    delete[] occurenceB;
    delete imgIn;
    delete imgOut;

    clock_t end1 = clock();

    cout << "Computing time : " << ((float)(end2-begin2))/ CLOCKS_PER_SEC << endl;
    cout << "Total time : " << ((float)(end1-begin1))/ CLOCKS_PER_SEC << endl;

    return 0;
}
