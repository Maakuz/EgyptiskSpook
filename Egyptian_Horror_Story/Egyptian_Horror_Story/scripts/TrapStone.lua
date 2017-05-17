-- All traps should follow this template
position = {x = 0, y = 0, z = 0}
collision = true
temp = 0

function onStart()
	position.x, position.y, position.z = GetPosition(); -- it is static, so lets just get it
	Log(string.format("Position: %f,%f,%f Size: %f,%f,%f",
		position.x, position.y, position.z, getSize()))
	SetTrapRotOffset(0, -4, 0)
end

function getSize() 
	return 5, 3, 5 -- width, height, depth
end

function isImpassible()
	return collision
end

function update()
	temp = temp + 0.008
	
	local rot = math.sin(temp) * 1.4
	
	SetPosition(position.x, position.y, position.z)
	RotateTrap(rot, 0, 0)
	
	collision = math.abs(rot) < 0.3
end

function onPlayerCollision()
	if collision then
		PushbackPlayer(position.x, position.y, position.z, 3)
		first = false
	end
end

function onEnemyCollision()
	if collision then
		PushbackEnemy(position.x, position.y, position.z, 3)
	end
end