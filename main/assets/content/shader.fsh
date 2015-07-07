precision mediump float;
uniform vec4 Colorv4;
void main()
{
    gl_FragColor = vec4(max(0.0, sin(gl_FragCoord.z*60.0)), 0.6, 0.1, 1.0);
}
