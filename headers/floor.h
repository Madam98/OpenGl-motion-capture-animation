#pragma once
#ifndef FLOOR_H

float basex = 30.0f;
float basey = 30.0f;
float basez = 0.0f;

float floorv[] = {
	-basex,-basey,basez,1.0f,
	basex,basey,basez,1.0f,
	basex,-basey,basez,1.0f,
	-basex,-basey,basez,1.0f,
	-basex,basey,basez,1.0f,
	basex,basey,basez,1.0f,
};

float float_atrib = 7.0f;

float floort[] = {
	float_atrib, 0.0f,
	0.0f, float_atrib,
	0.0f, 0.0f,

	float_atrib, 0.0f,
	float_atrib, float_atrib,
	0.0f, float_atrib,
};
float floorn[] = {
	0.0f,0.0f,1.0f,0.0f,
	0.0f,0.0f,1.0f,0.0f,
	0.0f,0.0f,1.0f,0.0f,
	0.0f,0.0f,1.0f,0.0f,
	0.0f,0.0f,1.0f,0.0f,
	0.0f,0.0f,1.0f,0.0f,
};

void generateFloor(glm::mat4 M, glm::mat4 V, glm::mat4 P, float* floorv, float* floorn, float* floort) {
	
	spLambertTextured->use();
	glUniformMatrix4fv(spLambertTextured->u("M"), 1, false, value_ptr(M)); //dla macierzy obiektu
	glUniformMatrix4fv(spLambertTextured->u("V"), 1, false, value_ptr(V)); //dla macierzy widoku
	glUniformMatrix4fv(spLambertTextured->u("P"), 1, false, value_ptr(P)); //dla macierzy przyiecia
	glEnableVertexAttribArray(spLambertTextured->a("vertex"));
	glVertexAttribPointer(spLambertTextured->a("vertex"), 4, GL_FLOAT, false, 0, floorv); //wartosc false sprawia ze kazda wartosc z tablicy GF_FLOAT nie jest normalizowana, 0 to liczba bajtow odzielajaca opis jednego wierzcholka od drugiego
	glEnableVertexAttribArray(spLambertTextured->a("normal"));
	glVertexAttribPointer(spLambertTextured->a("normal"), 4, GL_FLOAT, false, 0, floorn); //wartosc data() zwraca wskaznik na wewnetrzna reprezentacje wektora
	glEnableVertexAttribArray(spLambertTextured->a("texCoord"));
	glVertexAttribPointer(spLambertTextured->a("texCoord"), 2, GL_FLOAT, false, 0, floort);
	
	glBindTexture(GL_TEXTURE_2D, texFloor);				
	
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(spLambertTextured->a("vertex"));
	glDisableVertexAttribArray(spLambertTextured->a("normal"));
	glDisableVertexAttribArray(spLambertTextured->a("texCoord"));
	//glDeleteTextures(2, &texFloor);
}


#endif
