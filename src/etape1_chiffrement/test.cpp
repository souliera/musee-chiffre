#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    cout << "Hello World!" << endl;

    int width = 8;
    int height = 8;
    int size = width*height;
    int blockWidth = 4;
    int nbBlock = blockWidth*blockWidth;
    int widthBlock = width/blockWidth;
    int sizeBlock = widthBlock*widthBlock;

    srand(atoi(argv[4]));
    cout << "key : " << atoi(argv[4]) << endl;

    int* tab1 = new int[size];
    for(int i = 0; i < size; i++) {
        tab1[i] = i;
    }
    int* tab2 = new int[size];
    for(int i = 0; i < size; i++) {
        tab2[i] = 0;
    }

    for(int i = 0; i < size; i++) {
        if(i % width == 0) {
            cout << endl;
        }
        cout << tab1[i] << "\t";
    }
    cout << endl;
    for(int i = 0; i < size; i++) {
        if(i % width == 0) {
            cout << endl;
        }
        cout << tab2[i] << "\t";
    }
    cout << endl;

    vector<int> index;
    for(int i = 0; i < nbBlock; i++) {
        index.push_back(i);
    }

    int r;
    int newBlockIndex;
    int oldIndexFirst, newIndexFirst;
    int oldIndex, newIndex;

    int n = 0;

    for(int i = 0; i < nbBlock; i++) {
        r = rand() % (nbBlock - n);
        newBlockIndex = index[r];

        if(i == 0) {
            oldIndexFirst = 0;
        } else {
            oldIndexFirst = (i - (i % sizeBlock)) * sizeBlock + ((i % sizeBlock) * 2);
        }
        if(newBlockIndex == 0) {
            newIndexFirst = 0;
        } else {
            newIndexFirst = (newBlockIndex - (newBlockIndex % sizeBlock)) * sizeBlock + ((newBlockIndex % sizeBlock) * 2);
        }

        cout << "old : " << oldIndexFirst << ", new : " << newIndexFirst << endl;

        for(int x = 0; x < widthBlock; x++) {
            for(int y = 0; y < widthBlock; y++) {
                newIndex = newIndexFirst + x + (y * width);
                oldIndex = oldIndexFirst + x + (y * width);

                cout << oldIndex << " " << newIndex << endl;

                tab2[newIndex] = tab1[oldIndex];
            }
        }

        index.erase(index.begin()+r);
        n++;
    }

    for(int i = 0; i < size; i++) {
        if(i % width == 0) {
            cout << endl;
        }
        cout << tab1[i] << "\t";
    }
    cout << endl;
    for(int i = 0; i < size; i++) {
        if(i % width == 0) {
            cout << endl;
        }
        cout << tab2[i] << "\t";
    }

    cout << "Goobye World!" << endl;
}
