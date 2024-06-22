#include "Components.h"

glm::vec3 Transform::Get(unsigned int trans)
{
	switch (trans)
	{
	case 1:
		return m_pos;

	case 2:
		return m_rot;

	case 3:
		return m_scale;

	default:
		std::cout << "Error: Invalid Transform signature" << std::endl;
		break;
	}
	
}

void Transform::Set(unsigned int trans, glm::vec3 vec)
{
	switch (trans)
	{
	case 1:
		m_pos = vec;
		break;

	case 2:
		m_rot = vec;
		break;

	case 3:
		m_scale = vec;
		break;;

	default:
		std::cout << "Error: Invalid Transform signature" << std::endl;
		break;
	}
	
}

PhysicsBody::PhysicsBody()
{
	//physics.addRigidBody();
}

Physics PhysicsBody::Get()
{
	return physics;
}

void PhysicsBody::Set(Physics& phys)
{
	physics = phys;
}

