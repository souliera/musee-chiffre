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

    // recuperation des dimensions de l'image
    lire_nb_lignes_colonnes_image_ppm(argv[1], &height, &width);
    int size = height * width;
    int size3 = size * 3;

    // creation des tableaux de donnees
    allocation_tableau(imgIn, OCTET, size3);
    lire_image_ppm(argv[1], imgIn, size);
    allocation_tableau(imgOut, OCTET, size3);

    // initialisation des paramettres des blocs
    int nbBlockWidth = atoi(argv[3]);
    int nbBlock = nbBlockWidth*nbBlockWidth;
    int widthBlock = width/nbBlockWidth;
    int sizeBlock = widthBlock*widthBlock;

    // initialisation du generateur pseudo-aleatoire
    srand(atoi(argv[4]));

    // vecteur pour tirer les nouveaux indices
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
        // tirage d'un nouvel indice de bloc aleatoire
        r = rand() % (nbBlock - n);
        newBlockIndex = index[r];

        // calcul de l'indice du premier pixel du bloc et du son nouvel indice
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

        // boucle pour chaque pixel du bloc
        for(int x = 0; x < widthBlock; x++) {
            for(int y = 0; y < widthBlock; y++) {
                // calcul du nouvel indice du pixel dans le bloc
                newIndex = newIndexFirst + x + (y * width);
                oldIndex = oldIndexFirst + x + (y * width);

                // melange
                imgOut[newIndex*3+0] = imgIn[oldIndex*3+0];
                imgOut[newIndex*3+1] = imgIn[oldIndex*3+1];
                imgOut[newIndex*3+2] = imgIn[oldIndex*3+2];
            }
        }

        // suppression de l'indice choisi dans le tableau
        index.erase(index.begin()+r);
        // reduction de la limite aleatoire
        n++;
    }

    ecrire_image_ppm(argv[2], imgOut,  height, width);

    delete imgOut;
    delete imgIn;

    return 0;
}
