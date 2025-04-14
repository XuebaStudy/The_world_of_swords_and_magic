#include "SFMLUI.h"
#include <iostream>

SFMLUI::SFMLUI(const std::string& windowTitle, int width, int height)
    : window(sf::VideoMode(width, height), windowTitle) {
    if (!font.loadFromFile("../assets/fonts/Ouroboros.otf")) {
        throw std::runtime_error("Failed to load font");
    }
}

SFMLUI::~SFMLUI() {
    window.close();
}

void SFMLUI::run() {
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void SFMLUI::addButton(const std::string& text, float centerX, float centerY, float height, std::function<void()> callback) {
    // 计算文本的大小
    int textSize = static_cast<int>(height / 2.4f);

    // 创建文本对象以测量文本宽度
    sf::Text tempText(text, font, textSize);
    float textWidth = tempText.getLocalBounds().width;

    // 计算按钮的宽度（文本宽度加上左右填充）
    float buttonWidth = textWidth + 40.0f;  // 两边各留20像素的边距

    // 创建按钮
    sf::RectangleShape button(sf::Vector2f(buttonWidth, height));
    button.setPosition(centerX - buttonWidth / 2.0f, centerY - height / 2.0f);  // 设置按钮位置为中心点
    button.setFillColor(sf::Color(0, 128, 255, 128));
    button.setOutlineColor(sf::Color::Black);
    button.setOutlineThickness(2);

    buttons.push_back(button);
    buttonLabels.push_back(text);
    buttonCallbacks.push_back(callback);

    // 创建按钮文本
    sf::Text buttonText(text, font, textSize);
    sf::FloatRect textRect = buttonText.getLocalBounds();
    buttonText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    buttonText.setPosition(centerX, centerY);
    buttonText.setFillColor(sf::Color::White);
    texts.push_back(buttonText);
}

void SFMLUI::addText(const std::string& text, float centerX, float centerY, float height) {
    // 根据传入的高度自动计算文本大小
    int textSize = static_cast<int>(height / 2.4f);

    // 创建文本对象
    sf::Text t(text, font, textSize);
    t.setFillColor(sf::Color::White);

    // 获取文本的局部边界
    sf::FloatRect textRect = t.getLocalBounds();

    // 设置文本的原点为文本的中心点
    t.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

    // 设置文本的位置为中心点
    t.setPosition(centerX, centerY);

    // 将文本对象存储到列表中
    texts.push_back(t);
}

void SFMLUI::addBackgroundImage(const std::string& filePath) {
    sf::Texture texture;
    if (!texture.loadFromFile(filePath)) {
        throw std::runtime_error("Failed to load background image");
    }
    textures.push_back(texture);

    sf::Sprite sprite(textures.back());
    sprite.setPosition(0, 0);
    sprites.push_back(sprite);
}
void SFMLUI::addSound(const std::string& filePath, std::function<void()> playCallback) {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filePath)) {
        throw std::runtime_error("Failed to load sound file: " + filePath);
    }
    soundBuffers.push_back(buffer);

    sf::Sound sound;
    sound.setBuffer(soundBuffers.back());
    sound.setLoop(true);  // 设置音频为循环播放
    sounds.push_back(sound);

    soundCallbacks.push_back(playCallback);

    // 自动播放音频
    if (playCallback) {
        playCallback();  // 调用回调函数
    }
    sounds.back().play();  // 立即播放音频
}

void SFMLUI::pauseSound(size_t soundIndex) {
    if (soundIndex < sounds.size()) {
        sounds[soundIndex].pause();
    }
}

void SFMLUI::resumeSound(size_t soundIndex) {
    if (soundIndex < sounds.size()) {
        sounds[soundIndex].play();
    }
}

void SFMLUI::stopSound(size_t soundIndex) {
    if (soundIndex < sounds.size()) {
        sounds[soundIndex].stop();
    }
}

void SFMLUI::changeSound(size_t soundIndex, const std::string& newFilePath) {
    if (soundIndex < sounds.size()) {
        sf::SoundBuffer newBuffer;
        if (!newBuffer.loadFromFile(newFilePath)) {
            throw std::runtime_error("Failed to load new sound file: " + newFilePath);
        }
        soundBuffers[soundIndex] = newBuffer;
        sounds[soundIndex].setBuffer(soundBuffers[soundIndex]);
    }
}

void SFMLUI::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        for (size_t i = 0; i < buttons.size(); ++i) {
            if (buttons[i].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) &&
                sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                buttonCallbacks[i]();
            }
        }
    }
}

void SFMLUI::update() {
    // 获取鼠标位置
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    // 动态更新按钮状态
    for (size_t i = 0; i < buttons.size(); ++i) {
        bool isHovered = buttons[i].getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

        if (isHovered) {
            // 鼠标悬停在按钮上
            buttons[i].setFillColor(sf::Color(0, 128, 255, 100));  // 悬停时的颜色
        } else {
            // 鼠标不在按钮上
            buttons[i].setFillColor(sf::Color(0, 0, 255, 100));  // 默认颜色
        }
    }
}

void SFMLUI::render() {
    window.clear(sf::Color::Black);

    // 绘制背景图片
    if (!sprites.empty()) {
        window.draw(sprites[0]);
    }

    for (auto& button : buttons) {
        window.draw(button);
    }

    for (auto& text : texts) {
        window.draw(text);
    }

    window.display();
}