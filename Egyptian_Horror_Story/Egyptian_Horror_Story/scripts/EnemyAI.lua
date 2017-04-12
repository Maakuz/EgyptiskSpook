enemySpeed = 0.075

update = function()
	local dist = GetDistanceBetween();
	if (dist < 10)
		then SetEnemySpeed(0.1)
		else SetEnemySpeed(0.4)
	end
		
	if (dist > 20) then
		local fX, fY, fZ = GetPlayerForward()
		local pX, pY, pZ = GetPlayerPosition()
		SetEnemyPosition(pX - fX * 10, pY - fY * 10, pZ - fZ * 10)
	end
end