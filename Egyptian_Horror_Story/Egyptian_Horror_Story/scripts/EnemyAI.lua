-- @author LW

onPath = false
walkSpeed = 0.04
runSpeed = 0.1
prevWaypoint = 0
currentWaypoint = 1
frame = 0

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

function onStart()
	SetEnemySpeed(walkSpeed)
	SetEnemyWaypoint(waypoints[currentWaypoint])
end

function onReachingWaypoint()
	local toCon = math.random(1, #waypoints[currentWaypoint].c)
	local temp = waypoints[currentWaypoint].c[toCon]
	
	if (#waypoints[currentWaypoint].c > 1 and temp == prevWaypoint)
		then return onReachingWaypoint() end
		
	prevWaypoint = currentWaypoint
	currentWaypoint = temp
	SetEnemyWaypoint(waypoints[currentWaypoint])
end

function update()
	frame = frame + 1
	if not onPath and frame % 100 == 0 and SeesPlayer() then
		SetEnemySpeed(runSpeed)
		pathToPlayer()
	end
	--end
end

function onReachingPathEnd()
	Log("Path End")
	if (SeesPlayer()) then
		pathToPlayer()
	else
		StopPathing()
		SetEnemyWaypoint(waypoints[currentWaypoint])
		onPath = false
				pathToPlayer()
	end
end

function pathToPlayer()
	SetCurrentPathNode(0)
	LoadPathToPlayer()
	StartPathing()
	onPath = true
end