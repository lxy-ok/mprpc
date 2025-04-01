rpc:

<img width="510" alt="图片1" src="https://github.com/user-attachments/assets/67ecdc3a-4f56-447c-90df-132555271599" />

Muduo库实现高性能网络通信模块、  Protobuf提供数据序列化和反序列化 ，并基于其实现RPC框架；

采用std::queue和读写锁实现线程安全的缓冲区，分离业务模块和日志模块，实现异步日志输出；

用服务器中间件Zookeeper分布式协调服务 ，实现服务注册和服务发现 ，心跳机制检测服务状态。

（使用读写锁替换互斥锁，优化）

<img src="https://github.com/lxy-ok/mprpc/assets/154768611/67438cac-1454-45b8-9f67-ab6829eab6b3" width="310px">

<img src="https://github.com/lxy-ok/mprpc/assets/154768611/0beb60cf-28e4-4ce2-af62-21c34580ca3a" width="310px">

压测：

![770bb9a5105989a02f9693cb6168da6](https://github.com/user-attachments/assets/aa202564-d7df-4208-9e00-5b947cd42755)






