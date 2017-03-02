#
# Quake2 gamei386.so Makefile for Red Hat 5.1
#
# Nov '99 by Richard Hess <rhess@engr.sgi.com>
# -----------------------------------------------------
# Revised Mar 2000 by Connor Caple <connor@botgod.org.uk>
#
# Note:  you can't build Quake2 mods on Red Hat 6.0,
#        they crash shortly after loading...  :)
#
#

ARCH= i386
CC= gcc
BASE_CFLAGS= -DUNIX_FS -DXT_rhess \
	-Dstricmp=strcasecmp -D_strnicmp=strncasecmp 
#	-fwritable-strings

# DEBUG:  use "-O0 -g" flags...
#
CFLAGS= $(BASE_CFLAGS) -O2

LDFLAGS=
SHLIBCFLAGS=-fPIC
SHLIBLDFLAGS=-shared

# WARNING:  disabled fog support by default...
#
# ** to enable fog support, compile with "-DCGF_FOG"
#
# ** fog support contained in the following C++ code;
#
#	acesrc/cgf_sfx_fog.o
#
OBJS=\
	a_cmds.o \
	a_doorkick.o \
	a_game.o \
	a_items.o \
	a_menu.o \
	a_radio.o \
	a_team.o \
	acesrc/acebot_ai.o \
	acesrc/acebot_cmds.o \
	acesrc/acebot_compress.o \
	acesrc/acebot_items.o \
	acesrc/acebot_movement.o \
	acesrc/acebot_nodes.o \
	acesrc/acebot_spawn.o \
	acesrc/bot_ai.o \
	acesrc/bot_collision.o \
	acesrc/bot_combat.o \
	acesrc/bot_env_doors.o \
	acesrc/bot_movement.o \
	acesrc/bot_states.o \
	acesrc/bot_utility.o \
	acesrc/bot_weapon.o \
	acesrc/botchat.o \
	acesrc/botnav.o \
	acesrc/botscan.o \
	cgf_sfx_glass.o \
	g_ai.o \
	g_chase.o \
	g_cmds.o \
	g_combat.o \
	g_func.o \
	g_items.o \
	g_main.o \
	g_misc.o \
	g_monster.o \
	g_phys.o \
	g_save.o \
	g_spawn.o \
	g_svcmds.o \
	g_target.o \
	g_trigger.o \
	g_turret.o \
	g_utils.o \
	g_weapon.o \
	m_move.o \
	p_client.o \
	p_hud.o \
	p_trail.o \
	p_view.o \
	p_weapon.o \
	q_shared.o 

TARGET= gamei386.so

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(SHLIBLDFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

clean:
	rm -f $(OBJS) core

realclean:
	rm -f $(OBJS) *~ acesrc/*~ core

acesrc/cgf_sfx_fog.o:
	g++ $(CFLAGS) $(SHLIBCFLAGS) -c acesrc/cgf_sfx_fog.c -o acesrc/cgf_sfx_fog.o

.c.o:
	$(CC) $(CFLAGS) $(SHLIBCFLAGS) -c $*.c -o $*.o

