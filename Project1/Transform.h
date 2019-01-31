#ifndef TRANSFORM_INCLUDED_H
#define TRANSFORM_INCLUDED_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Transform
{
public:
	Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3()) :
		myPos(pos),
		myRot(rot),
		myScale(scale)
	{

	}

	inline glm::mat4 GetModel() const
	{
		glm::mat4 posMat = glm::translate(myPos);
		glm::mat4 scaleMat = glm::scale(glm::vec3(1.0, 1.0, 1.0));
		glm::mat4 rotX = glm::rotate(myRot.x, glm::vec3(1.0, 0.0, 0.0));
		glm::mat4 rotY = glm::rotate(myRot.y, glm::vec3(0.0, 1.0, 0.0));
		glm::mat4 rotZ = glm::rotate(myRot.z, glm::vec3(0.0, 0.0, 1.0));
		glm::mat4 rotMat = rotX * rotY * rotZ;

		return posMat * rotMat * scaleMat;
	}

	inline glm::vec3* GetPos() { return &myPos; }
	inline glm::vec3* GetRot() { return &myRot; }
	inline glm::vec3* GetScale() { return &myScale; }

	inline void SetPos(glm::vec3& pos) { this->myPos = pos; }
	inline void SetRot(glm::vec3& rot) { this->myRot = rot; }
	inline void SetScale(glm::vec3& scale) { this->myScale = scale; }

	glm::vec3 myPos, myRot, myScale;
private:

};


#endif // !TRANSFORM_INCLUDED_H