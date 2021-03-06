#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED
#include <cstring>
#include <SFML/Graphics.hpp>
#include "buttonTerritorio.hpp"

/// state of the button
enum BT_STATE
{
    BT_ENABLE,
    BT_HOVER,
    BT_DISABLE
};
/// A generic SFML Button
class Button : public sf::Drawable, public sf::Transformable,public ButtonTerritorio{
public:
    /*!
    * \param textstr button text
    * \param position position (x, y) vector
    * \param height height of the button
    * \param on_press fuction that will be called whe button is pressed
    * \param default_color background button color
    */
    Button() = default;
    void startTerrasBotton(const sf::Vector2f &position, size_t height, void (*on_press2)(int,int),int x,int y, sf::Color default_color);
    
    Button(std::string textstr, const sf::Vector2f &position, size_t height, void (*on_press2)(int,int),int i,int j, sf::Color default_color);
    Button(std::string textstr, const sf::Vector2f &position, size_t height, void (*on_press)(), sf::Color default_color = sf::Color(200, 200, 200));
    /// \return x_axis maximum of the button area
    unsigned int getRightX();
    /*! relative move
    * \param rx x_axis difference of old and new position
    * \param ry y_axis difference of old and new position
    */
    void move(int rx, int ry);
    /// update state
    void update(sf::Event& e);
    void operator=(const Button & b);
    void changeColor(sf::Color default_color);

private:
    /// draw methode of Button. Check the SFML Documentation
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    /// press event
    void press();
    /// hover event
    void hover();
    /// background rectangle
    sf::RectangleShape rect;
    /// poosition vector
    sf::Vector2f position;
    /// size vector
    sf::Vector2f size;
    /// used font
    sf::Font font;
    /// text of the button
    sf::Text text;
    /// on_press action function
    void (*on_press)();
    /// on_press action function2
    void (*on_press2)(int,int);
    /// state of the button
    BT_STATE state;
};
#endif

