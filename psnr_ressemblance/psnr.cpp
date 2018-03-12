#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>

#include "image_ppm.h"

using namespace std;

int main(int argc, char *argv[]) {
    if(argc != 2) {
        cout << "Usage: " << argv[0] << " <originImg>" << endl;
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

    FILE* file = fopen("profil.dat", "w");

    for(int l = 1; l < 800; l++) {
        if(800 % l == 0) {
            // initialisation des paramettres des blocs
            int nbBlockWidth = l;
            int nbBlock = nbBlockWidth*nbBlockWidth;
            int widthBlock = width/nbBlockWidth;
            int sizeBlock = widthBlock*widthBlock;

            int oldIndexFirst;
            int oldIndex;
            int average;

            // calcul des moyennes de chaque bloc
            for(int i = 0; i < nbBlock; i++) {
                average = 0;

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
                        average += imgIn[oldIndex];
                    }
                }

                // moyennes
                average /= (widthBlock * widthBlock);

                // boucle pour chaque pixel du bloc
                for(int x = 0; x < widthBlock; x++) {
                    for(int y = 0; y < widthBlock; y++) {
                        oldIndex = oldIndexFirst + x + (y * width);
                        // reecriture par les moyennes
                        imgOut[oldIndex] = average;
                    }
                }
            }

            double psnr = 0.0;
            double MSE = 0.0;

            for(int i = 0; i < height; i++) {
                for(int j = 0; j < width; j++) {
                    MSE += pow(((double)imgIn[i*width+j] - (double)imgOut[i*width+j]), 2.0);
                }
            }

            MSE /= size;

            psnr = 10 * log10(pow(255.0, 2.0)/MSE);

            fprintf(file, "%f %f\n", (double)widthBlock, psnr);

            cout << "PSNR : " << psnr << endl;
        }
    }

    delete imgOut;
    delete imgIn;

    return 0;
}
