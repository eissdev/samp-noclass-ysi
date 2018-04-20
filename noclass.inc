// Called when a player is fully connected to the server.
// OnPlayerFullyConnected(playerid)
#define ALS_DO_PlayerFullyConnected<%0> %0<PlayerFullyConnected,i>(end:playerid)

public OnPlayerRequestClass(playerid, classid)
{
	if(IsPlayerNPC(playerid)) {
		return 1;
	}
	
	// Enables spectator mode. This will hide the class selection buttons.
	TogglePlayerSpectating(playerid, true);
	
	SetPVarInt(playerid, "noclass", 1);

	#if defined CS_OnPlayerRequestClass
	    return CS_OnPlayerRequestClass(playerid, classid);
	#else
	    return 1;
	#endif
}

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(GetPVarType(playerid, "noclass")) {
		DeletePVar(playerid, "noclass");

		// -- Hook --
		call OnPlayerFullyConnected(playerid);

	}
	return 1;
}

stock CS_SpawnPlayer(playerid)
{
	if (GetPlayerState(playerid) == PLAYER_STATE_SPECTATING)
	{
	    TogglePlayerSpectating(playerid, false);
	}
	return SpawnPlayer(playerid);
}

#if defined _ALS_OnPlayerRequestClass
	#undef OnPlayerRequestClass
#else
	#define _ALS_OnPlayerRequestClass
#endif

#define OnPlayerRequestClass CS_OnPlayerRequestClass

#if defined _ALS_SpawnPlayer
	#undef SpawnPlayer
#else
	#define _ALS_SpawnPlayer
#endif

#define SpawnPlayer CS_SpawnPlayer

#if defined CS_OnPlayerRequestClass
	forward CS_OnPlayerRequestClass(playerid, classid);
#endif
