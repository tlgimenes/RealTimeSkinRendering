/*
 * =====================================================================================
 *       Filename:  parser.cpp
 *    Description:  
 *        Created:  2015-02-11 23:24
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#include "parser.hpp"
#include "error.hpp"

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <fstream>

////////////////////////////////////////////////////////////////////////////////////////

Parser::Parser(int argc, char* argv[])
{
    for(int i=1; i < argc; i++)
    {
        _argv << argv[i] << " ";
    }
}

////////////////////////////////////////////////////////////////////////////////////////

inline void Parser::print_help() const
{
    std::cout << HELP_STR << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////

void Parser::get_next_option(enum options_t& op, std::string& q)
{
    char option[MAX_INPUT_SIZE];

    _argv.getline(option, MAX_INPUT_SIZE, '-');
    _argv.getline(option, MAX_INPUT_SIZE, ' ');
    
    if(strcmp(option, "p") == 0) {
        _argv.getline(option, MAX_INPUT_SIZE, ' ');
        q = std::string(option);
        op = FILE_PATH;
    }
    else if(strcmp(option, "h") == 0) {
        op = PRINT_HELP;
    }
    else if(strcmp(option, "") == 0) {
        op = EOF_STRING;   
    }
    else {
        op = UNDEFINED_OPTION;
    }
}

////////////////////////////////////////////////////////////////////////////////////////
// Checks for invalid options
#define CHECK_INVALID_OPTIONS(string) \
    (void)(invalid_options(string) || (print_help(), exit(EXIT_FAILURE), 0))

////////////////////////////////////////////////////////////////////////////////////////
// Get program's options
void Parser::get_options(std::string& file_path)
{
    enum options_t opt;
    std::string file_path_aux;

    // Default values
    file_path = "../../models/blondGirl/ModelsFace.obj";

    // Read input
    while(!_argv.eof())
    {
        get_next_option(opt, file_path_aux);

        switch(opt)
        {
            case FILE_PATH:
                file_path = file_path_aux;
                break;
            case PRINT_HELP:
                print_help();
                exit(EXIT_SUCCESS);
                break;
            case EOF_STRING:
                CHECK_INVALID_OPTIONS(file_path);
                return;
            case UNDEFINED_OPTION:
            default:
                print_help();
                exit(EXIT_FAILURE);
        }
    }

    CHECK_INVALID_OPTIONS(file_path);
}

////////////////////////////////////////////////////////////////////////////////////////

bool Parser::invalid_options(std::string& file_path) const
{
    std::ifstream file(file_path, std::ios_base::in);

    return file;
}

////////////////////////////////////////////////////////////////////////////////////////
