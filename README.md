# DistributedRPCFramework
DistributedRPCFramework is a high-performance, c++-based open-source RPC framework.  
See the [中文文档](https://github.com/cmdmspaint/DistributedRPCFramework/blob/main/README-zh%20.md) for Chinese readme.
# Architecture
![image](https://user-images.githubusercontent.com/50624748/171139236-a3581c77-6589-427f-99dd-2c27b4c68555.png)

![image](https://user-images.githubusercontent.com/50624748/171136983-19564ae7-def1-4a9c-9c2f-d21e5564afcd.png)

# Components
rpc provider rpc comsumer zookeeper logger-system  Asynchronous buffer queues

# How to Build
git clone git@github.com:cmdmspaint/DistributedRPCFramework.git  
cd build  
cmake ..  
make  
cd ../bin  
./provider -i config.conf  
./consumer -i config.conf  
# How to Use
First write the proto file to generate the corresponding .cc and .h files You can refer to the proto file in my example directory  
change the configuration information in the bin directory to your own server ip and port  
Then override the virtual functions in the base class  
# Callee Example
```
class UserService : public UserServiceRpc  
{

public:
    bool Login(std::string name,std::string pwd)
    {
        std::cout << ""<<std::endl;;
        std::cout << ""<<std::endl;
    }
    void Login(::google::protobuf::RpcController* controller,
                       const ::example::LoginRequest* request,
                       ::example::LoginResponse* response,
                       ::google::protobuf::Closure* done)
    {
        std::string name = request->name();
        std::string pwd = request->pwd();
        bool login_result = Login(name,pwd);
        example::ResultCode *code = response->mutable_result();
        code->set_errcode(0);
        code->set_errmsg("");
        response->set_sucess(login_result);
        done->Run();
    }
};

int main(int argc,char **argv)
{
    DistributedRPC::Init(argc,argv);
    RpcProvider provider;
    provider.NotifyService(new UserService());
    provider.Run();
    return 0;

}
```
# Caller Example

```

    DistributedRPC::Init(argc,argv);
    example::UserServiceRpc_Stub stud(new DrpcChannel());
    example::LoginRequest request;
    request.set_name("zhang san");
    request.set_pwd("123456");
    example::LoginResponse response;
    DrpcController controller;
    stud.Login(nullptr,&request,&response,nullptr); // RpcChannel->RpcChannel::callMethod
    if (controller.Failed())
    {
       std::cout <<controller.ErrorText()<< std::endl;
    }
    else
    {
        if(0 == response.result().errcode())
        {
            std::cout << "rpc login response success:" << response.sucess() << std::endl;
        }
        else
        {
            std::cout << "rpc login response success:" << response.result().errmsg() << std::endl;
        }
    }
    
    return 0;
```

