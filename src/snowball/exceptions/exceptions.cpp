#include "exceptions.h"


using namespace std;
using namespace snowball;


//=============================================================================
// Exception class
//=============================================================================

//Constructor

Exception::Exception(string msg): m_message(msg)
{
    m_function = "";
    m_filename = "";
    m_lineno = 0;
}

Exception::Exception(string msg, string file, string func, int lineno): 
    m_message(msg), m_function(func), m_filename(file), m_lineno(lineno) {}

//Destructor

Exception::~Exception() { }

//Methods

const string Exception::get_function() const
{
    return m_function;
}

const string Exception::get_filename() const
{
    return m_filename;
}

const int Exception::get_lineno() const
{
    return m_lineno;
}

const bool Exception::is_extended() const
{
    return m_lineno != 0;
}

const string Exception::get_message() const
{
    return m_message;
}

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

//=============================================================================
// KeyError
//=============================================================================

//Constructor

KeyError::KeyError(string msg): Exception(msg) {}

KeyError::KeyError(string msg, string filename, string func, int lineno): 
    Exception(msg, filename, func, lineno) {}

//Destructor
KeyError::~KeyError() {}
