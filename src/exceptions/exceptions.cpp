#include "exceptions.h"


using namespace std;
using namespace snowball;


//=============================================================================
// BaseException class
//=============================================================================

//Constructor

BaseException::BaseException(string msg): message(msg)
{
    function = "";
    filename = "";
    lineno = 0;
}

BaseException::BaseException(string msg, string file, string func, int lineno): 
    message(msg), function(func), filename(file), lineno(lineno) {}

//Destructor

BaseException::~BaseException() { }

//Methods

const string BaseException::get_function() const
{
    return function;
}

const string BaseException::get_filename() const
{
    return filename;
}

const int BaseException::get_lineno() const
{
    return lineno;
}

const bool BaseException::is_extended() const
{
    return lineno != 0;
}

const string BaseException::get_message() const
{
    return message;
}

//=============================================================================
// Exception
//=============================================================================

//Constructor

Exception::Exception(string msg): Exception(msg) {}

Exception::Exception(string msg, string filename, string func, int lineno): 
    BaseException(msg, filename, func, lineno) {}
    
//Destructor
Exception::~Exception() {}

//what method
const char* Exception::what() const noexcept
{
    string msg;
    if (!is_extended())
        msg = get_message();
    else
    {
        msg =  get_message() + string(" {") + get_filename() + string(":") + 
               get_function() + string(":") + to_string(get_lineno()) + 
               string("}");
    }
    return msg.c_str();
}

//=============================================================================
// IndexError
//=============================================================================

//Constructor

IndexError::IndexError(string msg): Exception(msg) {}

IndexError::IndexError(string msg, string filename, string func, int lineno): 
    Exception(msg, filename, func, lineno) {}
    
//Destructor
IndexError::~IndexError() {}

//=============================================================================
// ValueError
//=============================================================================

//Constructor

ValueError::ValueError(string msg): Exception(msg) {}

ValueError::ValueError(string msg, string filename, string func, int lineno): 
    Exception(msg, filename, func, lineno) {}

//Destructor
ValueError::~ValueError() {}
