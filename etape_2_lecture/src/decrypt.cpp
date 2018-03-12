#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "image_ppm.h"

using namespace std;

/*
 * Computing time : 0,0107705
 * Total time : 0,0138713
 */

int main(int argc, char *argv[]) {
    if(argc != 6) {
        cout << "Usage: " << argv[0] << " <encryptImg> <decryptImg> <imgWidth> <nbBlockPerLine> <key>" << endl;
        exit(EXIT_FAILURE);
    }

    clock_t begin1 = clock();

    //****************
    //*   VARIABLE   *
    //****************

    // image dimension
    int height = 0;
    int width = 0;
    int size = 0;
    // threshold
    unsigned int grayAverage = 0;
    // angle point
    int Ax, Ay, Bx, By, Cx, Cy, Dx, Dy;
    int x, y;
    // transform point
    double Ex, Ey, Fx, Fy, Gx, Gy, Hx, Hy;
    int Kx, Ky;
    double a1, b1, a2, b2;
    int n = atoi(argv[3]);
    // initialisation des paramettres des blocs
    int nbBlockWidth = atoi(argv[4]);
    int nbBlock = nbBlockWidth*nbBlockWidth;
    int widthBlock = n/nbBlockWidth;
    int sizeBlock = widthBlock*widthBlock;
    // many index
    int k = 0;
    int r;
    int newBlockIndex;
    int oldIndexFirst, newIndexFirst;
    int newIndex, oldIndex;

    // initialisation du generateur pseudo-aleatoire
    srand(atoi(argv[5]));

    OCTET* imgIn;
    OCTET* gray;
    OCTET* binary;
    OCTET* transform;
    OCTET* imgOut;

    int* occurence = new int[256];
    for(int i = 0; i < 256; i++) {
        occurence[i] = 0;
    }

    // vecteur pour tirer les nouveaux indices
    vector<int> index;
    for(int i = 0; i < nbBlock; i++) {
        index.push_back(i);
    }

    FILE* file = fopen("rsc/profil.dat", "w");

    lire_nb_lignes_colonnes_image_ppm(argv[1], &height, &width);
    size = height * width;

    allocation_tableau(imgIn, OCTET, size*3);
    allocation_tableau(gray, OCTET, size);
    allocation_tableau(binary, OCTET, size);
    allocation_tableau(transform, OCTET, (n*n)*3);
    allocation_tableau(imgOut, OCTET, (n*n)*3);

    lire_image_ppm(argv[1], imgIn, size);

    clock_t begin2 = clock();

    //******************
    //*   GRAY SCALE   *
    //******************

    cout << "begin gray" << endl;

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            //.299 r + .587 g + .114 b.
            gray[i*width+j] = (0.299 * imgIn[(i*3)*width+(j*3)+0]) + (0.587 * imgIn[(i*3)*width+(j*3)+1]) + (0.114 * imgIn[(i*3)*width+(j*3)+2]);
        }
    }

    cout << "end gray" << endl;

    //*************
    //*   HISTO   *
    //*************

    cout << "begin histo" << endl;

    for(int i = 0; i < size; i++) {
        occurence[gray[i]]++;
    }

    for(int i = 0; i < 256; i++) {
        fprintf(file, "%d %d\n", i, occurence[i]);
        grayAverage += occurence[i] * i;
    }

    grayAverage /= size;

    cout << "end histo" << endl;

    //**************
    //*   BINARY   *
    //**************

    cout << "begin binary" << endl;

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(gray[i*width+j] > grayAverage) {
                binary[i*width+j] = 255;
            } else {
                binary[i*width+j] = 0;
            }
        }
    }

    cout << "end binary" << endl;

    //******************
    //*   FIND ANGLE   *
    //******************

    cout << "begin angle" << endl;

    x = height / 2;
    y = width / 2;
    // UpLeft limite
    for(int i = 0; i < height/2; i++) {
        for(int j = 0; j < width/2; j++) {
            if(binary[i*width+j] == 0) {
                if(i + j < x + y) {
                    x = i;
                    y = j;
                }
            }
        }
    }
    Ax = x;
    Ay = y;

    x = height / 2;
    y = width / 2;
    // UpRight limite
    for(int i = 0; i < height/2; i++) {
        for(int j = width-1; j > width/2; j--) {
            if(binary[i*width+j] == 0) {
                if(j - i > y - x) {
                    x = i;
                    y = j;
                }
            }
        }
    }
    Bx = x;
    By = y;

    x = height / 2;
    y = width / 2;
    // DownRight limite
    for(int i = height-1; i > height/2; i--) {
        for(int j = width-1; j > width/2; j--) {
            if(binary[i*width+j] == 0) {
                if(i + j > x + y) {
                    x = i;
                    y = j;
                }
            }
        }
    }
    Cx = x;
    Cy = y;

    x = height / 2;
    y = width / 2;
    // DownLeft limite
    for(int i = height-1; i > height/2; i--) {
        for(int j = 0; j < width/2; j++) {
            if(binary[i*width+j] == 0) {
                if(i - j > x - y) {
                    x = i;
                    y = j;
                }
            }
        }
    }
    Dx = x;
    Dy = y;

    cout << "end angle" << endl;

    //*****************
    //*   TRANSFORM   *
    //*****************

    cout << "begin transform" << endl;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            Ex = ((double)(i) / ((double)(n) / (Bx - Ax))) + Ax;
            Ey = ((double)(i) / ((double)(n) / (By - Ay))) + Ay;
            Fx = ((double)(j) / ((double)(n) / (Dx - Ax))) + Ax;
            Fy = ((double)(j) / ((double)(n) / (Dy - Ay))) + Ay;
            Gx = ((double)(i) / ((double)(n) / (Cx - Dx))) + Dx;
            Gy = ((double)(i) / ((double)(n) / (Cy - Dy))) + Dy;
            Hx = ((double)(j) / ((double)(n) / (Cx - Bx))) + Bx;
            Hy = ((double)(j) / ((double)(n) / (Cy - By))) + By;

            a1 = (Gy - Ey) / (Gx - Ex);
            b1 = Ey - a1 * Ex;
            a2 = (Hy - Fy) / (Hx - Fx);
            b2 = Fy - a2 * Fx;

            Kx = (int)round((b2 - b1) / (a1 - a2));
            Ky = (int)round(a1 * ((b2 - b1) / (a1 - a2)) + b1);

            transform[(j*3)*n+(i*3)+0] = imgIn[(Kx*3)*width+(Ky*3)+0];
            transform[(j*3)*n+(i*3)+1] = imgIn[(Kx*3)*width+(Ky*3)+1];
            transform[(j*3)*n+(i*3)+2] = imgIn[(Kx*3)*width+(Ky*3)+2];
        }
    }

    cout << "end transform" << endl;

    //***************
    //*   DECRYPT   *
    //***************

    cout << "begin decrypt" << endl;

    for(int i = 0; i < nbBlock; i++) {
        // tirage d'un nouvel indice de bloc aleatoire
        r = rand() % (nbBlock - k);
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
                newIndex = newIndexFirst + x + (y * n);
                oldIndex = oldIndexFirst + x + (y * n);

                // melange
                imgOut[oldIndex*3+0] = transform[newIndex*3+0];
                imgOut[oldIndex*3+1] = transform[newIndex*3+1];
                imgOut[oldIndex*3+2] = transform[newIndex*3+2];
            }
        }

        // suppression de l'indice choisi dans le tableau
        index.erase(index.begin()+r);
        // reduction de la limite aleatoire
        k++;
    }

    cout << "end decrypt" << endl;

    clock_t end2 = clock();

    ecrire_image_pgm((char*)"rsc/grayScale.pgm", gray, height, width);
    ecrire_image_pgm((char*)"rsc/binary.pgm", binary, height, width);
    ecrire_image_ppm((char*)"rsc/transform.pgm", transform, n, n);
    ecrire_image_ppm(argv[2], imgOut, n, n);

    delete[] occurence;

    fclose(file);

    delete imgOut;
    delete transform;
    delete binary;
    delete gray;
    delete imgIn;

    clock_t end1 = clock();

    cout << "Computing time : " << ((float)(end2-begin2))/ CLOCKS_PER_SEC << endl;
    cout << "Total time : " << ((float)(end1-begin1))/ CLOCKS_PER_SEC << endl;

    return 0;
}
