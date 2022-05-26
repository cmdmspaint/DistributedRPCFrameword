#pragma once

#include <unordered_map>
#include <string>
using namespace std;

// 框架读取配置文件类
class DRpcConfig
{
public:
    // 负责加载解析配置文件
    void LoadConfigFile(const char*config_file);

    // 查询配置项信息
    string Load(const string &key);
private:
    unordered_map<string,string> m_configMap;
    // 去掉字符串前后的空格
    void Trim(string &src_buf);
};
