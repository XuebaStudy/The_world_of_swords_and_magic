#ifndef SFMLUI_H
#define SFMLUI_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <functional>
#include <vector>

class SFMLUI {
public:
    SFMLUI(const std::string& windowTitle, int width, int height);
    ~SFMLUI();

    void run();

    void addButton(const std::string& text, float centerX, float centerY, float height, std::function<void()> callback=[](){});
    void addText(const std::string& text, float centerX, float centerY, float height);
    void addBackgroundImage(const std::string& filePath);
    void addSound(const std::string& filePath, std::function<void()> playCallback=[](){});  // 添加音频功能
    void pauseSound(size_t soundIndex);  // 暂停音频
    void resumeSound(size_t soundIndex);  // 恢复音频
    void stopSound(size_t soundIndex);  // 停止音频
    void changeSound(size_t soundIndex, const std::string& newFilePath);  // 更换音频文件

public:
    sf::RenderWindow window;
    std::vector<sf::RectangleShape> buttons;
    std::vector<std::string> buttonLabels;
    std::vector<std::function<void()>> buttonCallbacks;
    sf::Font font;
    std::vector<sf::Text> texts;
    std::vector<sf::Texture> textures;
    std::vector<sf::Sprite> sprites;

    std::vector<sf::SoundBuffer> soundBuffers;  // 存储音频缓冲区
    std::vector<sf::Sound> sounds;             // 存储音频对象
    std::vector<std::function<void()>> soundCallbacks;  // 存储音频播放回调

    void handleEvents();
    void update();
    void render();
};

#endif