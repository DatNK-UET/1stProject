#include "Menu.h"
#include "Play.h"
#include "Engine.h"
#include "Input.h"

Menu::Menu() {
    // Constructor có thể để trống nếu không cần khởi tạo gì đặc biệt.
}

bool Menu::Init() {
    m_Ctxt = Engine::GetInstance()->GetRenderer();
    std::cout << "menu initialized!" << std::endl;
    return true;
}

void Menu::Render() {
    SDL_SetRenderDrawColor(m_Ctxt, 16, 45, 70, 255);
    SDL_RenderClear(m_Ctxt);
    SDL_RenderPresent(m_Ctxt);
}

void Menu::Update() {
    // Hiện tại không có logic cập nhật cho menu.
    // Có thể thêm logic xử lý input hoặc animation sau này.
}

bool Menu::Exit() {
    std::cout << "exit menu!" << std::endl;
    return true;
}

// Callbacks
void Menu::StartGame() {
    std::cout << "start game!\n";
    // Có thể thêm logic để chuyển sang trạng thái Play, ví dụ:
    // Engine::GetInstance()->ChangeState(new Play());
}

void Menu::Editor() {
    std::cout << "editor mode\n";
}

void Menu::Settings() {
    std::cout << "options mode\n";
}

void Menu::Quit() {
    std::cout << "quit game\n";
    // Có thể thêm logic để thoát game, ví dụ:
    // Engine::GetInstance()->Quit();
}
