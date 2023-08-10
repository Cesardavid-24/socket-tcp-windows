#include <boost/asio.hpp>

boost::asio::io_service io_service_object;

boost::asio::ip::tcp::acceptor acceptor_object(
  io_service_object, 
  boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 9999)
);

boost::asio::ip::tcp::socket socket_object(io_service_object);

acceptor_object.accept(socket_object);

boost::asio::streambuf buf;
boost::asio::read_until(socket_object, buf, "\n");

std::string data = boost::asio::buffer_cast<const char*>(buf.data());

