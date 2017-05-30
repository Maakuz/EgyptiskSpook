-- @author LW

-- Pathing
onPlayerPath = false
onPointPath = false
sawPlayerLastFrame = false

-- Speeds movement per second
walkSpeed = 10
runSpeed = 14

-- Waypoint System
prevWaypoint = 0
currentWaypoint = 1

waypoints = { -- c = connections, length beetwen gets calc in c++
				{x = -6, z = 6, c = {2, 4}},
				{x = -6, z = -47, c = {1, 7, 5}},
				{x = 45, z = -47, c = {7, 4, 6}},
				{x = 45, z = 6, c = {1, 3}},
				{x = -6, z = -74, c = {2, 6}},
				{x = 45, z = -74, c = {5, 3}},
				{x = 17, z = -47, c = {2, 3, 8}},
				{x = 17, z = -61, c = {7}},
			}
			
-- Frame Counter
frame = 0
loadingPath = false
onWaypoint = true
sleep = 0

function onStart()
	SetEnemySpeed(walkSpeed)
	SetEnemyWaypoint(waypoints[currentWaypoint])
	onWaypoint = true
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

function update(deltaTime)
	if sleep > 0 then
		sleep = sleep - deltaTime
	else
		frame = frame + 1
		if frame % 25 == 0 and not loadingPath then
			seesPlayer = SeesPlayer()
			if not onPlayerPath and seesPlayer then
				pathToPlayer()
				sawPlayerLastFrame = true
			elseif sawPlayerLastFrame and not seesPlayer then -- goes to player if saw player last "frame"
				pathToPlayer()
				sawPlayerLastFrame = false
			end
		end
	end
end

function onLoadedPath()
	loadingPath = false
	if not onWaypoint then
		SetCurrentPathNode(0)
		SetEnemySpeed(runSpeed)
		StartPathing()
	end
end

function onReachingPathEnd()
	SetEnemySpeed(walkSpeed)
	
	if SeesPlayer() then
		if not loadingPath then 
			pathToPlayer()
		end
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
	
	onWaypoint = true
	onPointPath = false
end

function pathToPlayer()
	sleep = 0.25
	LoadPathToPlayer()
	
	onPlayerPath = true
	loadingPath = true
	onWaypoint = false
	
	onPointPath = false
end

function pathToWaypoint()
	SetCurrentPathNode(0)
	LoadPathToPoint(waypoints[currentWaypoint].x, waypoints[currentWaypoint].z)
	
	onPointPath = true
	onPlayerPath = false
end