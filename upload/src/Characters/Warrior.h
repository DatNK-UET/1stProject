#ifndef WARRIOR_H
#define WARRIOR_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"

class Warrior : public Character {
public:
    Warrior(Properties* props);
    ~Warrior();

    void Draw() override;
    void Update(float dt) override;
    void Clean() override;

    RigidBody* GetRigidBody() { return m_RigidBody; }

private:
    Animation* m_Animation;
    RigidBody* m_RigidBody;
};

#endif
