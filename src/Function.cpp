#include <cstring>

#include "Function.hpp"
#include "Image.hpp"

using namespace std;

void arnoldTransform(Image* img) {
    int height = img->getHeight();
    int width = img->getWidth();

    if(strcmp(img->getType(), "P2") == 0) {
        int* data = img->getDataP2();
        int* tmp = new int[height*width];

        for(int i = 0; i < height; i++) {
    		for(int j = 0; j < width; j++) {
                tmp[(((2*i)+j) % width)*width+((i+j) % width)] = data[i*width+j];
    		}
    	}

        img->setDataP2(tmp);
    } else if(strcmp(img->getType(), "P5") == 0) {
        unsigned char* data = img->getDataP5();
        unsigned char* tmp = new unsigned char[height*width];
        for(int i = 0; i < height; i++) {
    		for(int j = 0; j < width; j++) {
                tmp[(((2*i)+j) % width)*width+((i+j) % width)] = data[i*width+j];
            }
    	}

        img->setDataP5(tmp);
    }
}

// void bakerMap(Image& img, const int* n) {
//     int* q = new int[9];
//     int* N = new int[9];
//     N[0] = 0;
//     for(int i = 0; i < 9; i++) {
//         q[i] = (_height*_width) / n[i];
//         N[i] = N[i] + n[i];
//     }
//
//     if(strcmp(_type, "P2") == 0) {
//         int* tmp = new int[_height*_width];
//
//
//
//         _dataP2 = tmp;
//     } else if(strcmp(_type, "P5") == 0) {
//         unsigned char* tmp = new unsigned char[_height*_width];
//
//         for(int i = 0; i < _height; i++) {
//             for(int j = 0; j < _width; j++) {
//                 int k = 0;
//                 if(i >= N[k]) {
//                     for(int l = 1; l < 9; l++) {
//                         k = l;
//                         if(i < N[k]) {
//                             break;
//                         }
//                     }
//                 }
//                 // cout << "coucou" << endl;
//                 if(i < (_height*_width) / 2) {
//                     tmp[(i*2)*_width+(j/2)] = _dataP5[i*_width+j];
//                 } else {
//                     tmp[((i*2)+1)*_width+((j/2)+(1/2))] = _dataP5[i*_width+j];
//                 }
//             }
//         }
//
//         _dataP5 = tmp;
//     }
// }
//
// void queueTransform(Image& img, const int R, const int S) {
//     if(strcmp(_type, "P2") == 0) {
//         int* tmp = new int[_height*_width];
//
//         for(int i = 0; i < _height; i++) {
//             if(i > R) {
//                 for(int j = 0; j < _width; j++) {
//                     tmp[i*_width+((j+1)%_width)] = _dataP2[i*_width+j];
//                 }
//             } else {
//                 for(int j = 0; j < _width; j++) {
//                     tmp[i*_width+((j-1)%_width)] = _dataP2[i*_width+j];
//                 }
//             }
//         }
//
//         for(int j = 0; j < _width; j++) {
//             if(j > S) {
//                 for(int i = 0; i < _height; i++) {
//                     // cout << i << " " << j << endl;
//                     // cout << (i-1)%_width << endl;
//                     // cout << "tmp[" << ((i-1)%_width)*_width+j << "] : " << tmp[((i-1)%_width)*_width+j] << endl;
//                     // cout << "dataP2[" << i*_width+j << "] : " << endl;
//                     // cout <<  _dataP2[0] << endl;
//                     cout << "blup" << endl;
//                     cout << "_dataP2[" << i*_width+j << "] : " << _dataP2[i*_width+j] << endl;
//                     cout << "blop" << endl;
//                     tmp[((i-1)%_width)*_width+j] = _dataP2[i*_width+j];
//                     cout << "blip" << endl;
//                 }
//             } else {
//                 for(int i = 0; i < _height; i++) {
//                     cout << "blup" << endl;
//                     cout << "_dataP2[" << i*_width+j << "] : " << _dataP2[i*_width+j] << endl;
//                     cout << "blop" << endl;
//                     tmp[((i+1)%_width)*_width+j] = _dataP2[i*_width+j];
//                 }
//             }
//         }
//         // cout << endl << endl << endl;
//         // cout << "tmp";
//         // for(int i = 0; i < _height; i++) {
//         //     for(int j = 0; j < _width; j++) {
//         //         cout << tmp[i*_width+j] << " ";
//         //     }
//         //     cout << endl;
//         // }
//
//         _dataP2 = tmp;
//         delete[] tmp;
//     } else if(strcmp(_type, "P5") == 0) {
//         cout << "salut" << endl << endl << endl;
//         unsigned char* tmp = new unsigned char[_height*_width];
//
//         for(int i = 0; i < _height; i++) {
//             if(i > R) {
//                 for(int j = 0; j < _width; j++) {
//                     tmp[(((i*_width) % _width) + j+1)] = _dataP5[i*_width+j];
//                 }
//             } else {
//                 for(int j = 0; j < _width; j++) {
//                     tmp[(((i*_width) % _width) + j-1)] = _dataP5[i*_width+j];
//                 }
//             }
//         }
//
//         for(int j = 0; j < _width; j++) {
//             if(j > S) {
//                 for(int i = 0; i < _height; i++) {
//                     tmp[((((i+1)*_width) % _width) + j)] = _dataP5[i*_width+j];
//                 }
//             } else {
//                 for(int i = 0; i < _height; i++) {
//                     tmp[((((i-1)*_width) % _width) + j)] = _dataP5[i*_width+j];
//                 }
//             }
//         }
//
//         _dataP5 = tmp;
//         delete[] tmp;
//     }
// }
