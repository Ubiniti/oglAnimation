#include "Renderer.h"
#include "LogoScene.h"

#include <iostream>
#include <string>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

static void error_callback(int error, const char* description)
{
	std::cout << "Error: " << description << std::endl;
}

int main(void)
{
	GLFWwindow* window;

	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glfwSwapInterval(1);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // hide mouse and snaps to center

	Shader shader3d("res/shaders/basic_vs.glsl", "res/shaders/basic_fs.glsl");

	// specifies which texture uses which slot
	// diffuse uses 0 by default
	shader3d.setTextureLayout();

	Camera mainCamera(glm::vec3(0.0f, 0.0f, 3.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT);

	shader3d.setFloat("material.shininess", 4);

	//Scene scene("res/scenes/scene.json");
	LogoScene scene("res/scenes/logoScene.json");
	scene.updateLighting(shader3d);

	GlCall(glEnable(GL_DEPTH_TEST));
	GlCall(glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));

	std::cout << glGetString(GL_VERSION) << std::endl;

	Clock clock;
	while (!glfwWindowShouldClose(window))
	{
		const float deltaTime = (float)clock.reset().asSeconds();
		const float speed = 6.0f;
		// input
		// -----
		// keyboard
		if(Keyboard::isKeyPreesed(window, Keyboard::W))
			mainCamera.move(FORWARD, speed*deltaTime);
		if (Keyboard::isKeyPreesed(window, Keyboard::S))
			mainCamera.move(BACKWARD, speed*deltaTime);
		if (Keyboard::isKeyPreesed(window, Keyboard::A))
			mainCamera.move(LEFT, speed*deltaTime);
		if (Keyboard::isKeyPreesed(window, Keyboard::D))
			mainCamera.move(RIGHT, speed*deltaTime);
		if (Keyboard::isKeyPreesed(window, Keyboard::ESCAPE))
			glfwSetWindowShouldClose(window, 1);
		// mouse
		const glm::vec2 mm = Mouse::getMouseMove(window);
		if (mm.x != 0 || mm.y != 0) 
			mainCamera.rotate(mm.x * deltaTime, mm.y * deltaTime);

		// render
		// ------
		glClearColor(0.258f, 0.525f, 0.956f, 1.0f);
		GlCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		scene.update(deltaTime);
		Renderer::Draw(mainCamera, shader3d, scene);
		scene.drawDigitsCircle(shader3d);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}