/*
Copyright (C) 1997-2001 Id Software, Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/
/*
==============================================================================

BERSERK

==============================================================================
*/

#include "../g_local.h"
#include "m_berserk.h"

/*
static int sound_pain;
static int sound_die;
static int sound_idle;
static int sound_punch;
static int sound_sight;
static int sound_search;

void berserk_sight (edict_t *self, edict_t *other)
{
	gi.sound (self, CHAN_VOICE, sound_sight, 1, ATTN_NORM, 0);
}

void berserk_search (edict_t *self)
{
	gi.sound (self, CHAN_VOICE, sound_search, 1, ATTN_NORM, 0);
}


void berserk_fidget (edict_t *self);
mframe_t berserk_frames_stand [] =
{
	ai_stand, 0, berserk_fidget,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL
};
mmove_t berserk_move_stand = {FRAME_stand1, FRAME_stand5, berserk_frames_stand, NULL};

void berserk_stand (edict_t *self)
{
	self->monsterinfo.currentmove = &berserk_move_stand;
}

mframe_t berserk_frames_stand_fidget [] =
{
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL
};
mmove_t berserk_move_stand_fidget = {FRAME_standb1, FRAME_standb20, berserk_frames_stand_fidget, berserk_stand};

void berserk_fidget (edict_t *self)
{
	if (self->monsterinfo.aiflags & AI_STAND_GROUND)
		return;
	if (random() > 0.15)
		return;

	self->monsterinfo.currentmove = &berserk_move_stand_fidget;
	gi.sound (self, CHAN_WEAPON, sound_idle, 1, ATTN_IDLE, 0);
}


mframe_t berserk_frames_walk [] =
{
	ai_walk, 9.1, NULL,
	ai_walk, 6.3, NULL,
	ai_walk, 4.9, NULL,
	ai_walk, 6.7, NULL,
	ai_walk, 6.0, NULL,
	ai_walk, 8.2, NULL,
	ai_walk, 7.2, NULL,
	ai_walk, 6.1, NULL,
	ai_walk, 4.9, NULL,
	ai_walk, 4.7, NULL,
	ai_walk, 4.7, NULL,
	ai_walk, 4.8, NULL
};
mmove_t berserk_move_walk = {FRAME_walkc1, FRAME_walkc11, berserk_frames_walk, NULL};

void berserk_walk (edict_t *self)
{
	self->monsterinfo.currentmove = &berserk_move_walk;
}


mframe_t berserk_frames_run1 [] =
{
	ai_run, 21, NULL,
	ai_run, 11, NULL,
	ai_run, 21, NULL,
	ai_run, 25, NULL,
	ai_run, 18, NULL,
	ai_run, 19, NULL
};
mmove_t berserk_move_run1 = {FRAME_run1, FRAME_run6, berserk_frames_run1, NULL};

void berserk_run (edict_t *self)
{
	if (self->monsterinfo.aiflags & AI_STAND_GROUND)
		self->monsterinfo.currentmove = &berserk_move_stand;
	else
		self->monsterinfo.currentmove = &berserk_move_run1;
}


void berserk_attack_spike (edict_t *self)
{
	static	vec3_t	aim = {MELEE_DISTANCE, 0, -24};
	fire_hit (self, aim, (15 + (rand() % 6)), 400);		//	Faster attack -- upwards and backwards
}


void berserk_swing (edict_t *self)
{
	gi.sound (self, CHAN_WEAPON, sound_punch, 1, ATTN_NORM, 0);
}

mframe_t berserk_frames_attack_spike [] =
{
		ai_charge, 0, NULL,
		ai_charge, 0, NULL,
		ai_charge, 0, berserk_swing,
		ai_charge, 0, berserk_attack_spike,
		ai_charge, 0, NULL,
		ai_charge, 0, NULL,
		ai_charge, 0, NULL,
		ai_charge, 0, NULL
};
mmove_t berserk_move_attack_spike = {FRAME_att_c1, FRAME_att_c8, berserk_frames_attack_spike, berserk_run};


void berserk_attack_club (edict_t *self)
{
	vec3_t	aim;

	VectorSet (aim, MELEE_DISTANCE, self->mins[0], -4);
	fire_hit (self, aim, (5 + (rand() % 6)), 400);		// Slower attack
}

mframe_t berserk_frames_attack_club [] =
{	
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, berserk_swing,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, berserk_attack_club,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL
};
mmove_t berserk_move_attack_club = {FRAME_att_c9, FRAME_att_c20, berserk_frames_attack_club, berserk_run};


void berserk_strike (edict_t *self)
{
	//FIXME play impact sound
}


mframe_t berserk_frames_attack_strike [] =
{
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, berserk_swing,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, berserk_strike,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 9.7, NULL,
	ai_move, 13.6, NULL
};
	
mmove_t berserk_move_attack_strike = {FRAME_att_c21, FRAME_att_c34, berserk_frames_attack_strike, berserk_run};


void berserk_melee (edict_t *self)
{
	if ((rand() % 2) == 0)
		self->monsterinfo.currentmove = &berserk_move_attack_spike;
	else
		self->monsterinfo.currentmove = &berserk_move_attack_club;
}


mframe_t berserk_frames_pain1 [] =
{
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL
};
mmove_t berserk_move_pain1 = {FRAME_painc1, FRAME_painc4, berserk_frames_pain1, berserk_run};


mframe_t berserk_frames_pain2 [] =
{
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL
};
mmove_t berserk_move_pain2 = {FRAME_painb1, FRAME_painb20, berserk_frames_pain2, berserk_run};

void berserk_pain (edict_t *self, edict_t *other, float kick, int damage)
{
	if (self->health < (self->max_health / 2))
		self->s.skinnum = 1;

	if (level.time < self->pain_debounce_time)
		return;

	self->pain_debounce_time = level.time + 3;
	gi.sound (self, CHAN_VOICE, sound_pain, 1, ATTN_NORM, 0);

	if (skill->value == 3)
		return;		// no pain anims in nightmare

	if ((damage < 20) || (random() < 0.5))
		self->monsterinfo.currentmove = &berserk_move_pain1;
	else
		self->monsterinfo.currentmove = &berserk_move_pain2;
}


void berserk_dead (edict_t *self)
{
	VectorSet (self->mins, -16, -16, -24);
	VectorSet (self->maxs, 16, 16, -8);
	self->movetype = MOVETYPE_TOSS;
	self->svflags |= SVF_DEADMONSTER;
	self->nextthink = 0;
	gi.linkentity (self);
}


mframe_t berserk_frames_death1 [] =
{
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL
	
};
mmove_t berserk_move_death1 = {FRAME_death1, FRAME_death13, berserk_frames_death1, berserk_dead};


mframe_t berserk_frames_death2 [] =
{
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL
};
mmove_t berserk_move_death2 = {FRAME_deathc1, FRAME_deathc8, berserk_frames_death2, berserk_dead};


void berserk_die (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point)
{
	int		n;

	if (self->health <= self->gib_health)
	{
		gi.sound (self, CHAN_VOICE, gi.soundindex ("misc/udeath.wav"), 1, ATTN_NORM, 0);
		for (n= 0; n < 2; n++)
			ThrowGib (self, "models/objects/gibs/bone/tris.md2", damage, GIB_ORGANIC);
		for (n= 0; n < 4; n++)
			ThrowGib (self, "models/objects/gibs/sm_meat/tris.md2", damage, GIB_ORGANIC);
		ThrowHead (self, "models/objects/gibs/head2/tris.md2", damage, GIB_ORGANIC);
		self->deadflag = DEAD_DEAD;
		return;
	}

	if (self->deadflag == DEAD_DEAD)
		return;

	gi.sound (self, CHAN_VOICE, sound_die, 1, ATTN_NORM, 0);
	self->deadflag = DEAD_DEAD;
	self->takedamage = DAMAGE_YES;

	if (damage >= 50)
		self->monsterinfo.currentmove = &berserk_move_death1;
	else
		self->monsterinfo.currentmove = &berserk_move_death2;
}

void SP_monster_berserk (edict_t *self)
{
	if (deathmatch->value)
	{
		G_FreeEdict (self);
		return;
	}

	// pre-caches
	sound_pain  = gi.soundindex ("berserk/berpain2.wav");
	sound_die   = gi.soundindex ("berserk/berdeth2.wav");
	sound_idle  = gi.soundindex ("berserk/beridle1.wav");
	sound_punch = gi.soundindex ("berserk/attack.wav");
	sound_search = gi.soundindex ("berserk/bersrch1.wav");
	sound_sight = gi.soundindex ("berserk/sight.wav");

	self->s.modelindex = gi.modelindex("models/monsters/berserk/tris.md2");
	VectorSet (self->mins, -16, -16, -24);
	VectorSet (self->maxs, 16, 16, 32);
	self->movetype = MOVETYPE_STEP;
	self->solid = SOLID_BBOX;

	self->health = 240;
	self->gib_health = -60;
	self->mass = 250;

	self->pain = berserk_pain;
	self->die = berserk_die;

	self->monsterinfo.stand = berserk_stand;
	self->monsterinfo.walk = berserk_walk;
	self->monsterinfo.run = berserk_run;
	self->monsterinfo.dodge = NULL;
	self->monsterinfo.attack = NULL;
	self->monsterinfo.melee = berserk_melee;
	self->monsterinfo.sight = berserk_sight;
	self->monsterinfo.search = berserk_search;

	self->monsterinfo.currentmove = &berserk_move_stand;
	self->monsterinfo.scale = MODEL_SCALE;

	gi.linkentity (self);

	walkmonster_start (self);
}
*/


void knifethrowerThrow (edict_t *self);

mframe_t knifethrower_frames_stand [] =
{
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL
};
mmove_t knifethrower_move_stand = {0, 39, knifethrower_frames_stand, NULL};

void knifethrower_stand (edict_t *self)
{
	self->monsterinfo.currentmove = &knifethrower_move_stand;
}


mframe_t knifethrower_frames_fidget [] =
{
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL
};
mmove_t knifethrower_move_fidget = {0, 39, knifethrower_frames_fidget, knifethrower_stand};

void knifethrower_fidget (edict_t *self)
{
	self->monsterinfo.currentmove = &knifethrower_move_fidget;
	//gi.sound (self, CHAN_VOICE, sound_idle, 1, ATTN_IDLE, 0);
}

mframe_t knifethrower_frames_walk [] =
{
	ai_walk, 11,  NULL,
	ai_walk, 11,  NULL,
	ai_walk, 11,  NULL,
	ai_walk, 11,  NULL,
	ai_walk, 11,  NULL,
	ai_walk, 11,  NULL
};
mmove_t knifethrower_move_walk = {40, 45, knifethrower_frames_walk, NULL};

void knifethrower_walk (edict_t *self)
{
	self->monsterinfo.currentmove = &knifethrower_move_walk;
}

mframe_t knifethrower_frames_run [] =
{
	ai_run, 17, NULL,
	ai_run, 17, NULL,
	ai_run, 17, NULL,
	ai_run, 17, NULL,
	ai_run, 17, NULL,
	ai_run, 17, NULL
};
mmove_t knifethrower_move_run = {40, 45, knifethrower_frames_run, NULL};

void knifethrower_run (edict_t *self)
{
	if (self->monsterinfo.aiflags & AI_STAND_GROUND)
		self->monsterinfo.currentmove = &knifethrower_move_stand;
	else
		self->monsterinfo.currentmove = &knifethrower_move_run;
}


mframe_t knifethrower_frames_pain1 [] =
{
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL
};
mmove_t knifethrower_move_pain1 = {54, 57, knifethrower_frames_pain1, knifethrower_run};

mframe_t knifethrower_frames_pain2 [] =
{
	ai_move, 0, NULL,
	ai_move, 0,  NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL
};
mmove_t knifethrower_move_pain2 = {58, 61, knifethrower_frames_pain2, knifethrower_run};

mframe_t knifethrower_frames_pain3 [] =
{
	ai_move, 0, NULL,
	ai_move, 0,  NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL
};
mmove_t knifethrower_move_pain3 = {62, 65, knifethrower_frames_pain3, knifethrower_run};

void knifethrower_pain (edict_t *self, edict_t *other, float kick, int damage)
{
	int	n = rndnum (0, 2);
	int r = rndnum (0, 2);

	if (self->health < (self->max_health / 2))
		self->s.skinnum = 1;

	if (level.time < self->pain_debounce_time)
		return;

	self->pain_debounce_time = level.time + 3;
	
	if (skill->value == 3)
		return;		// no pain anims in nightmare

	if (r == 0)
		gi.sound (self, CHAN_VOICE, gi.soundindex("../players/male/pain100_1.wav"), 1, ATTN_NORM, 0);
	else if (r == 1)
		gi.sound (self, CHAN_VOICE, gi.soundindex("../players/male/pain100_2.wav"), 1, ATTN_NORM, 0);
	else
		gi.sound (self, CHAN_VOICE, gi.soundindex("../players/male/pain75_1.wav"), 1, ATTN_NORM, 0);
	
	if (n == 0)
	{
		self->monsterinfo.currentmove = &knifethrower_move_pain1;
	}
	else if (n == 1)
	{
		self->monsterinfo.currentmove = &knifethrower_move_pain2;
	}
	else
	{
		self->monsterinfo.currentmove = &knifethrower_move_pain3;
	}
}

void knifethrowerThrow (edict_t *self)
{
	vec3_t	start, target;
	vec3_t	forward, right;
//	vec3_t	vec;
	int		flash_number;
	int number = rndnum (1, 5);
    int damage = 70; //actionquake is 15 standard
    int kick = 0;

	flash_number = MZ2_SOLDIER_BLASTER_1;
	AngleVectors (self->s.angles, forward, right, NULL);
	G_ProjectSource (self->s.origin, monster_flash_offset[flash_number], forward, right, start);
	
	if (self->enemy)
	{
		VectorMA (self->enemy->s.origin, -0.2, self->enemy->velocity, target);
		target[2] += self->enemy->viewheight + 20;
		VectorSubtract (target, start, forward);
		VectorNormalize (forward);
	}
	else
	{
		AngleVectors (self->s.angles, forward, right, NULL);
	}

	//monster_fire_bullet (self, start, forward, 200, 150, 0, 0, flash_number);
	//monster_fire_shotgun (self, start, forward, damage, kick, 800, 800, 12, flash_number, MOD_M3);
	knife_throw (self, start, forward, damage, 1400);
	gi.sound(self, CHAN_AUTO, gi.soundindex("weapons/throw.wav"), 1, ATTN_NORM, 0);
}

void knifethrower_sight (edict_t *self, edict_t *other)
{
	//gi.sound (self, CHAN_BODY, sound_sight, 1, ATTN_NORM, 0);
}

void knifethrower_dead (edict_t *self)
{
	VectorSet (self->mins, -16, -16, -24);
	VectorSet (self->maxs, 16, 16, -8);
	self->movetype = MOVETYPE_TOSS;
	self->svflags |= SVF_DEADMONSTER;
	gi.linkentity (self);

	M_FlyCheck (self);
}

mframe_t knifethrower_frames_death1 [] =
{
	ai_move, 0, NULL,
	ai_move, 0,  NULL,
	ai_move, 0,  NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0,  NULL
};
mmove_t knifethrower_move_death1 = {178, 183, knifethrower_frames_death1, knifethrower_dead};

// Off with his head
mframe_t knifethrower_frames_death2 [] =
{
	ai_move, 0,   NULL,
	ai_move, 1,   NULL,
	ai_move, 5,   NULL,
	ai_move, -1,  NULL,
	ai_move, 0,   NULL,
	ai_move, 1,   NULL
};
mmove_t knifethrower_move_death2 = {184, 189, knifethrower_frames_death2, knifethrower_dead};

mframe_t knifethrower_frames_death3 [] =
{
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL
};
mmove_t knifethrower_move_death3 = {190, 197, knifethrower_frames_death3, knifethrower_dead};


void knifethrower_die (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point)
{
	int		n;
	int r = rndnum(0, 3);

// check for gib
	if (self->health <= self->gib_health)
	{
		gi.sound (self, CHAN_VOICE, gi.soundindex ("misc/udeath.wav"), 1, ATTN_NORM, 0);
		for (n= 0; n < 2; n++)
			ThrowGib (self, "models/objects/gibs/bone/tris.md2", damage, GIB_ORGANIC);
		for (n= 0; n < 4; n++)
			ThrowGib (self, "models/objects/gibs/sm_meat/tris.md2", damage, GIB_ORGANIC);
		ThrowHead (self, "models/objects/gibs/head2/tris.md2", damage, GIB_ORGANIC);
		self->deadflag = DEAD_DEAD;
		return;
	}

	if (self->deadflag == DEAD_DEAD)
		return;

// regular death
	self->deadflag = DEAD_DEAD;
	self->takedamage = DAMAGE_YES;

	self->s.modelindex2 = 0;

	if (r == 0)
		gi.sound (self, CHAN_VOICE, gi.soundindex("../players/male/death1.wav"), 1, ATTN_NORM, 0);
	else if (r == 1)
		gi.sound (self, CHAN_VOICE, gi.soundindex("../players/male/death2.wav"), 1, ATTN_NORM, 0);
	else if (r == 2)
		gi.sound (self, CHAN_VOICE, gi.soundindex("../players/male/death3.wav"), 1, ATTN_NORM, 0);
	else
		gi.sound (self, CHAN_VOICE, gi.soundindex("../players/male/death4.wav"), 1, ATTN_NORM, 0);

	n = rand() % 3;
	if (n == 0)
		self->monsterinfo.currentmove = &knifethrower_move_death1;
	else if (n == 1)
		self->monsterinfo.currentmove = &knifethrower_move_death2;
	else
		self->monsterinfo.currentmove = &knifethrower_move_death3;
}

void knifethrower_ready_fire (edict_t *self)
{
	gi.dprintf ("Ready.,,\n");
}

void knifethrower_fire (edict_t *self)
{
	knifethrowerThrow (self);
}

mframe_t knifethrower_frames_attack1 [] =
{
	ai_charge, 0, knifethrower_ready_fire,
	ai_charge, 0, knifethrower_fire,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL
};
mmove_t knifethrower_move_attack1 = {46, 53, knifethrower_frames_attack1, knifethrower_run};


/*void knifethrower_swing (edict_t *self)
{
	gi.sound (self, CHAN_WEAPON, sound_punch_swing, 1, ATTN_NORM, 0);
}

void knifethrower_smack (edict_t *self)
{
	vec3_t	aim;

	VectorSet (aim, MELEE_DISTANCE, 0, 0);
	if (fire_hit (self, aim, (5 + (rand() % 5)), 50))
		gi.sound (self, CHAN_WEAPON, sound_punch_hit, 1, ATTN_NORM, 0);
}

mframe_t knifethrower_frames_attack2 [] =
{
	ai_charge, 3, NULL,
	ai_charge, 6, NULL,
	ai_charge, 0, knifethrower_swing,
	ai_charge, 8, NULL,
	ai_charge, 5, NULL,
	ai_charge, 8, knifethrower_smack,
	ai_charge, 6, NULL,
	ai_charge, 3, NULL,
};
mmove_t knifethrower_move_attack2 = {FRAME_attak201, FRAME_attak208, knifethrower_frames_attack2, knifethrower_run};*/

void knifethrower_attack(edict_t *self)
{
	self->monsterinfo.currentmove = &knifethrower_move_attack1;
}


/*QUAKED monster_berserk (1 .5 0) (-16 -16 -24) (16 16 32) Ambush Trigger_Spawn Sight
*/
void SP_monster_berserk (edict_t *self)
{
	if (deathmatch->value)
	{
		G_FreeEdict (self);
		return;
	}

	self->movetype = MOVETYPE_STEP;
	self->solid = SOLID_BBOX;
	self->s.modelindex = gi.modelindex("models/knife/tris.md2");
	self->s.modelindex2 = gi.modelindex("models/knife/w_knife.md2");
	VectorSet (self->mins, -16, -16, -24);
	VectorSet (self->maxs, 16, 16, 32);

	self->health = 280;
	self->gib_health = -40;
	self->mass = 125;

	self->pain = knifethrower_pain;
	self->die = knifethrower_die;

	self->weap_num = 0;

	self->monsterinfo.stand = knifethrower_stand;
	self->monsterinfo.walk = knifethrower_walk;
	self->monsterinfo.run = knifethrower_run;
	self->monsterinfo.dodge = /*knifethrower_dodge*/NULL;
	self->monsterinfo.attack = knifethrower_attack;
	self->monsterinfo.melee = NULL;
	self->monsterinfo.sight = knifethrower_sight;
	self->monsterinfo.idle = knifethrower_fidget;

	gi.linkentity (self);

	self->monsterinfo.currentmove = &knifethrower_move_stand;
	self->monsterinfo.scale = MODEL_SCALE;

	walkmonster_start (self);
}