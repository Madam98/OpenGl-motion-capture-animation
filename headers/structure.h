#pragma once
#ifndef STRUCTURE_H
	
//********** PLIKI STRUCT PROJEKTU**********

struct VertexBoneData {
	glm::vec4 ID = glm::vec4(0);
	glm::vec4 Weights = glm::vec4(0.0f);
};

struct VertexBoneName {
	const aiNodeAnim* bonesNodeNames;
	std::string bonesStringNames;
};

struct BoneInfo {					//zadeklaruj dwie wyzerowane macierze 4x4 
	glm::mat4 BoneOffset;
	glm::mat4 FinalTransformation;
	BoneInfo() {
		BoneOffset = glm::mat4(0.0f);
		FinalTransformation = glm::mat4(0.0f);	//macierz wykorzystywana do obliczenia koncowego przesuniecia kosci
	}
};

struct MeshEntry {
	MeshEntry() {
		NumIndices = 0;				//ilosc wierzcholkow
		BaseVertex = 0;				//poczatkowy glowny wierzcholek
		BaseIndex = 0;				//index poczatkowego glownego wierzcholka
		//MaterialIndex = INVALID_MATERIAL;
	}
	unsigned int NumIndices;
	unsigned int BaseVertex;
	unsigned int BaseIndex;
};

#endif