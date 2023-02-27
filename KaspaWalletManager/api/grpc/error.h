#ifndef ERROR_H
#define ERROR_H

#include <string>
typedef struct {
    std::string Func; // Function name
    std::string Description; // Human readable description of the issue
}MessageError;

// Error satisfies the error interface and prints human-readable errors.
std::string Error(MessageError *e) {
    if( e->Func.compare("") ) {
        int length = std::snprintf(nullptr, 0, "%s: %s", e->Func.c_str(), e->Description.c_str() );
        char* str = new char[length+1]; // one more character for null terminator
        std::snprintf( str, length + 1, "%s: %s", e->Func.c_str(), e->Description.c_str() );
        std::string cppstr( str );
        delete[] str;
        return cppstr;
    }
    return e->Description;
}

// messageError creates an error for the given function and description.
MessageError messageError( std::string f, std::string desc ) {
    return MessageError{.Func = f, .Description = desc};
}

// RPCError represents an error arriving from the RPC
typedef struct {
    std::string Message;
} RPCError;

std::string Error(RPCError err) {
    return err.Message;
}

// RPCErrorf formats according to a format specifier and returns the string
// as an RPCError.
RPCError *RPCErrorf(std::string format, ...) {
    va_list args;
    va_start (args, format);
    int length = std::vsnprintf (NULL, 0, format.c_str(), args);
    char* buffer = new char[length+1]; // one more character for null terminator
    va_end (args);

    va_start (args, format);
    std::vsnprintf (buffer, length, format.c_str(), args);
    perror (buffer);
    va_end (args);
    std::string cppstr( buffer );
    delete[] buffer;
    RPCError *err = new RPCError;
    err->Message = cppstr;
    return err;
}

#endif // ERROR_H
