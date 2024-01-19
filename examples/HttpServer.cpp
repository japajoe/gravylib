#include "System/Net/TcpListener.hpp"
#include "System/Net/SslContext.hpp"
#include "System/Net/SslStream.hpp"
#include "System/Text/StringBuilder.hpp"
#include "System/String.hpp"
#include "System/Signal.hpp"
#include <iostream>
#include <memory>
#include <future>
#include <vector>

using namespace Gravy::System;
using namespace Gravy::System::Net;
using namespace Gravy::System::Text;

constexpr int MAX_HEADER_SIZE = 8192;
constexpr uint16_t PORT = 8080;
constexpr int32_t BACKLOG = 1000;

static std::unique_ptr<TcpListener> listener = nullptr;
static std::unique_ptr<SslContext> sslContext = nullptr;
static void OnHandleSignal(int signum);
static void OnHandleConnection(TcpClient client);
static uint32_t ReadHeader(SslStream *stream, std::string &header);

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

    listener = std::make_unique<TcpListener>("0.0.0.0", PORT, BACKLOG);

    if(!listener->Start())
        return 1;

    std::cout << "Server started listening on port " << PORT << '\n';

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

        std::string header;
        int32_t headerSize = ReadHeader(&stream, header);

        StringBuilder sb;

        if(headerSize > 0 && headerSize <= MAX_HEADER_SIZE)
        {
            std::cout << header << '\n';
            
            std::string content = "<h1>Hello world</h1>";
            //Status code 200: Ok
            sb.Append("HTTP/1.1 " + std::to_string(static_cast<int>(200)) + "\r\n");
            sb.Append("Content-Type: text/html\r\n");
            sb.Append("Content-length: " + std::to_string(content.size()) + "\r\n");
            sb.Append("\r\n");
            sb.Append(content);
        }
        else
        {
            //Status code 400: Bad request
            sb.Append("HTTP/1.1 " + std::to_string(static_cast<int>(400)) + "\r\n");
            sb.Append("\r\n");
        }

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

uint32_t ReadHeader(SslStream *stream, std::string &header)
{
    std::vector<char> headerBuilder;
    unsigned char prevByte = 0;
    unsigned char currentByte = 0;
    int curByte = 0;
    int headerSize = 0;

    while ((curByte = stream->ReadByte()) != -1)
    {
        currentByte = static_cast<unsigned char>(curByte);
        headerBuilder.push_back(static_cast<char>(currentByte));
        headerSize++;

        if(headerSize > MAX_HEADER_SIZE)
            break;

        if (prevByte == '\r' && currentByte == '\n')
        {
            std::string str(headerBuilder.begin(), headerBuilder.end());

            if(String::EndsWith(str, "\r\n\r\n"))
            {
                break;
            }
        }

        prevByte = currentByte;
    }

    header = std::string(headerBuilder.begin(), headerBuilder.end());
    return headerSize;
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
            std::cout << "Broken pipe\n";
            break;    
        }
    }
}