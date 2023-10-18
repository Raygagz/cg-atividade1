#include "window.hpp"

void Window::onCreate() {
  auto const assetsPath{abcg::Application::getAssetsPath()};

  // Create shader program
  m_arenaProgram =
      abcg::createOpenGLProgram({{.source = assetsPath + "arena.vert",
                                  .stage = abcg::ShaderStage::Vertex},
                                 {.source = assetsPath + "arena.frag",
                                  .stage = abcg::ShaderStage::Fragment}});

  m_ballProgram = abcg::createOpenGLProgram(
      {{.source = assetsPath + "ball.vert", .stage = abcg::ShaderStage::Vertex},
       {.source = assetsPath + "ball.frag",
        .stage = abcg::ShaderStage::Fragment}});

  // Clear window
  abcg::glClearColor(0, 0, 0, 1);
  abcg::glClear(GL_COLOR_BUFFER_BIT);

  std::array<GLfloat, 2> sizes{};
#if !defined(__EMSCRIPTEN__)
  abcg::glEnable(GL_PROGRAM_POINT_SIZE);
  abcg::glGetFloatv(GL_POINT_SIZE_RANGE, sizes.data());
#else
  abcg::glGetFloatv(GL_ALIASED_POINT_SIZE_RANGE, sizes.data());
#endif

  // Start pseudorandom number generator
  auto const seed{std::chrono::steady_clock::now().time_since_epoch().count()};
  m_randomEngine.seed(seed);

  restart();
}

void Window::onPaint() {
  abcg::glClear(GL_COLOR_BUFFER_BIT);
  abcg::glViewport(0, 0, m_viewportSize.x, m_viewportSize.y);

  m_arena.paint();
  m_ball.paint();
}

void Window::onPaintUI() {
  abcg::OpenGLWindow::onPaintUI();

  {
    ImGui::SetNextWindowPos(ImVec2(5, 81));
    ImGui::Begin(" ", nullptr, ImGuiWindowFlags_NoDecoration);

    if (ImGui::Button("Restart", ImVec2(150, 30))) {
      abcg::glClear(GL_COLOR_BUFFER_BIT);
    }

    ImGui::End();
  }
}

void Window::onResize(glm::ivec2 const &size) {
  m_viewportSize = size;

  abcg::glClear(GL_COLOR_BUFFER_BIT);
}

void Window::onDestroy() {
  abcg::glDeleteProgram(m_arenaProgram);

  m_arena.destroy();
  m_ball.destroy();
}

void Window::restart() {
  m_arena.create(m_arenaProgram);
  m_ball.create(m_ballProgram);
}