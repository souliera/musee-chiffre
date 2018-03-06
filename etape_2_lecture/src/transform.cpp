#include <iostream>
#include <cstdlib>
#include <ctime>

#include "image_ppm.h"

using namespace std;

/*
 * Computing time : 0,0107705
 * Total time : 0,0138713
 */

int main(int argc, char *argv[]) {
    if(argc != 3) {
        cout << "Usage: " << argv[0] << " <originalImg.ppm> <transformImg.ppm>" << endl;
        exit(EXIT_FAILURE);
    }

    clock_t begin1 = clock();

    int height = 0;
    int width = 0;

    int n = 1000;

    OCTET* imgIn;
    OCTET* imgOut;

    lire_nb_lignes_colonnes_image_ppm(argv[1], &height, &width);
    int size = height * width;

    allocation_tableau(imgIn, OCTET, size*3);
    lire_image_ppm(argv[1], imgIn, size);
    allocation_tableau(imgOut, OCTET, (n*n)*3);

    double Ax = 791.0;
    double Ay = 602.0;
    double Bx = 1093.0;
    double By = 3123.0;
    double Cx = 3568.0;
    double Cy = 2819.0;
    double Dx = 3308.0;
    double Dy = 324.0;

    double Ex, Ey, Fx, Fy, Gx, Gy, Hx, Hy;
    int Kx, Ky;
    double a1, b1, a2, b2;

    clock_t begin2 = clock();

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

            // cout << "#Trace: hello o/" << endl;

            a1 = (Gy - Ey) / (Gx - Ex);
            b1 = Ey - a1 * Ex;
            a2 = (Hy - Fy) / (Hx - Fx);
            b2 = Fy - a2 * Fx;

            Kx = (int)round((b2 - b1) / (a1 - a2));
            Ky = (int)round(a1 * ((b2 - b1) / (a1 - a2)) + b1);

            // cout << "[" << Kx << "," << Ky << "]" << " ";

            imgOut[(j*3)*n+(i*3)+0] = imgIn[(Kx*3)*width+(Ky*3)+0];
            imgOut[(j*3)*n+(i*3)+1] = imgIn[(Kx*3)*width+(Ky*3)+1];
            imgOut[(j*3)*n+(i*3)+2] = imgIn[(Kx*3)*width+(Ky*3)+2];
        }

        // cout << endl;
    }

    clock_t end2 = clock();

    ecrire_image_ppm(argv[2], imgOut, n, n);

    delete imgOut;
    delete imgIn;

    clock_t end1 = clock();

    cout << "Computing time : " << ((float)(end2-begin2))/ CLOCKS_PER_SEC << endl;
    cout << "Total time : " << ((float)(end1-begin1))/ CLOCKS_PER_SEC << endl;

    return 0;
}
