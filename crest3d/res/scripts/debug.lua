counter = 0
speed = 5
movementVector = vec3.new(0,0,0)
e = Entity.new()

function init()
    -- some stuff
    -- initalise new components
    e.Transform.position = vec3.new(0, 10, 0)
    e:AddComponent(RigidbodyComponent.new())
end

function start()
    -- some stuff
    

end

function earlyUpdate(deltaTime)
    -- some stuff
end

function update(deltaTime)
    movementVector = this.Transform().forward * Input.Controller1LY()
    movementVector = movementVector + this.Transform().right * Input.Controller1LX()
    movementVector = movementVector * speed * deltaTime
    this.Transform().position = this.Transform().position + movementVector
    -- this.Transform():LookAt(e.Transform.position)
    this.Transform():LookAt(vec3.new(0,0,0))

    rbc = e:GetComponent()
    rbc:ApplyForce(vec3.new(0, 5, 0))
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