#pragma once

#include "entt/entt.hpp"
#include "Components.h"

/**
 * @struct ENTITY
 * @brief Structure representing an entity.
 */
struct ENTITY
{
	entt::entity m_entity; /**< Entity handle. */
	unsigned int entID; /**< ID of the entity. */

	/**
	 * @brief Default constructor for ENTITY.
	 */
	ENTITY();

	/**
	 * @brief Constructs an ENTITY object with the specified entity.
	 * @param entity Entity handle.
	 */
	ENTITY(entt::entity entity);

	/**
	 * @brief Retrieves the ID of the entity.
	 * @return ID of the entity.
	 */
	unsigned int Get();

	/**
	 * @brief Sets the entity handle.
	 * @param _entity New entity handle.
	 */
	void Set(entt::entity _entity);
};

inline ENTITY::ENTITY()
{
	entID = -1;
}

inline ENTITY::ENTITY(entt::entity entity)
{
	m_entity = entity;

	entID = (unsigned int)m_entity;
}

inline unsigned int ENTITY::Get()
{
	return entID;
}

inline void ENTITY::Set(entt::entity _entity)
{
	m_entity = _entity;
	entID = (unsigned int)m_entity;
}

/**
 * @class ECS
 * @brief Class representing the ECS (Entity-Component-System) system.
 */
class ECS
{
private:
    entt::registry m_reg; /**< Entity registry. */

public:
    /**
     * @brief Default constructor for ECS.
     */
    ECS();

    /**
     * @brief Destructor for ECS.
     */
    ~ECS();

    /**
     * @brief Retrieves the entire registry.
     * @return View of the entire registry.
     */
    auto GetRegistry();

    /**
     * @brief Adds an entity to the registry with the specified transformation and rendering status.
     * @param trans Transformation of the entity.
     * @param render Rendering status of the entity.
     * @return ENTITY object representing the added entity.
     */
    ENTITY AddEntity(Transform trans, bool render);

    /**
     * @brief Adds a component to an entity.
     * @tparam Component Type of the component to add.
     * @tparam Args Types of arguments for the component constructor.
     * @param entity ENTITY object representing the entity.
     * @param args Arguments for the component constructor.
     */
    template<typename Component, typename... Args>
    void AddComponent(ENTITY entity, Args&... args);

    /**
     * @brief Deletes an entity from the registry.
     * @param entity ENTITY object representing the entity to delete.
     */
    void DeleteEntity(ENTITY entity);

    /**
     * @brief Deletes a component from an entity.
     * @tparam Component Type of the component to delete.
     * @param entity ENTITY object representing the entity.
     */
    template<typename Component>
    void DeleteComponent(ENTITY entity);

    /**
     * @brief Retrieves a component from an entity.
     * @tparam Component Type of the component to retrieve.
     * @param entity ENTITY object representing the entity.
     * @return Reference to the retrieved component.
     */
    template<typename Component>
    Component& GetComponent(ENTITY entity);

    /**
     * @brief Checks if an entity has a specific component.
     * @tparam Component Type of the component to check for.
     * @param entity ENTITY object representing the entity.
     * @return True if the entity has the component, otherwise false.
     */
    template<typename Component>
    bool HasComponent(ENTITY entity);

    /**
     * @brief Gets the size of the registry.
     * @return Size of the registry.
     */
    int Size();

    /**
     * @brief Retrieves a view containing all entities with specified components.
     * @tparam Components Types of components to check for.
     * @return View of entities with specified components.
     */
    template<typename... Components>
    auto Contains();

    /**
     * @brief Retrieves all entities with true rendering status.
     * @return Vector of entities with true rendering status.
     */
    std::vector<entt::entity> GetRenders();
};

inline ECS::ECS()
{

}

inline ECS::~ECS()
{

}

inline auto ECS::GetRegistry()
{
	auto view = m_reg.view<Transform>();

	/*for (entt::entity entity : view)
	{
		std::cout << (unsigned int)entity << ": " << m_reg.get<Position>(entity).x << ", " << m_reg.get<Position>(entity).y << ", " << m_reg.get<Position>(entity).z << std::endl;
	}*/

	return view;

	//return m_reg.view<ToRender>();
}

//template<typename T>
inline ENTITY ECS::AddEntity(Transform trans, bool render)
{
	entt::entity entity = m_reg.create();

	ENTITY entStruct(entity);

	AddComponent<Transform, glm::vec3&>(entStruct, trans.m_pos, trans.m_rot, trans.m_scale);

	AddComponent<ToRender, bool>(entStruct, render);

	return entStruct;
}

template<typename Component, typename... Args>
void ECS::AddComponent(ENTITY entity, Args&... args)
{
	m_reg.emplace<Component>(entity.m_entity, std::forward<Args>(args)...);
}

inline void ECS::DeleteEntity(ENTITY entity)
{
	m_reg.destroy(entity.m_entity);
}

template<typename Component>
void ECS::DeleteComponent(ENTITY entity)
{
	m_reg.remove<Component>(entity.m_entity);
}

template<typename Component>
Component& ECS::GetComponent(ENTITY entity)
{
	return m_reg.get<Component>(entity.m_entity);
}

template<typename Component>
bool ECS::HasComponent(ENTITY entity)
{
	for (entt::entity ent : m_reg.view<Component>())
	{
		if (ent == entity.m_entity)
		{
			return true;
		}
	}

	return false;
}

/*
int ECS::Size()
{
	int size = 0;

	m_reg.each([&size](auto entity)
		{
			if (m_reg.alive(entity))
			{
				size++;
			}
		});

	return size;
}*/

template<typename... Components>
auto ECS::Contains()
{
	return m_reg.view<Components...>();
}

//template<typename T>
inline std::vector<entt::entity> ECS::GetRenders()
{
	std::vector<entt::entity> renders;

	for (entt::entity entity : m_reg.view<ToRender>())
	{
		if (m_reg.get<ToRender>(entity).toRender)
		{
			renders.push_back(entity);
		}
	}

	return renders;
}