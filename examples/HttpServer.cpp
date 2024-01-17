#ifndef GRAVY_USE_OPENSSL
#define GRAVY_USE_OPENSSL
#endif

#include "System/Net/TcpListener.hpp"
#include "System/Net/SslContext.hpp"
#include "System/Net/SslStream.hpp"
#include "System/StringBuilder.hpp"
#include "System/Signal.hpp"
#include <iostream>
#include <memory>
#include <future>

using namespace Gravy::System;
using namespace Gravy::System::Net;

static std::unique_ptr<TcpListener> listener = nullptr;
static std::unique_ptr<SslContext> sslContext = nullptr;
static void OnHandleSignal(int signum);
static void OnHandleConnection(TcpClient client);

int main(int argc, char **argv)
{
    Signal::Register(SignalType::SigInt, OnHandleSignal);
    
    //Note: Windows does not have the SigPipe signal
    //OpenSSL can trigger this if a connection is lost
    //If not handled, the application simply closes
    Signal::Register(SignalType::SigPipe, OnHandleSignal);

    try
    {
        sslContext = std::make_unique<SslContext>("cert.pem", "key.pem");
    }
    catch(const SslException &ex)
    {
        std::cout << ex.what() << '\n';
        return 1;
    }

    uint16_t port = 8080;

    listener = std::make_unique<TcpListener>("0.0.0.0", port, 1000);

    if(!listener->Start())
    {
        return 1;
    }

    std::cout << "Server started listening on port " << port << '\n';

    while(true)
    {
        TcpClient client;

        if(listener->Accept(client))
        {
            auto result = std::async(std::launch::async, OnHandleConnection, client);
        }
    }

    return 0;
}

void OnHandleConnection(TcpClient client)
{
    try
    {
        SslStream stream(client.GetSocket(), sslContext.get());

        unsigned char buffer[1024];
        std::memset(buffer, 0, 1024);

        if(stream.Read(buffer, 1023) > 0)
        {
            std::cout << buffer;
        }

        StringBuilder sb;
        sb.Append("HTTP/1.1 " + std::to_string(static_cast<int>(200)) + "\r\n");
        sb.Append("\r\n");

        std::string response = sb.ToString();                
        stream.Write(response.data(), response.size());
        stream.Close();
    }
    catch(const SslException &ex)
    {
        std::cout << ex.what() << '\n';
    }
    
    client.Close();
}

void OnHandleSignal(int signum)
{
    SignalType type = static_cast<SignalType>(signum);
    switch(type)
    {
        case SignalType::SigInt:
        {
            if(listener)
                listener->Close();
            if(sslContext)
                sslContext->Dispose();
            std::cout << "Closing server\n";
            exit(signum);
            break;
        }
        case SignalType::SigPipe:
        {
            break;    
        }
    }
}