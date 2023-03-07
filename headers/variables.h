#pragma once
#ifndef VARIABLES_H

using namespace std;
Assimp::Importer importer;				//utworzenie obiektu importer klasy Assimp


//********** ZMIENNE **********
//nawigacja
float speed_x			= 0;			//[radiany/s]
float speed_y			= 0;			//[radiany/s]
float speed_light		= 0;			//obrót swiatel
float walk_speed_x		= 0;
float walk_speed_y		= 0;
float walk_speed		= 0.25f;
float speed_skeleton_x	= 0;			//<--do obrotu
float speed_skeleton_y	= 0;
float skeleton_x		= 0;
float skeleton_y		= 0;
//float angle_x			= 0;
//float angle_y			= 0;
double angle_x = 0;
double angle_y = 0;

float light_angle		= 0;
float aspectRatio		= 1;			//<--skalowanie okna
float rot				= 1.0;

//zmienne
GLuint tex;								//deklaracja globalna zmiennej uchwytu szkielet
GLuint texFloor;						//deklaracja globalna zmiennej uchwytu podlogi

vector<glm::vec4> verts;				//do szkieletu			
vector<glm::vec4> norms;				//do szkieletu
vector<glm::vec2> texCoords;			//do szkieletu
vector<glm::vec4> bonesID;
vector<unsigned int> indices;			//siatka

unsigned int bonesNamesIndex = 0;

vector<VertexBoneData> bones;			//aikosci
vector<aiAnimation*> animations;		//animacja
//vector<const aiNodeAnim*> bonesNames;
vector<VertexBoneName> bonesNames;

aiMatrix4x4 GlobalInverseTransform;		//ustawienie startowe modelu
glm::mat4 GIT2;							//przerzucenie z aiMatrix4x4 na glm::mat4
std::unordered_map<std::string, std::pair<int, glm::mat4>> m_BoneMapping = {};

vector<BoneInfo> m_BoneInfo;			//wektor struktur informacji o kosci
vector<MeshEntry> m_Entries;			//wektor struktur informacji o siatkach
int m_NumBones = 0;						//poczatkowa lista wczytanych kosci

glm::vec3 pos = glm::vec3(0, 0.3, -10);  //pozycja startowa widoku
float RunningTime = 0.f;
vector<glm::mat4> Transforms = {};
//*****************************

#endif