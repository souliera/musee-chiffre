#include <iostream>
#include <cstdlib>
#include <cmath>
#include <math.h>

#include "image_ppm.h"

using namespace std;

int main(int argc, char *argv[]) {
    if(argc != 3) {
        cout << "Usage: " << argv[0] << " <encryptImg> <decryptImg>" << endl;
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
            if(imgIn[i*width+j] > 127) {
                imgOut[i*width+j] = 255;
            } else {
                imgOut[i*width+j] = 0;
            }
            // n = 1;
            // int sum = imgIn[i*width+j];
            // if(i != 0) {
            //     sum += imgIn[(i-1)*width+j];
            //     n++;
            // }
            //
            // if(i != height-1) {
            //     sum += imgIn[(i+1)*width+j];
            //     n++;
            // }
            //
            // if(j != 0) {
            //     sum += imgIn[i*width+(j-1)];
            //     n++;
            // }
            //
            // if(j != width-1) {
            //     sum += imgIn[i*width+(j+1)];
            //     n++;
            // }
            //
            // imgOut[i*width+j] = sum / n;
        }
    }

    ecrire_image_pgm(argv[2], imgOut,  height, width);

    cout << "\t" << imgIn[0*width+1] / 1 << endl;
    cout << imgIn[1*width+0] / 1 << "\t" << imgIn[1*width+1] / 1 << "\t" << imgIn[1*width+2] / 1 << endl;
    cout << "\t" << imgIn[2*width+1] / 1 << endl;

    cout << endl;

    cout << imgOut[1*width+1] << endl;
    cout << imgOut[1*width+1] / 5 << endl;

    delete imgOut;
    delete imgIn;

    return 0;
}
