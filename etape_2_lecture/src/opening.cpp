#include <iostream>
#include <ctime>

#include "image_ppm.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 4) {
         cout << "Usage: " << argv[0] << " <binaryImg.pgm> <openingImg.pgm> <iteration>" << endl;
         exit(EXIT_FAILURE);
     }

     clock_t begin1 = clock();

    int height, width = 0;

    OCTET* imgIn;
    OCTET* imgOut;

    lire_nb_lignes_colonnes_image_pgm(argv[1], &height, &width);
    int size = height * width;

    allocation_tableau(imgIn, OCTET, size);
    lire_image_pgm(argv[1], imgIn, height * width);
    allocation_tableau(imgOut, OCTET, size);

    ecrire_image_pgm(argv[2], imgIn,  height, width);

    int iteration = atoi(argv[3]);

    clock_t begin2 = clock();

    for(int n = 0; n < iteration; n++) {
        lire_image_pgm(argv[2], imgIn, height * width);
        lire_image_pgm(argv[2], imgOut, height * width);

        for(int i = 0; i < height; i++) {
            for(int j = 0; j < width; j++) {
                if(imgIn[i*width+j] == 255) {
                    // X | X | X
                    //-----------
                    // X | X | X
                    //-----------
                    // X | X | X
                    if(i != 0) {
                        if(j != 0) {
                            imgOut[(i-1)*width+(j-1)] = 255;
                        }
                        if(j != width-1) {
                            imgOut[(i-1)*width+(j+1)] = 255;
                        }
                        imgOut[(i-1)*width+j] = 255;
                    }
                    if(i != height-1) {
                        if(j != 0) {
                            imgOut[(i+1)*width+(j-1)] = 255;
                        }
                        if(j != width-1) {
                            imgOut[(i+1)*width+(j+1)] = 255;
                        }
                        imgOut[(i+1)*width+j] = 255;
                    }
                    if(j != 0) {
                        imgOut[i*width+(j-1)] = 255;
                    }
                    if(j != width-1) {
                        imgOut[i*width+(j+1)] = 255;
                    }
                }
            }
        }

        ecrire_image_pgm(argv[2], imgOut,  height, width);
    }

    for(int n = 0; n < iteration; n++) {
        lire_image_pgm(argv[2], imgIn, height * width);
        lire_image_pgm(argv[2], imgOut, height * width);

        for(int i = 0; i < height; i++) {
            for(int j = 0; j < width; j++) {
                if(imgIn[i*width+j] == 0) {
                    // X | X | X
                    //-----------
                    // X | X | X
                    //-----------
                    // X | X | X
                    if(i != 0) {
                        if(j != 0) {
                            imgOut[(i-1)*width+(j-1)] = 0;
                        }
                        if(j != width-1) {
                            imgOut[(i-1)*width+(j+1)] = 0;
                        }
                        imgOut[(i-1)*width+j] = 0;
                    }
                    if(i != height-1) {
                        if(j != 0) {
                            imgOut[(i+1)*width+(j-1)] = 0;
                        }
                        if(j != width-1) {
                            imgOut[(i+1)*width+(j+1)] = 0;
                        }
                        imgOut[(i+1)*width+j] = 0;
                    }
                    if(j != 0) {
                        imgOut[i*width+(j-1)] = 0;
                    }
                    if(j != width-1) {
                        imgOut[i*width+(j+1)] = 0;
                    }
                }
            }
        }

        ecrire_image_pgm(argv[2], imgOut,  height, width);
    }

    clock_t end2 = clock();

    delete imgOut;
    delete imgIn;

    clock_t end1 = clock();

    cout << "Computing time : " << ((float)(end2-begin2))/ CLOCKS_PER_SEC << endl;
    cout << "Total time : " << ((float)(end1-begin1))/ CLOCKS_PER_SEC << endl;

    return 0;
}
