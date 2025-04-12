#ifndef CAMERA_H
#define CAMERA_H

#include "Point.h"
#include "Vector2D.h"
#include <SDL.h>
#include "Engine.h"

class Camera {
public:
    static Camera* GetInstance() {
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new Camera();
    }
    void SetTarget(Point* target);          // Thiết lập mục tiêu cho camera
    void Update(float dt);                  // Cập nhật vị trí camera
    Vector2D GetPosition() { return m_Position; } // Lấy vị trí camera
    void SetSceneLimit(Vector2D limit) {    // Thiết lập giới hạn cảnh
        m_SceneWidth = limit.X;
        m_SceneHeight = limit.Y;
    }
    Point* GetTarget() { return m_Target; } // Thêm getter để kiểm tra m_Target

private:
    Camera() : m_Position(0, 0) {           // Constructor mặc định
        m_ViewBox = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        m_SceneWidth = SCREEN_WIDTH * 2;    // Khởi tạo kích thước cảnh
        m_SceneHeight = SCREEN_HEIGHT;
    }
    static Camera* s_Instance;              // Singleton instance
    Point* m_Target = nullptr;              // Thêm khai báo m_Target
    Vector2D m_Position;                    // Vị trí camera
    SDL_Rect m_ViewBox;                     // Hộp nhìn của camera
    int m_SceneWidth, m_SceneHeight;        // Kích thước cảnh
};

#endif
