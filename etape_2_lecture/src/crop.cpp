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

    allocation_tableau(imgIn, OCTET, size*3);
    lire_image_ppm(argv[1], imgIn, size);

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
            int val1 = (imgIn[(i*3)*width+j + 0] + imgIn[(i*3)*width+j + 1] + imgIn[(i*3)*width+j + 2]) / 3;
            int val2 = (imgIn[(i*3)*width+(j+1) + 0] + imgIn[(i*3)*width+(j+1) + 1] + imgIn[(i*3)*width+(j+1) + 2]) / 3;
            if(abs(val1 - val2) > seuil) {
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
            int val1 = (imgIn[(i*3)*width+j + 0] + imgIn[(i*3)*width+j + 1] + imgIn[(i*3)*width+j + 2]) / 3;
            int val2 = (imgIn[(i*3)*width+(j-1) + 0] + imgIn[(i*3)*width+(j-1) + 1] + imgIn[(i*3)*width+(j-1) + 2]) / 3;
            if(abs(val1 - val2) > seuil) {
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
            int val1 = (imgIn[(i*3)*width+j + 0] + imgIn[(i*3)*width+j + 1] + imgIn[(i*3)*width+j + 2]) / 3;
            int val2 = (imgIn[((i+1)*3)*width+j + 0] + imgIn[((i+1)*3)*width+j + 1] + imgIn[((i+1)*3)*width+j + 2]) / 3;
            if(abs(val1 - val2) > seuil) {
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
            int val1 = (imgIn[(i*3)*width+j + 0] + imgIn[(i*3)*width+j + 1] + imgIn[(i*3)*width+j + 2]) / 3;
            int val2 = (imgIn[((i-1)*3)*width+j + 0] + imgIn[((i-1)*3)*width+j + 1] + imgIn[((i-1)*3)*width+j + 2]) / 3;
            if(abs(val1 - val2) > seuil) {
                newDown = i;
                break;
            }
        }

        if(newDown > down) {
            down = newDown;
        }
    }

    cout << "down : " << down << endl;

    int height2 = down - up;
    int width2 = right - left;
    int size2 = height2 * width2;
    allocation_tableau(imgOut, OCTET, size2*3);

    cout << "height : " << height2 << ", width : " << width2 << endl;

    for(int i = 0; i < height2*3; i+=3) {
        for(int j = 0; j < width2*3; j+=3) {
            imgOut[i*width2+j+0] = imgIn[(i+up)*width+(j+left)+0];
            imgOut[i*width2+j+1] = imgIn[(i+up)*width+(j+left)+1];
            imgOut[i*width2+j+2] = imgIn[(i+up)*width+(j+left)+2];

            // if(left < j && j < right && up < i && i < down) {
            //     imgOut[(i) * width + (j) ] = imgIn[(i) * width + (j) ];
            //     imgOut[(i) * width + (j) ] = imgIn[(i) * width + (j) ];
            //     imgOut[(i) * width + (j) ] = imgIn[(i) * width + (j) ];
            // } else {
            //     imgOut[(i) * width + (j) ] = 0;
            //     imgOut[(i) * width + (j) ] = 0;
            //     imgOut[(i) * width + (j) ] = 0;
            // }
        }
    }

    ecrire_image_ppm(argv[2], imgOut,  height2, width2);

    delete imgOut;
    delete imgIn;

    return 0;
}
