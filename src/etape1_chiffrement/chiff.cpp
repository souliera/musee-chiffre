#include <iostream>
#include <cstdlib>
#include <vector>

#include "ImageBase.h"

using namespace std;

int main(int argc, char *argv[]) {
    if(argc != 5) {
        cout << "Usage: " << argv[0] << " <input_filename> <output_filename> <nb_bloc> <key>" << endl;
        exit(EXIT_FAILURE);
    }

    cout << "Hello World" << endl;

    ImageBase imgIn = ImageBase();
    imgIn.load(argv[1]);

    int height = imgIn.getHeight();
    int width = imgIn.getWidth();
    int size = height * width;

    cout << height << "x" << width << endl;

    ImageBase imgChif = ImageBase(height, width, imgIn.getColor());

    srand(atoi(argv[4]));
    cout << "key : " << atoi(argv[4]) << endl;

    vector<int> index;
    for(int i = 0; i < size; i++) {
        index.push_back(i);
    }

    int n = -1;

    for(int x = 0; x < height; x++) {
        for(int y = 0; y < width; y++) {
            int r = rand() % (size - n);
            int newIndexX = index[r] / height;
            int newIndexY = index[r] % height;

            // cout << "it : " << x*width+y << " r : " << r << " n : " << n << endl;
            // cout << "x : " << newIndexX << " y : " << newIndexY << endl;

            // cout << "#trace 1" << endl;
            imgChif[newIndexX*3][newIndexY*3+0] = imgIn[x*3][y*3+0];
            // cout << "#trace 2" << endl;
            imgChif[newIndexX*3][newIndexY*3+1] = imgIn[x*3][y*3+1];
            // cout << "#trace 3" << endl;
            imgChif[newIndexX*3][newIndexY*3+2] = imgIn[x*3][y*3+2];
            // cout << "#trace 4" << endl;

            index.erase(index.begin()+r-1);
            // cout << "#trace 5" << endl;

            n++;
            // cout << "#trace 6" << endl;
        }
    }

    imgChif.save(argv[2]);

    ImageBase imgClr = ImageBase(height, width, imgIn.getColor());

    srand(atoi(argv[4]));
    cout << "key : " << atoi(argv[4]) << endl;

    index.clear();
    for(int i = 0; i < size; i++) {
        index.push_back(i);
    }

    n = -1;

    for(int x = 0; x < height; x++) {
        for(int y = 0; y < width; y++) {
            int r = rand() % (size - n);
            int newIndexX = index[r] / height;
            int newIndexY = index[r] % height;

            // cout << "it : " << x*width+y << " r : " << r << " n : " << n << endl;
            // cout << "x : " << newIndexX << " y : " << newIndexY << endl;

            // cout << "#trace 1" << endl;
            imgClr[x*3][y*3+0] = imgChif[newIndexX*3][newIndexY*3+0];
            // cout << "#trace 2" << endl;
            imgClr[x*3][y*3+1] = imgChif[newIndexX*3][newIndexY*3+1];
            // cout << "#trace 3" << endl;
            imgClr[x*3][y*3+2] = imgChif[newIndexX*3][newIndexY*3+2];
            // cout << "#trace 4" << endl;

            index.erase(index.begin()+r-1);
            // cout << "#trace 5" << endl;

            n++;
            // cout << "#trace 6" << endl;
        }
    }

    imgClr.save((char*)"rsc/back.ppm");

    cout << "Goodbye World" << endl;

    return 0;
}
