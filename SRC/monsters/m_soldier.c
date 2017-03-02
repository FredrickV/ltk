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

SOLDIER

==============================================================================
*/

#include "../g_local.h"
#include "m_soldier.h"


static int	sound_idle;
static int	sound_sight1;
static int	sound_sight2;
static int	sound_pain_light;
static int	sound_pain;
static int	sound_pain_ss;
static int	sound_death_light;
static int	sound_death;
static int	sound_death_ss;
static int	sound_cock;


void soldier_idle (edict_t *self)
{
	if (random() > 0.8)
		gi.sound (self, CHAN_VOICE, sound_idle, 1, ATTN_IDLE, 0);
}

void soldier_cock (edict_t *self)
{
	if (self->s.frame == FRAME_stand322)
		gi.sound (self, CHAN_WEAPON, sound_cock, 1, ATTN_IDLE, 0);
	else
		gi.sound (self, CHAN_WEAPON, sound_cock, 1, ATTN_NORM, 0);
}


// STAND

void soldier_stand (edict_t *self);

mframe_t soldier_frames_stand1 [] =
{
	ai_stand, 0, soldier_idle,
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
mmove_t soldier_move_stand1 = {FRAME_stand101, FRAME_stand130, soldier_frames_stand1, soldier_stand};

mframe_t soldier_frames_stand3 [] =
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
	ai_stand, 0, soldier_cock,
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
mmove_t soldier_move_stand3 = {FRAME_stand301, FRAME_stand339, soldier_frames_stand3, soldier_stand};

#if 0
mframe_t soldier_frames_stand4 [] =
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
	ai_stand, 0, NULL,

	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 0, NULL,
	ai_stand, 4, NULL,
	ai_stand, 1, NULL,
	ai_stand, -1, NULL,
	ai_stand, -2, NULL,

	ai_stand, 0, NULL,
	ai_stand, 0, NULL
};
mmove_t soldier_move_stand4 = {FRAME_stand401, FRAME_stand452, soldier_frames_stand4, NULL};
#endif

void soldier_stand (edict_t *self)
{
	if ((self->monsterinfo.currentmove == &soldier_move_stand3) || (random() < 0.8))
		self->monsterinfo.currentmove = &soldier_move_stand1;
	else
		self->monsterinfo.currentmove = &soldier_move_stand3;
}


//
// WALK
//

void soldier_walk1_random (edict_t *self)
{
	if (random() > 0.1)
		self->monsterinfo.nextframe = FRAME_walk101;
}

mframe_t soldier_frames_walk1 [] =
{
	ai_walk, 3,  NULL,
	ai_walk, 6,  NULL,
	ai_walk, 2,  NULL,
	ai_walk, 2,  NULL,
	ai_walk, 2,  NULL,
	ai_walk, 1,  NULL,
	ai_walk, 6,  NULL,
	ai_walk, 5,  NULL,
	ai_walk, 3,  NULL,
	ai_walk, -1, soldier_walk1_random,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL,
	ai_walk, 0,  NULL
};
mmove_t soldier_move_walk1 = {FRAME_walk101, FRAME_walk133, soldier_frames_walk1, NULL};

mframe_t soldier_frames_walk2 [] =
{
	ai_walk, 4,  NULL,
	ai_walk, 4,  NULL,
	ai_walk, 9,  NULL,
	ai_walk, 8,  NULL,
	ai_walk, 5,  NULL,
	ai_walk, 1,  NULL,
	ai_walk, 3,  NULL,
	ai_walk, 7,  NULL,
	ai_walk, 6,  NULL,
	ai_walk, 7,  NULL
};
mmove_t soldier_move_walk2 = {FRAME_walk209, FRAME_walk218, soldier_frames_walk2, NULL};

void soldier_walk (edict_t *self)
{
	if (random() < 0.5)
		self->monsterinfo.currentmove = &soldier_move_walk1;
	else
		self->monsterinfo.currentmove = &soldier_move_walk2;
}


//
// RUN
//

void soldier_run (edict_t *self);

mframe_t soldier_frames_start_run [] =
{
	ai_run, 7,  NULL,
	ai_run, 5,  NULL
};
mmove_t soldier_move_start_run = {FRAME_run01, FRAME_run02, soldier_frames_start_run, soldier_run};

mframe_t soldier_frames_run [] =
{
	ai_run, 10, NULL,
	ai_run, 11, NULL,
	ai_run, 11, NULL,
	ai_run, 16, NULL,
	ai_run, 10, NULL,
	ai_run, 15, NULL
};
mmove_t soldier_move_run = {FRAME_run03, FRAME_run08, soldier_frames_run, NULL};

void soldier_run (edict_t *self)
{
	if (self->monsterinfo.aiflags & AI_STAND_GROUND)
	{
		self->monsterinfo.currentmove = &soldier_move_stand1;
		return;
	}

	if (self->monsterinfo.currentmove == &soldier_move_walk1 ||
		self->monsterinfo.currentmove == &soldier_move_walk2 ||
		self->monsterinfo.currentmove == &soldier_move_start_run)
	{
		self->monsterinfo.currentmove = &soldier_move_run;
	}
	else
	{
		self->monsterinfo.currentmove = &soldier_move_start_run;
	}
}


//
// PAIN
//

mframe_t soldier_frames_pain1 [] =
{
	ai_move, -3, NULL,
	ai_move, 4,  NULL,
	ai_move, 1,  NULL,
	ai_move, 1,  NULL,
	ai_move, 0,  NULL
};
mmove_t soldier_move_pain1 = {FRAME_pain101, FRAME_pain105, soldier_frames_pain1, soldier_run};

mframe_t soldier_frames_pain2 [] =
{
	ai_move, -13, NULL,
	ai_move, -1,  NULL,
	ai_move, 2,   NULL,
	ai_move, 4,   NULL,
	ai_move, 2,   NULL,
	ai_move, 3,   NULL,
	ai_move, 2,   NULL
};
mmove_t soldier_move_pain2 = {FRAME_pain201, FRAME_pain207, soldier_frames_pain2, soldier_run};

mframe_t soldier_frames_pain3 [] =
{
	ai_move, -8, NULL,
	ai_move, 10, NULL,
	ai_move, -4, NULL,
	ai_move, -1, NULL,
	ai_move, -3, NULL,
	ai_move, 0,  NULL,
	ai_move, 3,  NULL,
	ai_move, 0,  NULL,
	ai_move, 0,  NULL,
	ai_move, 0,  NULL,
	ai_move, 0,  NULL,
	ai_move, 1,  NULL,
	ai_move, 0,  NULL,
	ai_move, 1,  NULL,
	ai_move, 2,  NULL,
	ai_move, 4,  NULL,
	ai_move, 3,  NULL,
	ai_move, 2,  NULL
};
mmove_t soldier_move_pain3 = {FRAME_pain301, FRAME_pain318, soldier_frames_pain3, soldier_run};

mframe_t soldier_frames_pain4 [] =
{
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, -10, NULL,
	ai_move, -6,  NULL,
	ai_move, 8,   NULL,
	ai_move, 4,   NULL,
	ai_move, 1,   NULL,
	ai_move, 0,   NULL,
	ai_move, 2,   NULL,
	ai_move, 5,   NULL,
	ai_move, 2,   NULL,
	ai_move, -1,  NULL,
	ai_move, -1,  NULL,
	ai_move, 3,   NULL,
	ai_move, 2,   NULL,
	ai_move, 0,   NULL
};
mmove_t soldier_move_pain4 = {FRAME_pain401, FRAME_pain417, soldier_frames_pain4, soldier_run};


void soldier_pain (edict_t *self, edict_t *other, float kick, int damage)
{
	float	r;
	int		n;

	if (self->health < (self->max_health / 2))
			self->s.skinnum |= 1;

	if (level.time < self->pain_debounce_time)
	{
		if ((self->velocity[2] > 100) && ( (self->monsterinfo.currentmove == &soldier_move_pain1) || (self->monsterinfo.currentmove == &soldier_move_pain2) || (self->monsterinfo.currentmove == &soldier_move_pain3)))
			self->monsterinfo.currentmove = &soldier_move_pain4;
		return;
	}

	self->pain_debounce_time = level.time + 3;

	n = self->s.skinnum | 1;
	if (n == 1)
		gi.sound (self, CHAN_VOICE, sound_pain_light, 1, ATTN_NORM, 0);
	else if (n == 3)
		gi.sound (self, CHAN_VOICE, sound_pain, 1, ATTN_NORM, 0);
	else
		gi.sound (self, CHAN_VOICE, sound_pain_ss, 1, ATTN_NORM, 0);

	if (self->velocity[2] > 100)
	{
		self->monsterinfo.currentmove = &soldier_move_pain4;
		return;
	}

	if (skill->value == 3)
		return;		// no pain anims in nightmare

	r = random();

	if (r < 0.33)
		self->monsterinfo.currentmove = &soldier_move_pain1;
	else if (r < 0.66)
		self->monsterinfo.currentmove = &soldier_move_pain2;
	else
		self->monsterinfo.currentmove = &soldier_move_pain3;
}


//
// ATTACK
//

static int blaster_flash [] = {MZ2_SOLDIER_BLASTER_1, MZ2_SOLDIER_BLASTER_2, MZ2_SOLDIER_BLASTER_3, MZ2_SOLDIER_BLASTER_4, MZ2_SOLDIER_BLASTER_5, MZ2_SOLDIER_BLASTER_6, MZ2_SOLDIER_BLASTER_7, MZ2_SOLDIER_BLASTER_8};
static int shotgun_flash [] = {MZ2_SOLDIER_SHOTGUN_1, MZ2_SOLDIER_SHOTGUN_2, MZ2_SOLDIER_SHOTGUN_3, MZ2_SOLDIER_SHOTGUN_4, MZ2_SOLDIER_SHOTGUN_5, MZ2_SOLDIER_SHOTGUN_6, MZ2_SOLDIER_SHOTGUN_7, MZ2_SOLDIER_SHOTGUN_8};
static int machinegun_flash [] = {MZ2_SOLDIER_MACHINEGUN_1, MZ2_SOLDIER_MACHINEGUN_2, MZ2_SOLDIER_MACHINEGUN_3, MZ2_SOLDIER_MACHINEGUN_4, MZ2_SOLDIER_MACHINEGUN_5, MZ2_SOLDIER_MACHINEGUN_6, MZ2_SOLDIER_MACHINEGUN_7, MZ2_SOLDIER_MACHINEGUN_8};

void soldier_fire (edict_t *self, int flash_number)
{
	vec3_t	start;
	vec3_t	forward, right, up;
	vec3_t	aim;
	vec3_t	dir;
	vec3_t	end;
	float	r, u;
	int		flash_index;

	if (self->s.skinnum < 2)
		flash_index = blaster_flash[flash_number];
	else if (self->s.skinnum < 4)
		flash_index = shotgun_flash[flash_number];
	else
		flash_index = machinegun_flash[flash_number];

	AngleVectors (self->s.angles, forward, right, NULL);
	G_ProjectSource (self->s.origin, monster_flash_offset[flash_index], forward, right, start);

	if (flash_number == 5 || flash_number == 6)
	{
		VectorCopy (forward, aim);
	}
	else
	{
		VectorCopy (self->enemy->s.origin, end);
		end[2] += self->enemy->viewheight;
		VectorSubtract (end, start, aim);
		vectoangles (aim, dir);
		AngleVectors (dir, forward, right, up);

		r = crandom()*1000;
		u = crandom()*500;
		VectorMA (start, 8192, forward, end);
		VectorMA (end, r, right, end);
		VectorMA (end, u, up, end);

		VectorSubtract (end, start, aim);
		VectorNormalize (aim);
	}

	if (self->s.skinnum <= 1)
	{
		monster_fire_blaster (self, start, aim, 5, 600, flash_index, EF_BLASTER);
	}
	else if (self->s.skinnum <= 3)
	{
		monster_fire_shotgun (self, start, aim, 2, 1, DEFAULT_SHOTGUN_HSPREAD, DEFAULT_SHOTGUN_VSPREAD, DEFAULT_SHOTGUN_COUNT, flash_index, MOD_M3);
	}
	else
	{
		if (!(self->monsterinfo.aiflags & AI_HOLD_FRAME))
			self->monsterinfo.pausetime = level.time + (3 + rand() % 8) * FRAMETIME;

		monster_fire_bullet (self, start, aim, 2, 4, DEFAULT_BULLET_HSPREAD, DEFAULT_BULLET_VSPREAD, flash_index, MOD_UNKNOWN);

		if (level.time >= self->monsterinfo.pausetime)
			self->monsterinfo.aiflags &= ~AI_HOLD_FRAME;
		else
			self->monsterinfo.aiflags |= AI_HOLD_FRAME;
	}
}

// ATTACK1 (blaster/shotgun)

void soldier_fire1 (edict_t *self)
{
	soldier_fire (self, 0);
}

void soldier_attack1_refire1 (edict_t *self)
{
	if (self->s.skinnum > 1)
		return;

	if (self->enemy->health <= 0)
		return;

	if ( ((skill->value == 3) && (random() < 0.5)) || (range(self, self->enemy) == RANGE_MELEE) )
		self->monsterinfo.nextframe = FRAME_attak102;
	else
		self->monsterinfo.nextframe = FRAME_attak110;
}

void soldier_attack1_refire2 (edict_t *self)
{
	if (self->s.skinnum < 2)
		return;

	if (self->enemy->health <= 0)
		return;

	if ( ((skill->value == 3) && (random() < 0.5)) || (range(self, self->enemy) == RANGE_MELEE) )
		self->monsterinfo.nextframe = FRAME_attak102;
}

mframe_t soldier_frames_attack1 [] =
{
	ai_charge, 0,  NULL,
	ai_charge, 0,  NULL,
	ai_charge, 0,  soldier_fire1,
	ai_charge, 0,  NULL,
	ai_charge, 0,  NULL,
	ai_charge, 0,  soldier_attack1_refire1,
	ai_charge, 0,  NULL,
	ai_charge, 0,  soldier_cock,
	ai_charge, 0,  soldier_attack1_refire2,
	ai_charge, 0,  NULL,
	ai_charge, 0,  NULL,
	ai_charge, 0,  NULL
};
mmove_t soldier_move_attack1 = {FRAME_attak101, FRAME_attak112, soldier_frames_attack1, soldier_run};

// ATTACK2 (blaster/shotgun)

void soldier_fire2 (edict_t *self)
{
	soldier_fire (self, 1);
}

void soldier_attack2_refire1 (edict_t *self)
{
	if (self->s.skinnum > 1)
		return;

	if (self->enemy->health <= 0)
		return;

	if ( ((skill->value == 3) && (random() < 0.5)) || (range(self, self->enemy) == RANGE_MELEE) )
		self->monsterinfo.nextframe = FRAME_attak204;
	else
		self->monsterinfo.nextframe = FRAME_attak216;
}

void soldier_attack2_refire2 (edict_t *self)
{
	if (self->s.skinnum < 2)
		return;

	if (self->enemy->health <= 0)
		return;

	if ( ((skill->value == 3) && (random() < 0.5)) || (range(self, self->enemy) == RANGE_MELEE) )
		self->monsterinfo.nextframe = FRAME_attak204;
}

mframe_t soldier_frames_attack2 [] =
{
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, soldier_fire2,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, soldier_attack2_refire1,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, soldier_cock,
	ai_charge, 0, NULL,
	ai_charge, 0, soldier_attack2_refire2,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL
};
mmove_t soldier_move_attack2 = {FRAME_attak201, FRAME_attak218, soldier_frames_attack2, soldier_run};

// ATTACK3 (duck and shoot)

void soldier_duck_down (edict_t *self)
{
	if (self->monsterinfo.aiflags & AI_DUCKED)
		return;
	self->monsterinfo.aiflags |= AI_DUCKED;
	self->maxs[2] -= 32;
	self->takedamage = DAMAGE_YES;
	self->monsterinfo.pausetime = level.time + 1;
	gi.linkentity (self);
}

void soldier_duck_up (edict_t *self)
{
	self->monsterinfo.aiflags &= ~AI_DUCKED;
	self->maxs[2] += 32;
	self->takedamage = DAMAGE_AIM;
	gi.linkentity (self);
}

void soldier_fire3 (edict_t *self)
{
	soldier_duck_down (self);
	soldier_fire (self, 2);
}

void soldier_attack3_refire (edict_t *self)
{
	if ((level.time + 0.4) < self->monsterinfo.pausetime)
		self->monsterinfo.nextframe = FRAME_attak303;
}

mframe_t soldier_frames_attack3 [] =
{
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, soldier_fire3,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, soldier_attack3_refire,
	ai_charge, 0, soldier_duck_up,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL
};
mmove_t soldier_move_attack3 = {FRAME_attak301, FRAME_attak309, soldier_frames_attack3, soldier_run};

// ATTACK4 (machinegun)

void soldier_fire4 (edict_t *self)
{
	soldier_fire (self, 3);
//
//	if (self->enemy->health <= 0)
//		return;
//
//	if ( ((skill->value == 3) && (random() < 0.5)) || (range(self, self->enemy) == RANGE_MELEE) )
//		self->monsterinfo.nextframe = FRAME_attak402;
}

mframe_t soldier_frames_attack4 [] =
{
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, soldier_fire4,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL
};
mmove_t soldier_move_attack4 = {FRAME_attak401, FRAME_attak406, soldier_frames_attack4, soldier_run};

#if 0
// ATTACK5 (prone)

void soldier_fire5 (edict_t *self)
{
	soldier_fire (self, 4);
}

void soldier_attack5_refire (edict_t *self)
{
	if (self->enemy->health <= 0)
		return;

	if ( ((skill->value == 3) && (random() < 0.5)) || (range(self, self->enemy) == RANGE_MELEE) )
		self->monsterinfo.nextframe = FRAME_attak505;
}

mframe_t soldier_frames_attack5 [] =
{
	ai_charge, 8, NULL,
	ai_charge, 8, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, soldier_fire5,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, soldier_attack5_refire
};
mmove_t soldier_move_attack5 = {FRAME_attak501, FRAME_attak508, soldier_frames_attack5, soldier_run};
#endif

// ATTACK6 (run & shoot)

void soldier_fire8 (edict_t *self)
{
	soldier_fire (self, 7);
}

void soldier_attack6_refire (edict_t *self)
{
	if (self->enemy->health <= 0)
		return;

	if (range(self, self->enemy) < RANGE_MID)
		return;

	if (skill->value == 3)
		self->monsterinfo.nextframe = FRAME_runs03;
}

mframe_t soldier_frames_attack6 [] =
{
	ai_charge, 10, NULL,
	ai_charge,  4, NULL,
	ai_charge, 12, NULL,
	ai_charge, 11, soldier_fire8,
	ai_charge, 13, NULL,
	ai_charge, 18, NULL,
	ai_charge, 15, NULL,
	ai_charge, 14, NULL,
	ai_charge, 11, NULL,
	ai_charge,  8, NULL,
	ai_charge, 11, NULL,
	ai_charge, 12, NULL,
	ai_charge, 12, NULL,
	ai_charge, 17, soldier_attack6_refire
};
mmove_t soldier_move_attack6 = {FRAME_runs01, FRAME_runs14, soldier_frames_attack6, soldier_run};

void soldier_attack(edict_t *self)
{
	if (self->s.skinnum < 4)
	{
		if (random() < 0.5)
			self->monsterinfo.currentmove = &soldier_move_attack1;
		else
			self->monsterinfo.currentmove = &soldier_move_attack2;
	}
	else
	{
		self->monsterinfo.currentmove = &soldier_move_attack4;
	}
}


//
// SIGHT
//

void soldier_sight(edict_t *self, edict_t *other)
{
	if (random() < 0.5)
		gi.sound (self, CHAN_VOICE, sound_sight1, 1, ATTN_NORM, 0);
	else
		gi.sound (self, CHAN_VOICE, sound_sight2, 1, ATTN_NORM, 0);

	if ((skill->value > 0) && (range(self, self->enemy) >= RANGE_MID))
	{
		if (random() > 0.5)
			self->monsterinfo.currentmove = &soldier_move_attack6;
	}
}

//
// DUCK
//

void soldier_duck_hold (edict_t *self)
{
	if (level.time >= self->monsterinfo.pausetime)
		self->monsterinfo.aiflags &= ~AI_HOLD_FRAME;
	else
		self->monsterinfo.aiflags |= AI_HOLD_FRAME;
}

mframe_t soldier_frames_duck [] =
{
	ai_move, 5, soldier_duck_down,
	ai_move, -1, soldier_duck_hold,
	ai_move, 1,  NULL,
	ai_move, 0,  soldier_duck_up,
	ai_move, 5,  NULL
};
mmove_t soldier_move_duck = {FRAME_duck01, FRAME_duck05, soldier_frames_duck, soldier_run};

void soldier_dodge (edict_t *self, edict_t *attacker, float eta)
{
	float	r;

	r = random();
	if (r > 0.25)
		return;

	if (!self->enemy)
		self->enemy = attacker;

	if (skill->value == 0)
	{
		self->monsterinfo.currentmove = &soldier_move_duck;
		return;
	}

	self->monsterinfo.pausetime = level.time + eta + 0.3;
	r = random();

	if (skill->value == 1)
	{
		if (r > 0.33)
			self->monsterinfo.currentmove = &soldier_move_duck;
		else
			self->monsterinfo.currentmove = &soldier_move_attack3;
		return;
	}

	if (skill->value >= 2)
	{
		if (r > 0.66)
			self->monsterinfo.currentmove = &soldier_move_duck;
		else
			self->monsterinfo.currentmove = &soldier_move_attack3;
		return;
	}

	self->monsterinfo.currentmove = &soldier_move_attack3;
}


//
// DEATH
//

void soldier_fire6 (edict_t *self)
{
	soldier_fire (self, 5);
}

void soldier_fire7 (edict_t *self)
{
	soldier_fire (self, 6);
}

void soldier_dead (edict_t *self)
{
	VectorSet (self->mins, -16, -16, -24);
	VectorSet (self->maxs, 16, 16, -8);
	self->movetype = MOVETYPE_TOSS;
	self->svflags |= SVF_DEADMONSTER;
	self->nextthink = 0;
	gi.linkentity (self);
}

mframe_t soldier_frames_death1 [] =
{
	ai_move, 0,   NULL,
	ai_move, -10, NULL,
	ai_move, -10, NULL,
	ai_move, -10, NULL,
	ai_move, -5,  NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   soldier_fire6,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   soldier_fire7,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL
};
mmove_t soldier_move_death1 = {FRAME_death101, FRAME_death136, soldier_frames_death1, soldier_dead};

mframe_t soldier_frames_death2 [] =
{
	ai_move, -5,  NULL,
	ai_move, -5,  NULL,
	ai_move, -5,  NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL
};
mmove_t soldier_move_death2 = {FRAME_death201, FRAME_death235, soldier_frames_death2, soldier_dead};

mframe_t soldier_frames_death3 [] =
{
	ai_move, -5,  NULL,
	ai_move, -5,  NULL,
	ai_move, -5,  NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
};
mmove_t soldier_move_death3 = {FRAME_death301, FRAME_death345, soldier_frames_death3, soldier_dead};

mframe_t soldier_frames_death4 [] =
{
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL
};
mmove_t soldier_move_death4 = {FRAME_death401, FRAME_death453, soldier_frames_death4, soldier_dead};

mframe_t soldier_frames_death5 [] =
{
	ai_move, -5,  NULL,
	ai_move, -5,  NULL,
	ai_move, -5,  NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,

	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL
};
mmove_t soldier_move_death5 = {FRAME_death501, FRAME_death524, soldier_frames_death5, soldier_dead};

mframe_t soldier_frames_death6 [] =
{
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL,
	ai_move, 0,   NULL
};
mmove_t soldier_move_death6 = {FRAME_death601, FRAME_death610, soldier_frames_death6, soldier_dead};

void soldier_die (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point)
{
	int		n;

// check for gib
	if (self->health <= self->gib_health)
	{
		gi.sound (self, CHAN_VOICE, gi.soundindex ("misc/udeath.wav"), 1, ATTN_NORM, 0);
		for (n= 0; n < 3; n++)
			ThrowGib (self, "models/objects/gibs/sm_meat/tris.md2", damage, GIB_ORGANIC);
		ThrowGib (self, "models/objects/gibs/chest/tris.md2", damage, GIB_ORGANIC);
		ThrowHead (self, "models/objects/gibs/head2/tris.md2", damage, GIB_ORGANIC);
		self->deadflag = DEAD_DEAD;
		return;
	}

	if (self->deadflag == DEAD_DEAD)
		return;

// regular death
	self->deadflag = DEAD_DEAD;
	self->takedamage = DAMAGE_YES;
	self->s.skinnum |= 1;

	if (self->s.skinnum == 1)
		gi.sound (self, CHAN_VOICE, sound_death_light, 1, ATTN_NORM, 0);
	else if (self->s.skinnum == 3)
		gi.sound (self, CHAN_VOICE, sound_death, 1, ATTN_NORM, 0);
	else // (self->s.skinnum == 5)
		gi.sound (self, CHAN_VOICE, sound_death_ss, 1, ATTN_NORM, 0);

	if (fabs((self->s.origin[2] + self->viewheight) - point[2]) <= 4)
	{
		// head shot
		self->monsterinfo.currentmove = &soldier_move_death3;
		return;
	}

	n = rand() % 5;
	if (n == 0)
		self->monsterinfo.currentmove = &soldier_move_death1;
	else if (n == 1)
		self->monsterinfo.currentmove = &soldier_move_death2;
	else if (n == 2)
		self->monsterinfo.currentmove = &soldier_move_death4;
	else if (n == 3)
		self->monsterinfo.currentmove = &soldier_move_death5;
	else
		self->monsterinfo.currentmove = &soldier_move_death6;
}


//
// SPAWN
//

void SP_monster_soldier_x (edict_t *self)
{
	self->monsterinfo.scale = MODEL_SCALE;
	VectorSet (self->mins, -16, -16, -24);
	VectorSet (self->maxs, 16, 16, 32);
	self->movetype = MOVETYPE_STEP;
	self->solid = SOLID_BBOX;

	sound_idle =	gi.soundindex ("soldier/solidle1.wav");
	sound_sight1 =	gi.soundindex ("soldier/solsght1.wav");
	sound_sight2 =	gi.soundindex ("soldier/solsrch1.wav");
	sound_cock =	gi.soundindex ("infantry/infatck3.wav");

	self->mass = 100;

	self->pain = soldier_pain;
	self->die = soldier_die;

	self->monsterinfo.stand = soldier_stand;
	self->monsterinfo.walk = soldier_walk;
	self->monsterinfo.run = soldier_run;
	self->monsterinfo.dodge = soldier_dodge;
	self->monsterinfo.attack = soldier_attack;
	self->monsterinfo.melee = NULL;
	self->monsterinfo.sight = soldier_sight;

	gi.linkentity (self);

	self->monsterinfo.stand (self);

	walkmonster_start (self);
}

void SoldierM4 (edict_t *self);
void mksoldier_reload (edict_t *self);


mframe_t mksoldier_frames_stand [] =
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
mmove_t mksoldier_move_stand = {0, 39, mksoldier_frames_stand, NULL};

void mksoldier_stand (edict_t *self)
{
	self->monsterinfo.currentmove = &mksoldier_move_stand;
}


mframe_t mksoldier_frames_fidget [] =
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
mmove_t mksoldier_move_fidget = {0, 39, mksoldier_frames_fidget, mksoldier_stand};

void mksoldier_fidget (edict_t *self)
{
	//self->monsterinfo.currentmove = &mksoldier_move_fidget;
	//gi.sound (self, CHAN_VOICE, sound_idle, 1, ATTN_IDLE, 0);
}

mframe_t mksoldier_frames_walk [] =
{
	ai_walk, 11,  NULL,
	ai_walk, 11,  NULL,
	ai_walk, 11,  NULL,
	ai_walk, 11,  NULL,
	ai_walk, 11,  NULL,
	ai_walk, 11,  NULL
};
mmove_t mksoldier_move_walk = {40, 45, mksoldier_frames_walk, NULL};

void mksoldier_walk (edict_t *self)
{
	self->monsterinfo.currentmove = &mksoldier_move_walk;
}

mframe_t mksoldier_frames_run [] =
{
	ai_run, 17, NULL,
	ai_run, 17, NULL,
	ai_run, 17, NULL,
	ai_run, 17, NULL,
	ai_run, 17, NULL,
	ai_run, 17, NULL
};
mmove_t mksoldier_move_run = {40, 45, mksoldier_frames_run, NULL};

void mksoldier_run (edict_t *self)
{
	if (self->monsterinfo.aiflags & AI_STAND_GROUND)
		self->monsterinfo.currentmove = &mksoldier_move_stand;
	else
		self->monsterinfo.currentmove = &mksoldier_move_run;
}


mframe_t mksoldier_frames_pain1 [] =
{
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL
};
mmove_t mksoldier_move_pain1 = {54, 57, mksoldier_frames_pain1, mksoldier_run};

mframe_t mksoldier_frames_pain2 [] =
{
	ai_move, 0, NULL,
	ai_move, 0,  NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL
};
mmove_t mksoldier_move_pain2 = {58, 61, mksoldier_frames_pain2, mksoldier_run};

mframe_t mksoldier_frames_pain3 [] =
{
	ai_move, 0, NULL,
	ai_move, 0,  NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL
};
mmove_t mksoldier_move_pain3 = {62, 65, mksoldier_frames_pain3, mksoldier_run};

void mksoldier_pain (edict_t *self, edict_t *other, float kick, int damage)
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
		self->monsterinfo.currentmove = &mksoldier_move_pain1;
	}
	else if (n == 1)
	{
		self->monsterinfo.currentmove = &mksoldier_move_pain2;
	}
	else
	{
		self->monsterinfo.currentmove = &mksoldier_move_pain3;
	}
}

void mksoldier_mk23out_sound (edict_t *self)
{
	gi.sound (self, CHAN_AUTO, gi.soundindex ("weapons/mk23out.wav"), 1, ATTN_NORM, 0);
}
void mksoldier_mk23in_sound (edict_t *self)
{
	gi.sound (self, CHAN_AUTO, gi.soundindex ("weapons/mk23in.wav"), 1, ATTN_NORM, 0);
}
void mksoldier_mk23slap_sound (edict_t *self)
{
	gi.sound (self, CHAN_AUTO, gi.soundindex ("weapons/mk23slap.wav"), 1, ATTN_NORM, 0);
}

mframe_t mksoldier_frames_reload [] =
{
	ai_run, 0, NULL,
	ai_run, 0, NULL,
	ai_run, 0, NULL,
	ai_run, 0, mksoldier_mk23out_sound,
	ai_run, 0, NULL,
	ai_run, 0, NULL,
	ai_run, 0, NULL,
	ai_run, 0, NULL,
	ai_run, 0, NULL,
	ai_run, 0, mksoldier_mk23in_sound,
	ai_run, 0, NULL,
	ai_run, 0, NULL,
	ai_run, 0, NULL,
	ai_run, 0, NULL,
	ai_run, 0, NULL,
	ai_run, 0, mksoldier_mk23slap_sound,
	ai_run, 0, NULL,
	ai_run, 0, NULL
};
mmove_t mksoldier_move_reload = {0, 17, mksoldier_frames_reload, mksoldier_reload};

void mksoldier_reload (edict_t *self)
{
	self->reloading = 0;
	self->monster_mk23_rounds = 12;
	mksoldier_run(self);
}

void SoldierMk23 (edict_t *self)
{
	vec3_t	start, target;
	vec3_t	forward, right;
//	vec3_t	vec;
	int		flash_number;
	int number = rndnum (1, 5);

	if (self->monster_mk23_rounds < 1) // Paril: No rounds, whoamg.
	{
		self->reloading = 1;
		//mksoldier_run(self);
		return;
	}

	flash_number = MZ2_SOLDIER_BLASTER_1;
	AngleVectors (self->s.angles, forward, right, NULL);
	G_ProjectSource (self->s.origin, monster_flash_offset[flash_number], forward, right, start);
	
	if (self->enemy)
	{
		VectorMA (self->enemy->s.origin, -0.2, self->enemy->velocity, target);
		target[2] += self->enemy->viewheight;
		VectorSubtract (target, start, forward);
		VectorNormalize (forward);
	}
	else
	{
		AngleVectors (self->s.angles, forward, right, NULL);
	}

	monster_fire_bullet (self, start, forward, 75, 100, 140, 140, flash_number, MOD_MK23);
	gi.sound(self, CHAN_AUTO, gi.soundindex("weapons/mk23fire.wav"), 1, ATTN_NORM, 0);

	self->monster_mk23_rounds--;
}

void mksoldier_sight (edict_t *self, edict_t *other)
{
	//gi.sound (self, CHAN_BODY, sound_sight, 1, ATTN_NORM, 0);
}

void mksoldier_dead (edict_t *self)
{
	VectorSet (self->mins, -16, -16, -24);
	VectorSet (self->maxs, 16, 16, -8);
	self->movetype = MOVETYPE_TOSS;
	self->svflags |= SVF_DEADMONSTER;
	gi.linkentity (self);

	M_FlyCheck (self);
}

mframe_t mksoldier_frames_death1 [] =
{
	ai_move, 0, NULL,
	ai_move, 0,  NULL,
	ai_move, 0,  NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0,  NULL
};
mmove_t mksoldier_move_death1 = {178, 183, mksoldier_frames_death1, mksoldier_dead};

// Off with his head
mframe_t mksoldier_frames_death2 [] =
{
	ai_move, 0,   NULL,
	ai_move, 1,   NULL,
	ai_move, 5,   NULL,
	ai_move, -1,  NULL,
	ai_move, 0,   NULL,
	ai_move, 1,   NULL
};
mmove_t mksoldier_move_death2 = {184, 189, mksoldier_frames_death2, mksoldier_dead};

mframe_t mksoldier_frames_death3 [] =
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
mmove_t mksoldier_move_death3 = {190, 197, mksoldier_frames_death3, mksoldier_dead};


void mksoldier_die (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point)
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
		self->monsterinfo.currentmove = &mksoldier_move_death1;
	else if (n == 1)
		self->monsterinfo.currentmove = &mksoldier_move_death2;
	else
		self->monsterinfo.currentmove = &mksoldier_move_death3;
}

void mksoldier_ready_fire (edict_t *self)
{
	gi.dprintf ("Ready.,,\n");
}

void mksoldier_fire (edict_t *self)
{
	SoldierMk23 (self);
}

void mksoldier_refire (edict_t *self);
void mksoldier_attack(edict_t *self);
mframe_t mksoldier_frames_attack1 [] =
{
	ai_charge, 0, mksoldier_ready_fire,
	ai_charge, 0, mksoldier_fire,
	ai_charge, 0, NULL,
	ai_charge, 0, mksoldier_refire,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL
};
mmove_t mksoldier_move_attack1 = {46, 53, mksoldier_frames_attack1, mksoldier_run};

void mksoldier_refire (edict_t *self)
{
	if (random() < 0.7 && (self->monster_mk23_rounds > 0))
		self->s.frame = 46;
}

void mksoldier_attack(edict_t *self)
{
	if (self->monster_mk23_rounds < 1)
	{
		//mksoldier_reload (self);
		self->monsterinfo.currentmove = &mksoldier_move_reload;
		return;
	}
	else
	{
		self->monsterinfo.currentmove = &mksoldier_move_attack1;
	}
}


/*QUAKED SP_monster_soldier_light (1 .5 0) (-16 -16 -24) (16 16 32) Ambush Trigger_Spawn Sight
*/
void SP_monster_soldier_light (edict_t *self)
{
	if (deathmatch->value)
	{
		G_FreeEdict (self);
		return;
	}
	

	self->movetype = MOVETYPE_STEP;
	self->solid = SOLID_BBOX;
	self->s.modelindex = gi.modelindex("models/mksoldier/tris.md2");
	self->s.modelindex2 = gi.modelindex("models/mksoldier/w_mk23.md2");
	VectorSet (self->mins, -16, -16, -24);
	VectorSet (self->maxs, 16, 16, 32);

	self->health = 65;
	self->gib_health = -40;
	self->mass = 125;

	self->monster_mk23_rounds = 12;
	self->reloading = 0;

	self->pain = mksoldier_pain;
	self->die = mksoldier_die;

	self->weap_num = 0;

	self->monsterinfo.stand = mksoldier_stand;
	self->monsterinfo.walk = mksoldier_walk;
	self->monsterinfo.run = mksoldier_run;
	self->monsterinfo.dodge = /*mksoldier_dodge*/NULL;
	self->monsterinfo.attack = mksoldier_attack;
	self->monsterinfo.melee = NULL;
	self->monsterinfo.sight = mksoldier_sight;
	self->monsterinfo.idle = mksoldier_fidget;

	gi.linkentity (self);

	self->monsterinfo.currentmove = &mksoldier_move_stand;
	self->monsterinfo.scale = MODEL_SCALE;

	walkmonster_start (self);
}
/*void SP_monster_soldier_light (edict_t *self)
{
	if (deathmatch->value)
	{
		G_FreeEdict (self);
		return;
	}
	self->s.modelindex = gi.modelindex ("models/monsters/soldier/tris.md2");
	self->s.skinnum = 0;
	self->health = 20;
	self->gib_health = -30;
	SP_monster_soldier_x (self);

	sound_pain_light = gi.soundindex ("soldier/solpain2.wav");
	sound_death_light =	gi.soundindex ("soldier/soldeth2.wav");
	gi.modelindex ("models/objects/laser/tris.md2");
	gi.soundindex ("misc/lasfly.wav");
	gi.soundindex ("soldier/solatck2.wav");
}*/
void ShotgunnerShotgun (edict_t *self);
void shotgunner_reload (edict_t *self);


mframe_t shotgunner_frames_stand [] =
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
mmove_t shotgunner_move_stand = {0, 39, shotgunner_frames_stand, NULL};

void shotgunner_stand (edict_t *self)
{
	self->monsterinfo.currentmove = &shotgunner_move_stand;
}


mframe_t shotgunner_frames_fidget [] =
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
mmove_t shotgunner_move_fidget = {0, 39, shotgunner_frames_fidget, shotgunner_stand};

void shotgunner_fidget (edict_t *self)
{
	self->monsterinfo.currentmove = &shotgunner_move_fidget;
	//gi.sound (self, CHAN_VOICE, sound_idle, 1, ATTN_IDLE, 0);
}

mframe_t shotgunner_frames_walk [] =
{
	ai_walk, 11,  NULL,
	ai_walk, 11,  NULL,
	ai_walk, 11,  NULL,
	ai_walk, 11,  NULL,
	ai_walk, 11,  NULL,
	ai_walk, 11,  NULL
};
mmove_t shotgunner_move_walk = {40, 45, shotgunner_frames_walk, NULL};

void shotgunner_walk (edict_t *self)
{
	self->monsterinfo.currentmove = &shotgunner_move_walk;
}

mframe_t shotgunner_frames_run [] =
{
	ai_run, 17, NULL,
	ai_run, 17, NULL,
	ai_run, 17, NULL,
	ai_run, 17, NULL,
	ai_run, 17, NULL,
	ai_run, 17, NULL
};
mmove_t shotgunner_move_run = {40, 45, shotgunner_frames_run, NULL};

void shotgunner_run (edict_t *self)
{
	if (self->monsterinfo.aiflags & AI_STAND_GROUND)
		self->monsterinfo.currentmove = &shotgunner_move_stand;
	else
		self->monsterinfo.currentmove = &shotgunner_move_run;
}


mframe_t shotgunner_frames_pain1 [] =
{
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL
};
mmove_t shotgunner_move_pain1 = {54, 57, shotgunner_frames_pain1, shotgunner_run};

mframe_t shotgunner_frames_pain2 [] =
{
	ai_move, 0, NULL,
	ai_move, 0,  NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL
};
mmove_t shotgunner_move_pain2 = {58, 61, shotgunner_frames_pain2, shotgunner_run};

mframe_t shotgunner_frames_pain3 [] =
{
	ai_move, 0, NULL,
	ai_move, 0,  NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL
};
mmove_t shotgunner_move_pain3 = {62, 65, shotgunner_frames_pain3, shotgunner_run};

void shotgunner_pain (edict_t *self, edict_t *other, float kick, int damage)
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
		self->monsterinfo.currentmove = &shotgunner_move_pain1;
	}
	else if (n == 1)
	{
		self->monsterinfo.currentmove = &shotgunner_move_pain2;
	}
	else
	{
		self->monsterinfo.currentmove = &shotgunner_move_pain3;
	}
}

void shotgunner_in (edict_t *self)
{
	gi.sound(self, CHAN_AUTO, gi.soundindex("weapons/m3in.wav"), 1, ATTN_NORM, 0);
}

mframe_t shotgunner_frames_reload [] =
{
	ai_run, 0, NULL,
	ai_run, 0, NULL,
	ai_run, 0, shotgunner_in,
	ai_run, 0, NULL,
	ai_run, 0, NULL,
	ai_run, 0, NULL,
	ai_run, 0, shotgunner_in,
	ai_run, 0, NULL,
	ai_run, 0, NULL,
	ai_run, 0, NULL,
	ai_run, 0, shotgunner_in,
	ai_run, 0, NULL,
	ai_run, 0, NULL,
	ai_run, 0, NULL,
	ai_run, 0, shotgunner_in,
	ai_run, 0, NULL,
	ai_run, 0, NULL,
	ai_run, 0, NULL,
	ai_run, 0, shotgunner_in,
	ai_run, 0, NULL,
	ai_run, 0, NULL,
	ai_run, 0, NULL,
	ai_run, 0, shotgunner_in,
	ai_run, 0, NULL,
	ai_run, 0, NULL,
	ai_run, 0, NULL,
	ai_run, 0, shotgunner_in
};
mmove_t shotgunner_move_reload = {0, 26, shotgunner_frames_reload, shotgunner_reload};

void shotgunner_reload (edict_t *self)
{
	self->reloading = 0;
	self->monster_shotgun_rounds = 7;
	shotgunner_run(self);
}

void ShotgunnerShotgun (edict_t *self)
{
	vec3_t	start, target;
	vec3_t	forward, right;
//	vec3_t	vec;
	int		flash_number;
	int number = rndnum (1, 5);
    int damage = 17; //actionquake is 15 standard
    int kick = 20;

	if (self->monster_shotgun_rounds < 1) // Paril: No rounds, whoamg.
	{
		self->reloading = 1;
		//shotgunner_run(self);
		self->monsterinfo.aiflags &= ~AI_HOLD_FRAME; // End firing sequence!
		return;
	}

	flash_number = MZ2_SOLDIER_BLASTER_1;
	AngleVectors (self->s.angles, forward, right, NULL);
	G_ProjectSource (self->s.origin, monster_flash_offset[flash_number], forward, right, start);
	
	if (self->enemy)
	{
		VectorMA (self->enemy->s.origin, -0.2, self->enemy->velocity, target);
		target[2] += self->enemy->viewheight;
		VectorSubtract (target, start, forward);
		VectorNormalize (forward);
	}
	else
	{
		AngleVectors (self->s.angles, forward, right, NULL);
	}

	//monster_fire_bullet (self, start, forward, 200, 150, 0, 0, flash_number);
	monster_fire_shotgun (self, start, forward, damage, kick, 800, 800, 12, flash_number, MOD_M3);
	gi.sound(self, CHAN_AUTO, gi.soundindex("weapons/shotgf1b.wav"), 1, ATTN_NORM, 0);

	self->monster_shotgun_rounds--;
}

void shotgunner_sight (edict_t *self, edict_t *other)
{
	//gi.sound (self, CHAN_BODY, sound_sight, 1, ATTN_NORM, 0);
}

void shotgunner_dead (edict_t *self)
{
	VectorSet (self->mins, -16, -16, -24);
	VectorSet (self->maxs, 16, 16, -8);
	self->movetype = MOVETYPE_TOSS;
	self->svflags |= SVF_DEADMONSTER;
	gi.linkentity (self);

	M_FlyCheck (self);
}

mframe_t shotgunner_frames_death1 [] =
{
	ai_move, 0, NULL,
	ai_move, 0,  NULL,
	ai_move, 0,  NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0,  NULL
};
mmove_t shotgunner_move_death1 = {178, 183, shotgunner_frames_death1, shotgunner_dead};

// Off with his head
mframe_t shotgunner_frames_death2 [] =
{
	ai_move, 0,   NULL,
	ai_move, 1,   NULL,
	ai_move, 5,   NULL,
	ai_move, -1,  NULL,
	ai_move, 0,   NULL,
	ai_move, 1,   NULL
};
mmove_t shotgunner_move_death2 = {184, 189, shotgunner_frames_death2, shotgunner_dead};

mframe_t shotgunner_frames_death3 [] =
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
mmove_t shotgunner_move_death3 = {190, 197, shotgunner_frames_death3, shotgunner_dead};


void shotgunner_die (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point)
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
		self->monsterinfo.currentmove = &shotgunner_move_death1;
	else if (n == 1)
		self->monsterinfo.currentmove = &shotgunner_move_death2;
	else
		self->monsterinfo.currentmove = &shotgunner_move_death3;
}

void shotgunner_ready_fire (edict_t *self)
{
	gi.dprintf ("Ready.,,\n");
}

void shotgunner_fire (edict_t *self)
{
	ShotgunnerShotgun (self);
}

mframe_t shotgunner_frames_attack1 [] =
{
	ai_charge, 0, shotgunner_ready_fire,
	ai_charge, 0, shotgunner_fire,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL
};
mmove_t shotgunner_move_attack1 = {46, 53, shotgunner_frames_attack1, shotgunner_run};


/*void shotgunner_swing (edict_t *self)
{
	gi.sound (self, CHAN_WEAPON, sound_punch_swing, 1, ATTN_NORM, 0);
}

void shotgunner_smack (edict_t *self)
{
	vec3_t	aim;

	VectorSet (aim, MELEE_DISTANCE, 0, 0);
	if (fire_hit (self, aim, (5 + (rand() % 5)), 50))
		gi.sound (self, CHAN_WEAPON, sound_punch_hit, 1, ATTN_NORM, 0);
}

mframe_t shotgunner_frames_attack2 [] =
{
	ai_charge, 3, NULL,
	ai_charge, 6, NULL,
	ai_charge, 0, shotgunner_swing,
	ai_charge, 8, NULL,
	ai_charge, 5, NULL,
	ai_charge, 8, shotgunner_smack,
	ai_charge, 6, NULL,
	ai_charge, 3, NULL,
};
mmove_t shotgunner_move_attack2 = {FRAME_attak201, FRAME_attak208, shotgunner_frames_attack2, shotgunner_run};*/

void shotgunner_attack(edict_t *self)
{
	/*if (range (self, self->enemy) == RANGE_MELEE) // Knife
	{
		if (self->weap_num == 0) // Still using Mp5
		{
			self->weap_num = 1;
			self->monsterinfo.currentmove = &shotgunner_changeweapons;
			return;
		}
		else
		{
			self->monsterinfo.currentmove = &shotgunner_move_attack1;
		}
	}
	else
	{*/
		/*if (self->weap_num == 1) // Still using knife
		{
			self->weap_num = 0;
			self->monsterinfo.currentmove = &shotgunner_changeweapons;
			return;
		}
		else
		{*/
			if (self->monster_shotgun_rounds < 1)
			{
				//shotgunner_reload (self);
				self->monsterinfo.currentmove = &shotgunner_move_reload;
				return;
			}
			else
			{
				self->monsterinfo.currentmove = &shotgunner_move_attack1;
			}
	//	}
//	}
}


/*QUAKED monster_soldier (1 .5 0) (-16 -16 -24) (16 16 32) Ambush Trigger_Spawn Sight
*/
void SP_monster_soldier (edict_t *self)
{
	if (deathmatch->value)
	{
		G_FreeEdict (self);
		return;
	}

	self->movetype = MOVETYPE_STEP;
	self->solid = SOLID_BBOX;
	self->s.modelindex = gi.modelindex("models/shotgun/tris.md2");
	self->s.modelindex2 = gi.modelindex("models/shotgun/w_super90.md2");
	VectorSet (self->mins, -16, -16, -24);
	VectorSet (self->maxs, 16, 16, 32);

	self->health = 184;
	self->gib_health = -40;
	self->mass = 125;

	self->monster_shotgun_rounds = 7;
	self->reloading = 0;

	self->pain = shotgunner_pain;
	self->die = shotgunner_die;

	self->weap_num = 0;

	self->monsterinfo.stand = shotgunner_stand;
	self->monsterinfo.walk = shotgunner_walk;
	self->monsterinfo.run = shotgunner_run;
	self->monsterinfo.dodge = /*shotgunner_dodge*/NULL;
	self->monsterinfo.attack = shotgunner_attack;
	self->monsterinfo.melee = NULL;
	self->monsterinfo.sight = shotgunner_sight;
	self->monsterinfo.idle = shotgunner_fidget;

	gi.linkentity (self);

	self->monsterinfo.currentmove = &shotgunner_move_stand;
	self->monsterinfo.scale = MODEL_SCALE;

	walkmonster_start (self);
}


/*QUAKED monster_soldier_ss (1 .5 0) (-16 -16 -24) (16 16 32) Ambush Trigger_Spawn Sight
*/
/*void SP_monster_soldier_ss (edict_t *self)
{
	if (deathmatch->value)
	{
		G_FreeEdict (self);
		return;
	}
	self->s.modelindex = gi.modelindex ("models/monsters/soldier/tris.md2");
	self->s.skinnum = 4;
	self->health = 40;
	self->gib_health = -30;
	SP_monster_soldier_x (self);

	sound_pain_ss = gi.soundindex ("soldier/solpain3.wav");
	sound_death_ss = gi.soundindex ("soldier/soldeth3.wav");
	gi.soundindex ("soldier/solatck3.wav");
}*/

void SoldierM4 (edict_t *self);
void dmksoldier_reload (edict_t *self);


mframe_t dmksoldier_frames_stand [] =
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
mmove_t dmksoldier_move_stand = {0, 39, dmksoldier_frames_stand, NULL};

void dmksoldier_stand (edict_t *self)
{
	self->monsterinfo.currentmove = &dmksoldier_move_stand;
}


mframe_t dmksoldier_frames_fidget [] =
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
mmove_t dmksoldier_move_fidget = {0, 39, dmksoldier_frames_fidget, dmksoldier_stand};

void dmksoldier_fidget (edict_t *self)
{
	//self->monsterinfo.currentmove = &dmksoldier_move_fidget;
	//gi.sound (self, CHAN_VOICE, sound_idle, 1, ATTN_IDLE, 0);
}

mframe_t dmksoldier_frames_walk [] =
{
	ai_walk, 11,  NULL,
	ai_walk, 11,  NULL,
	ai_walk, 11,  NULL,
	ai_walk, 11,  NULL,
	ai_walk, 11,  NULL,
	ai_walk, 11,  NULL
};
mmove_t dmksoldier_move_walk = {40, 45, dmksoldier_frames_walk, NULL};

void dmksoldier_walk (edict_t *self)
{
	self->monsterinfo.currentmove = &dmksoldier_move_walk;
}

mframe_t dmksoldier_frames_run [] =
{
	ai_run, 17, NULL,
	ai_run, 17, NULL,
	ai_run, 17, NULL,
	ai_run, 17, NULL,
	ai_run, 17, NULL,
	ai_run, 17, NULL
};
mmove_t dmksoldier_move_run = {40, 45, dmksoldier_frames_run, NULL};

void dmksoldier_run (edict_t *self)
{
	if (self->monsterinfo.aiflags & AI_STAND_GROUND)
		self->monsterinfo.currentmove = &dmksoldier_move_stand;
	else
		self->monsterinfo.currentmove = &dmksoldier_move_run;
}


mframe_t dmksoldier_frames_pain1 [] =
{
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL
};
mmove_t dmksoldier_move_pain1 = {54, 57, dmksoldier_frames_pain1, dmksoldier_run};

mframe_t dmksoldier_frames_pain2 [] =
{
	ai_move, 0, NULL,
	ai_move, 0,  NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL
};
mmove_t dmksoldier_move_pain2 = {58, 61, dmksoldier_frames_pain2, dmksoldier_run};

mframe_t dmksoldier_frames_pain3 [] =
{
	ai_move, 0, NULL,
	ai_move, 0,  NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL
};
mmove_t dmksoldier_move_pain3 = {62, 65, dmksoldier_frames_pain3, dmksoldier_run};

void dmksoldier_pain (edict_t *self, edict_t *other, float kick, int damage)
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
		self->monsterinfo.currentmove = &dmksoldier_move_pain1;
	}
	else if (n == 1)
	{
		self->monsterinfo.currentmove = &dmksoldier_move_pain2;
	}
	else
	{
		self->monsterinfo.currentmove = &dmksoldier_move_pain3;
	}
}

void dmksoldier_mk23out_sound (edict_t *self)
{
	gi.sound (self, CHAN_AUTO, gi.soundindex ("weapons/mk23out.wav"), 1, ATTN_NORM, 0);
}
void dmksoldier_mk23slap_sound (edict_t *self)
{
	gi.sound (self, CHAN_AUTO, gi.soundindex ("weapons/mk23slap.wav"), 1, ATTN_NORM, 0);
}

mframe_t dmksoldier_frames_reload [] =
{
	ai_run, 0, NULL,
	ai_run, 0, NULL,
	ai_run, 0, NULL,
	ai_run, 0, dmksoldier_mk23out_sound,
	ai_run, 0, NULL,
	ai_run, 0, NULL,
	ai_run, 0, NULL,
	ai_run, 0, NULL,
	ai_run, 0, NULL,
	ai_run, 0, dmksoldier_mk23slap_sound,
	ai_run, 0, NULL,
	ai_run, 0, NULL,
	ai_run, 0, NULL,
	ai_run, 0, NULL,
	ai_run, 0, dmksoldier_mk23slap_sound,
	ai_run, 0, NULL,
	ai_run, 0, NULL,
	ai_run, 0, NULL
};
mmove_t dmksoldier_move_reload = {0, 17, dmksoldier_frames_reload, dmksoldier_reload};

void dmksoldier_reload (edict_t *self)
{
	self->reloading = 0;
	self->monster_mk23_rounds = 24;
	dmksoldier_run(self);
}

void SoldierDMk23 (edict_t *self)
{
	vec3_t	start, target;
	vec3_t	forward, right;
//	vec3_t	vec;
	int		flash_number;
	int number = rndnum (1, 5);

	if (self->monster_mk23_rounds < 1) // Paril: No rounds, whoamg.
	{
		self->reloading = 1;
		//dmksoldier_run(self);
		return;
	}

	flash_number = MZ2_SOLDIER_BLASTER_1;
	AngleVectors (self->s.angles, forward, right, NULL);
	G_ProjectSource (self->s.origin, monster_flash_offset[flash_number], forward, right, start);
	
	if (self->enemy)
	{
		VectorMA (self->enemy->s.origin, -0.2, self->enemy->velocity, target);
		target[2] += self->enemy->viewheight;
		VectorSubtract (target, start, forward);
		VectorNormalize (forward);
	}
	else
	{
		AngleVectors (self->s.angles, forward, right, NULL);
	}

	monster_fire_bullet (self, start, forward, 50, 80, 200, 200, flash_number, MOD_DUAL);
	gi.sound(self, CHAN_AUTO, gi.soundindex("weapons/mk23fire.wav"), 1, ATTN_NORM, 0);

	self->monster_mk23_rounds--;
}

void dmksoldier_sight (edict_t *self, edict_t *other)
{
	//gi.sound (self, CHAN_BODY, sound_sight, 1, ATTN_NORM, 0);
}

void dmksoldier_dead (edict_t *self)
{
	VectorSet (self->mins, -16, -16, -24);
	VectorSet (self->maxs, 16, 16, -8);
	self->movetype = MOVETYPE_TOSS;
	self->svflags |= SVF_DEADMONSTER;
	gi.linkentity (self);

	M_FlyCheck (self);
}

mframe_t dmksoldier_frames_death1 [] =
{
	ai_move, 0, NULL,
	ai_move, 0,  NULL,
	ai_move, 0,  NULL,
	ai_move, 0, NULL,
	ai_move, 0, NULL,
	ai_move, 0,  NULL
};
mmove_t dmksoldier_move_death1 = {178, 183, dmksoldier_frames_death1, dmksoldier_dead};

// Off with his head
mframe_t dmksoldier_frames_death2 [] =
{
	ai_move, 0,   NULL,
	ai_move, 1,   NULL,
	ai_move, 5,   NULL,
	ai_move, -1,  NULL,
	ai_move, 0,   NULL,
	ai_move, 1,   NULL
};
mmove_t dmksoldier_move_death2 = {184, 189, dmksoldier_frames_death2, dmksoldier_dead};

mframe_t dmksoldier_frames_death3 [] =
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
mmove_t dmksoldier_move_death3 = {190, 197, dmksoldier_frames_death3, dmksoldier_dead};


void dmksoldier_die (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point)
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
		self->monsterinfo.currentmove = &dmksoldier_move_death1;
	else if (n == 1)
		self->monsterinfo.currentmove = &dmksoldier_move_death2;
	else
		self->monsterinfo.currentmove = &dmksoldier_move_death3;
}

void dmksoldier_ready_fire (edict_t *self)
{
	gi.dprintf ("Ready.,,\n");
}

void dmksoldier_fire (edict_t *self)
{
	SoldierDMk23 (self);
}

void dmksoldier_refire (edict_t *self);
void dmksoldier_attack(edict_t *self);
mframe_t dmksoldier_frames_attack1 [] =
{
	ai_charge, 0, dmksoldier_ready_fire,
	ai_charge, 0, dmksoldier_fire,
	ai_charge, 0, NULL,
	ai_charge, 0, dmksoldier_fire,
	ai_charge, 0, dmksoldier_refire,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL,
	ai_charge, 0, NULL
};
mmove_t dmksoldier_move_attack1 = {46, 53, dmksoldier_frames_attack1, dmksoldier_run};

void dmksoldier_refire (edict_t *self)
{
	if (random() < 0.7 && (self->monster_mk23_rounds > 0))
		self->s.frame = 46;
}

void dmksoldier_attack(edict_t *self)
{
	if (self->monster_mk23_rounds < 1)
	{
		//dmksoldier_reload (self);
		self->monsterinfo.currentmove = &dmksoldier_move_reload;
		return;
	}
	else
	{
		self->monsterinfo.currentmove = &dmksoldier_move_attack1;
	}
}


/*QUAKED SP_monster_soldier_ss (1 .5 0) (-16 -16 -24) (16 16 32) Ambush Trigger_Spawn Sight
*/
void SP_monster_soldier_ss (edict_t *self)
{
	if (deathmatch->value)
	{
		G_FreeEdict (self);
		return;
	}
	

	self->movetype = MOVETYPE_STEP;
	self->solid = SOLID_BBOX;
	self->s.modelindex = gi.modelindex("models/dmksoldier/tris.md2");
	self->s.modelindex2 = gi.modelindex("models/dmksoldier/w_akimbo.md2");
	VectorSet (self->mins, -16, -16, -24);
	VectorSet (self->maxs, 16, 16, 32);

	self->health = 80;
	self->gib_health = -40;
	self->mass = 125;

	self->monster_mk23_rounds = 12;
	self->reloading = 0;

	self->pain = dmksoldier_pain;
	self->die = dmksoldier_die;

	self->weap_num = 0;

	self->monsterinfo.stand = dmksoldier_stand;
	self->monsterinfo.walk = dmksoldier_walk;
	self->monsterinfo.run = dmksoldier_run;
	self->monsterinfo.dodge = /*dmksoldier_dodge*/NULL;
	self->monsterinfo.attack = dmksoldier_attack;
	self->monsterinfo.melee = NULL;
	self->monsterinfo.sight = dmksoldier_sight;
	self->monsterinfo.idle = dmksoldier_fidget;

	gi.linkentity (self);

	self->monsterinfo.currentmove = &dmksoldier_move_stand;
	self->monsterinfo.scale = MODEL_SCALE;

	walkmonster_start (self);
}