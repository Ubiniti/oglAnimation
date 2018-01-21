#include "Shader.h"
#include "Camera.h"
#include "Window.h"
#include "Color.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

// settings
const unsigned int SCR_WIDTH = 600;
const unsigned int SCR_HEIGHT = 600;

float blendvalue = 0.2f;
float rotation = 0.0f;

void processInput(float deltaTime);
unsigned int loadTexture(const char* path);
bool switchDisplayWireframe();

gle::Camera mainCamera(600, 600);

bool lightFollowCamera = true;

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
	gle::Shader ourShader("res/shaders/basic_vertex.glsl", "res/shaders/basic_fragment.glsl");
	std::cout << "light" << std::endl;
	gle::Shader lightShader("res/shaders/basic_vertex_light.glsl", "res/shaders/basic_fragment_light.glsl");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,		0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,		1.0f, 0.0f,0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,		1.0f, 1.0f,0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,		1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f, 0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,		1.0f, 1.0f, 0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,		1.0f, 1.0f, 0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,	0.0f, 1.0f, 0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f,	1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,	1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,-1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,	1.0f, 0.0f,-1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,		1.0f, 0.0f,1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,		1.0f, 1.0f,1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,		0.0f, 1.0f,1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,		0.0f, 1.0f,1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,		0.0f, 0.0f,1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,		1.0f, 0.0f,1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f, 0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,		1.0f, 1.0f, 0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,		1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,		1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f, 0.0f,  1.0f,  0.0f
	};

	unsigned int indices[] = {
		0, 1, 2,
		0, 1, 3
	};
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};

	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, lightVAO);


	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coords attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// normal attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	// glBindVertexArray(0);


	// bind the VAO (it was already bound, but just to demonstrate): seeing as we only have a single VAO we can 
	// just bind it beforehand before rendering the respective triangle; this is another approach.
	glBindVertexArray(VAO);

	// texture 1
	// ----------------
	unsigned int texture1, texture2, diffuseMap, specularMap, emissionMap;
	texture1 = loadTexture("res/imgs/container2.png");
	texture2 = loadTexture("res/imgs/awesomeface.png");
	diffuseMap = loadTexture("res/imgs/container2.png");
	specularMap = loadTexture("res/imgs/container2_specular.png");
	emissionMap = loadTexture("res/imgs/emission.jpg");

	// light
	//glm::vec3 lampPosition(1.2f, 1.0f, 2.0f);
	glm::vec3 lampPosition = mainCamera.Position;
	glm::vec3 lampColor(1.0f, 1.0f, 1.0f); //glm::vec3 lightColor(0.3f, 0.5f, 1.0f);

	glm::vec3 lightColor;

	ourShader.use();
	// material
	ourShader.setInt("material.diffuse", 0);
	ourShader.setInt("material.specular", 1);
	ourShader.setInt("material.emission", 2);
	ourShader.setFloat("material.shininess", 32.0f);
	// directional light
	ourShader.setVec3("dirLight.direction",-0.2f, -1.0f, -0.3f);
	ourShader.setVec3("dirLight.ambient", 0.2f, 0.2f, 0.2f);
	ourShader.setVec3("dirLight.diffuse", 1.0f, 1.0f, 1.0f);
	ourShader.setVec3("dirLight.specular", 1.0f, 1.0f, 1.0f);
	// point lights
	for (int i = 0; i < 4; i++)
	{
		ourShader.setVec3(("pointLights[" + std::to_string(i) + "].position").c_str(), pointLightPositions[i]);
		ourShader.setVec3(("pointLights[" + std::to_string(i) + "].ambient").c_str(), 0.2f, 0.2f, 0.2f);
		ourShader.setVec3(("pointLights[" + std::to_string(i) + "].diffuse").c_str(), 0.5f, 0.5f, 0.5f);
		ourShader.setVec3(("pointLights[" + std::to_string(i) + "].specular").c_str(), 1.0f, 1.0f, 1.0f);
		ourShader.setFloat(("pointLights[" + std::to_string(i) + "].constant").c_str(), 1.0f);
		ourShader.setFloat(("pointLights[" + std::to_string(i) + "].linear").c_str(), 0.09f);
		ourShader.setFloat(("pointLights[" + std::to_string(i) + "].quadratic").c_str(), 0.032f);
	}

	ourShader.setVec3("spotLight.ambient", 0.2f, 0.2f, 0.2f);
	ourShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
	ourShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);

	ourShader.setVec3("spotLight.position", lampPosition);
	ourShader.setVec3("spotLight.direction", mainCamera.Front);
	ourShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
	ourShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

	ourShader.setFloat("spotLight.constant", 1.0f);
	ourShader.setFloat("spotLight.linear", 0.09f);
	ourShader.setFloat("spotLight.quadratic", 0.032f);

	lightShader.use();
	lightShader.setVec3("lightColor", lampColor);

	// fps and frame time measure
	double lastTime = glfwGetTime(), currentTime;
	double deltaTime;
	int fps;

	glEnable(GL_DEPTH_TEST);

	// render loop
	// -----------
	double time1, time2,
		renderTime;
	while (window.isOpen())
	{
		currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		// draws debug info every 0.3s
		fps = (int)(1.0 / deltaTime);
		if ((int)(currentTime * 10) % 3 == 0 &&
			(int)(currentTime * 10) % 3 != (int)(lastTime * 10) % 3)
		{
			//system("cls");
			//std::cout << "fps: " << fps << std::endl;
		}
		lastTime = currentTime;

		// input
		// -----
		processInput((float)deltaTime);

		gle::Event ev;
		while (window.pollEvents(ev))
		{
			if (ev.type == gle::Event::KeyReleased && ev.key.code == gle::Keyboard::H)
				lightFollowCamera = !lightFollowCamera;
			if (ev.type == gle::Event::KeyReleased && ev.key.code == gle::Keyboard::F)
				switchDisplayWireframe();
			if (ev.type == gle::Event::MouseButtonPressed && ev.mouseButton.button == gle::Mouse::Left)
				std::cout << "LMB pressed!" << std::endl;
			if (ev.type == gle::Event::MouseMoved)
			{
				mainCamera.ProcessMouseMovement((float)ev.mouseMove.x, (float)ev.mouseMove.y);
			}
			if (ev.type == gle::Event::KeyPressed && ev.key.code == gle::Keyboard::ESCAPE)
				window.close();
			if (ev.type == gle::Event::MouseWheelScrolled)
				mainCamera.ProcessMouseScroll((float)ev.mouseScroll.delta);
		}

		// render
		// ------
		time1 = glfwGetTime();

		glm::mat4 view(1.0f),
			projection(1.0f);

		//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		view = mainCamera.getViewMatrix();
		projection = mainCamera.getProjectionMatrix();

		window.clear(gle::Color::CYAN);

		ourShader.use();
		ourShader.setVec3("viewPos", mainCamera.Position);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, emissionMap);


		ourShader.setMat4("view", view);
		ourShader.setMat4("projection", projection);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		if (lightFollowCamera)
		{
			ourShader.setVec3("spotLight.position", mainCamera.Position);
			ourShader.setVec3("spotLight.direction", mainCamera.Front);
		}

		ourShader.setFloat("time", currentTime);

		for (int i = 0; i < 10; i++)
		{
			glm::mat4 model(1.0f);
			float rotationAngle = 0;// (float)glfwGetTime()*glm::radians(20.0f);
			glm::vec3 rotationVec = glm::vec3(0.5f, 1.0f, 0.3f);

			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, rotationAngle, rotationVec);
			ourShader.setMat4("model", model);

			glm::mat4 normalModel(1.0f);
			normalModel = glm::rotate(normalModel, rotationAngle, rotationVec);
			ourShader.setMat4("normalModel", normalModel);

			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		// redner light objs
		// ------------------
		glm::mat4 model(1.0f);
		model = glm::translate(model, lampPosition);
		model = glm::scale(model, glm::vec3(0.2f));

		lightShader.use();
		lightShader.setMat4("view", view);
		lightShader.setMat4("projection", projection);
		lightShader.setMat4("model", model);

		if (!lightFollowCamera)
			glDrawArrays(GL_TRIANGLES, 0, 36);

		for (int i = 0; i < 4; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f));
			lightShader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		// --------------------

		time2 = glfwGetTime();
		renderTime = time2 - time1;
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwPollEvents();
		window.display();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glDeleteVertexArrays(1, &lightVAO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	return 0;
}

void processInput(float deltaTime)
{
	bool shift = gle::Keyboard::isKeyPreesed(gle::Keyboard::LEFT_SHIFT),
		space = gle::Keyboard::isKeyPreesed(gle::Keyboard::SPACE);

	// moving camera
	if(gle::Keyboard::isKeyPreesed(gle::Keyboard::W))
		mainCamera.ProcessKeyboard(gle::FORWARD, shift, space, deltaTime);
	if (gle::Keyboard::isKeyPreesed(gle::Keyboard::S))
		mainCamera.ProcessKeyboard(gle::BACKWARD, shift, space, deltaTime);
	if (gle::Keyboard::isKeyPreesed(gle::Keyboard::A))
		mainCamera.ProcessKeyboard(gle::LEFT, shift, space, deltaTime);
	if (gle::Keyboard::isKeyPreesed(gle::Keyboard::D))
		mainCamera.ProcessKeyboard(gle::RIGHT, shift, space, deltaTime);

	// blending value
	if (gle::Keyboard::isKeyPreesed(gle::Keyboard::UP))
	{
		if(blendvalue <= 1.0f)
			blendvalue += 0.01f;
	}
	if (gle::Keyboard::isKeyPreesed(gle::Keyboard::DOWN))
	{
		if (blendvalue >= 0.0f)
			blendvalue -= 0.01f;
	}
	// rotating value
	if (gle::Keyboard::isKeyPreesed(gle::Keyboard::RIGHT))
	{
		rotation += 1.0f;
	}
	if (gle::Keyboard::isKeyPreesed(gle::Keyboard::LEFT))
	{
		rotation -= 1.0f;
	}
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