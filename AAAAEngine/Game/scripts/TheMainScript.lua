AddScript("SecondLua.lua")

local trans = Transform:new()
local up = Vector3:new()
local physBody = PhysicsBody:new()
local sensitivity = 1.0
local direction = Vector3:new()
local HorizontalAngle = 0  -- Initialize HorizontalAngle
local VerticalAngle = 0    -- Initialize VerticalAngle
local camPos = Vector3:new()
local camRot = Vector3:new()
local camScale = Vector3:new()

local VelocityMagnitude = 30

--Vectors
local pos = Vector3:new()
local rot = Vector3:new()
local scale = Vector3:new()
local Velocity = Vector3:new()

--Transforms
local playerTrans = Transform:new()

--Entities
local camera = ENTITY:new()
local obj = ENTITY:new()
local player = ENTITY:new()

-- Input = InputHandler:new()

UseTerrain(true)

local WireModeBool = false

function K()
    drawMode(WireModeBool)
    WireModeBool = not WireModeBool
end

function empty()
end

function W()
    Velocity = normalize(GetTransform(player):Get(2))
    Velocity.x = Velocity.x * VelocityMagnitude
    Velocity.y = GetGravity().y * GetPhysicsBody(player):Get():GetMass()
    Velocity.z = Velocity.z * VelocityMagnitude
    SetVelocity(GetPhysicsBody(player), Velocity)
end

function A()
    local forwardVector = GetTransform(player):Get(2)
    local upVector = GetTransform(player):Get(3)

    local rightVector = crossProduct(upVector, forwardVector)

    local normal = normalize(rightVector)
    Velocity.x = normal.x * VelocityMagnitude
    Velocity.y = GetGravity().y * GetPhysicsBody(player):Get():GetMass()
    Velocity.z = normal.z * VelocityMagnitude
    SetVelocity(GetPhysicsBody(player), Velocity)
end

function S()
    Velocity = normalize(GetTransform(player):Get(2))
    Velocity.x = -Velocity.x * VelocityMagnitude
    Velocity.y = GetGravity().y * GetPhysicsBody(player):Get():GetMass()
    Velocity.z = -Velocity.z * VelocityMagnitude
    SetVelocity(GetPhysicsBody(player), Velocity)
end

function D()
    local forwardVector = GetTransform(player):Get(2)
    local upVector = GetTransform(player):Get(3)

    local rightVector = crossProduct(upVector, forwardVector)
    local normal = normalize(rightVector)
    Velocity.x = normal.x * -VelocityMagnitude
    Velocity.y = GetGravity().y * GetPhysicsBody(player):Get():GetMass()
    Velocity.z = normal.z * -VelocityMagnitude
    SetVelocity(GetPhysicsBody(player), Velocity)
end

function stopMove()
    Velocity.x = 0
    Velocity.y = 0
    Velocity.z = 0
    SetVelocity(GetPhysicsBody(player), Velocity)
end


function jump()
    Velocity.x = 0
    Velocity.y = 1
    Velocity.z = 0
    Velocity.x = Velocity.x * VelocityMagnitude
    Velocity.y = Velocity.y * VelocityMagnitude
    Velocity.z = Velocity.z * VelocityMagnitude
    AddForce(GetPhysicsBody(player), Velocity)
end

function look(x, y)
    local sensitivityX = 0.01
    local sensitivityY = 0.01

    HorizontalAngle = HorizontalAngle - x * sensitivityX
    VerticalAngle = VerticalAngle + y * sensitivityY

    -- Clamp vertical angle within a certain range
    VerticalAngle = math.max(-1.5, math.min(1.5, VerticalAngle))

    -- Calculate direction vector
    local direction = Vector3:new()
    direction.x = math.cos(VerticalAngle) * math.sin(HorizontalAngle)
    direction.y = math.sin(VerticalAngle)
    direction.z = math.cos(VerticalAngle) * math.cos(HorizontalAngle)
    

    -- Calculate right vector
    local right_vector = Vector3:new()
    
        right_vector.x = math.sin(HorizontalAngle - math.pi / 2.0)
        right_vector.y = 0
        right_vector.z = math.cos(HorizontalAngle - math.pi / 2.0)

    -- Calculate up vector using cross product
    local up_vector = crossProduct(right_vector, direction)

    -- Update camera rotation and transform
    rot.x = direction.x
    rot.y = direction.y
    rot.z = direction.z
    scale.x = up_vector.x
    scale.y = up_vector.y
    scale.z = up_vector.z
    SetEntityTransformRotation(player, rot)
    SetEntityTransformScale(player, scale)
end

function CreatePlayer()
    --Set Transforms
    pos.x = 500
    pos.y = 200
    pos.z = 500
    rot.x = 0
    rot.y = 0
    rot.z = 0
    scale.x = 1
    scale.y = 1
    scale.z = 1
    playerTrans:Set(1, pos)
    playerTrans:Set(2, rot)
    playerTrans:Set(3, scale)

    --Create Entities
    player = CreateEntity(playerTrans, true)

    --Add Components
    local playerPhysics = Physics:new()
    playerPhysics:AddRigidbody(GetTransform(player):Get(1), 1, BodyType.DYNAMIC, true)
    playerPhysics:AddCapsuleCollider(rot--[[position in relation to rigidbody]], 5, 15)
    playerPhysics:SetFriction(10)
    playerPhysics:SetBounciness(0)

    AddPhysicsBody(player)
    setEntityPhysicsBody(player, playerPhysics)

    AddCamera(player, pos, rot, up, 0.0, 0.0)   --Adds the Camera
end

function CreateSuperDome()
    --Create Entities
    pos.x = 600
    pos.y = 142
    scale.x = 3
    scale.y = 3
    scale.z = 3
    playerTrans:Set(1, pos)
    playerTrans:Set(3, scale)
    superdome = CreateEntity(playerTrans, true)

    --Add Components
    LoadMesh("resources/models/superdome.obj")
    AddMesh(superdome, GetMesh())

    scale.x = 50
    scale.y = 25
    scale.z = 50
    local superdomePhys = Physics:new()
    superdomePhys:AddRigidbody(GetTransform(superdome):Get(1), 1, BodyType.STATIC, true)
    superdomePhys:AddBoxCollider(rot--[[position in relation to rigidbody]], scale)

    AddPhysicsBody(superdome)
    setEntityPhysicsBody(superdome, superdomePhys)
end

function CreateOtherOBJS()
    pos.x = 450
    pos.y = 145
    for i = 1, 15 do
        --Create Entities
        pos.x = pos.x - 10
        pos.z = pos.z - 10
        scale.x = 10
        scale.y = 10
        scale.z = 10
        playerTrans:Set(1, pos)
        playerTrans:Set(3, scale)
        tinkywinky = CreateEntity(playerTrans, true)

        --Add Components
        LoadMesh("resources/models/teletubbie_tinkywinky.obj")
        AddMesh(tinkywinky, GetMesh())

        --[[scale.x = 50
        scale.y = 25
        scale.z = 50
        local superdomePhys = Physics:new()
        superdomePhys:AddRigidbody(GetTransform(superdome):Get(1), 1, BodyType.STATIC, true)
        superdomePhys:AddBoxCollider(rot--[[position in relation to rigidbody, scale)

        AddPhysicsBody(superdome)
        setEntityPhysicsBody(superdome, superdomePhys)]]
    end
end

-- Executes when you hit play
function Start()
    CreatePlayer()
    CreateOtherOBJS()
    CreateSuperDome()

        --[[pos.x = 600
        pos.y = 142
        pos.z = 600
        scale.x = 10
        scale.y = 10
        scale.z = 10
        playerTrans:Set(1, pos)
        playerTrans:Set(3, scale)
        tinkywinky = CreateEntity(playerTrans, true)

        --Add Components
        LoadMesh("resources/models/teletubbie_tinkywinky.obj")
        AddMesh(tinkywinky, GetMesh())]]

    --BindKey(GUKey.KEY_W, W)
    BindKey(87, W, stopMove, empty)
    BindKey(65, A, stopMove, empty)
    BindKey(83, S, stopMove, empty)
    BindKey(68, D, stopMove, empty)
    BindKey(75, K, empty, empty)
    --BindKey(32, Space, empty, empty)
    MousePosFunc(look)
    -- BindMouse(GUMouse.MOUSE_BUTTON_LEFT, LeftClick)
end

-- Executes every frame
function Update()
    local camTrans = GetTransform(player)

    GetCamera(player):Set(camTrans:Get(1), camTrans:Get(2), camTrans:Get(3), 0, 0)
end




------------------------------------------------------------------------
--[[LoadMesh("resources/models/4Story_Mat.obj")

    --obj = CreateEntity(trans, true)
    --print("b")
    --AddMesh(obj, GetMesh())

    --local body = Physics:new() 

    --body:AddRigidbody(pos, 100, 2, true)

    --AddPhysicsBody(obj)
    --setEntityPhysicsBody(obj, body)]]--