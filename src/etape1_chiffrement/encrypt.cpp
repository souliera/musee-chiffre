#include <iostream>
#include <cstdlib>
#include <vector>

#include "image_ppm.h"

using namespace std;

int main(int argc, char *argv[]) {
    if(argc != 5) {
        cout << "Usage: " << argv[0] << " <encryptImg> <decryptImg> <nbBlock> <encryptKey>" << endl;
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

    srand(atoi(argv[4]));

    vector<int> index;
    for(int i = 0; i < size; i++) {
        index.push_back(i);
    }

    int n = 0;

    for(int i = 0; i < size; i++) {
        int r = rand() % (size - n);
        int newIndex = index[r];

        imgOut[newIndex*3+0] = imgIn[i*3+0];
        imgOut[newIndex*3+1] = imgIn[i*3+1];
        imgOut[newIndex*3+2] = imgIn[i*3+2];

        index.erase(index.begin()+r);
        n++;
    }

    ecrire_image_ppm(argv[2], imgOut,  height, width);

    delete imgOut;
    delete imgIn;

    return 0;
}
