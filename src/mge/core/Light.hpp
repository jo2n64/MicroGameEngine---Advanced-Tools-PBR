#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "glm.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Camera.hpp"

/**
 * Exercise for the student: implement the Light class...
 * Imagine things like setLightType, setLightIntensity, setFalloffAngle etc, see the corresponding lectures
 */
class Light : public GameObject
{
	public:
		Light(const std::string& aName = nullptr, const glm::vec3& aPosition = glm::vec3( 2.0f, 10.0f, 5.0f ));
		virtual ~Light();

        //override set parent to register/deregister light...
        virtual void _setWorldRecursively (World* pWorld) override;
		void setLightColor(const glm::vec3 pLightColor);
		void setAmbientColor(const glm::vec3 pAmbientColor);
		void setSpecularIntensity(const float pSpecIntensity);
		void setAmbientIntensity(const float pAmbientIntensity);

		glm::vec3 getLightColor() const;
		glm::vec3 getAmbientColor() const;
		float getAmbientIntensity() const;
		float getSpecularIntensity() const;

	private:
		glm::vec3 _lightColor;
		glm::vec3 _ambientColor;
		glm::vec3 _lightPosition;
		float _specularIntensity;
		float _ambientIntensity;
};

#endif // LIGHT_HPP
