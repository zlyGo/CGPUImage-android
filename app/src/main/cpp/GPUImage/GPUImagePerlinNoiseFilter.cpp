/**
 * Created by lvHiei on 17-4-12.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImagePerlinNoiseFilter.h"


#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _perlinNoise_fragment_shader[] = SHADER_STR(
    precision highp float;
    varying highp vec2 textureCoordinate;
    uniform float scale;

    uniform vec4 colorStart;
    uniform vec4 colorFinish;

    //
    // Description : Array and textureless GLSL 2D/3D/4D simplex
    // noise functions.
    // Author : Ian McEwan, Ashima Arts.
    // Maintainer : ijm
    // Lastmod : 20110822 (ijm)
    // License : Copyright (C) 2011 Ashima Arts. All rights reserved.
    // Distributed under the MIT License. See LICENSE file.
    // https://github.com/ashima/webgl-noise
    //

    vec4 mod289(vec4 x)
    {
        return x - floor(x * (1.0 / 289.0)) * 289.0;
    }

    vec4 permute(vec4 x)
    {
        return mod289(((x*34.0)+1.0)*x);
    }

    vec4 taylorInvSqrt(vec4 r)
    {
        return 1.79284291400159 - 0.85373472095314 * r;
    }

    vec2 fade(vec2 t) {
        return t*t*t*(t*(t*6.0-15.0)+10.0);
    }

    // Classic Perlin noise
    float cnoise(vec2 P)
    {
        vec4 Pi = floor(P.xyxy) + vec4(0.0, 0.0, 1.0, 1.0);
        vec4 Pf = fract(P.xyxy) - vec4(0.0, 0.0, 1.0, 1.0);
        Pi = mod289(Pi); // To avoid truncation effects in permutation
        vec4 ix = Pi.xzxz;
        vec4 iy = Pi.yyww;
        vec4 fx = Pf.xzxz;
        vec4 fy = Pf.yyww;

        vec4 i = permute(permute(ix) + iy);

        vec4 gx = fract(i * (1.0 / 41.0)) * 2.0 - 1.0 ;
        vec4 gy = abs(gx) - 0.5 ;
        vec4 tx = floor(gx + 0.5);
        gx = gx - tx;

        vec2 g00 = vec2(gx.x,gy.x);
        vec2 g10 = vec2(gx.y,gy.y);
        vec2 g01 = vec2(gx.z,gy.z);
        vec2 g11 = vec2(gx.w,gy.w);

        vec4 norm = taylorInvSqrt(vec4(dot(g00, g00), dot(g01, g01), dot(g10, g10), dot(g11, g11)));
        g00 *= norm.x;
        g01 *= norm.y;
        g10 *= norm.z;
        g11 *= norm.w;

        float n00 = dot(g00, vec2(fx.x, fy.x));
        float n10 = dot(g10, vec2(fx.y, fy.y));
        float n01 = dot(g01, vec2(fx.z, fy.z));
        float n11 = dot(g11, vec2(fx.w, fy.w));

        vec2 fade_xy = fade(Pf.xy);
        vec2 n_x = mix(vec2(n00, n01), vec2(n10, n11), fade_xy.x);
        float n_xy = mix(n_x.x, n_x.y, fade_xy.y);
        return 2.3 * n_xy;
    }


    void main()
    {

        float n1 = (cnoise(textureCoordinate * scale) + 1.0) / 2.0;

        vec4 colorDiff = colorFinish - colorStart;
        vec4 color = colorStart + colorDiff * n1;

        gl_FragColor = color;
    }
);

#else

// 片元着色器
extern const char _perlinNoise_fragment_shader[] = SHADER_STR(
 precision mediump float;
 varying vec2 textureCoordinate;
 uniform float scale;

 uniform vec4 colorStart;
 uniform vec4 colorFinish;

 //
 // Description : Array and textureless GLSL 2D/3D/4D simplex
 // noise functions.
 // Author : Ian McEwan, Ashima Arts.
 // Maintainer : ijm
 // Lastmod : 20110822 (ijm)
 // License : Copyright (C) 2011 Ashima Arts. All rights reserved.
 // Distributed under the MIT License. See LICENSE file.
 // https://github.com/ashima/webgl-noise
 //

 vec4 mod289(vec4 x)
 {
 return x - floor(x * (1.0 / 289.0)) * 289.0;
 }

 vec4 permute(vec4 x)
 {
 return mod289(((x*34.0)+1.0)*x);
 }

 vec4 taylorInvSqrt(vec4 r)
 {
 return 1.79284291400159 - 0.85373472095314 * r;
 }

 vec2 fade(vec2 t) {
 return t*t*t*(t*(t*6.0-15.0)+10.0);
 }

 // Classic Perlin noise
 float cnoise(vec2 P)
 {
 vec4 Pi = floor(P.xyxy) + vec4(0.0, 0.0, 1.0, 1.0);
 vec4 Pf = fract(P.xyxy) - vec4(0.0, 0.0, 1.0, 1.0);
 Pi = mod289(Pi); // To avoid truncation effects in permutation
 vec4 ix = Pi.xzxz;
 vec4 iy = Pi.yyww;
 vec4 fx = Pf.xzxz;
 vec4 fy = Pf.yyww;

 vec4 i = permute(permute(ix) + iy);

 vec4 gx = fract(i * (1.0 / 41.0)) * 2.0 - 1.0 ;
 vec4 gy = abs(gx) - 0.5 ;
 vec4 tx = floor(gx + 0.5);
 gx = gx - tx;

 vec2 g00 = vec2(gx.x,gy.x);
 vec2 g10 = vec2(gx.y,gy.y);
 vec2 g01 = vec2(gx.z,gy.z);
 vec2 g11 = vec2(gx.w,gy.w);

 vec4 norm = taylorInvSqrt(vec4(dot(g00, g00), dot(g01, g01), dot(g10, g10), dot(g11, g11)));
 g00 *= norm.x;
 g01 *= norm.y;
 g10 *= norm.z;
 g11 *= norm.w;

 float n00 = dot(g00, vec2(fx.x, fy.x));
 float n10 = dot(g10, vec2(fx.y, fy.y));
 float n01 = dot(g01, vec2(fx.z, fy.z));
 float n11 = dot(g11, vec2(fx.w, fy.w));

 vec2 fade_xy = fade(Pf.xy);
 vec2 n_x = mix(vec2(n00, n01), vec2(n10, n11), fade_xy.x);
 float n_xy = mix(n_x.x, n_x.y, fade_xy.y);
 return 2.3 * n_xy;
 }

 void main()
 {

     float n1 = (cnoise(textureCoordinate * scale) + 1.0) / 2.0;

     vec4 colorDiff = colorFinish - colorStart;
     vec4 color = colorStart + colorDiff * n1;

     gl_FragColor = color;
 }
);

#endif




GPUImagePerlinNoiseFilter::GPUImagePerlinNoiseFilter()
    : GPUImageFilter(_perlinNoise_fragment_shader)
{
    m_fScale = 8.0f;

    m_pColorStart[0] = 0.0f;
    m_pColorStart[1] = 0.0f;
    m_pColorStart[2] = 0.0f;
    m_pColorStart[3] = 1.0f;

    m_pColorFinish[0] = 1.0f;
    m_pColorFinish[1] = 1.0f;
    m_pColorFinish[2] = 1.0f;
    m_pColorFinish[3] = 1.0f;

    m_iColorStartUniformLocation = -1;
    m_iColorFinishUniformLocation = -1;
    m_iScaleUniformLocation = -1;
}

GPUImagePerlinNoiseFilter::~GPUImagePerlinNoiseFilter()
{

}

void GPUImagePerlinNoiseFilter::setColorStart(float red, float green, float blue, float alpha)
{
    m_pColorStart[0] = red;
    m_pColorStart[1] = green;
    m_pColorStart[2] = blue;
    m_pColorStart[3] = alpha;
}

void GPUImagePerlinNoiseFilter::setColorFinish(float red, float green, float blue, float alpha)
{
    m_pColorFinish[0] = red;
    m_pColorFinish[1] = green;
    m_pColorFinish[2] = blue;
    m_pColorFinish[3] = alpha;
}

void GPUImagePerlinNoiseFilter::setScale(float scale)
{
    m_fScale = scale;
}

bool GPUImagePerlinNoiseFilter::createProgramExtra()
{
    m_iColorStartUniformLocation = glGetUniformLocation(m_uProgram, "colorStart");
    m_iColorFinishUniformLocation = glGetUniformLocation(m_uProgram, "colorFinish");
    m_iScaleUniformLocation = glGetUniformLocation(m_uProgram, "scale");
    return GPUImageFilter::createProgramExtra();
}

bool GPUImagePerlinNoiseFilter::beforeDrawExtra()
{
    glUniform1f(m_iScaleUniformLocation, m_fScale);
    glUniform4fv(m_iColorStartUniformLocation, 1, m_pColorStart);
    glUniform4fv(m_iColorFinishUniformLocation, 1, m_pColorFinish);

    return GPUImageFilter::beforeDrawExtra();
}




