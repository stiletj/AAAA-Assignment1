#pragma once 

#include <iostream>
#include "Image.h"
#include "TextureManager.h" 

/**
 * @brief A class for generating and managing textures.
 */
class TextureGenerator {
private:
    Image* tex[4]; /**< Array of pointers to Image objects, representing textures 0-3 */
    Image* newTex; /**< Pointer to the new texture */
    int newTexWidth; /**< The width of the new texture */
    int newTexHeight; /**< The height of the new texture */
    int newTexBPP; /**< The bits per pixel of the new texture */
    int numTextures; /**< The number of textures */

public:
    /**
     * @brief Constructor for TextureGenerator.
     */
    TextureGenerator();

    /**
     * @brief Destructor for TextureGenerator.
     */
    ~TextureGenerator();

    /**
     * @brief Adds a texture from a file.
     * @param filename The filename of the texture.
     * @return True if the texture is added successfully, false otherwise.
     */
    bool addTexture(const std::string& filename); // Change to use std::string for filename

    /**
     * @brief Gets the number of textures.
     * @return The number of textures.
     */
    int getNumTextures();

    /**
     * @brief Checks if a texture is loaded.
     * @param index The index of the texture.
     * @return True if the texture is loaded, false otherwise.
     */
    bool isLoaded(int index);

    /**
     * @brief Gets the color of a pixel in a texture.
     * @param texNum The index of the texture.
     * @param x The x-coordinate of the pixel.
     * @param y The y-coordinate of the pixel.
     * @return The color of the pixel.
     */
    ImgRGB<unsigned char> getColor(int texNum, int x, int y);

    /**
     * @brief Sets the color of a pixel in the new texture.
     * @param x The x-coordinate of the pixel.
     * @param y The y-coordinate of the pixel.
     * @param color The color to set.
     */
    void setColor(int x, int y, ImgRGB<unsigned char> color);

    /**
     * @brief Gets a reference to the new texture.
     * @return A reference to the new texture.
     */
    Image& getTex() { return *newTex; }

    /**
     * @brief Sets up a new texture with the given width and height.
     * @param width The width of the new texture.
     * @param height The height of the new texture.
     * @return True if the new texture is set up successfully, false otherwise.
     */
    bool setupNewTexture(int width, int height);

    /**
     * @brief Gets the range of the texture values.
     * @return The range of the texture values.
     */
    float getRange();

    /**
     * @brief Gets the maximum texture value for a given texture.
     * @param texNum The index of the texture.
     * @return The maximum texture value.
     */
    float getTextureMax(int texNum);

    /**
     * @brief Gets the width of a texture.
     * @param texNo The index of the texture.
     * @return The width of the texture.
     */
    unsigned int getTexWidth(int texNo);

    /**
     * @brief Gets the height of a texture.
     * @param texNo The index of the texture.
     * @return The height of the texture.
     */
    unsigned int getTexHeight(int texNo);
};
