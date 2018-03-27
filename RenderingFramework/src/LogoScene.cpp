#include "LogoScene.h"

void LogoScene::drawDigitsCircle(Shader & shader3d) const
{
	for (Digit digit : _digits)
	{
		glm::mat4 model(1.0f);
		glm::mat4 rotation(1.0f);
		model = glm::translate(model, digit.Position);
		model = glm::scale(model, _digit0->Scale);
		rotation = glm::rotate(rotation, glm::radians(_digitsRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		rotation = glm::rotate(rotation, glm::radians(_digitsRotation.z - digit.zRotation * 360.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		rotation = glm::rotate(rotation, glm::radians(_digitsRotation.y + digit.zRotation * 12312.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		shader3d.setVec3("Color", _digit0->Color);
		shader3d.setMat4("rotation", rotation);
		shader3d.setMat4("model", model);
		if (digit.Number) _digit1->draw(shader3d);
		else _digit0->draw(shader3d);
	}
}

void LogoScene::initDigitsPositions(glm::vec3 circlePos, unsigned int count, float beta, float gamma)
{
	const float PI = glm::pi<float>();
	float alpha = (2 * PI - beta - gamma) / count;
	float r = 1.5;
	glm::vec3 pos(0.0, 0.0, 0.0);
	float rotation, nAlpha = (alpha / (2 * PI)),
		nBeta = beta / (2 * PI),
		nGamma = gamma / (2 * PI);

	glm::vec3 scale(1.0);
	for (unsigned int i = 0; i < count; i++)
	{
		//angle = alpha * i + beta;
		rotation = 0.25f - nAlpha * i - nBeta;
		pos.x = cos(alpha * i + beta)*r + circlePos.x;
		pos.y = sin(alpha * i + beta)*r + circlePos.y;
		_digits.push_back({ i % 2 == 0, pos, rotation });
	}
}

void LogoScene::loadDigitsModels()
{
	auto j = json::parse(jsonData);

	std::string digit0path, digit1path;
	glm::vec3 rotation, scale, color;
	digit0path = j["model0"]["modelPath"].get<std::string>();
	rotation = JsonParser::getVec3(j["model0"]["rotation"]);
	scale = JsonParser::getVec3(j["model0"]["scale"]);
	color = JsonParser::getVec3(j["model0"]["color"]);
	_digit0 = new Model(digit0path, rotation);
	_digit0->Scale = scale;
	_digit0->Color = glm::vec3(color.x / 255.0f, color.y / 255.0f, color.z / 255.0f);

	digit1path = j["model1"]["modelPath"].get<std::string>();
	rotation = JsonParser::getVec3(j["model1"]["rotation"]);
	scale = JsonParser::getVec3(j["model1"]["scale"]);
	color = JsonParser::getVec3(j["model1"]["color"]);
	_digit1 = new Model(digit1path, rotation);
	_digit1->Scale = scale;
	_digit1->Color = glm::vec3(color.x/255.0f, color.y/255.0f, color.z/255.0f);
}

void LogoScene::update(float deltaTime)
{
	updateLightAnimation(deltaTime);
	_digitsRotation.y += deltaTime * _digitsRotationSpeed;
}

void LogoScene::updateLightAnimation(float deltaTime)
{
	//const glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 1.0f);
	const float speed = 90.0f;
	static float rotationAngle = 0.0f;
	rotationAngle += speed * deltaTime;
	glm::mat4 rotMat(1.0f);
	rotMat = glm::rotate(rotMat, glm::radians(rotationAngle), glm::vec3(-0.6f, 0.0f, 1.0f));
	glm::vec3 currentPos = rotMat * glm::vec4(_animLightPos, 1.0);
	currentPos += glm::vec3(2.0f, 0.0f, +0.5f);
	setPointLightPosition(0, currentPos);
}
