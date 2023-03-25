#include "Platform.h"

//Default
static const char pathFrame1[] = "data/GamePlatform/Platform(frame1).png";
static const char pathFrame2[] = "data/GamePlatform/Platform(frame2).png";
static const char pathFrame3[] = "data/GamePlatform/Platform(frame3).png";

//Long
static const char pathLong[] = "data/GamePlatform/LongPlatform.png";

//Short
static const char pathShort[] = "data/GamePlatform/ShortPlatform.png";

//ShotPlatform 
static const char pathShotPlatform1[] = "data/GamePlatform/ShotPlatform(frame1).png";
static const char pathShotPlatform2[] = "data/GamePlatform/ShotPlatform(frame2).png";
static const char pathShotPlatform3[] = "data/GamePlatform/ShotPlatform(frame3).png";



Platform::Platform(SDL_Renderer* renderer)
	:x(350), y(750), m_rect({0,0,0,0}),
    platformMode(0), renderer(renderer)
{
	//Default Platform
	m_defaultPlatform[0] = new Sprite{ pathFrame1, renderer };
	m_defaultPlatform[1] = new Sprite{ pathFrame2, renderer };
	m_defaultPlatform[2] = new Sprite{ pathFrame3, renderer };

    // long Platform
    m_longPlatform = std::unique_ptr<Sprite>( new Sprite{ pathLong , renderer});

    // short Platform
    m_shortPlatform =  std::unique_ptr<Sprite>(new Sprite { pathShort, renderer });

    //Shot Platform
    m_ShotPlatform[0] = new Sprite{ pathShotPlatform1, renderer };
    m_ShotPlatform[1] = new Sprite{ pathShotPlatform2, renderer };
    m_ShotPlatform[2] = new Sprite{ pathShotPlatform3, renderer };

	setPosition();
    setRect();
  
}

Platform::~Platform()
{
    //default Platform
    for ( int i = 0;  i < ANIMATION_FRAMES;  i++)
        delete m_defaultPlatform[i];
    
    //Shot Platform
    for (int i = 0; i < ANIMATION_FRAMES-1; ++i)
        delete m_ShotPlatform[i];

}

void Platform::update(int S_width, int S_height)
{
    if (keyLeft and x > this->getWidthP() / 2 )
        x -= speedPlatform;
    
    if (keyRight and x < S_width - getWidthP() / 2)
        x += speedPlatform;
    

    setPosition();
    setRect();
}

void Platform::poolEvent(SDL_Event& e)
{
    switch (e.type)
    {
        //If a key was press
    case SDL_KEYDOWN:
        switch (e.key.keysym.sym)
        {
        case SDLK_LEFT:
            keyLeft = true;
            break;
        case SDLK_RIGHT:
           
            keyRight = true;
            break;
        }
        break;

        //If a key was released
    case SDL_KEYUP:
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_LEFT:
            keyLeft = false;
            break;
        case SDLK_RIGHT:
            keyRight = false;
            break;
        }
    }
    break;
    }
}

void Platform::setMode(int mode)
{
    platformMode = mode;
}

void Platform::setPosition()
{
    switch (platformMode)
    {
    case 0:
        for (int i = 0; i < ANIMATION_FRAMES; i++)
        {
            m_defaultPlatform[i]->setX(x);
            m_defaultPlatform[i]->setY(y);
        }
        break;
    case 1:
        m_longPlatform->setX(x);
        m_longPlatform->setY(y);
        break;
    case 2:
        m_shortPlatform->setX(x);
        m_shortPlatform->setY(y);
        break;
    case 3:
        for (int i = 0; i < ANIMATION_FRAMES; i++)
        {
            m_ShotPlatform[i]->setX(x);
            m_ShotPlatform[i]->setY(y);
        }
        break;
    default:
        break;
    }
}

void Platform::setRect()
{
    switch (platformMode)
    {
    case 0:
        m_rect = { static_cast<int>(m_defaultPlatform[1]->getX() - getWidthP() / 2), static_cast<int>(m_defaultPlatform[1]->getY() - getHeightP() / 2), m_defaultPlatform[1]->getWidth(), m_defaultPlatform[1]->getHeight()};
        break;
    case 1:
        m_rect = { static_cast<int>(m_longPlatform->getX() - getWidthP() / 2), static_cast<int>(m_longPlatform->getY() - getHeightP() / 2),m_longPlatform->getWidth(), m_longPlatform->getHeight() };
        break;
    case 2:
        m_rect = { static_cast<int>(m_shortPlatform->getX() - getWidthP() / 2), static_cast<int>(m_shortPlatform->getY() - getHeightP() / 2),m_shortPlatform->getWidth(), m_shortPlatform->getHeight() };
        break;
    case 3:
        m_rect = { static_cast<int>(m_ShotPlatform[1]->getX() - getWidthP() / 2), static_cast<int>(m_ShotPlatform[1]->getY() - getHeightP() / 2), m_ShotPlatform[1]->getWidth(), m_ShotPlatform[1]->getHeight() };
        break;
    default:
        break;
    }
}

int Platform::getWidthP() const
{
    switch (platformMode)
    {
    case 0:
        return m_defaultPlatform[1]->getWidth();
        break;
    case 1:
        return m_longPlatform->getWidth();
        break;
    case 2:
        return m_shortPlatform->getWidth();
        break;
    case 3:
        return m_ShotPlatform[frame]->getWidth();
        break;
    default:
        break;
    }
    return 0;
}

int Platform::getHeightP() const
{
    switch (platformMode)
    {
    case 0:
        return m_defaultPlatform[1]->getHeight();
        break;
    case 1:
        return m_longPlatform->getHeight();
        break;
    case 2:
        return m_shortPlatform->getHeight();
        break;
    case 3:
        return m_ShotPlatform[frame]->getHeight();
        break;
    default:
        break;
    }
    return 0;
}

void Platform::render()
{
    switch (platformMode)
    {
    case 0:
        m_defaultPlatform[frame]->render_();
        break;
    case 1:
        m_longPlatform->render_();
        break;
    case 2:
        m_shortPlatform->render_();
        break;
    case 3:
        m_ShotPlatform[frame]->render_();
        break;
    default:
        break;
    }

    if (platformMode == 0 or platformMode == 3)
    {
        //Go to next frame
        if (SDL_GetTicks() % 2 == 0)
            ++frame;
        //Cycle animation
        if (frame == 3)
            frame = 0;
    }

   /* SDL_RenderFillRect(renderer, &m_rect);*/
}

bool Platform::check_collision(float x, float y, int width, int height)  const {

    return this->x + getWidth() / 2 > x - width / 2  && this->x - getWidth() / 2 < x + width / 2
        && this->y + getHeight() / 2 >= y - height / 2 && this->y - getHeight() / 2  <= y + height / 2;
}


