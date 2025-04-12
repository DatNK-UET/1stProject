#include "SpriteAnimation.h"
#include "TextureManager.h"
#include <iostream>



void SpriteAnimation::Draw(float x, float y, int width, int height, float xScale, float yScale, SDL_RendererFlip flip) {
    // Chỉ vẽ nếu frame hiện tại hợp lệ
    if (m_CurrentFrame >= 0 && m_CurrentFrame < m_FrameCount) {
        TextureManager::GetInstance()->DrawFrame(m_TextureID, x, y, width, height, m_SpriteRow, m_CurrentFrame, m_Flip);
    }
}
void SpriteAnimation::Update(float dt) {
    // Tích lũy thời gian
    m_ElapsedTime += dt * 1000.0f; // Chuyển dt (giây) thành mili-giây

    // Tính frame hiện tại dựa trên thời gian tích lũy
    int newFrame = static_cast<int>(m_ElapsedTime / m_Speed) % m_FrameCount;

    // Chỉ cập nhật frame nếu frame mới khác frame hiện tại
    if (newFrame != m_CurrentFrame) {
        m_CurrentFrame = newFrame;
    }

    // Nếu animation không lặp lại và đã đến frame cuối
    if (!m_Repeat && m_CurrentFrame == m_FrameCount - 1) {
        m_IsEnded = true;
        m_ElapsedTime = (m_FrameCount - 1) * m_Speed; // Giữ ở frame cuối
    }
}

void SpriteAnimation::SetProps(const std::string& textureID, int spriteRow, int frameCount, int speed, SDL_RendererFlip flip) {
    m_Speed = speed;
    m_TextureID = textureID;
    m_SpriteRow = spriteRow;
    m_FrameCount = frameCount;
    m_Flip = flip;
    // Không đặt lại m_ElapsedTime để tiếp tục từ frame hiện tại
    // m_ElapsedTime = 0.0f;
    m_IsEnded = false;
}
