#include <map>

#define CreateCheckPoint(%0,%1,%2) \
	CreateEasyCP(%0, #%1, %2)

#define CheckPoint:%0(%1) \
	forward Checkpoint_%0(%1); public Checkpoint_%0(%1)	

#define EASY_CP_FNAME_LEN   22

// Easy checkpoint functions
static Map:easyCPFunctions;

// Create easy checkpoint
stock CreateEasyCP(playerid, const fname[], Float:x, Float:y, Float:z, Float:size, Float:visibledistance = STREAMER_CP_SD)
{
	if(sizeof(fname) > EASY_CP_FNAME_LEN) return printf("[easyCP Error] function name can't be more then 21 character.");
    new ret = CreateDynamicCP(Float:x, Float:y, Float:z, Float:size, .playerid = playerid, .streamdistance = visibledistance);
    new fn[EASY_CP_FNAME_LEN + 11] = "Checkpoint_";
    strcat(fn, fname);
    MAP_insert_val_str(easyCPFunctions, ret, fn);
    Streamer_Update(playerid, STREAMER_TYPE_CHECKPOINT);
    return ret;
}

stock HideCheckPoint(playerid, checkpointid)
{
	Streamer_RemoveArrayData(STREAMER_TYPE_CP, checkpointid, E_STREAMER_PLAYER_ID, playerid);
	Streamer_Update(playerid, STREAMER_TYPE_CHECKPOINT);
}

stock ShowCheckPoint(playerid, checkpointid)
{
	Streamer_AppendArrayData(STREAMER_TYPE_CP, checkpointid, E_STREAMER_PLAYER_ID, playerid);
	Streamer_Update(playerid, STREAMER_TYPE_CHECKPOINT);
}


// Destroy easy checkpoint
stock DestroyCheckPoint(checkpointid)
{
    if (MAP_remove_val(easyCPFunctions, checkpointid))
        return DestroyDynamicCP(checkpointid);

    return 0;
}

// On player enter dynamic checkpoint
public OnPlayerEnterDynamicCP(playerid, checkpointid)
{
    if (MAP_contains_val(easyCPFunctions, checkpointid))
    {
        new fname[EASY_CP_FNAME_LEN + 11];
        MAP_get_val_arr(easyCPFunctions, checkpointid, fname);
        CallLocalFunction(fname, "dd", playerid, checkpointid);
    }
    return 0;    
}
#if defined _ALS_OnPlayerEnterDynamicCP
    #undef OnPlayerEnterDynamicCP
#else
    #define _ALS_OnPlayerEnterDynamicCP
#endif
#define OnPlayerEnterDynamicCP EasyCP_OnPlayerEnterDynamicCP
