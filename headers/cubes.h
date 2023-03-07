#pragma once
#ifndef CUBES_H

/*POCZATEK SWIATLA*/
float cubet[] = {
1.0f, 0.0f,		//A	//1 œciana
0.0f, 1.0f,		//B
0.0f, 0.0f,		//C

1.0f, 0.0f,    //A
1.0f, 1.0f,    //D
0.0f, 1.0f,    //B

1.0f, 0.0f,		//A	//2 œciana
0.0f, 1.0f,		//B
0.0f, 0.0f,		//C

1.0f, 0.0f,    //A
1.0f, 1.0f,    //D
0.0f, 1.0f,    //B

1.0f, 0.0f,		//A	//3 œciana
0.0f, 1.0f,		//B
0.0f, 0.0f,		//C

1.0f, 0.0f,    //A
1.0f, 1.0f,    //D
0.0f, 1.0f,    //B

1.0f, 0.0f,		//A	//4 œciana
0.0f, 1.0f,		//B
0.0f, 0.0f,		//C

1.0f, 0.0f,    //A
1.0f, 1.0f,    //D
0.0f, 1.0f,    //B

1.0f, 0.0f,		//A	//5 œciana
0.0f, 1.0f,		//B
0.0f, 0.0f,		//C

1.0f, 0.0f,    //A
1.0f, 1.0f,    //D
0.0f, 1.0f,    //B

1.0f, 0.0f,		//A	//6 œciana
0.0f, 1.0f,		//B
0.0f, 0.0f,		//C

1.0f, 0.0f,    //A
1.0f, 1.0f,    //D
0.0f, 1.0f,    //B
};

//Tablica wektorów normalnych
float cuben[] = {
0.0f,0.0f,-1.0f,0.0f, //A
0.0f,0.0f,-1.0f,0.0f, //B
0.0f,0.0f,-1.0f,0.0f, //C

0.0f,0.0f,-1.0f,0.0f, //A
0.0f,0.0f,-1.0f,0.0f, //D
0.0f,0.0f,-1.0f,0.0f, //B

0.0f,0.0f,1.0f,0.0f, //A
0.0f,0.0f,1.0f,0.0f, //B
0.0f,0.0f,1.0f,0.0f, //C

0.0f,0.0f,1.0f,0.0f, //A
0.0f,0.0f,1.0f,0.0f, //D
0.0f,0.0f,1.0f,0.0f, //B

0.0f,-1.0f,0.0f,0.0f, //A
0.0f,-1.0f,0.0f,0.0f, //B
0.0f,-1.0f,0.0f,0.0f, //C

0.0f,-1.0f,0.0f,0.0f, //A
0.0f,-1.0f,0.0f,0.0f, //D
0.0f,-1.0f,0.0f,0.0f, //B

0.0f,1.0f,0.0f,0.0f, //A
0.0f,1.0f,0.0f,0.0f, //B
0.0f,1.0f,0.0f,0.0f, //C

0.0f,1.0f,0.0f,0.0f, //A
0.0f,1.0f,0.0f,0.0f, //D
0.0f,1.0f,0.0f,0.0f, //B

-1.0f,0.0f,0.0f,0.0f, //A
-1.0f,0.0f,0.0f,0.0f, //B
-1.0f,0.0f,0.0f,0.0f, //C

-1.0f,0.0f,0.0f,0.0f, //A
-1.0f,0.0f,0.0f,0.0f, //D
-1.0f,0.0f,0.0f,0.0f, //B

1.0f,0.0f,0.0f,0.0f, //A
1.0f,0.0f,0.0f,0.0f, //B
1.0f,0.0f,0.0f,0.0f, //C

1.0f,0.0f,0.0f,0.0f, //A
1.0f,0.0f,0.0f,0.0f, //D
1.0f,0.0f,0.0f,0.0f, //B
};
float cubev[] = {
1.0f,-1.0f,-1.0f,1.0f,
-1.0f, 1.0f,-1.0f,1.0f,
-1.0f,-1.0f,-1.0f,1.0f,

1.0f,-1.0f,-1.0f,1.0f,
1.0f, 1.0f,-1.0f,1.0f,
-1.0f, 1.0f,-1.0f,1.0f,


-1.0f,-1.0f, 1.0f,1.0f,
1.0f, 1.0f, 1.0f,1.0f,
1.0f,-1.0f, 1.0f,1.0f,

-1.0f,-1.0f, 1.0f,1.0f,
-1.0f, 1.0f, 1.0f,1.0f,
1.0f, 1.0f, 1.0f,1.0f,

1.0f,-1.0f, 1.0f,1.0f,
1.0f, 1.0f,-1.0f,1.0f,
1.0f,-1.0f,-1.0f,1.0f,

1.0f,-1.0f, 1.0f,1.0f,
1.0f, 1.0f, 1.0f,1.0f,
1.0f, 1.0f,-1.0f,1.0f,

-1.0f,-1.0f,-1.0f,1.0f,
-1.0f, 1.0f, 1.0f,1.0f,
-1.0f,-1.0f, 1.0f,1.0f,

-1.0f,-1.0f,-1.0f,1.0f,
-1.0f, 1.0f,-1.0f,1.0f,
-1.0f, 1.0f, 1.0f,1.0f,

-1.0f,-1.0f,-1.0f,1.0f,
1.0f,-1.0f, 1.0f,1.0f,
1.0f,-1.0f,-1.0f,1.0f,

-1.0f,-1.0f,-1.0f,1.0f,
-1.0f,-1.0f, 1.0f,1.0f,
1.0f,-1.0f, 1.0f,1.0f,

-1.0f, 1.0f, 1.0f,1.0f,
1.0f, 1.0f,-1.0f,1.0f,
1.0f, 1.0f, 1.0f,1.0f,

-1.0f, 1.0f, 1.0f,1.0f,
-1.0f, 1.0f,-1.0f,1.0f,
1.0f, 1.0f,-1.0f,1.0f,
};

void generateCubes(glm::mat4 M, glm::mat4 V, glm::mat4 P, glm::mat4 Mhelp, glm::vec3* positions, float angle_x, float angle_y) {
	for (int i = 0; i < 4; i++) {
		//M = glm::mat4(1.0f);
		M = Mhelp;
		M = glm::translate(M, positions[i]);
		M = glm::scale(M, glm::vec3(0.2f));
		M = glm::translate(M, glm::vec3(0.0f, -0.5f, 0.0f));
		//M = glm::rotate(M, PI, glm::vec3(0.0f, 1.0f, 1.0f)); 
		//M = glm::rotate(M, skeleton_x, glm::vec3(0.0f, 0.0f, 1.0f));
		//M = glm::rotate(M, skeleton_y, glm::vec3(1.0f, 0.0f, 0.0f));
		V = glm::lookAt(pos, pos + calcDir(angle_x, angle_y), glm::vec3(0.0f, 0.1f, 0.0f));
		P = glm::perspective(glm::radians(40.0f), 1.0f, 1.0f, 50.0f);
		glUniformMatrix4fv(spLambertTextured->u("M"), 1, false, value_ptr(M)); //dla macierzy obiektu
		glUniformMatrix4fv(spLambertTextured->u("V"), 1, false, value_ptr(V)); //dla macierzy widoku
		glUniformMatrix4fv(spLambertTextured->u("P"), 1, false, value_ptr(P)); //dla macierzy przyiecia
		glEnableVertexAttribArray(spLambertTextured->a("vertex"));
		glVertexAttribPointer(spLambertTextured->a("vertex"), 4, GL_FLOAT, false, 0, cubev);
		glEnableVertexAttribArray(spLambertTextured->a("normal"));
		glVertexAttribPointer(spLambertTextured->a("normal"), 4, GL_FLOAT, false, 0, cuben);
		glEnableVertexAttribArray(spLambertTextured->a("texCoord"));
		glVertexAttribPointer(spLambertTextured->a("texCoord"), 2, GL_FLOAT, false, 0, cubet);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	glDisableVertexAttribArray(spLambertTextured->a("vertex"));
}


#endif
