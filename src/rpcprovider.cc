#include "rpcprovider.h"
#include "mprpcapplication.h"
#include "rpcheader.pb.h"
#include "logger.h"
#include "zookeeperutil.h"

/*
service_name =>  service描述   都是protobuf提供的
                        =》 service* 记录服务对象
                        method_name  =>  method方法对象
json   protobuf
*/

//这里是框架提供给外部使用的，可以发布rpc方法的函数接口，就是把各个比如login,register等这些方法分出来
 void rpcprovider::notifyservice(google::protobuf::Service * service){

    ServiceInfo service_info;

    // 获取了服务对象的描述信息
  const google::protobuf::ServiceDescriptor *pserviceDesc = service->GetDescriptor();
        
        // 获取服务的名字,UserServiceRpc
    std::string service_name = pserviceDesc->name();
   
    // 获取服务对象UserServiceRpc的方法的数量  有多少login等这种
    int methodCnt = pserviceDesc->method_count();

    std::cout << "service_name:" << service_name << std::endl;
    //LOG_INFO("service_name:%s", service_name.c_str());
  //service_name是UserServiceRpc，method_name是login
  
    for (int i=0; i < methodCnt; ++i)
    {
//获取了服务对象指定下标的服务方法的描述（抽象描述）用于表示一个服务对象中的一个具体方法。 UserService  Login
        const google::protobuf::MethodDescriptor* pmethodDesc = pserviceDesc->method(i);
        
        std::string method_name = pmethodDesc->name();

        service_info.m_methodMap.insert({method_name, pmethodDesc});
      //Login
        LOG_INFO("method_name:%s", method_name.c_str());
    }

    service_info.m_service = service;
    //比如login  login里面具体干什么的
    m_serviceMap.insert({service_name, service_info});
   
 }

    // 启动rpc服务节点，开始提供rpc远程网络调用服务
   void rpcprovider::run(){
std::string ip=mprpcapplication::getinstance().getconfig().load("rpcserviceip");

//无符号 16 位整数类型  uint16_t  atoi字符串转换为整数
uint16_t port=atoi(mprpcapplication::getinstance().getconfig().load("rpcserviceport").c_str());

//muduo::net::InetAddress 是一个网络地址类，属于 Muduo C++ 网络库的一部分。它封装了 IPv4 或 IPv6 的网络地址和端口号，并提供了一些方便的方法来获取和设置这些信息。
muduo::net::InetAddress address(ip,port);//启动tcp的参数

    // 创建TcpServer对象
   muduo::net::TcpServer server(&m_eventloop,address,"rpcprovider");

    // 绑定连接回调和消息读写回调方法  分离了网络代码和业务代码
/*
连接回调函数通常在服务器接受到客户端的连接时被调用。表示新建立的连接
消息回调函数：处理已连接的客户端发送过来的消息
std::placeholders::_1 是 C++11 标准库中提供的一种占位符，用于函数对象的参数绑定
代替一个函数的第一个参数，让这个参数在函数调用时才具体确定。
*/
server.setConnectionCallback(std::bind(&rpcprovider::OnConnection,this,std::placeholders::_1));
server.setMessageCallback(std::bind(&rpcprovider::OnMessage,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3));
    // 设置muduo库的线程数量
   server.setThreadNum(4);

    
    // 把当前rpc节点上要发布的服务全部注册到zk上面，让rpc client可以从zk上发现服务
    // session timeout   30s     zkclient 网络I/O线程  1/3 * timeout 时间发送ping消息
    ZkClient zkCli;
    zkCli.Start();
    // service_name为永久性节点    method_name为临时性节点
    for (auto &sp : m_serviceMap) 
    {
        // /service_name   /UserServiceRpc
        std::string service_path = "/" + sp.first;
        zkCli.Create(service_path.c_str(), nullptr, 0);
        for (auto &mp : sp.second.m_methodMap)
        {
            // /service_name/method_name   /UserServiceRpc/Login 存储当前这个rpc服务节点主机的ip和port
            std::string method_path = service_path + "/" + mp.first;
            char method_path_data[128] = {0};
            sprintf(method_path_data, "%s:%d", ip.c_str(), port);
            // ZOO_EPHEMERAL表示znode是一个临时性节点
            zkCli.Create(method_path.c_str(), method_path_data, strlen(method_path_data), ZOO_EPHEMERAL);
        }
    }

   


    // rpc服务端准备启动，打印信息
    std::cout << "RpcProvider start service at ip:" << ip << " port:" << port << std::endl;

    // 启动网络服务
    /*相当于启动了epoll wait，以阻塞的方式等待远程的连接
    有的时候moduo主动setConnectionCallback连接回调函数处理，
    收发数据就setMessageCallback消息回调函数*/
    server.start();
    m_eventloop.loop();
   }
   
   // 新的socket连接回调
    void rpcprovider::OnConnection(const muduo::net::TcpConnectionPtr& conn){
    if(!conn->connected())// 和rpc client的连接断开了
    conn->shutdown();
    }

/*
在框架内部，RpcProvider和RpcConsumer协商好之间通信用的protobuf数据类型
service_name method_name args    定义proto的message类型，进行数据头的序列化和反序列化
                                 service_name method_name args_size
16UserServiceLoginzhang san123456   

header_size(4个字节) + header_str + args_str是读完前面剩余的长度
10 "10"
10000 "1000000"
std::string   insert和copy方法 
*/
    // 已建立连接用户的读写事件回调
    void rpcprovider::OnMessage(const muduo::net::TcpConnectionPtr &conn, 
                            muduo::net::Buffer *buffer, 
                            muduo::Timestamp)
   {
   // 网络上接收的远程rpc调用请求的字符流    Login args 
    std::string recv_buf=buffer->retrieveAllAsString();

    // 从字符流中读取前4个字节的内容
   uint32_t header_size=0;
   recv_buf.copy((char *)&header_size,4,0);

    // 根据header_size读取数据头的原始字符流，反序列化数据，得到rpc请求的详细信息
   std::string rpc_header_str=recv_buf.substr(4,header_size);
  mprpc::rpcheader  rpcheader;
  std::string service_name;
  std::string method_name;
  uint32_t args_size;
  if(rpcheader.ParseFromString(rpc_header_str)){
        // 数据头反序列化成功
    service_name=rpcheader.servicename();
    method_name=rpcheader.methodname();
    args_size=rpcheader.argssize();
        }
        else{
        // 数据头反序列化失败
        std::cout << "rpc_header_str:" << rpc_header_str << " parse error!" << std::endl;
      return ;
       }
    
   
    // 获取rpc方法参数的字符流数据
   std::string args_str=recv_buf.substr(4+header_size,args_size);

    // 打印调试信息
    std::cout << "============================================" << std::endl;
    std::cout << "header_size: " << header_size << std::endl; 
    std::cout << "rpc_header_str: " << rpc_header_str << std::endl; 
    std::cout << "service_name: " << service_name << std::endl; 
    std::cout << "method_name: " << method_name << std::endl; 
    std::cout << "args_str: " << args_str << std::endl; 
    std::cout << "============================================" << std::endl;

    // 获取service对象和method对象
    auto it=m_serviceMap.find(service_name);
    if(it==m_serviceMap.end()){
        std::cout << service_name << " is not exist!" << std::endl;
        return;}
      
     
      auto mit=it->second.m_methodMap.find(method_name);
      if(mit==it->second.m_methodMap.end())
       {std::cout << service_name << ":" << method_name << " is not exist!" << std::endl;
        return;
    } 
 google::protobuf::Service *service=it->second.m_service; // 获取service对象  new UserService
 const google::protobuf::MethodDescriptor *method=mit->second; // 获取method对象  Login
  

    


    // 生成rpc方法调用的请求request和响应response参数
    google::protobuf::Message *request=service->GetRequestPrototype(method).New();
    if(!request->ParseFromString(args_str))
       { std::cout << "request parse error, content:" << args_str << std::endl;
        return;}
   google::protobuf::Message *response=service->GetResponsePrototype(method).New(); 

    // 给下面的method方法的调用，绑定一个Closure的回调函数
google::protobuf::Closure *done = google::protobuf::NewCallback< rpcprovider, 
                                          const muduo::net::TcpConnectionPtr&, 
                                                google::protobuf::Message*>
                                                      (this, 
                                                & rpcprovider::SendRpcResponse, 
                                                         conn, response);

    // 在框架上根据远端rpc请求，调用当前rpc节点上发布的方法
    // new UserService().Login(controller, request, response, done)
    //就是调用userservice.cc里面的login方法
    service->CallMethod(method, nullptr, request, response, done);


    } 
    // Closure的回调操作，用于序列化rpc(返回了)的响应和网络发送
    void  rpcprovider::SendRpcResponse(const muduo::net::TcpConnectionPtr& conn, google::protobuf::Message *response)
{
  //muduo::net::TcpConnectionPtr& conn,获取有关TCP连接的信息，以及对连接进行读写等操作。
   std::string response_str;
    if (response->SerializeToString(&response_str)) // response进行序列化
    {
        // 序列化成功后，通过网络把rpc方法执行的结果发送会rpc的调用方
        conn->send(response_str); 
    }
    else
    {
        std::cout << "serialize response_str error!" << std::endl; 
    }
   // 模拟http的短链接服务，由rpcprovider主动断开连接
    conn->shutdown();
    }