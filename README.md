# OpenGl Animation Project

Simple OpenGL rendering frammework made for school project. It was meant to be the base for school logo animation. It was the simplest I could imagine, a title with roating digits.

Features:
  - 3d models display
  - camera with movement ability
  - Phong shading
  - Window and Shader abstraction
  - Scene loading from JSON

Project code compiles under VS 2017, but it lacks of some 3d models for legal reasons.

Libraries used:
  - [GLFW](http://www.glfw.org/)  for OpenGL window context
  - [GLM](glm.g-truc.net/) for maths
  - [Glad](http://glad.dav1d.de/) for loading pointers to OpenGL functions
  - [STB Image](https://github.com/nothings/stb)
  - [Assimp](http://assimp.org/) for 3d models loading
  - [nlohmann JSON](https://github.com/nlohmann/json)