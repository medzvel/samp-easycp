#define CheckPoint:%0(%1) \
	forward CheckPoint_%0(%1); public CheckPoint_%0(%1)

#define CreateCheckPoint(%0,%1,%2) \
	CheckPoint_Create(%0, #%1, %2)

static stock
	c_cp_func[MAX_PLAYERS][32 char]
;


stock CheckPoint_Created(playerid)
	return (GetPVarInt(playerid, "CHECKPOINT_CREATED"));

stock CheckPoint_Delete(playerid)
{
	DeletePVar(playerid, "CHECKPOINT_CREATED");
	c_cp_func[playerid]{0} = 0;

	DisablePlayerCheckpoint(playerid);
	return 0;
}

stock CheckPoint_Create(playerid, function[], Float:x, Float:y, Float:z, Float:size)
{
	if(CheckPoint_Created(playerid))
	{
		CheckPoint_Delete(playerid);
	}	
	SetPlayerCheckpoint(playerid, x, y, z, size);
	SetPVarInt(playerid, "CHECKPOINT_CREATED", 1);
	strpack(c_cp_func[playerid], function);
	return 1;
}

public OnPlayerEnterCheckpoint(playerid)
{
	if((c_cp_func[playerid]{0}))
	{
		new 
			func[40]
		;
		
		strcat(func, "CheckPoint_");
		strcat(func, c_cp_func[playerid]);
		
		CheckPoint_Delete(playerid);

		CallLocalFunction(func, "d", playerid);
	}
	#if defined EasyCP_OnPlayerEnterCheckpoint
		EasyCP_OnPlayerEnterCheckpoint(playerid);
	#endif
	return 0;	
}

#if defined _ALS_OnPlayerEnterCheckpoint
	#undef OnPlayerEnterCheckpoint
#else
	#define _ALS_OnPlayerEnterCheckpoint
#endif

#define OnPlayerEnterCheckpoint EasyCP_OnPlayerEnterCheckpoint

#if defined EasyCP_OnPlayerEnterCheckpoint
	forward EasyCP_OnPlayerEnterCheckpoint(playerid);
#endif