#include "catch.hpp"

#include <stdio.h>

#include "subprocess/popen.h"

using namespace snowball;

class GenerateFile1
{
private:
    
    std::string m_filename;
    
public:
    
    GenerateFile1(const std::string& filename): m_filename(filename)
    {
        std::ofstream stream(m_filename);
        stream << "#!/bin/sh" << std::endl;
        stream << "exit 123" << std::endl;
        stream.close();
    };
    
    ~GenerateFile1()
    {
        remove(m_filename.c_str());
    };
};

class GenerateFile2
{
private:
    
    std::string m_filename;
    
public:
    
    GenerateFile2(const std::string& filename): m_filename(filename)
    {
        std::ofstream stream(m_filename);
        stream << "#!/bin/sh" << std::endl;
        stream << "sleep 5" << std::endl;
        stream.close();
    };
    
    ~GenerateFile2()
    {
        remove(m_filename.c_str());
    };
};

class GenerateFile3
{
private:
    
    std::string m_filename;
    
public:
    
    GenerateFile3(const std::string& filename): m_filename(filename)
    {
        std::ofstream stream(m_filename);
        stream << "#!/bin/sh" << std::endl;
        stream << "echo error 1 >&2 " << std::endl;
        stream << "echo out 1" << std::endl;
        stream << "echo error 2 >&2 " << std::endl;
        stream << "echo out 2" << std::endl;
        stream.close();
    };
    
    ~GenerateFile3()
    {
        remove(m_filename.c_str());
    };
};

class GenerateFile4
{
private:
    
    std::string m_filename;
    
public:
    
    GenerateFile4(const std::string& filename): m_filename(filename)
    {
        std::ofstream stream(m_filename);
        stream << "#!/bin/sh" << std::endl;
        stream << "echo Hello !" << std::endl;
        stream << "echo error sample >&2" << std::endl;
        stream << "echo -n What\\'s your name ? " << std::endl;
        stream << "read name" << std::endl;
        stream << "echo Nice to meet you ${name}" << std::endl;
        stream << "if [ -z ${name} ]; then" << std::endl;
        stream << "    exit 1" << std::endl;
        stream << "fi" << std::endl;
        stream.close();
    };
    
    ~GenerateFile4()
    {
        remove(m_filename.c_str());
    };
};

TEST_CASE("Redirection class", "[popen]")
{
    std::ofstream os;
    std::ifstream is;
    
    Redirection red_pipe = PIPE;
    Redirection red_none = NONE;
    Redirection red_stdout = STDOUT;
    Redirection red_ofstream(os);
    Redirection red_ifstream(is);
    
    SECTION("Pipe redirection")
    {
        REQUIRE (red_pipe.isNone() == false);
        REQUIRE (red_pipe.isPipe() == true);
        REQUIRE (red_pipe.isStdout() == false);
        REQUIRE (red_pipe.isOfStream() == false);
        REQUIRE (red_pipe.isIfStream() == false);
    }
    
    SECTION("None redirection")
    {
        REQUIRE (red_none.isNone() == true);
        REQUIRE (red_none.isPipe() == false);
        REQUIRE (red_none.isStdout() == false);
        REQUIRE (red_none.isOfStream() == false);
        REQUIRE (red_none.isIfStream() == false);
    }
    
    SECTION("Stdout redirection")
    {
        REQUIRE (red_stdout.isNone() == false);
        REQUIRE (red_stdout.isPipe() == false);
        REQUIRE (red_stdout.isStdout() == true);
        REQUIRE (red_stdout.isOfStream() == false);
        REQUIRE (red_stdout.isIfStream() == false);
    }
    
    SECTION("ofstream redirection")
    {
        REQUIRE (red_ofstream.isNone() == false);
        REQUIRE (red_ofstream.isPipe() == false);
        REQUIRE (red_ofstream.isStdout() == false);
        REQUIRE (red_ofstream.isOfStream() == true);
        REQUIRE (red_ofstream.isIfStream() == false);
    }
    
    SECTION("ifstream redirection")
    {
        REQUIRE (red_ifstream.isNone() == false);
        REQUIRE (red_ifstream.isPipe() == false);
        REQUIRE (red_ifstream.isStdout() == false);
        REQUIRE (red_ifstream.isOfStream() == false);
        REQUIRE (red_ifstream.isIfStream() == true);
    }
    
    SECTION("Copy constructor")
    {
        Redirection copy1(red_pipe);
        REQUIRE (copy1.isNone() == false);
        REQUIRE (copy1.isPipe() == true);
        REQUIRE (copy1.isStdout() == false);
        REQUIRE (copy1.isOfStream() == false);
        REQUIRE (copy1.isIfStream() == false);
        Redirection copy2(red_none);
        REQUIRE (copy2.isNone() == true);
        REQUIRE (copy2.isPipe() == false);
        REQUIRE (copy2.isStdout() == false);
        REQUIRE (copy2.isOfStream() == false);
        REQUIRE (copy2.isIfStream() == false);
        Redirection copy3(red_stdout);
        REQUIRE (copy3.isNone() == false);
        REQUIRE (copy3.isPipe() == false);
        REQUIRE (copy3.isStdout() == true);
        REQUIRE (copy3.isOfStream() == false);
        REQUIRE (copy3.isIfStream() == false);
        Redirection copy4(red_ofstream);
        REQUIRE (copy4.isNone() == false);
        REQUIRE (copy4.isPipe() == false);
        REQUIRE (copy4.isStdout() == false);
        REQUIRE (copy4.isOfStream() == true);
        REQUIRE (copy4.isIfStream() == false);
        Redirection copy5(red_ifstream);
        REQUIRE (copy5.isNone() == false);
        REQUIRE (copy5.isPipe() == false);
        REQUIRE (copy5.isStdout() == false);
        REQUIRE (copy5.isOfStream() == false);
        REQUIRE (copy5.isIfStream() == true);
    }
    
    SECTION("Assignment operator")
    {
        Redirection assign(Redirection::Target::None);
        assign = red_pipe;
        REQUIRE (assign.isNone() == false);
        REQUIRE (assign.isPipe() == true);
        REQUIRE (assign.isStdout() == false);
        REQUIRE (assign.isOfStream() == false);
        REQUIRE (assign.isIfStream() == false);
        assign = red_none;
        REQUIRE (assign.isNone() == true);
        REQUIRE (assign.isPipe() == false);
        REQUIRE (assign.isStdout() == false);
        REQUIRE (assign.isOfStream() == false);
        REQUIRE (assign.isIfStream() == false);
        assign = red_stdout;
        REQUIRE (assign.isNone() == false);
        REQUIRE (assign.isPipe() == false);
        REQUIRE (assign.isStdout() == true);
        REQUIRE (assign.isOfStream() == false);
        REQUIRE (assign.isIfStream() == false);
        assign = red_ofstream;
        REQUIRE (assign.isNone() == false);
        REQUIRE (assign.isPipe() == false);
        REQUIRE (assign.isStdout() == false);
        REQUIRE (assign.isOfStream() == true);
        REQUIRE (assign.isIfStream() == false);
        assign = red_ifstream;
        REQUIRE (assign.isNone() == false);
        REQUIRE (assign.isPipe() == false);
        REQUIRE (assign.isStdout() == false);
        REQUIRE (assign.isOfStream() == false);
        REQUIRE (assign.isIfStream() == true);        
    }
    
    SECTION("fileDescriptor method")
    {
        REQUIRE (red_pipe.target() 
            == Redirection::Target::Pipe);
        REQUIRE (red_stdout.target() 
            == Redirection::Target::Stdout);
        REQUIRE (red_none.target() 
            == Redirection::Target::None);
        REQUIRE (red_ofstream.target()
            == Redirection::Target::None);
        REQUIRE (red_ifstream.target()
            == Redirection::Target::None);
    }
    
    SECTION("ofStream method")
    {
        REQUIRE ((red_pipe.ofStream() == nullptr) == true);
        REQUIRE ((red_stdout.ofStream() == nullptr) == true);
        REQUIRE ((red_none.ofStream() == nullptr) == true);
        REQUIRE (red_ofstream.ofStream() == &os);
        REQUIRE ((red_ifstream.ofStream() == nullptr) == true);
    }
    
    SECTION("ifStream method")
    {
        REQUIRE ((red_pipe.ifStream() == nullptr) == true);
        REQUIRE ((red_stdout.ifStream() == nullptr) == true);
        REQUIRE ((red_none.ifStream() == nullptr) == true);
        REQUIRE ((red_ofstream.ifStream() == nullptr) == true);
        REQUIRE (red_ifstream.ifStream() == &is);
    }

}

TEST_CASE("Popen class", "[popen]")
{
    std::vector<std::string> args1 {"echo", "hello", "world"};
/*    args1.push_back("echo");
    args1.push_back("hello");
    args1.push_back("world");*/
    
    GenerateFile1 script1("script1.sh");
    
    std::vector<std::string> args2;
    args2.push_back("sh");
    args2.push_back("script1.sh");
    
    GenerateFile2 script2("script2.sh");
    
    std::vector<std::string> args3;
    args3.push_back("sh");
    args3.push_back("script2.sh");
    
    GenerateFile3 script3("script3.sh");
    
    std::vector<std::string> args4;
    args4.push_back("sh");
    args4.push_back("script3.sh");
    
    GenerateFile4 script4("script4.sh");
    
    std::vector<std::string> args5;
    args5.push_back("sh");
    args5.push_back("script4.sh");
    
    
    SECTION("No redirection")
    {
        Popen p(args1);
        p.wait();
        REQUIRE (p.poll() == 0);
    }
    
    SECTION("Error code")
    {
        Popen p(args2);
        REQUIRE (p.wait() == 123);
        REQUIRE (p.poll() == 123);
    }
    
    SECTION("wait method")
    {
        Popen p(args3);
        REQUIRE (p.wait() == 0);
    }
    
    SECTION("poll method")
    {
        Popen p(args3);
        while (p.poll() < 0) { }
        REQUIRE (p.poll() == 0);
    }
    
    SECTION("Redirection of stdout to ofstream")
    {
        std::ofstream ostream("tmp.log");
        Redirection red_stdout(ostream);
        Popen p(args4, NONE, red_stdout, NONE);
        p.wait();
        ostream.close();
        std::ifstream istream("tmp.log");
        std::string line;
        std::string fullmsg;
        while (std::getline(istream, line))
        {
            fullmsg += line;
            fullmsg += "\n";
        }
        REQUIRE (fullmsg.find("error 1") == std::string::npos);
        REQUIRE (fullmsg.find("error 2") == std::string::npos);
        REQUIRE (fullmsg.find("out 1") != std::string::npos);
        REQUIRE (fullmsg.find("out 2") != std::string::npos);
        istream.close();
    }

    SECTION("Redirection of stdout and stderr in separated ofstream's")
    {
        std::ofstream ostream1("stdout.log");
        std::ofstream ostream2("stderr.log");
        Redirection red_stdout(ostream1);
        Redirection red_stderr(ostream2);
        Popen p(args4, NONE, red_stdout, red_stderr);
        p.wait();
        ostream1.close();
        ostream2.close();
        std::vector<std::string> filenames;        
        filenames.push_back("stdout.log");
        filenames.push_back("stderr.log");
        for (unsigned int i = 0; i < filenames.size(); ++i)
        {
            std::ifstream stream(filenames[i]);
            std::string line;
            std::string fullmsg;
            while (std::getline(stream, line))
            {
                fullmsg += line;
                fullmsg += "\n";
            }
            stream.close();
            std::remove(filenames[i].c_str());
            if (i == 0)
            {
                REQUIRE (fullmsg.find("error 1") == std::string::npos);
                REQUIRE (fullmsg.find("error 2") == std::string::npos);
                REQUIRE (fullmsg.find("out 1") != std::string::npos);
                REQUIRE (fullmsg.find("out 2") != std::string::npos);
            }
            else if (i == 1)
            {
                REQUIRE (fullmsg.find("error 1") != std::string::npos);
                REQUIRE (fullmsg.find("error 2") != std::string::npos);
                REQUIRE (fullmsg.find("out 1") == std::string::npos);
                REQUIRE (fullmsg.find("out 2") == std::string::npos);                
            }
        }
    }
    
    SECTION("Redirection of stdout and stderr to the same ofstream")
    {
        std::ofstream ostream("tmp.log");
        Redirection red_stdout(ostream);
        Popen p(args4, NONE, red_stdout, STDOUT);
        p.wait();
        ostream.close();
        std::ifstream istream("tmp.log");
        std::string line;
        std::string fullmsg;
        while (std::getline(istream, line))
        {
            fullmsg += line;
            fullmsg += "\n";
        }
        REQUIRE (fullmsg.find("error 1") != std::string::npos);
        REQUIRE (fullmsg.find("error 2") != std::string::npos);
        REQUIRE (fullmsg.find("out 1") != std::string::npos);
        REQUIRE (fullmsg.find("out 2") != std::string::npos);
        istream.close();
        std::remove("tmp.log");
    }
    
    SECTION("Redirection of stdin from ifstream")
    {
        std::ofstream ostream("tmp.in");
        ostream << "Cédric" << std::endl;
        ostream.close();
        std::ifstream istream("tmp.in");
        Redirection red_stdin(istream);
        Popen p(args5, red_stdin, NONE, NONE);
        REQUIRE (p.wait() == 0);
        istream.close();
        std::remove("tmp.in");
    }
    
    SECTION("All redirections on")
    {
        std::ofstream ostream("tmp.in");
        ostream << "Cédric" << std::endl;
        ostream.close();
        std::ifstream istream("tmp.in");
        Redirection red_stdin(istream);
        ostream.open("tmp.log");
        Redirection red_stdout(ostream);
        Popen p(args5, red_stdin, red_stdout, STDOUT);
        REQUIRE (p.wait() == 0);
        ostream.close();
        istream.close();
        istream.open("tmp.log");
        std::string line;
        std::string fullmsg;
        while (getline(istream, line))
        {
            fullmsg += line;
            fullmsg += "\n";
        }
        REQUIRE (fullmsg.find("Hello !") != std::string::npos);
        REQUIRE (fullmsg.find("error sample") != std::string::npos);
        REQUIRE (fullmsg.find("What's your name ?") != std::string::npos);
        REQUIRE (fullmsg.find("Nice to meet you Cédric") != std::string::npos);       
        istream.close();
        std::remove("tmp.in");
        std::remove("tmp.log");
    }
    
    SECTION("Communicate without stdin")
    {
        Popen p(args4, NONE, PIPE, PIPE);
        std::string stdout;
        std::string stderr;
        REQUIRE (p.communicate(stdout, stderr) == 0);
        REQUIRE (stdout == "out 1\nout 2\n");
        REQUIRE (stderr == "error 1\nerror 2\n");
    }
    
    SECTION("Communicate with all redirections")
    {
        Popen p(args5, PIPE, PIPE, PIPE);
        std::string stdout;
        std::string stderr;
        REQUIRE (p.communicate("Cédric", stdout, stderr) == 0);
        REQUIRE (stdout 
            == "Hello !\nWhat's your name ?Nice to meet you Cédric\n");
        REQUIRE (stderr == "error sample\n");
    }
    
    SECTION("Communicate with all redirections and missing data")
    {
        Popen p(args5, PIPE, PIPE, PIPE);
        std::string stdout;
        std::string stderr;
        REQUIRE (p.communicate("", stdout, stderr) == 1);
    }
    
    SECTION("Pipe-connected Popen's")
    {
        std::vector<std::string> args1;
        args1.push_back("ls");
        std::vector<std::string> args2;
        args2.push_back("grep");
        args2.push_back("-c");
        args2.push_back(".sh");
        Popen p1(args1, NONE, PIPE, NONE);
        REQUIRE (p1.stdout().fileDescriptor() > 0);
        REQUIRE (p1.stdout().isPipe());
        //check copy
        Redirection red(p1.stdout());
        REQUIRE (red.fileDescriptor() > 0);
        REQUIRE (red.isPipe());        
        Popen p2(args2, p1.stdout(), PIPE, NONE);
        p1.wait();
        REQUIRE (p1.poll() == 0);
        std::string stdout;
        std::string stderr;
        REQUIRE (p2.communicate(stdout, stderr) == 0);
        REQUIRE (stdout == "4\n");
    }
}
