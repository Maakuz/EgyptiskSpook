-- All traps should follow this template
position = {x = 0, y = 0, z = 0}
collision = true
temp = 0

function onStart()
	position.x, position.y, position.z = GetPosition() -- it is static, so lets just get it
	SetTrapRotOffset(0, -0.5, 0)
end

function getHitboxSize()
	return 3, 25, 3
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
	RotateTrap(0, 0, rot)
	
	collision = math.abs(rot) < 0.35
end

function onPlayerCollision()
	if collision then
		PushbackPlayer(position.x, position.y, position.z, 1)
		DamagePlayer()
	end
end

function onEnemyCollision()
	if collision then
	--	PushbackEnemy(position.x, position.y, position.z, 1)
	end
end