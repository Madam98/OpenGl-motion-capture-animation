#pragma once
#ifndef KEYBOARD_H

//********** Obsluga klawiszy **********
void key_callback(
	GLFWwindow* window,
	int key,
	int scancode,
	int action,
	int mod
) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_LEFT)		speed_y = 1;
		if (key == GLFW_KEY_RIGHT)		speed_y = -1;
		if (key == GLFW_KEY_PAGE_UP)	speed_x = -1;
		if (key == GLFW_KEY_PAGE_DOWN)	speed_x = 1;
		if (key == GLFW_KEY_UP)			walk_speed = 2;
		if (key == GLFW_KEY_DOWN)		walk_speed = -2;
		if (key == GLFW_KEY_A)			speed_skeleton_x = -PI;
		if (key == GLFW_KEY_D)			speed_skeleton_x = PI;
		if (key == GLFW_KEY_W)			speed_skeleton_y = -PI;
		if (key == GLFW_KEY_S)			speed_skeleton_y = PI;
		if (key == GLFW_KEY_O)			speed_light = 1;
		if (key == GLFW_KEY_P)			speed_light = -1;
	}
	if (action == GLFW_RELEASE) {
		if (key == GLFW_KEY_LEFT || key == GLFW_KEY_RIGHT)			speed_y = 0;
		if (key == GLFW_KEY_PAGE_UP || key == GLFW_KEY_PAGE_DOWN)	speed_x = 0;
		if (key == GLFW_KEY_UP || key == GLFW_KEY_DOWN)				walk_speed = 0;
		if (key == GLFW_KEY_A || key == GLFW_KEY_D)					speed_skeleton_x = 0;
		if (key == GLFW_KEY_W || key == GLFW_KEY_S)					speed_skeleton_y = 0;
		if (key == GLFW_KEY_O || key == GLFW_KEY_P)					speed_light = 0;
	}
	//if(action == GLFW_REPEAT)
}
// Do obrotow
glm::vec3 calcDir(float kat_x, float kat_y) {
	glm::vec4 dir = glm::vec4(0, 0, 1, 0);
	glm::mat4 M = glm::rotate(glm::mat4(1.0f), kat_y, glm::vec3(0, 1, 0));
	M = glm::rotate(M, kat_x, glm::vec3(1, 0, 0));
	dir = M * dir;
	return glm::vec3(dir);
}

#endif 
