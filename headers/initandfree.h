#pragma once
#ifndef INIT_AND_FREE_H

//********** Skalowanie okna **********
void windowResizeCallback(GLFWwindow* window, int width, int height) {   //<---sklaowanie okna
	if (height == 0) return;
	aspectRatio = (float)width / (float)height;
	glViewport(0, 0, width, height);
}


//********** Procedura inicjujaca (raz)**********
const aiScene* initOpenGLProgram(GLFWwindow* window) {
	initShaders();
	//glClearColor(0, 0.5, 0.6, 1);							//Ustaw kolor czyszczenia bufora kolorów, ustawiamy niebieski
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);								//W³¹cz test g³êbokoœci na pikselach, (unikniecie Z bufora)
	glfwSetWindowSizeCallback(window, windowResizeCallback);//Skalowanie okna
	glfwSetKeyCallback(window, key_callback);				//Ustaw okno, w ktorym ma ''obserwowac'' klawisze
	texFloor	= readTexture("floorwood.png");
	tex			= readTexture("skelet_texture.png");		//Wczytywanie tekstury szkieleta
	//const aiScene* scene = loadModel("skelet_with_anim.fbx");//Wczytywanie animacji
	//const aiScene* scene = loadModel("final_skelet_with_anim.fbx");			
	//const aiScene* scene = loadModel("final_skelet_with_anim_2.fbx");
	//const aiScene* scene = loadModel("test.fbx");
	const aiScene* scene = loadModel("kinect_anim_dance_1.fbx");


	return scene;
}

//********** Zwolnienie zasobów zajêtych przez program **********
void freeOpenGLProgram(GLFWwindow* window) {
	freeShaders();
	glDeleteTextures(1, &tex);					//Usuwanie tekstury
}

#endif 

