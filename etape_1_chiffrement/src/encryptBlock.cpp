#include <iostream>
#include <cstdlib>
#include <vector>

#include "image_ppm.h"

using namespace std;

int main(int argc, char *argv[]) {
    if(argc != 5) {
        cout << "Usage: " << argv[0] << " <clearImg> <encryptImg> <BlockWidth> <encryptKey>" << endl;
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

    int nbBlockWidth = atoi(argv[3]);
    int nbBlock = nbBlockWidth*nbBlockWidth;
    int widthBlock = width/nbBlockWidth;
    int sizeBlock = widthBlock*widthBlock;

    srand(atoi(argv[4]));

    vector<int> index;
    for(int i = 0; i < nbBlock; i++) {
        index.push_back(i);
    }

    int n = 0;
    int r;
    int newBlockIndex;
    int oldIndexFirst, newIndexFirst;
    int newIndex, oldIndex;

    for(int i = 0; i < nbBlock; i++) {
        r = rand() % (nbBlock - n);
        newBlockIndex = index[r];

        if(i == 0) {
            oldIndexFirst = 0;
        } else {
            oldIndexFirst = (i - (i % nbBlockWidth)) * sizeBlock + ((i % nbBlockWidth) * widthBlock);
        }
        if(newBlockIndex == 0) {
            newIndexFirst = 0;
        } else {
            newIndexFirst = (newBlockIndex - (newBlockIndex % nbBlockWidth)) * sizeBlock + ((newBlockIndex % nbBlockWidth) * widthBlock);
        }

        for(int x = 0; x < widthBlock; x++) {
            for(int y = 0; y < widthBlock; y++) {
                newIndex = newIndexFirst + x + (y * width);
                oldIndex = oldIndexFirst + x + (y * width);

                imgOut[newIndex*3+0] = imgIn[oldIndex*3+0];
                imgOut[newIndex*3+1] = imgIn[oldIndex*3+1];
                imgOut[newIndex*3+2] = imgIn[oldIndex*3+2];
            }
        }

        index.erase(index.begin()+r);
        n++;
    }

    ecrire_image_ppm(argv[2], imgOut,  height, width);

    delete imgOut;
    delete imgIn;

    return 0;
}
