/**
 * Created by lvHiei on 17-5-5.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageGlassSphereFilter.h"


#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _glassSphere_fragment_shader[] = SHADER_STR(
    varying highp vec2 textureCoordinate;

    uniform sampler2D inputImageTexture;

    uniform highp vec2 center;
    uniform highp float radius;
    uniform highp float aspectRatio;
    uniform highp float refractiveIndex;
    // uniform vec3 lightPosition;
    const highp vec3 lightPosition = vec3(-0.5, 0.5, 1.0);
    const highp vec3 ambientLightPosition = vec3(0.0, 0.0, 1.0);

    void main()
    {
        highp vec2 textureCoordinateToUse = vec2(textureCoordinate.x, (textureCoordinate.y * aspectRatio + 0.5 - 0.5 * aspectRatio));
        highp float distanceFromCenter = distance(center, textureCoordinateToUse);
        lowp float checkForPresenceWithinSphere = step(distanceFromCenter, radius);

        distanceFromCenter = distanceFromCenter / radius;

        highp float normalizedDepth = radius * sqrt(1.0 - distanceFromCenter * distanceFromCenter);
        highp vec3 sphereNormal = normalize(vec3(textureCoordinateToUse - center, normalizedDepth));

        highp vec3 refractedVector = 2.0 * refract(vec3(0.0, 0.0, -1.0), sphereNormal, refractiveIndex);
        refractedVector.xy = -refractedVector.xy;

        highp vec3 finalSphereColor = texture2D(inputImageTexture, (refractedVector.xy + 1.0) * 0.5).rgb;

        // Grazing angle lighting
        highp float lightingIntensity = 2.5 * (1.0 - pow(clamp(dot(ambientLightPosition, sphereNormal), 0.0, 1.0), 0.25));
        finalSphereColor += lightingIntensity;

        // Specular lighting
        lightingIntensity  = clamp(dot(normalize(lightPosition), sphereNormal), 0.0, 1.0);
        lightingIntensity  = pow(lightingIntensity, 15.0);
        finalSphereColor += vec3(0.8, 0.8, 0.8) * lightingIntensity;

        gl_FragColor = vec4(finalSphereColor, 1.0) * checkForPresenceWithinSphere;
    }
);

#else

// 片元着色器
extern const char _glassSphere_fragment_shader[] = SHADER_STR(
    precision mediump float;
    varying vec2 textureCoordinate;

    uniform sampler2D inputImageTexture;

    uniform vec2 center;
    uniform float radius;
    uniform float aspectRatio;
    uniform float refractiveIndex;
    // uniform vec3 lightPosition;
    const vec3 lightPosition = vec3(-0.5, 0.5, 1.0);
    const vec3 ambientLightPosition = vec3(0.0, 0.0, 1.0);

    void main()
    {
     vec2 textureCoordinateToUse = vec2(textureCoordinate.x, (textureCoordinate.y * aspectRatio + 0.5 - 0.5 * aspectRatio));
     float distanceFromCenter = distance(center, textureCoordinateToUse);
     float checkForPresenceWithinSphere = step(distanceFromCenter, radius);

     distanceFromCenter = distanceFromCenter / radius;

     float normalizedDepth = radius * sqrt(1.0 - distanceFromCenter * distanceFromCenter);
     vec3 sphereNormal = normalize(vec3(textureCoordinateToUse - center, normalizedDepth));

     vec3 refractedVector = 2.0 * refract(vec3(0.0, 0.0, -1.0), sphereNormal, refractiveIndex);
     refractedVector.xy = -refractedVector.xy;

     vec3 finalSphereColor = texture2D(inputImageTexture, (refractedVector.xy + 1.0) * 0.5).rgb;

     // Grazing angle lighting
     float lightingIntensity = 2.5 * (1.0 - pow(clamp(dot(ambientLightPosition, sphereNormal), 0.0, 1.0), 0.25));
     finalSphereColor += lightingIntensity;

     // Specular lighting
     lightingIntensity  = clamp(dot(normalize(lightPosition), sphereNormal), 0.0, 1.0);
     lightingIntensity  = pow(lightingIntensity, 15.0);
     finalSphereColor += vec3(0.8, 0.8, 0.8) * lightingIntensity;

     gl_FragColor = vec4(finalSphereColor, 1.0) * checkForPresenceWithinSphere;
    }
);

#endif


GPUImageGlassSphereFilter::GPUImageGlassSphereFilter()
    : GPUImageSphereRefractionFilter(_glassSphere_fragment_shader)
{

}

GPUImageGlassSphereFilter::~GPUImageGlassSphereFilter() {

}

