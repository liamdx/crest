local class = require 'classy'

DebugComponent = class("DebugComponent")

function DebugComponent:initialize()
    
end

function DebugComponent:init()
    Component.init()
end

function DebugComponent:start()
    Component.start()
end

function DebugComponent:earlyUpdate()
    Component.earlyUpdate()
end

function DebugComponent:update()
    Component.update()
end

function DebugComponent:fixedUpdate()
    Component.fixedUpdate()
end

function DebugComponent:render()
    Component.render()
end

function DebugComponent:ui()
    Component.ui()
end

function DebugComponent:doSomething()
    print("Throw the jew down the well")
end

local MyComponent = DebugComponent:new()