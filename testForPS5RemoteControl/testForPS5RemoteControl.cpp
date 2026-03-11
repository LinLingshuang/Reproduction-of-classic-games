#include < Windows.h>
#include "ds5w.h"
#include <iostream>

void checkButton(uint8_t curr, uint8_t prev, uint8_t mask, const char* name) {
    bool now = (curr & mask) != 0;
    bool was = (prev & mask) != 0;
    if (now != was) {
        std::cout << name << ": " << (now ? "PRESSED" : "RELEASED") << std::endl;
    }
}

int main(int argc, char** argv) {
	DS5W::DeviceEnumInfo infos[16];
	unsigned int controllersCount = 0;

	switch (DS5W::enumDevices(infos, 16, &controllersCount)) {
	case DS5W_OK:
		// The buffer was not big enough . Ignore for now
	case DS5W_E_INSUFFICIENT_BUFFER:
		break;
		// Any other error will terminate the application
	default:
		// Insert your error handling
		return -1;
	}

	if (!controllersCount) {
		return -1;
	}

	// Context f o r c o n t r o l l e r
	DS5W::DeviceContext con;

	// I n i t c o n t r o l l e r and c l o s e a p p l i c a t i o n i s f a i l e d
	if (DS5W_FAILED(DS5W::initDeviceContext(&infos[0], &con))) {
		return -1;
	}

    DS5W::DS5InputState prevState = {};   // 保存上一帧状态，用于检测变化

	// Main loop
	while (true) {
		// . . .
		DS5W::DS5InputState inState;

		// Re t r i eve data
		if (DS5W_SUCCESS(DS5W::getDeviceInputState(&con, &inState))) {
			// Check f o r the Logo button
			if (inState.buttonsB & DS5W_ISTATE_BTN_B_PLAYSTATION_LOGO) {
				// Break from whi l e loop
				break;

			}
			DS5W::DS5OutputState outState;
			ZeroMemory(&outState, sizeof(DS5W::DS5OutputState));

			// Set output data
			outState.leftRumble = inState.leftTrigger;
			outState.rightRumble = inState.rightTrigger;

			// Send output to the c o n t r o l l e r
			DS5W::setDeviceOutputState(&con, &outState);


           
                // ----- 检测按键状态变化（buttons1 区域）-----
                // 根据 ds5w.h 中定义的掩码名称修改下面的常量
                checkButton(inState.buttonsAndDpad, prevState.buttonsAndDpad, DS5W_ISTATE_BTX_CROSS, "Cross (×)");
                checkButton(inState.buttonsAndDpad, prevState.buttonsAndDpad, DS5W_ISTATE_BTX_CIRCLE, "Circle (○)");
                checkButton(inState.buttonsAndDpad, prevState.buttonsAndDpad, DS5W_ISTATE_BTX_SQUARE, "Square (□)");
                checkButton(inState.buttonsAndDpad, prevState.buttonsAndDpad, DS5W_ISTATE_BTX_TRIANGLE, "Triangle (△)");
                checkButton(inState.buttonsA, prevState.buttonsA, DS5W_ISTATE_BTN_A_LEFT_BUMPER, "L1");
                checkButton(inState.buttonsA, prevState.buttonsA, DS5W_ISTATE_BTN_A_RIGHT_BUMPER, "R1");
                //checkButton(inState.buttonsA, prevState.buttonsA, DS5W_ISTATE_BTN_1_L3, "L3 (左摇杆按下)");
                //checkButton(inState.buttonsA, prevState.buttonsA, DS5W_ISTATE_BTN_1_R3, "R3 (右摇杆按下)");
                //checkButton(inState.buttonsA, prevState.buttonsA, DS5W_ISTATE_BTN_1_OPTIONS, "Options");
                //checkButton(inState.buttonsA, prevState.buttonsA, DS5W_ISTATE_BTN_1_SHARE, "Share");
                //checkButton(inState.buttonsA, prevState.buttonsA, DS5W_ISTATE_BTN_1_PS, "PS");
                checkButton(inState.buttonsAndDpad, prevState.buttonsAndDpad, DS5W_ISTATE_DPAD_UP, "D-Pad Up");
                checkButton(inState.buttonsAndDpad, prevState.buttonsAndDpad, DS5W_ISTATE_DPAD_DOWN, "D-Pad Down");
                checkButton(inState.buttonsAndDpad, prevState.buttonsAndDpad, DS5W_ISTATE_DPAD_LEFT, "D-Pad Left");
                checkButton(inState.buttonsAndDpad, prevState.buttonsAndDpad, DS5W_ISTATE_DPAD_RIGHT, "D-Pad Right");
                //checkButton(inState.buttonsA, prevState.buttonsA, DS5W_ISTATE_BTN_1_TOUCHPAD, "触摸板按下");

             
              
		}
	}
	// Shutdown cont ext
	DS5W::freeDeviceContext(&con);


	return 0;
}
/*#include <iostream>
#include <thread>
#include <chrono>
#include "ds5w.h"          // 库的主头文件

// 辅助函数：检查单个按键状态变化并打印
void checkButton(uint8_t curr, uint8_t prev, uint8_t mask, const char* name) {
    bool now = (curr & mask) != 0;
    bool was = (prev & mask) != 0;
    if (now != was) {
        std::cout << name << ": " << (now ? "PRESSED" : "RELEASED") << std::endl;
    }
}

int main() {
    // 初始化库
    if (DS5W::DS5W_InitAPI() != DS5W::DS5W_OK) {
        std::cerr << "初始化 DS5W 库失败" << std::endl;
        return -1;
    }

    // 枚举已连接的设备
    DS5W::DS5W_DeviceEnumerator enumerator;
    if (!DS5W::DS5W_EnumerateDevices(&enumerator)) {
        std::cerr << "未找到 DualSense 手柄" << std::endl;
        DS5W::DS5W_ExitAPI();
        return -1;
    }

    // 获取第一个手柄的信息
    DS5W::DS5W_Device device;
    if (!DS5W::DS5W_GetDeviceInfo(&enumerator, 0, &device)) {
        std::cerr << "无法获取设备信息" << std::endl;
        DS5W::DS5W_ExitAPI();
        return -1;
    }

    // 初始化设备上下文（用于后续读写）
    DS5W::DS5W_DeviceContext context;
    if (!DS5W::DS5W_InitDeviceContext(&device, &context)) {
        std::cerr << "初始化设备上下文失败" << std::endl;
        DS5W::DS5W_ExitAPI();
        return -1;
    }

    std::cout << "DualSense 手柄已连接！按下 PS 键退出程序。" << std::endl;

    DS5W::DS5W_InputState prevState = {};   // 保存上一帧状态，用于检测变化
    bool running = true;

    while (running) {
        DS5W::DS5W_InputState state;
        if (DS5W::DS5W_GetDeviceInputState(&context, &state) == DS5W::DS5W_OK) {
            // ----- 检测按键状态变化（buttons1 区域）-----
            // 根据 ds5w.h 中定义的掩码名称修改下面的常量
            checkButton(state.buttons1, prevState.buttons1, DS5W_ISTATE_BTN_1_CROSS,   "Cross (×)");
            checkButton(state.buttons1, prevState.buttons1, DS5W_ISTATE_BTN_1_CIRCLE,  "Circle (○)");
            checkButton(state.buttons1, prevState.buttons1, DS5W_ISTATE_BTN_1_SQUARE,  "Square (□)");
            checkButton(state.buttons1, prevState.buttons1, DS5W_ISTATE_BTN_1_TRIANGLE, "Triangle (△)");
            checkButton(state.buttons1, prevState.buttons1, DS5W_ISTATE_BTN_1_L1,      "L1");
            checkButton(state.buttons1, prevState.buttons1, DS5W_ISTATE_BTN_1_R1,      "R1");
            checkButton(state.buttons1, prevState.buttons1, DS5W_ISTATE_BTN_1_L3,      "L3 (左摇杆按下)");
            checkButton(state.buttons1, prevState.buttons1, DS5W_ISTATE_BTN_1_R3,      "R3 (右摇杆按下)");
            checkButton(state.buttons1, prevState.buttons1, DS5W_ISTATE_BTN_1_OPTIONS, "Options");
            checkButton(state.buttons1, prevState.buttons1, DS5W_ISTATE_BTN_1_SHARE,   "Share");
            checkButton(state.buttons1, prevState.buttons1, DS5W_ISTATE_BTN_1_PS,      "PS");
            checkButton(state.buttons1, prevState.buttons1, DS5W_ISTATE_BTN_1_DPAD_UP,    "D-Pad Up");
            checkButton(state.buttons1, prevState.buttons1, DS5W_ISTATE_BTN_1_DPAD_DOWN,  "D-Pad Down");
            checkButton(state.buttons1, prevState.buttons1, DS5W_ISTATE_BTN_1_DPAD_LEFT,  "D-Pad Left");
            checkButton(state.buttons1, prevState.buttons1, DS5W_ISTATE_BTN_1_DPAD_RIGHT, "D-Pad Right");
            checkButton(state.buttons1, prevState.buttons1, DS5W_ISTATE_BTN_1_TOUCHPAD,   "触摸板按下");

            // ----- 扳机键（模拟值，一般作为模拟量，但也可作为数字按键检测）-----
            // 如果需要查看模拟值，可以打印
            if (state.leftTrigger != prevState.leftTrigger || state.rightTrigger != prevState.rightTrigger) {
                std::cout << "左扳机: " << (int)state.leftTrigger 
                          << "  右扳机: " << (int)state.rightTrigger << std::endl;
            }

            // ----- 摇杆（范围 0~255）-----
            if (state.leftStick.x != prevState.leftStick.x || state.leftStick.y != prevState.leftStick.y) {
                std::cout << "左摇杆: (" << (int)state.leftStick.x << ", " << (int)state.leftStick.y << ")" << std::endl;
            }
            if (state.rightStick.x != prevState.rightStick.x || state.rightStick.y != prevState.rightStick.y) {
                std::cout << "右摇杆: (" << (int)state.rightStick.x << ", " << (int)state.rightStick.y << ")" << std::endl;
            }

            // ----- 陀螺仪/加速度计（可选）-----
            // 如果需要，可以在这里打印 state.gyroscope 和 state.accelerometer 的值

            // 更新前一状态
            prevState = state;

            // 按下 PS 键退出
            if (state.buttons1 & DS5W_ISTATE_BTN_1_PS) {
                std::cout << "PS 键按下，退出程序。" << std::endl;
                running = false;
            }
        } else {
            std::cerr << "读取手柄状态失败" << std::endl;
        }

        // 降低 CPU 占用
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    // 清理库资源
    DS5W::DS5W_ExitAPI();
    return 0;
}*/