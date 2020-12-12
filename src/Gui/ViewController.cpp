#include "ViewController.h"
#include <iostream>


ViewController::ViewController()
{
    isMousePressed=false;
}

ViewController::ViewController(sf::Vector2f center, sf::Vector2f size, sf::FloatRect viewport) :view(center,size)
{
    isMousePressed=false;
    view.setViewport(viewport);
}

void ViewController::OnUpdate(const sf::Vector2u& windowSize)
{
    view.setSize(windowSize.x * view.getViewport().width, windowSize.y * view.getViewport().height);
}


void ViewController::ProcessEvent(sf::Event& ev)
{
    if(ev.type == sf::Event::MouseButtonPressed && ev.mouseButton.button == sf::Mouse::Right)
    {
        isMousePressed=true;
        initialMousePos=sf::Vector2f(ev.mouseButton.x,ev.mouseButton.y);
    }

    if(ev.type == sf::Event::MouseButtonReleased && ev.mouseButton.button == sf::Mouse::Right)
        isMousePressed=false;

    if(ev.type == sf::Event::KeyPressed)
    {
        switch(ev.key.code)
        {
        case sf::Keyboard::Equal:
            view.zoom(0.75);
        break;
        case sf::Keyboard::Hyphen:
            view.zoom(1.25);
        break;

        case sf::Keyboard::Up:
            view.move(0,-view.getSize().y/20);
            break;
        case sf::Keyboard::Down:
            view.move(0,view.getSize().y/20);
            break;
        case sf::Keyboard::Left:
            view.move(-view.getSize().x/20,0);
            break;
        case sf::Keyboard::Right:
            view.move(view.getSize().x/20,0);
            break;
        default:
            break;
        }
    }
}

void ViewController::SetWindowView(sf::RenderWindow& window)
{
    window.setView(view);

    if(isMousePressed)
    {
        sf::Vector2f difference = sf::Vector2f(sf::Mouse::getPosition(window)) - initialMousePos;
        view.move(difference.x / 10, difference.y/10);
    }

}
