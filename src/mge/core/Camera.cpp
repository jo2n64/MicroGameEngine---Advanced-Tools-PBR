#include "glm.hpp"
#include "mge/core/Camera.hpp"

Camera::Camera( std::string pName, glm::vec3 pPosition, float pFov, glm::mat4 pProjectionMatrix )
:	GameObject(pName, pPosition), _projection(pProjectionMatrix), _fov(pFov)
{
}

Camera::~Camera()
{
	//dtor
}

glm::mat4& Camera::getProjection() {
    return _projection;
}

void Camera::setProjection(const glm::mat4& projection)
{
	_projection = projection;
}

void Camera::setFov(const float pFov)
{
	_fov = pFov;
}

float Camera::getFov() const
{
	return _fov;
}

void Camera::setPitch(const float pPitch)
{
	_pitch = pPitch;
	std::cout << "Pitch is: " << _pitch << std::endl;
}

float Camera::getPitch() const
{
	return _pitch;
}

void Camera::setYaw(const float pYaw)
{
	_yaw = pYaw;
}

float Camera::getYaw() const
{
	return _yaw;
}




