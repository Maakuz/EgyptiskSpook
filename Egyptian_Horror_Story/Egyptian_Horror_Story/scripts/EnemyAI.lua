walkSpeed = 0.001
runSpeed = 0.05
currentWaypoint = 1
nrOfWaypoints = 4
waypoints = { 
				{x = -6, y = 0, z = 6},
				{x = -6, y = 0, z = -47},
				{x = 45, y = 0, z = -47},
				{x = 45, y = 0, z = 6}
			}

onStart = function()
	SetEnemySpeed(walkSpeed)
	SetEnemyHuntingPlayer(false)
	SetEnemyWaypoint(waypoints[currentWaypoint])
end

onReachingWaypoint = function()
	currentWaypoint = currentWaypoint + 1;
	
	if (currentWaypoint > nrOfWaypoints)
		then currentWaypoint = 1
	end
	
	if IsEnemyHuntingPlayer() and SeesPlayer()
		then SetPlayerAsWaypoint()
	else
		SetEnemyWaypoint(waypoints[currentWaypoint])
	end
end

update = function()
	Log(string.format("Hunting Player! %s", IsEnemyHuntingPlayer()))
	if not IsEnemyHuntingPlayer() and SeesPlayer()
		then
			SetEnemySpeed(runSpeed)
			SetPlayerAsWaypoint()
			
			SetEnemyHuntingPlayer(true)	
	elseif IsEnemyHuntingPlayer() and not SeesPlayer()
		then
			Log("Player Lost!");
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
	
	SetEnemyWaypoint(playerPos)
end