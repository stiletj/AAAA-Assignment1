#include "Physics.h"

Physics::Physics() {
    m_rigidBody = nullptr;
    m_allocator = nullptr;
}

void Physics::addRigidBody(glm::vec3 pos, float mass, bodytype type, bool gravity)
{
    reactphysics3d::Quaternion orientation = reactphysics3d::Quaternion::identity();
    reactphysics3d::Vector3 rp3dPos(ConvertVector3(pos));
    reactphysics3d::Transform trans(rp3dPos, orientation);
    m_rigidBody = WorldPhysics::m_worldPhysics->createRigidBody(trans);
    m_rigidBody->setType(ConvertBodyType(type));
    m_rigidBody->setMass(mass);
    m_rigidBody->enableGravity(gravity);
}

reactphysics3d::RigidBody* Physics::GetRigidBody()
{
    return m_rigidBody;
}

void Physics::SetRigidBody(reactphysics3d::RigidBody& rigidBody)
{
    m_rigidBody = &rigidBody;
}

Physics::~Physics()
{
    
}

void Physics::addBox(glm::vec3 pos, glm::vec3 size)
{
    reactphysics3d::Vector3 position = ConvertVector3(pos);
    reactphysics3d::Quaternion orientation = reactphysics3d::Quaternion::identity();
    reactphysics3d::BoxShape* box = WorldPhysics::m_physicsCommon.createBoxShape(ConvertVector3(size));
    reactphysics3d::Transform transform(position, orientation);
    m_rigidBody->addCollider(box, transform);
}

void Physics::addSphere(glm::vec3 pos, float radius)
{
    reactphysics3d::Vector3 position = ConvertVector3(pos);
    reactphysics3d::Quaternion orientation = reactphysics3d::Quaternion::identity();
    reactphysics3d::SphereShape* sphere = WorldPhysics::m_physicsCommon.createSphereShape(radius);
    reactphysics3d::Transform transform(position, orientation);
    m_rigidBody->addCollider(sphere, transform);
}

void Physics::addCapsule(glm::vec3 pos, float radius, float height)
{
    reactphysics3d::Vector3 position = ConvertVector3(pos);
    reactphysics3d::Quaternion orientation = reactphysics3d::Quaternion::identity();
    reactphysics3d::CapsuleShape* capsule = WorldPhysics::m_physicsCommon.createCapsuleShape(radius, height);
    reactphysics3d::Transform transform(position, orientation);
    m_rigidBody->addCollider(capsule, transform);

}

void Physics::addConvexMesh(glm::vec3 pos, reactphysics3d::Vector3 scale, float* vertices, rp3d::uint32 numVertices, reactphysics3d::PolygonVertexArray::PolygonFace* faces, rp3d::uint32 numFaces, rp3d::uint32* indices)
{
    reactphysics3d::Vector3 position = ConvertVector3(pos);
    reactphysics3d::Quaternion orientation = reactphysics3d::Quaternion::identity();
    reactphysics3d::PolygonVertexArray vertexArray(numVertices, vertices, sizeof(float) * 3, indices, sizeof(rp3d::uint32), numFaces, faces, rp3d::PolygonVertexArray::VertexDataType::VERTEX_FLOAT_TYPE, rp3d::PolygonVertexArray::IndexDataType::INDEX_INTEGER_TYPE);
    reactphysics3d::PolyhedronMesh* polyhedronMesh = WorldPhysics::m_physicsCommon.createPolyhedronMesh(&vertexArray);
    reactphysics3d::ConvexMeshShape* convexMesh = WorldPhysics::m_physicsCommon.createConvexMeshShape(polyhedronMesh, scale);
    reactphysics3d::Transform transform(position, orientation);
    m_rigidBody->addCollider(convexMesh, transform);
}

/*
void Physics::addConcaveMesh(glm::vec3 pos, reactphysics3d::Vector3 scale, float* vertices, rp3d::uint32 numVertices, int numTriangles, rp3d::uint32* indices)
{
    // Create a concave mesh and a corresponding rigid body
    reactphysics3d::Vector3 position = ConvertVector3(pos);
    reactphysics3d::Quaternion orientation = reactphysics3d::Quaternion::identity();
    reactphysics3d::TriangleVertexArray* triangleArray = new rp3d::TriangleVertexArray(numVertices, vertices, 3 * sizeof(float), numTriangles, indices, 3 * sizeof(int), reactphysics3d::TriangleVertexArray::VertexDataType::VERTEX_FLOAT_TYPE, reactphysics3d::TriangleVertexArray::IndexDataType::INDEX_INTEGER_TYPE);

    // Create the TriangleMesh
    std::vector<rp3d::Message> messages;
    reactphysics3d::TriangleMesh* triangleMesh;

    //NOTE THIS MAY BE INCORRECT AS IT MIGHT ONLY CREATE ONE TRIANGLE MESH
    triangleMesh->addSubpart(triangleArray);

    // Display the messages (info, warning and errors)
    if (messages.size() > 0) {

        for (const rp3d::Message& message : messages) {

            std::string messageType;
            switch (message.type) {
            case rp3d::Message::Type::Information:
                messageType = "info";
                break;
            case rp3d::Message::Type::Warning:
                messageType = "warning";
                break;
            case rp3d::Message::Type::Error:
                messageType = "error";
                break;
            }

            std::cout << "Message (" << messageType << "): " << message.text << std::endl;
        }
    }

    // Make sure there was no errors during mesh creation
    assert(triangleMesh != nullptr);

    const rp3d::Vector3 scaling(1, 1, 1);

    // Create the ConcaveMeshShape using the TriangleMesh
    reactphysics3d::ConcaveMeshShape* concaveMesh = physicsCommon.createConcaveMeshShape(triangleMesh, scaling);

    reactphysics3d::Transform transform(position, orientation);
    m_rigidBody->addCollider(concaveMesh, transform);
}*/

void Physics::addHeightField(glm::vec3 pos, int numColumns, int numRows, reactphysics3d::decimal minHeight, reactphysics3d::decimal maxHeight, float* pointArray2d, int upAxis, glm::vec3 scale)
{
    reactphysics3d::Vector3 reactScale = ConvertVector3(scale);
    reactphysics3d::Vector3 position = ConvertVector3(pos);
    reactphysics3d::Quaternion orientation = reactphysics3d::Quaternion::identity();
    reactphysics3d::HeightFieldShape* heightField = WorldPhysics::m_physicsCommon.createHeightFieldShape(numColumns, numRows, minHeight, maxHeight, pointArray2d, reactphysics3d::HeightFieldShape::HeightDataType::HEIGHT_FLOAT_TYPE, upAxis, 1, reactScale);
    reactphysics3d::Transform transform(position, orientation);
    m_rigidBody->addCollider(heightField, transform);
}

void Physics::SetFrictionCoefficient(float friction)
{
    m_rigidBody->getCollider(0)->getMaterial().setFrictionCoefficient(10.0);

}

void Physics::SetBounciness(float bounce)
{
    m_rigidBody->getCollider(0)->getMaterial().setBounciness(0.0);
}

float Physics::GetMass()
{
    return m_rigidBody->getMass();
}

reactphysics3d::Vector3 Physics::ConvertVector3(glm::vec3 vect)
{
    return reactphysics3d::Vector3(vect.x, vect.y, vect.z);
}

reactphysics3d::BodyType Physics::ConvertBodyType(bodytype type)
{
    return reactphysics3d::BodyType(type);
}
