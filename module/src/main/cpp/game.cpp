//
// Created by Perfare on 2020/7/4.
// Modified to support config file
//

#include "game.h"
#include "log.h"
#include <fstream>
#include <algorithm>
#include <cstring>

#define CONFIG_PATH "/data/adb/target_packages.txt"

// 缓存包名列表
static std::vector<std::string> target_packages;
static bool packages_loaded = false;

std::vector<std::string> load_target_packages() {
    if (packages_loaded) {
        return target_packages;
    }
    
    std::ifstream config_file(CONFIG_PATH);
    if (!config_file.is_open()) {
        LOGW("Config file not found: %s", CONFIG_PATH);
        // 返回空列表，模块将不会hook任何应用
        return target_packages;
    }
    
    std::string line;
    int count = 0;
    while (std::getline(config_file, line)) {
        // 去除首尾空白字符
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);
        
        // 跳过空行和注释
        if (line.empty() || line[0] == '#') {
            continue;
        }
        
        target_packages.push_back(line);
        count++;
        LOGI("Loaded target package: %s", line.c_str());
    }
    
    config_file.close();
    packages_loaded = true;
    LOGI("Loaded %d target packages from %s", count, CONFIG_PATH);
    
    return target_packages;
}

bool is_target_package(const char* package_name) {
    if (!package_name) {
        return false;
    }
    
    // 确保包名列表已加载
    if (!packages_loaded) {
        load_target_packages();
    }
    
    // 如果配置文件不存在或为空，不hook任何应用
    if (target_packages.empty()) {
        return false;
    }
    
    // 检查包名是否在目标列表中
    for (const auto& target : target_packages) {
        if (strcmp(package_name, target.c_str()) == 0) {
            return true;
        }
    }
    
    return false;
}