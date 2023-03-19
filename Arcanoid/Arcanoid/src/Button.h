#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Text.h"
#include <iostream>
#include <string>
#include "Sprite.h"

class Button {
public:
   
    Button(SDL_Renderer* renderer, int x, int y, const char path[]);
    ~Button();

    void handleEvent(const SDL_Event& event, float mouseX, float mouseY);

    void draw();

    bool isMouseOver(float mouseX, float mouseY) const;
    bool isPressed() const;

    void setPosition(int x, int y);

    int getWidth() const { return m_rect.w; }
    int getHeight() const { return m_rect.h; }

    void setTextColor(SDL_Color textColor);
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void setSize(int size);
    void setText(std::string text);

    void setRectColor(SDL_Color rectColor);
    void setHovered(bool hovered);

private:
    SDL_Renderer* m_renderer;

    TTF_Font* m_font;
    std::string m_text;

    SDL_Rect m_rect;
    SDL_Rect m_rect_bottom;

    SDL_Color m_textColor;
    SDL_Color m_rectColor;


    std::unique_ptr<Text> text_b;
    std::unique_ptr<Sprite> sprite_b;

    bool m_hovered = false;
    SDL_Color m_hoveredRectColor;
    bool m_isPressed;

    bool active = false;
};


