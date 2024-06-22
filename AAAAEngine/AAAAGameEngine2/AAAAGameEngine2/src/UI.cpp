#include "UI.h"


UI::UI() = default;

UI::~UI() {
	cleanUp();
}

void UI::cleanUp() {
	if (ImGui::GetCurrentContext() != nullptr) {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
}

UI& UI::GetInstance() {
	static UI instance;
	return instance;
}

void UI::Initialise(GraphicsUtility::Window window) {
	//try catch for imgui initialisation
	try {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	io.Fonts->AddFontDefault();
}

void UI::addFont(const char* name, const char* path, float size) {
	ImGuiIO& io = ImGui::GetIO();
	ImFont* font = io.Fonts->AddFontFromFileTTF(path, size);
	fonts[name] = font;
}

void UI::setStyleColor(ImGuiCol_ color, ImVec4 value) {
	ImGui::StyleColorsDark();
	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[color] = value;
}

void UI::setThemeDark() {
	ImGui::StyleColorsDark();
}

void UI::setThemeLight() {
	ImGui::StyleColorsLight();
}

void UI::setWindowAlpha(float alpha) {
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowRounding = alpha;
}

void UI::setWindowRounding(float rounding) {
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowRounding = rounding;
}

void UI::setWindowBorderSize(float borderSize) {
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowBorderSize = borderSize;
}

void UI::setFrameRounding(float rounding) {
	ImGuiStyle& style = ImGui::GetStyle();
	style.FrameRounding = rounding;
}

void UI::setFrameBorderSize(float borderSize) {
	ImGuiStyle& style = ImGui::GetStyle();
	style.FrameBorderSize = borderSize;
}

void UI::preRender() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void UI::postRender() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UI::drawImage(const std::string &path, int x, int y, int width, int height, float scale) {
	ImGui::SetCursorPos(ImVec2(x, y));
	TextureManager::GetInstance().SetActiveTexture(path);
	unsigned int textureID = TextureManager::GetInstance().GetTexture(path); 
	ImGui::Image((void*)textureID, ImVec2(width, height));
	TextureManager::GetInstance().Unbind(); 
}

void UI::drawWindow(const char* title, int x, int y, int width, int height, std::function<void()> windowContent) {
	ImGui::SetNextWindowPos(ImVec2(x, y));
	ImGui::SetNextWindowSize(ImVec2(width, height));

	// Push font if available
	if (fonts.count("Title") > 0) {
		ImGui::PushFont(fonts["Title"]);
	}

	ImGui::Begin(title, NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);

	// Call the provided function to render the window content
	windowContent();

	ImGui::End(); // Close the window

	// Pop font if one was pushed
	if (fonts.count("Title") > 0) {
		ImGui::PopFont();
	}
}

bool UI::drawButton(const char* label, int x, int y, int width, int height, std::string fontType) {
	ImGui::SetCursorPos(ImVec2(x, y));
	ImGui::PushFont(fonts[fontType]);
	bool buttonPressed = ImGui::Button(label, ImVec2(width, height));
	ImGui::PopFont();
	return buttonPressed;
}


void UI::drawSlider(const char* label, int x, int y, int width, int height, float& value, float min, float max, std::string fontType) {
	ImGui::SetCursorPos(ImVec2(x, y));
	ImGui::PushFont(fonts[fontType]);
	ImGui::SliderFloat(label, &value, min, max);
	ImGui::PopFont();
}

void UI::drawCheckboxes(const std::vector<std::string>& labels, int x, int y, int width, int height, std::vector<bool>& values, std::string fontType) {
	ImGui::PushFont(fonts[fontType]); // Assuming fonts is defined and initialized correctly
	for (size_t i = 0; i < labels.size(); ++i) {
		ImGui::SetCursorPos(ImVec2(x, y + i * height)); // Adjust y position for each checkbox
		bool value = values[i];
		if (ImGui::Checkbox(labels[i].c_str(), &value)) {
			values[i] = value;
		}
	}
	ImGui::PopFont();
}

void UI::drawRadioButtons(const std::vector<std::string>& labels, int x, int y, int width, int height, int& activeIndex, std::string fontType) {
	ImGui::PushFont(fonts[fontType]);
	for (size_t i = 0; i < labels.size(); ++i) {
		ImGui::SetCursorPos(ImVec2(x, y + i * height)); // Adjust y position for each radio button
		ImGui::RadioButton(labels[i].c_str(), &activeIndex, i);
	}
	ImGui::PopFont();
}

void UI::drawInputText(const char* label, int x, int y, int width, int height, char* buffer, int bufferSize, std::string fontType) {
	ImGui::SetCursorPos(ImVec2(x, y));
	ImGui::PushFont(fonts[fontType]);
	ImGui::InputText(label, buffer, bufferSize);
	ImGui::PopFont();
}

void UI::drawComboBox(const char* label, int x, int y, int width, int height, const char* items[], int itemCount, int& currentItem, std::string fontType) {
	ImGui::SetCursorPos(ImVec2(x, y));
	ImGui::PushFont(fonts[fontType]);
	ImGui::Combo(label, &currentItem, items, itemCount);
	ImGui::PopFont();
}

void UI::drawProgressBar(float& progress, int x, int y, int width, int height, std::string fontType) {
	ImGui::SetCursorPos(ImVec2(x, y));
	ImGui::PushFont(fonts[fontType]);
	ImGui::ProgressBar(progress, ImVec2(width, height));
	ImGui::PopFont();
}

void UI::drawListBox(const char* label, int x, int y, int width, int height, const char* items[], int itemCount, int& currentItem, std::string fontType) {
	ImGui::SetCursorPos(ImVec2(x, y));
	ImGui::PushFont(fonts[fontType]);
	ImGui::ListBox(label, &currentItem, items, itemCount);
	ImGui::PopFont();
}

void UI::drawText(const char* text, int x, int y, int size, std::string fontType) {
	ImGui::SetCursorPos(ImVec2(x, y));
	ImGui::PushFont(fonts[fontType]);
	ImGui::Text(text);
	ImGui::PopFont(); 
}
