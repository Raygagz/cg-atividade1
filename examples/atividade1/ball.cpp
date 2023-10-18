#include "ball.hpp"

void Ball::create(GLuint program) {
  destroy();

  m_program = program;

  m_translationLoc = abcg::glGetUniformLocation(m_program, "translation");
  m_colorLoc = abcg::glGetUniformLocation(m_program, "color");
  m_scaleLoc = abcg::glGetUniformLocation(m_program, "scale");

  m_translation = glm::vec2(0);
  m_velocity = glm::vec2(0);

  // Can be a problem if the number of sides is too high
  std::array<glm::vec2, 100> positions{};

  for (int i = 0; i < m_sides; i++) {
    positions[i] = glm::vec2{0.5f * std::cos(2 * M_PI * i / m_sides),
                             0.5f * std::sin(2 * M_PI * i / m_sides)};
  }

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

void Ball::paint() {
  abcg::glUseProgram(m_program);

  abcg::glBindVertexArray(m_VAO);
  abcg::glUniform4f(m_colorLoc, 1, 1, 1, 1);
  abcg::glUniform1f(m_scaleLoc, m_scale);

  abcg::glDrawArrays(GL_LINE_LOOP, 0, m_sides);

  abcg::glBindVertexArray(0);

  abcg::glUseProgram(0);
}

void Ball::destroy() {
  abcg::glDeleteBuffers(1, &m_VBO);
  abcg::glDeleteVertexArrays(1, &m_VAO);
}