#include "distributedrpc.h"
#include "drpcconfig.h"
#include <iostream>
#include <unistd.h>

using namespace std;

DRpcConfig DistributedRPC::m_config;

void ShowArgsHelp()
{
    std::cout << "format: command -i <configfile>" << std::endl;
}

void DistributedRPC::Init(int argc,char **argv)
{
    if(argc < 2)
    {
        ShowArgsHelp();
        exit(EXIT_FAILURE);
    }

    int c= 0;
    string config_file;
    while ((c = getopt(argc,argv,"i:")) != -1)
    {
        switch(c)
        {
        case 'i':
            config_file = optarg;
            break;
        case '?':
            //std::cout << "invalid args!" <<std::endl;
            ShowArgsHelp();
            exit(EXIT_FAILURE);
        case ':':
            //std::cout << "need <configfile>!" <<std::endl;
            ShowArgsHelp();
            exit(EXIT_FAILURE);
        default:
            break;

        }
    }
    
    // 开始加载配置文件了 rpcserver_port zookeeper_ip = zookepper_port=
    m_config.LoadConfigFile(config_file.c_str());

    // cout << "rpcserverip:" << m_config.Load("rpcserverip")<<endl;
    // cout << "rpcserverport:" << m_config.Load("rpcserverport")<<endl;
    // cout << "zookeeperip:" << m_config.Load("zookeeperip")<<endl;
    // cout << "zookeeperport:" << m_config.Load("zookeeperport")<<endl;
    

}

DistributedRPC& DistributedRPC::GetInstance()
{
    static DistributedRPC disRpc;
    return disRpc;
}

DRpcConfig& DistributedRPC::GetConfig()
{
    return m_config;
}