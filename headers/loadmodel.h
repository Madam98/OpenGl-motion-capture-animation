#pragma once
#ifndef LOAD_MODEL_H


void checkSum(vector<VertexBoneData> bones) {
	return;
	float sum = 0;
	int counter = 0;
	for (int i = 0; i < bones.size(); i++) {
		sum = sum + bones[i].Weights.x;
		sum = sum + bones[i].Weights.y;
		sum = sum + bones[i].Weights.z;
		sum = sum + bones[i].Weights.w;
		//cout << "Indeks i:\t" << i << "\t waga: " << sum << endl;
		//cout << "Bones[0]: " << bones[i].Weights.x << endl;
		//cout << "Bones[1]: " << bones[i].Weights.y << endl;
		//cout << "Bones[2]: " << bones[i].Weights.z << endl;
		//cout << "Bones[3]: " << bones[i].Weights.w << endl << endl;
			
		if (sum < 0.9) {
			counter++;
		}

		sum = 0;
	}
	cout << "Size of bad vertices weight: " << counter << endl;
	//assert(counter == 0);
}


//********** Ladowanie modelu **********
const aiScene* loadModel(string plik) {

	string loadObject = "./animation_object/";
	plik = loadObject + static_cast<string>(plik);

	const aiScene* scene = importer.ReadFile(plik, aiProcess_Triangulate | aiProcess_FlipUVs); //wczytanie do sceny obietku importer (postprocesy)
	//aiProcess_Triangulate wszystkie wielok¹ty przerób na trójk¹ty (GrawElements!) 
	//aiProcess_FlipUVs odwracanie osi y na wczytanych teksturach ((0,0) lewy górny róg pocz¹tek obrazka - w OpenGL lewy dolny))
	//aiProcess_GenSmoothNormals - generuj usrednione wektory normalne (wierzcholkow) jezeli ich nie ma
	
	cout << importer.GetErrorString() << endl; //scene normalnie 0 lub lancuch bledu
	GlobalInverseTransform = scene->mRootNode->mTransformation;	 //przypisanie macierzy mTransformation

	GIT2 = ai_to_glm(GlobalInverseTransform);		//zamiana formatu ai to glm
	GIT2 = glm::inverse(GIT2);								//inwersja na macierzy git2
	m_Entries.resize(scene->mNumMeshes);			//wektor z iloscia siatek

	unsigned int NumVertices = 0;
	unsigned int NumIndices = 0;
	unsigned int VerticesPerPrim = 3;
	const aiMesh* mesh = scene->mMeshes[0];			//pobranie wskaznika na mesh ktory bedziemy przegladac

	NumVertices += scene->mMeshes[0]->mNumVertices;
	NumIndices += scene->mMeshes[0]->mNumFaces * VerticesPerPrim;

	verts.reserve(NumVertices);
	norms.reserve(NumVertices);
	texCoords.reserve(NumVertices);
	bones.resize(NumVertices);
	indices.reserve(NumIndices);
	

	for (int i = 0; i < mesh->mNumVertices; i++) {	//liczba wierzcholkow -mNumVertices i iczba odpowiadajacych danych
		//1.Wspolrzedne wierzcholka
		aiVector3D vertex = mesh->mVertices[i];		//aiVector3d podobny do glm::vec3
		verts.push_back(glm::vec4(vertex.x, vertex.y, vertex.z, 1));//wczytywanie do zmienej verts, parametrów wiezrcholka
		//2.Wektory normalne
		aiVector3D normal = mesh->mNormals[i];		//wektory normalne
		norms.push_back(glm::vec4(normal.x, normal.y, normal.z, 0));//wczytywanie do zmiennej norms, parametrów znormalizowanych
		//3.Teksturowanie
		aiVector3D texCoord = mesh->mTextureCoords[0][i];//(tekstura 2 wymiarowa) 
		texCoords.push_back(glm::vec2(texCoord.x, texCoord.y));//wczytanie wspolrzednych teksturowania
	}

	//4.Wczytywanie bone
	//Ladowanie BoneData
	std::vector<unsigned int> boneCounts;
	boneCounts.resize(bones.size(), 0);
	unsigned int nBoneCount = mesh->mNumBones;

	//petla przez kazda kosc
	int BoneIndex = 0;
	for (unsigned int i = 0; i < nBoneCount; i++) {
		aiBone* bone = mesh->mBones[i];
		glm::mat4 m = ai_to_glm(bone->mOffsetMatrix);
		m_BoneMapping[bone->mName.data] = { i, m };
		BoneIndex = m_NumBones;									//zwieksz Boneindex
		m_NumBones++;
		BoneInfo bi;											//<---ODWOLANIE DO STRUKTURY BoneInfo! inicjacja
		m_BoneInfo.push_back(bi);
		m_BoneInfo[BoneIndex].BoneOffset = ai_to_glm(mesh->mBones[i]->mOffsetMatrix);

		//petla przez kazdy wierzcholek ktory ma ta kosc
		for (int j = 0; j < bone->mNumWeights; j++) {
			unsigned int id = bone->mWeights[j].mVertexId;
			float weight = bone->mWeights[j].mWeight;
			boneCounts[id]++;
			switch (boneCounts[id]) {
			case 1:
				bones[id].ID.x = i;
				bones[id].Weights.x = weight;
				break;
			case 2:
				bones[id].ID.y = i;
				bones[id].Weights.y = weight;
				break;
			case 3:
				bones[id].ID.z = i;
				bones[id].Weights.z = weight;
				break;
			case 4:
				bones[id].ID.w = i;
				bones[id].Weights.w = weight;
				break;
			default:
				//std::cout << "err: unable to allocate bone to vertex" << std::endl;
				break;
			}
		}
		cout << "i: " << i << "\tBoneIndex: " << i << "\t" << bone->mName.data << endl;
	}
	//normalizowanie wag wszystkich aby suma 1


	//ladowanie siatki
	for (int i = 0; i < mesh->mNumFaces; i++) {		//dla kazdego wielokata skladowego (mNumFaces ilosc faces)
		aiFace& face = mesh->mFaces[i];				//zmienna face to jeden z wielokatow siatki dla kazdego indeksu->wierzcholka tworzacego wielokat dla aiProcess_Triangulat to zawsze bedzie 3
		assert(face.mNumIndices == 3);
		indices.push_back(face.mIndices[0]);
		indices.push_back(face.mIndices[1]);
		indices.push_back(face.mIndices[2]);
	}
	
	//Tworzenie hierarchi koœci
	BoneTransform(0, Transforms, scene, true);		//<---flaga true oznacza ze tworzymy drzewo kosci

	return scene;
}
#endif 

