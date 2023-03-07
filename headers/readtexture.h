#pragma once
#ifndef READ_TEXTURE_H

//********** Wczytywanie tekstury **********
GLuint readTexture(const char* filename) {  //filename nazwa pliku który ma byæ wczytany
	glActiveTexture(GL_TEXTURE0);			//aktywacja zerowej jednostki teksturuj¹cej ; na karcie graficznej

	//Wczytanie do pamiêci komputera
	std::vector<unsigned char> image;		//Alokuj wektor do wczytania obrazka
	unsigned width, height;					//Zmienne do których wczytamy wymiary obrazka

	string textexture = "./textures/";
	string textexturepath = textexture + static_cast<string>(filename);
	filename = textexturepath.c_str();

	//Wczytaj obrazek
	unsigned error = lodepng::decode(image, width, height, filename);
	
	if (error != 0) {
		//std::cout << "Blad wczytywania tekstury, kod bledu: " << error;
		assert(0);
	}
	//Import do pamiêci karty graficznej
	glGenTextures(1, &tex);					//Zainicjuj jeden uchwyt
	glBindTexture(GL_TEXTURE_2D, tex);		//Uaktywnij uchwyt, GL_TEXTURE_2D - typ tekstury, zawsze 2D czyli dwuwymiarowa tekstura z normalizacja teksturowania

	//Wczytaj obrazek do pamiêci KG skojarzonej z uchwytem
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());
	//glTexImage2D(Glenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels
	//target - zawsze GL_TEXTURE_2D
	//level - poziom minimapy zawsze 0
	//internalformat - liczba skladowych kolor dla obrazkow 32 bitowych 4 (RGBA) DLA 24 BITOWYCH 3 (RGB)
	//border - zawsze 0 (ile pikesli z kazdej strony powinno zostac obcietych)
	//format np. GL_RGBA, GL_RGB
	//type - GL_UNSINGED_BYTE (tablica bajtow)
	//pixels - wskaznik do obszaru pamieci w ktorym zapisano dane obrazka


	//polecenia dla aktywnej tekstury, jesli wczytujemy wiecej niz jeden obrazek trzeba wykonac dla kazdego z nich
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	//pomniejszanie tekseli
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	//powiekszanie tekseli
	return tex;
}

#endif