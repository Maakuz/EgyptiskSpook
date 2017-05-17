-- All traps should follow this template
position = {x = 0, y = 0, z = 0}
fallenDown = false
fallY = 12

function onStart()
	position.x, position.y, position.z = GetPosition(); -- it is static, so lets just get it
end

-- Height is high because rock is in the air
function getSize() 
	return 5, 50, 5 -- width, height, depth
end

function isImpassible()
	return fallenDown
end

function update()
	
end

function onPlayerCollision()
	PushbackPlayer(position.x, position.y, position.z, 1)
	DamagePlayer()
	
	fallDown()
end

function onEnemyCollision()
	PushbackEnemy(position.x, position.y, position.z, 1)
	
	fallDown()
end

function fallDown()
	if not fallenDown then
		fallenDown = true
		SetPosition(position.x, position.y - fallY, position.z);
	end
end