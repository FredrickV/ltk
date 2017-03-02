qboolean Coop_FindKillTarget ();
qboolean Coop_FindDefendTarget ();
qboolean Coop_FindCaptureTarget ();
void Coop_OpenEndingMenu(edict_t *ent, int won);
void Coop_OpenExtraOptionsMenu (edict_t *ent, pmenu_t *p);


edict_t *kill_target_entity;
edict_t *defend_target_entity;

#define COOPMODE_NORMAL 0
#define COOPMODE_EXTERMINATION 1
#define COOPMODE_KILLTARGET 2
#define COOPMODE_DEFENDTARGET 3
#define COOPMODE_CAPTURE 4

#define COOPGAME_WON 1
#define COOPGAME_LOST -1

#define CAPTURE_NAME "Briefcase"