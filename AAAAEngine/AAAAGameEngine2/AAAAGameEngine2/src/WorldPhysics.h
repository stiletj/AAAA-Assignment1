#pragma once
//world physics class
#include "reactphysics3d/reactphysics3d.h"
#include "glm.hpp"

static class WorldPhysics
{
public:
    ~WorldPhysics();

    static reactphysics3d::PhysicsWorld* m_worldPhysics; /**<Pointer to the physics world. */
    static reactphysics3d::Vector3 m_worldGravity; /**<The physics common object. */
    static reactphysics3d::PhysicsCommon m_physicsCommon; /**<Settings for the physics world. */

    /**
    * @brief Initializes the physics world.
    */
    static void inializeWorldPhysics(float gravityx, float gravityy, float gravityz);

    /**
    * @brief Updates the physics simulation.
    */
    static void updatePhysics();


    static void accumulate(float deltaTime);


    static rp3d::Vector3 GetGravity();


    static void CleanUp();
};

// Callback class for collision events
class MyCollisionCallback : public rp3d::CollisionCallback {
public:
    MyCollisionCallback(rp3d::RigidBody* body1, rp3d::RigidBody* body2)
        : mBody1(body1), mBody2(body2), mColliding(false) {}

    ~MyCollisionCallback();

    // Override the onContact() method to handle contact events
    virtual void onContact(const rp3d::CollisionCallback::CallbackData& callbackData) override {
        // Check if there is at least one contact point
        if (callbackData.getNbContactPairs() > 0) {
            // Get the first contact pair
            const rp3d::CollisionCallback::ContactPair& contactPair = callbackData.getContactPair(0);

            // Get the two colliding bodies
            const rp3d::CollisionBody* bodyA = contactPair.getBody1();
            const rp3d::CollisionBody* bodyB = contactPair.getBody2();

            // Check if the collision involves the specified bodies
            if ((bodyA == mBody1 && bodyB == mBody2) || (bodyA == mBody2 && bodyB == mBody1)) {
                // Set the colliding flag to true
                mColliding = true;
            }
        }
    }

    // Function to check if the specified bodies are colliding
    bool areColliding() const {
        return mColliding;
    }

private:
    rp3d::RigidBody* mBody1;
    rp3d::RigidBody* mBody2;
    bool mColliding;
};


static float accumulator = 1.f;
static float timeStep = 1.f / 30.f;

void SetWorldBoundary(reactphysics3d::Vector3 min, reactphysics3d::Vector3 max, float thickness);
void addWall(rp3d::Vector3 Pos, rp3d::Vector3 thickness);
void applyForceToRB(reactphysics3d::RigidBody* rb, glm::vec3 force);
void setVelocityToRB(reactphysics3d::RigidBody* rb, glm::vec3 velocity);
void setupCollisionCallback(rp3d::RigidBody* body1, rp3d::RigidBody* body2);

reactphysics3d::Vector3 GLMToVec3(glm::vec3 vector);
glm::vec3 Vec3ToGLM(rp3d::Vector3 vector);