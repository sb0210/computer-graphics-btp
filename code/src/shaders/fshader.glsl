#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform sampler2D texture;

varying vec2 v_texcoord;
varying vec4 v_color;
uniform float is_texture;

void main()
{
    // Set fragment color from texture
    if(true){
      gl_FragColor = texture2D(texture, v_texcoord);
    }
    else{

      gl_FragColor = v_color;
    }
}
//! [0]
