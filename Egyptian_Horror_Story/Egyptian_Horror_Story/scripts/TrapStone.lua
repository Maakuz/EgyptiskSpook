-- All traps should follow this template
position = {x = 0, y = 0, z = 0}
first = true
temp = 0
dir = 0

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
	return not first
end

function update()
	if dir == 0 then
		temp = temp + 0.01;
		if temp > 1.8 then dir = 1 end
	else
		temp = temp - 0.01;
		if temp < -1.8 then dir = 0 end
	end
	SetPosition(position.x, position.y, position.z)
	RotateTrap(temp, 0, 0)
end

function onPlayerCollision()
	--if (first) then
		PushbackPlayer(position.x, position.y, position.z, 1)
		first = false
	--end
end

function onEnemyCollision()
	PushbackEnemy(position.x, position.y, position.z, 1)
end