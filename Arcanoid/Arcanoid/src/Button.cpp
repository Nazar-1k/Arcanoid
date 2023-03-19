#include "Button.h"

Button::Button(SDL_Renderer* renderer, int x, int y, const char path[])
{
    sprite_b = std::unique_ptr<Sprite>(new Sprite{ path , renderer });
    sprite_b->setX(static_cast<float>(x));
    sprite_b->setY(static_cast<float>(y));
    m_rect = { static_cast<int>(sprite_b->getX()), static_cast<int>(sprite_b->getY()), sprite_b->getWidth(),  sprite_b->getHeight() };

    m_rect.x -= m_rect.w / 2;
    m_rect.y -= m_rect.h / 2;

    sprite_b->setX(static_cast<float>(m_rect.x));
    sprite_b->setY(static_cast<float>(m_rect.y));

}

Button::~Button()
{
    TTF_CloseFont(m_font);
}

void Button::draw()
{
    sprite_b->setY(static_cast<float>(m_rect.y));
    sprite_b->setX(static_cast<float>(m_rect.x));

    if (m_hovered)
    {
        sprite_b->setAlpha(200);
    }
    else
    {
        sprite_b->setAlpha(255);
    }
    sprite_b->render();
}

void Button::setPosition(int x, int y)
{
    m_rect.x = x - m_rect.w / 2;
    m_rect.y = y - m_rect.h / 2;
}

bool Button::isMouseOver(float mouseX, float mouseY) const
{
    return (mouseX >= m_rect.x && mouseX <= m_rect.x + m_rect.w &&
        mouseY >= m_rect.y && mouseY <= m_rect.y + m_rect.h);
}

bool Button::isPressed() const
{
    return m_isPressed;
}

void Button::handleEvent(const SDL_Event& event, float mouseX, float mouseY)
{
    switch (event.type)
    {
    case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT)
            if (isMouseOver(mouseX, mouseY))
                m_isPressed = true;
        break;

    case SDL_MOUSEBUTTONUP:
        if (event.button.button == SDL_BUTTON_LEFT)
            m_isPressed = false;
        break;
    case SDL_MOUSEMOTION:
    {
        // Check if the mouse is over the button and set its hovered state accordingly
        if (isMouseOver(mouseX, mouseY))
            m_hovered = true;
        else
            m_hovered = false;
    }
    }
}

void Button::setTextColor(SDL_Color textColor)
{
    m_textColor = textColor;
}

void Button::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
    sprite_b->setColor(red, green, blue);
}

void Button::setSize(int size)
{
    sprite_b->setSize(size, size);
}

void Button::setText(std::string text)
{
    m_text = text;
}

void Button::setRectColor(SDL_Color rectColor)
{
    m_rectColor = rectColor;
}

void Button::setHovered(bool hovered)
{
    m_hovered = hovered;
}