#pragma once

#include "DataStructures.h"

/**
 * @class Camera
 * @brief A class representing a camera in a GLFW game engine.
 * @author Milad Rakhshbahar
 * @date 11/10/23
 */
class Camera
{
public:
    /**
     * @brief Default constructor for the Camera class.
     */
    Camera();

    /**
     * @brief Copy constructor for the Camera class.
     *
     * @param camera The camera to copy.
     */
    Camera(Camera &camera);

    /**
     * @brief Constructor for the Camera class with specific parameters.
     *
     * @param position The position of the camera.
     * @param forwardVector The forward vector of the camera.
     * @param upVector The up vector of the camera.
     * @param pitch The pitch (x-axis angle) of the camera.
     * @param yaw The yaw (y-axis angle) of the camera.
     */
    Camera(glm::vec3 position, glm::vec3 forwardVector, glm::vec3 upVector, double pitch, double yaw);

    /**
     * @brief Destructor for the Camera class.
     */
    ~Camera();

    // Getters

    /**
     * @brief Get the position of the camera.
     *
     * @return The position of the camera.
     */
    const glm::vec3 GetPosition() const;

    /**
     * @brief Get the forward vector of the camera.
     *
     * @return The forward vector of the camera.
     */
    const glm::vec3 GetForwardVector() const;

    /**
     * @brief Get the up vector of the camera.
     *
     * @return The up vector of the camera.
     */
    const glm::vec3 GetUpVector() const;

    /**
     * @brief Get the pitch (x-axis angle) of the camera.
     *
     * @return The pitch of the camera.
     */
    const double GetPitch() const;

    /**
     * @brief Get the yaw (y-axis angle) of the camera.
     *
     * @return The yaw of the camera.
     */
    const double GetYaw() const;

    // Setters

    /**
     * @brief Set the position of the camera.
     *
     * @param position The new position of the camera.
     */
    void SetPosition(glm::vec3 position);

    /**
     * @brief Set the forward vector of the camera.
     *
     * @param forwardVector The new forward vector of the camera.
     */
    void SetForwardVector(glm::vec3 forwardVector);

    /**
     * @brief Set the pitch (x-axis angle) of the camera.
     *
     * @param pitch The new pitch of the camera.
     */
    void SetPitch(double pitch);

    /**
     * @brief Set the yaw (y-axis angle) of the camera.
     *
     * @param yaw The new yaw of the camera.
     */
    void SetYaw(double yaw);

    /**
     * @brief Set both pitch and yaw angles of the camera.
     *
     * @param pitch The new pitch of the camera.
     * @param yaw The new yaw of the camera.
     */
    void SetAngles(double pitch, double yaw);

    /**
     * @brief Set the up vector of the camera.
     *
     * @param upVector The new up vector of the camera.
     */
    void SetUpVector(glm::vec3 upVector);

    /**
     * @brief Set the camera parameters with new values.
     *
     * @param position The new position of the camera.
     * @param forwardVector The new forward vector of the camera.
     * @param upVector The new up vector of the camera.
     * @param pitch The new pitch (x-axis angle) of the camera.
     * @param yaw The new yaw (y-axis angle) of the camera.
     */
    void Set(glm::vec3 position, glm::vec3 forwardVector, glm::vec3 upVector, double pitch, double yaw);

    // Extra functions

    /**
     * @brief Get the view matrix of the camera.
     *
     * @return The view matrix.
     */
    const glm::mat4 getViewMatrix() const;

    /**
     * @brief Get the projection matrix based on specified parameters.
     *
     * @param screenWidth The width of the screen.
     * @param screenHeight The height of the screen.
     * @param isPerspective A flag indicating whether the projection is perspective or orthographic.
     * @param fov The field of view for perspective projection.
     * @param near The near clipping plane distance.
     * @param far The far clipping plane distance.
     * @param orthoSize The size of the orthographic projection.
     * @return The projection matrix.
     */
    const glm::mat4 getProjectionMatrix(float screenWidth, float screenHeight, bool isPerspective, float fov, float near, float far, float orthoSize) const;

private:
    glm::vec3 m_position; // Position of the camera.
    glm::vec3 m_forwardVect; // Direction the camera is facing.
    glm::vec3 m_upVector; // Direction above the camera.
    double m_pitch; // X-axis angle of the camera.
    double m_yaw; // Y-axis angle of the camera.
};