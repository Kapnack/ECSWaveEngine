#version 330 core

in vec3 vNearPoint;
in vec3 vFarPoint;

uniform mat4 uView;
uniform mat4 uProj;

uniform vec4  uMatColor;
uniform vec3  uPlaneNormal;
uniform float uPlaneOriginDistance;
uniform vec3  uCameraPos;
uniform float uFadeDistance;

out vec4 FragColor;

void main()
{
    vec3 rayDir = vFarPoint - vNearPoint;
    float denom = dot(uPlaneNormal, rayDir);

    if (abs(denom) < 1e-6)
        discard;

    float t = (uPlaneOriginDistance - dot(uPlaneNormal, vNearPoint)) / denom;

    if (t < 0.0 || t > 1.0)
        discard;

    vec3 worldPos = vNearPoint + t * rayDir;

    vec4 clipPos = uProj * uView * vec4(worldPos, 1.0);
    float ndcDepth = clipPos.z / clipPos.w;
    gl_FragDepth = ndcDepth * 0.5 + 0.5;

    float alpha = uMatColor.a;

    if (uFadeDistance > 0.0)
    {
        float dist = length(worldPos - uCameraPos);
        alpha *= clamp(1.0 - (dist / uFadeDistance), 0.0, 1.0);
    }

    FragColor = vec4(uMatColor.rgb, alpha);
}
