#include <iostream>

#include "popen.h"

using namespace snowball;

//=============================================================================
// Redirection class
//=============================================================================

/*
 * Constructors
 */

Redirection::Redirection(Target target)
    : m_switch(0), m_tgt(target) { }

Redirection::Redirection(std::ofstream& target)
    : m_switch(1), m_os(&target) { }

Redirection::Redirection(std::ifstream& target)
    : m_switch(2), m_is(&target) { }
    
Redirection::Redirection(int fildes)
    : m_switch(0), m_tgt(Redirection::Target::Pipe), m_fd(fildes) { }

Redirection::Redirection(const Redirection& other)
    : m_switch(other.m_switch), m_tgt(other.m_tgt), m_os(other.m_os), 
    m_is(other.m_is), m_fd(other.m_fd) { }

/*
 * Destructor
 */

Redirection::~Redirection() { }

/*
 * Assignment operator
 */

Redirection& Redirection::operator=(const Redirection& other)
{
    m_switch = other.m_switch;
    m_tgt = other.m_tgt;
    m_is = other.m_is;
    m_os = other.m_os;
    m_fd = other.m_fd;
    return *this;
}

/*
 * Methods: isIfStream, isOsStream, isTarget
 */

bool Redirection::isIfStream() const
{
    return m_switch == 2;
}

bool Redirection::isOfStream() const
{
    return m_switch == 1;
}

bool Redirection::isTarget() const
{
    return m_switch == 0;
}

/*
 * Methods: isStdout, isPipe, isNone
 */

bool Redirection::isStdout() const
{
    if (!isTarget())
        return false;
    else
        return m_tgt == Target::Stdout;
}

bool Redirection::isPipe() const
{
    if (!isTarget())
        return false;
    else
        return m_tgt == Target::Pipe;
}

bool Redirection::isNone() const
{
    if (!isTarget())
        return false;
    else
        return m_tgt == Target::None;
}

/*
 * Method: ofStream
 */

std::ofstream* Redirection::ofStream() const
{
    return m_os;
}

/*
 * Method: ifStream
 */

std::ifstream* Redirection::ifStream() const
{
    return m_is;
}

/*
 * Method: target
 */

Redirection::Target Redirection::target() const
{
    return m_tgt;
}

/*
 * Method: fileDescriptor
 */
int Redirection::fileDescriptor() const
{
    return m_fd;
}


//=============================================================================
// Static variables
//=============================================================================

const Redirection snowball::NONE(Redirection::Target::None);
const Redirection snowball::STDOUT(Redirection::Target::Stdout);
const Redirection snowball::PIPE(Redirection::Target::Pipe);

//=============================================================================
// Popen class
//=============================================================================

/*
 * Constructors
 */

Popen::Popen(const std::vector<std::string> args)
{
    setHandlers(NONE, NONE, NONE);
    executeChild(args);
}

Popen::Popen(const std::vector<std::string> args, 
             const Redirection& stdin,
             const Redirection& stdout, 
             const Redirection& stderr)
             
{
    setHandlers(stdin, stdout, stderr);
    executeChild(args);
}

/*
 * Destructor
 */

Popen::~Popen() { }

/*
 * Method: setHandlers
 */

void Popen::setHandlers(const Redirection& stdin,
                        const Redirection& stdout, 
                        const Redirection& stderr)
{
    //initialisation
    m_c2pwrite = 0;
    m_errwrite = 0;
    m_p2cread = 0;
    m_c2pread = 0;
    m_errread = 0;
    m_p2cwrite = 0;
    //stdout: m_c2pwrite
    if (stdout.isNone())
        m_c2pwrite = 0;
    else if (stdout.isOfStream())
        m_c2pwrite = fileno(cfile(*stdout.ofStream()));
    else if (stdout.isPipe())
    {
        //read part of the pipe is for parent and write part for child
        int fildes[2] = {0, 0};
        pipe(fildes);
        m_c2pread = fildes[0];
        m_c2pwrite = fildes[1];
    }
    else
        m_c2pwrite = 0;
    //stderr: m_errwrite
    if (stderr.isNone())
        m_errwrite = 0;
    else if (stderr.isOfStream())
        m_errwrite = fileno(cfile(*stderr.ofStream()));
    else if (stderr.isStdout())
        m_errwrite = m_c2pwrite;
    else if (stderr.isPipe())
    {
        //read part of the pipe is for parent and write part for child
        int fildes[2] = {0, 0};
        pipe(fildes);
        m_errread = fildes[0];
        m_errwrite = fildes[1];
    }
    else
        m_errwrite = 0;
    //stdin
    if (stdin.isNone())
        m_p2cread = 0;
    else if (stdin.isIfStream())
        m_p2cread = fileno(cfile(*stdin.ifStream()));
    else if (stdin.isPipe())
    {
        int fd = stdin.fileDescriptor();
        if (fd > 0)
        {
            //fd is the file descriptor of first process pipe
            m_p2cread = fd;
            m_p2cwrite = 0;
        }
        else
        {
            //we create a new pipe
            //read part is for child and write part for parent
            int fildes[2];
            pipe(fildes);
            m_p2cread = fildes[0];
            m_p2cwrite = fildes[1];            
        }
    }
    else
        m_p2cread = 0;
}

/*
 * Method executeChild
 */

void Popen::executeChild(const std::vector<std::string> args)
{
    m_returncode = -1;
    m_pid = fork();
    if (m_pid == 0) //child "forked" process
    {
        //close parent's pipe end
        if (m_c2pread)
            close(m_c2pread);
        if (m_p2cwrite)
            close(m_p2cwrite);
        if (m_errread)
            close(m_errread);
        //duplicate file descriptors
        if (m_c2pwrite)
            dup2(m_c2pwrite, 1);
        if (m_errwrite)
            dup2(m_errwrite, 2);
        if (m_p2cread)
            dup2(m_p2cread, 0);
        //close duplicated file descriptors
        if (m_c2pwrite)
            close(m_c2pwrite);
        if (m_errwrite)
            close(m_errwrite);
        if (m_p2cread)
            close(m_p2cread);
//        std::string command;
//        std::vector<std::string>::const_iterator it;
//        for (it = args.begin(); it != args.end(); ++it)
//        {
//            command.append(*it);
//            command.append(" ");
//        }
//        int err = system(command.c_str());
        char* argv[args.size() + 1];
        std::vector<std::string>::const_iterator it;
        int i = 0;
        for(it = args.begin(); it != args.end(); ++it)
        {
            argv[i++] = new_c_str_from_string(*it);
        }
        argv[i] = nullptr;
        int err = 0;
        /*std::ofstream log("test.log", std::ofstream::app);
        for (i = 0; i < args.size(); ++i)
        {
            log << argv[i] << " ";
        }
        log << std::endl;
        log.close();*/
        err = execvp(argv[0], argv);
        for(int j = 0; j < args.size(); ++j)
        {
            delete_c_str(argv[j]);
        }
       exit(EXIT_SUCCESS);
       exit(err);
    }
    //parent only
    //close child's pipe end
    if (m_p2cread)
        close(m_p2cread);
    if (m_c2pwrite)
        close(m_c2pwrite);
    if (m_errwrite)
        close(m_errwrite);
}

/*
 * Method: wait
 */

int Popen::wait()
{
    int status = 0;
    if (m_returncode < 0)
    {
        pid_t err = waitpid(m_pid, &status, 0);
        if (WIFEXITED(status))
            m_returncode = WEXITSTATUS(status);
    }
    return m_returncode;
}

/*
 * Method: poll
 */

int Popen::poll()
{
    int status = 0;
    pid_t err = waitpid(m_pid, &status, WNOHANG);
    //err = 0 means the child process is still running
    //err = m_pid if child process is over
    //err = -1 if another waitpid already captured termination of child
    if (err == m_pid)
    {
        if (WIFEXITED(status))
            m_returncode = WEXITSTATUS(status);
    }
    return m_returncode;
}

/*
 * Method: communicate
 */

int Popen::communicate(const std::string& stdin,
                 std::string& stdout,
                 std::string& stderr)
{
    //Define sets for select invokation, we want to monitor
    // - stdin (m_p2cwrite)
    // - stdout (m_c2pread)
    // - stderr (m_errread)
    fd_set rfds;             //holds the set for select (monitored read fds)
    fd_set wfds;             //holds the set for select (monitored write fds)
    int nfds;                //maximum file descriptor + 1
    struct timeval tv;       //timeout for select
    int retval;              //return value for select
    bool monitor_stdin = (m_p2cwrite > 0);
    bool monitor_stdout = (m_c2pread > 0);
    bool monitor_stderr = (m_errread > 0);
    //Other initialisations
    size_t input_offset = 0;
    size_t str_end = 0;
    //Monitoring loop
    while (monitor_stdin || monitor_stdout || monitor_stderr) 
    {
        //reset select parameters
        tv.tv_sec = 5;       //timeout is set to 5 seconds...
        tv.tv_usec = 0;      //... and 0 microsecond
        FD_ZERO(&rfds);
        FD_ZERO(&wfds);
        nfds = std::max(std::max(m_p2cwrite, m_c2pread), m_errread) + 1;
        if (monitor_stdin)
            FD_SET(m_p2cwrite, &wfds);
        if (monitor_stdout)
            FD_SET(m_c2pread, &rfds);
        if (monitor_stderr)
            FD_SET(m_errread, &rfds);
        //reset strings for stdout and stderr
        std::string msg_stdout("");
        std::string msg_stderr("");
        //wait for notification of change
        retval = select(nfds, &rfds, &wfds, nullptr, &tv);
        if (retval > 0)
        {
            //at least one is available
            if (monitor_stdin && FD_ISSET(m_p2cwrite, &wfds))
            {
                //stdin is available
                //only sends 512 bytes
                str_end = input_offset + 512;
                if (str_end > stdin.size())
                    str_end = std::string::npos;
                std::string sub = stdin.substr(input_offset, str_end);
                ssize_t written = writeToPipe(m_p2cwrite, sub);
                input_offset += written;
                if (input_offset >= stdin.size())
                {
                    //all data has been sent to pipe
                    monitor_stdin = false;
                    close(m_p2cwrite);
                }
            } //stdin is available
            if (monitor_stdout && FD_ISSET(m_c2pread, &rfds))
            {
                //stdout is available
                ssize_t readen = readFromPipe(m_c2pread, stdout);
                if (readen == 0)
                {
                    //pipe has been closed on children side
                    monitor_stdout = false;
                    close(m_c2pread);
                }
            } //stdout is available
            if (monitor_stderr && FD_ISSET(m_errread, &rfds))
            {
                //stderr is available
                ssize_t readen = readFromPipe(m_errread, stderr);
                if (readen == 0)
                {
                    //pipe has been closed on children side
                    monitor_stderr = false;
                    close(m_errread);
                }
            } //stderr is available
        } // retval > 0
    } //end of monitoring loop
    //we ensure that method returns when child has terminated
    while (poll() < 0)
        sleep(0.1);
    return poll(); //enables to get the return code
}

int Popen::communicate(std::string& stdout, std::string& stderr)
{
    //Define sets for select invokation, we want to monitor
    // - stdout (m_c2pread)
    // - stderr (m_errread)
    fd_set rfds;             //holds the set for select (monitored read fds)
    int nfds;                //maximum file descriptor + 1
    struct timeval tv;       //timeout for select
    int retval;              //return value for select
    bool monitor_stdout = (m_c2pread > 0);
    bool monitor_stderr = (m_errread > 0);
    //Monitoring loop
    while (monitor_stdout || monitor_stderr)
    {
        //reset select parameters
        tv.tv_sec = 5;       //timeout is set to 5 seconds...
        tv.tv_usec = 0;      //... and 0 microsecond
        FD_ZERO(&rfds);
        nfds = std::max(m_c2pread, m_errread) + 1;
        if (monitor_stdout)
            FD_SET(m_c2pread, &rfds);
        if (monitor_stderr)
            FD_SET(m_errread, &rfds);
        //reset strings for stdout and stderr
        std::string msg_stdout("");
        std::string msg_stderr("");
        //wait for notification of change
        retval = select(nfds, &rfds, nullptr, nullptr, &tv);
        if (retval > 0)
        {
            //at least one is available
            if (monitor_stdout && FD_ISSET(m_c2pread, &rfds))
            {
                //stdout is available
                ssize_t readen = readFromPipe(m_c2pread, stdout);
                if (readen == 0)
                {
                    //pipe has been closed on children side
                    monitor_stdout = false;
                    close(m_c2pread);
                }
            } //stdout is available
            if (monitor_stderr && FD_ISSET(m_errread, &rfds))
            {
                //stderr is available
                ssize_t readen = readFromPipe(m_errread, stderr);
                if (readen == 0)
                {
                    //pipe has been closed on children side
                    monitor_stderr = false;
                    close(m_errread);
                }
            } //stderr is available
        } // retval > 0
    } //end of monitoring loop
    //we ensure that method returns when child has terminated
    while (poll() < 0)
        sleep(0.1); 
    return poll(); //enables to get the return code
}

/*
 * Method: stdout
 */

Redirection Popen::stdout() const
{
    if (m_c2pread > 0)
    {
        //stdout is connected to a pipe
        return Redirection(m_c2pread);
    }
    else
        return Redirection(Redirection::Target::None);
}

/*
 * Method: stderr
 */

Redirection Popen::stderr() const
{
    if (m_errread > 0)
    {
        //stderr is connected to a pipe
        return Redirection(m_errread);
    }
    else
        return Redirection(Redirection::Target::None);
}

//==============================================================================
// Utilities
//==============================================================================

char* new_c_str_from_string(const std::string& str)
{
    char* c_str = new char[str.length()+1];
    std::copy(str.begin(), str.end(), c_str);
    c_str[str.length()] = '\0';
    return c_str;
}

void delete_c_str(char* c_str)
{
    delete[] c_str;
}

FILE* cfile_impl(buffer_t* const fb)
{
    return (static_cast<io_buffer_t* const>(fb))->file(); //type std::__c_file
}

FILE* cfile(std::ofstream const& ofs)
{
    return cfile_impl(ofs.rdbuf());
}

FILE* cfile(std::ifstream const& ifs)
{
    return cfile_impl(ifs.rdbuf());
}

ssize_t Popen::writeToPipe(int fildes, const std::string& msg)
{
    const char* buf = msg.c_str();
    ssize_t written = write(fildes, buf, strlen(buf) + 1);
    return written;
}

ssize_t Popen::readFromPipe(int fildes, std::string& msg, const int buffer_size)
{
    char buf[buffer_size + 1];
    ssize_t readen = read(fildes, buf, buffer_size);
    buf[readen] = '\0';
    msg += buf;
    return readen;
}

//==============================================================================
// Tests kept for posterity ;D
//==============================================================================

//same as Popen::writeToPipe, but to make it available for unit testing
ssize_t writeToPipe(int fildes, const std::string& msg)
{
    const char* buf = msg.c_str();
    ssize_t written = write(fildes, buf, strlen(buf) + 1);
    return written;
}

//same as Popen::readFromPipe, but to make it available for unit testing
ssize_t readFromPipe(int fildes, std::string& msg, const int buffer_size=1024)
{
    char buf[buffer_size + 1];
    ssize_t readen = read(fildes, buf, buffer_size);
    buf[readen] = '\0';
    msg += buf;
    return readen;
}

void test1()
{
    int fildes[2] = {0, 0};
    int err;
    err = pipe(fildes);
    std::cout << "pipe read = " << fildes[0] << " write = " << fildes[1]
        << std::endl;
    pid_t pid = fork();
    if (pid == 0)
    {
        std::cout << "child = " << pid << std::endl;
        close(fildes[0]);
        writeToPipe(fildes[1], "hello from child!\t");
        close(fildes[1]);
        exit(EXIT_SUCCESS);
    }
    else
    {
        std::cout << "parent = " << pid << std::endl;
        close(fildes[1]);
        std::string msg;
        readFromPipe(fildes[0], msg);
        std::cout << "parent gets = " << msg << std::endl;
        close(fildes[0]);
    }
}

void test2()
{
    int fildes[2] = {0, 0};
    int err;
    err = pipe(fildes);
    std::cout << "pipe read = " << fildes[0] << " write = " << fildes[1]
        << std::endl;
    pid_t pid = fork();
    if (pid == 0)
    {
        std::cout << "child = " << pid << std::endl;
        close(fildes[0]);
        writeToPipe(fildes[1], "hello from child!");
        close(fildes[1]);
        exit(EXIT_SUCCESS);
    }
    else
    {
        std::cout << "parent = " << pid << std::endl;
        close(fildes[1]);
        std::string msg;
        while(readFromPipe(fildes[0], msg, 2) > 0) { }
        std::cout << "parent gets = " << msg << std::endl;
        close(fildes[0]);
    }
}

void test3()
{
    int fildes[2] = {0, 0};
    int err;
    err = pipe(fildes);
    std::cout << "pipe read = " << fildes[0] << " write = " << fildes[1] 
        << std::endl;
    pid_t pid = fork();
    if (pid == 0)
    {
        std::cout << "child = " << pid << std::endl;
        close(fildes[0]);
        sleep(2);
        writeToPipe(fildes[1], "hello from child!\n");
        sleep(2);
        writeToPipe(fildes[1], "second line of text\n");
        sleep(4);
        writeToPipe(fildes[1], "third line of text\n");
        sleep(1);
        writeToPipe(fildes[1], "final line of text\n");
        close(fildes[1]);
        exit(EXIT_SUCCESS);
    }
    else
    {
        std::cout << "parent = " << pid << std::endl;
        close(fildes[1]);
        std::string msg;
        fd_set rfds;
        int nfds;
        int retval;
        struct timeval tv;
        while (true)
        {
            //configure select
            nfds = fildes[0] + 1;
            FD_ZERO(&rfds);
            std::cout << fildes[0] << std::endl;
            FD_SET(fildes[0], &rfds);
            tv.tv_sec = 1;
            tv.tv_usec = 0;
            //invoke select
            retval = select(nfds, &rfds, nullptr, nullptr, &tv);
            std::cout << "retval = " << retval << std::endl;
            if (retval > 0)
            {
                if (FD_ISSET(fildes[0], &rfds))
                {
                    ssize_t readen = readFromPipe(fildes[0], msg);
                    std::cout << "msg = " << msg << std::endl;
                    if (readen == 0)
                        break;
                }
            }
            else if (retval < 0)
            {
                if (errno == EBADF)
                {
                    std::cout << "EBADF exception" << std::endl;
                    close(fildes[0]);
                    break;
                }
            }
            sleep(1);
        }
        close(fildes[0]);
    }
}

void test4()
{
    int fildes_in[2] = {0, 0};
    int fildes_out[2] = {0, 0};
    int err;
    err = pipe(fildes_in);
    err = pipe(fildes_out);
    std::cout << "pipe in read = " << fildes_in[0] << " write = "
        << fildes_in[1] << std::endl;
    std::cout << "pipe out read = " << fildes_out[0] << " write = "
        << fildes_out[1] << std::endl;
    //fildes_in[0] => read stdin from child
    //fildes_in[1] => write stdin from parent
    //fildes_out[0] => read stdout from parent
    //fildes_out[1] => write stdout from child
    pid_t pid = fork();
    if (pid == 0)
    {
        //child
        //we close parent's pipe ends
        close(fildes_in[1]);
        close(fildes_out[0]);
        //we connect the stdin to the pipe
        dup2(fildes_in[0], 0);
        close(fildes_in[0]);
        //we connect the stdout to the pipe
        dup2(fildes_out[1], 1);
        close(fildes_out[1]);
        //let's start
        //data sent to cout is actually sent to the pipe
        std::cout << "Running child..." << std::endl;
        sleep(2);
        std::cout << "Enter a variable name: ";
        std::string name;
        //data collected from cin is actually coming from the pipe
        std::cin >> name;
        sleep(2);
        std::cout << "Enter a value for variable " << name << ": ";
        int value = 123;
        std::cin >> value;
        sleep(2);
        std::cout << "You have entered: " << value << std::endl;
        std::cout << "End of program" << std::endl;
        exit(EXIT_SUCCESS);
    }
    else
    {
        //parent
        //we close children's pipe ends
        close(fildes_in[0]);
        close(fildes_out[1]);
        //set variables for select loop
        std::string msg;
        fd_set rfds, wfds;
        bool monitor_stdin = true;
        bool monitor_stdout = true;
        int nfds;
        int retval;
        struct timeval tv;
        while (monitor_stdin || monitor_stdout)
        {
            //reset select parameters
            tv.tv_sec = 5;
            tv.tv_usec = 0;
            FD_ZERO(&rfds);
            FD_ZERO(&wfds);
            if (monitor_stdin)
                FD_SET(fildes_in[1], &wfds);
            if (monitor_stdout)
                FD_SET(fildes_out[0], &rfds);
            nfds = std::max(fildes_in[1], fildes_out[0]) + 1;
            //wait for modification on pipe
            retval = select(nfds, &rfds, &wfds, nullptr, &tv);
            if (retval > 0)
            {
                //something is available !
                if (FD_ISSET(fildes_in[1], &wfds))
                {
                    //stdin is available
                    ssize_t written = writeToPipe(fildes_in[1], 
                                                  "toto\n4012");
                    monitor_stdin = false;
                }
                if (FD_ISSET(fildes_out[0], &rfds))
                {
                    //stdout is available
                    ssize_t readen = readFromPipe(fildes_out[0], msg);
                    if (readen == 0)
                    {
                        //pipe has been closed on children side
                        monitor_stdout = false;
                    }
                }
            }
            else if (retval < 0)
            {
                //error !
                close(fildes_in[1]);
                close(fildes_out[0]);
                break;
            }
        }
        std::cout << msg;
        close(fildes_in[1]);
        close(fildes_out[0]);
    }
}

void test5()
{
    Redirection rstdout = Redirection(Redirection::Target::Pipe);
    Redirection rstderr = Redirection(Redirection::Target::Pipe);
    Redirection rstdin = Redirection(Redirection::Target::Pipe);
    std::vector<std::string> args;
    args.push_back("test.sh");
    Popen p(args, rstdin, rstdout, rstderr);
    std::string stdout;
    std::string stderr;
    int rcode = p.communicate("toto\n4012", stdout, stderr);
    std::cout << rcode << std::endl;
    std::cout << stderr;
    std::cout << stdout;
}

void test6()
{
    Redirection rstdout = Redirection(Redirection::Target::Pipe);
    Redirection rstderr = Redirection(Redirection::Target::Stdout);
    Redirection rstdin = Redirection(Redirection::Target::Pipe);
    std::vector<std::string> args;
    args.push_back("test.sh");
    Popen p(args, rstdin, rstdout, rstderr);
    std::string stdout;
    std::string stderr;
    int rcode = p.communicate("toto\n4012", stdout, stderr);
    std::cout << rcode << std::endl;
    std::cout << stdout;
}

