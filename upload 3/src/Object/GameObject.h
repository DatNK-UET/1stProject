#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "IObject.h"
#include "Transform.h"
#include "SDL.h"
#include <string>
#include "Point.h"

struct Properties {
public:
    Properties(const std::string textureID, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE)
        : TextureID(textureID), Width(width), Height(height), X(x), Y(y), Flip(flip) {}

    std::string TextureID;
    int Width, Height;
    float X, Y;
    SDL_RendererFlip Flip;
};

class GameObject : public IObject {
public:
    GameObject(Properties* props) : m_Width(props->Width),
                                    m_Height(props->Height),
                                    m_TextureID(props->TextureID),
                                    m_Flip(props->Flip) {
        m_Transform = new Transform();
        m_Transform->setPosition(Vector2D(props->X, props->Y));
        float px = props->X + props->Width / 2;
        float py = props->Y + props->Height / 2;
        m_Origin = new Point(px, py);
    }

    virtual ~GameObject() {
        delete m_Transform;
        delete m_Origin;
    }

    inline Point* GetOrigin() { return m_Origin; }
    virtual void Draw() = 0;
    virtual void Update(float dt) = 0;
    virtual void Clean() = 0;

protected:
    Point* m_Origin;
    Transform* m_Transform;
    int m_Width, m_Height;
    std::string m_TextureID;
    SDL_RendererFlip m_Flip;
};

#endif
