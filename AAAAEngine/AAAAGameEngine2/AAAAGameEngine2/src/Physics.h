#pragma once

#include "reactphysics3d/reactphysics3d.h" 
#include "WorldPhysics.h"
#include "DataStructures.h"

/**
 * @enum bodytype
 * @brief Enum representing the type of rigid body.
 */
enum class bodytype
{
    STATIC, /**< Static rigid body. */
    KINEMATIC, /**< Kinematic rigid body. */
    DYNAMIC /**< Dynamic rigid body. */
};

/**
 * @class Physics
 * @brief Class representing the physics engine interface.
 */
class Physics
{
public:
    /**
     * @brief Default constructor for Physics.
     */
    Physics();

    /**
     * @brief Destructor for Physics.
     */
    ~Physics();

    /**
     * @brief Adds a rigid body to the physics simulation.
     * @param pos The initial position of the rigid body.
     * @param mass The mass of the rigid body.
     * @param type The type of rigid body (static, kinematic, or dynamic).
     * @param gravity Flag indicating whether gravity affects the rigid body.
     */
    void addRigidBody(glm::vec3 pos, float mass, bodytype type, bool gravity);

    /**
     * @brief Sets the rigid body for the physics object.
     * @param rigidBody The rigid body to set.
     */
    void SetRigidBody(reactphysics3d::RigidBody& rigidBody);

    /**
     * @brief Retrieves the rigid body.
     * @return Pointer to the rigid body.
     */
    reactphysics3d::RigidBody* GetRigidBody();

    // Functions for adding different shapes to the physics simulation

    // Functions for adding different shapes to the physics simulation

    /**
     * @brief Adds a box collider to the physics simulation.
     * @param pos The initial position of the box collider.
     * @param size The size of the box collider.
     */
    void addBox(glm::vec3 pos, glm::vec3 size);

    /**
     * @brief Adds a sphere collider to the physics simulation.
     * @param pos The initial position of the sphere collider.
     * @param radius The radius of the sphere collider.
     */
    void addSphere(glm::vec3 pos, float radius);

    /**
     * @brief Adds a capsule collider to the physics simulation.
     * @param pos The initial position of the capsule collider.
     * @param radius The radius of the capsule collider.
     * @param height The height of the capsule collider.
     */
    void addCapsule(glm::vec3 pos, float radius, float height);

    /**
     * @brief Adds a convex mesh collider to the physics simulation.
     * @param pos The initial position of the convex mesh collider.
     * @param scale The scale of the convex mesh collider.
     * @param vertices The array of vertices defining the convex mesh.
     * @param numVertices The number of vertices in the mesh.
     * @param faces The array of faces defining the convex mesh.
     * @param numFaces The number of faces in the mesh.
     * @param indices The array of indices defining the mesh faces.
     */
    void addConvexMesh(glm::vec3 pos, reactphysics3d::Vector3 scale, float* vertices, rp3d::uint32 numVertices, reactphysics3d::PolygonVertexArray::PolygonFace* faces, rp3d::uint32 numFaces, rp3d::uint32* indices);

    /**
     * @brief Adds a concave mesh collider to the physics simulation.
     * @param pos The initial position of the concave mesh collider.
     * @param scale The scale of the concave mesh collider.
     * @param vertices The array of vertices defining the concave mesh.
     * @param numVertices The number of vertices in the mesh.
     * @param numTriangles The number of triangles in the mesh.
     * @param indices The array of indices defining the mesh triangles.
     */
    void addConcaveMesh(glm::vec3 pos, reactphysics3d::Vector3 scale, float* vertices, rp3d::uint32 numVertices, int numTriangles, rp3d::uint32* indices);

    /**
     * @brief Adds a height field collider to the physics simulation.
     * @param pos The initial position of the height field collider.
     * @param numColumns The number of columns in the height field.
     * @param numRows The number of rows in the height field.
     * @param minHeight The minimum height of the terrain.
     * @param maxHeight The maximum height of the terrain.
     * @param pointArray2d The 2D array of height values defining the terrain.
     * @param upAxis The up axis of the terrain.
     * @param scale The scale of the terrain.
     */
    void addHeightField(glm::vec3 pos, int numColumns, int numRows, reactphysics3d::decimal minHeight, reactphysics3d::decimal maxHeight, float* pointArray2d, int upAxis, glm::vec3 scale);

    void SetFrictionCoefficient(float friction);
    void SetBounciness(float bounce);

    float GetMass();

private:
    /**
    * @brief Converts a glm::vec3 vector to a reactphysics3d::Vector3 vector.
    * @param vect The glm::vec3 vector to convert.
    * @return The converted reactphysics3d::Vector3 vector.
    */
    reactphysics3d::Vector3 ConvertVector3(glm::vec3 vect);

    /**
    * @brief Converts a bodytype enum to a reactphysics3d::BodyType enum.
    * @param type The bodytype enum to convert.
    * @return The converted reactphysics3d::BodyType enum.
    */
    reactphysics3d::BodyType ConvertBodyType(bodytype type);
    reactphysics3d::RigidBody* m_rigidBody; /**< Pointer to the rigid body. */
    reactphysics3d::MemoryAllocator* m_allocator; /**< Pointer to the memory allocator. */

};
