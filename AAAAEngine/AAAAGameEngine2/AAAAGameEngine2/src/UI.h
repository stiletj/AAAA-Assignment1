//imgui
#pragma once

#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"
#include "GraphicsUtility.h"
#include "TextureManager.h"
#include <map>
#include <string>
#include <vector>

/**
 * @class UI
 * @brief A class for creating user interface elements using ImGui.
 */
class UI
{

public:
    /**
     * @brief Constructor.
     */
    UI();

    /**
     * @brief Destructor.
     */
    ~UI();

    /**
     * @brief Initializes the user interface.
     * @param window The GLFW window.
     */
    void Initialise(GraphicsUtility::Window window);

    /**
     * @brief Prepares ImGui for rendering.
     */
    void preRender();

    /**
     * @brief Finishes rendering ImGui elements.
     */
    void postRender();

    /**
     * @brief Cleans up resources used by the UI.
     */
    void cleanUp();

    /**
     * @brief Get the singleton instance of UI.
     * @return Reference to the UI instance.
     */
    static UI& GetInstance();

    /**
     * @brief Draws an image on the screen.
     * @param path The path to the image file.
     * @param x The x-coordinate of the top-left corner of the image.
     * @param y The y-coordinate of the top-left corner of the image.
     * @param width The width of the image.
     * @param height The height of the image.
     * @param scale The scale factor of the image.
     */
    void drawImage(const std::string& path, int x, int y, int width, int height, float scale);

    /**
     * @brief Draws a window with custom content.
     * @param title The title of the window.
     * @param x The x-coordinate of the top-left corner of the window.
     * @param y The y-coordinate of the top-left corner of the window.
     * @param width The width of the window.
     * @param height The height of the window.
     * @param windowContent The function that renders the window content.
     */
    void drawWindow(const char* title, int x, int y, int width, int height, std::function<void()> windowContent);
    /**
     * @brief Draws a button with the specified label.
     * @param label The text label of the button.
     * @param x The x-coordinate of the top-left corner of the button.
     * @param y The y-coordinate of the top-left corner of the button.
     * @param width The width of the button.
     * @param height The height of the button.
     * @param fontType The name of the font to use for the button label.
     * @return True if the button is clicked, false otherwise.
     */
    bool drawButton(const char* label, int x, int y, int width, int height, std::string fontType);

    /**
     * @brief Draws text on the screen.
     * @param text The text to draw.
     * @param x The x-coordinate of the top-left corner of the text.
     * @param y The y-coordinate of the top-left corner of the text.
     * @param size The size of the text.
     * @param fontType The name of the font to use for the text.
     */
    void drawText(const char* text, int x, int y, int size, std::string fontType);

    /**
     * @brief Draws a slider control.
     * @param label The label of the slider.
     * @param x The x-coordinate of the top-left corner of the slider.
     * @param y The y-coordinate of the top-left corner of the slider.
     * @param width The width of the slider.
     * @param height The height of the slider.
     * @param value A reference to the value controlled by the slider.
     * @param min The minimum value of the slider.
     * @param max The maximum value of the slider.
     * @param fontType The name of the font to use for the label.
     */
    void drawSlider(const char* label, int x, int y, int width, int height, float& value, float min, float max, std::string fontType);

    /**
     * @brief Draws a group of checkboxes.
     * @param labels The labels for each checkbox.
     * @param x The x-coordinate of the top-left corner of the checkboxes group.
     * @param y The y-coordinate of the top-left corner of the checkboxes group.
     * @param width The width of the checkboxes group.
     * @param height The height of the checkboxes group.
     * @param values A vector containing the state of each checkbox.
     * @param fontType The name of the font to use for the labels.
     */
    void drawCheckboxes(const std::vector<std::string>& labels, int x, int y, int width, int height, std::vector<bool>& values, std::string fontType);

    /**
     * @brief Draws a group of radio buttons.
     * @param labels The labels for each radio button.
     * @param x The x-coordinate of the top-left corner of the radio buttons group.
     * @param y The y-coordinate of the top-left corner of the radio buttons group.
     * @param width The width of the radio buttons group.
     * @param height The height of the radio buttons group.
     * @param activeIndice The index of the active radio button.
     * @param fontType The name of the font to use for the labels.
     */
    void drawRadioButtons(const std::vector<std::string>& labels, int x, int y, int width, int height, int& activeIndice, std::string fontType);

    /**
     * @brief Draws an input text field.
     * @param label The label of the input text field.
     * @param x The x-coordinate of the top-left corner of the input text field.
     * @param y The y-coordinate of the top-left corner of the input text field.
     * @param width The width of the input text field.
     * @param height The height of the input text field.
     * @param buffer The buffer to store the input text.
     * @param bufferSize The size of the buffer.
     * @param fontType The name of the font to use for the label.
     */
    void drawInputText(const char* label, int x, int y, int width, int height, char* buffer, int bufferSize, std::string fontType);

    /**
     * @brief Draws a combo box.
     * @param label The label of the combo box.
     * @param x The x-coordinate of the top-left corner of the combo box.
     * @param y The y-coordinate of the top-left corner of the combo box.
     * @param width The width of the combo box.
     * @param height The height of the combo box.
     * @param items An array of strings representing the items in the combo box.
     * @param itemCount The number of items in the combo box.
     * @param currentItem The index of the currently selected item.
     * @param fontType The name of the font to use for the label.
     */
    void drawComboBox(const char* label, int x, int y, int width, int height, const char* items[], int itemCount, int& currentItem, std::string fontType);

    /**
     * @brief Draws a progress bar.
     * @param progress A reference to the progress value.
     * @param x The x-coordinate of the top-left corner of the progress bar.
     * @param y The y-coordinate of the top-left corner of the progress bar.
     * @param width The width of the progress bar.
     * @param height The height of the progress bar.
     * @param fontType The name of the font to use for the label.
     */
    void drawProgressBar(float& progress, int x, int y, int width, int height, std::string fontType);

    /**
     * @brief Draws a list box.
     * @param label The label of the list box.
     * @param x The x-coordinate of the top-left corner of the list box.
     * @param y The y-coordinate of the top-left corner of the list box.
     * @param width The width of the list box.
     * @param height The height of the list box.
     * @param items An array of strings representing the items in the list box.
     * @param itemCount The number of items in the list box.
     * @param currentItem The index of the currently selected item.
     * @param fontType The name of the font to use for the label.
     */
    void drawListBox(const char* label, int x, int y, int width, int height, const char* items[], int itemCount, int& currentItem, std::string fontType);

    /**
     * @brief Adds a font to the UI.
     * @param name The name of the font.
     * @param path The path to the font file.
     * @param size The size of the font.
     */
    void addFont(const char* name, const char* path, float size);

    /**
     * @brief Sets the color of a style element.
     * @param color The ImGuiCol_ enum representing the style element.
     * @param value The new color value.
     */
    void setStyleColor(ImGuiCol_ color, ImVec4 value);

    /**
     * @brief Sets the dark theme for the UI.
     */
    void setThemeDark();

    /**
     * @brief Sets the light theme for the UI.
     */
    void setThemeLight();

    /**
     * @brief Sets the transparency level of windows.
     * @param alpha The alpha value (0.0 = fully transparent, 1.0 = fully opaque).
     */
    void setWindowAlpha(float alpha);

    /**
     * @brief Sets the rounding of window corners.
     * @param rounding The rounding value.
     */
    void setWindowRounding(float rounding);

    /**
     * @brief Sets the border size of windows.
     * @param borderSize The border size value.
     */
    void setWindowBorderSize(float borderSize);

    /**
     * @brief Sets the rounding of frame corners.
     * @param rounding The rounding value.
     */
    void setFrameRounding(float rounding);

    /**
     * @brief Sets the border size of frames.
     * @param borderSize The border size value.
     */
    void setFrameBorderSize(float borderSize);

private:
    // Map of fonts
    std::map<std::string, ImFont*> fonts;
};

