# DistributedRPCFramework
# 分布式rpc框架架构
![image](https://user-images.githubusercontent.com/50624748/171130403-e63d1a0b-bbb7-4821-9ebf-66d85e3dbdc7.png)
# rpc框架调用流程
![image](https://user-images.githubusercontent.com/50624748/171130670-da038ef9-e828-4674-ada7-b622dc2acdb8.png)

# 快速入门
项目内置例子 通过下面步骤快速开始  
git clone git@github.com:cmdmspaint/DistributedRPCFramework.git  
cd build  
cmake ..  
make  
cd ../bin  
./provider -i config.conf  

再开一个窗口 还是bin目录  
./consumer -i config.conf  
# 如何使用
首先编写 proto文件，生成对应的.cc和.h文件 你可以参考我example目录下的proto文件  
将bin目录下的配置信息改为 你自己对应的服务器ip和端口  
然后重写基类中的虚函数  
# 调用者实例  
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

