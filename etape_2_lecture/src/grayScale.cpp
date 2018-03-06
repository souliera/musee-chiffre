#include <iostream>
#include <cstdlib>
#include <ctime>

#include "image_ppm.h"

using namespace std;

/*
 * Computing time : 0,0107705
 * Total time : 0,0138713
 */

int main(int argc, char *argv[]) {
    if(argc != 3) {
        cout << "Usage: " << argv[0] << " <OriginalImg> <grayScaleImg>" << endl;
        exit(EXIT_FAILURE);
    }

    clock_t begin1 = clock();

    int height = 0;
    int width = 0;

    OCTET* imgIn;
    OCTET* imgOut;

    lire_nb_lignes_colonnes_image_ppm(argv[1], &height, &width);
    int size = height * width;

    allocation_tableau(imgIn, OCTET, size*3);
    lire_image_ppm(argv[1], imgIn, size);
    allocation_tableau(imgOut, OCTET, size);

    clock_t begin2 = clock();

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            //.299 r + .587 g + .114 b.
            imgOut[i*width+j] = (0.299 * imgIn[(i*3)*width+(j*3)+0]) + (0.587 * imgIn[(i*3)*width+(j*3)+1]) + (0.114 * imgIn[(i*3)*width+(j*3)+2]);
        }
    }

    clock_t end2 = clock();

    ecrire_image_pgm(argv[2], imgOut, height, width);

    delete imgOut;
    delete imgIn;

    clock_t end1 = clock();

    cout << "Computing time : " << ((float)(end2-begin2))/ CLOCKS_PER_SEC << endl;
    cout << "Total time : " << ((float)(end1-begin1))/ CLOCKS_PER_SEC << endl;

    return 0;
}
