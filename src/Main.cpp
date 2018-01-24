#include <iostream>
#include <cstdlib>
#include <cstring>

#include "Image.hpp"
#include "Function.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    if(argc < 2) {
        cout << "Usage: " << argv[0] << " input_file output_file" << endl;
        exit(EXIT_FAILURE);
    }

    Image* img = new Image(argv[1]);
    arnoldTransform(img);
    img->save(argv[2]);

    return 0;
}
