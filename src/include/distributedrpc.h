#pragma once
#include "drpcconfig.h"

// 框架基础类，负责rpc的一些初始操作
class DistributedRPC
{
public:
    static void Init(int argc,char **argv);
    static DistributedRPC& GetInstance();
    static DRpcConfig& GetConfig();
private:

    static DRpcConfig m_config;

    DistributedRPC(){};    
    DistributedRPC(const DistributedRPC&) = delete; //拷贝构造函数
    DistributedRPC(DistributedRPC&&) =delete;       //拷贝赋值函数
};