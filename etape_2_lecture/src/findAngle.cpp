#include <iostream>
#include <cstdlib>
#include <ctime>

#include "image_ppm.h"

using namespace std;

/*
 * Computing time : 0,0000242
 * Total time : 0,0006996
 */

int main(int argc, char *argv[]) {
    if(argc != 2) {
        cout << "Usage: " << argv[0] << " <binaryImg>" << endl;
        exit(EXIT_FAILURE);
    }

    clock_t begin1 = clock();

    int height = 0;
    int width = 0;

    OCTET* imgIn;

    lire_nb_lignes_colonnes_image_pgm(argv[1], &height, &width);
    int size = height * width;

    allocation_tableau(imgIn, OCTET, size);
    lire_image_pgm(argv[1], imgIn, size);

    int ulX, ulY, urX, urY, drX, drY, dlX, dlY;

    int x, y;

    clock_t begin2 = clock();

    // // limite upLeft
    // int i = height / 2;
    // int j = width / 2;
    //
    // do {
    //     if(imgIn[(i-1)*width+j] != 255) {
    //         i--;
    //     } else if(imgIn[i*width+(j-1)] != 255) {
    //         j--;
    //     } else if(imgIn[(i-1)*width+(j-1)] != 255) {
    //         i--;
    //         j--;
    //     } else if(imgIn[(i+1)*width+(j-1)] != 255) {
    //         i++;
    //         j--;
    //     }
    //
    //     if(i == 0 || j == 0) {
    //         break;
    //     }
    // } while(imgIn[(i-1)*width+j] != 255 || imgIn[i*width+(j-1)] != 255);
    //
    // ulX = i;
    // ulY = j;
    //
    // // limite upRight
    // i = height / 2;
    // j = width / 2;
    //
    // do {
    //     if(imgIn[(i-1)*width+j] != 255) {
    //         i--;
    //     } else if(imgIn[i*width+(j+1)] != 255) {
    //         j++;
    //     } else if(imgIn[(i-1)*width+(j+1)] != 255) {
    //         i--;
    //         j++;
    //     } else if(imgIn[(i+1)*width+(j+1)] != 255) {
    //         i++;
    //         j++;
    //     } else if(imgIn[(i+1)*width+(j+1)] != 255) {
    //     } else {
    //         break;
    //     }
    //
    //     if(i == 0 || j == width-1) {
    //         break;
    //     }
    // } while(1);
    //
    // urX = i;
    // urY = j;
    //
    // // limite downRight
    // i = height / 2;
    // j = width / 2;
    //
    // do {
    //     if(imgIn[(i+1)*width+j] != 255) {
    //         i++;
    //     } else if(imgIn[i*width+(j+1)] != 255) {
    //         j++;
    //     } else if(imgIn[(i+1)*width+(j+1)] != 255) {
    //         i++;
    //         j++;
    //     } else if(imgIn[(i-1)*width+(j+1)] != 255) {
    //         i--;
    //         j++;
    //     }
    //
    //     if(i == height-1 || j == width-1) {
    //         break;
    //     }
    // } while(imgIn[(i+1)*width+j] != 255 || imgIn[i*width+(j+1)] != 255);
    //
    // drX = i;
    // drY = j;
    //
    // // limite downLeft
    // i = height / 2;
    // j = width / 2;
    //
    // do {
    //     if(imgIn[(i+1)*width+j] != 255) {
    //         i++;
    //     } else if(imgIn[i*width+(j+1)] != 255) {
    //         j++;
    //     } else if(imgIn[(i+1)*width+(j-1)] != 255) {
    //         i++;
    //         j--;
    //     } else if(imgIn[(i-1)*width+(j-1)] != 255) {
    //         i--;
    //         j--;
    //     }
    //
    //     if(i == height-1 || j == 0) {
    //         break;
    //     }
    // } while(imgIn[(i+1)*width+j] != 255 || imgIn[i*width+(j-1)] != 255);
    //
    // dlX = i;
    // dlY = j;

    x = height / 2;
    y = width / 2;
    // UpLeft limite
    for(int i = 0; i < height/2; i++) {
        for(int j = 0; j < width/2; j++) {
            if(imgIn[i*width+j] == 0) {
                if(i + j < x + y) {
                    x = i;
                    y = j;
                }
            }
        }
    }

    ulX = x;
    ulY = y;

    x = height / 2;
    y = width / 2;
    // UpRight limite
    for(int i = 0; i < height/2; i++) {
        for(int j = width-1; j > width/2; j--) {
            if(imgIn[i*width+j] == 0) {
                if(j - i > y - x) {
                    x = i;
                    y = j;
                }
            }
        }
    }

    urX = x;
    urY = y;

    x = height / 2;
    y = width / 2;
    // DownRight limite
    for(int i = height-1; i > height/2; i--) {
        for(int j = width-1; j > width/2; j--) {
            if(imgIn[i*width+j] == 0) {
                if(i + j > x + y) {
                    x = i;
                    y = j;
                }
            }
        }
    }

    drX = x;
    drY = y;

    x = height / 2;
    y = width / 2;
    // DownLeft limite
    for(int i = height-1; i > height/2; i--) {
        for(int j = 0; j < width/2; j++) {
            if(imgIn[i*width+j] == 0) {
                if(i - j > x - y) {
                    x = i;
                    y = j;
                }
            }
        }
    }

    dlX = x;
    dlY = y;

    clock_t end2 = clock();

    cout << "[" << ulX << "," << ulY << "]" << "\t" << "[" << urX << "," << urY << "]" << endl;
    cout << endl;
    cout << "[" << dlX << "," << dlY << "]" << "\t" << "[" << drX << "," << drY << "]" << endl;

    delete imgIn;

    clock_t end1 = clock();

    cout << "Computing time : " << ((float)(end2-begin2))/ CLOCKS_PER_SEC << endl;
    cout << "Total time : " << ((float)(end1-begin1))/ CLOCKS_PER_SEC << endl;

    return 0;
}
