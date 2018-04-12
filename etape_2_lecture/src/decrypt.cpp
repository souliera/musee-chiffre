#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "image_ppm.h"

using namespace std;

/*
 * Computing time :
 * Total time :
 */

int main(int argc, char *argv[]) {
    if(argc != 7) {
        cout << "Usage: " << argv[0] << " <encryptImg> <decryptImg> <imgWidth> <nbBlockPerLine> <key> <average?>" << endl;
        cout << endl;
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
    // white balance
    int minR = -1;
    int maxR = -1;
    int minG = -1;
    int maxG = -1;
    int minB = -1;
    int maxB = -1;
    int nbPixel = 0;
    int* occurenceR = new int[256];
    int* occurenceG = new int[256];
    int* occurenceB = new int[256];
    for(int i = 0; i < 256; i++) {
        occurenceR[i] = 0;
        occurenceG[i] = 0;
        occurenceB[i] = 0;
    }

    // initialisation du generateur pseudo-aleatoire
    srand(atoi(argv[5]));

    OCTET* imgIn;
    OCTET* gray;
    OCTET* binary;
    OCTET* closing;
    OCTET* transform;
    OCTET* decrypt;
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
    allocation_tableau(closing, OCTET, size);
    allocation_tableau(transform, OCTET, (n*n)*3);
    allocation_tableau(decrypt, OCTET, (n*n)*3);
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

    //***************
    //*   CLOSING   *
    //***************

    cout << "begin closing" << endl;

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            closing[i*width+j] = binary[i*width+j];
        }
    }

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(binary[i*width+j] == 0) {
                // X | X | X
                //-----------
                // X | X | X
                //-----------
                // X | X | X
                for(int x = i-1; x < i+1; x++) {
                    for(int y = j-1; y < j+1; y++) {
                        if(x > 0) {
                            closing[(i-1)*width+j] = 0;
                        }
                        if(x < height-1) {
                            closing[(i+1)*width+j] = 0;
                        }
                        if(y > 0) {
                            closing[i*width+(j-1)] = 0;
                        }
                        if(y < width-1) {
                            closing[i*width+(j+1)] = 0;
                        }
                    }
                }
            }
        }
    }

    cout << "end closing" << endl;

    //******************
    //*   FIND ANGLE   *
    //******************

    cout << "begin angle" << endl;

    x = height / 2;
    y = width / 2;
    // UpLeft limite
    for(int i = 0; i < height/2; i++) {
        for(int j = 0; j < width/2; j++) {
            if(closing[i*width+j] == 0) {
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
            if(closing[i*width+j] == 0) {
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
            if(closing[i*width+j] == 0) {
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
            if(closing[i*width+j] == 0) {
                if(i - j > x - y) {
                    x = i;
                    y = j;
                }
            }
        }
    }
    Dx = x;
    Dy = y;

    // cout << "[" << Ax << ", " << Ay << "]" << "\t" << "[" << Bx << ", " << By << "]" << endl;
    // cout << "[" << Dx << ", " << Dy << "]" << "\t" << "[" << Cx << ", " << Cy << "]" << endl;

    cout << "end angle" << endl;

    //*****************
    //*   TRANSFORM   *
    //*****************

    cout << "begin transform" << endl;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            // cout << "[" << i << "," << j << "]" << endl;

            if(Bx - Ax == 0) {
                Ex = ((double)(i) / (double)(n)) + Ax;
            } else {
                Ex = ((double)(i) / ((double)(n) / (Bx - Ax))) + Ax;
            }
            Ey = ((double)(i) / ((double)(n) / (By - Ay))) + Ay;
            Fx = ((double)(j) / ((double)(n) / (Dx - Ax))) + Ax;
            if(Dy - Ay == 0) {
                Fy = ((double)(j) / (double)(n)) + Ay;
            } else {
                Fy = ((double)(j) / ((double)(n) / (Dy - Ay))) + Ay;
            }
            if(Cx - Dx == 0) {
                Gx = ((double)(i) / (double)(n)) + Dx;
            } else {
                Gx = ((double)(i) / ((double)(n) / (Cx - Dx))) + Dx;
            }
            Gy = ((double)(i) / ((double)(n) / (Cy - Dy))) + Dy;
            Hx = ((double)(j) / ((double)(n) / (Cx - Bx))) + Bx;
            if(Cy - By == 0) {
                Hy = ((double)(j) / (double)(n)) + By;
            } else {
                Hy = ((double)(j) / ((double)(n) / (Cy - By))) + By;
            }

            // cout << "\tE = [" << Ex << ", " << Ey << "]" << endl;
            // cout << "\tF = [" << Fx << ", " << Fy << "]" << endl;
            // cout << "\tG = [" << Gx << ", " << Gy << "]" << endl;
            // cout << "\tH = [" << Hx << ", " << Hy << "]" << endl;

            a1 = (Gy - Ey) / (Gx - Ex);
            b1 = Ey - a1 * Ex;
            if(Hx == Fx) {
                a2 = 0;
            } else {
                a2 = (Hy - Fy) / (Hx - Fx);
            }
            b2 = Fy - a2 * Fx;

            // cout << "\t" << a1 << "x + " << b1 << endl;
            // cout << "\t" << a2 << "x + " << b2 << endl;

            if(Fx == Hx) {
                Kx = Fx;
            } else {
                Kx = (int)round((b2 - b1) / (a1 - a2));
            }
            if(Ey == Gy) {
                Ky = Ey;
            } else {
                // cout << (b2 - b1) << " " << (a1 - a2) << endl;
                Ky = (int)round(a1 * ((b2 - b1) / (a1 - a2)) + b1);
            }

            // cout << "\t[" << Kx << "," << Ky << "]" << endl;

            transform[(j*3)*n+(i*3)+0] = imgIn[(Kx*3)*width+(Ky*3)+0];
            transform[(j*3)*n+(i*3)+1] = imgIn[(Kx*3)*width+(Ky*3)+1];
            transform[(j*3)*n+(i*3)+2] = imgIn[(Kx*3)*width+(Ky*3)+2];
        }
    }

    cout << "end transform" << endl;

    //***************
    //*   DECRYPT   *
    //***************

    if(atoi(argv[6]) == 0) {
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
                    decrypt[oldIndex*3+0] = transform[newIndex*3+0];
                    decrypt[oldIndex*3+1] = transform[newIndex*3+1];
                    decrypt[oldIndex*3+2] = transform[newIndex*3+2];
                }
            }

            // suppression de l'indice choisi dans le tableau
            index.erase(index.begin()+r);
            // reduction de la limite aleatoire
            k++;
        }

        cout << "end decrypt" << endl;
    } else {
        cout << "begin average decrypt" << endl;

        int averageR;
        int averageG;
        int averageB;

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

            // newIndex = newIndexFirst + (widthBlock/2) + ((widthBlock/2) * n);

            averageR = 0;
            averageG = 0;
            averageB = 0;

            // calcul de la moyenne du bloc
            for(int x = -1; x <= 1; x++) {
                for(int y = -1; y <= 1; y++) {
                    newIndex = newIndexFirst + ((widthBlock/2)+x) + (((widthBlock/2)+x) * n);
                    // newIndex = newIndexFirst + x + (y * n);
                    averageR += transform[newIndex*3+0];
                    averageG += transform[newIndex*3+1];
                    averageB += transform[newIndex*3+2];
                }
            }

            averageR /= 9;
            averageG /= 9;
            averageB /= 9;

            // boucle pour chaque pixel du bloc
            for(int x = 0; x < widthBlock; x++) {
                for(int y = 0; y < widthBlock; y++) {
                    // calcul du nouvel indice du pixel dans le bloc
                    oldIndex = oldIndexFirst + x + (y * n);

                    // melange
                    decrypt[oldIndex*3+0] = averageR;
                    decrypt[oldIndex*3+1] = averageG;
                    decrypt[oldIndex*3+2] = averageB;

                    // decrypt[oldIndex*3+0] = transform[newIndex*3+0];
                    // decrypt[oldIndex*3+1] = transform[newIndex*3+1];
                    // decrypt[oldIndex*3+2] = transform[newIndex*3+2];
                }
            }

            // suppression de l'indice choisi dans le tableau
            index.erase(index.begin()+r);
            // reduction de la limite aleatoire
            k++;
        }

        cout << "end average decrypt" << endl;
    }

    //*****************
    //* WHITE BALANCE *
    //*****************

    cout << "begin white balance" << endl;

    for(int i = 0; i < (n*n); i++) {
        occurenceR[decrypt[(i*3)+0]]++;
        occurenceG[decrypt[(i*3)+1]]++;
        occurenceB[decrypt[(i*3)+2]]++;
    }

    for(int i = 0; i <= 255; i++) {
        nbPixel += occurenceR[i];
        if(nbPixel > (n*n) * 0.0005) {
            minR = i;
            break;
        }
    }
    nbPixel = 0;
    for(int i = 255; i >= 0; i--) {
        nbPixel += occurenceR[i];
        if(nbPixel > (n*n) * 0.0005) {
            maxR = i;
            break;
        }
    }

    nbPixel = 0;
    for(int i = 0; i <= 255; i++) {
        nbPixel += occurenceG[i];
        if(nbPixel > (n*n) * 0.0005) {
            minG = i;
            break;
        }
    }
    nbPixel = 0;
    for(int i = 255; i >= 0; i--) {
        nbPixel += occurenceG[i];
        if(nbPixel > (n*n) * 0.0005) {
            maxG = i;
            break;
        }
    }

    nbPixel = 0;
    for(int i = 0; i <= 255; i++) {
        nbPixel += occurenceB[i];
        if(nbPixel > (n*n) * 0.0005) {
            minB = i;
            break;
        }
    }
    nbPixel = 0;
    for(int i = 255; i >= 0; i--) {
        nbPixel += occurenceB[i];
        if(nbPixel > (n*n) * 0.0005) {
            maxB = i;
            break;
        }
    }

    for(int i = 0; i < (n*n)*3; i+=3) {
        imgOut[i+0] = ((decrypt[i+0] - minR) * 255) / (maxR - minR);
        imgOut[i+1] = ((decrypt[i+1] - minG) * 255) / (maxG - minG);
        imgOut[i+2] = ((decrypt[i+2] - minB) * 255) / (maxB - minB);
    }

    cout << "end white balance" << endl;

    clock_t end2 = clock();

    ecrire_image_pgm((char*)"rsc/grayScale.pgm", gray, height, width);
    ecrire_image_pgm((char*)"rsc/binary.pgm", binary, height, width);
    ecrire_image_pgm((char*)"rsc/closing.pgm", closing, height, width);
    ecrire_image_ppm((char*)"rsc/transform.ppm", transform, n, n);
    ecrire_image_ppm((char*)"rsc/decrypt.ppm", decrypt, n, n);
    ecrire_image_ppm(argv[2], imgOut, n, n);

    delete[] occurence;

    fclose(file);

    delete imgOut;
    delete transform;
    delete binary;
    delete closing;
    delete gray;
    delete imgIn;

    clock_t end1 = clock();

    cout << "Computing time : " << ((float)(end2-begin2))/ CLOCKS_PER_SEC << endl;
    cout << "Total time : " << ((float)(end1-begin1))/ CLOCKS_PER_SEC << endl;

    return 0;
}
