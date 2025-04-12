#include "Camera.h"
#include <iostream>

Camera* Camera::s_Instance = nullptr;

void Camera::SetTarget(Point* target) {
    // Thêm log để kiểm tra giá trị target được truyền vào
    if (target == nullptr) {
        std::cout << "Error: SetTarget received nullptr!" << std::endl;
    } else {
        std::cout << "SetTarget called with address: " << target
                  << ", Position: (" << target->X << ", " << target->Y << ")" << std::endl;
    }
    m_Target = target; // Gán target cho camera
}

void Camera::Update(float dt) {
    // Kiểm tra và log nếu m_Target là nullptr
    if (m_Target == nullptr) {
        std::cout << "Camera target is nullptr!" << std::endl;
        return;
    }
    // Log thông tin vị trí của m_Target
    std::cout << "Target address: " << m_Target
              << ", Position: (" << m_Target->X << ", " << m_Target->Y << ")" << std::endl;

    // Tính toán vị trí hộp nhìn dựa trên m_Target
    m_ViewBox.x = m_Target->X - SCREEN_WIDTH / 2;
    m_ViewBox.y = m_Target->Y - SCREEN_HEIGHT / 2;

    // Log vị trí hộp nhìn trước khi áp dụng giới hạn
    std::cout << "ViewBox before limits: (" << m_ViewBox.x << ", " << m_ViewBox.y << ")" << std::endl;
    std::cout << "Scene size: (" << m_SceneWidth << ", " << m_SceneHeight << ")" << std::endl;

    // Áp dụng giới hạn cho hộp nhìn
    if (m_ViewBox.x < 0) m_ViewBox.x = 0;
    else if (m_ViewBox.x + m_ViewBox.w > m_SceneWidth) m_ViewBox.x = m_SceneWidth - m_ViewBox.w;

    if (m_ViewBox.y < 0) m_ViewBox.y = 0;
    else if (m_ViewBox.y + m_ViewBox.h > m_SceneHeight) m_ViewBox.y = m_SceneHeight - m_ViewBox.h;

    // Cập nhật vị trí camera và log
    m_Position = Vector2D(m_ViewBox.x, m_ViewBox.y);
    std::cout << "Camera position: (" << m_Position.X << ", " << m_Position.Y << ")" << std::endl;
}
