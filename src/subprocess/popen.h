/**
 * @file
 */

#ifndef SNOWBALL_POPEN_H
#define SNOWBALL_POPEN_H

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/time.h>
#include<ext/stdio_filebuf.h>

#include <cstring>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>


namespace snowball
{
//forward declaration for friendship within Redirection class
class Popen;

/**
 * Redirection enables to select redirection of:
 *    - stdout
 *    - stderr
 *    - stdin
 * 
 * of the child process created by Popen objects.
 */

class Redirection
{
public:
    
    /**
     * Special targets
     *    - None: no redirection is applied
     *    - Stdout: redirection copies the one applied to stdout
     *    - Pipe: redirects to or from a pipe between parent and child process
     */
    enum class Target {None, Stdout, Pipe};

private:
    
    Target m_tgt = Target::None;
    std::ofstream* m_os = nullptr;
    std::ifstream* m_is = nullptr;
    int m_switch = 0;
    int m_fd = -1;

public:
    
    /**
     * Constructor
     * 
     * A redirection may be specified on a file or a specific
     * destination or source:
     *    - Target::None applies no redirection
     *    - Target::Stdout is used for redirection of stderr on 
     *      the same location that stdout redirection.
     *    - Target::Pipe creates a pipe between parent and child 
     *      process. This enables advanced control from the parent process
     * @param target redirection target
     */
    Redirection(Target target);
    
    /**
     * Constructor
     * 
     * A redirection may be specified on a file or a specific
     * destination or source:
     *    - Target::None applies no redirection
     *    - Target::Stdout is used for redirection of stderr on 
     *      the same location that stdout redirection.
     *    - Target::Pipe creates a pipe between parent and child 
     *      process. This enables advanced control from the parent process
     * @param target redirection target
     */
    Redirection(std::ofstream& target);
    
    /**
     * Constructor
     * 
     * A redirection may be specified on a file or a specific
     * destination or source:
     *    - Target::None applies no redirection
     *    - Target::Stdout is used for redirection of stderr on 
     *      the same location that stdout redirection.
     *    - Target::Pipe creates a pipe between parent and child 
     *      process. This enables advanced control from the parent process
     * @param target redirection target
     */
    Redirection(std::ifstream& target);
    
    /**
     * Copy constructor
     * @param other object copied from
     */
    Redirection(const Redirection& other);
    
    /**
     * Destructor
     */
    ~Redirection();
    
    /**
     * Assignment operator
     * @param other object assigned from
     */
    Redirection& operator=(const Redirection& other);
    
    /**
     * Stat whether current object is a redirection to an ofstream.
     */
    bool isOfStream() const;
    
    /**
     * Stat whether current object is a redirection from an ifstream.
     */
    bool isIfStream() const;
    
    /**
     * Stat whether current object is a redirection to the same target 
     * than stdout.
     */
    bool isStdout() const;
    
    /**
     * Stat whether current object is a redirection to or from a pipe
     * with parent process.
     */
    bool isPipe() const;
    
    /**
     * Stat whether current object has no redirection.
     */
    bool isNone() const;
    
    /**
     * Stat whether current object is a redirection to a special target.
     */
    bool isTarget() const;
    
    /**
     * Return underlying pointer to ofstream object.
     * If Redirection has been created on a Target or on an ifstream
     * a null pointer is returned.
     */
    std::ofstream* ofStream() const;
    
    /**
     * Return underlying pointer to ifstream object.
     * If Redirection has been created on a Target or on an ofstream
     * a null pointer is returned.
     */
    std::ifstream* ifStream() const;
    
    /**
     * Return underlying Target object.
     * If Redirection has been created on a ifstream or on an ofstream
     * a None Target object is returned.
     */
    Target target() const;
    
    /**
     * Return file descriptor.
     * In case pipe is not attached to a file descriptor yet or for any 
     * non-pipe redirection, this method returns an invalid file descriptor 
     * equal to -1
     * @return file descriptor aassociated to pipe
     */
    int fileDescriptor() const;
    
private:
    
    /**
     * Constructor
     * 
     * This constructor can only be called by Popen object. The redirection is 
     * a pipe for which a file descriptor has been already open.
     * This redirection is created when calling Popen::output method.
     * @param fildes file descriptor of open pipe
     */
    Redirection(int fildes);
    
friend Popen;

}; //end of Redirection class

static const Redirection NONE(Redirection::Target::None);
static const Redirection STDOUT(Redirection::Target::Stdout);
static const Redirection PIPE(Redirection::Target::Pipe);

class Popen
{
private:
    
    pid_t m_pid;      //process id of child process
    int m_returncode; //return code of child process
    int m_c2pwrite;   //child writes into stdout
    int m_errwrite;   //child writes into stderr
    int m_p2cread;    //child reads from stdin
    int m_c2pread;    //parent reads from child stdout
    int m_errread;    //parent reads from child stderr
    int m_p2cwrite;   //parent writes to child stdin

public:

    /**
     * Constructor
     * The command to be run has to be tokenized into a 
     * vector of string.
     * The constructor run a child process immediatly and 
     * is non-blocking.
     * @param args tokenized command line
     */
    Popen(const std::vector<std::string> args);

    /**
     * Constructor
     * The command to be run has to be tokenized into a 
     * vector of string.
     * The constructor run a child process immediatly and 
     * is non-blocking.
     * This constructor takes 3 Redirection objects as argument:
     *   - the first one is for stdout redirection
     *   - the second one is for stderr redirection
     *   - the last one is for stdin redirection
     * @param args tokenized command line
     * @param stdin child process stdin redirection
     * @param stdout child process stdout redirection
     * @param stderr child process stderr redirection
     */
    Popen(const std::vector<std::string> args, 
          const Redirection& stdin,
          const Redirection& stdout, 
          const Redirection& stderr);
    
    /**
     * Destructor
     */
    ~Popen();
    
    /**
     * Wait till the underlyind command terminates. It then 
     * returns the return code of associated child process.
     * The call to wait is blocking.
     * @return process return code
     */
    int wait();
    
    /**
     * Poll the underlying child process.
     * The return value is negative while child process is running.
     * Once the child process is terminated, the return code is returned
     * instead.
     * This method can be used in an infinite loop from calling program:
     * 
     *     Popen p(args);
     *     while (p.poll() < 0)
     *     {
     *         ///do what you need
     *     }
     * 
     * @return -1 if process is still running or positive return code when 
     * completed.
     */
    int poll();
    
    /**
     * This blocking method enables to communicate with the child process
     * created with Popen object. Once finished the process return code is 
     * returned.
     * @param stdin data to send to stdin of child process
     * @param stdout data retrieved from stdout of child process
     * @param stderr data retrieved from stderr of child process
     * @return child process return code
     * @warning In order to be able either to provide data to stdin or retrieve
     * data from stdout and stderr, you must specify 
     * Redirection::Target::Pipe redirection to the relevant channel.
     * 
     * An example of usage would be:
     * 
     *     Popen p(args, PIPE, PIPE, PIPE);
     *     std::string stdout, stderr;
     *     p.communicate("first value\nsecond value", stdout, stderr);
     *     
     */
    int communicate(const std::string& stdin, 
                     std::string& stdout, 
                     std::string& stderr);
    
    /**
     * This blocking method enables to communicate with the child process
     * created with Popen object. Once finished, the process return code is 
     * returned.
     * @param stdout data retrieved from stdout of child process
     * @param stderr data retrieved from stderr of child process
     * @return child process return code
     * @warning In order to be able either to provide data to stdin or retrieve
     * data from stdout and stderr, you must specify 
     * Redirection::Target::Pipe redirection to the relevant channel.
     * 
     * An example of usage would be:
     * 
     *     Popen p(args, NONE, PIPE, PIPE);
     *     std::string stdout, stderr;
     *     p.communicate(stdout, stderr);
     *     
     */
    int communicate(std::string& stdout, std::string& stderr);
    
    /**
     * Returns a pipe redirection object with associated file descriptor 
     * for stdout channel of Popen object. If Popen object has not be created
     * with a pipe redirection for stdout a none redirection object is returned
     * instead.
     */
    Redirection stdout() const;
    
    /**
     * Returns a pipe redirection object with associated file descriptor 
     * for stderr channel of Popen object. If Popen object has not be created
     * with a pipe redirection for stdout a none redirection object is returned
     * instead.
     */
    Redirection stderr() const;
    
private:
    /**
     * Copy constructor is private to avoid copies.
     * It make no sense to copy Popen objects as commands are immediatly 
     * invoked.
     */
    Popen(const Popen& other);
    
    /**
     * Assignment operator is also private to deactivate any attempt
     * of affecting one Popen object to another.
     * Commands are immediatly invoked, there is no reason to use assignement
     * operator.
     */
    Popen& operator=(const Popen& other);
    
    /**
     * Set handlers for redirections
     */
    void setHandlers(const Redirection& stdout, 
                     const Redirection& stderr, 
                     const Redirection& stdin);
    
    /**
     * Excecute child command
     * @param args tokenized command line
     */
    void executeChild(const std::vector<std::string> args);

    /**
     * Write data to pipe
     * @param fildes file descriptor of the pipe to write into
     * @param msg message to write into pipe
     * @return the number of bytes actually written to the pipe
     */
    static ssize_t writeToPipe(int fildes, const std::string& msg);

    /**
     * Read data from pipe
     * @param fildes file descriptor of the pipe to read from
     * @param msg message read from pipe will be appended to msg
     * @param buffer_size number of bytes to be read
     * @return the number of bytes actually readen from the pipe
     */
    static ssize_t readFromPipe(int fildes, 
                                std::string& msg, 
                                int buffer_size = 1024);
}; //end of Popen class

} //end of snowball namespace

/**
 * This utility function enables to convert a string in char*
 * as it is required to call the execvp.
 * @param str the string to be converted
 */
char* new_c_str_from_string(const std::string& str);

/**
 * This method is call to deallocate all char* created with
 * new_c_str_from_string.
 * @param ch pointer to be deallocated
 */
void delete_c_str(char* ch);

typedef std::basic_ofstream<char>::__filebuf_type buffer_t;
typedef __gnu_cxx::stdio_filebuf<char>            io_buffer_t; 
FILE* cfile_impl(buffer_t* const fb);

/**
 * These functions enables to get a FILE* from a C++ fstream.
 * This is required to be capable of having the fileno of that fstream.
 * Credits go to alfC on <a href="http://stackoverflow.com/a/19749019">Stack Overflow</a>
 * @param ofs ofstream
 */
FILE* cfile(std::ofstream const& ofs);

/**
 * These functions enables to get a FILE* from a C++ fstream.
 * This is required to be capable of having the fileno of that fstream.
 * Credits go to alfC on <a href="http://stackoverflow.com/a/19749019">Stack Overflow</a>
 * @param ofs ofstream
 */
FILE* cfile(std::ifstream const& ifs);

#endif
