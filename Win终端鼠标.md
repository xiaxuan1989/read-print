在 Windows 下，如果你使用控制台程序，可以采用 `ReadConsoleInput()` 函数来获取当前鼠标的位置信息，示例代码如下。

```cpp
#include <windows.h>
#include <iostream>

using namespace std;

int main() {
    char black[] = "                ";     // 为输出填加的尾部空白，用于覆盖输出
    INPUT_RECORD inRec = { 0 };                    // 输入信息结构体，记录输入信息
    DWORD res;
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);       // 获取控制台标准输入句柄
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);     // 获取控制台标准输出句柄

    // 开启控制台窗口鼠标输入
    SetConsoleMode(hInput, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
    while (1) {
        // 获取当前输入信息，采用WaitForSingleObject来防止函数阻塞（异步监听）
        if (WaitForSingleObject(hInput, 0) == WAIT_OBJECT_0)
            ReadConsoleInputA(hInput, &inRec, 1, &res);

        // 将光标移动到左上角，覆盖输出
        COORD zeroPos = { 0,0 };
        SetConsoleCursorPosition(hOutput, zeroPos);

        // 监听事件状态
        switch (inRec.EventType) {
        case KEY_EVENT:
            // 键盘事件
            // dwControlKeyState 会记录键盘控制键状态，例如大小写是否开启等
            // wVirtualKeyCode wVirtualScanCode 是最终键盘按键的可以使用的组合变量
            cout << "KEY_EVENT" << endl;
            cout << "KeyEvent.bKeyDown" << inRec.Event.KeyEvent.bKeyDown << black << endl;
            cout << "KeyEvent.dwControlKeyState" << inRec.Event.KeyEvent.dwControlKeyState << black << endl;
            cout << "KeyEvent.uChar.AsciiChar" << inRec.Event.KeyEvent.uChar.AsciiChar << black << endl;
            cout << "KeyEvent.uChar.UnicodeChar" << inRec.Event.KeyEvent.uChar.UnicodeChar<< black << endl;
            cout << "KeyEvent.wRepeatCount" << inRec.Event.KeyEvent.wRepeatCount << black << endl;
            cout << "KeyEvent.wVirtualKeyCode" << inRec.Event.KeyEvent.wVirtualKeyCode << black << endl;
            cout << "KeyEvent.wVirtualScanCode" << inRec.Event.KeyEvent.wVirtualScanCode << black << endl;

            break;
        case MOUSE_EVENT:
            // 鼠标事件，Pos所显示的为鼠标所在的控制台的行和列
            // dwButtonState是鼠标的按键状态 0为鼠标按键抬起，1为左键单击，你可以具体测试其他按键
            // dwEventFlags会记录鼠标事件，其中2为鼠标双击，你可以具体测试其他事件的状态
            cout << "MOUSE_EVENT" << endl;
            cout << "MouseEvent.dwButtonState" << inRec.Event.MouseEvent.dwButtonState << black << endl;
            cout << "MouseEvent.dwControlKeyState" << inRec.Event.MouseEvent.dwControlKeyState << black << endl;
            cout << "MouseEvent.dwEventFlags" << inRec.Event.MouseEvent.dwEventFlags << black << endl;
            cout << "Mouse Pos x: " << inRec.Event.MouseEvent.dwMousePosition.X << " ,y: " << inRec.Event.MouseEvent.dwMousePosition.Y << black << endl;
            break;
        case WINDOW_BUFFER_SIZE_EVENT:
            cout << "WINDOW_BUFFER_SIZE_EVENT" << endl;
            break;
        case MENU_EVENT:
            cout << "MENU_EVENT" << endl;
            break;
        case FOCUS_EVENT:
            cout << "FOCUS_EVENT" << endl;
            break;
        }
        Sleep(1);
    }

    return 0;
}
```