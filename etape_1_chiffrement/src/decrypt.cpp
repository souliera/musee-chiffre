#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>

#include "image_ppm.h"

using namespace std;

int main(int argc, char *argv[]) {
    if(argc != 5) {
        cout << "Usage: " << argv[0] << " <encryptImg> <decryptImg> <nbBlock> <encryptKey>" << endl;
        exit(EXIT_FAILURE);
    }

    clock_t begin1 = clock();

    int height = 0;
    int width = 0;

    OCTET* imgIn;
    OCTET* imgOut;

    // recuperation des dimensions de l'image
    lire_nb_lignes_colonnes_image_ppm(argv[1], &height, &width);
    int size = height * width;
    int size3 = size * 3;

    // creation des tableaux de donnees
    allocation_tableau(imgIn, OCTET, size3);
    lire_image_ppm(argv[1], imgIn, size);
    allocation_tableau(imgOut, OCTET, size3);

    // initialisation du generateur pseudo-aleatoire
    srand(atoi(argv[4]));

    // vecteur pour tirer les nouveaux indices
    vector<int> index;
    for(int i = 0; i < size; i++) {
        index.push_back(i);
    }

    int n = 0;

    clock_t begin2 = clock();

    for(int i = 0; i < size; i++) {
        // tirage d'un nouvel indice aleatoire
        int r = rand() % (size - n);
        int oldIndex = index[r];

        // melange
        imgOut[i*3+0] = imgIn[oldIndex*3+0];
        imgOut[i*3+1] = imgIn[oldIndex*3+1];
        imgOut[i*3+2] = imgIn[oldIndex*3+2];

        // suppression de l'indice choisi dans le tableau
        index.erase(index.begin()+r);
        // reduction de la limite aleatoire
        n++;
    }

    clock_t end2 = clock();

    ecrire_image_ppm(argv[2], imgOut,  height, width);

    delete imgOut;
    delete imgIn;

    clock_t end1 = clock();

    cout << "Computing time : " << ((float)(end2-begin2))/ CLOCKS_PER_SEC << endl;
    cout << "Total time : " << ((float)(end1-begin1))/ CLOCKS_PER_SEC << endl;

    return 0;
}
