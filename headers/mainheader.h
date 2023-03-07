#pragma once
#ifndef LOAD_MAIN_HEADER

/*
Niniejszy program jest wolnym oprogramowaniem; mo¿esz go
rozprowadzaæ dalej i / lub modyfikowaæ na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundacjê Wolnego
Oprogramowania - wed³ug wersji 2 tej Licencji lub(wed³ug twojego
wyboru) którejœ z póŸniejszych wersji.

Niniejszy program rozpowszechniany jest z nadziej¹, i¿ bêdzie on
u¿yteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyœlnej
gwarancji PRZYDATNOŒCI HANDLOWEJ albo PRZYDATNOŒCI DO OKREŒLONYCH
ZASTOSOWAÑ.W celu uzyskania bli¿szych informacji siêgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnoœci¹ wraz z niniejszym programem otrzyma³eœ te¿ egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeœli nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/

#define GLM_FORCE_RADIANS

#include <GL/glew.h>					//<---open graphic library opengl
#include <GLFW/glfw3.h>					//<---uzupelnienie opengl (okienka, zdarzenia, animacje itp)
#include <glm/glm.hpp>					//<---opengl matematic (implementacja gotowych dzialan matematycznych)
#include <glm/gtc/type_ptr.hpp>			//<---opengl matematic (implementacja gotowych dzialan matematycznych)
#include <glm/gtc/matrix_transform.hpp>	//<---opengl matematic (implementacja gotowych dzialan matematycznych)
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/quaternion.hpp>

#include <assimp/Importer.hpp>			//<---biblioteka do wczytywania animacji				
#include <assimp/scene.h>				//<---symbolizuje ca³¹ zawartoœæ danego pliku
#include <assimp/postprocess.h>			//<---postprocesing wczytanego modelu

#include <windows.h>
#include <MMSystem.h>

#include <iostream>						//<---cin, cout, itp
#include <cstdlib>
#include <stddef.h>
#include <unordered_map>

#include "mainheaders/constants.h"		//<---stale (narazie przetrzymywana tam stala pi)
#include "mainheaders/lodepng.h"					//<---wczytywanie plikow png do wczytywania tekstur
#include "mainheaders/shaderprogram.h"				//<---program cieniujacy uruchamiany na CPU 

#include "headers/structure.h"			//<---struktury projektu
#include "headers/variables.h"			//<---spis zmiennych
#include "headers/matrixtransform.h"	//<---transformacja macierzy z aiMatri do glm
#include "headers/keyboard.h"			//<---obsluga klawiatury
#include "headers/errors.h"				//<---procedury obslugi bledow
#include "headers/floor.h"				//<---wspolrzedne podlogi/rysowanie podlogi
#include "headers/light.h"				//<---wspolrzedne swiatla/rysowanie swiatla
#include "headers/cubes.h"				//<---wspolrzedne kostek/rysowanie kostek
#include "headers/readtexture.h"		//<---czytanie tekstur
#include "headers/bonetransform.h"		//<---budowanie drzewa kosci transformacji
#include "headers/loadmodel.h"			//<---ladowanie modelu
#include "headers/initandfree.h"		//<---tworzenie i usuwanie danej sceny

#include <semaphore>

#endif