#include <iostream>
#include <cstdlib>
#include <ctime>

#include "image_ppm.h"

using namespace std;

/*
 * Computing time : 0,0041109
 * Total time : 0,0060008
 */

int main(int argc, char *argv[]) {
    if(argc != 4) {
        cout << "Usage: " << argv[0] << " <grayScaleImg> <binaryImg> <seuil>" << endl;
        exit(EXIT_FAILURE);
    }

    clock_t begin1 = clock();

    int height = 0;
    int width = 0;

    OCTET* imgIn;
    OCTET* imgOut;

    lire_nb_lignes_colonnes_image_pgm(argv[1], &height, &width);
    int size = height * width;

    allocation_tableau(imgIn, OCTET, size);
    lire_image_pgm(argv[1], imgIn, size);
    allocation_tableau(imgOut, OCTET, size);

    int seuil = atoi(argv[3]);

    clock_t begin2 = clock();

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(imgIn[i*width+j] > seuil) {
                imgOut[i*width+j] = 255;
            } else {
                imgOut[i*width+j] = 0;
            }
        }
    }

    clock_t end2 = clock();

    ecrire_image_pgm(argv[2], imgOut,  height, width);

    delete imgOut;
    delete imgIn;

    clock_t end1 = clock();

    cout << "Computing time : " << ((float)(end2-begin2))/ CLOCKS_PER_SEC << endl;
    cout << "Total time : " << ((float)(end1-begin1))/ CLOCKS_PER_SEC << endl;

    return 0;
}
