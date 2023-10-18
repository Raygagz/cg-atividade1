#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <random>

#include "abcgOpenGL.hpp"

#include "arena.hpp"
#include "ball.hpp"

class Window : public abcg::OpenGLWindow {
protected:
  void onCreate() override;
  void onPaint() override;
  void onPaintUI() override;
  void onResize(glm::ivec2 const &size) override;
  void onDestroy() override;

private:
  glm::ivec2 m_viewportSize{};

  GLuint m_arenaProgram{};
  GLuint m_ballProgram{};

  Arena m_arena;
  Ball m_ball;

  abcg::Timer m_restartWaitTimer;

  ImFont *m_font{};

  std::default_random_engine m_randomEngine;

  void restart();
};

#endif