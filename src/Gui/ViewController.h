#ifndef VIEWCONTROLLER_H_INCLUDED
#define VIEWCONTROLLER_H_INCLUDED
#include <SFML/Graphics.hpp>
class ViewController
{
public:
    ViewController();
    ViewController(sf::Vector2f center, sf::Vector2f size, sf::FloatRect viewport);

    void OnUpdate(const sf::Vector2u& windowSize);
    void ProcessEvent(sf::Event& e);
    void SetWindowView(sf::RenderWindow& window);
    void SetPos(int32_t x, int32_t y);
private:

    bool isMousePressed;
    sf::Vector2f initialMousePos;
    sf::View view;
};


#endif // VIEWCONTROLLER_H_INCLUDED
