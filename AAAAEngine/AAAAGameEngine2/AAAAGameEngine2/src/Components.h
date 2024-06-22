#pragma once

#include "Physics.h"
#include "MeshComponent.h"
#include "DataStructures.h"

/**
 * @struct ToRender
 * @brief Structure representing whether an object should be rendered.
 */
struct ToRender
{
    bool toRender; /**< Boolean indicating whether the object should be rendered. */

    /**
     * @brief Constructs a ToRender object with the specified rendering status.
     * @param render Boolean indicating whether the object should be rendered.
     */
    ToRender(bool render) : toRender(render) {}
};

/**
 * @struct Transform
 * @brief Structure representing the transformation of an object.
 */
struct Transform
{
    glm::vec3 m_pos;   /**< Position of the object. */
    glm::vec3 m_rot;   /**< Rotation of the object. */
    glm::vec3 m_scale; /**< Scale of the object. */

    /**
     * @brief Default constructor. Initializes position to (0,0,0), rotation to (0,0,0), and scale to (1,1,1).
     */
    Transform() : m_pos(0, 0, 0), m_rot(0, 0, 0), m_scale(1, 1, 1) {}

    /**
     * @brief Constructs a Transform object with the specified position, rotation, and scale.
     * @param pos Position vector.
     * @param rot Rotation vector.
     * @param scale Scale vector.
     */
    Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale) : m_pos(pos), m_rot(rot), m_scale(scale) {}

    /**
     * @brief Returns the component of the transformation vector at the specified index.
     * @param trans Index of the transformation component (0 for position, 1 for rotation, 2 for scale).
     * @return Reference to the transformation component vector.
     */
    glm::vec3 Get(unsigned int trans);

    /**
     * @brief Sets the component of the transformation vector at the specified index.
     * @param trans Index of the transformation component (0 for position, 1 for rotation, 2 for scale).
     * @param vec New value for the transformation component vector.
     */
    void Set(unsigned int trans, glm::vec3 vec);
};

/**
 * @struct PhysicsBody
 * @brief Structure representing a physics body.
 */
struct PhysicsBody
{
    Physics physics; /**< Physics properties of the body. */

    /**
     * @brief Default constructor for PhysicsBody.
     */
    PhysicsBody();

    /**
     * @brief Returns a physics properties of the body.
     * @return Physics object.
     */
	Physics Get();

    /**
     * @brief Sets a Phyhsics object to physics.
     */
	void Set(Physics &phys);
};
