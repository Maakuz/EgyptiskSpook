enemySpeed = 0.075

update = function()
	if (GetDistanceBetween() < 10)
		then SetEnemySpeed(0.0)
		else SetEnemySpeed(0.2)
	end
end