#include <error_handle.h>

#include <unordered_map> 

class HashErrorType {
public:
  template<typename T>
  std::size_t operator ()(const T& t) const {
    return static_cast<std::size_t>(t);
  }
};

namespace comnet {
namespace error { 

/**
   Operating system error map.
 */
  std::unordered_map<OSErrors, char*, HashErrorType> os_error_map = { 
   _ERROR(error_no_os, "Not operating system specific."),
   _ERROR(error_windows, "Windows error."),
   _ERROR(error_wsa_service, "WSA Service error."),
   _ERROR(error_linux, "Linux error."),
   _ERROR(error_unix, "Unix error."),
   _ERROR(error_mac, "Macintosh error."),
};

/**
   Connection Error map.
 */
  std::unordered_map<ConnectErrors, char*, HashErrorType> connect_error_map = { 
   _ERROR(error_no_connection_error, "No connection error."),
   _ERROR(error_con_unknown_error, "Unknown Error."),
   _ERROR(error_udp_error, "UDP error."),
   _ERROR(error_xbee_error, "Xbee error."),
   _ERROR(error_xbee_error_new_connection, "Xbee failed to create new connection to address."),
   _ERROR(error_xbee_error_init, "Xbee failed to init or is missing."),
   _ERROR(error_xbee_error_close, "Xbee failed to close."),
   _ERROR(error_tcp_error, "TCP error."),
   _ERROR(error_socket_bind_fail, "Socket bind failed."),
   _ERROR(error_open_socket_fail, "Open socket failed."),
   _ERROR(error_socket_error, "Error in socket!"),
   _ERROR(error_invalid_handle, "Invalid handle."),
   _ERROR(error_com_state, "Error in Com state."),
   _ERROR(error_set_time_out, "Error in setting the time out."),
   _ERROR(error_connection_failed, "The connection to receiving end has failed."),
   _ERROR(error_socket_close_failed, "The connection failed to close."),
   _ERROR(error_already_connected, "Already connected to address."),
 
};

/**
   Internal Error map.
 */
  std::unordered_map<InternalErrors, char*, HashErrorType> internal_error_map = {
   _ERROR(error_no_internal_error, "No internal error."),
   _ERROR(error_intern_unknown_error, "Unknown internal error."),
   _ERROR(error_internal_connection_error, "No live connection."),
   _ERROR(error_connection_already_established, "A connection was already established to the given node"),
   _ERROR(error_cannot_read_file, "Can not read file."),
   _ERROR(error_cannot_write_file, "Can not write into file."),
   _ERROR(error_invalid_hex_string, "Invalid hex string."),
};

/** 
   Constructor for ConnectionException. Allows all parameter customization.
 */
ConnectionException::ConnectionException(OSErrors os_err
                                       , ConnectErrors conn_err) : 
                                         connect_error(conn_err)
                                       , AbsException(os_err) {
}

/**
   ConnectionException Constructor checks os_err.
 */
ConnectionException::ConnectionException(OSErrors os_err) : 
                                         connect_error(error_con_unknown_error)
                                       , AbsException(os_err) {
}

/**
   ConnectionException Constructor checks error parameters.
 */
ConnectionException::ConnectionException(ConnectErrors conn_err) : 
                                         ConnectionException(error_no_os
                                                           , conn_err) { 
}

/**
   InternalException Constructor for customization.
 */
InternalException::InternalException(OSErrors os_err
                                   , InternalErrors intern_err) : 
                                     internal_error(intern_err)
                                   , AbsException(os_err) {
}

/**
   InternalException to define os error types.
 */
InternalException::InternalException(OSErrors os_err) : 
                                     InternalException(os_err
                                                     , error_intern_unknown_error) {
}

/**
   InternalException Constructor for interal error parameters.
 */
InternalException::InternalException(InternalErrors intern_err) : 
                                     InternalException(error_no_os
                                                     , intern_err) {
}

/**
   Returns the os type error.
*/
const std::string AbsException::get_os_error(void) { 
   return os_error_map.at(os_error);
}

/**
 Destructor for the error handler class.
*/
ConnectionException::~ConnectionException(void) throw() { 
}

/**
   Throws out what the exception is.
*/
const char* ConnectionException::what() const throw() { 
   return "Connection Error";
}

/**
   Returns explanation of error.
*/
const std::string ConnectionException::explain_error(void) const { 
   return connect_error_map.at(connect_error);
}

/**
   InternalException Destructor.
*/
InternalException::~InternalException(void) throw() {
}

/**
   Returns explanation of error.
*/
const std::string InternalException::explain_error(void) const { 
   return internal_error_map.at(internal_error);
}

/**
   Throws out what the exception is.
*/
const char* InternalException::what() const throw() { 
   return "Internal Error";
}
} // error namespace 
} // comnet namespace 
