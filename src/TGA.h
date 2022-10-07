
#ifndef PROJECT2_TGA_H
#define PROJECT2_TGA_H

#include <fstream>
#include <string>
using namespace std;


class TGA {

private:
        struct Header{
            char idLength;
            char colorMapType;
            char dataTypeCode;
            short colorMapOrigin;
            short colorMapLength;
            char colorMapDepth;
            short xOrigin;
            short yOrigin;
            short width;
            short height;
            char bitsPerPixel;
            char imageDescriptor;
        };

        struct Pixel{
            unsigned char Red;
            unsigned char Green;
            unsigned char Blue;
        };

        Header header;
        Pixel* image;
        int imageSize;  //in Pixels = header.height * header.width

        bool ReadHeader(ifstream& file);
        bool ReadImage(ifstream& file);
        bool WriteHeader(ofstream& file);

public:
    TGA();
    void ReadFromFile(string inputFileName);
    void PrintHeader();
    void WriteToFile(string outputFileName);
    bool compareImage(TGA* target);
    bool compareHeader(TGA *target);
    void Multiply(TGA* other);
    void Screen(TGA* other);
    void Subtract(TGA* other);
    void AddToChannel(char channel, int value); //channel R is Red, G is Green, B is Blue
    void CopyOneChannelToOne(char channel, TGA* target);
    void CopyOneChannelToAll(char channel, TGA* target);
    void CopyHeaderTo(TGA* target);
    void CopyImageTo(TGA* target);
    void RotateImage(TGA* from);
    int calcOverlay(int A, int B);
    void MultiplyToChannel(char channel, int value);
    void Overlay(TGA *other);
    void CopySourceToTarget(TGA* source, TGA* target, int startX, int startY);
    void InitializeImage(int width, int height);
    int getWidth();
    int getHeight();
};


#endif //PROJECT2_TGA_H
