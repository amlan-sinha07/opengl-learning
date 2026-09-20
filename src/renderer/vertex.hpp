#pragma once

struct Vertex {
    float x{0.0f};
    float y{0.0f};
    float z{0.0f};

    float nx{0.0f};
    float ny{0.0f};
    float nz{0.0f};

    float u{0.0f};
    float v{0.0f};

    Vertex() = default;

    Vertex(
        float px, float py, float pz,   //position
        float pnx, float pny, float pnz, //color
        float pu, float pv              //texture
    )
        : x{px}, y{py}, z{pz},
          nx{pnx}, ny{pny}, nz{pnz},
          u{pu}, v{pv}
    {
    }
};