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

    lire_nb_lignes_colonnes_image_pgm(argv[1], &height, &width);
    int size = height * width;

    allocation_tableau(imgIn, OCTET, size);
    lire_image_pgm(argv[1], imgIn, size);
    allocation_tableau(imgOut, OCTET, size);

    int seuil = atoi(argv[3]);

    int up = width;
    int left = width;
    int down = 0;
    int right = 0;
    int newUp = width;
    int newLeft = width;
    int newDown = 0;
    int newRight = 0;

    // limite left
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width-1; j++) {
            newLeft = width;
            if(abs(imgIn[i*width+j] - imgIn[i*width+(j+1)]) > seuil) {
                newLeft = j;
                break;
            }
        }

        if(newLeft < left) {
            left = newLeft;
        }
    }

    cout << "left : " << left << endl;

    // limite right
    for(int i = 0; i < height; i++) {
        for(int j = width-1; j > 0; j--) {
            newRight = 0;
            if(abs(imgIn[i*width+j] - imgIn[i*width+(j-1)]) > seuil) {
                newRight = j;
                break;
            }
        }

        if(newRight > right) {
            right = newRight;
        }
    }

    cout << "right : " << right << endl;

    // limite up
    for(int i = 0; i < height-1; i++) {
        for(int j = 0; j < width; j++) {
            newUp = height;
            if(abs(imgIn[i*width+j] - imgIn[(i+1)*width+j]) > seuil) {
                newUp = i;
                break;
            }
        }

        if(newUp < up) {
            up = newUp;
        }
    }

    cout << "up : " << up << endl;

    // limite down
    for(int i = height-1; i > 0; i--) {
        for(int j = 0; j < width; j++) {
            newDown = 0;
            if(abs(imgIn[i*width+j] - imgIn[(i-1)*width+j]) > seuil) {
                cout << i << " " << j << endl;
                newDown = i;
                break;
            }
        }

        if(newDown > down) {
            down = newDown;
        }
    }

    cout << "down : " << down << endl;

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(left < j && j < right && up < i && i < down) {
                imgOut[(i) * width + (j) ] = imgIn[(i) * width + (j) ];
                imgOut[(i) * width + (j) ] = imgIn[(i) * width + (j) ];
                imgOut[(i) * width + (j) ] = imgIn[(i) * width + (j) ];
            } else {
                imgOut[(i) * width + (j) ] = 0;
                imgOut[(i) * width + (j) ] = 0;
                imgOut[(i) * width + (j) ] = 0;
            }
        }
    }

    ecrire_image_pgm(argv[2], imgOut,  height, width);

    delete imgOut;
    delete imgIn;

    return 0;
}
