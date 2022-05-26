#include <iostream>
#include "distributedrpc.h"
#include "user.pb.h"
#include "drpcchannel.h"

int main(int argc,char **argv)
{
    // 整个程序启动以后 想使用mprpc框架来享受rpc服务调用，一定需要先调用框架的初始化函数（只初始化一次）
    DistributedRPC::Init(argc,argv);

    // 演示调用远程发布的rpc方法Login
    example::UserServiceRpc_Stub stud(new DrpcChannel());
    // rpc方法的请求参数
    example::LoginRequest request;
    request.set_name("zhang san");
    request.set_pwd("123456");
    // rpc方法的响应
    example::LoginResponse response;
    // 发起rpc方法的调用 同步的rpc调用过程 callmethod
    stud.Login(nullptr,&request,&response,nullptr); // RpcChannel->RpcChannel::callMethod

    // 一次rpc调用完成，读调用结果
    if(0 == response.result().errcode())
    {
        std::cout << "rpc login response success:" << response.sucess() << std::endl;
    }
    else
    {
        std::cout << "rpc login response success:" << response.result().errmsg() << std::endl;
    }
    return 0;

}

