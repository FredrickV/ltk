qboolean SpawnItemByClassname (vec3_t spot, char *classname, qboolean real);
void Mif_Clearitems(edict_t *ent);
void Mif_Undoitem(edict_t *ent);
void Mif_Touch_NewItem(edict_t *ent, edict_t *other, cplane_t *plane, csurface_t *surf);
void Mif_Listitems(edict_t *ent);
void Mif_Saveitems(edict_t *ent);
qboolean Mif_SaveItemData(edict_t *ent);

typedef struct newitem_s
{
     edict_t *ent;
     struct  newitem_s *next;
} newitem_t;

extern newitem_t    *newitem_head;
extern qboolean     erasing;