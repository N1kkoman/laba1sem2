#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include "windows.h"


class AnimatedText
{
public:
    AnimatedText(std::string text, float duration)
    {
        m_text = text;
        m_duration = duration;
    }

    std::string getDisplayedText() const
    {
        return m_text.substr(0, currentChar);
    }

    int update() 
    {
        currentChar++;
        return currentChar;
    }

    int getCurrentChar() const
    {
        return currentChar;
    }

    void DrawInConsole()
    {
        for (int i = 0; i < m_text.length(); i++, Sleep(m_duration * 1000 / m_text.length()))
        {
            std::cout << m_text[i];
        }
    }

    int getTextSize() const
    {
        return m_text.length();
    }

    float getDuration() const
    {
        return m_duration;
    }
private:
    std::string m_text;
    float m_duration;
    int currentChar = -1;
};

int main()
{
    AnimatedText animatedText("It was kinda difficult", 5);

    //animatedText.DrawInConsole(); // логика работы (если нужен вывод текста в консоль)

    // отрисовка с помощью графической библиотеки SFML

    sf::RenderWindow window(sf::VideoMode(800, 600), "Animated Text");
    sf::Font font;
    font.loadFromFile("arial.ttf");

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);

    long long delay = animatedText.getDuration() * 1000 / animatedText.getTextSize();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        if (animatedText.getCurrentChar() < animatedText.getTextSize())
        {
            animatedText.update();
            text.setString(animatedText.getDisplayedText());
        }
        window.draw(text);
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
    return 0;
}
