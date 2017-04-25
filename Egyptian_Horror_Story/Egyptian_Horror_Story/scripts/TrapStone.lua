-- All traps should follow this template
position = {x = 0, y = 0, z = 0}

function onStart()
	position.x, position.y, position.z = GetPosition(); -- it is static, so lets just get it
	Log(string.format("Position: %f,%f,%f Size: %f,%f,%f",
		position.x, position.y, position.z, getSize()))
end

function getSize() 
	return 1, 3, 1 -- width, height, depth
end

function update()
end

function onPlayerCollision()
	Log("Player Collision!")
end

function onEnemyCollision()
	Log("Enemy Collision!")
end