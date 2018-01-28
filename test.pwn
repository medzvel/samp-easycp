#include "easyCP.inc"

#include <zcmd>

CMD:testcp(playerid, params[])
{
	new
	    Float:x,
	    Float:y,
	    Float:z
	;
	
	GetPlayerPos(playerid, x, y, z);
	
	SetPlayerPos(playerid, x+5, y, z);
	
    CreateCheckPoint(playerid, TestCP, x, y, z, 2.0);
    return 1;
}

CMD:testcp2(playerid, params[])
{
	new
	    Float:x,
	    Float:y,
	    Float:z
	;

	GetPlayerPos(playerid, x, y, z);

	SetPlayerPos(playerid, x+5, y, z);
	
	CreateCheckPoint(playerid, TestCP2, x, y, z, 2.0);

	return 1;
}

CheckPoint:TestCP(playerid, checkpointid)
{
	SendClientMessage(playerid, -1, "Its TestCP");
	HideCheckPoint(playerid, checkpointid);
	return 1;
}

CheckPoint:TestCP2(playerid, checkpointid)
{
	SendClientMessage(playerid, -1, "Its TestCP2");
	HideCheckPoint(playerid, checkpointid);
	return 1;
}
