#pragma once

// Window settings
constexpr int VIEWPORT_WIDTH = 1920;
constexpr int VIEWPORT_HEIGHT = 1080;
constexpr const char* WINDOW_TITLE = "Cubicity";

// Vertices for a cube (positions only)
static const float cubeVertices[] = {
    // Back face
    -0.5f, -0.5f, -0.5f, // 0
     0.5f, -0.5f, -0.5f, // 1
     0.5f,  0.5f, -0.5f, // 2
    -0.5f,  0.5f, -0.5f, // 3
    // Front face
    -0.5f, -0.5f,  0.5f, // 4
     0.5f, -0.5f,  0.5f, // 5
     0.5f,  0.5f,  0.5f, // 6
    -0.5f,  0.5f,  0.5f  // 7
};

// Indices for the element buffer object (EBO)
static const unsigned int cubeIndices[] = {
    // Back face
    0, 1, 2, 2, 3, 0,
    // Front face
    4, 5, 6, 6, 7, 4,
    // Left face
    0, 3, 7, 7, 4, 0,
    // Right face
    1, 5, 6, 6, 2, 1,
    // Bottom face
    0, 1, 5, 5, 4, 0,
    // Top face
    3, 2, 6, 6, 7, 3
};