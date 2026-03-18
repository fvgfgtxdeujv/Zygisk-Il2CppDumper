//
// Created by Perfare on 2020/7/4.
//

#ifndef ZYGISK_IL2CPPDUMPER_GAME_H
#define ZYGISK_IL2CPPDUMPER_GAME_H

#include <string>
#include <vector>

// 从配置文件加载目标包名列表
std::vector<std::string> load_target_packages();
// 检查包名是否在目标列表中
bool is_target_package(const char* package_name);

#endif //ZYGISK_IL2CPPDUMPER_GAME_H
