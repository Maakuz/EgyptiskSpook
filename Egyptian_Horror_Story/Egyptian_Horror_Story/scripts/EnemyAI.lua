walkSpeed = 0.12
runSpeed = 0.10
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
	--Log("Reached Waypoint")
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

function onReachingPathEnd()
	--Log("Reached end")
	
	if SeesPlayer() then
		onChasingPlayer()
	else
		SetOnPath(false)
		SetEnemyWaypoint(waypoints[currentWaypoint])
	end
end

function onChasingPlayer() 
	SetCurrentPathNode(0)
	SetPathToPlayer()
	SetOnPath(true)
end