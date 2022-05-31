#include <iostream>
#include <string>
#include "user.pb.h"
#include "distributedrpc.h"
#include "rpcprovider.h"

using namespace example;

/*
 UserService是一个本地服务，提供了两个进程内的本地方法，Login和GetFriendLists
*/
class UserService : public UserServiceRpc   //rpc服务提供者
{

public:
    bool Login(std::string name,std::string pwd)
    {
        std::cout << ""<<std::endl;;
        std::cout << ""<<std::endl;
    }

    // 重写基类UserServiceRpc的虚函数 下面这些方法都是框架直接调用的
    void Login(::google::protobuf::RpcController* controller,
                       const ::example::LoginRequest* request,
                       ::example::LoginResponse* response,
                       ::google::protobuf::Closure* done)
    {
        // 框架给业务上报了请求参数LoginRequest，应用获取相应数据左本地业务
        std::string name = request->name();
        std::string pwd = request->pwd();

        // 做本地业务
        bool login_result = Login(name,pwd);

        // 把响应写入 包括错误码、错误消息、返回值
        example::ResultCode *code = response->mutable_result();
        code->set_errcode(0);
        code->set_errmsg("");
        response->set_sucess(login_result);

        // 执行回调操作 执行响应对象数据的序列化和网络发送（都是由框架来完成的）
        done->Run();
    }
};


int main(int argc,char **argv)
{

    // 调用框架的初始化操作
    DistributedRPC::Init(argc,argv);

    // provider是一个rpc网络服务对象，把UesrService对象发布到rpc节点上
    RpcProvider provider;
    provider.NotifyService(new UserService());
    //provider.NotifyService(new ProductService());

    // 启动一个rpc服务发布节点，Run以后，进程进入阻塞状态
    provider.Run();
    return 0;

}