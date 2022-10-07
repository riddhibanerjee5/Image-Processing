
#ifndef PROJECT2_TGA_CPP
#define PROJECT2_TGA_CPP


#include "TGA.h"
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

TGA::TGA() {
 //   null;
}

void TGA::ReadFromFile(string inputFileName) {
    ifstream inFile(inputFileName, ios::in|ios::binary);
    if (ReadHeader(inFile)) {
        if (!ReadImage(inFile)){
            throw runtime_error("Unable to read image from file: " + inputFileName);
        }
    } else {
        throw runtime_error("Unable to read header from file " + inputFileName);
    }
    inFile.close();
}

bool TGA::ReadHeader(ifstream &file) {
    if (file.is_open()) {
        file.read((char *)&header.idLength, sizeof(header.idLength));
        file.read((char *)&header.colorMapType, sizeof(header.colorMapType));
        file.read((char *)&header.dataTypeCode, sizeof(header.dataTypeCode));
        file.read((char *)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
        file.read((char *)&header.colorMapLength, sizeof(header.colorMapLength));
        file.read((char *)&header.colorMapDepth, sizeof(header.colorMapDepth));
        file.read((char *)&header.xOrigin, sizeof(header.xOrigin));
        file.read((char *)&header.yOrigin, sizeof(header.yOrigin));
        file.read((char *)&header.width, sizeof(header.width));
        file.read((char *)&header.height, sizeof(header.height));
        file.read((char *)&header.bitsPerPixel, sizeof(header.bitsPerPixel));
        file.read((char *)&header.imageDescriptor, sizeof(header.imageDescriptor));
        return true;
    } else {
        return false;
    }
}

bool TGA::WriteHeader(ofstream &file) { 
    if (file.is_open()) {
        file.write((char *)&header.idLength, sizeof(header.idLength));
        file.write((char *)&header.colorMapType, sizeof(header.colorMapType));
        file.write((char *)&header.dataTypeCode, sizeof(header.dataTypeCode));
        file.write((char *)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
        file.write((char *)&header.colorMapLength, sizeof(header.colorMapLength));
        file.write((char *)&header.colorMapDepth, sizeof(header.colorMapDepth));
        file.write((char *)&header.xOrigin, sizeof(header.xOrigin));
        file.write((char *)&header.yOrigin, sizeof(header.yOrigin));
        file.write((char *)&header.width, sizeof(header.width));
        file.write((char *)&header.height, sizeof(header.height));
        file.write((char *)&header.bitsPerPixel, sizeof(header.bitsPerPixel));
        file.write((char *)&header.imageDescriptor, sizeof(header.imageDescriptor));
        return true;
    } else {
        return false;
    }
}

bool TGA::ReadImage(ifstream &file) {
    imageSize = header.height * header.width;

    if (imageSize > 0) {
        image = new Pixel[imageSize];
        Pixel* tmpImage = image;
        char * imageInChars = new char[imageSize * 3 + 1];
        imageInChars[imageSize * 3] = '\0';
        file.read(imageInChars, imageSize * 3 * sizeof(imageInChars[0]));
        for (int i = 0; i < imageSize; i++ ) {
            tmpImage->Blue = imageInChars[3*i];
            tmpImage->Green = imageInChars[3*i+1];
            tmpImage->Red = imageInChars[3*i+2];
            tmpImage++;
        }
        delete [] imageInChars;
        return true;
    } else {
        cout << "No image data found" << endl;
        return false;
    }
}


void TGA::PrintHeader() {
        cout << "ID Length: " << (short) header.idLength << endl;
        cout << "Color Map Type: " << (short) header.colorMapType << endl;
        cout << "Data Type Code: " << (short) header.dataTypeCode << endl;
        cout << "Color Map Origin: " << header.colorMapOrigin << endl;
        cout << "Color Map Length: " << header.colorMapLength << endl;
        cout << "Color Map Depth: " << header.colorMapDepth << endl;
        cout << "X Origin: " << header.xOrigin << endl;
        cout << "Y Origin: " << header.yOrigin << endl;
        cout << "Width: " << header.width << endl;
        cout << "Height: " << header.height << endl;
        cout << "Bits per pixel: " << (short) header.bitsPerPixel << endl;
        cout << "Image Descriptor: " << header.imageDescriptor << endl;
}

void TGA::WriteToFile(string outputFileName) {
    ofstream outFile(outputFileName, ios_base::binary);
    if(outFile.is_open()) {
        if (WriteHeader(outFile)) {
                Pixel* thisImage = image;
                char* img = new char[imageSize * 3 + 1];
                img[imageSize * 3] = '\0';
                char* imgPtr = img;
                for (int i = 0; i < imageSize; i++) {
                    img[3*i] = thisImage->Blue;
                    img[3*i+1] = thisImage->Green;
                    img[3*i+2] = thisImage->Red;

                    thisImage++;
                }
               outFile.write(img, (imageSize * 3));
        }
        outFile.close();
    }
}

bool TGA::compareHeader(TGA *target) {
    if(header.idLength != target->header.idLength){
        return false;
    }
    if(header.colorMapType != target->header.colorMapType){
        return false;
    }
    if(header.dataTypeCode != target->header.dataTypeCode){
        return false;
    }
    if(header.colorMapOrigin != target->header.colorMapOrigin){
        return false;
    }
    if(header.colorMapLength != target->header.colorMapLength){
        return false;
    }
    if(header.colorMapDepth != target->header.colorMapDepth){
        return false;
    }
    if(header.xOrigin != target->header.xOrigin){
        return false;
    }
    if(header.yOrigin != target->header.yOrigin){
        return false;
    }
    if(header.width != target->header.width){
        return false;
    }
    if(header.height != target->header.height){
        return false;
    }
    if(header.bitsPerPixel!= target->header.bitsPerPixel){
        return false;
    }
    if(header.imageDescriptor != target->header.imageDescriptor){
        return false;
    }
    return true;
}

bool TGA::compareImage(TGA* target) {
    Pixel* thisImage = image;
    Pixel* targetImage = target->image;
    for (int i = 0; i < imageSize; i++){
        if(thisImage->Red == targetImage->Red && thisImage->Green == targetImage->Green && thisImage->Blue == targetImage->Blue){
            thisImage++;
            targetImage++;
        } else {
            return false;
        }
    }
    return true;
}

void TGA::AddToChannel(char channel, int value) {
        Pixel* thisImage = image;
        int newValue;
        for (int i = 0; i < imageSize; i++ ) {
            if (channel == 'R') {
                newValue = thisImage->Red + value;
                thisImage->Red = (newValue > 255)? 255: newValue;
            }
            if (channel == 'B') {
                newValue = thisImage->Blue + value;
                thisImage->Blue = (newValue > 255)? 255: newValue;
            }
            if (channel == 'G') {
                newValue = thisImage->Green + value;
                thisImage->Green = (newValue > 255)? 255: newValue;
            }
            thisImage++;
        }
}

void TGA::MultiplyToChannel(char channel, int value) {
    Pixel* thisImage = image;
    int newValue;
    for (int i = 0; i < imageSize; i++ ) {
        if (channel == 'R') {
            newValue = (thisImage->Red/255.0f) * (value) * 255.0f + 0.5f;
            thisImage->Red = (newValue > 255)? 255: newValue;
        }
        if (channel == 'B') {
            newValue = (thisImage->Blue/255.0f) * (value) * 255.0f + 0.5f;
            thisImage->Blue = (newValue > 255)? 255: newValue;
        }
        if (channel == 'G') {
            newValue = (thisImage->Green/255.0f) * (value) * 255.0f + 0.5f;
            thisImage->Green = (newValue > 255)? 255: newValue;
        }
        thisImage++;
    }
}

void TGA::Multiply(TGA* other) {
    Pixel* thisImage = image;
    Pixel* otherImage = other->image;
    int newValue;
    for(int i = 0; i < imageSize; i++) {
        newValue = (thisImage->Red/255.0f) * (otherImage->Red/255.0f) * 255.0f + 0.5f;
        thisImage->Red = (newValue > 255)? 255: newValue;

        newValue = (thisImage->Green/255.0f) * (otherImage->Green/255.0f) * 255.0f + 0.5f;
        thisImage->Green = (newValue > 255)? 255: newValue;

        newValue = (thisImage->Blue/255.0f) * (otherImage->Blue/255.0f) * 255.0f + 0.5f;
        thisImage->Blue = (newValue > 255)? 255: newValue;

        thisImage++;
        otherImage++;
    }
}

void TGA::Screen(TGA *other) {
    Pixel* thisImage = image;
    Pixel* otherImage = other->image;
    int newValue;
    for(int i = 0; i < imageSize; i++){
        newValue = (1 -(1 - thisImage->Red/255.0f) * (1 - otherImage->Red/255.0f)) * 255.0f + 0.5f;
        thisImage->Red = (newValue > 255)? 255: newValue;

        newValue = (1 - (1 - thisImage->Green/255.0f) * (1 - otherImage->Green/255.0f)) * 255.0f + 0.5f;
        thisImage->Green = (newValue > 255)? 255: newValue;

        newValue = (1 - (1 - thisImage->Blue/255.0f) * (1 - otherImage->Blue/255.0f)) * 255.0f + 0.5f;
        thisImage->Blue = (newValue > 255)? 255: newValue;

        thisImage++;
        otherImage++;
    }
}

void TGA::CopyOneChannelToOne(char channel, TGA* target) {
    Pixel* thisImage = image;
    Pixel* targetImage = target->image;
    int val;
    for (int i = 0; i < imageSize; i++ ) {
        if (channel == 'R') {
            val = thisImage->Red;
            targetImage->Red = val;
        }
        if (channel == 'B') {
            val = thisImage->Blue;
            targetImage->Blue = val;
        }
        if (channel == 'G') {
            val = thisImage->Green;
            targetImage->Green = val;
        }
        thisImage++;
        targetImage++;
    }
}

void TGA::CopyOneChannelToAll(char channel, TGA *target) {
    Pixel* thisImage = image;
    Pixel* targetImage = target->image;
    int val;
    for (int i = 0; i < imageSize; i++ ) {
        if (channel == 'R') {
            val = thisImage->Red;
        }
        if (channel == 'B') {
            val = thisImage->Blue;
        }
        if (channel == 'G') {
            val = thisImage->Green;
        }
        targetImage->Red = val;
        targetImage->Green = val;
        targetImage->Blue = val;

        thisImage++;
        targetImage++;
    }
}

void TGA::CopyHeaderTo(TGA* target) {
    target->header.idLength = header.idLength;
    target->header.colorMapType = header.colorMapType;
    target->header.dataTypeCode = header.dataTypeCode;
    target->header.colorMapOrigin = header.colorMapOrigin;
    target->header.colorMapLength = header.colorMapLength;
    target->header.colorMapDepth = header.colorMapDepth;
    target->header.xOrigin = header.xOrigin;
    target->header.yOrigin = header.yOrigin;
    target->header.width = header.width;
    target->header.height = header.height;
    target->header.bitsPerPixel = header.bitsPerPixel;
    target->header.imageDescriptor = header.imageDescriptor;
}

void TGA::CopyImageTo(TGA *target) {
    target->image = new Pixel[imageSize];
    Pixel* targetImage = target->image;
    Pixel* thisImage = image;
    target->imageSize = imageSize;
    int val;
    for (int i = 0; i < imageSize; i++ ) {
        val = thisImage->Red;
        targetImage->Red = val;
        val = thisImage->Blue;
        targetImage->Blue = val;
        val = thisImage->Green;
        targetImage->Green = val;

        thisImage++;
        targetImage++;
    }
}

void TGA::RotateImage(TGA* target){
    Pixel* srcPtr = image;
    Pixel* targetPtr = target->image + (imageSize-1);

    int val;
    for(int i = 0; i < imageSize; i++){
        val = srcPtr->Blue;
        targetPtr->Blue = val;
        val = srcPtr->Red;
        targetPtr->Red = val;
        val = srcPtr->Green;
        targetPtr->Green = val;

        srcPtr++;
        targetPtr--;
    }
}

void TGA::Subtract(TGA* other) {
    Pixel* thisImage = image;
    Pixel* otherImage = other->image;
    int newValue;
    for(int i = 0; i < imageSize; i++) {
        newValue = thisImage->Red - otherImage->Red;
        thisImage->Red = (newValue < 0)? 0: newValue;

        newValue = thisImage->Green - otherImage->Green;
        thisImage->Green = (newValue < 0)? 0: newValue;

        newValue = thisImage->Blue - otherImage->Blue;
        thisImage->Blue = (newValue < 0)? 0: newValue;

        thisImage++;
        otherImage++;
    }
}


int TGA::calcOverlay(int a, int b) {
    float A = a / 255.0f;
    float B = b / 255.0f;
    float C;
    int ret;
    if (B <= 0.5) {
        C = 2 * A * B;
    } else {
        C = 1 - 2 * (1 -A) * (1 - B);
    }
    ret = C * 255.0f + 0.5f;
    ret = (ret > 255)? 255: ret;
    return ret;
}


void TGA::Overlay(TGA* other) {
    Pixel* thisImage = image;
    Pixel* otherImage = other->image;
    int newVal;
    for(int i = 0; i < imageSize; i++) {
        thisImage->Red = calcOverlay( thisImage->Red,  otherImage->Red);
        thisImage->Green = calcOverlay( thisImage->Green,  otherImage->Green);
        thisImage->Blue = calcOverlay( thisImage->Blue,  otherImage->Blue);

        thisImage++;
        otherImage++;
    }
}

void TGA::CopySourceToTarget(TGA *source, TGA *target, int startX, int startY) {
    Pixel* sourcePtr = source->image;
    Pixel* targetPtr = target->image + startY * target->header.width + startX ;
    for(int y = 0; y < source->header.height; y++){
        for(int x = 0; x < source->header.width; x++){
            targetPtr->Blue = sourcePtr->Blue;
            targetPtr->Green = sourcePtr->Green;
            targetPtr->Red = sourcePtr->Red;
            targetPtr++;
            sourcePtr++;
        }
        targetPtr = target->image + startX + (startY + y + 1) * target->header.width;
    }
}

void TGA::InitializeImage(int width, int height) {
    header.width = width;
    header.height = height;
    imageSize = width * height;
    image = new Pixel[imageSize ];
}

int TGA::getHeight() {
    return header.height;
}

int TGA::getWidth() {
    return header.width;
}

#endif //PROJECT2_TGA_CPP
