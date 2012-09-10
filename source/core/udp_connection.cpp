#include "udp_connection.h"

#include <iostream>

#include <boost/bind.hpp>

using namespace std;
using namespace virt_dashboard;

static const int kInBufferLength = 1024;

void UdpConnection::Connect()
{
    if ( ! is_connected_ )
    {
        try
        {
            if ( socket_.is_open() )
                socket_.close();

            boost::system::error_code error;

            socket_.open(boost::asio::ip::udp::v4());

            socket_.bind(local_point_, error);

            if ( error == 0 )
                is_connected_ = true;
        }
        catch (exception& ex)
        {
            cout << "UdpConnection::Connect() - error = " << ex.what() << endl;
        }
    }
}

ByteArray ArrayToVector(char* array, int size)
{
    if ( size > kInBufferLength )
        return ByteArray();

    ByteArray result;

    for ( int i = 0; i < size; i++ )
        result.push_back(array[i]);

    return result;
}

ByteArray UdpConnection::ReceiveData()
{
    Connect();

    if ( ! is_connected_ )
        return ByteArray();

    char buffer[kInBufferLength];
    size_t bytes_transferred;

    try
    {
        /* FIXME: Try to use receive() nethod instead the receive_from() one */
        if ( socket_.available() != 0 )
            bytes_transferred = socket_.receive_from(
                                    boost::asio::buffer(buffer, kInBufferLength),
                                    remote_point_);
    }
    catch ( boost::system::system_error error )
    {
        is_connected_ = false;
        return ByteArray();
    }

    return ArrayToVector(buffer, bytes_transferred);
}

void UdpConnection::SendData(ByteArray data)
{
    Connect();

    if ( ! is_connected_ )
        return;

    if ( data.empty() )
        return;

    try
    {
        socket_.send_to(boost::asio::buffer(data), remote_point_);
    }
    catch ( boost::system::system_error error )
    {
        is_connected_ = false;
        cout << "UdpConnection::SendData() - error = " << error.what() << " code = " << error.code() << endl;
    }
}

void UdpConnection::SetLocalPoint(string address, int port)
{
    boost::asio::ip::address ip_address = boost::asio::ip::address::from_string(address);
    local_point_ = boost::asio::ip::udp::endpoint(ip_address, port);
}

void UdpConnection::SetRemotePoint(string address, int port)
{
    boost::asio::ip::address ip_address = boost::asio::ip::address::from_string(address);
    remote_point_ = boost::asio::ip::udp::endpoint(ip_address, port);
}