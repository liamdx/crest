counter = 0
speed = 5
movementVector = vec3.new(0,0,0)
e = Entity.new()

local rbc

function init()
    -- some stuff
    -- initalise new components
    e.Transform.position = vec3.new(0, 10, 0)
    e:AddComponent(RigidbodyComponent.new())
    this.Entity():AddComponent(RigidbodyComponent.new())
end

function start()
    -- some stuff
    rbc = this.Entity():GetComponent("RigidbodyComponent")

end

function earlyUpdate(deltaTime)
    -- some stuff
end

function update(deltaTime)

    rbcd = e:GetComponent()
    rbcd:ApplyForce(vec3.new(0, 0, 0))

    if Input.Controller1A() == true then
        rbc:ApplyForce(vec3.new(0, 10, 0))
    end
        -- rbc.ApplyForce(vec3.new(0, 5, 0))
    -- e.Transform.position = e.Transform.position + vec3.new(0, deltaTime, 0)
    -- local movement = vec3.new(0, 0, 0)
    -- this.Transform.position = this.Transform.position + movement * 5 * deltaTime
end               


function fixedUpdate(deltaTime)
    -- some stuff
end

function render(deltaTime)
    -- some stuff
end

function ui(deltaTime)
    -- some stuff
end