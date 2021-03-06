/* alchemy.c */
void attempt_do_alchemy(object *caster, object *cauldron);
int content_recipe_value(object *op);
int numb_ob_inside(object *op);
object *attempt_recipe(object *caster, object *cauldron, int ability, recipe *rp, int nbatches);
void adjust_product(object *item, int lvl, int yield);
object *make_item_from_recipe(object *cauldron, recipe *rp);
object *find_transmution_ob(object *first_ingred, recipe *rp, size_t *rp_arch_index, int create_item);
void alchemy_failure_effect(object *op, object *cauldron, recipe *rp, int danger);
void remove_contents(object *first_ob, object *save_item);
int calc_alch_danger(object *caster, object *cauldron, recipe *rp);
/* apply.c */
int transport_can_hold(const object *transport, const object *op, int nrof);
int apply_transport(object *pl, object *transport, int aflag);
int should_director_abort(object *op, object *victim);
int apply_potion(object *op, object *tmp);
int improve_weapon_stat(object *op, object *improver, object *weapon, signed char *stat, int sacrifice_count, const char *statname);
int prepare_weapon(object *op, object *improver, object *weapon);
int improve_weapon(object *op, object *improver, object *weapon);
int check_improve_weapon(object *op, object *tmp);
int improve_armour(object *op, object *improver, object *armour);
int convert_item(object *item, object *converter);
int apply_container(object *op, object *sack);
int esrv_apply_container(object *op, object *sack);
void move_apply(object *trap, object *victim, object *originator);
void do_learn_spell(object *op, object *spell, int special_prayer);
void do_forget_spell(object *op, const char *spell);
void apply_scroll(object *op, object *tmp, int dir);
int dragon_eat_flesh(object *op, object *meal);
void apply_poison(object *op, object *tmp);
int is_legal_2ways_exit(object *op, object *exit);
int manual_apply(object *op, object *tmp, int aflag);
int player_apply(object *pl, object *op, int aflag, int quiet);
void player_apply_below(object *pl);
object *get_item_from_body_location(object *start, int loc);
int unapply_for_ob(object *who, object *op, int aflags);
int can_apply_object(object *who, object *op);
int apply_special(object *who, object *op, int aflags);
int monster_apply_special(object *who, object *op, int aflags);
int auto_apply(object *op);
void fix_auto_apply(mapstruct *m);
void eat_special_food(object *who, object *food);
void apply_lighter(object *who, object *lighter);
void scroll_failure(object *op, int failure, int power);
void apply_changes_to_player(object *pl, object *change);
void apply_item_transformer(object *pl, object *transformer);
/* attack.c */
void cancellation(object *op);
int did_make_save_item(object *op, int type, object *originator);
void save_throw_object(object *op, int type, object *originator);
int hit_map(object *op, int dir, int type, int full_hit);
void attack_message(int dam, int type, object *op, object *hitter);
int attack_ob(object *op, object *hitter);
object *hit_with_arrow(object *op, object *victim);
void tear_down_wall(object *op);
void scare_creature(object *target, object *hitter);
int hit_player_attacktype(object *op, object *hitter, int dam, uint32 attacknum, int magic);
int kill_object(object *op, int dam, object *hitter, int type);
int friendly_fire(object *op, object *hitter);
int hit_player(object *op, int dam, object *hitter, int type, int full_hit);
void poison_player(object *op, object *hitter, int dam);
void slow_player(object *op, object *hitter, int dam);
void confuse_player(object *op, object *hitter, int dam);
void blind_player(object *op, object *hitter, int dam);
void paralyze_player(object *op, object *hitter, int dam);
void deathstrike_player(object *op, object *hitter, int *dam);
int adj_attackroll(object *hitter, object *target);
int is_aimed_missile(object *op);
/* ban.c */
int checkbanned(const char *login, const char *host);
/* build_map.c */
int can_build_over(struct mapdef *map, object *tmp, short x, short y);
void remove_marking_runes(struct mapdef *map, short x, short y);
int find_unused_connected_value(struct mapdef *map);
int find_or_create_connection_for_map(object *pl, short x, short y, object *rune);
object *get_connection_rune(object *pl, short x, short y);
object *get_msg_book(object *pl, short x, short y);
object *get_wall(struct mapdef *map, int x, int y);
void fix_walls(struct mapdef *map, int x, int y);
void apply_builder_floor(object *pl, object *material, short x, short y);
void apply_builder_wall(object *pl, object *material, short x, short y);
void apply_builder_item(object *pl, object *item, short x, short y);
void apply_builder_remove(object *pl, int dir);
void apply_map_builder(object *pl, int dir);
int adjust_sign_msg(object *pl, short x, short y, object *tmp);
/* c_chat.c */
int command_say(object *op, char *params);
int command_me(object *op, char *params);
int command_cointoss(object *op, char *params);
int command_orcknuckle(object *op, char *params);
int command_shout(object *op, char *params);
int command_chat(object *op, char *params);
int command_tell(object *op, char *params);
int command_reply(object *op, char *params);
int command_nod(object *op, char *params);
int command_dance(object *op, char *params);
int command_kiss(object *op, char *params);
int command_bounce(object *op, char *params);
int command_smile(object *op, char *params);
int command_cackle(object *op, char *params);
int command_laugh(object *op, char *params);
int command_giggle(object *op, char *params);
int command_shake(object *op, char *params);
int command_puke(object *op, char *params);
int command_growl(object *op, char *params);
int command_scream(object *op, char *params);
int command_sigh(object *op, char *params);
int command_sulk(object *op, char *params);
int command_hug(object *op, char *params);
int command_cry(object *op, char *params);
int command_poke(object *op, char *params);
int command_accuse(object *op, char *params);
int command_grin(object *op, char *params);
int command_bow(object *op, char *params);
int command_clap(object *op, char *params);
int command_blush(object *op, char *params);
int command_burp(object *op, char *params);
int command_chuckle(object *op, char *params);
int command_cough(object *op, char *params);
int command_flip(object *op, char *params);
int command_frown(object *op, char *params);
int command_gasp(object *op, char *params);
int command_glare(object *op, char *params);
int command_groan(object *op, char *params);
int command_hiccup(object *op, char *params);
int command_lick(object *op, char *params);
int command_pout(object *op, char *params);
int command_shiver(object *op, char *params);
int command_shrug(object *op, char *params);
int command_slap(object *op, char *params);
int command_smirk(object *op, char *params);
int command_snap(object *op, char *params);
int command_sneeze(object *op, char *params);
int command_snicker(object *op, char *params);
int command_sniff(object *op, char *params);
int command_snore(object *op, char *params);
int command_spit(object *op, char *params);
int command_strut(object *op, char *params);
int command_thank(object *op, char *params);
int command_twiddle(object *op, char *params);
int command_wave(object *op, char *params);
int command_whistle(object *op, char *params);
int command_wink(object *op, char *params);
int command_yawn(object *op, char *params);
int command_beg(object *op, char *params);
int command_bleed(object *op, char *params);
int command_cringe(object *op, char *params);
int command_think(object *op, char *params);
/* c_misc.c */
void map_info(object *op, char *search);
int command_body(object *op, char *params);
int command_motd(object *op, char *params);
int command_bug(object *op, char *params);
void malloc_info(object *op);
void current_region_info(object *op);
void current_map_info(object *op);
int command_whereabouts(object *op, char *params);
int command_who(object *op, char *params);
void display_who_entry(object *op, player *pl, const char *format);
void get_who_escape_code_value(char *return_val, const char letter, player *pl);
int command_afk(object *op, char *params);
int command_malloc(object *op, char *params);
int command_mapinfo(object *op, char *params);
int command_whereami(object *op, char *params);
int command_maps(object *op, char *params);
int command_strings(object *op, char *params);
int command_sstable(object *op, char *params);
int command_time(object *op, char *params);
int command_weather(object *op, char *params);
int command_archs(object *op, char *params);
int command_hiscore(object *op, char *params);
int command_debug(object *op, char *params);
int command_dumpbelow(object *op, char *params);
int command_wizpass(object *op, char *params);
int command_wizcast(object *op, char *params);
int command_dumpallobjects(object *op, char *params);
int command_dumpfriendlyobjects(object *op, char *params);
int command_dumpallarchetypes(object *op, char *params);
int command_ssdumptable(object *op, char *params);
int command_dumpmap(object *op, char *params);
int command_dumpallmaps(object *op, char *params);
int command_printlos(object *op, char *params);
int command_version(object *op, char *params);
void bug_report(const char *reportstring);
int command_output_sync(object *op, char *params);
int command_output_count(object *op, char *params);
int command_listen(object *op, char *params);
int command_statistics(object *pl, char *params);
int command_fix_me(object *op, char *params);
int command_players(object *op, char *paramss);
int command_logs(object *op, char *params);
int command_applymode(object *op, char *params);
int command_bowmode(object *op, char *params);
int command_petmode(object *op, char *params);
int command_showpets(object *op, char *params);
int command_usekeys(object *op, char *params);
int command_resistances(object *op, char *params);
int command_help(object *op, char *params);
int onoff_value(const char *line);
int command_quit(object *op, char *params);
int command_explore(object *op, char *params);
int command_sound(object *op, char *params);
void receive_player_name(object *op, char k);
void receive_player_password(object *op, char k);
int explore_mode(void);
int command_title(object *op, char *params);
int command_save(object *op, char *params);
int command_peaceful(object *op, char *params);
int command_wimpy(object *op, char *params);
int command_brace(object *op, char *params);
int command_style_map_info(object *op, char *params);
int command_kill_pets(object *op, char *params);
int command_quests(object *pl, char *params);
/* c_move.c */
int command_east(object *op, char *params);
int command_north(object *op, char *params);
int command_northeast(object *op, char *params);
int command_northwest(object *op, char *params);
int command_south(object *op, char *params);
int command_southeast(object *op, char *params);
int command_southwest(object *op, char *params);
int command_west(object *op, char *params);
int command_stay(object *op, char *params);
/* c_new.c */
int execute_newserver_command(object *pl, char *command);
int command_run(object *op, char *params);
int command_run_stop(object *op, char *params);
int command_fire(object *op, char *params);
int command_fire_stop(object *op, char *params);
int bad_command(object *op, char *params);
/* c_object.c */
object *find_best_object_match(object *pl, const char *params);
int command_build(object *pl, char *params);
int command_uskill(object *pl, char *params);
int command_rskill(object *pl, char *params);
int command_search(object *op, char *params);
int command_disarm(object *op, char *params);
int command_throw(object *op, char *params);
int command_apply(object *op, char *params);
int sack_can_hold(object *pl, object *sack, object *op, uint32 nrof);
void pick_up(object *op, object *alt);
int command_take(object *op, char *params);
void put_object_in_sack(object *op, object *sack, object *tmp, uint32 nrof);
void drop_object(object *op, object *tmp, uint32 nrof);
void drop(object *op, object *tmp);
int command_dropall(object *op, char *params);
int command_drop(object *op, char *params);
int command_examine(object *op, char *params);
object *find_marked_object(object *op);
int command_mark(object *op, char *params);
void examine_monster(object *op, object *tmp);
char *long_desc(object *tmp, object *pl);
void examine(object *op, object *tmp);
void inventory(object *op, object *inv);
int command_pickup(object *op, char *params);
void set_pickup_mode(object *op, int i);
int command_search_items(object *op, char *params);
int command_rename_item(object *op, char *params);
/* c_party.c */
partylist *get_firstparty(void);
void remove_party(partylist *target_party);
void obsolete_parties(void);
int confirm_party_password(object *op);
void receive_party_password(object *op, char k);
void send_party_message(object *op, char *msg);
int command_gsay(object *op, char *params);
int command_party(object *op, char *params);
/* c_range.c */
int command_invoke(object *op, char *params);
int command_cast(object *op, char *params);
int command_prepare(object *op, char *params);
int command_cast_spell(object *op, char *params, char command);
int legal_range(object *op, int r);
void change_spell(object *op, char k);
int command_rotateshoottype(object *op, char *params);
/* c_wiz.c */
int command_loadtest(object *op, char *params);
void do_wizard_hide(object *op, int silent_dm);
int command_hide(object *op, char *params);
int command_setgod(object *op, char *params);
int command_banish(object *op, char *params);
int command_kick(object *op, char *params);
int command_save_overlay(object *op, char *params);
int command_toggle_shout(object *op, char *params);
int command_shutdown(object *op, char *params);
int command_goto(object *op, char *params);
int command_generate(object *op, char *params);
int command_freeze(object *op, char *params);
int command_arrest(object *op, char *params);
int command_summon(object *op, char *params);
int command_teleport(object *op, char *params);
int command_create(object *op, char *params);
int command_inventory(object *op, char *params);
int command_skills(object *op, char *params);
int command_dump(object *op, char *params);
int command_mon_aggr(object *op, char *params);
int command_possess(object *op, char *params);
int command_patch(object *op, char *params);
int command_remove(object *op, char *params);
int command_free(object *op, char *params);
int command_addexp(object *op, char *params);
int command_speed(object *op, char *params);
int command_stats(object *op, char *params);
int command_abil(object *op, char *params);
int command_reset(object *op, char *params);
int command_nowiz(object *op, char *params);
int do_wizard_dm(object *op, char *params, int silent);
int command_dm(object *op, char *params);
int command_invisible(object *op, char *params);
int command_learn_spell(object *op, char *params);
int command_learn_special_prayer(object *op, char *params);
int command_forget_spell(object *op, char *params);
int command_listplugins(object *op, char *params);
int command_loadplugin(object *op, char *params);
int command_unloadplugin(object *op, char *params);
int command_dmhide(object *op, char *params);
void dm_stack_pop(player *pl);
object *dm_stack_peek(player *pl);
void dm_stack_push(player *pl, tag_t item);
object *get_dm_object(player *pl, char **params, int *from);
int command_stack_pop(object *op, char *params);
int command_stack_push(object *op, char *params);
int command_stack_list(object *op, char *params);
int command_stack_clear(object *op, char *params);
int command_diff(object *op, char *params);
int command_insert_into(object *op, char *params);
/* commands.c */
void init_commands(void);
CommFunc find_oldsocket_command(char *cmd);
CommFunc find_oldsocket_command2(char *cmd);
int parse_string(object *op, char *str);
int parse_command(object *op, char *str);
/* daemon.c */
FILE *BecomeDaemon(char *filename);
/* disease.c */
int move_disease(object *disease);
int remove_symptoms(object *disease);
object *find_symptom(object *disease);
int check_infection(object *disease);
int infect_object(object *victim, object *disease, int force);
int do_symptoms(object *disease);
int grant_immunity(object *disease);
int move_symptom(object *symptom);
int check_physically_infect(object *victim, object *hitter);
object *find_disease(object *victim);
int cure_disease(object *sufferer, object *caster);
int reduce_symptoms(object *sufferer, int reduction);
/* egoitem.c */
int create_artifact(object *op, const char *artifactname);
int apply_power_crystal(object *op, object *crystal);
/* hiscore.c */
char *spool(char *bp, char *error);
void check_score(object *op);
void display_high_score(object *op, int max, const char *match);
/* gods.c */
int lookup_god_by_name(const char *name);
object *find_god(const char *name);
const char *determine_god(object *op);
void pray_at_altar(object *pl, object *altar, object *skill);
void become_follower(object *op, object *new_god);
int worship_forbids_use(object *op, object *exp_obj, uint32 flag, const char *string);
void stop_using_item(object *op, int type, int number);
void update_priest_flag(object *god, object *exp_ob, uint32 flag);
archetype *determine_holy_arch(object *god, const char *type);
void god_intervention(object *op, object *god, object *skill);
int god_examines_priest(object *op, object *god);
int god_examines_item(object *god, object *item);
int get_god(object *priest);
const char *get_god_for_race(const char *race);
int tailor_god_spell(object *spellop, object *caster);
/* init.c */
void set_logfile(char *val);
void call_version(void);
void showscores(void);
void set_debug(void);
void unset_debug(void);
void set_mondebug(void);
void set_dumpmon1(void);
void set_dumpmon2(void);
void set_dumpmon3(void);
void set_dumpmon4(void);
void set_dumpmon5(void);
void set_dumpmon6(void);
void set_dumpmon7(void);
void set_dumpmon8(void);
void set_dumpmon9(void);
void set_dumpmont(char *name);
void set_daemon(void);
void set_datadir(char *path);
void set_confdir(char *path);
void set_localdir(char *path);
void set_mapdir(char *path);
void set_archetypes(char *path);
void set_regions(char *path);
void set_treasures(char *path);
void set_uniquedir(char *path);
void set_templatedir(char *path);
void set_playerdir(char *path);
void set_tmpdir(char *path);
void showscoresparm(char *data);
void set_csport(char *val);
void init(int argc, char **argv);
void usage(void);
void help(void);
void init_beforeplay(void);
void init_startup(void);
void compile_info(void);
void rec_sigsegv(int i);
void rec_sigint(int i);
void rec_sighup(int i);
void rec_sigquit(int i);
void rec_sigpipe(int i);
void rec_sigbus(int i);
void rec_sigterm(int i);
void fatal_signal(int make_core, int close_sockets);
void init_signals(void);
void init_races(void);
void dump_races(void);
void add_to_racelist(const char *race_name, object *op);
racelink *get_racelist(void);
racelink *find_racelink(const char *name);
/* login.c */
void emergency_save(int flag);
void delete_character(const char *name, int new);
int verify_player(const char *name, char *password);
int check_name(player *me, const char *name);
int create_savedir_if_needed(char *savedir);
void destroy_object(object *op);
int save_player(object *op, int flag);
void copy_file(const char *filename, FILE *fpout);
void check_login(object *op);
/* main.c */
void version(object *op);
void info_keys(object *op);
void start_info(object *op);
char *crypt_string(char *str, char *salt);
int check_password(char *typed, char *crypted);
void enter_player_savebed(object *op);
void leave_map(object *op);
void set_map_timeout(mapstruct *oldmap);
char *clean_path(const char *file);
char *unclean_path(const char *src);
void enter_exit(object *op, object *exit_ob);
void process_active_maps(void);
void process_players1(mapstruct *map);
void process_players2(mapstruct *map);
void process_events(mapstruct *map);
void clean_tmp_files(void);
void cleanup(void);
void leave(player *pl, int draw_exit);
int forbid_play(void);
void do_specials(void);
int main(int argc, char **argv);
/* monster.c */
object *check_enemy(object *npc, rv_vector *rv);
object *find_nearest_living_creature(object *npc);
object *find_enemy(object *npc, rv_vector *rv);
int check_wakeup(object *op, object *enemy, rv_vector *rv);
int move_randomly(object *op);
int move_monster(object *op);
int can_hit(object *ob1, object *ob2, rv_vector *rv);
object *monster_choose_random_spell(object *monster);
int monster_cast_spell(object *head, object *part, object *pl, int dir, rv_vector *rv);
int monster_use_scroll(object *head, object *part, object *pl, int dir, rv_vector *rv);
int monster_use_skill(object *head, object *part, object *pl, int dir);
int monster_use_range(object *head, object *part, object *pl, int dir);
int monster_use_bow(object *head, object *part, object *pl, int dir);
int check_good_weapon(object *who, object *item);
int check_good_armour(object *who, object *item);
void monster_check_pickup(object *monster);
int monster_can_pick(object *monster, object *item);
void monster_apply_below(object *monster);
void monster_check_apply(object *mon, object *item);
void npc_call_help(object *op);
int dist_att(int dir, object *ob, object *enemy, object *part, rv_vector *rv);
int run_att(int dir, object *ob, object *enemy, object *part, rv_vector *rv);
int hitrun_att(int dir, object *ob, object *enemy);
int wait_att(int dir, object *ob, object *enemy, object *part, rv_vector *rv);
int disthit_att(int dir, object *ob, object *enemy, object *part, rv_vector *rv);
int wait_att2(int dir, object *ob, object *enemy, object *part, rv_vector *rv);
void circ1_move(object *ob);
void circ2_move(object *ob);
void pace_movev(object *ob);
void pace_moveh(object *ob);
void pace2_movev(object *ob);
void pace2_moveh(object *ob);
void rand_move(object *ob);
void check_earthwalls(object *op, mapstruct *m, int x, int y);
void check_doors(object *op, mapstruct *m, int x, int y);
void communicate(object *op, const char *txt);
int talk_to_npc(object *op, object *npc, const char *txt);
int talk_to_wall(object *pl, object *npc, const char *txt);
object *find_mon_throw_ob(object *op);
int can_detect_enemy(object *op, object *enemy, rv_vector *rv);
int stand_in_light(object *op);
int can_see_enemy(object *op, object *enemy);
/* move.c */
int move_object(object *op, int dir);
int move_ob(object *op, int dir, object *originator);
int transfer_ob(object *op, int x, int y, int randomly, object *originator);
int teleport(object *teleporter, uint8 tele_type, object *user);
void recursive_roll(object *op, int dir, object *pusher);
int try_fit(object *op, mapstruct *m, int x, int y);
int roll_ob(object *op, int dir, object *pusher);
int push_ob(object *who, int dir, object *pusher);
/* pets.c */
object *get_pet_enemy(object *pet, rv_vector *rv);
void terminate_all_pets(object *owner);
void remove_all_pets(mapstruct *map);
void follow_owner(object *ob, object *owner);
void pet_move(object *ob);
object *fix_summon_pet(archetype *at, object *op, int dir, int is_golem);
void move_golem(object *op);
void control_golem(object *op, int dir);
int summon_golem(object *op, object *caster, int dir, object *spob);
object *choose_cult_monster(object *pl, object *god, int summon_level);
int summon_object(object *op, object *caster, object *spell_ob, int dir, const char *stringarg);
object *get_real_owner(object *ob);
int should_arena_attack(object *pet, object *owner, object *target);
/* player.c */
player *find_player(const char *plname);
player *find_player_partial_name(const char *plname);
void display_motd(const object *op);
void send_rules(const object *op);
void send_news(const object *op);
int playername_ok(const char *cp);
int add_player(NewSocket *ns);
archetype *get_player_archetype(archetype *at);
object *get_nearest_player(object *mon);
int path_to_player(object *mon, object *pl, unsigned mindiff);
void give_initial_items(object *pl, treasurelist *items);
void get_name(object *op);
void get_password(object *op);
void play_again(object *op);
int receive_play_again(object *op, char key);
void confirm_password(object *op);
void get_party_password(object *op, partylist *party);
int roll_stat(void);
void roll_stats(object *op);
void Roll_Again(object *op);
void Swap_Stat(object *op, int Swap_Second);
int key_roll_stat(object *op, char key);
int key_change_class(object *op, char key);
int key_confirm_quit(object *op, char key);
void flee_player(object *op);
int check_pick(object *op);
object *find_arrow(object *op, const char *type);
object *find_better_arrow(object *op, object *target, const char *type, int *better);
object *pick_arrow_target(object *op, const char *type, int dir);
int fire_bow(object *op, object *part, object *arrow, int dir, int wc_mod, sint16 sx, sint16 sy);
int player_fire_bow(object *op, int dir);
void fire_misc_object(object *op, int dir);
void fire(object *op, int dir);
object *find_key(object *pl, object *container, object *door);
void move_player_attack(object *op, int dir);
int move_player(object *op, int dir);
int handle_newcs_player(object *op);
int save_life(object *op);
void remove_unpaid_objects(object *op, object *env);
char *gravestone_text(object *op);
void do_some_living(object *op);
void kill_player(object *op);
void loot_object(object *op);
void fix_weight(void);
void fix_luck(void);
void cast_dust(object *op, object *throw_ob, int dir);
void make_visible(object *op);
int is_true_undead(object *op);
int hideability(object *ob);
void do_hidden_move(object *op);
int stand_near_hostile(object *who);
int player_can_view(object *pl, object *op);
int action_makes_visible(object *op);
int op_on_battleground(object *op, int *x, int *y);
void dragon_ability_gain(object *who, int atnr, int level);
void player_unready_range_ob(player *pl, object *ob);
/* plugins.c */
int execute_event(object *op, int eventcode, object *activator, object *third, const char *message, int fix);
int execute_global_event(int eventcode, ...);
int plugins_init_plugin(const char *libfile);
void *cfapi_get_hooks(int *type, ...);
int plugins_remove_plugin(const char *id);
crossfire_plugin *plugins_find_plugin(const char *id);
void plugins_display_list(object *op);
void *cfapi_system_find_animation(int *type, ...);
void *cfapi_system_strdup_local(int *type, ...);
void *cfapi_system_register_global_event(int *type, ...);
void *cfapi_system_unregister_global_event(int *type, ...);
void *cfapi_system_add_string(int *type, ...);
void *cfapi_system_remove_string(int *type, ...);
void *cfapi_system_check_path(int *type, ...);
void *cfapi_system_re_cmp(int *type, ...);
void *cfapi_system_directory(int *type, ...);
void *cfapi_map_get_map(int *type, ...);
void *cfapi_map_has_been_loaded(int *type, ...);
void *cfapi_map_create_path(int *type, ...);
void *cfapi_map_get_map_property(int *type, ...);
void *cfapi_map_set_map_property(int *type, ...);
void *cfapi_map_out_of_map(int *type, ...);
void *cfapi_map_update_position(int *type, ...);
void *cfapi_map_delete_map(int *type, ...);
void *cfapi_map_message(int *type, ...);
void *cfapi_map_get_object_at(int *type, ...);
void *cfapi_map_get_flags(int *type, ...);
void *cfapi_map_present_arch_by_name(int *type, ...);
void *cfapi_object_move(int *type, ...);
void *cfapi_object_get_key(int *type, ...);
void *cfapi_object_set_key(int *type, ...);
void *cfapi_object_get_property(int *type, ...);
void *cfapi_object_set_property(int *type, ...);
void *cfapi_object_apply_below(int *type, ...);
void *cfapi_object_apply(int *type, ...);
void *cfapi_object_identify(int *type, ...);
void *cfapi_object_describe(int *type, ...);
void *cfapi_object_drain(int *type, ...);
void *cfapi_object_fix(int *type, ...);
void *cfapi_object_give_skill(int *type, ...);
void *cfapi_object_transmute(int *type, ...);
void *cfapi_object_remove(int *type, ...);
void *cfapi_object_delete(int *type, ...);
void *cfapi_object_clone(int *type, ...);
void *cfapi_object_find(int *type, ...);
void *cfapi_object_create(int *type, ...);
void *cfapi_object_insert(int *type, ...);
void *cfapi_object_split(int *type, ...);
void *cfapi_object_merge(int *type, ...);
void *cfapi_object_distance(int *type, ...);
void *cfapi_object_update(int *type, ...);
void *cfapi_object_clear(int *type, ...);
void *cfapi_object_reset(int *type, ...);
void *cfapi_object_check_inventory(int *type, ...);
void *cfapi_object_clean_object(int *type, ...);
void *cfapi_object_on_same_map(int *type, ...);
void *cfapi_object_spring_trap(int *type, ...);
void *cfapi_object_check_trigger(int *type, ...);
void *cfapi_object_query_cost(int *type, ...);
void *cfapi_object_query_money(int *type, ...);
void *cfapi_object_cast(int *type, ...);
void *cfapi_object_learn_spell(int *type, ...);
void *cfapi_object_forget_spell(int *type, ...);
void *cfapi_object_check_spell(int *type, ...);
void *cfapi_object_pay_amount(int *type, ...);
void *cfapi_object_pay_item(int *type, ...);
void *cfapi_object_transfer(int *type, ...);
void *cfapi_object_find_archetype_inside(int *type, ...);
void *cfapi_object_drop(int *type, ...);
void *cfapi_object_take(int *type, ...);
void *cfapi_object_say(int *type, ...);
void *cfapi_object_speak(int *type, ...);
void *cfapi_player_find(int *type, ...);
void *cfapi_player_message(int *type, ...);
void *cfapi_player_send_inventory(int *type, ...);
void *cfapi_object_teleport(int *type, ...);
void *cfapi_object_pickup(int *type, ...);
void *cfapi_archetype_get_first(int *type, ...);
void *cfapi_archetype_get_property(int *type, ...);
void *cfapi_party_get_property(int *type, ...);
void *cfapi_region_get_property(int *type, ...);
CommArray_s *find_plugin_command(char *cmd, object *op);
int initPlugins(void);
/* resurrection.c */
int cast_raise_dead_spell(object *op, object *caster, object *spell, int dir, const char *arg);
int resurrection_fails(int levelcaster, int leveldead);
void dead_player(object *op);
void dead_character(const char *name);
int dead_player_exists(const char *name);
/* rune.c */
int write_rune(object *op, object *caster, object *spell, int dir, const char *runename);
void move_rune(object *op);
void rune_attack(object *op, object *victim);
void spring_trap(object *trap, object *victim);
int dispel_rune(object *op, object *caster, object *spell, object *skill, int dir);
int trap_see(object *op, object *trap);
int trap_show(object *trap, object *where);
int trap_disarm(object *disarmer, object *trap, int risk, object *skill);
void trap_adjust(object *trap, int difficulty);
/* shop.c */
double shopkeeper_approval(const mapstruct *map, const object *player);
uint64 query_cost(const object *tmp, object *who, int flag);
const char *query_cost_string(const object *tmp, object *who, int flag);
uint64 query_money(const object *op);
int pay_for_amount(uint64 to_pay, object *pl);
int pay_for_item(object *op, object *pl);
int can_pay(object *pl);
int get_payment(object *pl, object *op);
void sell_item(object *op, object *pl);
int describe_shop(const object *op);
void shop_listing(object *op);
/* skills.c */
int steal(object *op, int dir, object *skill);
int pick_lock(object *pl, int dir, object *skill);
int hide(object *op, object *skill);
int jump(object *pl, int dir, object *skill);
int do_skill_ident2(object *tmp, object *pl, int obj_class, object *skill);
int skill_ident(object *pl, object *skill);
int use_oratory(object *pl, int dir, object *skill);
int singing(object *pl, int dir, object *skill);
int find_traps(object *pl, object *skill);
int remove_trap(object *op, int dir, object *skill);
int pray(object *pl, object *skill);
void meditate(object *pl, object *skill);
int write_on_item(object *pl, const char *params, object *skill);
int skill_throw(object *op, object *part, int dir, const char *params, object *skill);
/* skill_util.c */
void init_skills(void);
void link_player_skills(object *op);
object *find_skill_by_name(object *who, const char *name);
object *find_skill_by_number(object *who, int skillno);
int change_skill(object *who, object *new_skill, int flag);
void clear_skill(object *who);
int do_skill(object *op, object *part, object *skill, int dir, const char *string);
int calc_skill_exp(object *who, object *op, object *skill);
int learn_skill(object *pl, object *scroll);
void show_skills(object *op, const char *search);
int use_skill(object *op, const char *string);
int skill_attack(object *tmp, object *pl, int dir, const char *string, object *skill);
int attack_hth(object *pl, int dir, const char *string, object *skill);
int attack_melee_weapon(object *op, int dir, const char *string, object *skill);
/* spell_attack.c */
void check_spell_knockback(object *op);
void forklightning(object *op, object *tmp);
void move_bolt(object *op);
int fire_bolt(object *op, object *caster, int dir, object *spob, object *skill);
void explosion(object *op);
void explode_bullet(object *op);
void check_bullet(object *op);
void move_bullet(object *op);
int fire_bullet(object *op, object *caster, int dir, object *spob);
void cone_drop(object *op);
void move_cone(object *op);
int cast_cone(object *op, object *caster, int dir, object *spell);
void animate_bomb(object *op);
int create_bomb(object *op, object *caster, int dir, object *spell);
object *get_pointed_target(object *op, int dir, int range, int type);
int cast_smite_spell(object *op, object *caster, int dir, object *spell);
void move_missile(object *op);
int make_object_glow(object *op, int radius, int time);
int cast_destruction(object *op, object *caster, object *spell_ob);
int cast_curse(object *op, object *caster, object *spell_ob, int dir);
int mood_change(object *op, object *caster, object *spell);
void move_ball_spell(object *op);
void move_swarm_spell(object *op);
int fire_swarm(object *op, object *caster, object *spell, int dir);
int cast_light(object *op, object *caster, object *spell, int dir);
int cast_cause_disease(object *op, object *caster, object *spell, int dir);
/* spell_effect.c */
void cast_magic_storm(object *op, object *tmp, int lvl);
int recharge(object *op, object *caster, object *spell_ob);
void polymorph_living(object *op);
void polymorph_melt(object *who, object *op);
void polymorph_item(object *who, object *op);
void polymorph(object *op, object *who);
int cast_polymorph(object *op, object *caster, object *spell_ob, int dir);
int cast_create_missile(object *op, object *caster, object *spell, int dir, const char *stringarg);
int cast_create_food(object *op, object *caster, object *spell_ob, int dir, const char *stringarg);
int probe(object *op, object *caster, object *spell_ob, int dir);
int makes_invisible_to(object *pl, object *mon);
int cast_invisible(object *op, object *caster, object *spell_ob);
int cast_earth_to_dust(object *op, object *caster, object *spell_ob);
void execute_word_of_recall(object *op);
int cast_word_of_recall(object *op, object *caster, object *spell_ob);
int cast_wonder(object *op, object *caster, int dir, object *spell_ob);
int perceive_self(object *op);
int cast_create_town_portal(object *op, object *caster, object *spell, int dir);
int magic_wall(object *op, object *caster, int dir, object *spell_ob);
int dimension_door(object *op, object *caster, object *spob, int dir);
int cast_heal(object *op, object *caster, object *spell, int dir);
int cast_change_ability(object *op, object *caster, object *spell_ob, int dir, int silent);
int cast_bless(object *op, object *caster, object *spell_ob, int dir);
int alchemy(object *op, object *caster, object *spell_ob);
int remove_curse(object *op, object *caster, object *spell);
int cast_identify(object *op, object *caster, object *spell);
int cast_detection(object *op, object *caster, object *spell, object *skill);
int cast_transfer(object *op, object *caster, object *spell, int dir);
void counterspell(object *op, int dir);
int cast_consecrate(object *op, object *caster, object *spell);
int animate_weapon(object *op, object *caster, object *spell, int dir);
int cast_change_map_lightlevel(object *op, object *caster, object *spell);
int create_aura(object *op, object *caster, object *spell);
void move_aura(object *aura);
void move_peacemaker(object *op);
int write_mark(object *op, object *spell, const char *msg);
/* spell_util.c */
object *find_random_spell_in_ob(object *ob, const char *skill);
void set_spell_skill(object *op, object *caster, object *spob, object *dest);
void init_spells(void);
void dump_spells(void);
void spell_effect(object *spob, int x, int y, mapstruct *map, object *originator);
int min_casting_level(object *caster, object *spell);
int caster_level(object *caster, object *spell);
sint16 SP_level_spellpoint_cost(object *caster, object *spell, int flags);
int SP_level_dam_adjust(object *caster, object *spob);
int SP_level_duration_adjust(object *caster, object *spob);
int SP_level_range_adjust(object *caster, object *spob);
object *check_spell_known(object *op, const char *name);
object *lookup_spell_by_name(object *op, const char *spname);
int reflwall(mapstruct *m, int x, int y, object *sp_op);
int cast_create_obj(object *op, object *caster, object *new_op, int dir);
int ok_to_put_more(mapstruct *m, sint16 x, sint16 y, object *op, int immune_stop);
int fire_arch_from_position(object *op, object *caster, sint16 x, sint16 y, int dir, object *spell);
void regenerate_rod(object *rod);
void drain_rod_charge(object *rod);
object *find_target_for_friendly_spell(object *op, int dir);
int spell_find_dir(mapstruct *m, int x, int y, object *exclude);
void put_a_monster(object *op, const char *monstername);
int summon_hostile_monsters(object *op, int n, const char *monstername);
void shuffle_attack(object *op, int change_face);
void prayer_failure(object *op, int failure, int power);
void spell_failure(object *op, int failure, int power, object *skill);
int cast_party_spell(object *op, object *caster, int dir, object *spell_ob, char *stringarg);
int cast_spell(object *op, object *caster, int dir, object *spell_ob, char *stringarg);
void move_spell_effect(object *op);
void check_spell_effect(object *op);
void apply_spell_effect(object *spell, object *victim);
/* swamp.c */
void walk_on_deep_swamp(object *op, object *victim);
void move_deep_swamp(object *op);
/* swap.c */
void read_map_log(void);
void swap_map(mapstruct *map);
void check_active_maps(void);
mapstruct *map_least_timeout(char *except_level);
void swap_below_max(char *except_level);
int players_on_map(mapstruct *m, int show_all);
void flush_old_maps(void);
/* time.c */
void remove_door(object *op);
void remove_door2(object *op);
void generate_monster_inv(object *gen);
void generate_monster_arch(object *gen);
void generate_monster(object *gen);
void remove_force(object *op);
void remove_blindness(object *op);
void poison_more(object *op);
void move_gate(object *op);
void move_timed_gate(object *op);
void move_detector(object *op);
void animate_trigger(object *op);
void move_hole(object *op);
object *stop_item(object *op);
void fix_stopped_item(object *op, mapstruct *map, object *originator);
object *fix_stopped_arrow(object *op);
void move_arrow(object *op);
void change_object(object *op);
void move_teleporter(object *op);
void move_player_changer(object *op);
void move_firewall(object *op);
void move_player_mover(object *op);
void move_duplicator(object *op);
void move_creator(object *creator);
void move_marker(object *op);
int process_object(object *op);
/* timers.c */
void cftimer_process_timers(void);
void cftimer_process_event(object *ob);
int cftimer_create(int id, long delay, object *ob, int mode);
int cftimer_destroy(int id);
int cftimer_find_free_id(void);
/* weather.c */
void set_darkness_map(mapstruct *m);
void tick_the_clock(void);
void init_weather(void);
void weather_effect(const char *filename);
int worldmap_to_weathermap(int x, int y, int *wx, int *wy, mapstruct *m);
int real_world_temperature(int x, int y, mapstruct *m);
int similar_direction(int a, int b);
