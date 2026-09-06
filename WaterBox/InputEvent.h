#pragma once

#include <variant>
#include <cstdint>

namespace in
{

    // Побитовая маска для клавиш-модификаторов (Ctrl, Shift, Alt)
    enum class KeyModifiers : uint8_t {
        None = 0,
        Shift = 1 << 0,
        Ctrl = 1 << 1,
        Alt = 1 << 2
    };

    inline KeyModifiers operator|(KeyModifiers a, KeyModifiers b) {
        return static_cast<KeyModifiers>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
    }
    inline bool operator&(KeyModifiers a, KeyModifiers b) {
        return static_cast<uint8_t>(a) & static_cast<uint8_t>(b);
    }

    enum class MouseButton : uint8_t {
        None, Left, Right, Middle, XButton1, XButton2
    };

    enum class InputAction : uint8_t {
        Release = 0,
        Press = 1,
        Repeat = 2 // Для удержания клавиш клавиатуры
    };

  

    struct MouseMoveEvent {};

    struct MouseButtonEvent {    
        MouseButton button;  
        InputAction action;    
    };

    struct MouseScrollEvent {    
        float deltaX;           
        float deltaY;  
        int FullX;
        int FullY;       
    };


    struct KeyEvent {
        uint32_t keyCode;       // Скан-код клавиши (для физических кнопок вроде стрелочек, F1-F12, Escape)
        char character;         // ASCII/UTF-8 чар (если нажата текстовая кнопка, иначе 0)
        InputAction action;    
    };

  
    struct TextInputEvent {
        char32_t codepoint;
    };


    struct InputEvent {

        std::variant<
            MouseMoveEvent,
            MouseButtonEvent,
            MouseScrollEvent,
            KeyEvent,
            TextInputEvent
        > data;

        KeyModifiers modifiers;
        int x, y;
   
        bool isMouseMove() const { return data.index() == 0; }
        bool isMouseButton() const { return data.index() == 1; }
        bool isMouseScroll() const { return data.index() == 2; }
        bool isKey() const { return data.index() == 3; }
        bool isTextInput() const { return data.index() == 4; }
    };
}




/*          USE


создает перегруженный функтор из лямбд
template<class... Ts> struct overloaded : Ts... { use Ts::operator()...; };

void ProcessInput(const InputEvent& event) {
    std::visit(overloaded {
        [](const MouseMoveEvent& e) {
            std::cout << "Мышь двинулась: " << e.x << ", " << e.y;
            if (e.modifiers & KeyModifiers::Ctrl) std::cout << " (с зажатым Ctrl)";
            std::cout << "\n";
        },
        [](const MouseButtonEvent& e) {
            if (e.action == InputAction::Press) {
                std::cout << "Кликнули кнопкой " << (int)e.button << " в точкe " << e.x << "," << e.y << "\n";
            }
        },
        [](const MouseScrollEvent& e) {
            std::cout << "Скролл! По вертикали: " << e.deltaY << ", По горизонтали: " << e.deltaX << "\n";
        },
        [](const KeyEvent& e) {
            std::cout << "Клавиатура: код " << e.keyCode << ", символ '" << e.character << "'\n";
        },
        [](const TextInputEvent& e) {
            // Для чатов и ввода текста
        }
    }, event.data);
}


*/