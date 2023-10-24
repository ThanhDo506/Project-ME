#version 460

void calculate_TilingAndOffset(vec2 UV, vec2 Tiling, vec2 Offset, out vec2 Out)
{
    Out = UV * Tiling + Offset;
}