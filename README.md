

![ChatGPT Image 10_50_00 27 thg 4, 2025](https://github.com/user-attachments/assets/346ef170-4f64-459c-b7e2-f0b766bda629)


**Arcane Knight** là một trò chơi platformer 2D được xây dựng bằng C++ và SDL2. Người chơi điều khiển một chiến binh di chuyển qua các màn chơi, bắn đạn, né kẻ thù và tìm cánh cửa để hoàn thành màn. Dự án này là tài liệu học tập hữu ích cho những ai muốn tìm hiểu về phát triển game với SDL2, tập trung vào lập trình hướng đối tượng, vật lý và render.



[![Arcane Knight Trailer](https://img.youtube.com/vi/0gxGH9Pu0kI/0.jpg)](https://youtu.be/0gxGH9Pu0kI)


## Mục Lục

- [Tính Năng](#tính-năng)
- [Công Nghệ](#công-nghệ)
- [Cài Đặt](#cài-đặt)
- [Cách Chơi](#cách-chơi)
- [Cơ Chế Game](#cơ-chế-game)
- [Source](#Source)


## Tính Năng

- **Trạng Thái Game**: Menu chính, chọn màn chơi, chơi game, Game Over, Level Complete.
- **Màn Chơi**: Hai màn (map1.tmx, map2.tmx) với cơ chế mở khóa.
- **Nhân Vật**: Di chuyển, nhảy, bắn đạn (thời gian chờ 0.5s).
- **Kẻ Thù**: Tuần tra trong phạm vi, tiêu diệt bằng đạn.
- **Va Chạm**: Xử lý va chạm chính xác cho nhân vật, đạn, kẻ thù, bản đồ.
- **Camera**: Theo dõi nhân vật mượt mà, giới hạn trong bản đồ.
- **Bản Đồ**: Tải file Tiled (.tmx) với hỗ trợ layer và va chạm.
- **Âm Thanh**: Nhạc nền qua SDL2 Mixer.
- **Đồng Hồ**: Theo dõi và hiển thị thời gian chơi.
- **Debug**: Log chi tiết vị trí, va chạm, trạng thái game.
  
 <img width="397" alt="Untitled2" src="https://github.com/user-attachments/assets/94b15175-1b9c-4b0a-9d7a-b00c882cd4f6" />

 

## Công Nghệ




- **C++**: Logic game.
- **SDL2**: Render, input, cửa sổ.
- **SDL2_image**: Tải texture PNG.
- **SDL2_ttf**: Hiển thị văn bản.
- **SDL2_mixer**: Phát nhạc.
- **TinyXML2**: Phân tích file .tmx.
- **Tiled Map Editor**: Thiết kế bản đồ.

 <img width="597" alt="Screenshot 2025-04-27 233705" src="https://github.com/user-attachments/assets/f2645cf6-2359-4a26-b6b3-94fbb67b77ad" />

## Cài Đặt



### Yêu Cầu

- Trình biên dịch C++ (GCC, MSVC, Clang, hỗ trợ C++11+).
- Thư viện: SDL2, SDL2_image, SDL2_ttf, SDL2_mixer, TinyXML2.
- CMake (tùy chọn).
- Tiled Map Editor (tùy chọn, để chỉnh sửa .tmx).

### Hướng Dẫn

1. Tải Repository:

    git clone https://github.com/DatNK-UET/1stProject?tab=readme-ov-file
    cd Arcane-Knight

2. Cài Thư Viện:

- Ubuntu/Debian:

    sudo apt-get update  
    sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev libtinyxml2-dev

- Windows:

    1. Tải SDL2, SDL2_image, SDL2_ttf, SDL2_mixer, TinyXML2 từ trang chính thức.  
    2. Giải nén vào thư mục (ví dụ: C:\\SDL2).  
    3. Cấu hình IDE (Visual Studio, Code::Blocks) để include và link thư viện.

- macOS (Homebrew):

    brew install sdl2 sdl2_image sdl2_ttf sdl2_mixer tinyxml2

3. Build Dự Án:

    mkdir build  
    cd build  
    cmake ..  
    make

4. Chạy Game:

    ./Arcane Knight

## Cách Chơi

- Menu Chính: Nhấn Play để chọn màn, Quit để thoát.  
- Điều Khiển:  
    A / D: Di chuyển trái / phải  
    Space: Nhảy  
    F: Bắn đạn  
- Mục Tiêu: Né kẻ thù, đến cửa xanh để hoàn thành màn.  
- Game Over: Va chạm kẻ thù hoặc rơi khỏi bản đồ. Chọn Retry hoặc Menu.  
- Hoàn Thành: Mở khóa màn tiếp theo, hiển thị Level Complete.

## Cơ Chế Game

### Nhân Vật (Warrior)

- Kích thước: 32×32 px  
- Tốc độ: 200 px/s, nhảy -758.9 px/s  
- Đạn: 8×8 px, tốc độ 800 px/s  

### Kẻ Thù

- Kích thước: 24×24 px  
- Phạm vi tuần tra: 200 px, tốc độ 100 px/s  

### Cửa

- Kích thước: 32×32 px  
- Chạm để hoàn thành màn  

### Bản Đồ

- Tải .tmx, scale 1.5×  
- Ô ID 1–272: Va chạm  
- Ô ID 273–284: Trang trí (coin)  

### Camera

- Theo sau nhân vật bằng lerp 0.2  
- Giới hạn trong bản đồ  

### Vật Lý

- Trọng lực: 1500 px/s² (nhân vật), 1600 px/s² (kẻ thù)  
- Va chạm AABB với bước chia nhỏ  



## Source

- Asset: https://brackeysgames.itch.io/brackeys-platformer-bundle


    


