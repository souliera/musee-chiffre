#ifndef IMAGE_DEF_HPP
#define IMAGE_DEF_HPP

class Image {
    private:
        char _type[2];
        int _height;
        int _width;
        int _size;
        int _maxValue;
        int* _dataP2;
        unsigned char* _dataP5;

    public:
        Image(char*);
        void load(char*);
        void save(char*);

        void arnoldTransform();
        void bakerMap(int*);
        void queueTransform(int, int);

        char* getType();
        int getHeight() const;
        int getWidth() const;
        int* getDataP2() const;
        unsigned char* getDataP5();
        void setDataP2(int*);
        void setDataP5(unsigned char*);

        void toString();
};

#endif
