uniform mat4 MVPMatrix;

attribute vec4 Position;

void main()
{
    gl_Position = MVPMatrix * Position;
}