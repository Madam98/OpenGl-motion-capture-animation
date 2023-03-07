#pragma once
#ifndef LIGHT_H

float high = -1.0f; //zmiana wysokosci swiatel

//kolory swiatel
glm::vec3 colors[] = {
	glm::vec3(1.0f, 0.0f, 0.0f),
	glm::vec3(0.0f, 1.0f, 0.0f),
	glm::vec3(0.0f, 0.0f, 1.0f),
	glm::vec3(0.5f, 0.5f, 0.5f)
};


void generateLight(glm::vec3* colors, glm::vec3* positions, float light_angle, float light_y) {


	//zmiana pozycji swiatel
	positions[0].x = 0.0f + (2.0f * cos(light_angle));
	positions[0].y = light_y + (2.0f * sin(light_angle));
	positions[1].x = 0.0f + (2.0f * sin(light_angle));
	positions[1].y = light_y + (2.0f * -cos(light_angle));
	positions[2].x = 0.0f + (2.0f * -cos(light_angle));
	positions[2].y = light_y + (2.0f * -sin(light_angle));
	positions[3].x = 0.0f + (2.0f * -sin(light_angle));
	positions[3].y = light_y + (2.0f * cos(light_angle));
	positions[0].z = high;
	positions[1].z = high;
	positions[2].z = high;
	positions[3].z = high;


	spLambertTextured->use();
	glUniform3f(spLambertTextured->u("viewPos"), pos.x, pos.y, pos.z);

	//1 swiatlo
	glUniform3f(spLambertTextured->u("light[0].position"), positions[0].x, positions[0].y, positions[0].z);
	//glUniform3f(spLambertTextured->u("light[0].direction"), positions[0].x, positions[0].y, -1.0f);
	glUniform3f(spLambertTextured->u("light[0].ambient"), colors[0].x * 0.1, colors[0].y * 0.1, colors[0].z * 0.1);
	glUniform3f(spLambertTextured->u("light[0].diffuse"), colors[0].x, colors[0].y, colors[0].z);
	glUniform3f(spLambertTextured->u("light[0].specular"), colors[0].x, colors[0].y, colors[0].z);
	glUniform1f(spLambertTextured->u("light[0].constant"), 1.0f);
	glUniform1f(spLambertTextured->u("light[0].linear"), 0.09f);
	glUniform1f(spLambertTextured->u("light[0].quadratic"), 0.032f);
	//glUniform1f(spLambertTextured->u("light[0].cutOff"), glm::cos(glm::radians(12.5f)));
	//glUniform1f(spLambertTextured->u("light[0].outerCutOff"), glm::cos(glm::radians(15.0f)));

	//2 swiatlo
	glUniform3f(spLambertTextured->u("light[1].position"), positions[1].x, positions[1].y, positions[1].z);
	glUniform3f(spLambertTextured->u("light[1].ambient"), colors[1].x * 0.1, colors[1].y * 0.1, colors[1].z * 0.1);
	glUniform3f(spLambertTextured->u("light[1].diffuse"), colors[1].x, colors[1].y, colors[1].z);
	glUniform3f(spLambertTextured->u("light[1].specular"), colors[1].x, colors[1].y, colors[1].z);
	glUniform1f(spLambertTextured->u("light[1].constant"), 1.0f);
	glUniform1f(spLambertTextured->u("light[1].linear"), 0.09f);
	glUniform1f(spLambertTextured->u("light[1].quadratic"), 0.032f);

	//3 swiatlo
	glUniform3f(spLambertTextured->u("light[2].position"), positions[2].x, positions[2].y, positions[2].z);
	glUniform3f(spLambertTextured->u("light[2].ambient"), colors[2].x * 0.1, colors[2].y * 0.1, colors[2].z * 0.1);
	glUniform3f(spLambertTextured->u("light[2].diffuse"), colors[2].x, colors[2].y, colors[2].z);
	glUniform3f(spLambertTextured->u("light[2].specular"), colors[2].x, colors[2].y, colors[2].z);
	glUniform1f(spLambertTextured->u("light[2].constant"), 1.0f);
	glUniform1f(spLambertTextured->u("light[2].linear"), 0.09f);
	glUniform1f(spLambertTextured->u("light[2].quadratic"), 0.032f);

	//4 swiatlo
	glUniform3f(spLambertTextured->u("light[3].position"), positions[3].x, positions[3].y, positions[3].z);
	glUniform3f(spLambertTextured->u("light[3].ambient"), colors[3].x * 0.1, colors[3].y * 0.1, colors[3].z * 0.1);
	glUniform3f(spLambertTextured->u("light[3].diffuse"), colors[3].x, colors[3].y, colors[3].z);
	glUniform3f(spLambertTextured->u("light[3].specular"), colors[3].x, colors[3].y, colors[3].z);
	glUniform1f(spLambertTextured->u("light[3].constant"), 1.0f);
	glUniform1f(spLambertTextured->u("light[3].linear"), 0.09f);
	glUniform1f(spLambertTextured->u("light[3].quadratic"), 0.032f);
}

#endif