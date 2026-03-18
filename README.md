# Zygisk-Il2CppDumper (Dev Branch - Config File Version)

Zygisk版Il2CppDumper，在Unity游戏运行时dump il2cpp元数据，能够绕过各种保护、加密和混淆机制。

> **分支说明**：这是开发分支（dev），支持配置文件管理多个目标包名。如需使用传统的硬编码包名版本，请切换到`master`分支。
> 
> **基于原项目修改**：[Perfare/Zygisk-Il2CppDumper](https://github.com/Perfare/Zygisk-Il2CppDumper)
> 
> **主要改进**：支持通过配置文件管理多个目标包名，无需重新编译即可修改目标应用。

## ✨ 新特性

- **配置文件支持**：通过 `/data/adb/target_packages.txt` 管理目标包名
- **多包名支持**：一行一个包名，支持监控多个应用
- **热配置**：修改配置文件无需重新编译模块
- **向后兼容**：保持原有功能，仅扩展配置方式

## 🚀 快速开始

### 前置要求
- Android设备已root
- Magisk v24+ 并启用Zygisk
- 目标应用为Unity游戏（使用il2cpp后端）

### 使用步骤

1. **准备配置文件**
   ```bash
   # 创建配置文件（需要root权限）
   su
   echo "com.example.game1" > /data/adb/target_packages.txt
   echo "com.example.game2" >> /data/adb/target_packages.txt
   ```

2. **构建模块**
   ```bash
   # 方法一：使用Android Studio
   ./gradlew :module:assembleRelease
   # 模块将生成在 out/ 目录
   
   # 方法二：GitHub Actions（需fork项目）
   # 1. Fork本项目
   # 2. 进入Actions标签页
   # 3. 运行Build workflow
   # 4. 下载构建产物
   ```

3. **安装模块**
   - 将生成的zip文件通过Magisk安装
   - 重启设备

4. **开始使用**
   - 启动配置文件中指定的任何应用
   - dump文件将生成在 `/data/data/<包名>/files/dump.cs`

## ⚙️ 配置文件详解

### 配置文件位置
```
/data/adb/target_packages.txt
```

### 文件格式
- 每行一个包名
- 支持 `#` 开头的注释行
- 自动忽略空行和首尾空白字符
- 包名区分大小写

### 配置示例
```txt
# Zygisk-Il2CppDumper 目标包名配置
# 每行一个包名，支持注释

# 游戏A
com.company.game.a

# 游戏B  
com.company.game.b

# 测试应用
com.test.unityapp
```

### 动态更新
配置文件支持动态更新，修改后：
1. 新启动的应用会使用新配置
2. 已运行的应用不受影响（需重启应用）
3. 无需重启设备或重新安装模块

## 🔧 构建指南

### Android Studio构建
```bash
# 克隆项目
git clone https://github.com/fvgfgtxdeujv/Zygisk-Il2CppDumper.git

# 构建模块
cd Zygisk-Il2CppDumper
./gradlew :module:assembleRelease

# 输出位置：out/*.zip
```

### GitHub Actions构建
1. Fork本项目到你的GitHub账户
2. 进入项目的Actions标签页
3. 选择"Build" workflow
4. 点击"Run workflow"
5. 等待构建完成并下载artifacts

## 📁 输出文件

### dump.cs 文件位置
```
/data/data/<目标包名>/files/dump.cs
```

### 文件内容
生成的 `dump.cs` 包含：
- Unity il2cpp二进制中的所有类型定义
- 类、方法、字段等元数据
- 可用于逆向分析和研究

### 多应用输出
当监控多个应用时，每个应用都会在自己的数据目录生成独立的dump文件：
```
/data/data/com.game.a/files/dump.cs
/data/data/com.game.b/files/dump.cs
...
```

## ❓ 常见问题

### Q1: 配置文件不存在怎么办？
A: 如果 `/data/adb/target_packages.txt` 不存在，模块将不会hook任何应用，处于静默状态。

### Q2: 配置文件为空或只有注释行？
A: 模块不会hook任何应用，与配置文件不存在的情况相同。

### Q3: 如何验证配置是否生效？
A: 查看logcat日志，搜索 "Perfare" tag，模块会输出加载的包名列表。

### Q4: 支持同时hook多少个应用？
A: 理论上无限制，但建议根据实际需求配置，过多可能会影响性能。

### Q5: 修改配置文件后需要重启吗？
A: 不需要重启设备，但需要重启目标应用才能应用新配置。

## ⚠️ 注意事项

1. **权限要求**：配置文件路径 `/data/adb/` 需要root权限访问
2. **文件编码**：建议使用UTF-8编码，避免特殊字符问题
3. **包名验证**：请确保包名拼写正确，区分大小写
4. **安全考虑**：配置文件中的包名将全部被hook，请谨慎配置

## 📄 许可证

本项目基于GPL-3.0许可证发布。详见 [LICENSE](LICENSE) 文件。

## 🙏 致谢

- 原项目作者：Perfare
- Zygisk框架：topjohnwu
- 所有贡献者和用户

---

> **提示**：本工具仅供学习和研究用途，请遵守相关法律法规和服务条款。
