#include <iostream>
#include <cstdlib>
#include <vector>

#include "image_ppm.h"

using namespace std;

int main(int argc, char *argv[]) {
    if(argc != 4) {
        cout << "Usage: " << argv[0] << " <orignialImg> <averageImg> <nbBlockWidth>" << endl;
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

    // vecteur pour tirer les nouveaux indices
    vector<int> index;
    for(int i = 0; i < nbBlock; i++) {
        index.push_back(i);
    }

    int oldIndexFirst;
    int oldIndex;
    int averageR, averageG, averageB;

    // calcul des moyennes de chaque bloc
    for(int i = 0; i < nbBlock; i++) {
        averageR = 0;
        averageG = 0;
        averageB = 0;

        // calcul de l'indice du premier pixel du bloc
        if(i == 0) {
            oldIndexFirst = 0;
        } else {
            oldIndexFirst = (i - (i % nbBlockWidth)) * sizeBlock + ((i % nbBlockWidth) * widthBlock);
        }

        // boucle pour recuperer la valeur de chaque pixel du bloc
        for(int x = 0; x < widthBlock; x++) {
            for(int y = 0; y < widthBlock; y++) {
                oldIndex = oldIndexFirst + x + (y * width);
                averageR += imgIn[oldIndex*3+0];
                averageG += imgIn[oldIndex*3+1];
                averageB += imgIn[oldIndex*3+2];
            }
        }

        // moyennes
        averageR /= (widthBlock * widthBlock);
        averageG /= (widthBlock * widthBlock);
        averageB /= (widthBlock * widthBlock);

        // boucle pour chaque pixel du bloc
        for(int x = 0; x < widthBlock; x++) {
            for(int y = 0; y < widthBlock; y++) {
                oldIndex = oldIndexFirst + x + (y * width);
                // reecriture par les moyennes
                imgOut[oldIndex*3+0] = averageR;
                imgOut[oldIndex*3+1] = averageG;
                imgOut[oldIndex*3+2] = averageB;
            }
        }
    }

    ecrire_image_ppm(argv[2], imgOut,  height, width);

    delete imgOut;
    delete imgIn;

    return 0;
}
