# Zygisk-Il2CppDumper
Zygisk版Il2CppDumper，在游戏运行时dump il2cpp数据，可以绕过保护，加密以及混淆。

[原创](https://github.com/Perfare/Zygisk-Il2CppDumper)
我只是更改了一下，以适应现在新的github
## 如何食用
1. 安装[Magisk](https://github.com/topjohnwu/Magisk) v24以上版本并开启Zygisk
2. 生成模块
   - GitHub Actions
      1. Fork这个项目
      2. 在你fork的项目中选择**Actions**选项卡
      3. 在左边的侧边栏中，单击**Build**
      4. 选择**Run workflow**
      5. 输入游戏包名并点击**Run workflow**
      6. 等待操作完成并下载
    - Android Studio
       1. 下载源码
       2. 创建配置文件`/data/adb/target_packages.txt`，每行一个目标包名（例如：`com.game.packagename`）
       3. 使用Android Studio运行gradle任务`:module:assembleRelease`编译，zip包会生成在`out`文件夹下
3. 在Magisk里安装模块
4. 启动目标应用，会在`/data/data/<目标包名>/files/`目录下生成`dump.cs`

## 配置文件说明
模块现在支持通过配置文件`/data/adb/target_packages.txt`指定多个目标包名。每行一个包名，空行和以`#`开头的行会被忽略。

示例配置文件：
```
# 目标Unity游戏包名列表
com.game.packagename
com.another.game
com.example.unitygame
```
