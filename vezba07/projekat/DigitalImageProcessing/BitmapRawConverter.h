#ifndef BITMAPRAWCONVERTER_H_
#define BITMAPRAWCONVERTER_H_

#include "EasyBMP.h"

class BitmapRawConverter {
private:
    BMP bitmap;
    int width;
    int height;
    int *pixels;
public:
    void bitmapToPixels();
    void pixelsToBitmap(char *outFilename);

    RGBApixel getPixel(int i, int j);
    void putPixel(int i, int j, RGBApixel value);

    int *getBuffer();
    void setBuffer(int *buffer);

    BitmapRawConverter(int width, int height);
    BitmapRawConverter(char *filename);
    virtual ~BitmapRawConverter();
    int getHeight() const;
    int getWidth() const;
    void setHeight(int height);
    void setWidth(int width);
};

#endif /* BITMAPRAWCONVERTER_H_ */
