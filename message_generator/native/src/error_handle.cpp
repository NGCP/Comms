#include <error_handle.h>

#include <unordered_map>

namespace comnet {
namespace error { 

/**
   Operating system error map.
 */
std::unordered_map<OSErrors, char*> os_error_map = { 
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
std::unordered_map<ConnectErrors, char*> connect_error_map = { 
   _ERROR(error_no_connection_error, "No connection error."),
   _ERROR(error_con_unknown_error, "Unknown Error."),
   _ERROR(error_udp_error, "UDP error."),
   _ERROR(error_xbee_error, "Xbee error."),
   _ERROR(error_tcp_error, "TCP error."),
   _ERROR(error_socket_bind_fail, "Socket bind failed."),
   _ERROR(error_open_socket_fail, "Open socket failed."),
   _ERROR(error_socket_error, "Error in socket!"),
   _ERROR(error_invalid_handle, "Invalid handle."),
   _ERROR(error_com_state, "Error in Com state."),
   _ERROR(error_set_time_out, "Error in setting the time out."),
   _ERROR(error_connection_failed, "The connection to receiving end has failed."),
   _ERROR(error_socket_close_failed, "The connection failed to close."),
};

std::unordered_map<InternalErrors, char*> internal_error_map = {
   _ERROR(error_no_internal_error, "No internal error."),
   _ERROR(error_intern_unknown_error, "Unknown internal error."),
   _ERROR(error_internal_connection_error, "No live connection."),
   _ERROR(error_connection_already_established, "A connection was already established to the given node"),
   _ERROR(error_cannot_read_file, "Can not read file."),
   _ERROR(error_cannot_write_file, "Can not write into file."),
};

ConnectionException::ConnectionException(OSErrors os_err, 
                                         ConnectErrors conn_err) : 
                                         connect_error(conn_err), 
                                         AbsException(os_err) {
}

ConnectionException::ConnectionException(OSErrors os_err) : 
                                         connect_error(error_con_unknown_error),
                                         AbsException(os_err) {
}

ConnectionException::ConnectionException(ConnectErrors conn_err) : 
                                         ConnectionException(error_no_os,
                                                             conn_err) { 
}

InternalException::InternalException(OSErrors os_err,
                                     InternalErrors intern_err) : 
                                     internal_error(intern_err),
                                     AbsException(os_err) {
}

InternalException::InternalException(OSErrors os_err) : 
                                     InternalException(os_err, 
                                                       error_intern_unknown_error) {
}

InternalException::InternalException(InternalErrors intern_err) : 
                                     InternalException(error_no_os, 
                                                       intern_err) {
}

const std::string AbsException::get_os_error(void) { 
   return os_error_map.at(os_error);
}

// Destructor for the error handler class.
ConnectionException::~ConnectionException(void) { 
}

const char* ConnectionException::what() const throw() { 
   return "Connection Error";
}

const std::string ConnectionException::explain_error(void) const { 
   return connect_error_map.at(connect_error);
}

InternalException::~InternalException(void) {
}

const std::string InternalException::explain_error(void) const { 
   return internal_error_map.at(internal_error);
}

const char* InternalException::what() const throw() { 
   return "Internal Error";
}
} // error namespace 
} // comnet namespace 