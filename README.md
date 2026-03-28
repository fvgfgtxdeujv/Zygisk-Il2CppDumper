# Zygisk-Il2CppDumper

Zygisk版Il2CppDumper，在游戏运行时dump il2cpp数据，可以绕过保护，加密以及混淆。

> [!NOTE]
> 本项目基于 [Perfare/Zygisk-Il2CppDumper](https://github.com/Perfare/Zygisk-Il2CppDumper) 进行适配更新

## 特性

- ✅ 支持绕过游戏保护、加密和混淆
- ✅ 兼容最新版 Magisk 和 Zygisk
- ✅ GitHub Actions 自动构建
- ✅ 支持 x86/x86_64 模拟器（通过 Native Bridge）

## 构建环境

| 组件 | 版本 |
|------|------|
| Android Gradle Plugin | 8.2.0 |
| Gradle | 8.2 |
| Java (OpenJDK) | 17 |
| Android SDK | API 34 |
| Android NDK | 26.2.11394342 |
| CMake | 3.22.1 |

## 使用方法

### 前置要求

- [Magisk](https://github.com/topjohnwu/Magisk) v24+ 并开启 Zygisk

### 方式一：GitHub Actions（推荐）

1. Fork 本项目
2. 进入你 Fork 的仓库，点击 **Actions** 选项卡
3. 在左侧边栏选择 **Classic Build (Hardcoded Mode)**
4. 点击 **Run workflow**
5. 输入目标游戏包名（如 `com.example.game`）
6. 等待构建完成后下载 Artifact

### 方式二：本地构建

**环境要求：**
- JDK 17 (推荐 [Eclipse Temurin](https://adoptium.net/))
- Android SDK API 34
- Android NDK 26.x

**构建步骤：**

```bash
# 1. 克隆仓库
git clone https://github.com/fvgfgtxdeujv/Zygisk-Il2CppDumper.git
cd Zygisk-Il2CppDumper

# 2. 修改目标包名
# 编辑 module/src/main/cpp/game.h
# 将 GamePackageName "com.game.packagename" 改为你的目标包名

# 3. 构建
./gradlew :module:assembleRelease

# 4. 输出文件位于
# out/magisk_module_release/
```

### 安装与使用

1. 在 Magisk 中安装生成的模块 ZIP
2. 重启设备
3. 启动目标游戏
4. 等待几秒后，dump 文件将生成于：
   ```
   /data/data/<游戏包名>/files/dump.cs
   ```

## 常见问题

<details>
<summary><b>如何获取 dump.cs 文件？</b></summary>

使用 ADB 或 Root 文件管理器：
```bash
adb shell su -c "cat /data/data/<包名>/files/dump.cs" > dump.cs
```
</details>

<details>
<summary><b>为什么没有生成 dump.cs？</b></summary>

1. 确认 Magisk 和 Zygisk 已正确启用
2. 确认模块已激活并重启设备
3. 检查包名是否正确
4. 查看 Logcat 过滤 `Zygisk-Il2CppDumper` 标签
</details>

<details>
<summary><b>支持模拟器吗？</b></summary>

支持 x86/x86_64 模拟器，通过 Native Bridge 机制加载 ARM 库。
</details>

## 开发

### 项目结构

```
├── module/
│   ├── src/main/cpp/     # Native C++ 代码
│   │   ├── main.cpp      # Zygisk 模块入口
│   │   ├── hack.cpp      # 注入逻辑
│   │   ├── il2cpp_dump.cpp # Dump 实现
│   │   └── game.h        # 目标包名配置
│   └── build.gradle      # 模块构建配置
├── template/             # Magisk 模块模板
├── build.gradle          # 项目构建配置
└── gradle.properties     # Gradle 配置
```

### 自定义修改

- **game.h** - 修改 `GamePackageName` 宏定义目标包名
- **module.gradle** - 修改模块元数据（名称、版本、作者等）

## License

[MIT License](LICENSE)

## 致谢

- [Perfare](https://github.com/Perfare) - 原始项目作者
- [Magisk](https://github.com/topjohnwu/Magisk) - Zygisk 框架
