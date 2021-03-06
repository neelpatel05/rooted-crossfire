/*
 * static char *rcsid_swap_c =
 *    "$Id: swap.c,v 1.17 2005/12/05 23:34:04 akirschbaum Exp $";
 */

/*
    CrossFire, A Multiplayer game for X-windows

    Copyright (C) 2002 Mark Wedel & Crossfire Development Team
    Copyright (C) 1992 Frank Tore Johansen

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

    The author can be reached via e-mail to crossfire-devel@real-time.com
*/

#include <global.h>
#ifndef __CEXTRACT__
#include <sproto.h>
#endif
#include <object.h>

/* This writes out information on all the temporary maps.  It is called by
 * swap_map below.
 */
static void write_map_log(void) 
{
    FILE *fp;
    mapstruct *map;
    char buf[MAX_BUF];
    long current_time=time(NULL);

    sprintf(buf,"%s/temp.maps", settings.localdir);
    if (!(fp=fopen(buf,"w"))) {
	LOG(llevError,"Could not open %s for writing\n", buf);
	return;
    }
    for (map=first_map; map!=NULL; map=map->next) {
	/* If tmpname is null, it is probably a unique player map,
	 * so don't save information on it.
	 */
	if (map->in_memory != MAP_IN_MEMORY && (map->tmpname !=NULL) &&
	    (strncmp(map->path,"/random",7))) {
	    /* the 0 written out is a leftover from the lock number for
	     * unique items and second one is from encounter maps.
	     * Keep using it so that old temp files continue
	     * to work.
	     */
		fprintf(fp,"%s:%s:%ld:0:0:%d:0:%d\n", map->path, map->tmpname,
		    (map->reset_time==-1 ? -1: map->reset_time-current_time),
		    map->difficulty,
		    map->darkness);
	}
    }
    fclose(fp);
}

void read_map_log(void) 
{
    FILE *fp;
    mapstruct *map;
    char buf[MAX_BUF],*cp,*cp1;
    int do_los, darkness, lock;
    long sec =  seconds();


    sprintf(buf,"%s/temp.maps", settings.localdir);
    if (!(fp=fopen(buf,"r"))) {
	LOG(llevDebug,"Could not open %s for reading\n", buf);
	return;
    }
    while (fgets(buf, MAX_BUF, fp)!=NULL) {
	map=get_linked_map();
	/* scanf doesn't work all that great on strings, so we break
	 * out that manually.  strdup is used for tmpname, since other
	 * routines will try to free that pointer.
	 */
	cp=strchr(buf,':');
	*cp++='\0';
	strcpy(map->path, buf);
	cp1=strchr(cp,':');
	*cp1++='\0';
	map->tmpname=strdup_local(cp);

	/* Lock is left over from the lock items - we just toss it now.
	 * We use it twice - second one is from encounter, but as we
	 * don't care about the value, this works fine
	 */
	sscanf(cp1,"%d:%d:%d:%hd:%d:%d\n",
		    &map->reset_time, &lock,
		    &lock, &map->difficulty, &do_los,
		    &darkness);


	map->in_memory=MAP_SWAPPED;
	map->darkness=darkness;

	/* When the reset time is saved out, it is adjusted so that
	 * the current time is subtracted (thus, it is saved as number
         * of seconds from current time that it should reset).  We need
	 * to add in the current seconds for this to work right.
	 * On metalforge, strange behavior was observed with really high
	 * reset times - I don't know how they got to that state, 
	 * but easy enough to do some sanity checking here.
	 */
	map->reset_time += sec;
	if (map->reset_time > (sec + MAP_MAXRESET))
	    map->reset_time = 0;

    }
    fclose(fp);
}

void swap_map(mapstruct *map) {
    player *pl;

    if(map->in_memory != MAP_IN_MEMORY) {
	LOG(llevError,"Tried to swap out map which was not in memory.\n");
	return;
    }
    for(pl=first_player;pl!=NULL;pl=pl->next)
	if(pl->ob == NULL || (!(QUERY_FLAG(pl->ob,FLAG_REMOVED)) && pl->ob->map == map))
	    break;

    if(pl != NULL) {
	LOG(llevDebug,"Wanted to swap out map with player.\n");
	return;
    }
    remove_all_pets(map); /* Give them a chance to follow */

    /* Update the reset time.  Only do this is STAND_STILL is not set */
    if (!map->fixed_resettime)
	set_map_reset_time(map);

    /* If it is immediate reset time, don't bother saving it - just get
     * rid of it right away.
     */
    if (map->reset_time <= seconds()) {
	mapstruct *oldmap = map;

	LOG(llevDebug,"Resetting map %s.\n",map->path);
        /* Lauwenmark : Here we handle the MAPRESET global event */
        execute_global_event(EVENT_MAPRESET, map->path);
	map = map->next;
	delete_map(oldmap);
	return;
    }

    if (new_save_map (map, 0) == -1) {
	LOG(llevError, "Failed to swap map %s.\n", map->path);
	/* need to reset the in_memory flag so that delete map will also
	 * free the objects with it.
	 */
	map->in_memory = MAP_IN_MEMORY;
	delete_map(map);
    } else {
	free_map(map,1);
    }

    if (settings.recycle_tmp_maps == TRUE)
	write_map_log();
}

void check_active_maps(void) {
    mapstruct *map, *next;

    for(map=first_map;map!=NULL;map=next) {
	next = map->next;
	if(map->in_memory != MAP_IN_MEMORY)
	    continue;
	if(!map->timeout)
	    continue;
	if( --(map->timeout) > 0)
	    continue;
	/* If LWM is set, we only swap maps out when we run out of objects */
#ifndef MAX_OBJECTS_LWM
	swap_map(map);
#endif
    }
}

/*
 * map_least_timeout() returns the map with the lowest timeout variable (not 0)
 */

mapstruct *map_least_timeout(char *except_level) {
  mapstruct *map, *chosen=NULL;
  int timeout = MAP_MAXTIMEOUT + 1;
  for(map = first_map;map != NULL; map = map->next)
    if(map->in_memory == MAP_IN_MEMORY && strcmp (map->path, except_level) &&
       map->timeout && map->timeout < timeout)
	chosen = map, timeout = map->timeout;
  return chosen;
}

/*
 * swap_below_max() tries to swap out maps which are still in memory because
 * of MAP_TIMEOUT until used objects is below MAX_OBJECTS or there are
 * no more maps to swap.
 */

void swap_below_max(char *except_level) {
    mapstruct *map;

    if(nrofallocobjects - nroffreeobjects < MAX_OBJECTS)
	return;
    for(;;) {
#ifdef MAX_OBJECTS_LWM
	if(nrofallocobjects - nroffreeobjects < MAX_OBJECTS_LWM)
	    return;
#else
	if(nrofallocobjects - nroffreeobjects < MAX_OBJECTS)
	    return;
#endif
	if ((map = map_least_timeout(except_level)) == NULL)
	    return;
	LOG(llevDebug,"Trying to swap out %s before its time.\n", map->path);
	map->timeout=0;
	swap_map(map);
    }
}

/*
 * players_on_map(): will be replaced by map->players when I'm satisfied
 * that the variable is always correct.
 * If show_all is true, we show everyone.  If not, we don't show hidden
 * players (dms)
 */

int players_on_map(mapstruct *m, int show_all) {
  player *pl;
  int nr=0;
  for(pl=first_player;pl!=NULL;pl=pl->next)
    if(pl->ob != NULL && !QUERY_FLAG(pl->ob,FLAG_REMOVED) && pl->ob->map==m &&
       (show_all || !pl->hidden))
      nr++;
  return nr;
}

/*
 * flush_old_maps():
 * Removes tmp-files of maps which are going to be reset next time
 * they are visited.
 * This is very useful if the tmp-disk is very full.
 */
void flush_old_maps(void) {

    mapstruct *m, *oldmap;
    long sec;
    sec = seconds();

    m= first_map;
    while (m) {
	/* There can be cases (ie death) where a player leaves a map and the timeout
	 * is not set so it isn't swapped out.
	 */
	if ((m->in_memory == MAP_IN_MEMORY) && (m->timeout==0) &&
	    !players_on_map(m,TRUE)) {
	    set_map_timeout(m);
	}

	/* per player unique maps are never really reset.  However, we do want
	 * to perdiocially remove the entries in the list of active maps - this
	 * generates a cleaner listing if a player issues the map commands, and
	 * keeping all those swapped out per player unique maps also has some
	 * memory and cpu consumption.
	 * We do the cleanup here because there are lots of places that call
	 * swap map, and doing it within swap map may cause problems as
	 * the functions calling it may not expect the map list to change
	 * underneath them.
	 */
	if ((m->unique || m->template) && m->in_memory == MAP_SWAPPED) {
	    LOG(llevDebug,"Resetting map %s.\n",m->path);
	    oldmap = m;
	    m = m->next;
	    delete_map(oldmap);
	}
	else if(m->in_memory != MAP_SWAPPED || m->tmpname == NULL ||
	   sec < m->reset_time) {
	    m = m->next;
	}
	else {
	    LOG(llevDebug,"Resetting map %s.\n",m->path);
            /* Lauwenmark : Here we handle the MAPRESET global event */
            execute_global_event(EVENT_MAPRESET, m->path);
	clean_tmp_map(m);
	oldmap = m;
	m = m->next;
	delete_map(oldmap);
	}
    }
}
