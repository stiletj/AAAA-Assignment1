#include "textureGenerator.h"

TextureGenerator::TextureGenerator() {
    for (int i = 0; i < 4; i++)
    {
        tex[i] = nullptr;
    }
    numTextures = 0;
    newTex = nullptr;
    newTexWidth = 0;
    newTexHeight = 0;
    newTexBPP = 3; // 24 bit
}

TextureGenerator::~TextureGenerator() {}

bool TextureGenerator::addTexture(const std::string& filename) {
    if (numTextures < 4) {
        numTextures++;
        tex[numTextures - 1] = new Image(filename);
        if (tex[numTextures - 1]) {
            // Texture loaded successfully
            return true;
        }
        else {
            // Failed to load texture
            numTextures--;
        }
    }
    return false;
}

int TextureGenerator::getNumTextures() {
    return numTextures;
}

bool TextureGenerator::isLoaded(int index) {
    if (index >= 0 && index < numTextures)
        return true;
    return false;
}

ImgRGB<unsigned char> TextureGenerator::getColor(int texNum, int x, int y) {
    if (texNum >= 0 && texNum < numTextures) {
        return tex[texNum]->getPixelColor(x, y);
    }
    return { 0, 0, 0 }; // Return black if texture or coordinates are invalid
}

void TextureGenerator::setColor(int x, int y, ImgRGB<unsigned char> color) {
    if ((x < newTexWidth) && (y < newTexHeight))
    {
        newTex->setPixelColor(x, y, color); 
    }
}

bool TextureGenerator::setupNewTexture(int width, int height) {
   newTexHeight = height;
   newTexWidth = width;
   newTex = new Image(width, height); 
   if (!newTex) {
       return false; 
   }
   return true; 
}

float TextureGenerator::getRange() {
    if (numTextures > 0)
        return 255.0f / static_cast<float>(numTextures);
    return 0.0f;
}

float TextureGenerator::getTextureMax(int texNum) {
    if (texNum > (numTextures - 1)) {
        return 0.0f;
    }else{
        return((255.0 / (float)numTextures) * (texNum + 1));
    }
    return 0.0f; // Return 0 if the texture index is out of range
}

unsigned int TextureGenerator::getTexWidth(int texNo) {
    if (texNo > 0 && texNo < numTextures) {
        return tex[texNo]->getWidth();
    }
    return -1;
}

unsigned int TextureGenerator::getTexHeight(int texNo) {
    if (texNo > 0 && texNo < numTextures) {
        return tex[texNo]->getHeight();
    }
    return -1;
}
