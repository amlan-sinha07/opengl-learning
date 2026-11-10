# opengl-learning

OpenGL learning project. C++23, OpenGL 4.5 core, GLSL 450 core, GLFW, GLAD, GLM.

## Building

```bash
g++ -std=c++23 -Wall -Wextra -Wpedantic -O0 -g -DDEBUG \
    -Isrc src/main.cpp src/*/*.cpp src/*/*/*.cpp \
    -lGL -lglfw -lglad -o bin/test
```

Adjust the include and library paths for wherever GLAD and GLFW are installed.

Run from the repo root, the shaders are loaded by relative path.

## Layout

```
src/
├── main.cpp                    entry point and render loop
├── app/                        Application
├── core/
│   ├── debugging/              GL error checking
│   └── logging/                logger
├── platform/window.cpp         GLFW window, GL context, monitor setup
└── renderer/
    ├── buffers/                VBO, EBO, VAO, buffer layout
    ├── mesh/                   Vertex, Mesh
    ├── rendering/              Renderer, GLHelper
    └── shader/                 Shader
```

Every raw GL call lives in `renderer/rendering/gl_helper.cpp`.

## Shaders

`shaders/vertex.vert` and `shaders/fragment.frag` take a position and a color per
vertex and pass the color straight through to the fragment shader. Both use `#version 450 core`.

## Math

Math lives in the external **GLM** library, included as `<glm/glm.hpp>`. The project
does not ship its own vector types any more.

`glm::vec2`, `glm::vec3` and `glm::vec4` all share one operator set: arithmetic, component
wise `*`, `dot`, `length`, `normalized`, `distance`, `lerp`, and `cross` on `glm::vec3`.
Layout matches the GLSL `vec2`/`vec3`/`vec4` types so no conversion is needed when
uploading to the GPU.

`lerp` does not clamp `t`, values outside `[0, 1]` extrapolate. `operator==` compares
exactly, use an epsilon for float results.

`glm::vec3` is used for positions, colors and normals alike, which keeps the vertex
struct and the GLSL `vec3` in exact agreement. `glm::vec3` is 12 bytes, `glm::vec4` is
16 bytes, and both line up with the matching GLSL components.

The pulse interpolation goes through the `glm::lerp` free function (from
`glm::gtx::compatibility`, which needs `GLM_ENABLE_EXPERIMENTAL`), not a member
function. `glm::to_string` for printing comes from `glm::gtx::string_cast`, also under
that flag.

## Vertex layout

```cpp
struct MeshVertex {
    glm::vec3 Position;   // offset 0
    glm::vec3 Color;      // offset 12
    glm::vec3 Normal;     // offset 24
};                      // 36 bytes, stride 36
```

`BufferLayout` computes element offsets and the stride from the element list using
member pointers. `Mesh` move operations are disabled.

## Rendering

All raw GL calls go through `GLHelper`. Buffer and VAO creation use Direct State Access (DSA)
where possible (`glCreateBuffers`, `glNamedBufferData`, `glNamedBufferSubData`, `glCreateVertexArrays`).

### Renderer API

```cpp
Renderer Renderer;

// Set clear color
Renderer.clear_color({0.1f, 0.1f, 0.1f, 1.0f});

// Clear with specified bit masks (OR'd together)
Renderer.clear_bits(GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT);

// Draw a mesh with a shader
Renderer.draw(Rectangle, Shader);
```

`clear_bits` is variadic and ORs all provided masks together. `clear_color` sets the clear
color via `glClearColor`. `GLHelper` splits clearing into `clearColor` and `clearMask`.

### VAO setup (DSA)

`attachLayoutToVAO` configures vertex attributes directly on the VAO by ID using:
- `glVertexArrayVertexBuffer` to bind the VBO to a binding slot with the layout stride
- `glEnableVertexArrayAttrib`, `glVertexArrayAttribFormat`, `glVertexArrayAttribBinding` to describe each attribute
- `glVertexArrayElementBuffer` attaches the EBO to the VAO in the draw path

Redundant context bindings like `glBindVertexArray` and `glBindBuffer` are commented out with
notes explaining the difference between object state (DSA) and context binding state (legacy).
The old bind-to-edit paths remain commented for learning/comparison.

### Window

The window is created on the primary monitor with work area queried via `glfwGetMonitorWorkarea`.
OpenGL debug context is enabled. Framebuffer resize updates the viewport.
