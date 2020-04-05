require "core.component"
require "DebugComponent"
local AnotherComponent = class("AnotherComponent", Component)

function AnotherComponent:initialize()
    Component.initialize("AnotherComponent")
    self.e = Entity.new()
    self.dc = e:AddComponent(DebugComponent:new())
end

function AnotherComponent:init()
    Component.init()
end

function AnotherComponent:start()
    Component.start()
end

function AnotherComponent:earlyUpdate()
    Component.earlyUpdate()
    self.dc:doSomething()
end

function AnotherComponent:update()
    Component.update()
end

function AnotherComponent:fixedUpdate()
    Component.fixedUpdate()
end

function AnotherComponent:render()
    Component.render()
end

function AnotherComponent:ui()
    Component.ui()
end

function AnotherComponent:doSomething()
    print("Throw the jew down the well")
end

local myComponent = AnotherComponent:new()