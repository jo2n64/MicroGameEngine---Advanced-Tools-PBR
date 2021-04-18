#include "CameraBehaviour.hpp"
#include <mge/core/GameObject.hpp>
#include <mge/core/Camera.hpp>
#include <SFML/Window.hpp>

CameraBehaviour::CameraBehaviour(float pRotSpeed, float pMoveSpeed, float pSensitivity, Camera& pCamera) : 
	AbstractBehaviour(), _rotSpeed(pRotSpeed), _moveSpeed(pMoveSpeed), _sensitivity(pSensitivity), _camera(pCamera)
{
}

CameraBehaviour::~CameraBehaviour()
{
}

void CameraBehaviour::update(float pStep)
{
	_mousePos = sf::Mouse::getPosition();
	_diff = sf::Vector2i(_mousePos.x - _prevMousePos.x, _mousePos.y - _prevMousePos.y);
	_diffLength = sqrt(_diff.x * _diff.x + _diff.y * _diff.y);
	if (_diffLength == 0) {
		_diffLength = 1.0f;
	}
	_diffNormalized = sf::Vector2f(_diff.x / _diffLength, _diff.y / _diffLength);
	_handleRotation(pStep, _mousePos, _sensitivity);
	_handleZoom(pStep, _mousePos, _sensitivity);
}

void CameraBehaviour::_handleRotation(float pStep, sf::Vector2i pMousePos, float pSensitivity)
{
	
	float xSensitivity = _diffNormalized.x * _sensitivity;
	float ySensitivity = _diffNormalized.y * _sensitivity;

	glm::vec3 position = _owner->getLocalPosition();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		glm::mat4 rotXMatrix = glm::mat4(1.0f);
		glm::mat4 rotYMatrix = glm::mat4(1.0f);

		glm::vec3 forward = glm::normalize(position - glm::vec3(0, 0, 0));
		glm::vec3 temp = glm::vec3(0, 1, 0);
		glm::vec3 right = glm::cross(glm::normalize(temp), forward);
		glm::vec3 up = glm::cross(forward, right);

		glm::mat4 lookAtMatrix = glm::mat4(
			glm::vec4(right, 0),
			glm::vec4(up, 0),
			glm::vec4(forward, 0),
			glm::vec4(position, 1)
		);

		if (ySensitivity != 0.0f) {
			rotXMatrix = glm::rotate(glm::radians(-ySensitivity * pStep), right);
		}
		if (xSensitivity != 0.0f) {
			rotYMatrix = glm::rotate(glm::radians(-xSensitivity * pStep), up);
		}
		_owner->setTransform(rotYMatrix * rotXMatrix * lookAtMatrix);
		//std::cout << position.x << ", " << position.y << ", " << position.z << std::endl;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		_sensitivity -= 1.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		_sensitivity += 1.0f;
	}

	if (_sensitivity <= 0.0f) {
		_sensitivity = 0.0f;
	}

	_prevMousePos = _mousePos;
}

void CameraBehaviour::_handleZoom(float pStep, sf::Vector2i pMousePos, float pSensitivity)
{
	float ySensitivity = _diffNormalized.y * _sensitivity;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
		float fov = _camera.getFov() + ySensitivity;
		_camera.setFov(fov);
		_camera.setProjection(glm::perspective(glm::radians(fov), 4.0f / 3.0f, 0.1f, 1000.0f));
	}
}

