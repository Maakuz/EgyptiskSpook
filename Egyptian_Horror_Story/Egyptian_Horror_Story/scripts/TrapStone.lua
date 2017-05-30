-- All traps should follow this template
position = {x = 0, y = 0, z = 0}

fallenDown = false
falling = false
fallY = 12
timeToFall = 0.5
temp = 0

function onStart()
	position.x, position.y, position.z = GetPosition() -- it is static, so lets just get it
end

-- Height is high because rock is in the air
function getHitboxSize()
	return 5, 50, 5
end

function getSize() 
	return 2.5, 2.5, 2.5 -- width, height, depth
end

function isImpassible()
	return fallenDown
end

function update(deltaTime)
	if falling then
		temp = temp + deltaTime / timeToFall
		SetPosition(position.x, position.y - (fallY * temp), position.z);
		
		if temp >= 1 then
			fallDown()
		end
	end
end

function onPlayerCollision()
	if falling and temp >= 0.7 and temp <= 1.0 then
		DamagePlayer()
		PushbackPlayer(position.x, position.y, position.z, 1)
	elseif not fallenDown then
		falling = true
	end
end

function onEnemyCollision()
	if fallenDown then
		PushbackEnemy(position.x, position.y, position.z, 2)
	else
		falling = true
	end
end

function fallDown()
	if not fallenDown then
		fallenDown = true
		falling = false
		SetPosition(position.x, position.y - fallY, position.z);
	end
end