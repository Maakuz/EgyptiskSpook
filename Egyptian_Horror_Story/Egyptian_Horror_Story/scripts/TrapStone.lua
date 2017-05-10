-- All traps should follow this template
position = {x = 0, y = 0, z = 0}
first = true

function onStart()
	position.x, position.y, position.z = GetPosition(); -- it is static, so lets just get it
	Log(string.format("Position: %f,%f,%f Size: %f,%f,%f",
		position.x, position.y, position.z, getSize()))
end

function getSize() 
	return 5, 3, 5 -- width, height, depth
end

function update()
end

function onPlayerCollision()
	Log("Test" .. position.x)
	if (first) then
		PushbackPlayer(position.x, position.y, position.z, 1)
		first = false
	end
end

function onEnemyCollision()
	PushbackEnemy(position.x, position.y, position.z, 1)
end