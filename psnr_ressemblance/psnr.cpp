#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>

#include "image_ppm.h"

using namespace std;

int main(int argc, char *argv[]) {
    if(argc != 3) {
        cout << "Usage: " << argv[0] << " <originImg> <refImg>" << endl;
        exit(EXIT_FAILURE);
    }

    int height = 0;
    int width = 0;

    OCTET* imgIn;
    OCTET* gray;
    OCTET* ref;
    OCTET* grayRef;

    lire_nb_lignes_colonnes_image_ppm(argv[1], &height, &width);
    int size = height * width;

    allocation_tableau(imgIn, OCTET, size*3);
    lire_image_ppm(argv[1], imgIn, size);
    allocation_tableau(gray, OCTET, size);
    allocation_tableau(ref, OCTET, size*3);
    lire_image_ppm(argv[2], ref, size);
    allocation_tableau(grayRef, OCTET, size);

    for(int i = 0; i < size; i++) {
        gray[i] = (0.299 * imgIn[(i*3)+0]) + (0.587 * imgIn[(i*3)+1]) + (0.114 * imgIn[(i*3)+2]);
    }

    for(int i = 0; i < size; i++) {
        grayRef[i] = (0.299 * ref[(i*3)+0]) + (0.587 * ref[(i*3)+1]) + (0.114 * ref[(i*3)+2]);
    }

    double psnr = 0.0;
    double MSE = 0.0;

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            MSE += pow(((double)grayRef[i*width+j] - (double)gray[i*width+j]), 2.0);
        }
    }

    MSE /= size;

    psnr = 10 * log10(pow(255.0, 2.0)/MSE);

    cout << "PSNR : " << psnr << endl;

    delete grayRef;
    delete ref;
    delete gray;
    delete imgIn;

    return 0;
}
