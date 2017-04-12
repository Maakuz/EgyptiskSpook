enemySpeed = 0.075

update = function()
	enemySpeed = enemySpeed + 0.00001
	SetEnemySpeed(enemySpeed)
end

SeesPlayer = function(lengthBeetwen)
	if (lengthBeetwen < 20)
		then SetEnemySpeed(0.005)
		else SetEnemySpeed(3)
	end
end