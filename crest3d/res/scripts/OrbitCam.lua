target = vec3.new(0,0,0)
distance = 30.0
xSpeed = 0.02
ySpeed = 3.0

yMinLimit = -30.0
yMaxLimit = 180.0

distanceMin = 20
distanceMax = 40.0

x = 0
y = 0

function clamp(number, min, max)
    if number <= min then
        number = min
    elseif number >= max then
        number = max
    end
    return number
end

function clampAngle(angle, min, max)
    if(angle <= -180.0) then
        angle = angle + 360.0
    elseif (angle >= 180.0) then
        angle = angle - 360.0
    end

    return clamp(angle, min, max)
end

function init()
    -- some stuff
end

function start()
    -- some stuff
end

function earlyUpdate(deltaTime)
    -- some stuff
end

function update(deltaTime)
    -- x = x + Input.Controller1RX() * xSpeed * distance * 360.0 * deltaTime
    -- y = y - Input.Controller1RY() * ySpeed * 0.02

    -- rotation = CrestMaths.EulerToQuat(vec3.new(y,x,0))
    -- distance = clamp(distance, distanceMin, distanceMax)
    -- distance_vec = target - this.Transform().position
    -- -- distance = distance - CrestMaths.Magnitude(distance_vec)

    -- negative_distance = vec3.new(0, 0, -distance)
    -- position = rotation * negative_distance + target
    -- this.Transform().position = position
    this.Transform():LookAt(vec3.new(0,0,0))

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