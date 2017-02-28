//#include "serverservice.h"
//#include <thrift/protocol/TBinaryProtocol.h>
//#include <thrift/transport/TSocket.h>
//#include <thrift/transport/TTransportUtils.h>
//#include "../gen-cpp/RpcService.h"
//#include "../gen-cpp/RpcService_constants.h"
//#include "../gen-cpp/RpcService_types.h"
//#include "../gen-cpp/RpcService.cpp"
//#include "../gen-cpp/RpcService_constants.cpp"
//#include "../gen-cpp/RpcService_types.cpp"
//#include <QtCore/QCoreApplication>
//#include <QDebug>
//using namespace std;
//using namespace apache::thrift;
//using namespace apache::thrift::protocol;
//using namespace apache::thrift::transport;
//using namespace rpcc;

//string server = "127.0.0.1";
//boost::shared_ptr<TTransport> socket1(new TSocket(server, 19090));
//boost::shared_ptr<TTransport> transport1(new TBufferedTransport(socket1));
//boost::shared_ptr<TProtocol> protocol1(new TBinaryProtocol(transport1));
//RpcServiceClient client(protocol1);

//serverservice::serverservice()
//{
//    protocol_m=protocol1;
//    transport_m=transport1;
//    }
//void serverservice::trytoconnect()
//{

//    try
//    {
//    transport_m->open();
//    res ress;
//    client.login(ress,"json","newpass");
//    qDebug()<<QString::fromStdString(ress.msg);
//    }
//    catch(apache::thrift::TApplicationException &e)
//    {
//        cout<<e.what()<<endl;
//    }
//}
