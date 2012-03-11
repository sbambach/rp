#include <iostream>
#include <exception>

#include "coloshell.hpp"
#include "platform.h"
#include "program.hpp"
#include "beadisassembler.hpp"

#define NUM_V "1.3.3.7"

#ifdef ARCH_X64
#define VERSION_TMP NUM_V " x64 built the " __DATE__ " " __TIME__
#else
#define VERSION_TMP NUM_V " x86 built the " __DATE__ " " __TIME__
#endif

#ifdef WINDOWS
#define VERSION_TM VERSION_TMP " for Windows"
#else
#define VERSION_TM VERSION_TMP " for Unix"
#endif

#ifdef _DEBUG
#define VERSION VERSION_TM " (Debug)."
#else
#define VERSION VERSION_TM " (Release)."
#endif

void display_version()
{
    std::cout << "VERSION: " << VERSION << std::endl;
}

void display_usage()
{
    std::cout << "USAGE: ./rp++ <file>\n" << std::endl;
}

int main(int argc, char* argv[])
{
    display_version();

    if(argc != 2)
    {
        display_usage();
        return -1;
    }
    
    std::string program_path(argv[1]);
    try
    {
        Program p(program_path);
        p.display_information(VERBOSE_LEVEL_3);

        p.find_and_display_gadgets();
    }
    catch(const std::exception &e)
    {
        enable_color(COLO_RED);
        std::cout << e.what() << std::endl;
        disable_color();
    }

    return 0;
}