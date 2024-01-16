#include "System/Net/HttpClient.hpp"
#include "System/String.hpp"
#include "System/URI.hpp"
#include "System/Math.hpp"
#include "System/StringBuilder.hpp"
#include "System/Net/Socket.hpp"
#include "System/Net/HostInfo.hpp"
#include "System/Net/SslStream.hpp"

namespace Gravy::System::Net
{
#ifdef GRAVY_USE_OPENSSL
    static void HttpClientWrite(SslStream *stream, const void *data, size_t dataSize);
    static void HttpClientRead(SslStream *stream, const HttpClientResponseHandler &responseHandler, void *userData);
#endif    
    static void HttpClientWrite(Socket *socket, const void *data, size_t dataSize);
    static void HttpClientRead(Socket *socket, const HttpClientResponseHandler &responseHandler, void *userData);

    HttpClient::HttpClient()
    {
        this->responseHandler = nullptr;
        this->userData = nullptr;
    }

    HttpClient::~HttpClient()
    {
        Close();
    }

    void HttpClient::SetResponseHandler(const HttpClientResponseHandler &responseHandler, void *userData)
    {
        this->responseHandler = responseHandler;
        this->userData = userData;
    }

    void HttpClient::Get(const std::string &url)
    {
        if(responseHandler == nullptr)
            throw HttpClientException("No HttpClientResponseHandler has been assigned");

    #ifdef GRAVY_USE_OPENSSL
        if(sslContext.GetContext() == nullptr)
            throw HttpClientException("SSL context is not initialized");
    #endif

        URI uri(url);

        std::string path;

        if(!uri.GetPath(path))
            throw HttpClientException("Failed to resolve path from URL");

        if(path.size() == 0)
            path = "/";

        HostInfo hostInfo;
        
        if(!HostInfo::Resolve(url, hostInfo))
            throw HttpClientException("Failed to resolve host from URL");

        Socket socket(SocketType::Stream, AddressFamily::AFInet);
        
        if(!socket.Connect(hostInfo.ip, hostInfo.port))
        {
            socket.Close();
            throw HttpClientException("Failed to connect to IP");
        }

        StringBuilder sb;
        sb.Append("GET " + path + " HTTP/1.1\r\n");
        sb.Append("Host: " + hostInfo.name + "\r\n");
        sb.Append("Connection: close\r\n\r\n");

        std::string request = sb.ToString();
        char *pRequest = const_cast<char*>(request.data());

    #ifdef GRAVY_USE_OPENSSL
        if(String::Contains(url, "https://"))
        {
            SslStream sslStream(socket, &sslContext, hostInfo.name.c_str());
            HttpClientWrite(&sslStream, pRequest, request.size());
            HttpClientRead(&sslStream, responseHandler, userData);
            sslStream.Close();
        }
        else
        {
            HttpClientWrite(&socket, pRequest, request.size());
            HttpClientRead(&socket, responseHandler, userData);
        }
    #else
        HttpClientWrite(&socket, pRequest, request.size());
        HttpClientRead(&socket, responseHandler, userData);
    #endif
        socket.Close();
    }

    void HttpClient::Close()
    {
    #ifdef GRAVY_USE_OPENSSL
        if(sslContext.GetContext() != nullptr)
            sslContext.Dispose();
    #endif
    }

#ifdef GRAVY_USE_OPENSSL
    void HttpClientWrite(SslStream *stream, const void *data, size_t dataSize)
    {
        size_t bytesSent = 0;
        size_t bytesLeft = dataSize;
        char *pData = reinterpret_cast<char*>(const_cast<void*>(data));

        while(bytesSent < dataSize)
        {
            int64_t size = Math::Min(bytesLeft, dataSize);
            size_t numBytes = stream->Write(&pData[bytesSent], size);

            if(numBytes > 0)
            {
                bytesSent += numBytes;
                bytesLeft -= numBytes;
            }
        }
    }

    void HttpClientRead(SslStream *stream, const HttpClientResponseHandler &responseHandler, void *userData)
    {
        unsigned char buffer[1024];
        std::memset(buffer, 0, 1024);

        size_t numBytes = 0;

        while((numBytes = stream->Read(buffer, 1023)) > 0)
        {
            responseHandler(buffer, numBytes, userData);
        }
    }
#endif

    void HttpClientWrite(Socket *socket, const void *data, size_t dataSize)
    {
        size_t bytesSent = 0;
        size_t bytesLeft = dataSize;
        char *pData = reinterpret_cast<char*>(const_cast<void*>(data));

        while(bytesSent < dataSize)
        {
            int64_t size = Math::Min(bytesLeft, dataSize);
            size_t numBytes = socket->Write(&pData[bytesSent], size);

            if(numBytes > 0)
            {
                bytesSent += numBytes;
                bytesLeft -= numBytes;
            }
        }
    }

    void HttpClientRead(Socket *socket, const HttpClientResponseHandler &responseHandler, void *userData)
    {
        unsigned char buffer[1024];
        std::memset(buffer, 0, 1024);

        size_t numBytes = 0;

        while((numBytes = socket->Read(buffer, 1023)) > 0)
        {
            responseHandler(buffer, numBytes, userData);
        }
    }
};