#include "WorldPhysics.h"

reactphysics3d::PhysicsCommon WorldPhysics::m_physicsCommon;
reactphysics3d::PhysicsWorld* WorldPhysics::m_worldPhysics = nullptr;



void addWall(rp3d::Vector3 Pos, rp3d::Vector3 thickness) {
    rp3d::BoxShape* boxShape = WorldPhysics::m_physicsCommon.createBoxShape(thickness);
    rp3d::Transform transform(Pos, rp3d::Quaternion::identity());

    rp3d::RigidBody* body = WorldPhysics::m_worldPhysics->createRigidBody(transform);

    body->addCollider(boxShape, reactphysics3d::Transform::identity());
    reactphysics3d::BodyType bodyType = reactphysics3d::BodyType::STATIC;
    body->setType(bodyType);
    body->getCollider(0)->getMaterial().setFrictionCoefficient(0.0);
    body->getCollider(0)->getMaterial().setBounciness(0.0);
}

void applyForceToRB(reactphysics3d::RigidBody* rb, glm::vec3 force)
{
    rb->applyLocalForceAtCenterOfMass(GLMToVec3(force));
}

void setVelocityToRB(reactphysics3d::RigidBody* rb, glm::vec3 velocity)
{
	rb->setLinearVelocity(GLMToVec3(velocity));
}



void setupCollisionCallback(rp3d::RigidBody* body1, rp3d::RigidBody* body2) {
    // Create an instance of your collision callback class
    std::shared_ptr<MyCollisionCallback> collisionCallback = std::make_shared<MyCollisionCallback>(body1, body2);

    // Register the collision callback with the physics world
    WorldPhysics::m_worldPhysics->testCollision(body1, body2, *collisionCallback);
}


void SetWorldBoundary(reactphysics3d::Vector3 min, reactphysics3d::Vector3 max, float thickness) {
    // Calculate the absolute dimensions
    reactphysics3d::Vector3 dimensions = reactphysics3d::Vector3(std::abs(max.x - min.x), std::abs(max.y - min.y), std::abs(max.z - min.z));

    // Calculate the center of the boundary
    reactphysics3d::Vector3 midPoint = (max + min) * 0.5;

    // Adjust thickness considering the absolute dimensions
    reactphysics3d::Vector3 thicknessVec = dimensions / 2 + reactphysics3d::Vector3(thickness, thickness, thickness);

    // Min x wall
    reactphysics3d::Vector3 trans1(min.x, midPoint.y, midPoint.z);
    addWall(trans1, reactphysics3d::Vector3(thickness, thicknessVec.y, thicknessVec.z));

    // Min y wall
    reactphysics3d::Vector3 trans2(midPoint.x, min.y, midPoint.z);
    addWall(trans2, reactphysics3d::Vector3(thicknessVec.x, thickness, thicknessVec.z));

    // Min z wall
    reactphysics3d::Vector3 trans3(midPoint.x, midPoint.y, min.z);
    addWall(trans3, reactphysics3d::Vector3(thicknessVec.x, thicknessVec.y, thickness));

    // Max x wall
    reactphysics3d::Vector3 trans4(max.x, midPoint.y, midPoint.z);
    addWall(trans4, reactphysics3d::Vector3(thickness, thicknessVec.y, thicknessVec.z));

    // Max y wall
    reactphysics3d::Vector3 trans5(midPoint.x, max.y, midPoint.z);
    addWall(trans5, reactphysics3d::Vector3(thicknessVec.x, thickness, thicknessVec.z));

    // Max z wall
    reactphysics3d::Vector3 trans6(midPoint.x, midPoint.y, max.z);
    addWall(trans6, reactphysics3d::Vector3(thicknessVec.x, thicknessVec.y, thickness));
}

WorldPhysics::~WorldPhysics()
{
    m_physicsCommon.destroyPhysicsWorld(m_worldPhysics);
}

void WorldPhysics::inializeWorldPhysics(float gravityx, float gravityy, float gravityz)
{
    accumulator = 0.0f;
    timeStep = 1.0f / 30.0f;
    reactphysics3d::PhysicsWorld::WorldSettings settings;
    settings.defaultVelocitySolverNbIterations = 50;
    settings.defaultPositionSolverNbIterations = 50;
    settings.isSleepingEnabled = false;
    settings.gravity = reactphysics3d::Vector3(gravityx, gravityy, gravityz); // Gravity vector

    WorldPhysics::m_worldPhysics = WorldPhysics::m_physicsCommon.createPhysicsWorld(settings);
}

void WorldPhysics::updatePhysics()
{
    while (accumulator >= timeStep)
    {
        WorldPhysics::m_worldPhysics->update(timeStep);

        accumulator -= timeStep;
    }
}

void WorldPhysics::accumulate(float deltaTime)
{
    accumulator += deltaTime;
}

rp3d::Vector3 WorldPhysics::GetGravity()
{
    return m_worldPhysics->getGravity();
}

void WorldPhysics::CleanUp()
{
    m_physicsCommon.destroyPhysicsWorld(m_worldPhysics);
}

reactphysics3d::Vector3 GLMToVec3(glm::vec3 vector)
{
    return reactphysics3d::Vector3(vector.x, vector.y, vector.z);
}

glm::vec3 Vec3ToGLM(rp3d::Vector3 vector)
{
    return glm::vec3(vector.x, vector.y, vector.z);
}

MyCollisionCallback::~MyCollisionCallback()
{
    delete[] mBody1;
    delete[] mBody2;
}
