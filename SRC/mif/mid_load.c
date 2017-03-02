/*
====================================
Paril

Functions, Macros, Extras for the
Mission File placement.

Most of this code credit goes to
the creators of Annihilation.

You can load and save as many missions
as you want (but it will only read up
to 8 missions for each type of map).
If two types of missions on the same map is
found (ex. murder2_ext.mif and murder2_ext2.mif),
it will display a menu asking you which one to
load, or you can manually add the argument to the
end of the server command.

Saving a mission will always keep the number going up,


Most code is also kudos to ID Software.
====================================
*/
#define MAX_LINE_SIZE 255
#include "../g_local.h"

#define MAX_LINES 20 // Number of classes
typedef struct storage_t
{

	char Classname[56];
    char CName[56];
	char Spawnflags[56];
	int SValue;


	vec3_t Origin;
	vec3_t Angles;

}storage_t;

storage_t LoadData[MAX_LINES];

newitem_t   *newitem_head;
qboolean    erasing;

qboolean SpawnItemByClassname (vec3_t spot, char *classname, qboolean real)
{
	edict_t	*ent;
	gitem_t	*item;
	vec3_t	angles;
	newitem_t	*old_newitem_head;
 
    item = FindItemByClassname(classname);
    if (!item)
        return 0;
 
    ent = G_Spawn();
 
    ent->classname = gi.TagMalloc(64*sizeof(char), TAG_LEVEL);
    strcpy(ent->classname,classname);
    
    ent->item = item;
    if (real)
    {
        ent->s.effects = ent->item->world_model_flags;
        ent->s.renderfx = RF_GLOW;
        ent->touch = Touch_Item;
    }
    else
    {
        ent->s.effects = ent->item->world_model_flags|EF_COLOR_SHELL;
        ent->s.renderfx = RF_GLOW|RF_SHELL_RED;
        ent->touch = Mif_Touch_NewItem;
    }
    VectorSet (ent->mins, -15, -15, -15);
    VectorSet (ent->maxs, 15, 15, 15);
    gi.setmodel (ent, ent->item->world_model);
    ent->solid = SOLID_TRIGGER;
    ent->movetype = MOVETYPE_BOUNCE;  
    ent->owner = ent;
    
    angles[0] = 0;
    angles[1] = rand() % 360;
    angles[2] = 0;
    
    VectorCopy (spot, ent->s.origin);
    ent->s.origin[2] += 16;
 
    gi.linkentity (ent);
    
    if (!real)
    {
        old_newitem_head = newitem_head;
        newitem_head = gi.TagMalloc(sizeof(newitem_t), TAG_LEVEL);
        memset(newitem_head, 0, sizeof(newitem_t));
        newitem_head->next = old_newitem_head;
        newitem_head->ent = ent;
    }
 
    return 1;
}
 
void Mif_ClearItems (edict_t *ent)
{
    /*newitem_t   *old_newitem_head;
    
    if (newitem_head)
    {
        while (newitem_head)
        {
            G_FreeEdict(newitem_head->ent);
            old_newitem_head=newitem_head;
            newitem_head=newitem_head->next;
            gi.TagFree(old_newitem_head);
        }
        
        gi.cprintf(ent, PRINT_HIGH, "All new item data cleared\n");
    }
    else
    {
        gi.cprintf(ent, PRINT_HIGH, "There is no new item data stored\n");
    }*/
}
 
void Mif_UndoItem (edict_t *ent)
{
    newitem_t	*old_newitem_head;
    
    if (newitem_head)
    {
        gi.cprintf(ent, PRINT_HIGH, "%s was removed\n",newitem_head->ent->classname);
        G_FreeEdict(newitem_head->ent);
        old_newitem_head=newitem_head;
        newitem_head=newitem_head->next;
        gi.TagFree(old_newitem_head);
    }
    else
    {
        gi.cprintf(ent, PRINT_HIGH, "There is no new item data stored\n");
    }
}
 
void Mif_Touch_NewItem (edict_t *ent, edict_t *other, cplane_t *plane, csurface_t *surf)
{
    newitem_t   *old_newitem_head;
    newitem_t   *old_old_newitem_head;
    
    if (!erasing)
        return;
 
    if (!other->client)
        return;
 
    if (other->health<=0)
        return;
 
    // flash the screen
    other->client->bonus_alpha = 0.25;  
    
    old_newitem_head=newitem_head;
    old_old_newitem_head=old_newitem_head;
    
    while (old_newitem_head)
    {
        if (old_newitem_head->ent==ent)
        {
            if (old_newitem_head==newitem_head)
                newitem_head=newitem_head->next;
            
            old_old_newitem_head->next=old_newitem_head->next;
            
            gi.cprintf(other, PRINT_HIGH, "%s was removed\n",old_newitem_head->ent->classname);
            G_FreeEdict(old_newitem_head->ent);
            gi.TagFree(old_newitem_head);
            return;
        }
        else
        {
            old_old_newitem_head=old_newitem_head;
            old_newitem_head=old_newitem_head->next;
        }
    }
}
 
void Mif_Listitems (edict_t *ent)
{
    newitem_t   *other_newitem_head;
    
    if (newitem_head)
    {
        gi.cprintf(ent, PRINT_HIGH, "New item list, starting with the most recent...\n");
        
        other_newitem_head=newitem_head;
        
        while (other_newitem_head)
        {
            gi.cprintf(ent, PRINT_HIGH, "(%d,%d,%d): %s\n",(int)other_newitem_head->ent->s.origin[0],(int)other_newitem_head->ent->s.origin[1],(int)other_newitem_head->ent->s.origin[2],other_newitem_head->ent->classname);
            other_newitem_head=other_newitem_head->next;
        }
        
    }
    else
    {
        gi.cprintf(ent, PRINT_HIGH, "There is no new item data stored\n");
    }
}
 
void Mif_Saveitems (edict_t *ent)
{
    gi.cprintf(ent, PRINT_HIGH, "Saving new item data for this level... ");
    if (Mif_SaveItemData(ent))
        gi.cprintf(ent, PRINT_HIGH, "OK\n");
    else
        gi.cprintf(ent, PRINT_HIGH, "ERROR! No new items?\n");
}
 
qboolean Mif_SaveItemData(edict_t *ent)
{
    FILE        *fp;
    int         i;
    char        filename[256];
    cvar_t      *game_dir,*mapname;
    newitem_t   *other_newitem_head;
 
    game_dir = gi.cvar ("game", "", 0);
    mapname = gi.cvar ("mapname", "", 0);
 
#ifdef  _WIN32
    i =  sprintf(filename, ".\\");
    i += sprintf(filename + i, game_dir->string);
    i += sprintf(filename + i, "\\missions\\");
    i += sprintf(filename + i, level.mapname);
    i += sprintf(filename + i, ".mif");
#else
    strcpy(filename, "./");
    strcat(filename, game_dir->string);
    strcat(filename, "/missions/");
    strcat(filename, level.mapname);
    strcat(filename, ".mif");
#endif
 
    if (!newitem_head)
    {
        if (fp = fopen (filename, "rt")) // checks to see if the file exists
        {
            fclose(fp);
            gi.cprintf(ent,PRINT_HIGH,"ERASING NEW ITEMS DATA... ");
            if (remove(filename)==0)
                return 1;
        }
        
        return 0;
    }
 
    fp = fopen (filename, "wt");
    if (!fp)
        return 0;
    
    fprintf(fp,"# Generated by Action Quake Mission Editor (Ingame)\n");
    fprintf(fp,"# Code by Paril, idea by Paril.\n");
    fprintf(fp,"# ---------------------------------------------------\n");
    fprintf(fp,"# Make sure, if you modify this file, that you do it right..\n");
    fprintf(fp,"# Read the readme to find out how to use it correctly.\n");
    fprintf(fp,"\n");
    fprintf(fp,"[ItemData]\n");
    
    // Surf the linked list :)
    other_newitem_head = newitem_head;
 
    while (other_newitem_head)
    {
        fprintf(fp,"%d %d %d %s\n",(int)other_newitem_head->ent->s.origin[0],(int)other_newitem_head->ent->s.origin[1],(int)other_newitem_head->ent->s.origin[2],other_newitem_head->ent->classname);
        other_newitem_head=other_newitem_head->next;
    }
 
    fclose(fp);
    
    return 1;
}
 
// addition to get the data from the file without needing trimstring which was used in the original.
 
int Mif_GetLineFromFile(FILE *in, char s[])
{
        int i, c;
 
        // This reads characters from in into s until MAX_LINE_SIZE-1 is reached,
        // a newline character is reached, or an EOF is reached.
        for (i = 0; i < MAX_LINE_SIZE-1 && (c = fgetc(in)) != '\n' && c != EOF; i++)
               s[i] = c;
        // Add a '\0' to the end of s
        s[i] = '\0';
        return i;
}
// end addition
 
 
/*qboolean Mif_LoadItemData(void)
{
    FILE        *fp;
    char        filename[256],classname[64],buffer[256];
    cvar_t      *game_dir;
    vec3_t      spot;
    long        line;
    int         i,a,b,c;
    qboolean    inkey=0;
    
    game_dir = gi.cvar ("game", "", 0);
 
    i =  sprintf(filename, ".\\");
    i += sprintf(filename + i, game_dir->string);
    i += sprintf(filename + i, "\\missions\\");
    i += sprintf(filename + i, level.mapname);
    i += sprintf(filename + i, ".mif"); // change file extension here
 
 
    fp = fopen (filename, "rt");
    if (!fp)
	{
        gi.dprintf ("No item file found\n");  
        return 0;
	}
    
    line = 0;
    while (!feof(fp))
    {
        line++;
        Mif_GetLineFromFile(fp,buffer);        // modification in this codeblock to not use trimstring
        if (buffer[0] =='\0' || buffer[0] =='#')
            continue;
        if (!inkey)
        {
            // Search for [ItemData] key
            if (Q_stricmp(buffer,"[ItemData]")!=0)
                continue;
            inkey=1;
        }
        else
        {
            classname[0] = '\0';
            sscanf (buffer,"%d %d %d %63s",&a,&b,&c,classname);
            spot[0] = (float)a;
            spot[1] = (float)b;
            spot[2] = (float)c;
                    
            if (strlen(classname)==0 || !FindItemByClassname(classname))
            {
                gi.dprintf("Error in missions/%s.mif on line %d!\n",level.mapname,line);
            }
            else if (deathmatch->value || coop->value)
            {
                SpawnItemByClassname(spot,classname,1);
                gi.dprintf("Added %s at (%d,%d,%d)\n",classname,(int)spot[0],(int)spot[1],(int)spot[2]);
            }
            else
            {
                SpawnItemByClassname(spot,classname,0);
                gi.dprintf("Loaded %s at (%d,%d,%d)\n",classname,(int)spot[0],(int)spot[1],(int)spot[2]);
            }
        }
    }
 
    fclose(fp);
    
    return 1;
}*/


void FindMonsterByLoadedClassname (edict_t *m, char *c)
{
	char *monster_array[20] = {"monster_mp5", "monster_infantry",
				               "monster_m4", "monster_gunner",
							   "monster_shotgunner", "monster_soldier",
							   "monster_mk23", "monster_soldier_light",
							   "monster_dmk23", "monster_soldier_ss",
							   "monster_hc", "monster_chick",
							   "monster_throwknife", "monster_berserk",
							   "monster_sniper", "monster_gladiator"};

	m = G_Spawn();

	if (!Q_stricmp(c, monster_array[0]) || !Q_stricmp(c, monster_array[1]))
	{
		SP_monster_infantry(m);
		findspawnpoint (m);
		Coop_RandomizeAngles (m);
	}
	else if (!Q_stricmp(c, monster_array[2]) || !Q_stricmp(c, monster_array[3]))
	{
		SP_monster_gunner(m);
		findspawnpoint (m);
		Coop_RandomizeAngles (m);
	}
	else if (!Q_stricmp(c, monster_array[4]) || !Q_stricmp(c, monster_array[5]))
	{
		SP_monster_soldier(m);
		findspawnpoint (m);
		Coop_RandomizeAngles (m);
	}
	else if (!Q_stricmp(c, monster_array[6]) || !Q_stricmp(c, monster_array[7]))
	{
		SP_monster_soldier_light(m);
		findspawnpoint (m);
		Coop_RandomizeAngles (m);
	}
	else if (!Q_stricmp(c, monster_array[8]) || !Q_stricmp(c, monster_array[9]))
	{
		SP_monster_soldier_ss(m);
		findspawnpoint (m);
		Coop_RandomizeAngles (m);
	}
	else if (!Q_stricmp(c, monster_array[10]) || !Q_stricmp(c, monster_array[11]))
	{
		SP_monster_chick(m);
		findspawnpoint (m);
		Coop_RandomizeAngles (m);
	}
	else if (!Q_stricmp(c, monster_array[12]) || !Q_stricmp(c, monster_array[13]))
	{
		SP_monster_berserk(m);
		findspawnpoint (m);
		Coop_RandomizeAngles (m);
	}
	else if (!Q_stricmp(c, monster_array[14]) || !Q_stricmp(c, monster_array[15]))
	{
		SP_monster_gladiator(m);
		findspawnpoint (m);
		Coop_RandomizeAngles (m);
	}
	else
	{
		G_FreeEdict (m);
		gi.dprintf ("Error on found classname!\n");
	}
}


qboolean Mif_LoadItemData(void)
{
	cvar_t      *game_dir;
	int         i;
	FILE *fp;
	char *Mem;
	long FileSize;
	int LineNum = 0;
	int MemPos= 0;
	int CurrentPos = 0;
	char filename[256];
    int Itter = 0;
    char buffer[10];
	int it;

    memset(buffer,0,sizeof buffer);
	
    game_dir = gi.cvar ("game", "", 0);
 
    i =  sprintf(filename, ".\\");
    i += sprintf(filename + i, game_dir->string);
    i += sprintf(filename + i, "\\missions\\");
    i += sprintf(filename + i, level.mapname);
    i += sprintf(filename + i, ".mif"); // change file extension here

	fp = fopen(filename, "r");


	if (!fp)
	{
		return false;
	}
	fseek(fp,0, SEEK_END);
	FileSize = ftell(fp);
	fseek(fp,0, SEEK_SET);

	Mem = (char *)malloc(FileSize);

	memset(LoadData,0, sizeof LoadData);

	fseek(fp, 0, SEEK_SET);
	fread(Mem, 1, FileSize, fp);

	while(Itter < MAX_LINES && Mem[MemPos] != -51) // dont loop more than this
	{   
	  while(Mem[MemPos] != -51)// while not reached end of file
	  {
		Mem[MemPos];

		if(Mem[MemPos] == 0x7b) // found { , start of the class body
        {

			while(Mem[MemPos] != 0x22) // while we havent found '"'  
                MemPos++;

			MemPos++; //continue
			
            // we found the ' " '
			while(Mem[MemPos] != 0x22)
			{
              LoadData[LineNum].Classname[CurrentPos] = Mem[MemPos];
              MemPos++; CurrentPos++;
			}

         
            MemPos += 2; //continue    
            CurrentPos = 0;
			while(Mem[MemPos] != 0x0a) // while we have not reached new line
			{
               LoadData[LineNum].CName[CurrentPos] = Mem[MemPos];
               MemPos++; CurrentPos++;
			}


             MemPos += 3; //continue  
             CurrentPos = 0;

			 while(Mem[MemPos] != 0x22)
			 {
              LoadData[LineNum].Spawnflags[CurrentPos] = Mem[MemPos];
              MemPos++; CurrentPos++;
			 }

             CurrentPos = 0;
             MemPos+=2; //continue
             while(Mem[MemPos] != 0x0a)
			 {
			   buffer[CurrentPos] = Mem[MemPos];

               MemPos++; CurrentPos++;    
			 }

             LoadData[LineNum].SValue = atoi(buffer);

             // while we havent found the class terminator';' 
			while(Mem[MemPos] != 0x3b) 
                MemPos++;

            break; // go to the next line

		}

		MemPos++;
        CurrentPos = 0;

	  }

      Itter++;
      LineNum++;
	  MemPos++;
	}

	for (it = 0; it < LineNum; it++)
	{
		edict_t *monster = NULL;

		FindMonsterByLoadedClassname (monster, LoadData[it].CName);

		// Paril, To do, of course.
		//monster->spawnflags = LoadData[it].SValue;
		//monster->s.origin = LoadData[it].Origin;
		//monster->s.angles = LoadData[it].Angles;
	}

	return true;
}

int MissionEditorCommands (void)
{
	char *cmd;

	cmd = gi.argv(0);

/*	if (Q_stricmp (cmd, "placeitem") == 0)
    {
        if (mifed->value)
            return 3;
		
        cmd = gi.argv(1);
		
        if (strlen(cmd) == 0)
        {
            safe_bprintf (PRINT_HIGH, "You must specify a classname\n");
            return 2;
        }
        
        if (spawnitembyclassname(ent->s.origin,cmd,0))      
            safe_bprintf (PRINT_HIGH, "%s placed at (%d,%d,%d)\n", cmd, (int)ent->s.origin[0], (int)ent->s.origin[1], (int)ent->s.origin[2]);
        else
            safe_bprintf (PRINT_HIGH, "Could not place %s - item classname unrecognised\n",cmd);
		
        return 1;
    }
    else*/ if (Q_stricmp (cmd, "clearitems") == 0)
    {
        if (mifed->value)
            return 3;
        
//        Cmd_Clearitems_f(ent);

		return 1;
    }
    else if (Q_stricmp (cmd, "undoitem") == 0)
    {
        if (mifed->value)
            return 3;
		
  //      Cmd_Undoitem_f(ent);
		
		return 1;
    }
	
    else if (Q_stricmp (cmd, "eraseitems") == 0)
    {
        if (mifed->value)
            return 3;
		
        if (erasing)
        {
            erasing=0;
            safe_bprintf (PRINT_HIGH, "New item eraser disabled!\n");
        }
        else
        {
            erasing=1;
            safe_bprintf (PRINT_HIGH, "New item eraser enabled!\nCareful where you walk!\n");
        }

		return 1;
    }
	
    else if (Q_stricmp (cmd, "listitems") == 0)
    {
        if (mifed->value)
            return 3;
		
        //Cmd_Listitems_f (ent);

		return 1;
    }
	
    else if (Q_stricmp (cmd, "saveitems") == 0)
    {
        if (mifed->value)
            return 3;
		
       // Cmd_Saveitems_f (ent);

		return 1;
    }
	else if (Q_stricmp(cmd, "loaditems") == 0)
	{
		if (!mifed->value)
			return 3;

		Mif_LoadItemData();
	}
	return 0;
}

