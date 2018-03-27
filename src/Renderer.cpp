#include "Renderer.h"

glm::mat4 Renderer::model(1.0f);
glm::mat4 Renderer::view(1.0f);
glm::mat4 Renderer::projection(1.0f);

std::ostream& operator<<(std::ostream& stream, glm::vec3 v)
{
	return stream << "x: " << v.x << ", y: " << v.y << ", z: " << v.z;
}

std::ostream& operator<<(std::ostream& stream, DirectLight dl)
{
	return stream << "Direction: " << dl.Direction
		<< "\nAmbient: " << dl.Ambient
		<< "\nDiffuse: " << dl.Diffuse
		<< "\nSpecular: " << dl.Specular
		<< "\nStrength: " << dl.Strength;
}

std::ostream& operator<<(std::ostream& stream, PointLight pl)
{
	return stream << "Position: " << pl.Position
		<< "\nAmbient: " << pl.Ambient
		<< "\nDiffuse: " << pl.Diffuse
		<< "\nSpecular: " << pl.Specular
		<< "\nStrength: " << pl.Strength
		<< "\nConstant: " << pl.Constant
		<< "\nLiniear: " << pl.Liniear
		<< "\nQuadratic: " << pl.Quadratic;
}

void Renderer::Draw(const Camera & camera, const Shader & shader3d, const Scene & scene)
{
	scene.updateLighting(shader3d);
	view = camera.getViewMatrix();
	projection = camera.getProjectionMatrix();
	glm::vec3 camPos = camera.getPosition();
	glm::mat4 rotation = glm::mat4(1.0f);

	shader3d.setMat4("view", view);
	shader3d.setMat4("projection", projection);
	shader3d.setMat4("rotation", rotation);

	shader3d.setVec3("cameraPos", camPos);

	unsigned int modelsCount = scene.modelsCount();
	for (unsigned int i = 0; i < modelsCount; i++)
	{
		const Model * model3d = scene.getModel(i);
		model = glm::mat4(1.0f);
		model = glm::translate(model, model3d->Position);
		model = glm::scale(model, model3d->Scale);
		shader3d.setMat4("model", model);
		shader3d.setVec3("Color", model3d->Color);

		model3d->draw(shader3d);
	}
	const Model * lampMdl = scene.getLampModel();
	for (unsigned int i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		glm::vec3 lightPos = scene.getPointLightPosition(i);
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, lampMdl->Scale);
		shader3d.setMat4("model", model);
		shader3d.setVec3("Color", lampMdl->Color);

		lampMdl->draw(shader3d);
	}
}

void Renderer::Draw(const Camera & camera, const Shader & shader3d, Model & model3d)
{
	model = glm::mat4(1.0f);
	model = glm::translate(model, model3d.Position);
	model = glm::scale(model, model3d.Scale);
	view = camera.getViewMatrix();
	projection = camera.getProjectionMatrix();
	glm::vec3 camPos = camera.getPosition();

	shader3d.setMat4("model", model);
	shader3d.setMat4("view", view);
	shader3d.setMat4("projection", projection);

	shader3d.setVec3("Color", model3d.Color);
	shader3d.setVec3("cameraPos", camPos);

	model3d.draw(shader3d);
}

void Renderer::Draw(const Camera & camera, const Shader & shader3d, Mesh & mesh)
{
	model = glm::mat4(1.0f);
	view = camera.getViewMatrix();
	projection = camera.getProjectionMatrix();
	glm::vec3 camPos = camera.getPosition();

	shader3d.setMat4("model", model);
	shader3d.setMat4("view", view);
	shader3d.setMat4("projection", projection);

	shader3d.setVec3("cameraPos", camPos);

	shader3d.use();
	mesh.draw();
}

void Renderer::Draw(GLFWwindow * window, const Shader & shader2d, Texture2D & texture)
{
	texture.draw(window, shader2d);
}
