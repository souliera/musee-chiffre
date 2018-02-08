#include <iostream>
#include <cstdlib>

#include "image_ppm.h"

using namespace std;

int main(int argc, char *argv[]) {
    if(argc != 4) {
        cout << "Usage: " << argv[0] << " <encryptImg> <decryptImg> <seuil>" << endl;
        exit(EXIT_FAILURE);
    }

    int height = 0;
    int width = 0;

    OCTET* imgIn;
    OCTET* imgOut;

    lire_nb_lignes_colonnes_image_ppm(argv[1], &height, &width);
    int size = height * width;
    int size3 = size * 3;

    allocation_tableau(imgIn, OCTET, size3);
    lire_image_ppm(argv[1], imgIn, size);
    allocation_tableau(imgOut, OCTET, size3);

    int seuil = atoi(argv[3]);

    int up, left = width;
    int down, right = 0;
    int newUp, newLeft = width;
    int newDown, newRight = 0;

    // limite left
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width-1; j++) {
            newLeft = width;
            if(abs(imgIn[(i*3) * width + (j*3) + 0] - imgIn[(i*3) * width + ((j+1)*3) + 0]) > seuil) {
                newLeft = j;
                break;
            }
            if(abs(imgIn[(i*3) * width + (j*3) + 1] - imgIn[(i*3) * width + ((j+1)*3) + 1]) > seuil) {
                newLeft = j;
                break;
            }
            if(abs(imgIn[(i*3) * width + (j*3) + 2] - imgIn[(i*3) * width + ((j+1)*3) + 2]) > seuil) {
                newLeft = j;
                break;
            }
        }

        if(newLeft < left) {
            left = newLeft;
        }
    }

    cout << left << endl;

    // limite right
    for(int i = 0; i < height; i++) {
        for(int j = width-1; j > 0; j--) {
            newRight = 0;
            if(abs(imgIn[(i*3) * width + (j*3) + 0] - imgIn[(i*3) * width + ((j-1)*3) + 0]) > seuil) {
                newRight = j;
                break;
            }
            if(abs(imgIn[(i*3) * width + (j*3) + 1] - imgIn[(i*3) * width + ((j-1)*3) + 1]) > seuil) {
                newRight = j;
                break;
            }
            if(abs(imgIn[(i*3) * width + (j*3) + 2] - imgIn[(i*3) * width + ((j-1)*3) + 2]) > seuil) {
                newRight = j;
                break;
            }
        }

        if(newRight > right) {
            right = newRight;
        }
    }

    cout << right << endl;

    // limite up
    for(int i = 0; i < height-1; i++) {
        for(int j = 0; j < width; j++) {
            newUp = width;
            if(abs(imgIn[(i*3) * width + (j*3) + 0] - imgIn[((i+1)*3) * width + (j*3) + 0]) > seuil) {
                newUp = j;
                break;
            }
            if(abs(imgIn[(i*3) * width + (j*3) + 1] - imgIn[((i+1)*3) * width + (j*3) + 1]) > seuil) {
                newUp = j;
                break;
            }
            if(abs(imgIn[(i*3) * width + (j*3) + 2] - imgIn[((i+1)*3) * width + (j*3) + 2]) > seuil) {
                newUp = j;
                break;
            }
        }

        if(newUp < up) {
            up = newUp;
        }
    }

    cout << up << endl;

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(left <= j && j <= right) {
                imgOut[(i*3) * width + (j*3) + 0] = imgIn[(i*3) * width + (j*3) + 0];
                imgOut[(i*3) * width + (j*3) + 1] = imgIn[(i*3) * width + (j*3) + 1];
                imgOut[(i*3) * width + (j*3) + 2] = imgIn[(i*3) * width + (j*3) + 2];
            } else {
                imgOut[(i*3) * width + (j*3) + 0] = 0;
                imgOut[(i*3) * width + (j*3) + 1] = 0;
                imgOut[(i*3) * width + (j*3) + 2] = 0;
            }
        }
    }

    ecrire_image_ppm(argv[2], imgOut,  height, width);

    delete imgOut;
    delete imgIn;

    return 0;
}
