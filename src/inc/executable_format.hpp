#ifndef EXECUTABLE_FORMAT_H
#define EXECUTABLE_FORMAT_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "cpu.hpp"
#include "toolbox.hpp"
#include "section.hpp"

class ExecutableFormat
{
    public:

        /* The format RP++ handles */
        enum E_ExecutableFormat
        {
            FORMAT_PE,
            FORMAT_ELF,
            FORMAT_UNKNOWN
        };

        explicit ExecutableFormat(void);
        virtual ~ExecutableFormat(void);

        /* In your executable format, you can find the CPU used */
        virtual CPU* get_cpu(std::ifstream &file) = 0;

        /* Display the verbosity level */
        virtual void display_information(const VerbosityLevel lvl) const
        {
            std::cout << "Verbose level: " << verbosity_to_string(lvl) << std::endl;
        }

        /* Retrieves the class name, useful when using polymorphism */
        virtual std::string get_class_name(void) const = 0;

        /* Get the executable section of you binary ; it is there we will look for gadgets */
        virtual std::vector<Section*> get_executables_section(std::ifstream & file) = 0;

        /* 
            A very useful method to do the conversion raw_offset (relative to a section) to virtual address (which is absolute) 
            Example:
                offset = 0x10
                raw_section_offset = 0x100

                virtual_section_offset = 0x1000
                raw_offset_to_va(offset, 0x100) will return 0x1010
        */
        virtual unsigned long long raw_offset_to_va(const unsigned long long absolute_raw_offset, const unsigned long long absolute_raw_offset_section) const = 0;

        /* Find the executable format used -- based mostly on the magic signature */
        static E_ExecutableFormat FindExecutableFormat(unsigned int magic_dword);

    private:

        /* Fill the structures you need, parse your executable format to extract the useful information */
        virtual CPU::E_CPU extract_information_from_binary(std::ifstream &file) = 0;
};

#endif