#include "CameraBehaviour.hpp"
#include <mge/core/GameObject.hpp>
#include <mge/core/Camera.hpp>
#include <SFML/Window.hpp>

CameraBehaviour::CameraBehaviour(float pRotSpeed, float pMoveSpeed, float pSensitivity, Camera* pCamera) :
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

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		glm::mat4 rotXMatrix = glm::mat4(1.0f);
		glm::mat4 rotYMatrix = glm::mat4(1.0f);
		//if (_pitch > 50.0f - (ySensitivity * pStep)) {
		//	_pitch = 50.0f;
		//}
		//else if (_pitch < -50.0f + (ySensitivity * pStep)) {
		//	_pitch = -50.0f;
		//}
		//_pitch += ySensitivity * pStep;
		//_yaw += xSensitivity * pStep;

		//glm::vec3 target = glm::vec3(0, 0, 0);
		//glm::vec3 cameraTargetVec = position - target;

		////setting up the lookAt matrix - basically acts as the transform we will use to translate
		//glm::vec3 forward = glm::normalize(cameraTargetVec);
		//glm::vec3 temp = glm::vec3(0, 1, 0);
		//glm::vec3 right = glm::normalize(glm::cross(temp, forward));
		//glm::vec3 up = glm::cross(right, forward);

		//_owner->setLocalPosition(position);

		//

		//if (ySensitivity != 0.0f) {
		//	if (_pitch < 50.0f && _pitch > -50.0f) {
		//		rotXMatrix = glm::rotate(glm::radians(-ySensitivity * pStep), right);
		//	}
		//}
		//if (xSensitivity != 0.0f) {
		//	rotYMatrix = glm::rotate(glm::radians(-xSensitivity * pStep), glm::vec3(0,1,0));
		//}

		//order from right to left - translates first, then rotates
		//_owner->setTransform(rotXMatrix * rotYMatrix * _owner->getTransform());
		
		_handleMovement(pStep, pSensitivity);
		if (ySensitivity != 0.0f) {
			rotXMatrix = glm::rotate(glm::radians(-ySensitivity * pStep * _rotSpeed), glm::vec3(1, 0, 0));
			_owner->setTransform(_owner->getTransform() * rotXMatrix);
		}
		if (xSensitivity != 0.0f) {
			rotYMatrix = glm::rotate(glm::radians(-xSensitivity * pStep * _rotSpeed), glm::vec3(0, 1, 0));
			_owner->setTransform(glm::translate(position) * rotYMatrix * glm::translate(-position) * _owner->getTransform());
		}
		//_owner->setTransform(glm::translate(position) * rotXMatrix * rotYMatrix * glm::translate(-position) * _owner->getTransform());

		//std::cout << "Pitch: " << _pitch << std::endl;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
		_sensitivity -= 1.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
		_sensitivity += 1.0f;
	}

	if (_sensitivity <= 0.0f) {
		_sensitivity = 0.0f;
	}

	_prevMousePos = _mousePos;
}

void CameraBehaviour::_handleZoom(float pStep, sf::Vector2i pMousePos, float pSensitivity)
{
	float ySensitivity = _diffNormalized.y;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
		float fov = _camera->getFov() + ySensitivity;
		if (fov <= 1.0f) {
			fov = 1.0f;
		}
		if (fov >= 80.0f) {
			fov = 80.0f;
		}
		_camera->setFov(fov);
		_camera->setProjection(glm::perspective(glm::radians(fov), 4.0f / 3.0f, 0.1f, 1000.0f));

	}
}

void CameraBehaviour::_handleMovement(float pStep, float pSensitivity)
{	
	float moveSpeedX = 0.0f, moveSpeedY = 0.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		moveSpeedX = -_moveSpeedX;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		moveSpeedX = _moveSpeedX;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		moveSpeedY = -_moveSpeedY;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		moveSpeedY = _moveSpeedY;
	}
	_owner->translate(glm::vec3(moveSpeedX * pStep, 0, moveSpeedY * pStep));
}

