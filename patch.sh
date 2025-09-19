 (cd "$(git rev-parse --show-toplevel)" && git apply --3way <<'EOF' 
diff --git a/Makefile b/Makefile
index 791044df8e7076889634075db1eba5e27017d628..35f5769450590711fcc8091780ecd9c261390257 100644
--- a/Makefile
+++ b/Makefile
@@ -61,55 +61,55 @@ SRC         = name.cpp \
               chaos_crystal.cpp \
 			  dwarf_paladin.cpp \
               gundren_rockseeker.cpp \
 			  dorgar_stoneguard.cpp \
 			  hilda_stormshield.cpp \
 			  murna_claygrip.cpp \
 			  thorbald_ironpocket.cpp \
               goblin_warmaster.cpp \
 			  ancient_predatory_beast.cpp \
 			  night_elven_guard.cpp \
               grizz.cpp \
 			  ghost.cpp \
               main.cpp \
               template.cpp \
               npc_stats.cpp \
               npc_set_stats.cpp \
               npc_change_stats_02.cpp \
               npc_change_stats_03.cpp \
               npc_change_stats_04.cpp \
               npc_update_buff_01.cpp \
               growth_stack.cpp \
               utils01.cpp \
               utils02.cpp \
               debug.cpp \
 			  add_element.cpp \
-			  fetch_target.cpp \
-			  remove_concentration.cpp \
-			  initialize.cpp \
-			  remove_element.cpp \
-			  open.cpp \
+                          fetch_target.cpp \
+                          remove_concentration.cpp \
+                          initialize.cpp \
+                          initialize_character_template.cpp \
+                          open.cpp \
               initiative_all.cpp \
               initiative_pc.cpp \
               initiative_request.cpp \
               initiative_sort_1.cpp \
               initiative_sort_2.cpp \
               initiative.cpp \
               free_memory.cpp \
               init_info.cpp \
               save_data.cpp \
               save_player.cpp \
               check_data.cpp \
               shadow_claw_effect.cpp \
               nightmare_claw_effect.cpp \
               check_buff_attack.cpp \
               check_buff_save.cpp \
               check_buff_skill.cpp \
               check_buff_general.cpp \
               update_buff.cpp \
               update_buff_special.cpp \
               update_lightning_strike.cpp \
               to_hit.cpp \
               readline_check.cpp \
               roll.cpp \
               fclean.cpp \
               player.cpp \
diff --git a/ancient_predatory_beast.cpp b/ancient_predatory_beast.cpp
index 45c891c6f14e8353d51151def0abd4608b1e3b17..950a8b66a569ec0cc66bd7f9175eb47ef651c05f 100644
--- a/ancient_predatory_beast.cpp
+++ b/ancient_predatory_beast.cpp
@@ -19,51 +19,51 @@ void ft_ancient_predatory_beast_turn(t_char * info)
     pf_printf("%s currently has %d/%d hp\n", info->name, info->stats.health, info->dstats.health);
     return ;
 }
 
 static void ft_initialize_gear_and_feats(t_char * info)
 {
     (void)info;
     return ;
 }
 
 void    ft_ancient_predatory_beast_loot(t_char * info)
 {
     (void)info;
     return ;
 }
 
 t_char *ft_ancient_predatory_beast(const int index, const char **input, t_name *name, int exception)
 {
     int error = 0;
     t_char *info = static_cast<t_char *>(cma_malloc(sizeof(t_char)));
     if (!info)
     {
         pf_printf_fd(2, "105-Error: Failed to allocate memory info %s\n", input[0]);
         return (ft_nullptr);
     }
-    *info = ANCIENT_PREDATORY_BEAST_INFO;
+    ft_initialize_character_template(info, &ANCIENT_PREDATORY_BEAST_INFO);
     info->name = input[0];
     info->struct_name = name;
     info->save_file = cma_strjoin("data/", input[0]);
     if (!info->save_file)
     {
         ft_free_info(info);
         return (ft_nullptr);
     }
     if (index == 2)
     {
         if (ft_strcmp(input[1], "init") == 0)
         {
             int result = ft_dice_roll(info->hit_dice.dice_amount, info->hit_dice.dice_faces);
             if (result == -1)
             {
                 pf_printf("147-Error Invalid hit dice %s", info->name);
                 ft_free_info(info);
                 return (ft_nullptr);
             }
             info->dstats.health = info->dstats.health + result;
             ft_file file(info->save_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
             if (file.get_error())
             {
                 pf_printf_fd(2, "123-Error opening file %s: %s\n", info->save_file,
                     file.get_error_str());
diff --git a/ancient_predatory_beast.hpp b/ancient_predatory_beast.hpp
index a3609e027e585a9a4ba0a0988d4e316268928eff..b3b2f6614eb61a5901ccf6a062f39b3869a0a586 100644
--- a/ancient_predatory_beast.hpp
+++ b/ancient_predatory_beast.hpp
@@ -149,52 +149,52 @@ static const t_inventory ANCIENT_PREDATORY_BEAST_INVENTORY
 constexpr t_hit_dice ANCIENT_PREDATORY_BEAST_HIT_DICE =
 {
     .dice_amount = 0,
     .dice_faces = 0,
 };
 
 static const t_char ANCIENT_PREDATORY_BEAST_INFO =
 {
     .level = 0,
     .mechanical = 0,
     .passive_perception = 15,
     .initiative = -1,
     .version_number = 2,
     .save_file = ft_nullptr,
     .name = ft_nullptr,
     .turn = ft_ancient_predatory_beast_turn,
     .drop_loot = ft_ancient_predatory_beast_loot,
     .loot = INITIALIZE_LOOT,
     .hit_dice = ANCIENT_PREDATORY_BEAST_HIT_DICE,
     .inventory = ANCIENT_PREDATORY_BEAST_INVENTORY,
     .spells = INITIALIZE_SPELLS,
     .spell_slots = ANCIENT_PREDATORY_BEAST_SPELL_SLOTS,
     .flags = INITIALIZE_FLAGS,
     .crit = ANCIENT_PREDATORY_BEAST_CRIT,
     .attack_bonus = ANCIENT_PREDATORY_BEAST_ATTACK,
-    .bufs = INITIALIZE_BUFFS,
-    .debufs = INITIALIZE_DEBUFFS,
+    .bufs = ft_initialize_buffs(),
+    .debufs = ft_initialize_debuffs(),
     .concentration = INITIALIZE_CONCENTRATION,
     .d_resistance = ANCIENT_PREDATORY_BEAST_DEFAULT_RESISTANCE,
     .c_resistance = INITIALIZE_CURRENT_RESISTANCE,
     .equipment = ANCIENT_PREDATORY_BEAST_EQUIPMENT,
     .skill_mod = ANCIENT_PREDATORY_BEAST_SKILL_MODS,
     .save_mod = ANCIENT_PREDATORY_BEAST_SAVE_MODS,
     .stats = INITIALIZE_STATS,
     .dstats = ANCIENT_PREDATORY_BEAST_DEFAULT_STATS,
     .feats = INITIALIZE_FEATS,
     .struct_name = ft_nullptr,
     .physical = ANCIENT_PREDATORY_BEAST_PHYSICAL,
     .position = INITIALIZE_POSITION,
 };
 
 template <int Amount, int Faces>
 struct ValidateHitDice
 {
     static_assert
     (
         ((Amount == 0 && Faces == 0) || (Amount >= 1 && Faces >= 1)) &&
         (Amount <= 40 && Faces <= 12),
         "Invalid TEMPLATE_HIT_DICE values: Either both must be 0 or both at least 1, " \
             "and the dice amount must not exceed 40, the dice faces must not exceed 12."
     );
 };
diff --git a/chaos_crystal.cpp b/chaos_crystal.cpp
index 3c46080df1465b234f5df9573eb3e9e31e54dc6f..8c6c403170ca6fcd723548f5c064c19e2445357d 100644
--- a/chaos_crystal.cpp
+++ b/chaos_crystal.cpp
@@ -1,81 +1,88 @@
 #include <cerrno>
 #include "dnd_tools.hpp"
 #include "chaos_crystal.hpp"
 #include "libft/Printf/printf.hpp"
 #include "libft/CMA/CMA.hpp"
+#include "libft/Errno/errno.hpp"
 #include "libft/RNG/rng.hpp"
 #include "veraak.hpp"
 #include <fcntl.h>
 #include <sys/types.h>
 #include <sys/stat.h>
 #include <unistd.h>
 
 static void ft_chaos_crystal_damage(t_char * info)
 {
-    char    **player_list;
-    int        i;
+    ft_vector<ft_string>    player_list = ft_get_pc_list();
+    int                     i;
 
-    player_list = ft_get_pc_list();
-    if (!player_list)
+    if (player_list.get_error() != ER_SUCCESS || player_list.size() == 0)
+    {
+        player_list.clear();
         return ;
-    i = ft_double_char_length(const_cast<const char **>(player_list));
-    i = ft_dice_roll(1, i) - 1;
+    }
+    i = ft_dice_roll(1, static_cast<int>(player_list.size())) - 1;
+    if (i < 0)
+    {
+        player_list.clear();
+        return ;
+    }
     pf_printf("%s shoots a magic missile at %s and he/she takes 1 force damage, " \
             " the target does not need to make a concentration save for this damage\n",
-            info->name, player_list[i]);
-    cma_free_double(player_list);
+            info->name, player_list[static_cast<size_t>(i)].c_str());
+    player_list.clear();
     return ;
 }
 
 void ft_chaos_crystal_turn(t_char * info)
 {
     ft_update_buf(info);
     ft_chaos_crystal_damage(info);
     pf_printf("Chaos_crystal currently has %d/%d hp\n",
             info->stats.health, info->dstats.health);
     return ;
 }
 
 static void ft_initialize_gear_and_feats(t_char * info)
 {
     (void)info;
     return ;
 }
 
 t_char *ft_chaos_crystal(const int index, const char **input, t_name *name,
                                         int exception)
 {
     int error = 0;
     t_char *info = static_cast<t_char *>(cma_malloc(sizeof(t_char)));
 
     if (!info)
     {
         pf_printf_fd(2, "105-Error: Failed to allocate memory info %s\n", input[0]);
         return (ft_nullptr);
     }
-    *info = VERAAK_INFO;
+    ft_initialize_character_template(info, &CHAOS_CRYSTAL_INFO);
     info->name = input[0];
     info->struct_name = name;
     info->save_file = cma_strjoin("data/", input[0]);
     if (!info->save_file)
     {
         ft_free_info(info);
         return (ft_nullptr);
     }
     if (index == 2)
     {
         if (ft_strcmp(input[1], "init") == 0)
         {
             ft_file file(info->save_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
             if (file.get_error())
             {
                 pf_printf_fd(2, "123-Error opening file %s: %s\n", info->save_file,
                     file.get_error_str());
                 return (ft_nullptr);
             }
             ft_npc_write_file(info, &info->dstats, &info->d_resistance, file);
             pf_printf("Stats for %s written on a file\n", info->name);
             ft_free_info(info);
             return (ft_nullptr);
         }
     }
diff --git a/chaos_crystal.hpp b/chaos_crystal.hpp
index 0f6ed31fffb9b4aac7a8e390919f93bbc5d8873f..019c666fee559c83fe081b2e7bc732881910c4d2 100644
--- a/chaos_crystal.hpp
+++ b/chaos_crystal.hpp
@@ -114,42 +114,42 @@ static const t_physical CHAOS_CRYSTAL_PHYSICAL =
     .height = 60,
     .weight = 500,
     .age = 200,
     .speed = 0,
 };
 
 static const t_char CHAOS_CRYSTAL_INFO =
 {
     .level = 2,
     .mechanical = 1,
     .passive_perception = 15,
     .initiative = -1,
     .version_number = 2,
     .save_file = ft_nullptr,
     .name = ft_nullptr,
     .turn = ft_chaos_crystal_turn,
     .drop_loot = ft_nullptr,
     .loot = INITIALIZE_LOOT,
     .hit_dice = INITIALIZ_HIT_DICE,
     .inventory = INITIALIZE_INVENTORY,
     .spells = INITIALIZE_SPELLS,
     .spell_slots = INITIALIZE_SPELL_SLOTS,
     .flags = INITIALIZE_FLAGS,
     .crit = CHAOS_CRYSTAL_CRIT,
     .attack_bonus = CHAOS_CRYSTAL_ATTACK,
-    .bufs = INITIALIZE_BUFFS,
-    .debufs = INITIALIZE_DEBUFFS,
+    .bufs = ft_initialize_buffs(),
+    .debufs = ft_initialize_debuffs(),
     .concentration = INITIALIZE_CONCENTRATION,
     .d_resistance = CHAOS_CRYSTAL_DEFAULT_RESISTANCE,
     .c_resistance = INITIALIZE_CURRENT_RESISTANCE,
     .equipment = CHAOS_CRYSTAL_EQUIPMENT,
     .skill_mod = CHAOS_CRYSTAL_SKILL_MODS,
     .save_mod = CHAOS_CRYSTAL_SAVE_MODS,
     .stats = INITIALIZE_STATS,
     .dstats = CHAOS_CRYSTAL_DEFAULT_STATS,
     .feats = INITIALIZE_FEATS,
     .struct_name = ft_nullptr,
     .physical = CHAOS_CRYSTAL_PHYSICAL,
     .position = INITIALIZE_POSITION,
 };
 
 #endif
diff --git a/chaos_goblin.cpp b/chaos_goblin.cpp
index 338e8ecf765393d8bd2e4908e7eec4fe381f8d19..5df8a7ea2c5c4063db67c8b505204e3a9981f604 100644
--- a/chaos_goblin.cpp
+++ b/chaos_goblin.cpp
@@ -17,51 +17,51 @@ void ft_chaos_goblin_turn(t_char *info)
     else
     {
         pf_printf("The chaos_goblin will try to make either a ranged or melee attack " \
                 "during his turn\n");
     }
     pf_printf("Chaos_goblin currently has %d/%d hp\n", info->stats.health, info->dstats.health);
 }
 
 static void ft_initialize_gear_and_feats(t_char *info)
 {
     (void)info;
     return ;
 }
 
 t_char *ft_chaos_goblin(const int index, const char **input, t_name *name,
                                         int exception)
 {
     int error = 0;
     t_char *info = static_cast<t_char *>(cma_malloc(sizeof(t_char)));
 
     if (!info)
     {
         pf_printf_fd(2, "105-Error: Failed to allocate memory info %s\n", input[0]);
         return (ft_nullptr);
     }
-    *info = CHAOS_GOBLIN_INFO;
+    ft_initialize_character_template(info, &CHAOS_GOBLIN_INFO);
     info->name = input[0];
     info->struct_name = name;
     info->save_file = cma_strjoin("data/", input[0]);
     if (!info->save_file)
     {
         pf_printf_fd(2, "104-Error: Failed to allocate memory save_file name %s\n", info->name);
         ft_free_info(info);
         return (ft_nullptr);
     }
     if (index == 2)
     {
         if (ft_strcmp(input[1], "init") == 0)
         {
             ft_file file(info->save_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
             if (file.get_error())
             {
                 pf_printf_fd(2, "123-Error opening file %s: %s\n", info->save_file,
                     file.get_error_str());
                 return (ft_nullptr);
             }
             ft_npc_write_file(info, &info->dstats, &info->d_resistance, file);
             pf_printf("Stats for %s written on a file\n", info->name);
             ft_free_info(info);
             return (ft_nullptr);
         }
diff --git a/chaos_goblin.hpp b/chaos_goblin.hpp
index 9b94cb887b5daa409dc5cb0cbd8e6a547e51a000..89497285b0a4fdb3574017041dd736bafeff7b69 100644
--- a/chaos_goblin.hpp
+++ b/chaos_goblin.hpp
@@ -117,42 +117,42 @@ static const t_physical CHAOS_GOBLIN_PHYSICAL =
     .height = 48,
     .weight = 40,
     .age = 70,
     .speed = 30,
 };
 
 static const t_char CHAOS_GOBLIN_INFO =
 {
     .level = 2,
     .mechanical = 0,
     .passive_perception = 15,
     .initiative = -1,
     .version_number = 2,
     .save_file = ft_nullptr,
     .name = ft_nullptr,
     .turn = ft_chaos_goblin_turn,
     .drop_loot = ft_nullptr,
     .loot = INITIALIZE_LOOT,
     .hit_dice = INITIALIZ_HIT_DICE,
     .inventory = INITIALIZE_INVENTORY,
     .spells = INITIALIZE_SPELLS,
     .spell_slots = INITIALIZE_SPELL_SLOTS,
     .flags = INITIALIZE_FLAGS,
     .crit = CHAOS_GOBLIN_CRIT,
     .attack_bonus = CHAOS_GOBLIN_ATTACK,
-    .bufs = INITIALIZE_BUFFS,
-    .debufs = INITIALIZE_DEBUFFS,
+    .bufs = ft_initialize_buffs(),
+    .debufs = ft_initialize_debuffs(),
     .concentration = INITIALIZE_CONCENTRATION,
     .d_resistance = CHAOS_GOBLIN_DEFAULT_RESISTANCE,
     .c_resistance = INITIALIZE_CURRENT_RESISTANCE,
     .equipment = CHAOS_GOBLIN_EQUIPMENT,
     .skill_mod = CHAOS_GOBLIN_SKILL_MODS,
     .save_mod = CHAOS_GOBLIN_SAVE_MODS,
     .stats = INITIALIZE_STATS,
     .dstats = CHAOS_GOBLIN_DEFAULT_STATS,
     .feats = INITIALIZE_FEATS,
     .struct_name = ft_nullptr,
     .physical = CHAOS_GOBLIN_PHYSICAL,
     .position = INITIALIZE_POSITION,
 };
 
 #endif
diff --git a/demonic_portal_a.cpp b/demonic_portal_a.cpp
index 0bd7fbc74a6518523662f6959ede5c97b005b625..dc4a2dea2bdcd599c3df7a85a02a2efa84bce65f 100644
--- a/demonic_portal_a.cpp
+++ b/demonic_portal_a.cpp
@@ -1,98 +1,105 @@
 #include "dnd_tools.hpp"
 #include "demonic_portal_a.hpp"
 #include "libft/CPP_class/class_nullptr.hpp"
 #include "libft/Printf/printf.hpp"
 #include "libft/RNG/rng.hpp"
 #include "libft/CMA/CMA.hpp"
+#include "libft/Errno/errno.hpp"
 
 static void ft_portal_surge(t_char *info)
 {
     (void)info;
     int roll = ft_dice_roll(1, 5);
     if (roll == -1)
         return ;
     if (roll == 1)
         pf_printf("Portal Surge: Psychic shriek - DC15 Con save for all nearby or " \
                 "be stunned\n");
     else if (roll == 2)
         pf_printf("Portal Surge: Demonic tentacles - DC15 Dex save or be grappled\n");
     else if (roll == 3)
         pf_printf("Portal Surge: Vision flash - DC15 Wis save or suffer disadvantage " \
                 "on attacks\n");
     else if (roll == 4)
     {
-        char    **player_list;
-        int             i;
-        int             damage;
+        ft_vector<ft_string>    player_list = ft_get_pc_list();
+        int                     i;
+        int                     damage;
 
-        player_list = ft_get_pc_list();
-        if (!player_list)
+        if (player_list.get_error() != ER_SUCCESS || player_list.size() == 0)
+        {
+            player_list.clear();
             return ;
-        i = ft_double_char_length(const_cast<const char **>(player_list));
-        i = ft_dice_roll(1, i) - 1;
+        }
+        i = ft_dice_roll(1, static_cast<int>(player_list.size())) - 1;
+        if (i < 0)
+        {
+            player_list.clear();
+            return ;
+        }
         damage = ft_dice_roll(2, 6);
         pf_printf("Portal Surge: Arcane backlash hits %s for %d force damage\n",
-                player_list[i], damage);
-        cma_free_double(player_list);
+                player_list[static_cast<size_t>(i)].c_str(), damage);
+        player_list.clear();
     }
     else
         pf_printf("Portal Surge: Calm moment - no effect\n");
     return ;
 }
 
 void ft_demonic_portal_a_turn(t_char * info)
 {
     ft_update_buf(info);
     ft_portal_surge(info);
     pf_printf("%s currently has %d/%d hp\n", info->name, info->stats.health,
             info->dstats.health);
     return ;
 }
 
 static void ft_initialize_gear_and_feats(t_char * info)
 {
     (void)info;
     return ;
 }
 
 void    ft_demonic_portal_a_loot(t_char * info)
 {
     (void)info;
     return ;
 }
 
 t_char *ft_demonic_portal_a(const int index, const char **input, t_name *name, int exception)
 {
     int error = 0;
     t_char *info = static_cast<t_char *>(cma_malloc(sizeof(t_char)));
     if (!info)
     {
         pf_printf_fd(2, "105-Error: Failed to allocate memory info %s\n", input[0]);
         return (ft_nullptr);
     }
-    *info = DEMONIC_PORTAL_A_INFO;
+    ft_initialize_character_template(info, &DEMONIC_PORTAL_A_INFO);
     info->name = input[0];
     info->struct_name = name;
     info->save_file = cma_strjoin("data/", input[0]);
     if (!info->save_file)
     {
         ft_free_info(info);
         return (ft_nullptr);
     }
     if (index == 2)
     {
         if (ft_strcmp(input[1], "init") == 0)
         {
             int result = ft_dice_roll(info->hit_dice.dice_amount,
                     info->hit_dice.dice_faces);
             if (result == -1)
             {
                 pf_printf("147-Error Invalid hit dice %s", info->name);
                 ft_free_info(info);
                 return (ft_nullptr);
             }
             info->dstats.health = info->dstats.health + result;
             ft_file file(info->save_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR |
                     S_IWUSR);
             if (file.get_error())
             {
diff --git a/demonic_portal_a.hpp b/demonic_portal_a.hpp
index 4ef39693b81c615305005921376b976788cc5c11..62a2fdebc594120376d29d799a0d664150d603f3 100644
--- a/demonic_portal_a.hpp
+++ b/demonic_portal_a.hpp
@@ -149,52 +149,52 @@ static const t_inventory DEMONIC_PORTAL_A_INVENTORY
 constexpr t_hit_dice DEMONIC_PORTAL_A_HIT_DICE =
 {
     .dice_amount = 0,
     .dice_faces = 0,
 };
 
 static const t_char DEMONIC_PORTAL_A_INFO =
 {
     .level = 0,
     .mechanical = 0,
     .passive_perception = 15,
     .initiative = -1,
     .version_number = 2,
     .save_file = ft_nullptr,
     .name = ft_nullptr,
     .turn = ft_demonic_portal_a_turn,
     .drop_loot = ft_demonic_portal_a_loot,
     .loot = INITIALIZE_LOOT,
     .hit_dice = DEMONIC_PORTAL_A_HIT_DICE,
     .inventory = DEMONIC_PORTAL_A_INVENTORY,
     .spells = INITIALIZE_SPELLS,
     .spell_slots = DEMONIC_PORTAL_A_SPELL_SLOTS,
     .flags = INITIALIZE_FLAGS,
     .crit = DEMONIC_PORTAL_A_CRIT,
     .attack_bonus = DEMONIC_PORTAL_A_ATTACK,
-    .bufs = INITIALIZE_BUFFS,
-    .debufs = INITIALIZE_DEBUFFS,
+    .bufs = ft_initialize_buffs(),
+    .debufs = ft_initialize_debuffs(),
     .concentration = INITIALIZE_CONCENTRATION,
     .d_resistance = DEMONIC_PORTAL_A_DEFAULT_RESISTANCE,
     .c_resistance = INITIALIZE_CURRENT_RESISTANCE,
     .equipment = DEMONIC_PORTAL_A_EQUIPMENT,
     .skill_mod = DEMONIC_PORTAL_A_SKILL_MODS,
     .save_mod = DEMONIC_PORTAL_A_SAVE_MODS,
     .stats = INITIALIZE_STATS,
     .dstats = DEMONIC_PORTAL_A_DEFAULT_STATS,
     .feats = INITIALIZE_FEATS,
     .struct_name = ft_nullptr,
     .physical = DEMONIC_PORTAL_A_PHYSICAL,
     .position = INITIALIZE_POSITION,
 };
 
 template <int Amount, int Faces>
 struct ValidateHitDice
 {
     static_assert
     (
         ((Amount == 0 && Faces == 0) || (Amount >= 1 && Faces >= 1)) &&
         (Amount <= 40 && Faces <= 12),
         "Invalid DEMONIC_PORTAL_A_HIT_DICE values: Either both must be 0 or both at least 1, " \
             "and the dice amount must not exceed 40, the dice faces must not exceed 12."
     );
 };
diff --git a/dnd_tools.hpp b/dnd_tools.hpp
index 69fee59b35f72ca66ef6bb189f04ee4ee414995e..81d16f11521b8db0d754dbbf8decd391f0c1cfea 100644
--- a/dnd_tools.hpp
+++ b/dnd_tools.hpp
@@ -1,52 +1,56 @@
 #ifndef DND_TOOLS_H
 # define DND_TOOLS_H
 
 static_assert(sizeof(int) == 4, "Expected int to be 4 bytes");
 
 #include <cstdio>
 #include "libft/Libft/libft.hpp"
+#include "libft/CPP_class/class_string_class.hpp"
+#include "libft/Template/vector.hpp"
 #include "character.hpp"
 #include "player_character.hpp"
 #include "libft/CPP_class/class_file.hpp"
 
 # ifndef DEBUG
 #  define DEBUG 0
 # endif
 
 # define MAX_ERROR_COUNT 5
 # define MAX_PLAYERS 8
 # define MAX_COORDINATE 10000
 # define CRIT_SUCCES 999
 # define CRIT_FAIL -999
 # define RL_CRIT_SUCCES 1
 # define RL_SUCCES 2
 # define RL_FAIL 3
 # define RL_CRIT_FAIL 4
 
 extern bool g_dnd_test;
 
+void        ft_initialize_character_template(t_char * dst, const t_char * src);
+
 // NPC
 void        ft_npc_change_stats(t_char * info, int argument_count, const char **argument_vector);
 void        ft_npc_set_stat(t_char * info, const char **input);
 int         ft_npc_open_file(t_char * info);
 void        ft_npc_init_stats(t_char * info);
 
 // Template
 t_char      *ft_shadow_illusion(const int index, const char **input, t_name *name, int exception);
 void        ft_shadow_illusion_turn(t_char * info);
 void        ft_shadow_illusion_loot(t_char * info);
 
 // Shadow Illusion
 t_char      *ft_template(const int index, const char **input, t_name *name, int exception);
 void        ft_template_turn(t_char * info);
 void        ft_template_loot(t_char * info);
 
 // Felguard
 t_char      *ft_felguard(const int index, const char **input, t_name *name, int exception);
 void        ft_felguard_turn(t_char * info);
 void        ft_felguard_loot(t_char * info);
 
 // Mannoroth
     t_char  *ft_mannoroth(const int index, const char **input, t_name *name,
                 int exception);
     void    ft_mannoroth_turn(t_char * info);
@@ -141,52 +145,52 @@ void        ft_chaos_crystal_turn(t_char * info);
 // Chaos Goblin
 t_char      *ft_chaos_goblin(const int index, const char **input, t_name *name, int exception);
 void        ft_chaos_goblin_turn(t_char * info);
 
 // Grizz
 t_char      *ft_grizz(const int index, const char **input, t_name *name, int exception);
 void        ft_grizz_turn(t_char * info);
 
 // Veraak
 t_char      *ft_veraak(const int index, const char **input, t_name *name, int exception);
 void        ft_veraak_check_phase(t_char * info);
 void        ft_veraak_turn(t_char * info);
 
 // Dwarf Paladin
 t_char      *ft_dwarf_paladin(const int index, const char **input, t_name *name, int exception);
 void        ft_dwarf_paladin_turn(t_char * info);
 
 // Ancient Predatory Beast
 t_char      *ft_ancient_predatory_beast(const int index, const char **input, t_name *name,
                 int exception);
 void        ft_ancient_predatory_beast_turn(t_char * info);
 
 // Maverick
 t_char      *ft_maverick(const int index, const char **input, t_name *name, int exception);
 void        ft_maverick_turn(t_char * info);
-void        ft_maverick_print_s(int first, int second, t_char * info, char **player_list);
-void        ft_maverick_print_f(int first, int second, t_char * info, char **player_list);
+void        ft_maverick_print_s(int first, int second, t_char * info, ft_vector<ft_string> &player_list);
+void        ft_maverick_print_f(int first, int second, t_char * info, ft_vector<ft_string> &player_list);
 
 // Commands
 void        ft_request_input(t_name *name);
 
 // Print Abilities
 void        print_meteor_strike(const t_char * info);
 void        print_lightning_strike(const t_char * info);
 void        print_flame_geyser(const t_char * info);
 void        print_frost_breath(const t_char * info);
 void        print_lightning_strike_v2(const t_char * info);
 void        print_arcane_pounce(const t_char * info);
 void        print_earth_pounce(const t_char * info);
 void        print_shadow_illusion(const t_char * info);
 
 // Tester
 void        ft_test(t_name *name);
 int         ft_test_excecute(const char **input, int argc, t_name *name);
 
 // Tester Make input strings
 void        ft_excecute_test(const char *string1, t_name *name);
 void        ft_excecute_test(const char *string1, const char *string2, t_name *name);
 void        ft_excecute_test(const char *string1, const char *string2, const char *string3,
                 t_name *name);
 void        ft_excecute_test(const char *string1, const char *string2, const char *string3,
                 const char *string4, t_name *name);
@@ -380,60 +384,58 @@ void        ft_concentration_remove_bless(t_char *character, t_target_data *targ
 void        ft_cast_magic_drain(t_char *info, const char **input);
 int         ft_magic_drain_apply_debuff(t_char *target, const char **input, t_buff *buff);
 void        ft_concentration_remove_magic_drain(t_char *character, t_target_data *targets_data);
 
 // Resistance
 int         ft_get_resistance(t_char * info, const char *type);
 
 // Ability modifier
 int         ft_ability_mod(int ability_score);
 
 // Advantage or disadvantage
 void        ft_reroll(t_char * info, int *result);
 
 // Open and read
 int         ft_open_file_write_only(const char *filename, ft_file &file);
 
 // Utils
 int         ft_create_data_dir();
 int         ft_initialize_info(t_char * character, char **content);
 int         ft_check_value(const char *input);
 void        ft_print_character_status(t_char * info, int number, int temp);
 void        ft_skill_throw(t_char * info, const char *skill, int ability_mod, int save_mod);
 int         ft_set_stats(t_char * info, char **content);
 int         ft_check_stat(t_char * info, const char *stat, const size_t index);
 char        **ft_set_stats_con_targets(char *content, size_t ofset, char **data, t_char *info);
-int         ft_double_char_length(const char **double_char);
 void        ft_dual_save_file(t_char * info, t_char * target);
 char        *ft_strtrim_prefix(const char *s1, const char *prefix);
 const char  *ft_ordinal_suffix(int number);
 int         ft_check_equipment_slots(t_char * character);
 void        ft_initialize_suggestions_readline();
-char        **ft_get_pc_list();
-void        ft_remove_element(char **array, char *element, bool free_element);
+ft_vector<ft_string>    ft_get_pc_list();
 void        ft_add_element(const char ***array, const char *element);
-void        ft_get_random_target(char **player_list, char **target_field);
+void        ft_get_random_target(ft_vector<ft_string> &player_list, char **target_field);
 int         ft_check_player_entry(const char *entry);
 int         ft_set_stat_player(size_t key_len, const char **field, const char *content);
 int         ft_check_write_permissions(const char *filepath);
 t_char *    ft_validate_and_fetch_target(char *target_name, t_char * info, int *error_code);
 void        ft_initialize_variables(t_target_data *target_data);
 int         initialize_stat_key_value_pairs(t_char * info);
 t_char *    ft_get_info(const char *tf_name, t_name *name);
 
 // Check name
 int         ft_set_stats_check_name(const char *name);
 int         ft_check_player_character(const char *name);
 
 // Readline checks
 int         ft_readline_confirm(const char *mesage);
 int                     ft_readline_check_succes_or_fail(const char *message);
 int         ft_readline_spell_level(const char *message, t_char * character,
                 int *invalid_input_amount);
 
 // Dice rolling
 int         ft_saving_throw(t_char * info, const char *ability_score, int ability_mod, int save_mod);
 
 // Free memory
 void        ft_free_pc(t_pc *player);
 int         ft_free_players(t_pc *players);
 void        ft_free_info(t_char * info);
diff --git a/dorgar_stoneguard.cpp b/dorgar_stoneguard.cpp
index 409e4c5375ab5826fb6754f78b34c425f40761f2..4ad6c8c9a7763a5b3244076df350a0f4b81098a6 100644
--- a/dorgar_stoneguard.cpp
+++ b/dorgar_stoneguard.cpp
@@ -13,51 +13,51 @@ void ft_dorgar_stoneguard_turn(t_char * info)
     }
     else
         pf_printf("%s will try to make either a ranged or melee " \
                 "attack during his turn\n", info->name);
     pf_printf("%s currently has %d/%d hp\n", info->name, info->stats.health, info->dstats.health);
     return ;
 }
 
 static void ft_initialize_gear_and_feats(t_char * info)
 {
     info->feats.crackback.active = 1;
     return ;
 }
 
 t_char *ft_dorgar_stoneguard(const int index, const char **input, t_name *name,
                                             int exception)
 {
     int error = 0;
     t_char *info = static_cast<t_char *>(cma_malloc(sizeof(t_char)));
 
     if (!info)
     {
         pf_printf_fd(2, "105-Error: Failed to allocate memory info %s\n", input[0]);
         return (ft_nullptr);
     }
-    *info = DORGAR_STONEGUARD_INFO;
+    ft_initialize_character_template(info, &DORGAR_STONEGUARD_INFO);
     info->name = input[0];
     info->struct_name = name;
     info->save_file = cma_strjoin("data/", input[0]);
     if (!info->save_file)
     {
         ft_free_info(info);
         return (ft_nullptr);
     }
     if (index == 2)
     {
         if (ft_strcmp(input[1], "init") == 0)
         {
             ft_file file(info->save_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
             if (file.get_error())
             {
                 pf_printf_fd(2, "123-Error opening file %s: %s\n", info->save_file,
                     file.get_error_str());
                 return (ft_nullptr);
             }
             ft_npc_write_file(info, &info->dstats, &info->d_resistance, file);
             pf_printf("Stats for %s written on a file\n", info->name);
             ft_free_info(info);
             return (ft_nullptr);
         }
     }
diff --git a/dorgar_stoneguard.hpp b/dorgar_stoneguard.hpp
index 8f30c8c7331f6d715b0eb0bd270ee3bf07ec6186..72d4fce9f592abe4570a0daf61efe0b9bc7f6f28 100644
--- a/dorgar_stoneguard.hpp
+++ b/dorgar_stoneguard.hpp
@@ -114,42 +114,42 @@ static const    t_physical DORGAR_STONEGUARD_PHYSICAL =
     .height = 48,
     .weight = 150,
     .age = 100,
     .speed = 25,
 };
 
 static const    t_char DORGAR_STONEGUARD_INFO =
 {
     .level = 0,
     .mechanical = 0,
     .passive_perception = 12,
     .initiative = -1,
     .version_number = 2,
     .save_file = ft_nullptr,
     .name = ft_nullptr,
     .turn = ft_dorgar_stoneguard_turn,
     .drop_loot = ft_nullptr,
     .loot = INITIALIZE_LOOT,
     .hit_dice = INITIALIZ_HIT_DICE,
     .inventory = INITIALIZE_INVENTORY,
     .spells = INITIALIZE_SPELLS,
     .spell_slots = INITIALIZE_SPELL_SLOTS,
     .flags = INITIALIZE_FLAGS,
     .crit = DORGAR_STONEGUARD_CRIT,
     .attack_bonus = DORGAR_STONEGUARD_ATTACK,
-    .bufs = INITIALIZE_BUFFS,
-    .debufs = INITIALIZE_DEBUFFS,
+    .bufs = ft_initialize_buffs(),
+    .debufs = ft_initialize_debuffs(),
     .concentration = INITIALIZE_CONCENTRATION,
     .d_resistance = DORGAR_STONEGUARD_DEFAULT_RESISTANCE,
     .c_resistance = INITIALIZE_CURRENT_RESISTANCE,
     .equipment = DORGAR_STONEGUARD_EQUIPMENT,
     .skill_mod = DORGAR_STONEGUARD_SKILL_MODS,
     .save_mod = DORGAR_STONEGUARD_SAVE_MODS,
     .stats = INITIALIZE_STATS,
     .dstats = DORGAR_STONEGUARD_DEFAULT_STATS,
     .feats = INITIALIZE_FEATS,
     .struct_name = ft_nullptr,
     .physical = DORGAR_STONEGUARD_PHYSICAL,
     .position = INITIALIZE_POSITION,
 };
 
 #endif
diff --git a/dwarf_paladin.cpp b/dwarf_paladin.cpp
index 15bbdbd10e951036927ccea7969c08b8f1270e5c..fe40f8a0881734e5650a17bb51e14006cd8d5bfc 100644
--- a/dwarf_paladin.cpp
+++ b/dwarf_paladin.cpp
@@ -16,51 +16,51 @@ void ft_dwarf_paladin_turn(t_char * info)
                 info->name);
     pf_printf("%s currently has %d/%d hp\n", info->name, info->stats.health, info->dstats.health);
     return ;
 }
 
 static void ft_initialize_gear_and_feats(t_char * info)
 {
     info->feats.crackback.active = 1;
     info->spells.cure_wounds = DWARF_PALADIN_SPELL_CURE_WOUNDS;
     info->spells.bless = DWARF_PALADIN_SPELL_BLESS;
     info->spells.divine_smite = DWARF_PALADIN_SPELL_DIVINE_SMITE;
     return ;
 }
 
 t_char *ft_dwarf_paladin(const int index, const char **input, t_name *name,
         int exception)
 {
     int error = 0;
     t_char *info = static_cast<t_char *>(cma_malloc(sizeof(t_char)));
 
     if (!info)
     {
         pf_printf_fd(2, "105-Error: Failed to allocate memory info %s\n", input[0]);
         return (ft_nullptr);
     }
-    *info = DWARF_PALADIN_INFO;
+    ft_initialize_character_template(info, &DWARF_PALADIN_INFO);
     info->name = input[0];
     info->struct_name = name;
     info->save_file = cma_strjoin("data/", input[0]);
     if (!info->save_file)
     {
         ft_free_info(info);
         return (ft_nullptr);
     }
     if (index == 2)
     {
         if (ft_strcmp(input[1], "init") == 0)
         {
             ft_file file(info->save_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
             if (file.get_error())
             {
                 pf_printf_fd(2, "123-Error opening file %s: %s\n", info->save_file,
                     file.get_error_str());
                 return (ft_nullptr);
             }
             ft_npc_write_file(info, &info->dstats, &info->d_resistance, file);
             pf_printf("Stats for %s written on a file\n", info->name);
             ft_free_info(info);
             return (ft_nullptr);
         }
     }
diff --git a/dwarf_paladin.hpp b/dwarf_paladin.hpp
index 4474b030f29762b8acb1b27a52941cf8dccd80d3..df106f1016588483d4c488c2750cd5a391a584f8 100644
--- a/dwarf_paladin.hpp
+++ b/dwarf_paladin.hpp
@@ -187,42 +187,42 @@ static const t_spell_bless DWARF_PALADIN_SPELL_BLESS =
     .upcast_extra_targets = 1,
     .upcast_extra_duration = 10,
     .upcast_extra_dice_faces = 0,
     .upcast_extra_dice_amount = 0,
 };
 
 static const t_char DWARF_PALADIN_INFO =
 {
     .level = 0,
     .mechanical = 0,
     .passive_perception = 15,
     .initiative = -1,
     .version_number = 2,
     .save_file = ft_nullptr,
     .name = ft_nullptr,
     .turn = ft_dwarf_paladin_turn,
     .drop_loot = ft_nullptr,
     .loot = INITIALIZE_LOOT,
     .hit_dice = INITIALIZ_HIT_DICE,
     .inventory = INITIALIZE_INVENTORY,
     .spells = INITIALIZE_SPELLS,
     .spell_slots = DWARF_PALADIN_SPELL_SLOTS,
     .flags = INITIALIZE_FLAGS,
     .crit = DWARF_PALADIN_CRIT,
     .attack_bonus = DWARF_PALADIN_ATTACK,
-    .bufs = INITIALIZE_BUFFS,
-    .debufs = INITIALIZE_DEBUFFS,
+    .bufs = ft_initialize_buffs(),
+    .debufs = ft_initialize_debuffs(),
     .concentration = INITIALIZE_CONCENTRATION,
     .d_resistance = DWARF_PALADIN_DEFAULT_RESISTANCE,
     .c_resistance = INITIALIZE_CURRENT_RESISTANCE,
     .equipment = DWARF_PALADIN_EQUIPMENT,
     .skill_mod = DWARF_PALADIN_SKILL_MODS,
     .save_mod = DWARF_PALADIN_SAVE_MODS,
     .stats = INITIALIZE_STATS,
     .dstats = DWARF_PALADIN_DEFAULT_STATS,
     .feats = INITIALIZE_FEATS,
     .struct_name = ft_nullptr,
     .physical = DWARF_PALADIN_PHYSICAL,
     .position = INITIALIZE_POSITION,
 };
 
 #endif
diff --git a/felbeast.cpp b/felbeast.cpp
index 8664aeb55563ac38b131d3c8967aa2c5ba0a1421..287133fd9dda710e1b0a7b18a24aa41ff5789289 100644
--- a/felbeast.cpp
+++ b/felbeast.cpp
@@ -24,51 +24,51 @@ void ft_felbeast_turn(t_char * info)
 
 static void ft_initialize_gear_and_feats(t_char * info)
 {
     info->spells.magic_drain = FELBEAST_SPELL_MAGIC_DRAIN;
     info->equipment.armor = FELBEAST_HIDE;
     info->equipment.weapon = FELBEAST_CLAW;
     info->equipment.offhand_weapon = FELBEAST_CLAW_OH;
     return ;
 }
 
 void    ft_felbeast_loot(t_char * info)
 {
     (void)info;
     return ;
 }
 
 t_char *ft_felbeast(const int index, const char **input, t_name *name, int exception)
 {
     int error = 0;
     t_char *info = static_cast<t_char *>(cma_malloc(sizeof(t_char)));
     if (!info)
     {
         pf_printf_fd(2, "105-Error: Failed to allocate memory info %s\n", input[0]);
         return (ft_nullptr);
     }
-    *info = FELBEAST_INFO;
+    ft_initialize_character_template(info, &FELBEAST_INFO);
     info->name = input[0];
     info->struct_name = name;
     info->save_file = cma_strjoin("data/", input[0]);
     if (!info->save_file)
     {
         ft_free_info(info);
         return (ft_nullptr);
     }
     if (index == 2)
     {
         if (ft_strcmp(input[1], "init") == 0)
         {
             int result = ft_dice_roll(info->hit_dice.dice_amount, info->hit_dice.dice_faces);
             if (result == -1)
             {
                 pf_printf("147-Error Invalid hit dice %s", info->name);
                 ft_free_info(info);
                 return (ft_nullptr);
             }
             info->dstats.health = info->dstats.health + result;
             ft_file file(info->save_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
             if (file.get_error())
             {
                 pf_printf_fd(2, "123-Error opening file %s: %s\n", info->save_file,
                     file.get_error_str());
diff --git a/felbeast.hpp b/felbeast.hpp
index d1ae2f71fe72e8fee9d6ae9efe4342068945d20c..cff8cdef1ee0419d7234e2fa4dc93b4572cdfcbb 100644
--- a/felbeast.hpp
+++ b/felbeast.hpp
@@ -149,52 +149,52 @@ static const t_inventory FELBEAST_INVENTORY
 constexpr t_hit_dice FELBEAST_HIT_DICE =
 {
     .dice_amount = 0,
     .dice_faces = 0,
 };
 
 static const t_char FELBEAST_INFO =
 {
     .level = 0,
     .mechanical = 0,
     .passive_perception = 15,
     .initiative = -1,
     .version_number = 2,
     .save_file = ft_nullptr,
     .name = ft_nullptr,
     .turn = ft_felbeast_turn,
     .drop_loot = ft_felbeast_loot,
     .loot = INITIALIZE_LOOT,
     .hit_dice = FELBEAST_HIT_DICE,
     .inventory = FELBEAST_INVENTORY,
     .spells = INITIALIZE_SPELLS,
     .spell_slots = FELBEAST_SPELL_SLOTS,
     .flags = INITIALIZE_FLAGS,
     .crit = FELBEAST_CRIT,
     .attack_bonus = FELBEAST_ATTACK,
-    .bufs = INITIALIZE_BUFFS,
-    .debufs = INITIALIZE_DEBUFFS,
+    .bufs = ft_initialize_buffs(),
+    .debufs = ft_initialize_debuffs(),
     .concentration = INITIALIZE_CONCENTRATION,
     .d_resistance = FELBEAST_DEFAULT_RESISTANCE,
     .c_resistance = INITIALIZE_CURRENT_RESISTANCE,
     .equipment = FELBEAST_EQUIPMENT,
     .skill_mod = FELBEAST_SKILL_MODS,
     .save_mod = FELBEAST_SAVE_MODS,
     .stats = INITIALIZE_STATS,
     .dstats = FELBEAST_DEFAULT_STATS,
     .feats = INITIALIZE_FEATS,
     .struct_name = ft_nullptr,
     .physical = FELBEAST_PHYSICAL,
     .position = INITIALIZE_POSITION,
 };
 
 template <int Amount, int Faces>
 struct ValidateHitDice
 {
     static_assert
     (
         ((Amount == 0 && Faces == 0) || (Amount >= 1 && Faces >= 1)) &&
         (Amount <= 40 && Faces <= 12),
         "Invalid FELBEAST_HIT_DICE values: Either both must be 0 or both at least 1, " \
             "and the dice amount must not exceed 40, the dice faces must not exceed 12."
     );
 };
diff --git a/felguard.cpp b/felguard.cpp
index 36f07f1df00d343319d7d08647d0f4b7949aac1f..1e33c90e2140b50c7939afa25ca3e065c0f8cda9 100644
--- a/felguard.cpp
+++ b/felguard.cpp
@@ -19,51 +19,51 @@ void ft_felguard_turn(t_char * info)
     pf_printf("%s currently has %d/%d hp\n", info->name, info->stats.health, info->dstats.health);
     return ;
 }
 
 static void ft_initialize_gear_and_feats(t_char * info)
 {
     (void)info;
     return ;
 }
 
 void    ft_felguard_loot(t_char * info)
 {
     (void)info;
     return ;
 }
 
 t_char *ft_felguard(const int index, const char **input, t_name *name, int exception)
 {
     int error = 0;
     t_char *info = static_cast<t_char *>(cma_malloc(sizeof(t_char)));
     if (!info)
     {
         pf_printf_fd(2, "105-Error: Failed to allocate memory info %s\n", input[0]);
         return (ft_nullptr);
     }
-    *info = FELGUARD_INFO;
+    ft_initialize_character_template(info, &FELGUARD_INFO);
     info->name = input[0];
     info->struct_name = name;
     info->save_file = cma_strjoin("data/", input[0]);
     if (!info->save_file)
     {
         ft_free_info(info);
         return (ft_nullptr);
     }
     if (index == 2)
     {
         if (ft_strcmp(input[1], "init") == 0)
         {
             int result = ft_dice_roll(info->hit_dice.dice_amount, info->hit_dice.dice_faces);
             if (result == -1)
             {
                 pf_printf("147-Error Invalid hit dice %s", info->name);
                 ft_free_info(info);
                 return (ft_nullptr);
             }
             info->dstats.health = info->dstats.health + result;
             ft_file file(info->save_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
             if (file.get_error())
             {
                 pf_printf_fd(2, "123-Error opening file %s: %s\n", info->save_file,
                     file.get_error_str());
diff --git a/felguard.hpp b/felguard.hpp
index 997c722473fa2e074bb805aedfaddde0c3049c3e..c72554ad3cd501623d7e410e224a620d3e3c5683 100644
--- a/felguard.hpp
+++ b/felguard.hpp
@@ -149,52 +149,52 @@ static const t_inventory FELGUARD_INVENTORY
 constexpr t_hit_dice FELGUARD_HIT_DICE =
 {
     .dice_amount = 0,
     .dice_faces = 0,
 };
 
 static const t_char FELGUARD_INFO =
 {
     .level = 0,
     .mechanical = 0,
     .passive_perception = 15,
     .initiative = -1,
     .version_number = 2,
     .save_file = ft_nullptr,
     .name = ft_nullptr,
     .turn = ft_felguard_turn,
     .drop_loot = ft_felguard_loot,
     .loot = INITIALIZE_LOOT,
     .hit_dice = FELGUARD_HIT_DICE,
     .inventory = FELGUARD_INVENTORY,
     .spells = INITIALIZE_SPELLS,
     .spell_slots = FELGUARD_SPELL_SLOTS,
     .flags = INITIALIZE_FLAGS,
     .crit = FELGUARD_CRIT,
     .attack_bonus = FELGUARD_ATTACK,
-    .bufs = INITIALIZE_BUFFS,
-    .debufs = INITIALIZE_DEBUFFS,
+    .bufs = ft_initialize_buffs(),
+    .debufs = ft_initialize_debuffs(),
     .concentration = INITIALIZE_CONCENTRATION,
     .d_resistance = FELGUARD_DEFAULT_RESISTANCE,
     .c_resistance = INITIALIZE_CURRENT_RESISTANCE,
     .equipment = FELGUARD_EQUIPMENT,
     .skill_mod = FELGUARD_SKILL_MODS,
     .save_mod = FELGUARD_SAVE_MODS,
     .stats = INITIALIZE_STATS,
     .dstats = FELGUARD_DEFAULT_STATS,
     .feats = INITIALIZE_FEATS,
     .struct_name = ft_nullptr,
     .physical = FELGUARD_PHYSICAL,
     .position = INITIALIZE_POSITION,
 };
 
 template <int Amount, int Faces>
 struct ValidateHitDice
 {
     static_assert
     (
         ((Amount == 0 && Faces == 0) || (Amount >= 1 && Faces >= 1)) &&
         (Amount <= 40 && Faces <= 12),
         "Invalid FELGUARD_HIT_DICE values: Either both must be 0 or both at least 1, " \
             "and the dice amount must not exceed 40, the dice faces must not exceed 12."
     );
 };
diff --git a/frank.cpp b/frank.cpp
index 6e575a76e1f8367e1fd00e71f44f376f6bea7e62..94930802e71a1661240a957dbb09869206c666f1 100644
--- a/frank.cpp
+++ b/frank.cpp
@@ -31,51 +31,51 @@ void ft_frank_turn(t_char * info)
         print_lightning_strike_v2(info);
     }
     if (info->stats.turn == 3)
         info->stats.turn = 1;
     else
         info->stats.turn++;
     return ;
 }
 
 static void ft_initialize_gear_and_feats(t_char * info)
 {
     (void)info;
     return ;
 }
 
 t_char *ft_frank(const int index, const char **input, t_name *name, int exception)
 {
     int error = 0;
     t_char *info = static_cast<t_char *>(cma_malloc(sizeof(t_char)));
 
     if (!info)
     {
         pf_printf_fd(2, "105-Error: Failed to allocate memory info %s\n", input[0]);
         return (ft_nullptr);
     }
-    *info = FRANK_INFO;
+    ft_initialize_character_template(info, &FRANK_INFO);
     info->name = input[0];
     info->struct_name = name;
     info->save_file = cma_strjoin("data/", input[0]);
     if (!info->save_file)
     {
         ft_free_info(info);
         return (ft_nullptr);
     }
     if (index == 2)
     {
         if (ft_strcmp(input[1], "init") == 0)
         {
             ft_file file(info->save_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
             if (file.get_error())
             {
                 pf_printf_fd(2, "123-Error opening file %s: %s\n", info->save_file,
                     file.get_error_str());
                 return (ft_nullptr);
             }
             ft_npc_write_file(info, &info->dstats, &info->d_resistance, file);
             pf_printf("Stats for %s written on a file\n", info->name);
             ft_free_info(info);
             return (ft_nullptr);
         }
     }
diff --git a/frank.hpp b/frank.hpp
index 6dfcec7988e294d52da9f852bdfd30d2984010fd..96cd674fe7ff57383d70f72779551b3da0f2eba4 100644
--- a/frank.hpp
+++ b/frank.hpp
@@ -116,42 +116,42 @@ static const t_physical FRANK_PHYSICAL =
     .height = 110,
     .weight = 60,
     .age = 6,
     .speed = 50,
 };
 
 static const t_char FRANK_INFO =
 {
     .level = 0,
     .mechanical = 0,
     .passive_perception = 15,
     .initiative = -1,
     .version_number = 2,
     .save_file = ft_nullptr,
     .name = ft_nullptr,
     .turn = ft_frank_turn,
     .drop_loot = ft_nullptr,
     .loot = INITIALIZE_LOOT,
     .hit_dice = INITIALIZ_HIT_DICE,
     .inventory = INITIALIZE_INVENTORY,
     .spells = INITIALIZE_SPELLS,
     .spell_slots = INITIALIZE_SPELL_SLOTS,
     .flags = INITIALIZE_FLAGS,
     .crit = FRANK_CRIT,
     .attack_bonus = FRANK_ATTACK,
-    .bufs = INITIALIZE_BUFFS,
-    .debufs = INITIALIZE_DEBUFFS,
+    .bufs = ft_initialize_buffs(),
+    .debufs = ft_initialize_debuffs(),
     .concentration = INITIALIZE_CONCENTRATION,
     .d_resistance = FRANK_DEFAULT_RESISTANCE,
     .c_resistance = INITIALIZE_CURRENT_RESISTANCE,
     .equipment = FRANK_EQUIPMENT,
     .skill_mod = FRANK_SKILL_MODS,
     .save_mod = FRANK_SAVE_MODS,
     .stats = INITIALIZE_STATS,
     .dstats = FRANK_DEFAULT_STATS,
     .feats = INITIALIZE_FEATS,
     .struct_name = ft_nullptr,
     .physical = FRANK_PHYSICAL,
     .position = INITIALIZE_POSITION,
 };
 
 #endif
diff --git a/get_pc_list.cpp b/get_pc_list.cpp
index 9d62eab382b739af97aecb1da7a745217f384217..90fda029a32db62bac4ea96e21ec55939ce8856d 100644
--- a/get_pc_list.cpp
+++ b/get_pc_list.cpp
@@ -1,65 +1,72 @@
 #include "dnd_tools.hpp"
-#include "libft/CMA/CMA.hpp"
 #include "libft/CPP_class/class_nullptr.hpp"
+#include "libft/Errno/errno.hpp"
 #include "libft/Libft/libft.hpp"
 #include "libft/Printf/printf.hpp"
 #include "libft/File/open_dir.hpp"
 #include <fcntl.h>
 #include <unistd.h>
 
 int ft_check_player_entry(const char *entry)
 {
     char *filename = cma_strjoin("data/", entry);
     if (!filename)
         return 1;
     if (access(filename, R_OK | W_OK) == 0)
     {
         cma_free(filename);
         return 1;
     }
     cma_free(filename);
     return 0;
 }
 
-char **ft_get_pc_list()
+ft_vector<ft_string>    ft_get_pc_list()
 {
-    file_dir *dir = file_opendir("data");
+    ft_vector<ft_string>    player_list;
+    file_dir                *dir;
+    file_dirent             *dir_entry;
+
+    dir = file_opendir("data");
     if (!dir)
-        return (ft_nullptr);
-    char **player_list = static_cast<char **>(cma_calloc(MAX_PLAYERS, sizeof(char *)));
-    if (!player_list)
-    {
-        file_closedir(dir);
-        return (ft_nullptr);
-    }
-    int player_count = 0;
-    file_dirent *dir_entry;
-    while ((dir_entry = file_readdir(dir)) != ft_nullptr && player_count < MAX_PLAYERS)
+        return (player_list);
+    dir_entry = ft_nullptr;
+    while ((dir_entry = file_readdir(dir)) != ft_nullptr
+        && player_list.size() < static_cast<size_t>(MAX_PLAYERS))
     {
         if (ft_strncmp("PC--", dir_entry->d_name, 4) == 0)
         {
-            char *player_name = cma_strdup(dir_entry->d_name + 4);
-            if (!player_name)
+            ft_string player_name(dir_entry->d_name + 4);
+            if (player_name.get_error() != ER_SUCCESS)
+            {
+                file_closedir(dir);
+                player_list.clear();
+                return (player_list);
+            }
+            player_list.push_back(player_name);
+            if (player_list.get_error() != ER_SUCCESS)
             {
-                cma_free_double(player_list);
                 file_closedir(dir);
-                return (ft_nullptr);
+                player_list.clear();
+                return (player_list);
             }
-            player_list[player_count++] = player_name;
         }
     }
     file_closedir(dir);
-    if (player_count == 0)
+    if (player_list.size() == 0)
     {
         pf_printf_fd(2, "Error: No player character found\n");
-        cma_free_double(player_list);
-        return ft_nullptr;
+        return (player_list);
     }
-    int index = 0;
-    while (DEBUG == 1 && player_list[index])
+    if (DEBUG == 1)
     {
-        pf_printf("player %i on the list is %s\n", index, player_list[index]);
-        index++;
+        size_t index = 0;
+        while (index < player_list.size())
+        {
+            pf_printf("player %i on the list is %s\n", static_cast<int>(index),
+                    player_list[index].c_str());
+            index++;
+        }
     }
     return (player_list);
 }
diff --git a/get_random_target.cpp b/get_random_target.cpp
index 5034596c885c8dad0fbf296b5350675d3a15de16..a6a1b43ba0e5f3c898f072e635133d9d2c2dbad9 100644
--- a/get_random_target.cpp
+++ b/get_random_target.cpp
@@ -1,13 +1,36 @@
 #include "dnd_tools.hpp"
+#include "libft/CPP_class/class_nullptr.hpp"
+#include "libft/CMA/CMA.hpp"
+#include "libft/Errno/errno.hpp"
 #include "libft/RNG/rng.hpp"
 
-void    ft_get_random_target(char **player_list, char **target_field)
+void    ft_get_random_target(ft_vector<ft_string> &player_list, char **target_field)
 {
-    int     length;
+    int                             dice_faces;
+    int                             index;
+    ft_vector<ft_string>::iterator  it;
 
-    length = ft_double_char_length(const_cast<const char **>(player_list));
-    int index = ft_dice_roll(1, length) - 1;
-    *target_field = player_list[index];
-    ft_remove_element(player_list, player_list[index], false);
+    if (!target_field || player_list.size() == 0)
+        return ;
+    dice_faces = static_cast<int>(player_list.size());
+    index = ft_dice_roll(1, dice_faces) - 1;
+    if (index < 0)
+        return ;
+    if (*target_field)
+    {
+        cma_free(*target_field);
+        *target_field = ft_nullptr;
+    }
+    *target_field = cma_strdup(player_list[index].c_str());
+    if (!*target_field)
+    {
+        player_list.clear();
+        return ;
+    }
+    it = player_list.begin();
+    it = it + index;
+    player_list.erase(it);
+    if (player_list.get_error() != ER_SUCCESS)
+        player_list.clear();
     return ;
 }
diff --git a/ghost.cpp b/ghost.cpp
index 128d51df5242ce501bb2c648cd63cf9938f72c12..d4175696f0749d0c3f3a6d6ab1208d4dca6897d4 100644
--- a/ghost.cpp
+++ b/ghost.cpp
@@ -18,51 +18,51 @@ void ft_ghost_turn(t_char * info)
     {
         pf_printf("%s lets out a terrifying screech!\n", info->name);
         pf_printf("All enemies within 15 feet must make a DC 14 Wisdom saving throw.\n");
         pf_printf("On a failed save, enemies are frightened and have disadvantage on " \
                 "their attack rolls against %s until the end of their next turn.\n", info->name);
     }
     pf_printf("%s currently has %d/%d HP.\n", info->name, info->stats.health, info->dstats.health);
     return ;
 }
 
 static void ft_initialize_gear_and_feats(t_char * info)
 {
     (void)info;
     return ;
 }
 
 t_char *ft_ghost(const int index, const char **input, t_name *name, int exception)
 {
     int error = 0;
     t_char *info = static_cast<t_char *>(cma_malloc(sizeof(t_char)));
     if (!info)
     {
         pf_printf_fd(2, "105-Error: Failed to allocate memory info %s\n", input[0]);
         return (ft_nullptr);
     }
-    *info = GHOST_INFO;
+    ft_initialize_character_template(info, &GHOST_INFO);
     info->name = input[0];
     info->struct_name = name;
     info->save_file = cma_strjoin("data/", input[0]);
     if (!info->save_file)
     {
         ft_free_info(info);
         return (ft_nullptr);
     }
     if (index == 2)
     {
         if (ft_strcmp(input[1], "init") == 0)
         {
             ft_file file(info->save_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
             if (file.get_error())
             {
                 pf_printf_fd(2, "123-Error opening file %s: %s\n", info->save_file,
                     file.get_error_str());
                 return (ft_nullptr);
             }
             ft_npc_write_file(info, &info->dstats, &info->d_resistance, file);
             pf_printf("Stats for %s written on a file\n", info->name);
             ft_free_info(info);
             return (ft_nullptr);
         }
     }
diff --git a/ghost.hpp b/ghost.hpp
index 9c0c05616b6697c7faf012eefa505c8697c3d501..09da2bfe5d4e555cc52a49e8928c746834ecde42 100644
--- a/ghost.hpp
+++ b/ghost.hpp
@@ -129,42 +129,42 @@ static const t_spell_slots GHOST_SPELL_SLOTS =
     .level_7 = INITIALIZE_SPELL_SLOT,
     .level_8 = INITIALIZE_SPELL_SLOT,
     .level_9 = INITIALIZE_SPELL_SLOT,
     .warlock = INITIALIZE_SPELL_SLOT,
 };
 
 static const t_char GHOST_INFO =
 {
     .level = 0,
     .mechanical = 0,
     .passive_perception = 15,
     .initiative = -1,
     .version_number = 2,
     .save_file = ft_nullptr,
     .name = ft_nullptr,
     .turn = ft_ghost_turn,
     .drop_loot = ft_nullptr,
     .loot = INITIALIZE_LOOT,
     .hit_dice = INITIALIZ_HIT_DICE,
     .inventory = INITIALIZE_INVENTORY,
     .spells = INITIALIZE_SPELLS,
     .spell_slots = GHOST_SPELL_SLOTS,
     .flags = INITIALIZE_FLAGS,
     .crit = GHOST_CRIT,
     .attack_bonus = GHOST_ATTACK,
-    .bufs = INITIALIZE_BUFFS,
-    .debufs = INITIALIZE_DEBUFFS,
+    .bufs = ft_initialize_buffs(),
+    .debufs = ft_initialize_debuffs(),
     .concentration = INITIALIZE_CONCENTRATION,
     .d_resistance = GHOST_DEFAULT_RESISTANCE,
     .c_resistance = INITIALIZE_CURRENT_RESISTANCE,
     .equipment = GHOST_EQUIPMENT,
     .skill_mod = GHOST_SKILL_MODS,
     .save_mod = GHOST_SAVE_MODS,
     .stats = INITIALIZE_STATS,
     .dstats = GHOST_DEFAULT_STATS,
     .feats = INITIALIZE_FEATS,
     .struct_name = ft_nullptr,
     .physical = GHOST_PHYSICAL,
     .position = INITIALIZE_POSITION,
 };
 
 #endif
diff --git a/goblin.cpp b/goblin.cpp
index 1edaea9643832914f799b8bb835dcdcba3879e71..19a7f25dd5904432de19d7c2a623ff5502ec1aa8 100644
--- a/goblin.cpp
+++ b/goblin.cpp
@@ -13,51 +13,51 @@ void ft_goblin_turn(t_char *info)
         info->flags.prone = 0;
     }
     else
         pf_printf("The goblin will try to make either a ranged or melee attack during his turn\n");
     pf_printf("Goblin currently has %d/%d hp\n", info->stats.health, info->dstats.health);
     if (info->stats.health < info->dstats.health / 2)
         pf_printf("The goblin is on low health and can disengage as a bonus action\n");
     return ;
 }
 
 static void ft_initialize_gear_and_feats(t_char *info)
 {
     (void)info;
     return ;
 }
 
 t_char *ft_goblin(const int index, const char **input, t_name *name, int exception)
 {
     int error = 0;
     t_char *info = static_cast<t_char *>(cma_malloc(sizeof(t_char)));
     if (!info)
     {
         pf_printf_fd(2, "105-Error: Failed to allocate memory info %s\n", input[0]);
         return (ft_nullptr);
     }
-    *info = GOBLIN_INFO;
+    ft_initialize_character_template(info, &GOBLIN_INFO);
     info->name = input[0];
     info->struct_name = name;
     info->save_file = cma_strjoin("data/", input[0]);
     if (!info->save_file)
     {
         ft_free_info(info);
         return (ft_nullptr);
     }
     if (index == 2)
     {
         if (ft_strcmp(input[1], "init") == 0)
         {
             ft_file file(info->save_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
             if (file.get_error())
             {
                 pf_printf_fd(2, "123-Error opening file %s: %s\n", info->save_file,
                     file.get_error_str());
                 return (ft_nullptr);
             }
             ft_npc_write_file(info, &info->dstats, &info->d_resistance, file);
             pf_printf("Stats for %s written on a file\n", info->name);
             ft_free_info(info);
             return (ft_nullptr);
         }
     }
diff --git a/goblin.hpp b/goblin.hpp
index 1d13584ef9fc7a3fb24c42e7dc90e9a0431896ba..372330ee169b68205ac1d3169d19aa3256507136 100644
--- a/goblin.hpp
+++ b/goblin.hpp
@@ -116,42 +116,42 @@ static const t_physical GOBLIN_PHYSICAL =
     .height = 48,
     .weight = 40,
     .age = 15,
     .speed = 30,
 };
 
 static const t_char GOBLIN_INFO =
 {
     .level = 2,
     .mechanical = 0,
     .passive_perception = 12,
     .initiative = -1,
     .version_number = 2,
     .save_file = ft_nullptr,
     .name = ft_nullptr,
     .turn = ft_goblin_turn,
     .drop_loot = ft_nullptr,
     .loot = INITIALIZE_LOOT,
     .hit_dice = INITIALIZ_HIT_DICE,
     .inventory = INITIALIZE_INVENTORY,
     .spells = INITIALIZE_SPELLS,
     .spell_slots = INITIALIZE_SPELL_SLOTS,
     .flags = INITIALIZE_FLAGS,
     .crit = GOBLIN_CRIT,
     .attack_bonus = GOBLIN_ATTACK,
-    .bufs = INITIALIZE_BUFFS,
-    .debufs = INITIALIZE_DEBUFFS,
+    .bufs = ft_initialize_buffs(),
+    .debufs = ft_initialize_debuffs(),
     .concentration = INITIALIZE_CONCENTRATION,
     .d_resistance = GOBLIN_DEFAULT_RESISTANCE,
     .c_resistance = INITIALIZE_CURRENT_RESISTANCE,
     .equipment = GOBLIN_EQUIPMENT,
     .skill_mod = GOBLIN_SKILL_MODS,
     .save_mod = GOBLIN_SAVE_MODS,
     .stats = INITIALIZE_STATS,
     .dstats = GOBLIN_DEFAULT_STATS,
     .feats = INITIALIZE_FEATS,
     .struct_name = ft_nullptr,
     .physical = GOBLIN_PHYSICAL,
     .position = INITIALIZE_POSITION,
 };
 
 #endif
diff --git a/goblin_warmaster.cpp b/goblin_warmaster.cpp
index 8b401b505402b65b80c88bdb80c9b46cb78c7499..7869deb62893139bcff11834dfef666adb78f7ef 100644
--- a/goblin_warmaster.cpp
+++ b/goblin_warmaster.cpp
@@ -14,51 +14,51 @@ void ft_goblin_warmaster_turn(t_char * info)
     else
         pf_printf("The warmaster will attempt a strategic melee or ranged attack during his turn\n");
     pf_printf("Warmaster currently has %d/%d hp\n", info->stats.health, info->dstats.health);
     if (info->stats.health < info->dstats.health / 2)
         pf_printf("The warmaster is on low health and may use the command ability as " \
                 "a bonus action\n");
 }
 
 static void ft_initialize_gear_and_feats(t_char * info)
 {
     (void)info;
     return ;
 }
 
 t_char *ft_goblin_warmaster(const int index, const char **input, t_name *name,
                                             int exception)
 {
     int error = 0;
     t_char *info = static_cast<t_char *>(cma_malloc(sizeof(t_char)));
 
     if (!info)
     {
         pf_printf_fd(2, "105-Error: Failed to allocate memory info %s\n", input[0]);
         return (ft_nullptr);
     }
-    *info = GOBLIN_WARMASTER_INFO;
+    ft_initialize_character_template(info, &GOBLIN_WARMASTER_INFO);
     info->name = input[0];
     info->struct_name = name;
     info->save_file = cma_strjoin("data/", input[0]);
     if (!info->save_file)
     {
         ft_free_info(info);
         return (ft_nullptr);
     }
     if (index == 2)
     {
         if (ft_strcmp(input[1], "init") == 0)
         {
             ft_file file(info->save_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
             if (file.get_error())
             {
                 pf_printf_fd(2, "123-Error opening file %s: %s\n", info->save_file,
                     file.get_error_str());
                 return (ft_nullptr);
             }
             ft_npc_write_file(info, &info->dstats, &info->d_resistance, file);
             pf_printf("Stats for %s written on a file\n", info->name);
             ft_free_info(info);
             return (ft_nullptr);
         }
     }
diff --git a/goblin_warmaster.hpp b/goblin_warmaster.hpp
index 1ed770726d923b3f6bddaab7d0b5accb4ca992e9..e05827d0f1188d9b2d30116da861e4c965c1d9b8 100644
--- a/goblin_warmaster.hpp
+++ b/goblin_warmaster.hpp
@@ -115,42 +115,42 @@ static const t_physical GOBLIN_WARMASTER_PHYSICAL =
     .height = 52,
     .weight = 50,
     .age = 25,
     .speed = 25,
 };
 
 static const t_char GOBLIN_WARMASTER_INFO =
 {
     .level = 4,
     .mechanical = 0,
     .passive_perception = 14,
     .initiative = -1,
     .version_number = 2,
     .save_file = ft_nullptr,
     .name = ft_nullptr,
     .turn = ft_goblin_warmaster_turn,
     .drop_loot = ft_nullptr,
     .loot = INITIALIZE_LOOT,
     .hit_dice = INITIALIZ_HIT_DICE,
     .inventory = INITIALIZE_INVENTORY,
     .spells = INITIALIZE_SPELLS,
     .spell_slots = INITIALIZE_SPELL_SLOTS,
     .flags = INITIALIZE_FLAGS,
     .crit = GOBLIN_WARMASTER_CRIT,
     .attack_bonus = GOBLIN_WARMASTER_ATTACK,
-    .bufs = INITIALIZE_BUFFS,
-    .debufs = INITIALIZE_DEBUFFS,
+    .bufs = ft_initialize_buffs(),
+    .debufs = ft_initialize_debuffs(),
     .concentration = INITIALIZE_CONCENTRATION,
     .d_resistance = GOBLIN_WARMASTER_DEFAULT_RESISTANCE,
     .c_resistance = INITIALIZE_CURRENT_RESISTANCE,
     .equipment = GOBLIN_WARMASTER_EQUIPMENT,
     .skill_mod = GOBLIN_WARMASTER_SKILL_MODS,
     .save_mod = GOBLIN_WARMASTER_SAVE_MODS,
     .stats = INITIALIZE_STATS,
     .dstats = GOBLIN_WARMASTER_DEFAULT_STATS,
     .feats = INITIALIZE_FEATS,
     .struct_name = ft_nullptr,
     .physical = GOBLIN_WARMASTER_PHYSICAL,
     .position = INITIALIZE_POSITION,
 };
 
 #endif
diff --git a/grizz.cpp b/grizz.cpp
index bc835c2758dbfcc6ac5bdc555baa12661c18b6d7..2738d432b1dc37403040476f6cfbc14fb5a23fe8 100644
--- a/grizz.cpp
+++ b/grizz.cpp
@@ -19,51 +19,51 @@ void ft_grizz_turn(t_char * info)
     {
         pf_printf("%s uses Roar of the Grizz!\n", info->name);
         pf_printf("All enemies within 15 feet must make a DC 14 Wisdom saving throw.\n");
         pf_printf("On a failed save, enemies are frightened, imposing disadvantage on their " \
                 "attack rolls against Grizz until the end of their next turn.\n");
     }
     info->flags.reaction_used = 0;
     return ;
 }
 
 static void ft_initialize_gear_and_feats(t_char * info)
 {
     info->feats.crackback.active = 1;
     return ;
 }
 
 t_char *ft_grizz(const int index, const char **input, t_name *name, int exception)
 {
     int error = 0;
     t_char *info = static_cast<t_char *>(cma_malloc(sizeof(t_char)));
     if (!info)
     {
         pf_printf_fd(2, "105-Error: Failed to allocate memory info %s\n", input[0]);
         return (ft_nullptr);
     }
-    *info = GRIZZ_INFO;
+    ft_initialize_character_template(info, &GRIZZ_INFO);
     info->name = input[0];
     info->struct_name = name;
     info->save_file = cma_strjoin("data/", input[0]);
     if (!info->save_file)
     {
         ft_free_info(info);
         return (ft_nullptr);
     }
     if (index == 2)
     {
         if (ft_strcmp(input[1], "init") == 0)
         {
             ft_file file(info->save_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
             if (file.get_error())
             {
                 pf_printf_fd(2, "123-Error opening file %s: %s\n", info->save_file,
                     file.get_error_str());
                 return (ft_nullptr);
             }
             ft_npc_write_file(info, &info->dstats, &info->d_resistance, file);
             pf_printf("Stats for %s written on a file\n", info->name);
             ft_free_info(info);
             return (ft_nullptr);
         }
     }
diff --git a/grizz.hpp b/grizz.hpp
index cd860fc7f6b88b926492a696355a0b42bf215986..86f11eab61624ae6095c3708391334394efac538 100644
--- a/grizz.hpp
+++ b/grizz.hpp
@@ -117,42 +117,42 @@ static const t_physical GRIZZ_PHYSICAL =
     .height = 0,
     .weight = 0,
     .age = 0,
     .speed = 0,
 };
 
 static const t_char GRIZZ_INFO =
 {
     .level = 0,
     .mechanical = 0,
     .passive_perception = 15,
     .initiative = -1,
     .version_number = 2,
     .save_file = ft_nullptr,
     .name = ft_nullptr,
     .turn = ft_grizz_turn,
     .drop_loot = ft_nullptr,
     .loot = INITIALIZE_LOOT,
     .hit_dice = INITIALIZ_HIT_DICE,
     .inventory = INITIALIZE_INVENTORY,
     .spells = INITIALIZE_SPELLS,
     .spell_slots = INITIALIZE_SPELL_SLOTS,
     .flags = INITIALIZE_FLAGS,
     .crit = GRIZZ_CRIT,
     .attack_bonus = GRIZZ_ATTACK,
-    .bufs = INITIALIZE_BUFFS,
-    .debufs = INITIALIZE_DEBUFFS,
+    .bufs = ft_initialize_buffs(),
+    .debufs = ft_initialize_debuffs(),
     .concentration = INITIALIZE_CONCENTRATION,
     .d_resistance = GRIZZ_DEFAULT_RESISTANCE,
     .c_resistance = INITIALIZE_CURRENT_RESISTANCE,
     .equipment = GRIZZ_EQUIPMENT,
     .skill_mod = GRIZZ_SKILL_MODS,
     .save_mod = GRIZZ_SAVE_MODS,
     .stats = INITIALIZE_STATS,
     .dstats = GRIZZ_DEFAULT_STATS,
     .feats = INITIALIZE_FEATS,
     .struct_name = ft_nullptr,
     .physical = GRIZZ_PHYSICAL,
     .position = INITIALIZE_POSITION,
 };
 
 #endif
diff --git a/gundren_rockseeker.cpp b/gundren_rockseeker.cpp
index 19d04119e751a08c65cbba8d85df43a373bd88a3..0c07e07e02adfc6bc166059bd1b49cb18697f4d1 100644
--- a/gundren_rockseeker.cpp
+++ b/gundren_rockseeker.cpp
@@ -14,51 +14,51 @@ void ft_gundren_rockseeker_turn(t_char * info)
     }
     else
         pf_printf("%s will try to make either a ranged or melee " \
                 "attack during his turn\n", info->name);
     pf_printf("%s currently has %d/%d hp\n", info->name, info->stats.health, info->dstats.health);
     return ;
 }
 
 static void ft_initialize_gear_and_feats(t_char * info)
 {
     info->feats.crackback.active = 1;
     return ;
 }
 
 t_char *ft_gundren_rockseeker(const int index, const char **input, t_name *name,
                                             int exception)
 {
     int error = 0;
     t_char *info = static_cast<t_char *>(cma_malloc(sizeof(t_char)));
 
     if (!info)
     {
         pf_printf_fd(2, "105-Error: Failed to allocate memory info %s\n", input[0]);
         return (ft_nullptr);
     }
-    *info = GUNDREN_ROCKSEEKER_INFO;
+    ft_initialize_character_template(info, &GUNDREN_ROCKSEEKER_INFO);
     info->name = input[0];
     info->struct_name = name;
     info->save_file = cma_strjoin("data/", input[0]);
     if (!info->save_file)
     {
         ft_free_info(info);
         return (ft_nullptr);
     }
     if (index == 2)
     {
         if (ft_strcmp(input[1], "init") == 0)
         {
             ft_file file(info->save_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
             if (file.get_error())
             {
                 pf_printf_fd(2, "123-Error opening file %s: %s\n", info->save_file,
                     file.get_error_str());
                 return (ft_nullptr);
             }
             ft_npc_write_file(info, &info->dstats, &info->d_resistance, file);
             pf_printf("Stats for %s written on a file\n", info->name);
             ft_free_info(info);
             return (ft_nullptr);
         }
     }
diff --git a/gundren_rockseeker.hpp b/gundren_rockseeker.hpp
index f0eedab1046b57df8bd24314e502c179bfadce1b..ec3c0a7e3ea75db0de3d0f78b93cb73494809224 100644
--- a/gundren_rockseeker.hpp
+++ b/gundren_rockseeker.hpp
@@ -114,42 +114,42 @@ static const    t_physical GUNDREN_ROCKSEEKER_PHYSICAL =
     .height = 48,
     .weight = 150,
     .age = 100,
     .speed = 25,
 };
 
 static const    t_char GUNDREN_ROCKSEEKER_INFO =
 {
     .level = 0,
     .mechanical = 0,
     .passive_perception = 12,
     .initiative = -1,
     .version_number = 2,
     .save_file = ft_nullptr,
     .name = ft_nullptr,
     .turn = ft_gundren_rockseeker_turn,
     .drop_loot = ft_nullptr,
     .loot = INITIALIZE_LOOT,
     .hit_dice = INITIALIZ_HIT_DICE,
     .inventory = INITIALIZE_INVENTORY,
     .spells = INITIALIZE_SPELLS,
     .spell_slots = INITIALIZE_SPELL_SLOTS,
     .flags = INITIALIZE_FLAGS,
     .crit = GUNDREN_ROCKSEEKER_CRIT,
     .attack_bonus = GUNDREN_ROCKSEEKER_ATTACK,
-    .bufs = INITIALIZE_BUFFS,
-    .debufs = INITIALIZE_DEBUFFS,
+    .bufs = ft_initialize_buffs(),
+    .debufs = ft_initialize_debuffs(),
     .concentration = INITIALIZE_CONCENTRATION,
     .d_resistance = GUNDREN_ROCKSEEKER_DEFAULT_RESISTANCE,
     .c_resistance = INITIALIZE_CURRENT_RESISTANCE,
     .equipment = GUNDREN_ROCKSEEKER_EQUIPMENT,
     .skill_mod = GUNDREN_ROCKSEEKER_SKILL_MODS,
     .save_mod = GUNDREN_ROCKSEEKER_SAVE_MODS,
     .stats = INITIALIZE_STATS,
     .dstats = GUNDREN_ROCKSEEKER_DEFAULT_STATS,
     .feats = INITIALIZE_FEATS,
     .struct_name = ft_nullptr,
     .physical = GUNDREN_ROCKSEEKER_PHYSICAL,
     .position = INITIALIZE_POSITION,
 };
 
 #endif
diff --git a/hilda_stormshield.cpp b/hilda_stormshield.cpp
index 1b8236162ffd0b2ef8738b3ba4880abfcc98f9b6..7963113aba23e0fdae888fc0863e3fd8826eaec6 100644
--- a/hilda_stormshield.cpp
+++ b/hilda_stormshield.cpp
@@ -13,51 +13,51 @@ void ft_hilda_stormshield_turn(t_char * info)
     }
     else
         pf_printf("%s will try to make either a ranged or melee " \
                 "attack during his turn\n", info->name);
     pf_printf("%s currently has %d/%d hp\n", info->name, info->stats.health, info->dstats.health);
     return ;
 }
 
 static void ft_initialize_gear_and_feats(t_char * info)
 {
     info->feats.crackback.active = 1;
     return ;
 }
 
 t_char *ft_hilda_stormshield(const int index, const char **input, t_name *name,
                                             int exception)
 {
     int error = 0;
     t_char *info = static_cast<t_char *>(cma_malloc(sizeof(t_char)));
 
     if (!info)
     {
         pf_printf_fd(2, "105-Error: Failed to allocate memory info %s\n", input[0]);
         return (ft_nullptr);
     }
-    *info = HILDA_STORMSHIELD_INFO;
+    ft_initialize_character_template(info, &HILDA_STORMSHIELD_INFO);
     info->name = input[0];
     info->struct_name = name;
     info->save_file = cma_strjoin("data/", input[0]);
     if (!info->save_file)
     {
         ft_free_info(info);
         return (ft_nullptr);
     }
     if (index == 2)
     {
         if (ft_strcmp(input[1], "init") == 0)
         {
             ft_file file(info->save_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
             if (file.get_error())
             {
                 pf_printf_fd(2, "123-Error opening file %s: %s\n", info->save_file,
                     file.get_error_str());
                 return (ft_nullptr);
             }
             ft_npc_write_file(info, &info->dstats, &info->d_resistance, file);
             pf_printf("Stats for %s written on a file\n", info->name);
             ft_free_info(info);
             return (ft_nullptr);
         }
     }
diff --git a/hilda_stormshield.hpp b/hilda_stormshield.hpp
index dac47e350c86af1b5d5daee5fc1949da5e138686..60e621586689d9ae32713294ae51c31d9df8336a 100644
--- a/hilda_stormshield.hpp
+++ b/hilda_stormshield.hpp
@@ -114,42 +114,42 @@ static const    t_physical HILDA_STORMSHIELD_PHYSICAL =
     .height = 48,
     .weight = 150,
     .age = 100,
     .speed = 25,
 };
 
 static const    t_char HILDA_STORMSHIELD_INFO =
 {
     .level = 0,
     .mechanical = 0,
     .passive_perception = 12,
     .initiative = -1,
     .version_number = 2,
     .save_file = ft_nullptr,
     .name = ft_nullptr,
     .turn = ft_hilda_stormshield_turn,
     .drop_loot = ft_nullptr,
     .loot = INITIALIZE_LOOT,
     .hit_dice = INITIALIZ_HIT_DICE,
     .inventory = INITIALIZE_INVENTORY,
     .spells = INITIALIZE_SPELLS,
     .spell_slots = INITIALIZE_SPELL_SLOTS,
     .flags = INITIALIZE_FLAGS,
     .crit = HILDA_STORMSHIELD_CRIT,
     .attack_bonus = HILDA_STORMSHIELD_ATTACK,
-    .bufs = INITIALIZE_BUFFS,
-    .debufs = INITIALIZE_DEBUFFS,
+    .bufs = ft_initialize_buffs(),
+    .debufs = ft_initialize_debuffs(),
     .concentration = INITIALIZE_CONCENTRATION,
     .d_resistance = HILDA_STORMSHIELD_DEFAULT_RESISTANCE,
     .c_resistance = INITIALIZE_CURRENT_RESISTANCE,
     .equipment = HILDA_STORMSHIELD_EQUIPMENT,
     .skill_mod = HILDA_STORMSHIELD_SKILL_MODS,
     .save_mod = HILDA_STORMSHIELD_SAVE_MODS,
     .stats = INITIALIZE_STATS,
     .dstats = HILDA_STORMSHIELD_DEFAULT_STATS,
     .feats = INITIALIZE_FEATS,
     .struct_name = ft_nullptr,
     .physical = HILDA_STORMSHIELD_PHYSICAL,
     .position = INITIALIZE_POSITION,
 };
 
 #endif
diff --git a/initialize.hpp b/initialize.hpp
index 646d39417a40acf09cdc57bcc52f21363b864edc..ccc8a704c47949271a1de7b1aa9a7c676d313f65 100644
--- a/initialize.hpp
+++ b/initialize.hpp
@@ -161,58 +161,61 @@ static const    t_stats INITIALIZE_STATS =
     .inte = -1,
     .wis = -1,
     .cha = -1,
 };
 
 static const    t_position INITIALIZE_POSITION =
 {
     .x = 0,
     .y = 0,
     .z = 0,
 };
 
 static const    t_concentration INITIALIZE_CONCENTRATION =
 {
     .concentration = 0,
     .spell_id = 0,
     .dice_amount_mod = 0,
     .dice_faces_mod = 0,
     .extra = 0,
     .base_mod = 0,
     .duration = 0,
     .targets = ft_nullptr,
 };
 
 
-static const    t_buff_bless INITIALIZE_BUFF_BLESS =
+static t_buff_bless ft_initialize_buff_bless()
 {
-    .duration = 0,
-    .dice_amount_mod = 0,
-    .dice_faces_mod = 0,
-    .base_mod = 0,
-    .caster_name = ft_set<ft_string>(),
-};
+    t_buff_bless    bless;
+
+    bless.duration = 0;
+    bless.dice_amount_mod = 0;
+    bless.dice_faces_mod = 0;
+    bless.base_mod = 0;
+    bless.caster_name.clear();
+    return (bless);
+}
 
 static const    t_buff_protective_winds INITIALIZE_BUFF_PROTECTIVE_WINDS =
 {
     .duration = 0,
 };
 
 static const    t_buff_lightning_strike INITIALIZE_BUFF_LIGHTNING_STRIKE =
 {
     .duration = 0,
     .amount = 0,
     .distance = 0,
     .dice_amount = 0,
     .dice_faces = 0,
     .extra_damage = 0,
 };
 
 static const    t_buff_air_totem INITIALIZE_BUFF_AIR_TOTEM =
 {
     .save_file = ft_nullptr,
     .health = 0,
     .ac = 0,
     .knock_back_distance = 0,
     .erea_of_effect = 0,
 };
 
@@ -259,112 +262,124 @@ static const    t_buff_frost_breath INITIALIZE_BUFF_FROST_BREATH =
 {
     .active = 0,
     .damage = 0,
     .target_id = ft_nullptr,
 };
 
 static const    t_buff_shadow_illusion INITIALIZE_BUFF_SHADOW_ILLUSION =
 {
     .active = 0,
     .duration = 0,
 };
 
 static const    t_buff_rejuvenation INITIALIZE_BUFF_REJUVENATION =
 {
     .duration = 0,
     .healing_dice_amount = 0,
     .healing_dice_faces = 0,
     .healing_extra = 0,
 };
 static const    t_buff_growth INITIALIZE_BUFF_GROWTH =
 {
         .stacks = 0,
 };
 
 
-static const    t_bufs INITIALIZE_BUFFS =
+static inline t_bufs ft_initialize_buffs()
 {
-    .bless = INITIALIZE_BUFF_BLESS,
-    .protective_winds = INITIALIZE_BUFF_PROTECTIVE_WINDS,
-    .lightning_strike = INITIALIZE_BUFF_LIGHTNING_STRIKE,
-    .lightning_strikeV2 = INITIALIZE_BUFF_LIGHTNING_STRIKE,
-    .flame_geyser = INITIALIZE_BUFF_FLAME_GEYSER,
-    .meteor_strike = INITIALIZE_BUFF_METEOR_STRIKE,
-    .chaos_armor = INITIALIZE_BUFF_CHAOS_ARMOR,
-    .arcane_pounce = INITIALIZE_BUFF_ARCANE_POUNCE,
-    .earth_pounce = INITIALIZE_BUFF_EARTH_POUNCE,
-    .frost_breath = INITIALIZE_BUFF_FROST_BREATH,
-    .shadow_illusion = INITIALIZE_BUFF_SHADOW_ILLUSION,
-    .growth = INITIALIZE_BUFF_GROWTH,
-    .rejuvenation = INITIALIZE_BUFF_REJUVENATION,
-};
+    t_bufs  buffs;
+
+    buffs.bless = ft_initialize_buff_bless();
+    buffs.protective_winds = INITIALIZE_BUFF_PROTECTIVE_WINDS;
+    buffs.lightning_strike = INITIALIZE_BUFF_LIGHTNING_STRIKE;
+    buffs.lightning_strikeV2 = INITIALIZE_BUFF_LIGHTNING_STRIKE;
+    buffs.flame_geyser = INITIALIZE_BUFF_FLAME_GEYSER;
+    buffs.meteor_strike = INITIALIZE_BUFF_METEOR_STRIKE;
+    buffs.chaos_armor = INITIALIZE_BUFF_CHAOS_ARMOR;
+    buffs.arcane_pounce = INITIALIZE_BUFF_ARCANE_POUNCE;
+    buffs.earth_pounce = INITIALIZE_BUFF_EARTH_POUNCE;
+    buffs.frost_breath = INITIALIZE_BUFF_FROST_BREATH;
+    buffs.shadow_illusion = INITIALIZE_BUFF_SHADOW_ILLUSION;
+    buffs.growth = INITIALIZE_BUFF_GROWTH;
+    buffs.rejuvenation = INITIALIZE_BUFF_REJUVENATION;
+    return (buffs);
+}
 
-static const    t_debuff_hunters_mark INITIALIZE_HUNTERS_MARK =
+static t_debuff_hunters_mark ft_initialize_hunters_mark()
 {
-    .amount = 0,
-    .caster_name = ft_set<ft_string>(),
-};
+    t_debuff_hunters_mark    debuff;
+
+    debuff.amount = 0;
+    debuff.caster_name.clear();
+    return (debuff);
+}
 
 static const    t_debuff_blinded INITIALIZE_BLINDED =
 {
     .duration = 0,
 };
 
-static const    t_debuff_magic_drain INITIALIZE_DEBUFF_MAGIC_DRAIN =
+static t_debuff_magic_drain ft_initialize_debuff_magic_drain()
 {
-    .caster = ft_set<ft_string>(),
-    .amount = 0,
-    .damage_flat = 0,
-    .damage_dice_amount = 0,
-    .damage_dice_faces = 0,
-    .extra_damage_flat = 0,
-    .extra_dice_amount = 0,
-    .extra_dice_faces = 0,
-    .spell_slot_total_level_drain = 0,
-    .con_save = 0,
-};
+    t_debuff_magic_drain    debuff;
+
+    debuff.caster.clear();
+    debuff.amount = 0;
+    debuff.damage_flat = 0;
+    debuff.damage_dice_amount = 0;
+    debuff.damage_dice_faces = 0;
+    debuff.extra_damage_flat = 0;
+    debuff.extra_dice_amount = 0;
+    debuff.extra_dice_faces = 0;
+    debuff.spell_slot_total_level_drain = 0;
+    debuff.con_save = 0;
+    return (debuff);
+}
 
 static const    t_debuff_fell_poison INITIALIZE_FELL_POISON =
 {
     .duration = 0,
 };
 
 static const    t_debuff_shadow_touched INITIALIZE_SHADOW_TOUCHED =
 {
     .duration = 0,
     .stacks = 0,
     .armor_reduction_amount = 0,
 };
 
-static const    t_debufs INITIALIZE_DEBUFFS =
+static inline t_debufs ft_initialize_debuffs()
 {
-    .hunters_mark = INITIALIZE_HUNTERS_MARK,
-    .blinded = INITIALIZE_BLINDED,
-    .magic_drain = INITIALIZE_DEBUFF_MAGIC_DRAIN,
-    .fell_poison = INITIALIZE_FELL_POISON,
-    .shadow_touched = INITIALIZE_SHADOW_TOUCHED,
-};
+    t_debufs    debuffs;
+
+    debuffs.hunters_mark = ft_initialize_hunters_mark();
+    debuffs.blinded = INITIALIZE_BLINDED;
+    debuffs.magic_drain = ft_initialize_debuff_magic_drain();
+    debuffs.fell_poison = INITIALIZE_FELL_POISON;
+    debuffs.shadow_touched = INITIALIZE_SHADOW_TOUCHED;
+    return (debuffs);
+}
 
 static const    t_flags INITIALIZE_FLAGS =
 {
     .alreaddy_saved = 0,
     .error = 0,
     .flanking = 0,
     .advantage = 0,
     .prone = 0,
     .reaction_used = 0,
     .dont_save = 0,
 };
 
 static const     t_crackback INITIALIZE_CRACKBACK =
 {
     .active = 0,
 };
 
 static const     t_mighty_resilience INITIALIZE_MIGHTY_RESILIENCE =
 {
     .active = 0,
 };
 
 static const     t_feats INITIALIZE_FEATS =
 {
     .crackback = INITIALIZE_CRACKBACK,
diff --git a/initialize_character_template.cpp b/initialize_character_template.cpp
new file mode 100644
index 0000000000000000000000000000000000000000..9841e177e66dd24164b3c3c4598ad672f7d74f53
--- /dev/null
+++ b/initialize_character_template.cpp
@@ -0,0 +1,24 @@
+#include "dnd_tools.hpp"
+#include "initialize.hpp"
+#include <stddef.h>
+
+void    ft_initialize_character_template(t_char * dst, const t_char * src)
+{
+    unsigned char           *dst_bytes;
+    const unsigned char     *src_bytes;
+    size_t                  prefix_size;
+    size_t                  suffix_offset;
+
+    if (dst == ft_nullptr || src == ft_nullptr)
+        return ;
+    dst_bytes = reinterpret_cast<unsigned char *>(dst);
+    src_bytes = reinterpret_cast<const unsigned char *>(src);
+    prefix_size = offsetof(t_char, bufs);
+    ft_memcpy(dst_bytes, src_bytes, prefix_size);
+    dst->bufs = ft_initialize_buffs();
+    dst->debufs = ft_initialize_debuffs();
+    suffix_offset = offsetof(t_char, concentration);
+    ft_memcpy(dst_bytes + suffix_offset, src_bytes + suffix_offset,
+        sizeof(t_char) - suffix_offset);
+    return ;
+}
diff --git a/libft b/libft
index c92d4f2f8829c26d1c929e95fd69c6615794b33d..35c8a4f6b217ec701126f87dae9f3662a0b51608 160000
--- a/libft
+++ b/libft
@@ -1 +1 @@
-Subproject commit c92d4f2f8829c26d1c929e95fd69c6615794b33d
+Subproject commit 35c8a4f6b217ec701126f87dae9f3662a0b51608
diff --git a/malfurion.cpp b/malfurion.cpp
index d453f836445bdb9c036666cff1726c7afd44350f..f7847f932528f4a27bfbf5c20dca75af84bc6b18 100644
--- a/malfurion.cpp
+++ b/malfurion.cpp
@@ -19,51 +19,51 @@ void ft_malfurion_turn(t_char * info)
     pf_printf("%s currently has %d/%d hp\n", info->name, info->stats.health, info->dstats.health);
     return ;
 }
 
 static void ft_initialize_gear_and_feats(t_char * info)
 {
     info->spells.cure_wounds = MALFURION_SPELL_CURE_WOUNDS;
     return ;
 }
 
 void    ft_malfurion_loot(t_char * info)
 {
     (void)info;
     return ;
 }
 
 t_char *ft_malfurion(const int index, const char **input, t_name *name, int exception)
 {
     int error = 0;
     t_char *info = static_cast<t_char *>(cma_malloc(sizeof(t_char)));
     if (!info)
     {
         pf_printf_fd(2, "105-Error: Failed to allocate memory info %s\n", input[0]);
         return (ft_nullptr);
     }
-    *info = MALFURION_INFO;
+    ft_initialize_character_template(info, &MALFURION_INFO);
     info->name = input[0];
     info->struct_name = name;
     info->save_file = cma_strjoin("data/", input[0]);
     if (!info->save_file)
     {
         ft_free_info(info);
         return (ft_nullptr);
     }
     if (index == 2)
     {
         if (ft_strcmp(input[1], "init") == 0)
         {
             int result = ft_dice_roll(info->hit_dice.dice_amount, info->hit_dice.dice_faces);
             if (result == -1)
             {
                 pf_printf("147-Error Invalid hit dice %s", info->name);
                 ft_free_info(info);
                 return (ft_nullptr);
             }
             info->dstats.health = info->dstats.health + result;
             ft_file file(info->save_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
             if (file.get_error())
             {
                 pf_printf_fd(2, "123-Error opening file %s: %s\n", info->save_file,
                     file.get_error_str());
diff --git a/malfurion.hpp b/malfurion.hpp
index 7cf1834ff251de79bf9d717d889273dd07bcc6e7..1dcd1cf7a105466c875ef8f8a95b3a2e8699c5fc 100644
--- a/malfurion.hpp
+++ b/malfurion.hpp
@@ -161,52 +161,52 @@ static const t_spell_cure_wounds MALFURION_SPELL_CURE_WOUNDS =
     .extra_healing = 4,
     .upcast_extra_dice_face = 8,
     .upcast_extra_dice_amount = 1,
     .upcast_extra_healing = 0,
 };
 
 static const t_char MALFURION_INFO =
 {
     .level = 0,
     .mechanical = 0,
     .passive_perception = 15,
     .initiative = -1,
     .version_number = 2,
     .save_file = ft_nullptr,
     .name = ft_nullptr,
     .turn = ft_malfurion_turn,
     .drop_loot = ft_malfurion_loot,
     .loot = INITIALIZE_LOOT,
     .hit_dice = MALFURION_HIT_DICE,
     .inventory = MALFURION_INVENTORY,
     .spells = INITIALIZE_SPELLS,
     .spell_slots = MALFURION_SPELL_SLOTS,
     .flags = INITIALIZE_FLAGS,
     .crit = MALFURION_CRIT,
     .attack_bonus = MALFURION_ATTACK,
-    .bufs = INITIALIZE_BUFFS,
-    .debufs = INITIALIZE_DEBUFFS,
+    .bufs = ft_initialize_buffs(),
+    .debufs = ft_initialize_debuffs(),
     .concentration = INITIALIZE_CONCENTRATION,
     .d_resistance = MALFURION_DEFAULT_RESISTANCE,
     .c_resistance = INITIALIZE_CURRENT_RESISTANCE,
     .equipment = MALFURION_EQUIPMENT,
     .skill_mod = MALFURION_SKILL_MODS,
     .save_mod = MALFURION_SAVE_MODS,
     .stats = INITIALIZE_STATS,
     .dstats = MALFURION_DEFAULT_STATS,
     .feats = INITIALIZE_FEATS,
     .struct_name = ft_nullptr,
     .physical = MALFURION_PHYSICAL,
     .position = INITIALIZE_POSITION,
 };
 
 template <int Amount, int Faces>
 struct ValidateHitDice
 {
     static_assert
     (
         ((Amount == 0 && Faces == 0) || (Amount >= 1 && Faces >= 1)) &&
         (Amount <= 40 && Faces <= 12),
         "Invalid MALFURION_HIT_DICE values: Either both must be 0 or both at least 1, " \
             "and the dice amount must not exceed 40, the dice faces must not exceed 12."
     );
 };
diff --git a/mannoroth.cpp b/mannoroth.cpp
index 699d91bc9f83bf3fa9f269223eb09d63b0b2e350..1dad303559c84736b72ef70381874e39887da42a 100644
--- a/mannoroth.cpp
+++ b/mannoroth.cpp
@@ -19,51 +19,51 @@ void ft_mannoroth_turn(t_char * info)
     pf_printf("%s currently has %d/%d hp\n", info->name, info->stats.health, info->dstats.health);
     return ;
 }
 
 static void ft_initialize_gear_and_feats(t_char * info)
 {
     (void)info;
     return ;
 }
 
 void    ft_mannoroth_loot(t_char * info)
 {
     (void)info;
     return ;
 }
 
 t_char *ft_mannoroth(const int index, const char **input, t_name *name, int exception)
 {
     int error = 0;
     t_char *info = static_cast<t_char *>(cma_malloc(sizeof(t_char)));
     if (!info)
     {
         pf_printf_fd(2, "105-Error: Failed to allocate memory info %s\n", input[0]);
         return (ft_nullptr);
     }
-    *info = MANNOROTH_INFO;
+    ft_initialize_character_template(info, &MANNOROTH_INFO);
     info->name = input[0];
     info->struct_name = name;
     info->save_file = cma_strjoin("data/", input[0]);
     if (!info->save_file)
     {
         ft_free_info(info);
         return (ft_nullptr);
     }
     if (index == 2)
     {
         if (ft_strcmp(input[1], "init") == 0)
         {
             int result = ft_dice_roll(info->hit_dice.dice_amount, info->hit_dice.dice_faces);
             if (result == -1)
             {
                 pf_printf("147-Error Invalid hit dice %s", info->name);
                 ft_free_info(info);
                 return (ft_nullptr);
             }
             info->dstats.health = info->dstats.health + result;
             ft_file file(info->save_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
             if (file.get_error())
             {
                 pf_printf_fd(2, "123-Error opening file %s: %s\n", info->save_file,
                     file.get_error_str());
diff --git a/mannoroth.hpp b/mannoroth.hpp
index 86cb7e997aa19c9caf9caacdce8c8113c8911406..575338610f33475828f970d630ea56f54e5b8a29 100644
--- a/mannoroth.hpp
+++ b/mannoroth.hpp
@@ -150,52 +150,52 @@ static const t_inventory MANNOROTH_INVENTORY
 constexpr t_hit_dice MANNOROTH_HIT_DICE =
 {
     .dice_amount = 0,
     .dice_faces = 0,
 };
 
 static const t_char MANNOROTH_INFO =
 {
     .level = 0,
     .mechanical = 0,
     .passive_perception = 15,
     .initiative = -1,
     .version_number = 2,
     .save_file = ft_nullptr,
     .name = ft_nullptr,
     .turn = ft_mannoroth_turn,
     .drop_loot = ft_mannoroth_loot,
     .loot = INITIALIZE_LOOT,
     .hit_dice = MANNOROTH_HIT_DICE,
     .inventory = MANNOROTH_INVENTORY,
     .spells = INITIALIZE_SPELLS,
     .spell_slots = MANNOROTH_SPELL_SLOTS,
     .flags = INITIALIZE_FLAGS,
     .crit = MANNOROTH_CRIT,
     .attack_bonus = MANNOROTH_ATTACK,
-    .bufs = INITIALIZE_BUFFS,
-    .debufs = INITIALIZE_DEBUFFS,
+    .bufs = ft_initialize_buffs(),
+    .debufs = ft_initialize_debuffs(),
     .concentration = INITIALIZE_CONCENTRATION,
     .d_resistance = MANNOROTH_DEFAULT_RESISTANCE,
     .c_resistance = INITIALIZE_CURRENT_RESISTANCE,
     .equipment = MANNOROTH_EQUIPMENT,
     .skill_mod = MANNOROTH_SKILL_MODS,
     .save_mod = MANNOROTH_SAVE_MODS,
     .stats = INITIALIZE_STATS,
     .dstats = MANNOROTH_DEFAULT_STATS,
     .feats = INITIALIZE_FEATS,
     .struct_name = ft_nullptr,
     .physical = MANNOROTH_PHYSICAL,
     .position = INITIALIZE_POSITION,
 };
 
 template <int Amount, int Faces>
 struct ValidateHitDice
 {
     static_assert
     (
         ((Amount == 0 && Faces == 0) || (Amount >= 1 && Faces >= 1)) &&
         (Amount <= 40 && Faces <= 12),
         "Invalid MANNOROTH_HIT_DICE values: Either both must be 0 or both at least 1, " \
             "and the dice amount must not exceed 40, the dice faces must not exceed 12."
     );
 };
diff --git a/maverick.cpp b/maverick.cpp
index e2d1270e3923b1076c07695d6c848764ef34a782..7d469f16552b6eb9e57f1ae680f2adb5870a5acf 100644
--- a/maverick.cpp
+++ b/maverick.cpp
@@ -1,77 +1,82 @@
 #include "dnd_tools.hpp"
 #include "maverick.hpp"
 #include "libft/Printf/printf.hpp"
 #include "libft/CMA/CMA.hpp"
+#include "libft/Errno/errno.hpp"
 #include "libft/RNG/rng.hpp"
 
 void    ft_maverick_turn(t_char * info)
 {
     int        first;
     int        second;
-    char    **player_list;
+    ft_vector<ft_string>    player_list = ft_get_pc_list();
 
     ft_update_buf(info);
     pf_printf("\n\n");
-    player_list = ft_get_pc_list();
-        if (ft_double_char_length(const_cast<const char **>(player_list)) < 2)
+    if (player_list.get_error() != ER_SUCCESS)
     {
-        if (ft_double_char_length(const_cast<const char **>(player_list)) > 0)
+        player_list.clear();
+        return ;
+    }
+    if (player_list.size() < 2)
+    {
+        if (player_list.size() > 0)
             pf_printf_fd(2, "283-Error not enough targets for %s\n", info->name);
-        cma_free_double(player_list);
+        player_list.clear();
         return ;
     }
     first = 0;
     second = 0;
     while (first == second && first != 8)
     {
         first = ft_dice_roll(1, 8);
         second = ft_dice_roll(1, 8);
     }
     ft_maverick_print_f(first, second, info, player_list);
     ft_maverick_print_s(first, second, info, player_list);
     pf_printf("\n\n");
-    cma_free_double(player_list);
+    player_list.clear();
     return ;
 }
 
 static void ft_initialize_gear_and_feats(t_char * info)
 {
     (void)info;
     return ;
 }
 
 t_char *ft_maverick(const int index, const char **input, t_name *name, int exception)
 {
     int error = 0;
     t_char *info = static_cast<t_char *>(cma_malloc(sizeof(t_char)));
     if (!info)
     {
         pf_printf_fd(2, "105-Error: Failed to allocate memory info %s\n", input[0]);
         return (ft_nullptr);
     }
-    *info = MAVERICK_INFO;
+    ft_initialize_character_template(info, &MAVERICK_INFO);
     info->name = input[0];
     info->struct_name = name;
     info->save_file = cma_strjoin("data/", input[0]);
     if (!info->save_file)
     {
         ft_free_info(info);
         return (ft_nullptr);
     }
     if (index == 2)
     {
         if (ft_strcmp(input[1], "init") == 0)
         {
             ft_file file(info->save_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
             if (file.get_error())
             {
                 pf_printf_fd(2, "123-Error opening file %s: %s\n", info->save_file,
                     file.get_error_str());
                 return (ft_nullptr);
             }
             ft_npc_write_file(info, &info->dstats, &info->d_resistance, file);
             pf_printf("Stats for %s written on a file\n", info->name);
             ft_free_info(info);
             return (ft_nullptr);
         }
     }
diff --git a/maverick.hpp b/maverick.hpp
index 7009de077acb4144e5327570e78fac9566ed8225..03d2d2071c6f5ecf899039efb58cd59bc7d7fca0 100644
--- a/maverick.hpp
+++ b/maverick.hpp
@@ -115,52 +115,52 @@ static const t_physical MAVERICK_PHYSICAL =
     .height = 0,
     .weight = 0,
     .age = 0,
     .speed = 35,
 };
 
 static const t_char MAVERICK_INFO =
 {
     .level = 0,
     .mechanical = 0,
     .passive_perception = 20,
     .initiative = -1,
     .version_number = 2,
     .save_file = ft_nullptr,
     .name = ft_nullptr,
     .turn = ft_maverick_turn,
     .drop_loot = ft_nullptr,
     .loot = INITIALIZE_LOOT,
     .hit_dice = INITIALIZ_HIT_DICE,
     .inventory = INITIALIZE_INVENTORY,
     .spells = INITIALIZE_SPELLS,
     .spell_slots = INITIALIZE_SPELL_SLOTS,
     .flags = INITIALIZE_FLAGS,
     .crit = MAVERICK_CRIT,
     .attack_bonus = MAVERICK_ATTACK,
-    .bufs = INITIALIZE_BUFFS,
-    .debufs = INITIALIZE_DEBUFFS,
+    .bufs = ft_initialize_buffs(),
+    .debufs = ft_initialize_debuffs(),
     .concentration = INITIALIZE_CONCENTRATION,
     .d_resistance = MAVERICK_DEFAULT_RESISTANCE,
     .c_resistance = INITIALIZE_CURRENT_RESISTANCE,
     .equipment = MAVERICK_EQUIPMENT,
     .skill_mod = MAVERICK_SKILL_MODS,
     .save_mod = MAVERICK_SAVE_MODS,
     .stats = INITIALIZE_STATS,
     .dstats = MAVERICK_DEFAULT_STATS,
     .feats = INITIALIZE_FEATS,
     .struct_name = ft_nullptr,
     .physical = MAVERICK_PHYSICAL,
     .position = INITIALIZE_POSITION,
 };
 
 #define MAVERICK_MASS_TELEPORT "Mass Teleport: Teleport all players to random locations"\
     " across the arena depending on what ability it is paired with"
 #define MAVERICK_METEOR_STRIKE "Meteor Strike: Create a circle around the target with arrows"\
     " pointing towards the center (10ft.radius), at the start of the next turn a meteor hits"\
     " the target dealing damage dependent on the number of targets hit."\
     " (Cannot be the same target as Arcane Pounce or Earth Pounce)\n"\
     "1 target         22 fire damage\n"\
     "2 targets        9 fire damage each\n"\
     "3 targets        5 fire damage each\n"\
     "4 or more targets    3 fire damage each"
 #define MAVERICK_LIGHTNING_STRIKE "Lightning Strike: the bosses skin will flare with"\
diff --git a/maverick_turn.cpp b/maverick_turn.cpp
index a6306c66243b7179f6f2da40e74982b949f9fa92..9873d64533ad35a881bf4210f878994c2085b0ae 100644
--- a/maverick_turn.cpp
+++ b/maverick_turn.cpp
@@ -16,143 +16,143 @@ static void    ft_maverick_lightning_strike(t_char * info)
     info->bufs.lightning_strike.distance = 5;
     print_lightning_strike(info);
     return ;
 }
 
 static void    ft_maverick_lightningV2_strike(t_char * info)
 {
     info->bufs.lightning_strikeV2.duration = 1;
     info->bufs.lightning_strikeV2.dice_amount = 2;
     info->bufs.lightning_strikeV2.dice_faces = 8;
     info->bufs.lightning_strikeV2.distance = 5;
     print_lightning_strike_v2(info);
     return ;
 }
 
 static void    ft_maverick_flame_geyser(t_char * info)
 {
     info->bufs.flame_geyser.amount = 2;
     info->bufs.flame_geyser.duration = 1;
     info->bufs.flame_geyser.tower_explode_d = 10;
     info->bufs.flame_geyser.close_to_tower_d = 3;
     print_flame_geyser(info);
     return ;
 }
 
-static void ft_maverick_meteor_strike(t_char * info, char **player_list)
+static void ft_maverick_meteor_strike(t_char * info, ft_vector<ft_string> &player_list)
 {
     cma_free(info->bufs.meteor_strike.target_id);
     info->bufs.meteor_strike.target_id = ft_nullptr;
     ft_get_random_target(player_list, &info->bufs.meteor_strike.target_id);
     info->bufs.meteor_strike.duration = 1;
     info->bufs.meteor_strike.one_target_d = 22;
     info->bufs.meteor_strike.two_targets_d = 10;
     info->bufs.meteor_strike.three_targets_d = 16;
     info->bufs.meteor_strike.four_targets_d = 4;
     info->bufs.meteor_strike.five_targets_d = 3;
     print_meteor_strike(info);
     return ;
 }
 
-static void    ft_maverick_earth_pounce(t_char * info, char **player_list)
+static void    ft_maverick_earth_pounce(t_char * info, ft_vector<ft_string> &player_list)
 {
     cma_free(info->bufs.earth_pounce.target_id);
     info->bufs.earth_pounce.target_id = ft_nullptr;
     ft_get_random_target(player_list, &info->bufs.earth_pounce.target_id);
     info->bufs.earth_pounce.active = 1;
     info->bufs.earth_pounce.base_damage = 27;
     print_earth_pounce(info);
     return ;
 }
 
-static void    ft_maverick_arcane_pounce(t_char * info, char **player_list)
+static void    ft_maverick_arcane_pounce(t_char * info, ft_vector<ft_string> &player_list)
 {
     cma_free(info->bufs.frost_breath.target_id);
     info->bufs.frost_breath.target_id = ft_nullptr;
     ft_get_random_target(player_list, &info->bufs.arcane_pounce.target_id);
     info->bufs.arcane_pounce.active = 1;
     info->bufs.arcane_pounce.erea_damage = 8;
     info->bufs.arcane_pounce.magic_damage = 4;
     print_arcane_pounce(info);
     return ;
 }
 
-static void    ft_maverick_frost_breath(t_char * info, char **player_list)
+static void    ft_maverick_frost_breath(t_char * info, ft_vector<ft_string> &player_list)
 {
     cma_free(info->bufs.frost_breath.target_id);
     info->bufs.frost_breath.target_id = ft_nullptr;
     ft_get_random_target(player_list, &info->bufs.frost_breath.target_id);
     info->bufs.frost_breath.active = 1;
     info->bufs.frost_breath.damage = 25;
     print_frost_breath(info);
     return ;
 }
 
 static void print_mass_teleport(int tp_number)
 {
     pf_printf("Mass Teleport: Teleport all players to random locations " \
             "across the arena depending on what ability it is paired with.\n");    
     if (tp_number == 2)
         pf_printf("Teleportation Type: Meteor Strike - Spreading " \
                 "players 20ft-60ft. away from one another.\n");
     else if (tp_number == 3)
         pf_printf("Teleportation Type: Lightning Strike - Teleporting " \
                 "the players close to the boss.\n");
     else if (tp_number == 4)
         pf_printf("Teleportation Type: Flame Geyser - Teleporting the " \
                 "players to random locations 30-60ft. away from the flame geysers.\n");
     else if (tp_number == 5)
         pf_printf("Teleportation Type: Frost Breath - Teleporting all " \
                 "players in front of the boss.\n");
     else if (tp_number == 6)
         pf_printf("Teleportation Type: Lightning Strike V2 - Teleporting " \
                 "all players to the marker.\n");
     else if (tp_number == 7)
         pf_printf("Teleportation Type: Arcane Pounce - Teleporting all " \
                 "players around the target.\n");
     else if (tp_number == 8)
         pf_printf("Teleportation Type: Earth Pounce - Teleporting all " \
                 "players around the target.\n");
     return ;
 }
 
-void ft_maverick_print_f(int first, int second, t_char * info, char **player_list)
+void ft_maverick_print_f(int first, int second, t_char * info, ft_vector<ft_string> &player_list)
 {
     if (first == 1)
         print_mass_teleport(second);
     else if (first == 2)
         ft_maverick_meteor_strike(info, player_list);
     else if (first == 3)
         ft_maverick_lightning_strike(info);
     else if (first == 4)
         ft_maverick_flame_geyser(info);
     else if (first == 5)
         ft_maverick_frost_breath(info, player_list);
     else if (first == 6)
         ft_maverick_lightningV2_strike(info);
     else if (first == 7)
         ft_maverick_arcane_pounce(info, player_list);
     else if (first == 8)
         ft_maverick_earth_pounce(info, player_list);
     return ;
 }
 
-void ft_maverick_print_s(int first, int second, t_char * info, char **player_list)
+void ft_maverick_print_s(int first, int second, t_char * info, ft_vector<ft_string> &player_list)
 {
     if (second == 1)
         print_mass_teleport(first);
     else if (second == 2)
         ft_maverick_meteor_strike(info, player_list);
     else if (second == 3)
         ft_maverick_lightning_strike(info);
     else if (second == 4)
         ft_maverick_flame_geyser(info);
     else if (second == 5)
         ft_maverick_frost_breath(info, player_list);
     else if (second == 6)
         ft_maverick_lightningV2_strike(info);
     else if (second == 7)
         ft_maverick_arcane_pounce(info, player_list);
     else if (second == 8)
         ft_maverick_earth_pounce(info, player_list);
     return ;
 }
diff --git a/murna_claygrip.cpp b/murna_claygrip.cpp
index a1e02e649fbc20aa30e13947e0bbdf6329b0f27e..7e7bc2c680bae43c19a4da8ea1eb1475d9bc56bb 100644
--- a/murna_claygrip.cpp
+++ b/murna_claygrip.cpp
@@ -13,51 +13,51 @@ void ft_murna_claygrip_turn(t_char * info)
     }
     else
         pf_printf("%s will try to make either a ranged or melee " \
                 "attack during his turn\n", info->name);
     pf_printf("%s currently has %d/%d hp\n", info->name, info->stats.health, info->dstats.health);
     return ;
 }
 
 static void ft_initialize_gear_and_feats(t_char * info)
 {
     (void)info;
     return ;
 }
 
 t_char *ft_murna_claygrip(const int index, const char **input, t_name *name,
                                             int exception)
 {
     int error = 0;
     t_char *info = static_cast<t_char *>(cma_malloc(sizeof(t_char)));
 
     if (!info)
     {
         pf_printf_fd(2, "105-Error: Failed to allocate memory info %s\n", input[0]);
         return (ft_nullptr);
     }
-    *info = MURNA_CLAYGRIP_INFO;
+    ft_initialize_character_template(info, &MURNA_CLAYGRIP_INFO);
     info->name = input[0];
     info->struct_name = name;
     info->save_file = cma_strjoin("data/", input[0]);
     if (!info->save_file)
     {
         ft_free_info(info);
         return (ft_nullptr);
     }
     if (index == 2)
     {
         if (ft_strcmp(input[1], "init") == 0)
         {
             ft_file file(info->save_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
             if (file.get_error())
             {
                 pf_printf_fd(2, "123-Error opening file %s: %s\n", info->save_file,
                     file.get_error_str());
                 return (ft_nullptr);
             }
             ft_npc_write_file(info, &info->dstats, &info->d_resistance, file);
             pf_printf("Stats for %s written on a file\n", info->name);
             ft_free_info(info);
             return (ft_nullptr);
         }
     }
diff --git a/murna_claygrip.hpp b/murna_claygrip.hpp
index 0aad839a1d07422ab4c8cf510147d69caddc1abf..34ff850eb3659cab816cafee9a72789691b25fb6 100644
--- a/murna_claygrip.hpp
+++ b/murna_claygrip.hpp
@@ -114,42 +114,42 @@ static const    t_physical MURNA_CLAYGRIP_PHYSICAL =
     .height = 48,
     .weight = 150,
     .age = 100,
     .speed = 25,
 };
 
 static const    t_char MURNA_CLAYGRIP_INFO =
 {
     .level = 0,
     .mechanical = 0,
     .passive_perception = 12,
     .initiative = -1,
     .version_number = 2,
     .save_file = ft_nullptr,
     .name = ft_nullptr,
     .turn = ft_murna_claygrip_turn,
     .drop_loot = ft_nullptr,
     .loot = INITIALIZE_LOOT,
     .hit_dice = INITIALIZ_HIT_DICE,
     .inventory = INITIALIZE_INVENTORY,
     .spells = INITIALIZE_SPELLS,
     .spell_slots = INITIALIZE_SPELL_SLOTS,
     .flags = INITIALIZE_FLAGS,
     .crit = MURNA_CLAYGRIP_CRIT,
     .attack_bonus = MURNA_CLAYGRIP_ATTACK,
-    .bufs = INITIALIZE_BUFFS,
-    .debufs = INITIALIZE_DEBUFFS,
+    .bufs = ft_initialize_buffs(),
+    .debufs = ft_initialize_debuffs(),
     .concentration = INITIALIZE_CONCENTRATION,
     .d_resistance = MURNA_CLAYGRIP_DEFAULT_RESISTANCE,
     .c_resistance = INITIALIZE_CURRENT_RESISTANCE,
     .equipment = MURNA_CLAYGRIP_EQUIPMENT,
     .skill_mod = MURNA_CLAYGRIP_SKILL_MODS,
     .save_mod = MURNA_CLAYGRIP_SAVE_MODS,
     .stats = INITIALIZE_STATS,
     .dstats = MURNA_CLAYGRIP_DEFAULT_STATS,
     .feats = INITIALIZE_FEATS,
     .struct_name = ft_nullptr,
     .physical = MURNA_CLAYGRIP_PHYSICAL,
     .position = INITIALIZE_POSITION,
 };
 
 #endif
diff --git a/night_elven_guard.cpp b/night_elven_guard.cpp
index 59900557fa53a82f08b6ea99023f68445adc18aa..0255f86b8d9c630991de78b1015d1035c6f475c8 100644
--- a/night_elven_guard.cpp
+++ b/night_elven_guard.cpp
@@ -19,51 +19,51 @@ void ft_night_elven_guard_turn(t_char * info)
     pf_printf("%s currently has %d/%d hp\n", info->name, info->stats.health, info->dstats.health);
     return ;
 }
 
 static void ft_initialize_gear_and_feats(t_char * info)
 {
     (void)info;
     return ;
 }
 
 void    ft_night_elven_guard_loot(t_char * info)
 {
     (void)info;
     return ;
 }
 
 t_char *ft_night_elven_guard(const int index, const char **input, t_name *name, int exception)
 {
     int error = 0;
     t_char *info = static_cast<t_char *>(cma_malloc(sizeof(t_char)));
     if (!info)
     {
         pf_printf_fd(2, "105-Error: Failed to allocate memory info %s\n", input[0]);
         return (ft_nullptr);
     }
-    *info = NIGHT_ELVEN_GUARD_INFO;
+    ft_initialize_character_template(info, &NIGHT_ELVEN_GUARD_INFO);
     info->name = input[0];
     info->struct_name = name;
     info->save_file = cma_strjoin("data/", input[0]);
     if (!info->save_file)
     {
         ft_free_info(info);
         return (ft_nullptr);
     }
     if (index == 2)
     {
         if (ft_strcmp(input[1], "init") == 0)
         {
             int result = ft_dice_roll(info->hit_dice.dice_amount, info->hit_dice.dice_faces);
             if (result == -1)
             {
                 pf_printf("147-Error Invalid hit dice %s", info->name);
                 ft_free_info(info);
                 return (ft_nullptr);
             }
             info->dstats.health = info->dstats.health + result;
             ft_file file(info->save_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
             if (file.get_error())
             {
                 pf_printf_fd(2, "123-Error opening file %s: %s\n", info->save_file,
                     file.get_error_str());
diff --git a/night_elven_guard.hpp b/night_elven_guard.hpp
index ba4c335c5496edf741ec85b5a4641e865b557813..0e63bab13121ea5dc2afcd9b933cfd3320413332 100644
--- a/night_elven_guard.hpp
+++ b/night_elven_guard.hpp
@@ -150,52 +150,52 @@ static const t_inventory NIGHT_ELVEN_GUARD_INVENTORY
 constexpr t_hit_dice NIGHT_ELVEN_GUARD_HIT_DICE =
 {
     .dice_amount = 0,
     .dice_faces = 0,
 };
 
 static const t_char NIGHT_ELVEN_GUARD_INFO =
 {
     .level = 0,
     .mechanical = 0,
     .passive_perception = 17,
     .initiative = -1,
     .version_number = 2,
     .save_file = ft_nullptr,
     .name = ft_nullptr,
     .turn = ft_night_elven_guard_turn,
     .drop_loot = ft_night_elven_guard_loot,
     .loot = INITIALIZE_LOOT,
     .hit_dice = NIGHT_ELVEN_GUARD_HIT_DICE,
     .inventory = NIGHT_ELVEN_GUARD_INVENTORY,
     .spells = INITIALIZE_SPELLS,
     .spell_slots = NIGHT_ELVEN_GUARD_SPELL_SLOTS,
     .flags = INITIALIZE_FLAGS,
     .crit = NIGHT_ELVEN_GUARD_CRIT,
     .attack_bonus = NIGHT_ELVEN_GUARD_ATTACK,
-    .bufs = INITIALIZE_BUFFS,
-    .debufs = INITIALIZE_DEBUFFS,
+    .bufs = ft_initialize_buffs(),
+    .debufs = ft_initialize_debuffs(),
     .concentration = INITIALIZE_CONCENTRATION,
     .d_resistance = NIGHT_ELVEN_GUARD_DEFAULT_RESISTANCE,
     .c_resistance = INITIALIZE_CURRENT_RESISTANCE,
     .equipment = NIGHT_ELVEN_GUARD_EQUIPMENT,
     .skill_mod = NIGHT_ELVEN_GUARD_SKILL_MODS,
     .save_mod = NIGHT_ELVEN_GUARD_SAVE_MODS,
     .stats = INITIALIZE_STATS,
     .dstats = NIGHT_ELVEN_GUARD_DEFAULT_STATS,
     .feats = INITIALIZE_FEATS,
     .struct_name = ft_nullptr,
     .physical = NIGHT_ELVEN_GUARD_PHYSICAL,
     .position = INITIALIZE_POSITION,
 };
 
 template <int Amount, int Faces>
 struct ValidateHitDice
 {
     static_assert
     (
         ((Amount == 0 && Faces == 0) || (Amount >= 1 && Faces >= 1)) &&
         (Amount <= 40 && Faces <= 12),
         "Invalid NIGHT_ELVEN_GUARD_HIT_DICE values: Either both must be 0 or both at least 1, " \
             "and the dice amount must not exceed 40, the dice faces must not exceed 12."
     );
 };
diff --git a/read_line.cpp b/read_line.cpp
index b1c37c1830a3c2d8782a66ecc59facbd1c7fc745..512a6ae5dbbfcb67c9f8a5688d931523cccd90d0 100644
--- a/read_line.cpp
+++ b/read_line.cpp
@@ -65,40 +65,42 @@ static int ft_handle_builtins(char **input, int i, t_name *name, char *input_str
     else if (i == 1 && ft_strcmp(input[0], "turn") == 0)
         ft_turn_next(name);
     else if (i == 1 && ft_strcmp(input[0], "test") == 0)
         ft_test(name);
     else if (i == 1 && ft_strcmp(input[0], "help") == 0)
         ft_print_help();
         else if (i == 3 && ft_strcmp(input[1], "player") == 0)
         ft_player(const_cast<const char **>(input));
         else if (i >= 2 && ft_strcmp(input[0], "encounter") == 0)
                 ft_encounter(i - 1, const_cast<const char **>(input + 1), name);
     else
         return (0);
     return (1);
 }
 
 void ft_request_input(t_name *name)
 {
     char *input_string;
     char **input;
 
     while ((input_string = rl_readline("dndtools: ")) != ft_nullptr)
     {
         input = ft_parse_input(input_string);
         if (!input)
             continue ;
-        int index = ft_double_char_length(const_cast<const char **>(input));
+        int index = 0;
+        while (input[index])
+            index++;
         int found = ft_handle_builtins(input, index, name, input_string);
         if (found == -1)
         {
             rl_clear_history();
             return ;
         }
         else if (!found)
             found = ft_handle_custom_commands(input, index, name);
         if (!found)
             pf_printf_fd(2, "007-Error unknown command: %s\n", input_string);
         ft_free_input(input, input_string);
     }
     return ;
 }
diff --git a/remove_concentration.cpp b/remove_concentration.cpp
index d59a3b7cecf9fa43f7bc9df49268467620b6dbbb..b7ad3098ce832f2ed9c49492762bbad8ff5864e4 100644
--- a/remove_concentration.cpp
+++ b/remove_concentration.cpp
@@ -34,35 +34,35 @@ static int    ft_remove_concentration_fetch_targets(t_target_data *targets,
     if (error || !targets->target_copy[i])
     {
         ft_free_memory_cmt(targets, i);
         return (FAILURE);
     }
     return (SUCCES);
 }
 
 int ft_remove_concentration(t_char * info)
 {
     t_target_data    targets;
     int                i;
 
     ft_initialize_variables(&targets);
     if (DEBUG == 1)
         pf_printf("Removing concentration\n");
     i = 0;
     targets.buff_info = ft_nullptr;
     while (info->concentration.targets && info->concentration.targets[i])
     {
         if (ft_remove_concentration_fetch_targets(&targets, info, i))
             return (FAILURE);
         i++;
     }
     t_buff buff = INITIALIZE_T_BUFF;
-    buff.target_amount = ft_double_char_length(const_cast<const char **>(info->concentration.targets));
+    buff.target_amount = i;
     targets.buff_info = &buff;
     ft_file info_save_file(ft_check_and_open(&targets, info));
     if (info_save_file.get_error())
         return (FAILURE);
     ft_concentration_remove_buf(info, &targets);
     ft_cast_concentration_save_files(info, &targets, info_save_file);
     info->flags.alreaddy_saved = 0;
     return (SUCCES);
 }
diff --git a/remove_element.cpp b/remove_element.cpp
deleted file mode 100644
index 58bad907c65db360c37c3569a5309d006e5db174..0000000000000000000000000000000000000000
--- a/remove_element.cpp
+++ /dev/null
@@ -1,28 +0,0 @@
-#include "dnd_tools.hpp"
-#include "libft/CMA/CMA.hpp"
-#include <fcntl.h>
-#include <unistd.h>
-
-void    ft_remove_element(char **array, char *element, bool free_element)
-{
-    int    i;
-    int    j;
-
-    if (!array || !element)
-        return ;
-    i = 0;
-    while (array[i] && array[i] != element)
-        i++;
-    if (array[i] == element)
-    {
-        if (free_element)
-            cma_free(element);
-        j = i;
-        while (array[j])
-        {
-            array[j] = array[j + 1];
-            j++;
-        }
-    }
-    return ;
-}
diff --git a/shadow_illusion.cpp b/shadow_illusion.cpp
index 6642c9dd9848b669a812aac65fbbcacf8d3563f3..724c633628530c1353e346316879c86b02939c3d 100644
--- a/shadow_illusion.cpp
+++ b/shadow_illusion.cpp
@@ -19,51 +19,51 @@ void ft_shadow_illusion_turn(t_char * info)
     pf_printf("%s currently has %d/%d hp\n", info->name, info->stats.health, info->dstats.health);
     return ;
 }
 
 static void ft_initialize_gear_and_feats(t_char * info)
 {
     (void)info;
     return ;
 }
 
 void    ft_shadow_illusion_loot(t_char * info)
 {
     (void)info;
     return ;
 }
 
 t_char *ft_shadow_illusion(const int index, const char **input, t_name *name, int exception)
 {
     int error = 0;
     t_char *info = static_cast<t_char *>(cma_malloc(sizeof(t_char)));
     if (!info)
     {
         pf_printf_fd(2, "105-Error: Failed to allocate memory info %s\n", input[0]);
         return (ft_nullptr);
     }
-    *info = SHADOW_ILLUSION_INFO;
+    ft_initialize_character_template(info, &SHADOW_ILLUSION_INFO);
     info->name = input[0];
     info->struct_name = name;
     info->save_file = cma_strjoin("data/", input[0]);
     if (!info->save_file)
     {
         ft_free_info(info);
         return (ft_nullptr);
     }
     if (index == 2)
     {
         if (ft_strcmp(input[1], "init") == 0)
         {
             int result = ft_dice_roll(info->hit_dice.dice_amount, info->hit_dice.dice_faces);
             if (result == -1)
             {
                 pf_printf("147-Error Invalid hit dice %s", info->name);
                 ft_free_info(info);
                 return (ft_nullptr);
             }
             info->dstats.health = info->dstats.health + result;
             ft_file file(info->save_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
             if (file.get_error())
             {
                 pf_printf_fd(2, "123-Error opening file %s: %s\n", info->save_file,
                     file.get_error_str());
diff --git a/shadow_illusion.hpp b/shadow_illusion.hpp
index a30c93101ad4a8875cf09174ac761434923cf8b5..079d0fc13cbdcc44b07e90a4cea7134025edb227 100644
--- a/shadow_illusion.hpp
+++ b/shadow_illusion.hpp
@@ -149,52 +149,52 @@ static const t_inventory SHADOW_ILLUSION_INVENTORY
 constexpr t_hit_dice SHADOW_ILLUSION_HIT_DICE =
 {
     .dice_amount = 0,
     .dice_faces = 0,
 };
 
 static const t_char SHADOW_ILLUSION_INFO =
 {
     .level = 0,
     .mechanical = 0,
     .passive_perception = 15,
     .initiative = -1,
     .version_number = 2,
     .save_file = ft_nullptr,
     .name = ft_nullptr,
     .turn = ft_shadow_illusion_turn,
     .drop_loot = ft_shadow_illusion_loot,
     .loot = INITIALIZE_LOOT,
     .hit_dice = SHADOW_ILLUSION_HIT_DICE,
     .inventory = SHADOW_ILLUSION_INVENTORY,
     .spells = INITIALIZE_SPELLS,
     .spell_slots = SHADOW_ILLUSION_SPELL_SLOTS,
     .flags = INITIALIZE_FLAGS,
     .crit = SHADOW_ILLUSION_CRIT,
     .attack_bonus = SHADOW_ILLUSION_ATTACK,
-    .bufs = INITIALIZE_BUFFS,
-    .debufs = INITIALIZE_DEBUFFS,
+    .bufs = ft_initialize_buffs(),
+    .debufs = ft_initialize_debuffs(),
     .concentration = INITIALIZE_CONCENTRATION,
     .d_resistance = SHADOW_ILLUSION_DEFAULT_RESISTANCE,
     .c_resistance = INITIALIZE_CURRENT_RESISTANCE,
     .equipment = SHADOW_ILLUSION_EQUIPMENT,
     .skill_mod = SHADOW_ILLUSION_SKILL_MODS,
     .save_mod = SHADOW_ILLUSION_SAVE_MODS,
     .stats = INITIALIZE_STATS,
     .dstats = SHADOW_ILLUSION_DEFAULT_STATS,
     .feats = INITIALIZE_FEATS,
     .struct_name = ft_nullptr,
     .physical = SHADOW_ILLUSION_PHYSICAL,
     .position = INITIALIZE_POSITION,
 };
 
 template <int Amount, int Faces>
 struct ValidateHitDice
 {
     static_assert
     (
         ((Amount == 0 && Faces == 0) || (Amount >= 1 && Faces >= 1)) &&
         (Amount <= 40 && Faces <= 12),
         "Invalid SHADOW_ILLUSION_HIT_DICE values: Either both must be 0 or both at least 1, " \
             "and the dice amount must not exceed 40, the dice faces must not exceed 12."
     );
 };
diff --git a/shield_spell_a.cpp b/shield_spell_a.cpp
index 3093e7e7c1af48d0e9428898d47e52ab4212ff59..df3b863926936602f93975f5d28d55239b37211a 100644
--- a/shield_spell_a.cpp
+++ b/shield_spell_a.cpp
@@ -12,51 +12,51 @@ void ft_shield_spell_a_turn(t_char * info)
             info->dstats.health);
     return ;
 }
 
 static void ft_initialize_gear_and_feats(t_char * info)
 {
     (void)info;
     return ;
 }
 
 void    ft_shield_spell_a_loot(t_char * info)
 {
     (void)info;
     return ;
 }
 
 t_char *ft_shield_spell_a(const int index, const char **input, t_name *name, int exception)
 {
     int error = 0;
     t_char *info = static_cast<t_char *>(cma_malloc(sizeof(t_char)));
     if (!info)
     {
         pf_printf_fd(2, "105-Error: Failed to allocate memory info %s\n", input[0]);
         return (ft_nullptr);
     }
-    *info = SHIELD_SPELL_A_INFO;
+    ft_initialize_character_template(info, &SHIELD_SPELL_A_INFO);
     info->name = input[0];
     info->struct_name = name;
     info->save_file = cma_strjoin("data/", input[0]);
     if (!info->save_file)
     {
         ft_free_info(info);
         return (ft_nullptr);
     }
     if (index == 2)
     {
         if (ft_strcmp(input[1], "init") == 0)
         {
             int result = ft_dice_roll(info->hit_dice.dice_amount,
                     info->hit_dice.dice_faces);
             if (result == -1)
             {
                 pf_printf("147-Error Invalid hit dice %s", info->name);
                 ft_free_info(info);
                 return (ft_nullptr);
             }
             info->dstats.health = info->dstats.health + result;
             ft_file file(info->save_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR |
                     S_IWUSR);
             if (file.get_error())
             {
diff --git a/shield_spell_a.hpp b/shield_spell_a.hpp
index 4705479f3cfb57ff84502b55390918f5f603e837..0511ea6b4b16f2d69322ed7e5b45c878dd64c5e4 100644
--- a/shield_spell_a.hpp
+++ b/shield_spell_a.hpp
@@ -149,52 +149,52 @@ static const t_inventory SHIELD_SPELL_A_INVENTORY
 constexpr t_hit_dice SHIELD_SPELL_A_HIT_DICE =
 {
     .dice_amount = 0,
     .dice_faces = 0,
 };
 
 static const t_char SHIELD_SPELL_A_INFO =
 {
     .level = 0,
     .mechanical = 0,
     .passive_perception = 15,
     .initiative = -1,
     .version_number = 2,
     .save_file = ft_nullptr,
     .name = ft_nullptr,
     .turn = ft_shield_spell_a_turn,
     .drop_loot = ft_shield_spell_a_loot,
     .loot = INITIALIZE_LOOT,
     .hit_dice = SHIELD_SPELL_A_HIT_DICE,
     .inventory = SHIELD_SPELL_A_INVENTORY,
     .spells = INITIALIZE_SPELLS,
     .spell_slots = SHIELD_SPELL_A_SPELL_SLOTS,
     .flags = INITIALIZE_FLAGS,
     .crit = SHIELD_SPELL_A_CRIT,
     .attack_bonus = SHIELD_SPELL_A_ATTACK,
-    .bufs = INITIALIZE_BUFFS,
-    .debufs = INITIALIZE_DEBUFFS,
+    .bufs = ft_initialize_buffs(),
+    .debufs = ft_initialize_debuffs(),
     .concentration = INITIALIZE_CONCENTRATION,
     .d_resistance = SHIELD_SPELL_A_DEFAULT_RESISTANCE,
     .c_resistance = INITIALIZE_CURRENT_RESISTANCE,
     .equipment = SHIELD_SPELL_A_EQUIPMENT,
     .skill_mod = SHIELD_SPELL_A_SKILL_MODS,
     .save_mod = SHIELD_SPELL_A_SAVE_MODS,
     .stats = INITIALIZE_STATS,
     .dstats = SHIELD_SPELL_A_DEFAULT_STATS,
     .feats = INITIALIZE_FEATS,
     .struct_name = ft_nullptr,
     .physical = SHIELD_SPELL_A_PHYSICAL,
     .position = INITIALIZE_POSITION,
 };
 
 template <int Amount, int Faces>
 struct ValidateHitDice
 {
     static_assert
     (
         ((Amount == 0 && Faces == 0) || (Amount >= 1 && Faces >= 1)) &&
         (Amount <= 40 && Faces <= 12),
         "Invalid SHIELD_SPELL_A_HIT_DICE values: Either both must be 0 or both at least 1, " \
             "and the dice amount must not exceed 40, the dice faces must not exceed 12."
     );
 };
diff --git a/snow_goblin.cpp b/snow_goblin.cpp
index e7a68dd30e325da9c8e7e83fa23aedc35a6e9ccc..1d9abf39d3d89af8d83035ac8b76e0cb3f5bc215 100644
--- a/snow_goblin.cpp
+++ b/snow_goblin.cpp
@@ -19,51 +19,51 @@ void ft_snow_goblin_turn(t_char * info)
     pf_printf("%s currently has %d/%d hp\n", info->name, info->stats.health, info->dstats.health);
     return ;
 }
 
 static void ft_initialize_gear_and_feats(t_char * info)
 {
     (void)info;
     return ;
 }
 
 void    ft_snow_goblin_loot(t_char * info)
 {
     (void)info;
     return ;
 }
 
 t_char *ft_snow_goblin(const int index, const char **input, t_name *name, int exception)
 {
     int error = 0;
     t_char *info = static_cast<t_char *>(cma_malloc(sizeof(t_char)));
     if (!info)
     {
         pf_printf_fd(2, "105-Error: Failed to allocate memory info %s\n", input[0]);
         return (ft_nullptr);
     }
-    *info = SNOW_GOBLIN_INFO;
+    ft_initialize_character_template(info, &SNOW_GOBLIN_INFO);
     info->name = input[0];
     info->struct_name = name;
     info->save_file = cma_strjoin("data/", input[0]);
     if (!info->save_file)
     {
         ft_free_info(info);
         return (ft_nullptr);
     }
     if (index == 2)
     {
         if (ft_strcmp(input[1], "init") == 0)
         {
             int result = ft_dice_roll(info->hit_dice.dice_amount, info->hit_dice.dice_faces);
             if (result == -1)
             {
                 pf_printf("147-Error Invalid hit dice %s", info->name);
                 ft_free_info(info);
                 return (ft_nullptr);
             }
             info->dstats.health = info->dstats.health + result;
             ft_file file(info->save_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
             if (file.get_error())
             {
                 pf_printf_fd(2, "123-Error opening file %s: %s\n", info->save_file,
                     file.get_error_str());
diff --git a/snow_goblin.hpp b/snow_goblin.hpp
index fffdfa722ce0028e2d6a37b2f6b2795ac78f8be8..cdb37727e3d7c7b54c570e87ba77bf83692f7655 100644
--- a/snow_goblin.hpp
+++ b/snow_goblin.hpp
@@ -207,52 +207,52 @@ static const t_inventory SNOW_GOBLIN_INVENTORY
 constexpr t_hit_dice SNOW_GOBLIN_HIT_DICE =
 {
     .dice_amount = 0,
     .dice_faces = 0,
 };
 
 static const t_char SNOW_GOBLIN_INFO =
 {
     .level = 0,
     .mechanical = 0,
     .passive_perception = 15,
     .initiative = -1,
     .version_number = 2,
     .save_file = ft_nullptr,
     .name = ft_nullptr,
     .turn = ft_snow_goblin_turn,
     .drop_loot = ft_snow_goblin_loot,
     .loot = INITIALIZE_LOOT,
     .hit_dice = SNOW_GOBLIN_HIT_DICE,
     .inventory = SNOW_GOBLIN_INVENTORY,
     .spells = INITIALIZE_SPELLS,
     .spell_slots = SNOW_GOBLIN_SPELL_SLOTS,
     .flags = INITIALIZE_FLAGS,
     .crit = SNOW_GOBLIN_CRIT,
     .attack_bonus = SNOW_GOBLIN_ATTACK,
-    .bufs = INITIALIZE_BUFFS,
-    .debufs = INITIALIZE_DEBUFFS,
+    .bufs = ft_initialize_buffs(),
+    .debufs = ft_initialize_debuffs(),
     .concentration = INITIALIZE_CONCENTRATION,
     .d_resistance = SNOW_GOBLIN_DEFAULT_RESISTANCE,
     .c_resistance = INITIALIZE_CURRENT_RESISTANCE,
     .equipment = SNOW_GOBLIN_EQUIPMENT,
     .skill_mod = SNOW_GOBLIN_SKILL_MODS,
     .save_mod = SNOW_GOBLIN_SAVE_MODS,
     .stats = INITIALIZE_STATS,
     .dstats = SNOW_GOBLIN_DEFAULT_STATS,
     .feats = INITIALIZE_FEATS,
     .struct_name = ft_nullptr,
     .physical = SNOW_GOBLIN_PHYSICAL,
     .position = INITIALIZE_POSITION,
 };
 
 template <int Amount, int Faces>
 struct ValidateHitDice
 {
     static_assert
     (
         ((Amount == 0 && Faces == 0) || (Amount >= 1 && Faces >= 1)) &&
         (Amount <= 40 && Faces <= 12),
         "Invalid TEMPLATE_HIT_DICE values: Either both must be 0 or both at least 1, " \
             "and the dice amount must not exceed 40, the dice faces must not exceed 12."
     );
 };
diff --git a/snow_goblin_shaman.cpp b/snow_goblin_shaman.cpp
index b13c12e5af0d75b0493c3de273ba9972c30a3647..70861d73ed272ff1744e68a0a2004caa04a9e619 100644
--- a/snow_goblin_shaman.cpp
+++ b/snow_goblin_shaman.cpp
@@ -19,51 +19,51 @@ void ft_snow_goblin_shaman_turn(t_char * info)
     pf_printf("%s currently has %d/%d hp\n", info->name, info->stats.health, info->dstats.health);
     return ;
 }
 
 static void ft_initialize_gear_and_feats(t_char * info)
 {
     (void)info;
     return ;
 }
 
 void    ft_snow_goblin_shaman_loot(t_char * info)
 {
     (void)info;
     return ;
 }
 
 t_char *ft_snow_goblin_shaman(const int index, const char **input, t_name *name, int exception)
 {
     int error = 0;
     t_char *info = static_cast<t_char *>(cma_malloc(sizeof(t_char)));
     if (!info)
     {
         pf_printf_fd(2, "105-Error: Failed to allocate memory info %s\n", input[0]);
         return (ft_nullptr);
     }
-    *info = SNOW_GOBLIN_SHAMAN_INFO;
+    ft_initialize_character_template(info, &SNOW_GOBLIN_SHAMAN_INFO);
     info->name = input[0];
     info->struct_name = name;
     info->save_file = cma_strjoin("data/", input[0]);
     if (!info->save_file)
     {
         ft_free_info(info);
         return (ft_nullptr);
     }
     if (index == 2)
     {
         if (ft_strcmp(input[1], "init") == 0)
         {
             int result = ft_dice_roll(info->hit_dice.dice_amount, info->hit_dice.dice_faces);
             if (result == -1)
             {
                 pf_printf("147-Error Invalid hit dice %s", info->name);
                 ft_free_info(info);
                 return (ft_nullptr);
             }
             info->dstats.health = info->dstats.health + result;
             ft_file file(info->save_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
             if (file.get_error())
             {
                 pf_printf_fd(2, "123-Error opening file %s: %s\n", info->save_file,
                     file.get_error_str());
diff --git a/snow_goblin_shaman.hpp b/snow_goblin_shaman.hpp
index 540cd1258c43d8f8959672c20da514405bf85f27..b70b825e30335eb4660b8f0a45c0e1a206c409ac 100644
--- a/snow_goblin_shaman.hpp
+++ b/snow_goblin_shaman.hpp
@@ -150,52 +150,52 @@ static const t_inventory SNOW_GOBLIN_SHAMAN_INVENTORY
 constexpr t_hit_dice SNOW_GOBLIN_SHAMAN_HIT_DICE =
 {
     .dice_amount = 0,
     .dice_faces = 0,
 };
 
 static const t_char SNOW_GOBLIN_SHAMAN_INFO =
 {
     .level = 0,
     .mechanical = 0,
     .passive_perception = 15,
     .initiative = -1,
     .version_number = 2,
     .save_file = ft_nullptr,
     .name = ft_nullptr,
     .turn = ft_snow_goblin_shaman_turn,
     .drop_loot = ft_snow_goblin_shaman_loot,
     .loot = INITIALIZE_LOOT,
     .hit_dice = SNOW_GOBLIN_SHAMAN_HIT_DICE,
     .inventory = SNOW_GOBLIN_SHAMAN_INVENTORY,
     .spells = INITIALIZE_SPELLS,
     .spell_slots = SNOW_GOBLIN_SHAMAN_SPELL_SLOTS,
     .flags = INITIALIZE_FLAGS,
     .crit = SNOW_GOBLIN_SHAMAN_CRIT,
     .attack_bonus = SNOW_GOBLIN_SHAMAN_ATTACK,
-    .bufs = INITIALIZE_BUFFS,
-    .debufs = INITIALIZE_DEBUFFS,
+    .bufs = ft_initialize_buffs(),
+    .debufs = ft_initialize_debuffs(),
     .concentration = INITIALIZE_CONCENTRATION,
     .d_resistance = SNOW_GOBLIN_SHAMAN_DEFAULT_RESISTANCE,
     .c_resistance = INITIALIZE_CURRENT_RESISTANCE,
     .equipment = SNOW_GOBLIN_SHAMAN_EQUIPMENT,
     .skill_mod = SNOW_GOBLIN_SHAMAN_SKILL_MODS,
     .save_mod = SNOW_GOBLIN_SHAMAN_SAVE_MODS,
     .stats = INITIALIZE_STATS,
     .dstats = SNOW_GOBLIN_SHAMAN_DEFAULT_STATS,
     .feats = INITIALIZE_FEATS,
     .struct_name = ft_nullptr,
     .physical = SNOW_GOBLIN_SHAMAN_PHYSICAL,
     .position = INITIALIZE_POSITION,
 };
 
 template <int Amount, int Faces>
 struct ValidateHitDice
 {
     static_assert
     (
         ((Amount == 0 && Faces == 0) || (Amount >= 1 && Faces >= 1)) &&
         (Amount <= 40 && Faces <= 12),
         "Invalid SNOW_GOBLIN_SHAMAN_HIT_DICE values: Either both must be 0 or both at least 1, " \
             "and the dice amount must not exceed 40, the dice faces must not exceed 12."
     );
 };
diff --git a/template.cpp b/template.cpp
index 3c13bdd766d5688d635a5f3e897df2c73be9e183..29c48765632145b4b0f3f2e50882cf0ee5cb6b7d 100644
--- a/template.cpp
+++ b/template.cpp
@@ -19,51 +19,51 @@ void ft_template_turn(t_char * info)
     pf_printf("%s currently has %d/%d hp\n", info->name, info->stats.health, info->dstats.health);
     return ;
 }
 
 static void ft_initialize_gear_and_feats(t_char * info)
 {
     (void)info;
     return ;
 }
 
 void    ft_template_loot(t_char * info)
 {
     (void)info;
     return ;
 }
 
 t_char *ft_template(const int index, const char **input, t_name *name, int exception)
 {
     int error = 0;
     t_char *info = static_cast<t_char *>(cma_malloc(sizeof(t_char)));
     if (!info)
     {
         pf_printf_fd(2, "105-Error: Failed to allocate memory info %s\n", input[0]);
         return (ft_nullptr);
     }
-    *info = TEMPLATE_INFO;
+    ft_initialize_character_template(info, &TEMPLATE_INFO);
     info->name = input[0];
     info->struct_name = name;
     info->save_file = cma_strjoin("data/", input[0]);
     if (!info->save_file)
     {
         ft_free_info(info);
         return (ft_nullptr);
     }
     if (index == 2)
     {
         if (ft_strcmp(input[1], "init") == 0)
         {
             int result = ft_dice_roll(info->hit_dice.dice_amount, info->hit_dice.dice_faces);
             if (result == -1)
             {
                 pf_printf("147-Error Invalid hit dice %s", info->name);
                 ft_free_info(info);
                 return (ft_nullptr);
             }
             info->dstats.health = info->dstats.health + result;
             ft_file file(info->save_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
             if (file.get_error())
             {
                 pf_printf_fd(2, "123-Error opening file %s: %s\n", info->save_file,
                     file.get_error_str());
diff --git a/template.hpp b/template.hpp
index c39922edfb50703828e49ff17b2152de48916dc6..82cee592adde0bbdc22a88effd86102d08aa5542 100644
--- a/template.hpp
+++ b/template.hpp
@@ -149,52 +149,52 @@ static const t_inventory TEMPLATE_INVENTORY
 constexpr t_hit_dice TEMPLATE_HIT_DICE =
 {
     .dice_amount = 0,
     .dice_faces = 0,
 };
 
 static const t_char TEMPLATE_INFO =
 {
     .level = 0,
     .mechanical = 0,
     .passive_perception = 15,
     .initiative = -1,
     .version_number = 2,
     .save_file = ft_nullptr,
     .name = ft_nullptr,
     .turn = ft_template_turn,
     .drop_loot = ft_template_loot,
     .loot = INITIALIZE_LOOT,
     .hit_dice = TEMPLATE_HIT_DICE,
     .inventory = TEMPLATE_INVENTORY,
     .spells = INITIALIZE_SPELLS,
     .spell_slots = TEMPLATE_SPELL_SLOTS,
     .flags = INITIALIZE_FLAGS,
     .crit = TEMPLATE_CRIT,
     .attack_bonus = TEMPLATE_ATTACK,
-    .bufs = INITIALIZE_BUFFS,
-    .debufs = INITIALIZE_DEBUFFS,
+    .bufs = ft_initialize_buffs(),
+    .debufs = ft_initialize_debuffs(),
     .concentration = INITIALIZE_CONCENTRATION,
     .d_resistance = TEMPLATE_DEFAULT_RESISTANCE,
     .c_resistance = INITIALIZE_CURRENT_RESISTANCE,
     .equipment = TEMPLATE_EQUIPMENT,
     .skill_mod = TEMPLATE_SKILL_MODS,
     .save_mod = TEMPLATE_SAVE_MODS,
     .stats = INITIALIZE_STATS,
     .dstats = TEMPLATE_DEFAULT_STATS,
     .feats = INITIALIZE_FEATS,
     .struct_name = ft_nullptr,
     .physical = TEMPLATE_PHYSICAL,
     .position = INITIALIZE_POSITION,
 };
 
 template <int Amount, int Faces>
 struct ValidateHitDice
 {
     static_assert
     (
         ((Amount == 0 && Faces == 0) || (Amount >= 1 && Faces >= 1)) &&
         (Amount <= 40 && Faces <= 12),
         "Invalid TEMPLATE_HIT_DICE values: Either both must be 0 or both at least 1, " \
             "and the dice amount must not exceed 40, the dice faces must not exceed 12."
     );
 };
diff --git a/thorbald_ironpocket.cpp b/thorbald_ironpocket.cpp
index 9a9fcfa3f32bf045e2c85ad35d77d3716628aab4..84d612df08547f36445e7232039598968bd61563 100644
--- a/thorbald_ironpocket.cpp
+++ b/thorbald_ironpocket.cpp
@@ -13,51 +13,51 @@ void ft_thorbald_ironpocket_turn(t_char * info)
     }
     else
         pf_printf("%s will try to make either a ranged or melee " \
                 "attack during his turn\n", info->name);
     pf_printf("%s currently has %d/%d hp\n", info->name, info->stats.health, info->dstats.health);
     return ;
 }
 
 static void ft_initialize_gear_and_feats(t_char * info)
 {
     (void)info;
     return ;
 }
 
 t_char *ft_thorbald_ironpocket(const int index, const char **input, t_name *name,
                                                 int exception)
 {
     int error = 0;
     t_char *info = static_cast<t_char *>(cma_malloc(sizeof(t_char)));
 
     if (!info)
     {
         pf_printf_fd(2, "105-Error: Failed to allocate memory info %s\n", input[0]);
         return (ft_nullptr);
     }
-    *info = THORBALD_IRONPOCKET_INFO;
+    ft_initialize_character_template(info, &THORBALD_IRONPOCKET_INFO);
     info->name = input[0];
     info->struct_name = name;
     info->save_file = cma_strjoin("data/", input[0]);
     if (!info->save_file)
     {
         ft_free_info(info);
         return (ft_nullptr);
     }
     if (index == 2)
     {
         if (ft_strcmp(input[1], "init") == 0)
         {
             ft_file file(info->save_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
             if (file.get_error())
             {
                 pf_printf_fd(2, "123-Error opening file %s: %s\n", info->save_file,
                     file.get_error_str());
                 return (ft_nullptr);
             }
             ft_npc_write_file(info, &info->dstats, &info->d_resistance, file);
             pf_printf("Stats for %s written on a file\n", info->name);
             ft_free_info(info);
             return (ft_nullptr);
         }
     }
diff --git a/thorbald_ironpocket.hpp b/thorbald_ironpocket.hpp
index 7428439db3c5203218293e04dde7940dca2c9fef..6af1201a2d99d86949ffa109de7b2068cfd887d5 100644
--- a/thorbald_ironpocket.hpp
+++ b/thorbald_ironpocket.hpp
@@ -114,42 +114,42 @@ static const    t_physical THORBALD_IRONPOCKET_PHYSICAL =
     .height = 48,
     .weight = 150,
     .age = 100,
     .speed = 25,
 };
 
 static const    t_char THORBALD_IRONPOCKET_INFO =
 {
     .level = 0,
     .mechanical = 0,
     .passive_perception = 12,
     .initiative = -1,
     .version_number = 2,
     .save_file = ft_nullptr,
     .name = ft_nullptr,
     .turn = ft_thorbald_ironpocket_turn,
     .drop_loot = ft_nullptr,
     .loot = INITIALIZE_LOOT,
     .hit_dice = INITIALIZ_HIT_DICE,
     .inventory = INITIALIZE_INVENTORY,
     .spells = INITIALIZE_SPELLS,
     .spell_slots = INITIALIZE_SPELL_SLOTS,
     .flags = INITIALIZE_FLAGS,
     .crit = THORBALD_IRONPOCKET_CRIT,
     .attack_bonus = THORBALD_IRONPOCKET_ATTACK,
-    .bufs = INITIALIZE_BUFFS,
-    .debufs = INITIALIZE_DEBUFFS,
+    .bufs = ft_initialize_buffs(),
+    .debufs = ft_initialize_debuffs(),
     .concentration = INITIALIZE_CONCENTRATION,
     .d_resistance = THORBALD_IRONPOCKET_DEFAULT_RESISTANCE,
     .c_resistance = INITIALIZE_CURRENT_RESISTANCE,
     .equipment = THORBALD_IRONPOCKET_EQUIPMENT,
     .skill_mod = THORBALD_IRONPOCKET_SKILL_MODS,
     .save_mod = THORBALD_IRONPOCKET_SAVE_MODS,
     .stats = INITIALIZE_STATS,
     .dstats = THORBALD_IRONPOCKET_DEFAULT_STATS,
     .feats = INITIALIZE_FEATS,
     .struct_name = ft_nullptr,
     .physical = THORBALD_IRONPOCKET_PHYSICAL,
     .position = INITIALIZE_POSITION,
 };
 
 #endif
diff --git a/utils02.cpp b/utils02.cpp
index 3a5c4b1b1fb49e78587baade05bb891b3007991f..7e28f655a3d228fdf6b5d45193b382d9b40f9c27 100644
--- a/utils02.cpp
+++ b/utils02.cpp
@@ -1,32 +1,22 @@
 #include "dnd_tools.hpp"
 #include "libft/Errno/errno.hpp"
 #include <fcntl.h>
 #include <unistd.h>
 
-int ft_double_char_length(const char **double_char)
-{
-    if (!double_char)
-        return (0);
-    int index = 0;
-    while (double_char[index])
-        index++;
-    return (index);
-}
-
 int ft_is_caster_name_present(ft_set<ft_string> *caster_name_list, const char *name)
 {
     const ft_string    *existing_name;
     ft_string           search_value(name);
 
     if (!caster_name_list || !name)
         return (0);
     if (search_value.get_error())
         return (0);
     existing_name = caster_name_list->find(search_value);
     if (existing_name)
         return (1);
     if (caster_name_list->get_error() != SET_NOT_FOUND
         && caster_name_list->get_error() != ER_SUCCESS)
         return (1);
     return (0);
 }
diff --git a/veraak.cpp b/veraak.cpp
index 3a201457e4ca09a57e0d316f68e4f5762ed23e19..e395a36c2e6a126710328aca9251d5fc5f77f9a5 100644
--- a/veraak.cpp
+++ b/veraak.cpp
@@ -82,51 +82,51 @@ void ft_veraak_turn(t_char *info)
     else
         pf_printf("%s will try to make either a ranged or melee attack during his turn\n",
                 info->name);
     pf_printf("%s currently has %d/%d hp\n", info->name, info->stats.health,
             info->dstats.health);
     return ;
 }
 
 static void ft_initialize_gear_and_feats(t_char *info)
 {
     info->spells.hunters_mark = VERAAK_SPELL_HUNTERS_MARK;
     info->spells.bless = VERAAK_SPELL_BLESS;
     return ;
 }
 
 t_char *ft_veraak(const int index, const char **input, t_name *name,
                                 int exception)
 {
     int error = 0;
     t_char *info = static_cast<t_char *>(cma_malloc(sizeof(t_char)));
     if (!info)
     {
         pf_printf_fd(2, "105-Error: Failed to allocate memory info %s\n", input[0]);
         return (ft_nullptr);
     }
-    *info = VERAAK_INFO;
+    ft_initialize_character_template(info, &VERAAK_INFO);
     info->name = input[0];
     info->struct_name = name;
     info->save_file = cma_strjoin("data/", input[0]);
     if (!info->save_file)
     {
         ft_free_info(info);
         return (ft_nullptr);
     }
     if (index == 2 && ft_strcmp(input[1], "init") == 0)
     {
         ft_file file(info->save_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
         if (file.get_error())
         {
             pf_printf_fd(2, "123-Error opening file %s: %s\n", info->save_file,
                 file.get_error_str());
             return (ft_nullptr);
         }
         ft_npc_write_file(info, &info->dstats, &info->d_resistance, file);
         pf_printf("Stats for %s written on a file\n", info->name);
         ft_veraak_initialize(info);
         ft_free_info(info);
         return (ft_nullptr);
     }
     error = ft_npc_open_file(info);
     if (error)
diff --git a/veraak.hpp b/veraak.hpp
index 9ef7a726521cf8f5d2db1926dff20e1acc6db232..82a1890c212efb1cbb0e2aee0d2e2e1adb699573 100644
--- a/veraak.hpp
+++ b/veraak.hpp
@@ -169,52 +169,52 @@ static const t_spell_slots VERAAK_SPELL_SLOTS =
     .level_7 = INITIALIZE_SPELL_SLOT,
     .level_8 = INITIALIZE_SPELL_SLOT,
     .level_9 = INITIALIZE_SPELL_SLOT,
     .warlock = INITIALIZE_SPELL_SLOT,
 };
 
 static const t_char VERAAK_INFO =
 {
     .level = 2,
     .mechanical = 0,
     .passive_perception = 15,
     .initiative = -1,
     .version_number = 2,
     .save_file = ft_nullptr,
     .name = ft_nullptr,
     .turn = ft_veraak_turn,
     .drop_loot = ft_nullptr,
     .loot = INITIALIZE_LOOT,
     .hit_dice = INITIALIZ_HIT_DICE,
     .inventory = INITIALIZE_INVENTORY,
     .spells = INITIALIZE_SPELLS,
     .spell_slots = VERAAK_SPELL_SLOTS,
     .flags = INITIALIZE_FLAGS,
     .crit = VERAAK_CRIT,
     .attack_bonus = VERAAK_ATTACK,
-    .bufs = INITIALIZE_BUFFS,
-    .debufs = INITIALIZE_DEBUFFS,
+    .bufs = ft_initialize_buffs(),
+    .debufs = ft_initialize_debuffs(),
     .concentration = INITIALIZE_CONCENTRATION,
     .d_resistance = VERAAK_DEFAULT_RESISTANCE,
     .c_resistance = INITIALIZE_CURRENT_RESISTANCE,
     .equipment = VERAAK_EQUIPMENT,
     .skill_mod = VERAAK_SKILL_MODS,
     .save_mod = VERAAK_SAVE_MODS,
     .stats = INITIALIZE_STATS,
     .dstats = VERAAK_DEFAULT_STATS,
     .feats = INITIALIZE_FEATS,
     .struct_name = ft_nullptr,
     .physical = VERAAK_PHYSICAL,
     .position = INITIALIZE_POSITION,
 };
 
 #define CHAOS_SMASH "Veraak conjures a hammer made out of dark energy hitting his" \
     " target with it dealing damage based on his armor class\n" \
     "10-12 ac -> 15 " DAMAGE_TYPE_FORCE " damage\n" \
     "13-15 ac -> 10 " DAMAGE_TYPE_FORCE " damage\n" \
     "16-17 ac -> 8 " DAMAGE_TYPE_FORCE " damage\n" \
     "18-19 ac -> 6 " DAMAGE_TYPE_FORCE " damage\n" \
     "20-21 ac -> 4 " DAMAGE_TYPE_FORCE " damage\n" \
     "22->23 ac -> 2 " DAMAGE_TYPE_FORCE " damage\n" \
     "24 ac and higher -> 0 damage\n"
 #define CHAOS_BREATH "annyone in a 90 degree cone in front of veraak needs to make a" \
     " dc 12 dex save, on a failed save takes 10 " DAMAGE_TYPE_NECROTIC " damage and" \
diff --git a/xavius.cpp b/xavius.cpp
index eabf9891fab2a01a576aba7b0a9c07da7afb11e6..1aa327742913b883078026144d926d3b8f8f6114 100644
--- a/xavius.cpp
+++ b/xavius.cpp
@@ -106,51 +106,51 @@ void ft_xavius_turn(t_char * info)
             info->dstats.health);
     return ;
 }
 
 static void ft_initialize_gear_and_feats(t_char * info)
 {
     (void)info;
     return ;
 }
 
 void    ft_xavius_loot(t_char * info)
 {
     (void)info;
     return ;
 }
 
 t_char *ft_xavius(const int index, const char **input, t_name *name, int exception)
 {
     int error = 0;
     t_char *info = static_cast<t_char *>(cma_malloc(sizeof(t_char)));
     if (!info)
     {
         pf_printf_fd(2, "105-Error: Failed to allocate memory info %s\n", input[0]);
         return (ft_nullptr);
     }
-    *info = XAVIUS_INFO;
+    ft_initialize_character_template(info, &XAVIUS_INFO);
     info->name = input[0];
     info->struct_name = name;
     info->save_file = cma_strjoin("data/", input[0]);
     if (!info->save_file)
     {
         ft_free_info(info);
         return (ft_nullptr);
     }
     if (index == 2)
     {
         if (ft_strcmp(input[1], "init") == 0)
         {
             int result = ft_dice_roll(info->hit_dice.dice_amount,
                     info->hit_dice.dice_faces);
             if (result == -1)
             {
                 pf_printf("147-Error Invalid hit dice %s", info->name);
                 ft_free_info(info);
                 return (ft_nullptr);
             }
             info->dstats.health = info->dstats.health + result;
             ft_file file(info->save_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR |
                     S_IWUSR);
             if (file.get_error())
             {
diff --git a/xavius.hpp b/xavius.hpp
index f69787d5a9e109a230ec96464b0cd3d393b92b48..95ea2265575a2afc8be9f8c3b5a266e4660bcd91 100644
--- a/xavius.hpp
+++ b/xavius.hpp
@@ -150,52 +150,52 @@ static const t_inventory XAVIUS_INVENTORY
 constexpr t_hit_dice XAVIUS_HIT_DICE =
 {
     .dice_amount = 0,
     .dice_faces = 0,
 };
 
 static const t_char XAVIUS_INFO =
 {
     .level = 0,
     .mechanical = 0,
     .passive_perception = 15,
     .initiative = -1,
     .version_number = 2,
     .save_file = ft_nullptr,
     .name = ft_nullptr,
     .turn = ft_xavius_turn,
     .drop_loot = ft_xavius_loot,
     .loot = INITIALIZE_LOOT,
     .hit_dice = XAVIUS_HIT_DICE,
     .inventory = XAVIUS_INVENTORY,
     .spells = INITIALIZE_SPELLS,
     .spell_slots = XAVIUS_SPELL_SLOTS,
     .flags = INITIALIZE_FLAGS,
     .crit = XAVIUS_CRIT,
     .attack_bonus = XAVIUS_ATTACK,
-    .bufs = INITIALIZE_BUFFS,
-    .debufs = INITIALIZE_DEBUFFS,
+    .bufs = ft_initialize_buffs(),
+    .debufs = ft_initialize_debuffs(),
     .concentration = INITIALIZE_CONCENTRATION,
     .d_resistance = XAVIUS_DEFAULT_RESISTANCE,
     .c_resistance = INITIALIZE_CURRENT_RESISTANCE,
     .equipment = XAVIUS_EQUIPMENT,
     .skill_mod = XAVIUS_SKILL_MODS,
     .save_mod = XAVIUS_SAVE_MODS,
     .stats = INITIALIZE_STATS,
     .dstats = XAVIUS_DEFAULT_STATS,
     .feats = INITIALIZE_FEATS,
     .struct_name = ft_nullptr,
     .physical = XAVIUS_PHYSICAL,
     .position = INITIALIZE_POSITION,
 };
 
 template <int Amount, int Faces>
 struct ValidateHitDice
 {
     static_assert
     (
         ((Amount == 0 && Faces == 0) || (Amount >= 1 && Faces >= 1)) &&
         (Amount <= 40 && Faces <= 12),
         "Invalid XAVIUS_HIT_DICE values: Either both must be 0 or both at least 1, " \
             "and the dice amount must not exceed 40, the dice faces must not exceed 12."
     );
 };
 
EOF
)
