walkSpeed = 0.12
runSpeed = 0.50
prevWaypoint = 0
currentWaypoint = 1
waypoints = { -- c = connections, length beetwen gets calc in c++
				{x = -6, y = 0, z = 6, c = {2, 4}},
				{x = -6, y = 0, z = -47, c = {1, 7, 5}},
				{x = 45, y = 0, z = -47, c = {7, 4, 6}},
				{x = 45, y = 0, z = 6, c = {1, 3}},
				{x = -6, y = 0, z = -74, c = {2, 6}},
				{x = 45, y = 0, z = -74, c = {5, 3}},
				{x = 17, y = 0, z = -47, c = {2, 3, 8}},
				{x = 17, y = 0, z = -61, c = {7}},
			}

onStart = function()
	SetEnemySpeed(walkSpeed)
	SetEnemyHuntingPlayer(false)
	SetEnemyWaypoint(waypoints[currentWaypoint])
end

onReachingWaypoint = function()
	local toCon = math.random(1, #waypoints[currentWaypoint].c)
	local temp = waypoints[currentWaypoint].c[toCon]
	
	if (#waypoints[currentWaypoint].c > 1 and temp == prevWaypoint)
		then return onReachingWaypoint() end
		
	prevWaypoint = currentWaypoint
	currentWaypoint = temp
	SetEnemyWaypoint(waypoints[currentWaypoint])
end

update = function()
	if not IsEnemyHuntingPlayer() and SeesPlayer()
		then
			SetEnemySpeed(runSpeed)
			SetPlayerAsWaypoint()
			
			SetEnemyHuntingPlayer(true)	
	elseif IsEnemyHuntingPlayer() and not SeesPlayer()
		then
			SetEnemySpeed(walkSpeed)
			SetEnemyWaypoint(waypoints[currentWaypoint])
			
			SetEnemyHuntingPlayer(false)
	elseif IsEnemyHuntingPlayer() then
		onChasingPlayer()
	end
end

function onChasingPlayer() 
	SetPlayerAsWaypoint()
end

function SetPlayerAsWaypoint()
	local playerPos = {x = 0, y = 0, z = 0}
	playerPos["x"], playerPos["y"], playerPos["z"] = GetPlayerPosition()
	
	--SetEnemyWaypoint(playerPos) search for player path not walk towards it :)
end