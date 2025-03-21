#ifndef CHARACTER_H
#define CHARACTER_H

#include "Transform.h"
#include <string>

class Properties {
public:
    std::string TextureID;
    int X, Y, Width, Height;

    Properties(std::string textureID, int x, int y, int width, int height)
        : TextureID(textureID), X(x), Y(y), Width(width), Height(height) {}
};

class Character {
public:
    Character(Properties* props) {
    m_TextureID = props->TextureID;
    m_Width = props->Width;
    m_Height = props->Height;
    m_transform = new Transform();  // Cấp phát động cho con trỏ
    m_transform->setPosition(Vector2D(props->X, props->Y));  // Sử dụng ->
}

    virtual ~Character() {
        delete m_transform;
    }

    virtual void Draw() = 0; // Hàm ảo thuần túy
    virtual void Update(float dt) = 0; // Hàm ảo thuần túy
    virtual void Clean() = 0; // Hàm ảo thuần túy

protected:
    Transform* m_transform;
    int m_Width, m_Height;
    std::string m_TextureID;
};

#endif
