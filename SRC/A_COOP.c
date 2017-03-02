/*
Paril

Cooperative and Single Player related stuff
goes here!

NOTE: All functions related must start with Coop_
*/
#include "g_local.h"
#include "a_coop.h"

/*
===============
Main Functions!
===============
*/
// Paril
// -----
// Searches for an entity
// and sees if one is a target
// the player must kill
// (forces killtarget mode if not set)
// -----
qboolean Coop_FindKillTarget ()
{
	edict_t *e;
	int i;
	
	for (i=1, e=g_edicts+i; i < globals.num_edicts; i++,e++)
	{
		if (!e->inuse)
			continue;
		
		if (e->kill_target)
		{
			// Uh oh, Kill target found!
			// Mapper forgot to set this, or
			// the map is a custom mission and
			// forgot to set the appropriate flag
			level.coop_gamemode = COOPMODE_KILLTARGET;
			gi.dprintf ("Found kill target when no kill target flag. Fixing.\n");
			return true;
		}
	}
	return false;
}

// Paril
// -----
// Searches for an entity
// and sees if one is a target
// the player must defend
// (forces defend target mode if not set)
// -----

qboolean Coop_FindDefendTarget ()
{
	edict_t *e;
	int i;
	
	for (i=1, e=g_edicts+i; i < globals.num_edicts; i++,e++)
	{
		if (!e->inuse)
			continue;
		
		if (e->defend_target)
		{
			// Uh oh, Defend target found!
			// Mapper forgot to set this, or
			// the map is a custom mission and
			// forgot to set the appropriate flag
			level.coop_gamemode = COOPMODE_DEFENDTARGET;
			gi.dprintf ("Found defend target when no defend target flag. Fixing.\n");
			return true;
		}
	}
	return false;
}

// Paril
// -----
// Searches for an entity
// and sees if the capture
// entity is there.
// (forces capture mode if not set)
// -----
qboolean Coop_FindCaptureTarget ()
{
	edict_t *e;
	int i;
	
	for (i=1, e=g_edicts+i; i < globals.num_edicts; i++,e++)
	{
		if (!e->inuse)
			continue;
		
		if (Q_stricmp (e->classname, "coop_briefcase") == 0)
		{
			// Uh oh, capture ent found!
			// Mapper forgot to set this, or
			// the map is a custom mission and
			// forgot to set the appropriate flag
			level.coop_gamemode = COOPMODE_CAPTURE;
			gi.dprintf ("Found briefcase when no capture flag. Fixing.\n");
			return true;
		}
	}
	return false;
}

void Coop_CheckExterminationRules()
{
	edict_t *ent;
	int i;
	int monsters_killed = level.killed_monsters;
	int total_monsters = level.total_monsters;

	if (level.game_won == 1)
		return;

	// Are all the monsters killed?
	if (monsters_killed == total_monsters)
	{
		level.game_won = 1;
        for (i = 0; i < game.maxclients; i++)
        {
			ent = &g_edicts[1+i];
			if (!ent->inuse)
				continue;
			if (!ent->client)
				continue;
			
			Coop_OpenEndingMenu (ent, 1);
		}
	}

	// Paril, FIXME
	// Cvar that if you die, 
	// you lose this mission
}

void Coop_CheckKillTargetRules()
{
	edict_t *e, *ent;
	int i;
	
	if (level.game_won == 1)
		return;

	// Put the kill target as a global entity.
	// This way, we can use him anywhere! ANYWHERE!
	if (!kill_target_entity)
	{
		for (i=1, e=g_edicts+i; i < globals.num_edicts; i++,e++)
		{
			if (!e->inuse)
				continue;
			
			if (e->kill_target)
			{
				kill_target_entity = e;
			}
		}
	}

	// We win!
	if (kill_target_entity->health < 1)
	{
		level.game_won = 1;
        for (i = 0; i < game.maxclients; i++)
        {
			ent = &g_edicts[1+i];
			if (!ent->inuse)
				continue;
			if (!ent->client)
				continue;
			
			Coop_OpenEndingMenu (ent, 1);
		}
	}
}

void Coop_CheckDefendTargetRules()
{
	int monsters_killed = level.killed_monsters;
	int total_monsters = level.total_monsters;
	edict_t *e, *ent;
	int i;
	
	if (level.game_won == 1)
		return;
	// Put the kill target as a global entity.
	// This way, we can use him anywhere! ANYWHERE!
	if (!defend_target_entity)
	{
		for (i=1, e=g_edicts+i; i < globals.num_edicts; i++,e++)
		{
			if (!e->inuse)
				continue;
			
			if (e->defend_target)
			{
				defend_target_entity = e;
			}
		}
	}

	if (level.game_won == 1 || level.game_won == -1)
		return;

	// We win!
	if (monsters_killed == total_monsters && defend_target_entity->health > 1)
	{
		level.game_won = 1;
        for (i = 0; i < game.maxclients; i++)
        {
			ent = &g_edicts[1+i];
			if (!ent->inuse)
				continue;
			if (!ent->client)
				continue;
			
			Coop_OpenEndingMenu (ent, 1);
		}
	}
	else if (defend_target_entity->health < 1) // Uh oh, the defend target died!
	{
		level.game_won = -1;
        for (i = 0; i < game.maxclients; i++)
        {
			ent = &g_edicts[1+i];
			if (!ent->inuse)
				continue;
			if (!ent->client)
				continue;
			
			Coop_OpenEndingMenu (ent, 0);
		}
	}
}

void Coop_CheckCaptureRules()
{
	//int monsters_killed = level.killed_monsters;
	//int total_monsters = level.total_monsters;
//	edict_t *e, *ent;
//	int i;

	// Paril: This one is a doozy
	// We need to find the person who has the CT, and
	// then check if they are near a target_ct.
	
	// FIXME: If the case falls somewhere where it shouldn't,
	// how do we check that?
	
	// Revision: Workaround, don't use a map that has lava/slime XD

	// Revision 2: You can't drop the case. If you die, the case drops where you died.
	// Maybe it should go back to it's starting pos?

	// Revision numéro trois: Coop_FindPersonWithCase is called by the target_ct. This old way
	// looked for stuff in the player, it looks from the Capture point.

	/*for (i = 0; i < game.maxclients; i++)
	{
		ent = &g_edicts[1+i];
		if (!ent->inuse)
			continue;
		if (!ent->client)
			continue;
	}*/
}

// Paril
// -----
// Checks the gameplay, checks if
// the mission has been won!
// -----
void Coop_CheckRules ()
{
	switch (level.coop_gamemode)
	{
	case 0:
		break;
	case 1:
		Coop_CheckExterminationRules();
		break;
	case 2:
		Coop_CheckKillTargetRules();
		break;
	case 3:
		Coop_CheckDefendTargetRules();
		break;
	case 4:
		Coop_CheckCaptureRules();
		break;
	default:
		break;
	}
}

/*
===============
Menu Functions!
===============
*/
// Paril
// -----
// The menu that opens to tell you
// you won the mission.
// -----
void CloseMenu (edict_t *ent, pmenu_t *p)
{
	PMenu_Close (ent);
}

// Paril
// -----
// The menu command that reloads the map.
// FIXME
// -----
void Coop_ReloadMap (edict_t *ent, pmenu_t *p)
{
}

pmenu_t coop_extraoptionsmenu[] = {
  { "*Action Quake 2",                      PMENU_ALIGN_CENTER, NULL, NULL },
  { "--------------",                       PMENU_ALIGN_CENTER, NULL, NULL },
  { "*Extra Options:",                PMENU_ALIGN_CENTER, NULL, NULL },
  { NULL,   PMENU_ALIGN_CENTER, NULL, NULL },
  { NULL,                PMENU_ALIGN_CENTER, NULL, NULL },
  { "--Client--",           PMENU_ALIGN_CENTER, NULL, NULL },
  { "Disconnect",          PMENU_ALIGN_CENTER, NULL, NULL },
  { "Cheats",          PMENU_ALIGN_CENTER, NULL, NULL },
  { "--Server--",             PMENU_ALIGN_CENTER, NULL, NULL },
  { "Reload Map",             PMENU_ALIGN_CENTER, NULL, Coop_ReloadMap },
  { "Select Mission",                          PMENU_ALIGN_CENTER, NULL, NULL },
  { NULL,                               PMENU_ALIGN_LEFT, NULL, NULL },
  { NULL,                               PMENU_ALIGN_LEFT, NULL, NULL },
  { "Close",                               PMENU_ALIGN_LEFT, NULL, CloseMenu },
  { NULL,                               PMENU_ALIGN_LEFT, NULL, NULL },
  { "Press TAB to close.",    PMENU_ALIGN_LEFT, NULL, NULL },
  { NULL,                                 PMENU_ALIGN_LEFT, NULL, NULL },
  { "v" ACTION_VERSION,       PMENU_ALIGN_RIGHT, NULL, NULL },
};

pmenu_t coop_winningmenu[] = {
  { "*Action Quake 2",                      PMENU_ALIGN_CENTER, NULL, NULL },
  { "--------------",                       PMENU_ALIGN_CENTER, NULL, NULL },
  { NULL,   PMENU_ALIGN_CENTER, NULL, NULL },
  { NULL,                PMENU_ALIGN_CENTER, NULL, NULL },
  { NULL,           PMENU_ALIGN_CENTER, NULL, NULL },
  { NULL,          PMENU_ALIGN_CENTER, NULL, NULL },
  { "*You Won The Mission!",                PMENU_ALIGN_CENTER, NULL, NULL },
  { NULL,             PMENU_ALIGN_CENTER, NULL, NULL },
  { "You may continue playing, but",             PMENU_ALIGN_CENTER, NULL, NULL },
  { "you cannot gain anything extra.",                          PMENU_ALIGN_CENTER, NULL, NULL },
  { NULL,                               PMENU_ALIGN_LEFT, NULL, NULL },
 // { "Extra Options",                               PMENU_ALIGN_LEFT, NULL, Coop_OpenExtraOptionsMenu },
  { "Close",                               PMENU_ALIGN_LEFT, NULL, CloseMenu },
  { NULL,                               PMENU_ALIGN_LEFT, NULL, NULL },
  { "Press TAB to close.",    PMENU_ALIGN_LEFT, NULL, NULL },
  { NULL,                                 PMENU_ALIGN_LEFT, NULL, NULL },
  { "v" ACTION_VERSION,       PMENU_ALIGN_RIGHT, NULL, NULL },
};

pmenu_t coop_loosingmenu[] = {
  { "*Action Quake 2",                      PMENU_ALIGN_CENTER, NULL, NULL },
  { "--------------",                       PMENU_ALIGN_CENTER, NULL, NULL },
  { NULL,   PMENU_ALIGN_CENTER, NULL, NULL },
  { NULL,                PMENU_ALIGN_CENTER, NULL, NULL },
  { NULL,           PMENU_ALIGN_CENTER, NULL, NULL },
  { NULL,          PMENU_ALIGN_CENTER, NULL, NULL },
  { "*You Lost The Mission!",                PMENU_ALIGN_CENTER, NULL, NULL },
  { NULL,             PMENU_ALIGN_CENTER, NULL, NULL },
  { "You may continue playing, but",             PMENU_ALIGN_CENTER, NULL, NULL },
  { "you cannot win the mission anymore,",                          PMENU_ALIGN_CENTER, NULL, NULL },
  { "mainly because the target was killed.",                   PMENU_ALIGN_CENTER, NULL, NULL },
  { NULL,                               PMENU_ALIGN_LEFT, NULL, NULL },
//{ "Extra Options",                               PMENU_ALIGN_LEFT, NULL, Coop_OpenExtraOptionsMenu },
  { "Close",                               PMENU_ALIGN_LEFT, NULL, CloseMenu },
  { NULL,                               PMENU_ALIGN_LEFT, NULL, NULL },
  { "Press TAB to close.",    PMENU_ALIGN_LEFT, NULL, NULL },
  { NULL,                                 PMENU_ALIGN_LEFT, NULL, NULL },
  { "v" ACTION_VERSION,       PMENU_ALIGN_RIGHT, NULL, NULL },
};

// Paril
// -----
// Function to open the menu that
// tells you you won or lost the mission
// -----

void Coop_OpenEndingMenu(edict_t *ent, int won)
{
	if (won)
        PMenu_Open(ent, coop_winningmenu, -1, sizeof(coop_winningmenu) / sizeof(pmenu_t));
	else
		PMenu_Open(ent, coop_loosingmenu, -1, sizeof(coop_loosingmenu) / sizeof(pmenu_t));
}

// Paril
// -----
// Function that opens the extra
// options menu.
// -----
void Coop_OpenExtraOptionsMenu (edict_t *ent, pmenu_t *p)
{
	PMenu_Open(ent, coop_extraoptionsmenu, -1, sizeof(coop_extraoptionsmenu) / sizeof(pmenu_t));
}

/*
=============
New Entities!
=============
*/

void Coop_FindPersonWithCase (edict_t *self)
{
	edict_t *ent;
	int i;
	edict_t *e = findradius(NULL, self->s.origin, 80);
	
	while (e)
	{
		if (!e->inuse)
			return;
		if (level.game_won)
		{
			G_FreeEdict (self);
			return;
		}
		
		if (Q_stricmp(e->classname, "player") == 0)
		{
			if (!e->client->pers.inventory[ITEM_INDEX(FindItem(CAPTURE_NAME))])
				break;
			// Yay, we won! Open the menu and tell everybody about it.
			for (i = 0; i < game.maxclients; i++)
			{
				ent = &g_edicts[1+i];
				if (!ent->inuse)
					continue;
				if (!ent->client)
					continue;
				
				Coop_OpenEndingMenu (ent, 1);
				level.game_won = 1;
			}
		}
	}

	self->nextthink = 0.01;
	return;
}

void SP_target_ct (edict_t *self)
{
	self->think = Coop_FindPersonWithCase;
	self->nextthink = 0.01;

	gi.linkentity (self);
}

/*
===============
Test Functions!
===============
*/

// Paril
// -----
// Finds a random spot
// on the map, and uses it.
// Not to be confused with
// DM spawn points, this is
// full random spots!
// -----
qboolean findspawnpoint (edict_t *ent)
{
	vec3_t loc = {0,0,0};
	vec3_t floor;
	int i;
	int j = 0;
	int k = 0;
	trace_t tr;

	do 
	{
		j++;
		for (i = 0; i < 3; i++)
			loc[i] = rand() % (8192 + 1) - 4096;
		
		if (gi.pointcontents(loc) == 0)
		{
			VectorCopy(loc, floor);
			floor[2] = -4096;
			tr = gi.trace (loc, vec3_origin, vec3_origin, floor, NULL, MASK_SOLID);
			k++;
			if (tr.contents & MASK_WATER)
				continue; 
			VectorCopy (tr.endpos, loc);
			loc[2] += ent->maxs[2] - ent->mins[2]; // make sure the entity can fit!
		}
	} while (gi.pointcontents(loc) > 0 && j < 1000 && k < 500);
	
	if (j >= 1000 || k >= 500)
		return false;
	
	loc[2] += 82;
	VectorCopy(loc,ent->s.origin);
	VectorCopy(loc,ent->s.old_origin);
	return true;
}

void Coop_RandomizeAngles (edict_t *e)
{
	//e->s.angles[0] = rndnum (0, 360);
	e->s.angles[1] = rndnum (0, 360);
	//e->s.angles[2] = rndnum (0, 360);
}

// Paril, For testing
// Creates a random mission!
// This may become a part of the real thing later.
// What do you think, Fred?
void Coop_CreateRandomMission()
{
	edict_t *monster[10];
	int random;
	int rnd;
	//void functions[3] = {SP_monster_soldier, SP_monster_infantry, SP_monster_gunner};

	// 10 monsters for test!

	// Revision: Wow, it actually worked.
	for (random = 0; random < 10; random++)
	{
		monster[random] = G_Spawn();
		findspawnpoint (monster[random]);

		rnd = rndnum (0, 5);

		if (random == 0 || random == 1)
			SP_monster_soldier (monster[random]);
		else if (random == 2 || random == 3)
			SP_monster_infantry (monster[random]);
		else if (random == 4 || random == 5)
			SP_monster_gunner (monster[random]);

		Coop_RandomizeAngles (monster[random]);
	}
}

void Coop_FollowPlayer (edict_t *self)
{
	if (!self->owner)
	{
		G_FreeEdict (self);
		return;
	}
	if (!self->owner->inuse)
	{
		G_FreeEdict (self);
		return;
	}	
	if (self->owner->health < 1)
	{
		G_FreeEdict (self);
		return;
	}
	VectorCopy(self->owner->s.origin, self->s.origin);
	gi.linkentity (self);

	self->nextthink = 0.01;
}


void Coop_SpawnBriefcaseSprite (edict_t *ent)
{
	ent->s.modelindex4 = gi.modelindex ("models/items/case/high.md2");
}

