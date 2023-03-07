#pragma once
#ifndef LOAD_MAIN_HEADER

/*
Niniejszy program jest wolnym oprogramowaniem; mo�esz go
rozprowadza� dalej i / lub modyfikowa� na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundacj� Wolnego
Oprogramowania - wed�ug wersji 2 tej Licencji lub(wed�ug twojego
wyboru) kt�rej� z p�niejszych wersji.

Niniejszy program rozpowszechniany jest z nadziej�, i� b�dzie on
u�yteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domy�lnej
gwarancji PRZYDATNO�CI HANDLOWEJ albo PRZYDATNO�CI DO OKRE�LONYCH
ZASTOSOWA�.W celu uzyskania bli�szych informacji si�gnij do
Powszechnej Licencji Publicznej GNU.

Z pewno�ci� wraz z niniejszym programem otrzyma�e� te� egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
je�li nie - napisz do Free Software Foundation, Inc., 59 Temple
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
#include <assimp/scene.h>				//<---symbolizuje ca�� zawarto�� danego pliku
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