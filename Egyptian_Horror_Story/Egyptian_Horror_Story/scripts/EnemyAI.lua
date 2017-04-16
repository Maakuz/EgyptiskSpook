enemySpeed = 0.075
currentWaypoint = 1
nrOfWaypoints = 4
waypoints = { 
				{x = -6, y = 0, z = 6},
				{x = -6, y = 0, z = -47},
				{x = 45, y = 0, z = -47},
				{x = 45, y = 0, z = 6}
			}

onStart = function()
	SetEnemyWaypoint(waypoints[currentWaypoint])
end

onReachingWaypoint = function()
	currentWaypoint = currentWaypoint + 1;
	
	if (currentWaypoint > nrOfWaypoints)
		then currentWaypoint = 1
	end
	
	SetEnemyWaypoint(waypoints[currentWaypoint])
end

update = function()
	if (SeesPlayer())
		then SetEnemySpeed(0.3)
		else SetEnemySpeed(0.01)
	end
end