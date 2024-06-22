#include "Image.h"

Image::Image(const std::string& path) : m_Width(0), m_Height(0), m_BPP(0), m_LocalBuffer(nullptr) {
    stbi_set_flip_vertically_on_load(0);
    m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 0);
    if (!m_LocalBuffer) {
        std::cout << "Error: Failed to load image " << path << std::endl;
        std::cout << stbi_failure_reason() << std::endl;
        exit(EXIT_FAILURE);
    }
}

Image::Image(int width, int height) : m_Width(width), m_Height(height), m_BPP(3) {
    m_LocalBuffer = new unsigned char[m_Width * m_Height * m_BPP];
}

Image::Image() : m_Width(0), m_Height(0), m_BPP(0), m_LocalBuffer(nullptr) {}

Image::~Image()
{
    if (m_LocalBuffer)
        stbi_image_free(m_LocalBuffer);
}

ImgRGB<unsigned char> Image::getPixelColor(int x, int y) const {
    ImgRGB<unsigned char> color{};
    if (m_LocalBuffer && x >= 0 && x < m_Width && y >= 0 && y < m_Height) {
        int index = (y * m_Width + x) * m_BPP;
        color.r = m_LocalBuffer[index];
        color.g = m_LocalBuffer[index + 1];
        color.b = m_LocalBuffer[index + 2];
    }
    return color;
}

void Image::setPixelColor(int x, int y, const ImgRGB<unsigned char> color) {
    if (m_LocalBuffer && x >= 0 && x < m_Width && y >= 0 && y < m_Height) {
        int index = (y * m_Width + x) * m_BPP;
        m_LocalBuffer[index] = color.r;
        m_LocalBuffer[index + 1] = color.g;
        m_LocalBuffer[index + 2] = color.b;
    }
}