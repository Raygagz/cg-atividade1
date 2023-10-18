#ifndef BALL_HPP_
#define BALL_HPP_

#include "abcgOpenGL.hpp"

class Ball {
public:
  void create(GLuint program);
  void paint();
  void destroy();

  glm::vec4 m_color{1};
  float m_scale{0.125f};
  glm::vec2 m_translation{};
  glm::vec2 m_velocity{};

private:
  int m_sides{36};
  GLint m_translationLoc{};
  GLint m_colorLoc{};
  GLint m_scaleLoc{};

  GLuint m_program{};
  GLuint m_VAO{};
  GLuint m_VBO{};
};
#endif