#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H
#include <unordered_map>

enum class MouseButton
{
    Left,
    Right,
    Middle
};
enum class Key
{
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    Left,
    Right,
    Up,
    Down,
    Space,
    Comma,
    Period,
    Escape,
};

class InputManager
{
    
    private:
        InputManager() {};
        std::unordered_map<Key, bool> m_keyMap;
        std::unordered_map<MouseButton, bool> m_mouseButtonMap;
        double m_mouseX;
        double m_mouseY;   
        double m_lastMouseX;
        double m_lastMouseY;
        bool m_firstMouseMovement = true;        
    public:
        
        static InputManager& GetInstance() {
            static InputManager instance;
            return instance; 
        }

        bool IsKeyDown(Key key) { return m_keyMap[key]; }
        bool ConsumeKeyDown(Key key) { if (m_keyMap[key]) { m_keyMap[key] = false; return true; } return false; }
        bool IsMouseButtonDown(MouseButton button) { return m_mouseButtonMap[button]; }

        double GetMouseX() { return m_mouseX; }
        double GetMouseY() { return m_mouseY; }
        double GetMouseDeltaX() { return m_mouseX - m_lastMouseX; }
        double GetMouseDeltaY() { return m_mouseY - m_lastMouseY; }

        void CursorPositionCallback(double xpos, double ypos) {
            if (m_firstMouseMovement) {
                m_lastMouseX = m_mouseX;
                m_lastMouseY = m_mouseY;
                m_firstMouseMovement = false;
            } else {
                m_lastMouseX = xpos;
                m_lastMouseY = ypos;
            }

            m_mouseX = xpos;
            m_mouseY = ypos;
        }
        
        void KeyCallback(int key, int scancode, int action, int mods) {
            if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
                m_keyMap[Key::Escape] = true;
            if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) 
                m_keyMap[Key::Space] = true;
            if (key == GLFW_KEY_A && action == GLFW_PRESS) 
                m_keyMap[Key::A] = true;
            if (key == GLFW_KEY_B && action == GLFW_PRESS)
                m_keyMap[Key::B] = true;
            if (key == GLFW_KEY_C && action == GLFW_PRESS)
                m_keyMap[Key::C] = true;
            if (key == GLFW_KEY_D && action == GLFW_PRESS)
                m_keyMap[Key::D] = true;
            if (key == GLFW_KEY_E && action == GLFW_PRESS)
                m_keyMap[Key::E] = true;
            if (key == GLFW_KEY_F && action == GLFW_PRESS)
                m_keyMap[Key::F] = true;
            if (key == GLFW_KEY_G && action == GLFW_PRESS)
                m_keyMap[Key::G] = true;
            if (key == GLFW_KEY_H && action == GLFW_PRESS)
                m_keyMap[Key::H] = true;
            if (key == GLFW_KEY_I && action == GLFW_PRESS)
                m_keyMap[Key::I] = true;
            if (key == GLFW_KEY_J && action == GLFW_PRESS)
                m_keyMap[Key::J] = true;
            if (key == GLFW_KEY_K && action == GLFW_PRESS)
                m_keyMap[Key::K] = true;
            if (key == GLFW_KEY_L && action == GLFW_PRESS)
                m_keyMap[Key::L] = true;
            if (key == GLFW_KEY_M && action == GLFW_PRESS)
                m_keyMap[Key::M] = true;
            if (key == GLFW_KEY_N && action == GLFW_PRESS)
                m_keyMap[Key::N] = true;
            if (key == GLFW_KEY_O && action == GLFW_PRESS)
                m_keyMap[Key::O] = true;
            if (key == GLFW_KEY_P && action == GLFW_PRESS)
                m_keyMap[Key::P] = true;
            if (key == GLFW_KEY_Q && action == GLFW_PRESS)
                m_keyMap[Key::Q] = true;
            if (key == GLFW_KEY_R && action == GLFW_PRESS)
                m_keyMap[Key::R] = true;
            if (key == GLFW_KEY_S && action == GLFW_PRESS)
                m_keyMap[Key::S] = true;
            if (key == GLFW_KEY_T && action == GLFW_PRESS)
                m_keyMap[Key::T] = true;
            if (key == GLFW_KEY_U && action == GLFW_PRESS)
                m_keyMap[Key::U] = true;
            if (key == GLFW_KEY_V && action == GLFW_PRESS)
                m_keyMap[Key::V] = true;
            if (key == GLFW_KEY_W && action == GLFW_PRESS)
                m_keyMap[Key::W] = true;
            if (key == GLFW_KEY_X && action == GLFW_PRESS)
                m_keyMap[Key::X] = true;
            if (key == GLFW_KEY_Y && action == GLFW_PRESS)
                m_keyMap[Key::Y] = true;
            if (key == GLFW_KEY_Z && action == GLFW_PRESS)
                m_keyMap[Key::Z] = true;
            if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
                m_keyMap[Key::Left] = true;
            if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
                m_keyMap[Key::Right] = true;
            if (key == GLFW_KEY_UP && action == GLFW_PRESS)
                m_keyMap[Key::Up] = true;
            if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
                m_keyMap[Key::Down] = true;
            if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
                m_keyMap[Key::Comma] = true;
            if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
                m_keyMap[Key::Period] = true;

            // Release
            if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE) 
                m_keyMap[Key::Escape] = false;
            if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE) 
                m_keyMap[Key::Space] = false;
            if (key == GLFW_KEY_A && action == GLFW_RELEASE) 
                m_keyMap[Key::A] = false;
            if (key == GLFW_KEY_B && action == GLFW_RELEASE)
                m_keyMap[Key::B] = false;
            if (key == GLFW_KEY_C && action == GLFW_RELEASE)
                m_keyMap[Key::C] = false;
            if (key == GLFW_KEY_D && action == GLFW_RELEASE)
                m_keyMap[Key::D] = false;
            if (key == GLFW_KEY_E && action == GLFW_RELEASE)
                m_keyMap[Key::E] = false;
            if (key == GLFW_KEY_F && action == GLFW_RELEASE)
                m_keyMap[Key::F] = false;
            if (key == GLFW_KEY_G && action == GLFW_RELEASE)
                m_keyMap[Key::G] = false;
            if (key == GLFW_KEY_H && action == GLFW_RELEASE)
                m_keyMap[Key::H] = false;
            if (key == GLFW_KEY_I && action == GLFW_RELEASE)
                m_keyMap[Key::I] = false;
            if (key == GLFW_KEY_J && action == GLFW_RELEASE)
                m_keyMap[Key::J] = false;
            if (key == GLFW_KEY_K && action == GLFW_RELEASE)
                m_keyMap[Key::K] = false;
            if (key == GLFW_KEY_L && action == GLFW_RELEASE)
                m_keyMap[Key::L] = false;
            if (key == GLFW_KEY_M && action == GLFW_RELEASE)
                m_keyMap[Key::M] = false;
            if (key == GLFW_KEY_N && action == GLFW_RELEASE)
                m_keyMap[Key::N] = false;
            if (key == GLFW_KEY_O && action == GLFW_RELEASE)
                m_keyMap[Key::O] = false;
            if (key == GLFW_KEY_P && action == GLFW_RELEASE)
                m_keyMap[Key::P] = false;
            if (key == GLFW_KEY_Q && action == GLFW_RELEASE)
                m_keyMap[Key::Q] = false;
            if (key == GLFW_KEY_R && action == GLFW_RELEASE)
                m_keyMap[Key::R] = false;
            if (key == GLFW_KEY_S && action == GLFW_RELEASE)
                m_keyMap[Key::S] = false;
            if (key == GLFW_KEY_T && action == GLFW_RELEASE)
                m_keyMap[Key::T] = false;
            if (key == GLFW_KEY_U && action == GLFW_RELEASE)
                m_keyMap[Key::U] = false;
            if (key == GLFW_KEY_V && action == GLFW_RELEASE)
                m_keyMap[Key::V] = false;
            if (key == GLFW_KEY_W && action == GLFW_RELEASE)
                m_keyMap[Key::W] = false;
            if (key == GLFW_KEY_X && action == GLFW_RELEASE)
                m_keyMap[Key::X] = false;
            if (key == GLFW_KEY_Y && action == GLFW_RELEASE)
                m_keyMap[Key::Y] = false;
            if (key == GLFW_KEY_Z && action == GLFW_RELEASE)
                m_keyMap[Key::Z] = false;
            if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE)
                m_keyMap[Key::Left] = false;
            if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE)
                m_keyMap[Key::Right] = false;
            if (key == GLFW_KEY_UP && action == GLFW_RELEASE)
                m_keyMap[Key::Up] = false;
            if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE)
                m_keyMap[Key::Down] = false;
            if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
                m_keyMap[Key::Comma] = false;
            if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
                m_keyMap[Key::Period] = false;
            
        }
};
#endif // INPUT_MANAGER_H