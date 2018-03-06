#include <iostream>
#include <cstdlib>
#include <cmath>
#include <math.h>

#include "image_ppm.h"

using namespace std;

int main(int argc, char *argv[]) {
    if(argc != 3) {
        cout << "Usage: " << argv[0] << " <grayScaleImg> <smoothImg>" << endl;
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

    int n = 0;

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            n = 1;
            int sum = imgIn[i*width+j];
            if(i != 0) {
                sum += imgIn[(i-1)*width+j];
                n++;
            }

            if(i != height-1) {
                sum += imgIn[(i+1)*width+j];
                n++;
            }

            if(j != 0) {
                sum += imgIn[i*width+(j-1)];
                n++;
            }

            if(j != width-1) {
                sum += imgIn[i*width+(j+1)];
                n++;
            }

            imgOut[i*width+j] = sum / n;
        }
    }

    ecrire_image_pgm(argv[2], imgOut,  height, width);

    delete imgOut;
    delete imgIn;

    return 0;
}
