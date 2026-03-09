# EasyX Game Gallery - Classic Games Collection

一个使用 EasyX 图形库开发的经典游戏合集演示软件。

## 项目概述

本项目是一个个人练习项目，旨在复刻经典游戏（贪吃蛇、俄罗斯方块、吃豆人等），并通过一个统一的展示平台来演示这些游戏。

## 功能特性

- 🎮 **开始菜单** - 包含退出、设置、复刻游戏目录按钮
- 📁 **游戏目录** - 展示已复刻游戏的预览（图片、名称、简介）
- 🎯 **可扩展架构** - 方便添加新游戏
- ⚙️ **设置系统** - 支持自定义配置

## 项目结构

```
ClassicGamesGallery/
├── CMakeLists.txt          # CMake 构建配置
├── README.md               # 项目说明文档
├── .gitignore             # Git 忽略配置
├── include/               # 头文件目录
│   ├── core/             # 核心框架
│   │   ├── Application.h
│   │   ├── MenuSystem.h
│   │   ├── GameGallery.h
│   │   └── Settings.h
│   ├── games/            # 游戏基类和接口
│   │   ├── Game.h
│   │   ├── SnakeGame.h
│   │   ├── TetrisGame.h
│   │   └── PacmanGame.h
│   └── ui/               # UI 组件
│       ├── Button.h
│       └── TextBox.h
├── src/                  # 源文件目录
│   ├── main.cpp
│   ├── Application.cpp
│   ├── MenuSystem.cpp
│   ├── GameGallery.cpp
│   └── games/
│       ├── SnakeGame.cpp
│       ├── TetrisGame.cpp
│       └── PacmanGame.cpp
├── assets/               # 资源文件
│   ├── images/           # 游戏图片
│   ├── sounds/           # 音效文件
│   └── fonts/            # 字体文件
└── bin/                  # 编译输出目录
```

## 环境要求

- **操作系统**: Windows 10/11
- **编译器**: MSVC (Visual Studio 2019+) 或 MinGW
- **图形库**: EasyX 2022 或更新版本
- **CMake**: 3.14 或更新版本

## 安装 EasyX

1. 访问 [EasyX 官网](https://easyx.cn/)
2. 下载最新版本的 EasyX
3. 按照安装向导完成安装（默认安装在 `C:/Program Files (x86)/EasyX/`）

## 构建项目

### 使用 Visual Studio

1. 打开 `ClassicGamesGallery.sln` 解决方案文件
2. 选择 `Release` 或 `Debug` 配置
3. 按 `Ctrl+Shift+B` 编译项目

### 使用 CMake

```bash
# 创建构建目录
mkdir build
cd build

# 生成项目
cmake ..

# 编译
cmake --build . --config Release

# 运行
cd ../bin
ClassicGamesGallery.exe
```

## 添加新游戏

1. 在 `include/games/` 目录下创建游戏头文件，继承自 `Game` 基类
2. 在 `src/games/` 目录下实现游戏逻辑
3. 在 `GameGallery` 中注册新游戏
4. 在 `assets/images/` 目录下添加游戏预览图片

## 游戏开发指南

### 基本框架

```cpp
#include "games/Game.h"

class MyGame : public Game {
public:
    MyGame() : Game("游戏名称", "assets/images/game.png") {}
    
    void Initialize() override {
        // 初始化游戏
    }
    
    void Update() override {
        // 游戏逻辑更新
    }
    
    void Render() override {
        // 渲染游戏画面
    }
    
    void HandleInput(int key) override {
        // 处理输入
    }
};
```

### 按钮事件

```cpp
void MyGame::HandleInput(int key) {
    switch(key) {
        case VK_UP:
            // 向上移动
            break;
        case VK_DOWN:
            // 向下移动
            break;
        case VK_ESCAPE:
            // 返回菜单
            SetExitFlag(true);
            break;
    }
}
```

## 核心 API

### Application 类
- `Run()` - 启动应用程序
- `SwitchScene(SceneType type)` - 切换场景

### MenuSystem 类
- `Show()` - 显示主菜单
- `HandleInput()` - 处理菜单输入

### GameGallery 类
- `Show()` - 显示游戏目录
- `SelectGame(int index)` - 选择游戏

### Game 基类
- `Initialize()` - 初始化游戏
- `Update()` - 更新游戏逻辑
- `Render()` - 渲染游戏画面
- `HandleInput(int key)` - 处理输入

## 示例游戏

### 1. 贪吃蛇 (Snake)
经典贪吃蛇游戏，通过方向键控制蛇的移动。

### 2. 俄罗斯方块 (Tetris)
经典俄罗斯方块游戏，方向键控制方块移动和旋转。

### 3. 吃豆人 (Pacman)
经典吃豆人游戏，通过方向键控制角色移动。

## 扩展功能

- [ ] 添加音效系统
- [ ] 添加游戏存档功能
- [ ] 添加高分榜
- [ ] 支持游戏设置（速度、音量等）
- [ ] 添加更多经典游戏

## 许可证

MIT License

## 作者

[Your Name]

## 更新日志

### v1.0.0 (2024-01)
- 初始版本
- 实现基础框架
- 实现开始菜单
- 实现游戏目录预览
- 添加贪吃蛇示例游戏
