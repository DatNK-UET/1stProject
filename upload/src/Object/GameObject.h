#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "IObject.h"
#include "Transform.h"
#include "SDL.h"
#include <string>


struct Properties {
public:
    Properties(const std::string textureID, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE)
        : TextureID(textureID), X(x), Y(y), Width(width), Height(height), Flip(flip) {}

    std::string TextureID;
    int Width, Height;
    float X, Y;
    SDL_RendererFlip Flip;
};


class GameObject : public IObject
{
    public:
        GameObject(Properties* props): m_textureID(props->TextureID),
        m_Width (props->Width), m_Height (props->Height), m_Flip (props->Flip) {

        m_transform = new Transform(props->X, props-> Y);
        }


        virtual void Draw()=0;
        virtual void Update (float dt) = 0;
        virtual void Clean () = 0;

    protected:
        Transform* m_transform;
        int m_Width, m_Height;
        std::string m_textureID;
        SDL_RendererFlip m_Flip;
    private:
};

#endif // GAMEOBJECT_H
