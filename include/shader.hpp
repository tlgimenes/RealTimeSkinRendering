/*
 * =====================================================================================
 *       Filename:  shader.hpp
 *    Description:  
 *        Created:  2015-02-11 16:55
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#ifndef SHADER_HPP
#define SHADER_HPP

////////////////////////////////////////////////////////////////////////////////////////

#include "error.hpp"

////////////////////////////////////////////////////////////////////////////////////////

class Shader 
{
    public:
        Shader ();
        virtual ~Shader ();

        /**
         * Loads both vertex and fragment shaders from fileName
         * */
        void load_from_file(const std::string& vertex_shader_filename,
                const std::string& fragment_shader_filename = "");

        /**
         * Binds shader
         * */
        inline void bind () {glUseProgram (_shader_program);}

        /**
         * Unbinds shader 
         * */
        inline void unbind () {glUseProgram (0);}

        inline bool has_vertex_shader   () const { return (_vertex_shader_size > 0); }
        inline bool has_fragment_shader () const { return (_fragment_shader_size > 0); }

        /**
         * Gets
         * */
        inline GLuint shader_program  () const {return _shader_program;}
        inline GLuint vertex_shader   () const {return _vertex_shader;}
        inline GLuint fragment_shader () const {return _fragment_shader;}

    protected:
        void read_shader_source (const std::string& shader_filename, std::string& shader_src);
        void compile_attach(GLuint & shader, GLenum type, const std::string& source);
        
        GLint get_uni_loc (const GLchar *name, GLuint program);
        inline GLint get_uni_loc(const GLchar *name) {return get_uni_loc(name, _shader_program);}
        
    private:
        GLuint _shader_program;
        GLuint _vertex_shader;
        GLuint _fragment_shader;
        unsigned int _vertex_shader_size;
        unsigned int _fragment_shader_size;

};

////////////////////////////////////////////////////////////////////////////////////////

#endif /* !SHADER_HPP */

////////////////////////////////////////////////////////////////////////////////////////

