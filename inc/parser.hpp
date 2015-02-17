/*
 * =====================================================================================
 *       Filename:  parser.hpp
 *    Description:  
 *        Created:  2015-02-11 23:22
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#ifndef PARSER_HPP
#define PARSER_HPP

////////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <sstream>

////////////////////////////////////////////////////////////////////////////////////////

#define MAX_INPUT_SIZE 256

////////////////////////////////////////////////////////////////////////////////////////

#define HELP_STR \
"Usage: skinrenderer [OPTIONS] \n\
Options: \n\
  -p: Set the path to the 3D model \n\
  -h: Display this information \n\
\n\
Skin renderer - An skin engine based on the NVIDIA's skin rendering demo \n\
Authors: \n\
    Tiago Lobato Gimenes - (tlgimenes@gmail.com)\n" 

////////////////////////////////////////////////////////////////////////////////////////

enum options_t
{
    FILE_PATH,
    PRINT_HELP,
    EOF_STRING,
    UNDEFINED_OPTION
};
////////////////////////////////////////////////////////////////////////////////////////

class Parser
{
    private:
        std::stringstream _argv; // main's argv

    protected:
        void get_next_option(enum options_t&, std::string&);

        inline void print_help() const;

        /**
         * @arg0: program option file_path
         * @return: True if there is an invalid options
         * */
        bool invalid_options(std::string& file_path) const;

    public:
        Parser(int argc, char* argv[]);

        /**
         * Get the program options from the argv. If you want to add any new
         * parameter for the program, add this parameter here !
         * */
        void get_options(std::string& file_path);

        /* 
         * Gets 
         * */
        inline const std::stringstream& argv() const {return _argv;}

        /**
         * Sets 
         *  */
        inline std::stringstream& argv() {return _argv;}
};

////////////////////////////////////////////////////////////////////////////////////////

#endif /* !PARSER_HPP */

////////////////////////////////////////////////////////////////////////////////////////

