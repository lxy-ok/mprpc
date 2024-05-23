#include <iostream>
#include <string>
#include "user.pb.h"
#include "rpcprovider.h"
#include "mprpcapplication.h"
/*
UserService原来是一个本地服务，提供了两个进程内的本地方法，Login和GetFriendLists
*/
class userservice:public fixbug::UserServiceRpc{
public:   //发布端，用rpc远程调用，让其他的能调用这个方法
     bool Login(std::string name, std::string pwd)
    {
        std::cout << "doing local service: Login" << std::endl;
        std::cout << "name:" << name << " pwd:" << pwd << std::endl;  
        return true;
    }
     bool Register(uint32_t id, std::string name, std::string pwd)
    {
        std::cout << "doing local service: Register" << std::endl;
        std::cout << "id:" << id << "name:" << name << " pwd:" << pwd << std::endl;
        return true;
    }
     /*
    重写基类UserServiceRpc的虚函数 下面这些方法都是框架直接调用的
    1. caller   ===>   Login(LoginRequest)  => muduo =>   callee 
    2. callee   ===>    Login(LoginRequest)  => 交到下面重写的这个Login方法上了
    现在我们相当于callee，接受其他想要调用我门的login，然后用下面的，拿出数据，然后响应，回调，经过框架，在返回到调用我们的那边*/
void Login(::google::protobuf::RpcController* controller,
                       const ::fixbug::loginrequest* request,
                       ::fixbug::loginresponse* response,
                       ::google::protobuf::Closure* done)
{
// 框架给业务上报了请求参数LoginRequest，应用获取相应数据做本地业务
        std::string name=request->name();
        std::string pwd=request->pwd();

        // 做本地业务
       bool login_result=Login(name,pwd);

        // 把响应写入  包括错误码、错误消息、返回值
        fixbug::resultcode * code=response->mutable_result();
        code->set_errcode(0);
        code->set_errmsg("");
        response->set_success(login_result);

        // 执行回调操作   执行响应对象数据的序列化和网络发送（都是由框架来完成的）
      done->Run();

}
void Register(::google::protobuf::RpcController* controller,
                       const ::fixbug::registerrequest* request,
                       ::fixbug::registerresponse* response,
                       ::google::protobuf::Closure* done){
          uint32_t id = request->id();
        std::string name = request->name();
        std::string pwd = request->pwd();

        bool ret = Register(id, name, pwd);

        response->mutable_result()->set_errcode(0);
        response->mutable_result()->set_errmsg("");
        response->set_success(ret);

        done->Run();


                       }
};
int main(int  argc,char** argv)
{

     // 调用框架的初始化操作          
     mprpcapplication::init(argc,argv);

    // provider是一个rpc网络服务对象。把UserService对象发布到rpc节点上
    rpcprovider provider;
       provider.notifyservice(new userservice());
    
    // 启动一个rpc服务发布节点   Run以后，进程进入阻塞状态，等待远程的rpc调用请求
      provider.run();
    return 0;
}