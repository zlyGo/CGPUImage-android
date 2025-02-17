/**
* Created by lvHiei on 17-5-3.
* This is a project of GPUImage implemented with c++, you can
* use it free. if you find some bug please send me a email.
* My Email is majun_1523@163.com.
*/

#include "GPUImageRGBErosionFilter.h"


extern const char _dilationRadiusOne_vertex_shader[];
extern const char _dilationRadiusTwo_vertex_shader[];
extern const char _dilationRadiusThree_vertex_shader[];
extern const char _dilationRadiusFour_vertex_shader[];

#ifdef __GLSL_SUPPORT_HIGHP__


// 片元着色器
extern const char _rgbErosionRadiusOne_fragment_shader[] = SHADER_STR(
    precision highp float;

    varying vec2 centerTextureCoordinate;
    varying vec2 oneStepPositiveTextureCoordinate;
    varying vec2 oneStepNegativeTextureCoordinate;

    uniform sampler2D inputImageTexture;

    void main()
    {
        lowp vec4 centerIntensity = texture2D(inputImageTexture, centerTextureCoordinate);
        lowp vec4 oneStepPositiveIntensity = texture2D(inputImageTexture, oneStepPositiveTextureCoordinate);
        lowp vec4 oneStepNegativeIntensity = texture2D(inputImageTexture, oneStepNegativeTextureCoordinate);

        lowp vec4 minValue = min(centerIntensity, oneStepPositiveIntensity);

        gl_FragColor = min(minValue, oneStepNegativeIntensity);
    }
);


// 片元着色器
extern const char _rgbErosionRadiusTwo_fragment_shader[] = SHADER_STR(
    precision highp float;

    varying vec2 centerTextureCoordinate;
    varying vec2 oneStepPositiveTextureCoordinate;
    varying vec2 oneStepNegativeTextureCoordinate;
    varying vec2 twoStepsPositiveTextureCoordinate;
    varying vec2 twoStepsNegativeTextureCoordinate;

    uniform sampler2D inputImageTexture;

    void main()
    {
        lowp vec4 centerIntensity = texture2D(inputImageTexture, centerTextureCoordinate);
        lowp vec4 oneStepPositiveIntensity = texture2D(inputImageTexture, oneStepPositiveTextureCoordinate);
        lowp vec4 oneStepNegativeIntensity = texture2D(inputImageTexture, oneStepNegativeTextureCoordinate);
        lowp vec4 twoStepsPositiveIntensity = texture2D(inputImageTexture, twoStepsPositiveTextureCoordinate);
        lowp vec4 twoStepsNegativeIntensity = texture2D(inputImageTexture, twoStepsNegativeTextureCoordinate);

        lowp vec4 minValue = min(centerIntensity, oneStepPositiveIntensity);
        minValue = min(minValue, oneStepNegativeIntensity);
        minValue = min(minValue, twoStepsPositiveIntensity);

        gl_FragColor = min(minValue, twoStepsNegativeIntensity);
    }
);


// 片元着色器
extern const char _rgbErosionRadiusThree_fragment_shader[] = SHADER_STR(
    precision highp float;

    varying vec2 centerTextureCoordinate;
    varying vec2 oneStepPositiveTextureCoordinate;
    varying vec2 oneStepNegativeTextureCoordinate;
    varying vec2 twoStepsPositiveTextureCoordinate;
    varying vec2 twoStepsNegativeTextureCoordinate;
    varying vec2 threeStepsPositiveTextureCoordinate;
    varying vec2 threeStepsNegativeTextureCoordinate;

    uniform sampler2D inputImageTexture;

    void main()
    {
        lowp vec4 centerIntensity = texture2D(inputImageTexture, centerTextureCoordinate);
        lowp vec4 oneStepPositiveIntensity = texture2D(inputImageTexture, oneStepPositiveTextureCoordinate);
        lowp vec4 oneStepNegativeIntensity = texture2D(inputImageTexture, oneStepNegativeTextureCoordinate);
        lowp vec4 twoStepsPositiveIntensity = texture2D(inputImageTexture, twoStepsPositiveTextureCoordinate);
        lowp vec4 twoStepsNegativeIntensity = texture2D(inputImageTexture, twoStepsNegativeTextureCoordinate);
        lowp vec4 threeStepsPositiveIntensity = texture2D(inputImageTexture, threeStepsPositiveTextureCoordinate);
        lowp vec4 threeStepsNegativeIntensity = texture2D(inputImageTexture, threeStepsNegativeTextureCoordinate);

        lowp vec4 minValue = min(centerIntensity, oneStepPositiveIntensity);
        minValue = min(minValue, oneStepNegativeIntensity);
        minValue = min(minValue, twoStepsPositiveIntensity);
        minValue = min(minValue, twoStepsNegativeIntensity);
        minValue = min(minValue, threeStepsPositiveIntensity);

        gl_FragColor = min(minValue, threeStepsNegativeIntensity);
    }
);


// 片元着色器
extern const char _rgbErosionRadiusFour_fragment_shader[] = SHADER_STR(
    precision highp float;

    varying vec2 centerTextureCoordinate;
    varying vec2 oneStepPositiveTextureCoordinate;
    varying vec2 oneStepNegativeTextureCoordinate;
    varying vec2 twoStepsPositiveTextureCoordinate;
    varying vec2 twoStepsNegativeTextureCoordinate;
    varying vec2 threeStepsPositiveTextureCoordinate;
    varying vec2 threeStepsNegativeTextureCoordinate;
    varying vec2 fourStepsPositiveTextureCoordinate;
    varying vec2 fourStepsNegativeTextureCoordinate;

    uniform sampler2D inputImageTexture;

    void main()
    {
        lowp vec4 centerIntensity = texture2D(inputImageTexture, centerTextureCoordinate);
        lowp vec4 oneStepPositiveIntensity = texture2D(inputImageTexture, oneStepPositiveTextureCoordinate);
        lowp vec4 oneStepNegativeIntensity = texture2D(inputImageTexture, oneStepNegativeTextureCoordinate);
        lowp vec4 twoStepsPositiveIntensity = texture2D(inputImageTexture, twoStepsPositiveTextureCoordinate);
        lowp vec4 twoStepsNegativeIntensity = texture2D(inputImageTexture, twoStepsNegativeTextureCoordinate);
        lowp vec4 threeStepsPositiveIntensity = texture2D(inputImageTexture, threeStepsPositiveTextureCoordinate);
        lowp vec4 threeStepsNegativeIntensity = texture2D(inputImageTexture, threeStepsNegativeTextureCoordinate);
        lowp vec4 fourStepsPositiveIntensity = texture2D(inputImageTexture, fourStepsPositiveTextureCoordinate);
        lowp vec4 fourStepsNegativeIntensity = texture2D(inputImageTexture, fourStepsNegativeTextureCoordinate);

        lowp vec4 minValue = min(centerIntensity, oneStepPositiveIntensity);
        minValue = min(minValue, oneStepNegativeIntensity);
        minValue = min(minValue, twoStepsPositiveIntensity);
        minValue = min(minValue, twoStepsNegativeIntensity);
        minValue = min(minValue, threeStepsPositiveIntensity);
        minValue = min(minValue, threeStepsNegativeIntensity);
        minValue = min(minValue, fourStepsPositiveIntensity);

        gl_FragColor = min(minValue, fourStepsNegativeIntensity);
    }
);


#else


// 片元着色器
extern const char _rgbErosionRadiusOne_fragment_shader[] = SHADER_STR(
 precision mediump float;
 varying vec2 centerTextureCoordinate;
 varying vec2 oneStepPositiveTextureCoordinate;
 varying vec2 oneStepNegativeTextureCoordinate;

 uniform sampler2D inputImageTexture;

 void main()
 {
     vec4 centerIntensity = texture2D(inputImageTexture, centerTextureCoordinate);
     vec4 oneStepPositiveIntensity = texture2D(inputImageTexture, oneStepPositiveTextureCoordinate);
     vec4 oneStepNegativeIntensity = texture2D(inputImageTexture, oneStepNegativeTextureCoordinate);

     vec4 minValue = min(centerIntensity, oneStepPositiveIntensity);

     gl_FragColor = min(minValue, oneStepNegativeIntensity);
 }
);


// 片元着色器
extern const char _rgbErosionRadiusTwo_fragment_shader[] = SHADER_STR(
 precision mediump float;
 varying vec2 centerTextureCoordinate;
 varying vec2 oneStepPositiveTextureCoordinate;
 varying vec2 oneStepNegativeTextureCoordinate;
 varying vec2 twoStepsPositiveTextureCoordinate;
 varying vec2 twoStepsNegativeTextureCoordinate;

 uniform sampler2D inputImageTexture;

 void main()
 {
     vec4 centerIntensity = texture2D(inputImageTexture, centerTextureCoordinate);
     vec4 oneStepPositiveIntensity = texture2D(inputImageTexture, oneStepPositiveTextureCoordinate);
     vec4 oneStepNegativeIntensity = texture2D(inputImageTexture, oneStepNegativeTextureCoordinate);
     vec4 twoStepsPositiveIntensity = texture2D(inputImageTexture, twoStepsPositiveTextureCoordinate);
     vec4 twoStepsNegativeIntensity = texture2D(inputImageTexture, twoStepsNegativeTextureCoordinate);

     vec4 minValue = min(centerIntensity, oneStepPositiveIntensity);
     minValue = min(minValue, oneStepNegativeIntensity);
     minValue = min(minValue, twoStepsPositiveIntensity);

     gl_FragColor = min(minValue, twoStepsNegativeIntensity);
 }
);


// 片元着色器
extern const char _rgbErosionRadiusThree_fragment_shader[] = SHADER_STR(
 precision mediump float;
 varying vec2 centerTextureCoordinate;
 varying vec2 oneStepPositiveTextureCoordinate;
 varying vec2 oneStepNegativeTextureCoordinate;
 varying vec2 twoStepsPositiveTextureCoordinate;
 varying vec2 twoStepsNegativeTextureCoordinate;
 varying vec2 threeStepsPositiveTextureCoordinate;
 varying vec2 threeStepsNegativeTextureCoordinate;

 uniform sampler2D inputImageTexture;

 void main()
 {
     vec4 centerIntensity = texture2D(inputImageTexture, centerTextureCoordinate);
     vec4 oneStepPositiveIntensity = texture2D(inputImageTexture, oneStepPositiveTextureCoordinate);
     vec4 oneStepNegativeIntensity = texture2D(inputImageTexture, oneStepNegativeTextureCoordinate);
     vec4 twoStepsPositiveIntensity = texture2D(inputImageTexture, twoStepsPositiveTextureCoordinate);
     vec4 twoStepsNegativeIntensity = texture2D(inputImageTexture, twoStepsNegativeTextureCoordinate);
     vec4 threeStepsPositiveIntensity = texture2D(inputImageTexture, threeStepsPositiveTextureCoordinate);
     vec4 threeStepsNegativeIntensity = texture2D(inputImageTexture, threeStepsNegativeTextureCoordinate);

     vec4 minValue = min(centerIntensity, oneStepPositiveIntensity);
     minValue = min(minValue, oneStepNegativeIntensity);
     minValue = min(minValue, twoStepsPositiveIntensity);
     minValue = min(minValue, twoStepsNegativeIntensity);
     minValue = min(minValue, threeStepsPositiveIntensity);

     gl_FragColor = min(minValue, threeStepsNegativeIntensity);
 }
);


// 片元着色器
extern const char _rgbErosionRadiusFour_fragment_shader[] = SHADER_STR(
 precision mediump float;
 varying vec2 centerTextureCoordinate;
 varying vec2 oneStepPositiveTextureCoordinate;
 varying vec2 oneStepNegativeTextureCoordinate;
 varying vec2 twoStepsPositiveTextureCoordinate;
 varying vec2 twoStepsNegativeTextureCoordinate;
 varying vec2 threeStepsPositiveTextureCoordinate;
 varying vec2 threeStepsNegativeTextureCoordinate;
 varying vec2 fourStepsPositiveTextureCoordinate;
 varying vec2 fourStepsNegativeTextureCoordinate;

 uniform sampler2D inputImageTexture;

 void main()
 {
     vec4 centerIntensity = texture2D(inputImageTexture, centerTextureCoordinate);
     vec4 oneStepPositiveIntensity = texture2D(inputImageTexture, oneStepPositiveTextureCoordinate);
     vec4 oneStepNegativeIntensity = texture2D(inputImageTexture, oneStepNegativeTextureCoordinate);
     vec4 twoStepsPositiveIntensity = texture2D(inputImageTexture, twoStepsPositiveTextureCoordinate);
     vec4 twoStepsNegativeIntensity = texture2D(inputImageTexture, twoStepsNegativeTextureCoordinate);
     vec4 threeStepsPositiveIntensity = texture2D(inputImageTexture, threeStepsPositiveTextureCoordinate);
     vec4 threeStepsNegativeIntensity = texture2D(inputImageTexture, threeStepsNegativeTextureCoordinate);
     vec4 fourStepsPositiveIntensity = texture2D(inputImageTexture, fourStepsPositiveTextureCoordinate);
     vec4 fourStepsNegativeIntensity = texture2D(inputImageTexture, fourStepsNegativeTextureCoordinate);

     vec4 minValue = min(centerIntensity, oneStepPositiveIntensity);
     minValue = min(minValue, oneStepNegativeIntensity);
     minValue = min(minValue, twoStepsPositiveIntensity);
     minValue = min(minValue, twoStepsNegativeIntensity);
     minValue = min(minValue, threeStepsPositiveIntensity);
     minValue = min(minValue, threeStepsNegativeIntensity);
     minValue = min(minValue, fourStepsPositiveIntensity);

     gl_FragColor = min(minValue, fourStepsNegativeIntensity);
 }
);


#endif



GPUImageRGBErosionFilter::GPUImageRGBErosionFilter()
    : GPUImageTwoPassTextureSamplingFilter(_dilationRadiusOne_vertex_shader, _rgbErosionRadiusOne_fragment_shader, _dilationRadiusOne_vertex_shader, _rgbErosionRadiusOne_fragment_shader)
{

}

GPUImageRGBErosionFilter::GPUImageRGBErosionFilter(int radius)
    : GPUImageTwoPassTextureSamplingFilter(_dilationRadiusOne_vertex_shader, _rgbErosionRadiusOne_fragment_shader, _dilationRadiusOne_vertex_shader, _rgbErosionRadiusOne_fragment_shader)
{
    const char* vertexShaderForThisRadius = NULL;
    const char* fragmentShaderForThisRadius = NULL;
    switch (radius)
    {
        case 0:
        case 1:
        {
            vertexShaderForThisRadius = _dilationRadiusOne_vertex_shader;
            fragmentShaderForThisRadius = _rgbErosionRadiusOne_fragment_shader;
            break;
        }
        case 2:
        {
            vertexShaderForThisRadius = _dilationRadiusTwo_vertex_shader;
            fragmentShaderForThisRadius = _rgbErosionRadiusTwo_fragment_shader;
            break;
        }
        case 3:
        {
            vertexShaderForThisRadius = _dilationRadiusThree_vertex_shader;
            fragmentShaderForThisRadius = _rgbErosionRadiusThree_fragment_shader;
            break;
        }
        case 4:
        {
            vertexShaderForThisRadius = _dilationRadiusFour_vertex_shader;
            fragmentShaderForThisRadius = _rgbErosionRadiusFour_fragment_shader;
            break;
        }
        default:
        {
            vertexShaderForThisRadius = _dilationRadiusOne_vertex_shader;
            fragmentShaderForThisRadius = _rgbErosionRadiusOne_fragment_shader;
            break;
        }
    }

    resetShader(vertexShaderForThisRadius, fragmentShaderForThisRadius, vertexShaderForThisRadius, fragmentShaderForThisRadius);
}

GPUImageRGBErosionFilter::~GPUImageRGBErosionFilter() {

}

