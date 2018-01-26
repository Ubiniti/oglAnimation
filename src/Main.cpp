#include "Shader.h"
#include "Camera.h"
#include "Window.h"
#include "Color.h"
#include "Model.h"
#include "LogoScene.h"
#include "Clock.h"
#include "PointLight.h"
#include "DirLight.h"
#include "SpotLight.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>

#include <stb_image.h>

// settings
const unsigned int SCR_WIDTH = 600;
const unsigned int SCR_HEIGHT = 600;

void processInput(float deltaTime);
unsigned int loadTexture(const char* path);
bool switchDisplayWireframe();
static void initializeLights(gle::Shader shader, glm::vec3 pointLightPositions[4]);

//gle::Scene mainScene(SCR_WIDTH, SCR_HEIGHT);
int sceneId = 0;

gle::LogoScene mainScene(SCR_WIDTH, SCR_HEIGHT);
gle::LogoScene sponzaScene(SCR_WIDTH, SCR_HEIGHT);
gle::LogoScene boxesScene(SCR_WIDTH, SCR_HEIGHT);

gle::LogoScene *currentScene = &mainScene;

std::ostream& operator<<(std::ostream& stream, glm::vec2& vec)
{
	return stream << vec.x << ", " << vec.y;
}

int main()
{
	gle::Window window(SCR_WIDTH, SCR_HEIGHT, "Learn OpenGL");
	window.setVerticalSyncEnabled(true);
	// load and compile shaders
	std::cout << "basic" << std::endl;
	gle::Shader basicShader("res/shaders/basic_vertex.glsl", "res/shaders/basic_fragment.glsl");
	
	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};

	gle::Model models[9] {
		gle::Model("res/models/logo/logo_0.ply"),
		gle::Model("res/models/logo/logo_1.ply"),
		gle::Model("res/models/logo/logo_ik.stl"),
		gle::Model("res/models/logo/napis.ply"),
		gle::Model("res/models/lampa.stl"),
		gle::Model("res/models/flash.fbx"),
		gle::Model("res/models/sponza/sponza.obj"),
		gle::Model("res/models/boxes/boxes.obj"),
		gle::Model("res/models/sun.ply")
	};

	mainScene.load(basicShader, models, pointLightPositions);
	sponzaScene.addObject(models[6], glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.01f));
	boxesScene.addObject(models[7]);

	initializeLights(basicShader, pointLightPositions);

	for(int i = 0; i < 4; i++)
		mainScene.addObject(models[4], pointLightPositions[i], glm::vec3(0.75f, 0.0f, 0.0f), glm::vec3(0.2f));

	for (int i = 0; i < 4; i++)
		sponzaScene.addObject(models[4], pointLightPositions[i], glm::vec3(0.75f, 0.0f, 0.0f), glm::vec3(0.2f));

	for (int i = 0; i < 4; i++)
		boxesScene.addObject(models[4], pointLightPositions[i], glm::vec3(0.75f, 0.0f, 0.0f), glm::vec3(0.2f));

	double deltaTime;

	// render loop
	// -----------
	gle::Clock clock;

	while (window.isOpen())
	{
		// frame time measure
		deltaTime = clock.reset().asSeconds();

		// input
		// -----
		processInput((float)deltaTime);

		gle::Event ev;
		while (window.pollEvents(ev))
		{
			if (ev.type == gle::Event::KeyReleased && ev.key.code == gle::Keyboard::F)
				switchDisplayWireframe();
			if (ev.type == gle::Event::MouseButtonPressed && ev.mouseButton.button == gle::Mouse::Left)
				std::cout << "LMB pressed!" << std::endl;
			if (ev.type == gle::Event::MouseMoved)
			{
				currentScene->ProcessMouseMovement((float)ev.mouseMove.x, (float)ev.mouseMove.y);
			}
			if (ev.type == gle::Event::KeyPressed && ev.key.code == gle::Keyboard::ESCAPE)
				window.close();
			if (ev.type == gle::Event::MouseWheelScrolled)
				currentScene->ProcessMouseScroll((float)ev.mouseScroll.delta);
			if (ev.type == gle::Event::KeyPressed && ev.key.code == gle::Keyboard::NUM_1)
				currentScene = &mainScene;
			if (ev.type == gle::Event::KeyPressed && ev.key.code == gle::Keyboard::NUM_2)
				currentScene = &sponzaScene;
			if (ev.type == gle::Event::KeyPressed && ev.key.code == gle::Keyboard::NUM_3)
				currentScene = &boxesScene;
		}

		// render
		// ------
		window.clear(gle::Color::CYAN);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		currentScene->update(basicShader, deltaTime);

		currentScene->Draw(basicShader);

		window.display();
	}

	return 0;
}

void processInput(float deltaTime)
{
	bool shift = gle::Keyboard::isKeyPreesed(gle::Keyboard::LEFT_SHIFT),
		space = gle::Keyboard::isKeyPreesed(gle::Keyboard::SPACE);

	// moving camera
	if (gle::Keyboard::isKeyPreesed(gle::Keyboard::W))
		currentScene->ProcessKeyboard(gle::FORWARD, shift, space, deltaTime);
	if (gle::Keyboard::isKeyPreesed(gle::Keyboard::S))
		currentScene->ProcessKeyboard(gle::BACKWARD, shift, space, deltaTime);
	if (gle::Keyboard::isKeyPreesed(gle::Keyboard::A))
		currentScene->ProcessKeyboard(gle::LEFT, shift, space, deltaTime);
	if (gle::Keyboard::isKeyPreesed(gle::Keyboard::D))
		currentScene->ProcessKeyboard(gle::RIGHT, shift, space, deltaTime);
}

unsigned int loadTexture(const char* path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);

	if (data)
	{
		GLenum format = nrChannels == 1 ? GL_RED :
			nrChannels == 3 ? GL_RGB :
			nrChannels == 4 ? GL_RGBA : 0;

		glBindTexture(GL_TEXTURE_2D, textureID);
		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture at path: " << path << std::endl;
	}
	stbi_image_free(data);

	return textureID;
}

bool switchDisplayWireframe()
{
	static bool displayWireframe = false;

	// switch frame/texture display
	if (displayWireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	displayWireframe = !displayWireframe;

	return displayWireframe;
}

static void initializeLights(gle::Shader shader, glm::vec3 pointLightPositions[4])
{
	shader.use();
	shader.setFloat("material.shininess", 32.0f);
	// directional light
	gle::DirLight dirlight(glm::vec3(-0.2f, -1.0f, -0.3f));
	gle::SpotLight spotlight(glm::vec3(-0.2f, -1.0f, -0.3f));
	dirlight.upload(shader);
	spotlight.upload(shader);
	// point lights
	gle::PointLight pointlights[4] = 
	{
		gle::PointLight(pointLightPositions[0]),
		gle::PointLight(pointLightPositions[1]),
		gle::PointLight(pointLightPositions[2]),
		gle::PointLight(pointLightPositions[3])
	};
	for (int i = 0; i < 4; i++)
	{
		pointlights[i].upload(shader);
	}
}