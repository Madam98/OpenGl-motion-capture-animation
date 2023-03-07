#version 330

const int MAX_BONES = 250;

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform mat4 gBones[MAX_BONES];
uniform vec4 lightDir=vec4(0,0,1,0);
uniform bool boned;

//Atrybuty
in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
in vec4 normal; //wektor normalny w wierzcholku
in vec2 texCoord; //wspó³rzêdne teksturowania
in ivec4 boneIDs;
in vec4 weights;

//Zmienne interpolowane
out vec2 i_tc;
out float i_nl;
out vec3 FragPos;
out vec3 Normals;
out vec4 pos;

void main(void) {
    if (boned)
    {
        mat4 BoneTransform = mat4(0.0);
        BoneTransform += gBones[boneIDs[0]] * weights[0];
        BoneTransform += gBones[boneIDs[1]] * weights[1];
        BoneTransform += gBones[boneIDs[2]] * weights[2];
        BoneTransform += gBones[boneIDs[3]] * weights[3];

        //BoneTransform  +=  gBones[int(boneIDs.x)] * weights.x;
		//BoneTransform  +=  gBones[int(boneIDs.y)] * weights.y;
		//BoneTransform  +=  gBones[int(boneIDs.z)] * weights.z;
		//BoneTransform  +=  gBones[int(boneIDs.w)] * weights.w;

        //BoneTransform  +=  gBones[int(boneIDs.x)] * 1;
		//BoneTransform  +=  gBones[int(boneIDs.y)] * 1;
		//BoneTransform  +=  gBones[int(boneIDs.z)] * 1;
		//BoneTransform  +=  gBones[int(boneIDs.w)] * 1;

        vec4 PosL       = BoneTransform * vec4(vertex);
        gl_Position     = P * V * M * PosL;
        pos = M * BoneTransform * vertex;//* rotate(vertex, vec3(0.0, 0.0, .0.0));
        
        FragPos         = vec3(M * vertex);
        vec4 NormalL    = BoneTransform * normal;

        mat4 G=mat4(inverse(transpose(mat3(M*BoneTransform))));
        vec4 n=normalize(V*G*NormalL);
        
        Normals      = (P*NormalL).xyz; 
        
        //Normals = mat3(transpose(inverse(M)))*normal.xyz;
        i_nl=clamp(dot(n,lightDir),0,0.5);
        i_tc=texCoord;
    }
    else
    { 
        gl_Position = P * V * M * vertex;
        FragPos = vec3(M * vertex);
        mat4 G=mat4(inverse(transpose(mat3(M))));
        vec4 n=normalize(V*G*normal);
        Normals = mat3(transpose(inverse(M)))*normal.xyz;
        i_nl=clamp(dot(n,lightDir),0,0.5);
        i_tc=texCoord;
    }

}
