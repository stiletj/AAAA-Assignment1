#pragma once

#include "vendor/stb_image/stb_image.h"
#include <string>
#include <iostream>
#include <fstream>

/**
 * @struct ImgRGB
 * @brief Structure representing a color in RGB format.
 * @tparam T Type of color components.
 */
template <class T>
struct ImgRGB
{
    T r; /**< Red component of the color. */
    T g; /**< Green component of the color. */
    T b; /**< Blue component of the color. */

    /**
     * @brief Sets the color components to the values of another RGB color.
     * @param rgb Another RGB color.
     */
    void set(ImgRGB<T> rgb) { r = rgb.r; g = rgb.g; b = rgb.b; }

    /**
     * @brief Resets the color components to zero.
     */
    void reset() { r = 0; g = 0; b = 0; }
};

class Image {
private:
    int m_Width; /**< Width of the image in pixels. */
    int m_Height; /**< Height of the image in pixels. */
    int m_BPP; /**< Bytes per pixel of the image. */
    unsigned char* m_LocalBuffer; /**< Pointer to the image data buffer. */

public:
    /**
     * @brief Constructs an Image object from the specified file path.
     * @param path The path to the image file.
     */
    Image(const std::string& path);

    /**
     * @brief Constructs an Image object from the width and height
     * @param width The width of the image
     * @param height The height of the image
     */
    Image(int width, int height);

    /*
    * @brief Default Constructor 
    * Sets member variables to 0/nullptr 
    */
    Image();

    /**
     * @brief Destroys the Image object and frees the allocated memory.
     */
    ~Image();

    /**
     * @brief Retrieves the width of the image.
     * @return The width of the image in pixels.
     */
    unsigned int getWidth() const { return m_Width; }

    /**
     * @brief Retrieves the height of the image.
     * @return The height of the image in pixels.
     */
    unsigned int getHeight() const { return m_Height; }

    /**
     * @brief Retrieves the pointer to the image data buffer.
     * @return Pointer to the image data buffer.
     */
    unsigned char* getBuffer() const { return m_LocalBuffer; }

    /**
     * @brief Retrieves the bytes per pixel of the image.
     * @return The bytes per pixel of the image.
     */
    unsigned int getBPP() const { return m_BPP; }

    /**
     * @brief Retrieves the color of the pixel at the specified position.
     * @param x The x-coordinate of the pixel.
     * @param y The y-coordinate of the pixel.
     * @return The color of the pixel.
     */
    ImgRGB<unsigned char> getPixelColor(int x, int y) const;

    /**
     * @brief Sets the color of the pixel at the specified position.
     * @param x The x-coordinate of the pixel.
     * @param y The y-coordinate of the pixel.
     * @param color The color to set.
     */
    void setPixelColor(int x, int y, const ImgRGB<unsigned char> color);
};

