#ifndef LAYER_H
#define LAYER_H

class Layer {
public:
    virtual void Render(float offsetX = 0, float offsetY = 0) = 0; // Thêm tham số với giá trị mặc định
    virtual void Update() = 0;
    virtual ~Layer() {}
};

#endif
