#include "headers/mainheader.h";

/*Procedury obslugi bledow
Przed KAZDYM wywolaniem procedury gl uzyj proceduty GLCall
pozwoli to zawsze zlokalizowac z wynikiem w konsoli zrodlo wystapienia bledu
*/
//********** Spis procedur **********
const aiScene* initOpenGLProgram(GLFWwindow* window);
void freeOpenGLProgram(GLFWwindow* window);
void error_callback(int error, const char* description);
GLuint readTexture(const char* filename);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mod);
glm::vec3 calcDir(float kat_x, float kat_y, glm::vec4 dir);
void windowResizeCallback(GLFWwindow* window, int width, int height);
const aiScene* loadModel(string plik);
void drawScene(GLFWwindow* window, float skeleton_x, float skeleton_y, float angle_x, float angle_y, float light_angle, const aiScene* scene, float RunningTime);

const aiNodeAnim* FindNodeAnim(const aiAnimation* pAnimation, const string NodeName);
int FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim);
int FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim);
int FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim);
void CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
void CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
void CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
void ReadNodeHeirarchy(float AnimationTime, const aiNode* pNode, const glm::mat4& ParentTransform, const aiScene* scene);
void BoneTransform(float TimeInSeconds, vector<glm::mat4>& Transforms, const aiScene* scene, bool create);
//***********************************

float oldTime = 0;
float animationSpeed = 60.0;


//********** Procedura rysująca zawartość sceny **********
void drawScene(GLFWwindow* window, float skeleton_x, float skeleton_y, float angle_x, float angle_y, float light_angle, const aiScene* scene, float RunningTime) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			//Wyczyść bufor koloru i bufor głębokości	

	//1. Macierz modelu
	glm::mat4 M = glm::mat4(1.0f);								//Zainicjuj macierz modelu macierzą jednostkową
	M = glm::translate(M, glm::vec3(0.0f, -0.5f, 0.0f));
	M = glm::rotate(M, -PI/2, glm::vec3(1.0f, 0.0f, 0.0f));		
	M = glm::rotate(M, PI, glm::vec3(0.0f, 0.0f, 1.0f));

	M = glm::rotate(M, skeleton_x, glm::vec3(0.0f, 0.0f, 1.0f));
	M = glm::rotate(M, skeleton_y, glm::vec3(1.0f, 0.0f, 0.0f));

	//2.Macierz widoku
	glm::mat4 V = glm::lookAt(pos, pos + calcDir(angle_x, angle_y), glm::vec3(0.0f, 0.1f, 0.0f)); //Wylicz macierz widoku

	//3.Macierz przyciecia
	glm::mat4 P = glm::perspective(glm::radians(40.0f), 1.0f, 1.0f, 50.0f); //Wylicz macierz rzutowania

	//4.Aktywacja programow cieniujacych
	glm::vec3 positions[4];
	//vector<glm::mat4> Transforms = {};

	glm::mat4 MCube = M;
	glm::mat4 MModel = M;

	float light_y = 0.0f;

	glUniform1i(spLambertTextured->u("boned"), false);
	generateLight(colors, positions, light_angle, light_y);
	generateFloor(M, V, P, floorv, floorn, floort);
	generateCubes(M, V, P, MCube, positions, angle_x, angle_y);
	glUniform1i(spLambertTextured->u("boned"), true);

	//MModel = glm::rotate(MModel, PI, glm::vec3(1.0f, 0.0f, 0.0f));		//model na poczatku jest niefajnie ustawiony. Tu jesty git
	MModel = glm::rotate(MModel, PI/2, glm::vec3(1.0f, 0.0f, 0.0f));
	MModel = glm::rotate(MModel, PI, glm::vec3(0.0f, 1.0f, 0.0f));
	MModel = glm::translate(MModel, glm::vec3(0.0f, 0.28f, -1.0f));
	//MModel = glm::scale(MModel, glm::vec3(1.0f));
	MModel = glm::scale(MModel, glm::vec3(0.01f));

	spLambertTextured->use();
	glUniformMatrix4fv(spLambertTextured->u("M"), 1, false, value_ptr(MModel)); //dla macierzy obiektu
	glUniformMatrix4fv(spLambertTextured->u("V"), 1, false, value_ptr(V)); //dla macierzy widoku
	glUniformMatrix4fv(spLambertTextured->u("P"), 1, false, value_ptr(P)); //dla macierzy przyciecia

	//vertex - wspolrzedna wierzcholka wspolrzednych homogenicznych (4 liczby)
	//normal - wektor normalny do ktorej nalezy wierzcholek (4 liczby)
	//texCoord - wspolrzedna teksturowania (2 liczby)
	//parametry ktore maja stala wartosc to zmienne jednorodne
	//zwiazane z wierzcholkami nazywane sa atrybutami (np. wspolrzedne wierzchoka)
	//wysylamy wszystkie atrybuty wierzchokow
	//GL_FLOAT - zmienne jednorodne, wspolrzedne wierzchokow z verts.data() lub norms.data() lub texCoords.daata()

	//ladowanie modelu
	//RunningTime += (float)glfwGetTime() * 80;
	
	//RunningTime += 0.02f;
	//RunningTime += (float)glfwGetTime();
	//cout << "Running time: " << RunningTime << endl;
	bonesNamesIndex = 0;

	BoneTransform(RunningTime - 13.0, Transforms, scene, false);

	//BoneTransform((RunningTime-tPrev) * animationSpeed/1000.0, Transforms, scene, false);

	glUniformMatrix4fv(spLambertTextured->u("gBones"), 20, GL_FALSE, glm::value_ptr(Transforms[0]));
	//GLCall(glUniformMatrix4fv(spLambertTextured->u("gBones"), 250, GL_FALSE, (float*)(Transforms.data())));
	//GLCall(glUniformMatrix4fv(spLambertTextured->u("gBones"), Transforms.size(), GL_FALSE, (float*)(Transforms.data())));
	//glUniformMatrix4fv(spLambertTextured->u("gBones"), 250, GL_FALSE, (float*)(Transforms.data()));

	glEnableVertexAttribArray(spLambertTextured->a("vertex"));
	glVertexAttribPointer(spLambertTextured->a("vertex"), 4, GL_FLOAT, false, 0, verts.data()); //wartosc false sprawia ze kazda wartosc z tablicy GF_FLOAT nie jest normalizowana, 0 to liczba bajtow odzielajaca opis jednego wierzcholka od drugiego
	glEnableVertexAttribArray(spLambertTextured->a("normal"));
	glVertexAttribPointer(spLambertTextured->a("normal"), 4, GL_FLOAT, false, 0, norms.data()); //wartosc data() zwraca wskaznik na wewnetrzna reprezentacje wektora
	glEnableVertexAttribArray(spLambertTextured->a("texCoord"));
	glVertexAttribPointer(spLambertTextured->a("texCoord"), 2, GL_FLOAT, false, 0, texCoords.data());

	int* ids = new int[4 * bones.size()];
	float* weights = new float[4 * bones.size()];

	for (int i = 0; i != bones.size(); ++i)
	{
		ids[4 * i] = bones[i].ID.x;
		ids[4 * i + 1] = bones[i].ID.y;
		ids[4 * i + 2] = bones[i].ID.z;
		ids[4 * i + 3] = bones[i].ID.w;
		weights[4 * i] = bones[i].Weights.x;
		weights[4 * i + 1] = bones[i].Weights.y;
		weights[4 * i + 2] = bones[i].Weights.z;
		weights[4 * i + 3] = bones[i].Weights.w;
	}
	glEnableVertexAttribArray(spLambertTextured->a("boneIDs"));
	glVertexAttribIPointer(spLambertTextured->a("boneIDs"), 4, GL_INT, 0, ids);

	glEnableVertexAttribArray(spLambertTextured->a("weights"));
	glVertexAttribPointer(spLambertTextured->a("weights"), 4, GL_FLOAT, GL_FALSE, 0, weights);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);

	//5.Teksutorwanie
	GLCall(glBindTexture(GL_TEXTURE_2D, tex));		//przypisanie tekstury tex

	//6.Rysowanie modelu
	if (RunningTime > 15.0f) {
		GLCall(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data()));
	}

	//7.Usuwanie wspolrzednych dla programu cieniujacego
	glDisableVertexAttribArray(spLambertTextured->a("vertex"));
	glDisableVertexAttribArray(spLambertTextured->a("normal"));
	glDisableVertexAttribArray(spLambertTextured->a("texCoord"));
	glDisableVertexAttribArray(spLambertTextured->a("boneIDs"));
	glDisableVertexAttribArray(spLambertTextured->a("weights"));

	glfwSwapBuffers(window);				//Skopiuj bufor tylny do bufora przedniego
	delete[] weights;
	delete[] ids;

}
//****************************************************************************************
int main(void)
{
	GLFWwindow* window;								//Wskaźnik na obiekt reprezentujący okno
	const aiScene* scene;
	float tAnimation = 0.0f;


	glfwSetErrorCallback(error_callback);			//Zarejestruj procedurę obsługi błędów ;;https://www.glfw.org/docs/3.3/group__init.html#gaff45816610d53f0b83656092a4034f40

	if (!glfwInit()) {								//Zainicjuj bibliotekę GLFW
		fprintf(stderr, "Nie można zainicjować GLFW.\n");
		exit(EXIT_FAILURE);
	}
	window = glfwCreateWindow(1000, 1000, "OpenGL", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

	if (!window) {									//Jeżeli okna nie udało się utworzyć, to zamknij program
		fprintf(stderr, "Nie można utworzyć okna.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);					//Od tego momentu kontekst okna staje się aktywny i polecenia OpenGL będą dotyczyć właśnie jego.
	glfwSwapInterval(1);							//Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora
	if (glewInit() != GLEW_OK) {					//Zainicjuj bibliotekę GLEW
		fprintf(stderr, "Nie można zainicjować GLEW.\n");
		exit(EXIT_FAILURE);
	}

	scene = initOpenGLProgram(window);				//Operacje inicjujące

	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//if (glfwRawMouseMotionSupported())
	//	glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	//glfwSetCursorPos(window, 0, 0);
	glfwSetTime(0);                                //Wyzeruj licznik czasu	
	
	//bool playedAudience = PlaySound(TEXT("./audio/audience.wav"), NULL, SND_FILENAME | SND_ASYNC);
	//bool played = PlaySound(TEXT("./audio/spooky.wav"), NULL, SND_FILENAME | SND_ASYNC);
	//bool playedAudience = PlaySound(TEXT("./audio/audience.wav"), NULL, SND_FILENAME | SND_ASYNC);


	bool bAudience = true;
	bool bMusic = true;
	//Główna pętla
	while (!glfwWindowShouldClose(window))         //Tak długo jak okno nie powinno zostać zamknięte
	{
		//Kamera 3D i obsluga myszki
		/*
		glfwGetCursorPos(window, &angle_y, &angle_x);
		if (angle_x > 1570){
			angle_x = 1570;
			glfwSetCursorPos(window, angle_y, angle_x);
		}
		else if (angle_x < -1570){
			angle_x = -1570;
			glfwSetCursorPos(window, angle_y, angle_x);
		}
		angle_x /= 1000.0;
		angle_y /= -1000.0;
		pos += walk_speed * walk_speed_y * static_cast<float>(glfwGetTime()) * calcDir(static_cast<float>(angle_x), static_cast<float>(angle_y));
		pos += walk_speed * walk_speed_x * static_cast<float>(glfwGetTime()) * calcDir(static_cast<float>(angle_x), static_cast<float>(angle_y), glm::vec4(1, 0, 0, 0));
		*/
		

		float RunningTime = (float)glfwGetTime();
		float tPrev = RunningTime - oldTime;
		//cout << "Running time: " << RunningTime << "\t\tTprev: " << tPrev << endl;
		oldTime = RunningTime;

		
		angle_x += (speed_x / rot) * tPrev; //Oblicz kąt o jaki obiekt obrócił się podczas poprzedniej klatki
		angle_y += (speed_y / rot) * tPrev; //Oblicz kąt o jaki obiekt obrócił się podczas poprzedniej klatki
		skeleton_x += (speed_skeleton_x / rot) * tPrev;
		skeleton_y += (speed_skeleton_y / rot) * tPrev;
		light_angle += (speed_light / rot) * tPrev;
		pos += (float)(walk_speed * tPrev) * calcDir(angle_x, angle_y);
		//glfwSetTime(0);                                //Wyzeruj licznik czasu

		tAnimation += tPrev;
		if ((tAnimation > 2.0 and tAnimation < 10.0) || (tAnimation > 220.0)) {
			if (colors[0].x > 0) colors[0].x -= 0.1f;
			if (colors[1].y > 0) colors[1].y -= 0.1f;
			if (colors[2].z > 0) colors[2].z -= 0.1f;
			if (colors[3].x > 0) {
				colors[3].x -= 0.1f;
				colors[3].y -= 0.1f;
				colors[3].z -= 0.1f;
			}
			if (bAudience) {
				bool playedAudience = PlaySound(TEXT("./audio/audience.wav"), NULL, SND_FILENAME | SND_ASYNC);
				bAudience = false;
			}
		}

		if (bMusic and tAnimation > 10.0) {
			bool played = PlaySound(TEXT("./audio/spooky.wav"), NULL, SND_FILENAME | SND_ASYNC);
			bMusic = false;
		}

		if (tAnimation > 15.0 and tAnimation < 30.0) {
			if (colors[0].x < 1.0) colors[0].x += 0.005f;
			if (colors[1].y < 1.0) colors[1].y += 0.005f;
			if (colors[2].z < 1.0) colors[2].z += 0.005f;
			if (colors[3].x < 0.5) {
				colors[3].x += 0.005f;
				colors[3].y += 0.005f;
				colors[3].z += 0.005f;
			}
			speed_light = 1.5;
		}

		if (tAnimation > 137.0 and tAnimation < 139.0) {
			if (colors[0].x < 1.0) colors[0].x += 0.2f;
			if (colors[1].y < 1.0) colors[1].y += 0.2f;
			if (colors[2].z < 1.0) colors[2].z += 0.2f;
			if (colors[3].x < 0.5) {
				colors[3].x += 0.2f;
				colors[3].y += 0.2f;
				colors[3].z += 0.2f;
			}
			speed_light = 1.5;
		}


		if (tAnimation > 25.0) {
			walk_speed = -0.01f;
			speed_skeleton_x = PI/4;
		}

		drawScene(window, skeleton_x, skeleton_y, static_cast<float>(angle_x), static_cast<float>(angle_y), light_angle, scene, tAnimation); //Wykonaj procedurę rysującą
		glfwPollEvents();                            //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window);						//Usuń kontekst OpenGL i okno
	glfwTerminate();								//Zwolnij zasoby zajęte przez GLFW
	exit(EXIT_SUCCESS);
}