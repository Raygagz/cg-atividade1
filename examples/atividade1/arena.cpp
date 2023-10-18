#include "arena.hpp"

void Arena::create(GLuint program) {
  destroy();

  m_program = program;

  m_colorLoc = abcg::glGetUniformLocation(m_program, "color");

  std::array<glm::vec2, 4> positions{
      // Arena
      glm::vec2{-0.5f, +0.5f},
      glm::vec2{-0.5f, -0.5f},
      glm::vec2{+0.5f, -0.5f},
      glm::vec2{+0.5f, +0.5f},
  };

  // Generate VBO
  abcg::glGenBuffers(1, &m_VBO);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  abcg::glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions.data(),
                     GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Get location of attributes in the program
  auto const positionAttribute{
      abcg::glGetAttribLocation(m_program, "inPosition")};

  // Create VAO
  abcg::glGenVertexArrays(1, &m_VAO);

  // Bind vertex attributes to current VAO
  abcg::glBindVertexArray(m_VAO);

  abcg::glEnableVertexAttribArray(positionAttribute);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  abcg::glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 0,
                              nullptr);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  // End of binding to current VAO
  abcg::glBindVertexArray(0);
}

void Arena::paint() {
  abcg::glUseProgram(m_program);

  abcg::glBindVertexArray(m_VAO);
  abcg::glUniform4f(m_colorLoc, 1, 1, 1, 1);

  abcg::glDrawArrays(GL_LINE_LOOP, 0, 4);

  abcg::glBindVertexArray(0);

  abcg::glUseProgram(0);
}

void Arena::destroy() {
  abcg::glDeleteBuffers(1, &m_VBO);
  abcg::glDeleteVertexArrays(1, &m_VAO);
}