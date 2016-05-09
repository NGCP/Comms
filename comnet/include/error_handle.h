//-----------------------------------------------------
// EXCEPTION HANDLER FILE.
//
//
//
//
//
//
//-----------------------------------------------------
#ifndef _ERROR_HANDLE_H_
#define _ERROR_HANDLE_H_
#pragma once

#include <exception>
#include <iostream>
#include <stdint.h>

#define DISALLOW_EVIL_CONSTRUCTORS(object_constructor) object_constructor(void) { }
#define _ERROR(m, e, str) m[e] = str; // { e, str }

namespace comnet {
namespace error { 

/**
 Operating System errors, Tells the type of error on the operating 
 system.
*/
enum OSErrors {
   error_no_os,
   error_windows = 0x4FF,
   error_wsa_service,
   error_linux,
   error_unix,
   error_mac,
};

/** 
 Connection Errors enumerator to handle connection type
 errors.
*/ 
enum ConnectErrors {
   error_no_connection_error = 0x0,
   error_con_unknown_error,
   error_udp_error,
   error_xbee_error,
   error_xbee_error_new_connection,
   error_xbee_error_init,
   error_xbee_error_close,
   error_tcp_error,
   error_socket_bind_fail,
   error_open_socket_fail,
   error_socket_error,
   error_invalid_handle,
   error_com_state,
   error_set_time_out,
   error_connection_failed,
   error_socket_close_failed,
   error_already_connected,
};

enum InternalErrors {
   error_no_internal_error = 0x0,
   error_intern_unknown_error,
   error_internal_connection_error,
   error_connection_already_established,
   error_cannot_read_file,
   error_cannot_write_file,
   error_invalid_hex_string,
};

/**
 Abstract Error handle. Unit testing purposes.
*/ 
class AbsException : public std::exception { 
protected:
   OSErrors os_error;
public:
   AbsException(void) : os_error(error_no_os) { }
   AbsException(OSErrors os_err) : os_error(os_err) { }
   virtual ~AbsException(void) throw() { }

   const std::string get_os_error(void);

   virtual const char* what() const throw() { return "abs error"; }
   virtual const std::string explain_error(void) const = 0;
   virtual int32_t get_type(void) const = 0;
private:
};

/**
   Connection Error handler.
*/
class ConnectionException : public AbsException {
   ConnectErrors connect_error;
public:
   ConnectionException(OSErrors os_err);
   ConnectionException(ConnectErrors conn_err);
   ConnectionException(OSErrors os_err, ConnectErrors conn_err);
   ~ConnectionException(void) throw();

   const char* what() const throw();
   const std::string explain_error(void) const;
   int32_t get_type(void) const { return connect_error; }
private:
   DISALLOW_EVIL_CONSTRUCTORS(ConnectionException)
};

/**
   Internal Error handler.
*/
class InternalException : public AbsException {
   InternalErrors internal_error;
public:
   InternalException(OSErrors os_err);
   InternalException(InternalErrors intern_err);
   InternalException(OSErrors os_err, InternalErrors intern_err);
   ~InternalException(void) throw();

   const char* what() const throw();
   const std::string explain_error(void) const;
   int32_t get_type(void) const { return internal_error; }
private:
   DISALLOW_EVIL_CONSTRUCTORS(InternalException)
};

} // error namespace 
} // comnet namespace 


#endif /* _ERROR_HANDLE_H_ */
