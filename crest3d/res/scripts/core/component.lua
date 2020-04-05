class = require 'middleclass'

Component = class('Component') -- 'Component' is the class' name

function Component:initialize(name)
    self:name(name)
end

function Component:init()
    return 0
end

function Component:start()
    return 0
end

function Component:earlyUpdate()
    return 0
end

function Component:update()
    return 0
end

function Component:fixedUpdate()
    return 0
end

function Component:render()
    return 0
end

function Component:ui()
    return 0
end

return Component

-- local Lemon = class('Lemon', Component) -- subclassing

-- function Lemon:initialize()
--   Component.initialize(self, 1) -- invoking the superclass' initializer
-- end

-- local lemon = Lemon:new()

-- print(lemon:isSweet()) -- false