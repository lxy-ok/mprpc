#pragma once
#include <google/protobuf/service.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>

class mprpcchannel:public google::protobuf::RpcChannel{
// 所有通过stub代理对象调用的rpc方法，都走到这里了,调用者那一方
//统一做rpc方法调用的数据数据序列化和网络发送 
public:
void CallMethod(const google::protobuf::MethodDescriptor* method,
                          google::protobuf::RpcController* controller, 
                          const google::protobuf::Message* request,
                          google::protobuf::Message* response,
                          google::protobuf:: Closure* done);

};