#include <iostream>
#include <cstdio>
#include <cstring>

#include "Image.hpp"

using namespace std;

Image::Image(char* filename) : _height(0), _width(0), _maxValue(0), _size(0) {
    load(filename);
}

void Image::load(char* filename) {
    FILE* file = fopen(filename, "r");
    if(file) {
        fscanf(file, "%s", _type);
        fscanf(file, "%d", &_height);
        fscanf(file, "%d", &_width);
        fscanf(file, "%d%*c", &_maxValue);
        if(strcmp(_type, (char*)"P2") == 0) {
            _dataP2 = new int[_height*_width];
            for(int i = 0; i < _height; i++) {
                for(int j = 0; j < _width; j++) {
                    fscanf(file, "%d", &_dataP2[i*_width+j]);
                }
            }
        } else if(strcmp(_type, (char*)"P5") == 0) {
            _dataP5 = new unsigned char[_height*_width];
            fread(_dataP5, sizeof(char), _height*_width, file);
        }
    }
    _size = _height * _width;
    fclose(file);
}

void Image::save(char* filename) {
    FILE* file = fopen(filename, "w");
    fprintf(file, "%s\n", _type);
    fprintf(file, "%d %d\n", _height, _width);
    fprintf(file, "%d\n", _maxValue);
    if(strcmp(_type, "P2") == 0) {
        for(int i = 0; i < _height; i++) {
            for(int j = 0; j < _width; j++) {
                fprintf(file, "%d ", _dataP2[i*_width+j]);
            }
            fprintf(file, "\n");
        }
    } else if(strcmp(_type, "P5") == 0) {
        fwrite(_dataP5, sizeof(char), _height*_width, file);
    }
    fclose(file);
}

char* Image::getType() {
    return _type;
}

int Image::getHeight() const {
    return _height;
}

int Image::getWidth() const {
    return _width;
}

int* Image::getDataP2() const {
    return _dataP2;
}

unsigned char* Image::getDataP5() {
    return _dataP5;
}

void Image::setDataP2(int* dataP2) {
    for(int i = 0; i < _size; i++) {
        _dataP2[i] = dataP2[i];
    }
}

void Image::setDataP5(unsigned char* dataP5) {
    for(int i = 0; i < _size; i++) {
        _dataP5[i] = dataP5[i];
    }
}


void Image::toString() {
    cout << _type << endl;
    cout << _height << " " << _width << endl;
    cout << _maxValue << endl;
    if(strcmp(_type, "P2") == 0) {
        for(int i = 0; i < _height; i++) {
            for(int j = 0; j < _width; j++) {
                cout << _dataP2[i*_width+j] << " ";
            }
            cout << endl;
        }
    } else if(strcmp(_type, "P5") == 0) {
        for(int i = 0; i < _height; i++) {
            for(int j = 0; j < _width; j++) {
                cout << _dataP5[i*_width+j];
            }
            cout << endl;
        }
    }
}
