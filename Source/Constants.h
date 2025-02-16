#pragma once

// Window settings
constexpr int VIEWPORT_WIDTH = 1920;
constexpr int VIEWPORT_HEIGHT = 1080;
constexpr const char* WINDOW_TITLE = "Cubicity";

// Vertices for a cube (positions only)
static const float CUBE_VERTICES[] = {
    // Back face
    -0.5f, -0.5f, -0.5f, // 0
     0.5f, -0.5f, -0.5f, // 1
     0.5f,  0.5f, -0.5f, // 2
    -0.5f,  0.5f, -0.5f, // 3
    // Front face
    -0.5f, -0.5f,  0.5f, // 4
     0.5f, -0.5f,  0.5f, // 5
     0.5f,  0.5f,  0.5f, // 6
    -0.5f,  0.5f,  0.5f, // 7
    // Left face
    -0.5f, -0.5f, -0.5f, // 8
    -0.5f,  0.5f, -0.5f, // 9
    -0.5f,  0.5f,  0.5f, // 10
    -0.5f, -0.5f,  0.5f, // 11
    // Right face
     0.5f, -0.5f, -0.5f, // 12
     0.5f,  0.5f, -0.5f, // 13
     0.5f,  0.5f,  0.5f, // 14
     0.5f, -0.5f,  0.5f, // 15
     // Bottom face
     -0.5f, -0.5f, -0.5f, // 16
      0.5f, -0.5f, -0.5f, // 17
      0.5f, -0.5f,  0.5f, // 18
     -0.5f, -0.5f,  0.5f, // 19
     // Top face
     -0.5f,  0.5f, -0.5f, // 20
      0.5f,  0.5f, -0.5f, // 21
      0.5f,  0.5f,  0.5f, // 22
     -0.5f,  0.5f,  0.5f  // 23
};

// Texture coordinates for a cube
static const float CUBE_TEXTURE_COORDINATES[] = {
    // Back face
    0.0f, 0.0f, // 0
    1.0f, 0.0f, // 1
    1.0f, 1.0f, // 2
    0.0f, 1.0f, // 3
    // Front face
    0.0f, 0.0f, // 4
    1.0f, 0.0f, // 5
    1.0f, 1.0f, // 6
    0.0f, 1.0f, // 7
    // Left face
    0.0f, 0.0f, // 8
    1.0f, 0.0f, // 9
    1.0f, 1.0f, // 10
    0.0f, 1.0f, // 11
    // Right face
    0.0f, 0.0f, // 12
    1.0f, 0.0f, // 13
    1.0f, 1.0f, // 14
    0.0f, 1.0f, // 15
    // Bottom face
    0.0f, 0.0f, // 16
    1.0f, 0.0f, // 17
    1.0f, 1.0f, // 18
    0.0f, 1.0f, // 19
    // Top face
    0.0f, 0.0f, // 20
    1.0f, 0.0f, // 21
    1.0f, 1.0f, // 22
    0.0f, 1.0f  // 23
};

// Indices for the element buffer object (EBO)
static const unsigned int CUBE_INDICES[] = {
    // Back face
    0, 1, 2, 2, 3, 0,
    // Front face
    4, 5, 6, 6, 7, 4,
    // Left face
    8, 9, 10, 10, 11, 8,
    // Right face
    12, 13, 14, 14, 15, 12,
    // Bottom face
    16, 17, 18, 18, 19, 16,
    // Top face
    20, 21, 22, 22, 23, 20
};