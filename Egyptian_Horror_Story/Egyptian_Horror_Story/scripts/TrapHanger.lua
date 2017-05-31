-- All traps should follow this template
position = {x = 0, y = 0, z = 0}
temp = 0
triggered = true

function onStart()
	position.x, position.y, position.z = GetPosition() -- it is static, so lets just get it
	SetTrapRotOffset(0, -0.5, 0)
end

function getHitboxSize()
	return 0, 0, 0
end

function getLength() -- Sphere intersections
	return 3.5
end

function getSize() 
	return 1.5, 1.5, 1.5 -- width, height, depth
end

function isImpassible()
	return false
end

function update(deltaTime)
	temp = temp + deltaTime
	
	local rot = math.sin(temp) * 1.4
	rotX, rotY, rotZ = GetRotation()
	RotateTrap(rotX, rotY, rot)
end

function onPlayerCollision()
	PushbackPlayer(position.x, position.y, position.z, 1)
	DamagePlayer()
end

function onPlayerTrigger()
end

function onEnemyTrigger()
end

function onEnemyCollision()
	if collision then
	--	PushbackEnemy(position.x, position.y, position.z, 1)
	end
end