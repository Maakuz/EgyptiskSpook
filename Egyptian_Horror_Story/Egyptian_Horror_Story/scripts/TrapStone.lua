-- All traps should follow this template
position = {x = 0, y = 0, z = 0}

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
	x, y, z = GetPlayerPosition();
	SetPlayerPosition(x, y + 0.1, z)
end

function onEnemyCollision()

end