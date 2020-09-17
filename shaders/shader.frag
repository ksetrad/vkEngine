#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec3 fragNormal;
layout(location = 2) in vec3 fragPos;

layout(location = 0) out vec4 outColor;


vec3 lightning_linear( vec3 normal, vec3 fragPos)
{
    /// Вычисляем вектор направления от освещаемого фрагмента к источнику света
    vec3 invLightDir = normalize(vec3(0,1,1));
    /// Вычисляем уровень освещенности дифузионной компоненты как косинус между нормалью фрагмента и направляющей на источник
    /// Т.к. освещенность не может быть отрицательной, то отрицательные косинусы зануляем.
    float diff = max(dot(normal, invLightDir), 0.0);
//    /// Вычисляем бликовую компоненту
//    vec3 viewDir = normalize(fragPos-camera_position);
//    vec3 halfwayDir = normalize(invLightDir+viewDir);
//    /// Считаем что коэффичиент блика не более 1.
//    float spec = min(pow(max(dot(normal, halfwayDir), 0.0), light_linear.shininess), 1.0);
//    /// Вычисляется свет от источника и добавляется общий уровень освещения
//    float shadow = ShadowCalculation(fragPosLightSpace, normal, -light_linear.direction);



    return (diff*vec3(0.8,0.8,0.8)) + vec3(0.2,0.2,0.2);
}


void main() {
    vec3 light = lightning_linear( fragNormal, fragPos);

    outColor = vec4(light, 1.0);
}