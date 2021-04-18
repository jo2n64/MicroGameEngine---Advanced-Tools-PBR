#include "mge/behaviours/AbstractBehaviour.hpp"
#include "SFML/Graphics.hpp"
#include "glm.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Camera.hpp"

#pragma once
class CameraBehaviour : public AbstractBehaviour
{
public:
	CameraBehaviour(float pRotSpeed, float pMoveSpeed, float pSensitivity, Camera& pCamera);
	virtual ~CameraBehaviour();
	virtual void update(float pStep);
private:
	float _moveSpeed, _rotSpeed;
	float _sensitivity;
	float _diffLength;
	sf::Vector2i _mousePos, _prevMousePos = sf::Vector2i(0,0), _diff;
	sf::Vector2f _diffNormalized;
	Camera& _camera;
private:
	void _handleRotation(float pStep, sf::Vector2i pMousePos, float pSensitivity);
	void _handleZoom(float pStep, sf::Vector2i pMousePos, float pSensitivity);
};

