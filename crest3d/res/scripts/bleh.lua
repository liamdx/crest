x = 0.0
counter = 0

function init()
    -- some stuff
end

function start()
    -- some stuff
    e = Entity.new()
    e.Transform.position = vec3.new(0, 10 ,0)


end

function earlyUpdate(deltaTime)
    -- some stuff
end

function update(deltaTime)
    x = x + deltaTime
    if x > 1 then
        counter = counter + 1
        Debug.Warn("Lua Component", counter )
        x = 0
    end

    if InputManager.GetKeyA() then
        Debug.Warn("Pressed A", counter )
        print("Pressed A")
    end
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