enemySpeed = 0.075

SeesPlayer = function(lengthBeetwen)
	if (lengthBeetwen < 20)
		then SetEnemySpeed(100)
		else SetEnemySpeed(150)
	end
end