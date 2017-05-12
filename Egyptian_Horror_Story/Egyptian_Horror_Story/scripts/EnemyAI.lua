-- @author LW

-- Pathing
onPlayerPath = false
onPointPath = false
sawPlayerLastFrame = false

-- Speeds
walkSpeed = 0.04
runSpeed = 0.10

-- Waypoint System
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
			
-- Frame Counter
frame = 0

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
	if frame % 10 == 0 then
		seesPlayer = SeesPlayer()
		if not onPlayerPath or not sawPlayerLastFrame and seesPlayer then
			pathToPlayer()
			sawPlayerLastFrame = true
		elseif sawPlayerLastFrame and not seesPlayer then
			pathToPlayer()
			sawPlayerLastFrame = false
		end
	end
	
	if frame % 100 then
		if seesPlayer() then
			pathToPlayer()
			sawPlayerLastFrame = true
		end
	end
end

function onReachingPathEnd()
	SetEnemySpeed(walkSpeed)
	if SeesPlayer() then
		pathToPlayer()
	elseif onPointPath then
		onReachingPointPathEnd()
	else
		StopPathing()
		pathToWaypoint()
	end
end

function onReachingPointPathEnd()
	StopPathing()
	SetEnemyWaypoint(waypoints[currentWaypoint])
		
	onPointPath = false
end

function pathToPlayer()
	SetEnemySpeed(runSpeed)
	SetCurrentPathNode(0)
	LoadPathToPlayer()
	StartPathing()
	
	onPlayerPath = true
	onPointPath = false
end

function pathToWaypoint()
	SetCurrentPathNode(0)
	LoadPathToPoint(waypoints[currentWaypoint].x, waypoints[currentWaypoint].z)
	StartPathing()
	
	onPointPath = true
	onPlayerPath = false
end