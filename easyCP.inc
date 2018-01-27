#include <streamer>
#include <map>

#define CreateCheckPoint(%0,%1,%2) \
	CreateEasyCP(%0, #%1, %2)

#define CheckPoint:%0(%1) \
	forward Checkpoint_%0(%1); public Checkpoint_%0(%1)	

#define EASY_CP_FNAME_LEN   21

// Easy checkpoint functions
static Map:easyCPFunctions;

// Create easy checkpoint
stock CreateEasyCP(playerid, const fname[], Float:x, Float:y, Float:z, Float:size, Float:visibledistance = STREAMER_CP_SD)
{
    new ret = CreateDynamicCP(Float:x, Float:y, Float:z, Float:size, .playerid = playerid, .streamdistance = visibledistance);
    new fn[EASY_CP_FNAME_LEN + 11] = "Checkpoint_";
    strcat(fn, fname);
    MAP_insert_val_str(easyCPFunctions, ret, fn);
    return ret;
}

// Destroy easy checkpoint
stock DestroyEasyCP(checkpointid)
{
    if (MAP_contains_val(easyCPFunctions, checkpointid))
    {
        MAP_remove_val(easyCPFunctions, checkpointid);
    }
    return DestroyDynamicCP(checkpointid);
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
