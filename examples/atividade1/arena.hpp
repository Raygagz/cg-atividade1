#ifndef ARENA_HPP_
#define ARENA_HPP_

#include "abcgOpenGL.hpp"

class Arena {
public:
  void create(GLuint program);
  void paint();
  void destroy();

private:
  GLuint m_colorLoc{};

  GLuint m_program{};
  GLuint m_VAO{};
  GLuint m_VBO{};
};
#endif