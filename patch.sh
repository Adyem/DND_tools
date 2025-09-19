 (cd "$(git rev-parse --show-toplevel)" && git apply --3way <<'EOF' 
diff --git a/Makefile b/Makefile
index 09c3d25541ac86ab039c2444f52e627895e2f4ef..791044df8e7076889634075db1eba5e27017d628 100644
--- a/Makefile
+++ b/Makefile
@@ -104,51 +104,50 @@ SRC         = name.cpp \
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
               concentration.cpp \
               request_damage_taken.cpp \
               saving_throw.cpp \
               skill_throw.cpp \
               deal_damage.cpp \
               print_hp_status.cpp \
               turn.cpp \
               update_intiative_file.cpp \
               npc_set_stats_string.cpp \
               check_name.cpp \
               cast_concentration.cpp \
               free_info.cpp \
               get_character_info.cpp \
-              resize_double_char.cpp \
               check_buff_damage.cpp \
               attack.cpp \
               to_hit_check_buffs.cpp \
               kill.cpp \
               calculate_stats.cpp \
               trim_start.cpp \
               set_debuf.cpp \
               cast_hunters_mark.cpp \
               read_line.cpp \
               calculate_skills.cpp \
               calculate_resistance.cpp \
               calculate_damage_reduction.cpp \
               cast_chaos_armor.cpp \
               cast_concentration_caster.cpp \
               roll_dice.cpp \
               create_data_folder.cpp \
               cast_concentration_multi_target_01.cpp \
               cast_concentration_multi_target_02.cpp \
               ordinal_suffix.cpp \
               check_equipment.cpp \
               test.cpp \
               test_make_input.cpp \
               initialize_suggestions_readline.cpp \
               test_excecute.cpp \
               print_abilities.cpp \
diff --git a/cast_bless.cpp b/cast_bless.cpp
index 55e957e901b9673e814ef12bed1e0cc862ede564..21aacd425bff82d7ab19af9c051839d1a021a8f0 100644
--- a/cast_bless.cpp
+++ b/cast_bless.cpp
@@ -40,80 +40,77 @@ void ft_cast_bless(t_char *info, const char **input)
         return ;
     t_buff buff = MAKE_BUFF_BLESS(info->spells.bless, cast_at_level, input[3]);
     if (!buff.target)
     {
         pf_printf_fd(2, "121-Error: %s allocating memory bless target\n", info->name);
         return ;
     }
     int error = ft_cast_concentration_multi_target_01(info, &buff, input);
     cma_free(buff.target);
     if (error)
     {
         pf_printf_fd(2, "154-Error: %s allocating memory bless target\n", info->name);
         return ;
     }
     pf_printf("%s cast bless on %s\n", info->name, input[3]);
     ft_remove_spell_slot(&info->spell_slots, cast_at_level);
     return ;
 }
 
 int ft_cast_bless_apply_debuf(t_char * target, const char **input, t_buff *buff)
 {
 
     (void)buff;
     if (target)
     {
-        if (ft_is_caster_name_present(target->bufs.bless.caster_name, input[0]))
+        if (ft_is_caster_name_present(&target->bufs.bless.caster_name, input[0]))
         {
             pf_printf_fd(2, "102-Error: Caster name already present\n");
             return (1);
         }
         if (ft_update_caster_name(&target->bufs.bless.caster_name, input[0]))
             return (2);
     }
 
     if (DEBUG == 1 && target)
     {
-        int index = 0;
-        while (target->bufs.bless.caster_name
-                && target->bufs.bless.caster_name[index])
+        size_t              index;
+        size_t              count;
+        const ft_string    *names;
+
+        count = target->bufs.bless.caster_name.size();
+        if (count > 0)
         {
-            pf_printf("%s has cast bless\n", target->bufs.bless.caster_name[index]);
-            index++;
+            names = target->bufs.bless.caster_name.data();
+            if (names)
+            {
+                index = 0;
+                while (index < count)
+                {
+                    pf_printf("%s has cast bless\n", names[index].c_str());
+                    index++;
+                }
+            }
         }
     }
     return (0);
 }
 
 void    ft_concentration_remove_bless(t_char * character,
             t_target_data *targets_data)
 {
     int target_index = 0;
-    int caster_index;
-
     while (targets_data->target[target_index])
     {
-        caster_index = 0;
-        while (targets_data->target[target_index]->bufs.bless.caster_name[caster_index])
-        {
-            if (ft_strcmp(targets_data->target[target_index]->bufs.bless.caster_name
-                    [caster_index],
-                character->name) == 0)
-            {
-                cma_free(targets_data->target[target_index]->bufs.bless.caster_name
-                        [caster_index]);
-                targets_data->target[target_index]->bufs.bless.caster_name[caster_index]
-                    = ft_nullptr;
-            }
-            caster_index++;
-        }
+        targets_data->target[target_index]->bufs.bless.caster_name.remove(
+            ft_string(character->name));
         target_index++;
     }
     character->concentration.concentration = 0;
     character->concentration.spell_id = 0;
     character->concentration.dice_amount_mod = 0;
     character->concentration.dice_faces_mod = 0;
     character->concentration.base_mod = 0;
     character->concentration.targets = ft_nullptr;
     cma_free_double(character->concentration.targets);
     return ;
 }
diff --git a/cast_concentration_caster.cpp b/cast_concentration_caster.cpp
index 709d3ce9254abf44261dc28aa57f701a5d4a477a..539f62ad7ec96226ebba80df5aed671fcc5c8c54 100644
--- a/cast_concentration_caster.cpp
+++ b/cast_concentration_caster.cpp
@@ -1,38 +1,22 @@
 #include "dnd_tools.hpp"
-#include "libft/CMA/CMA.hpp"
+#include "libft/Errno/errno.hpp"
 #include "libft/Printf/printf.hpp"
 
-int ft_update_caster_name(char ***caster_name, const char *input_name)
+int ft_update_caster_name(ft_set<ft_string> *caster_name, const char *input_name)
 {
-    char **temp;
+    int error_code;
 
+    if (!caster_name || !input_name)
+        return (1);
     if (DEBUG == 1)
         pf_printf("adding the new caster name to the target struct %s\n", input_name);
-    if (!(*caster_name))
+    caster_name->insert(ft_string(input_name));
+    error_code = caster_name->get_error();
+    if (error_code != ER_SUCCESS && error_code != SET_NOT_FOUND)
     {
-        *caster_name = static_cast<char **>(cma_calloc(2, sizeof(char *)));
-        if (!(*caster_name))
-        {
-            pf_printf_fd(2, "165-Error allocating memory for caster name\n");
-            return (1);
-        }
-        **caster_name = cma_strdup(input_name);
-        if (!(**caster_name))
-        {
-            pf_printf_fd(2, "162-Error allocating memory for caster name\n");
-            return (1);
-        }
-    }
-    else
-    {
-        temp = ft_resize_double_char(*caster_name, input_name, 1);
-        if (!temp)
-        {
-            pf_printf_fd(2, "298-Error allocating memory for caster name\n");
-            return (1);
-        }
-        cma_free_double(*caster_name);
-        *caster_name = temp;
+        pf_printf_fd(2, "165-Error updating caster name: %s\n",
+            caster_name->get_error_str());
+        return (1);
     }
     return (0);
 }
diff --git a/cast_hunters_mark.cpp b/cast_hunters_mark.cpp
index ad5e905c04d1ea7fd24f58aef927e4664b793ae4..b78a14eb74f1539541c607726973c2efb9f4976f 100644
--- a/cast_hunters_mark.cpp
+++ b/cast_hunters_mark.cpp
@@ -41,80 +41,89 @@ void ft_cast_hunters_mark(t_char * info, const char **input)
         int cast_at_level = ft_prompt_spell_level(info, info->spells.hunters_mark.base_level,
                                 HUNTERS_MARK_NAME);
     if (cast_at_level == -1)
         return ;
     t_buff buff = MAKE_BUFF_HUNTERS_MARK(info->spells.hunters_mark, cast_at_level, input[3]);
     if (!buff.target)
     {
         pf_printf_fd(2, "121-Error allocating memory hunters mark target");
         return ;
     }
     int error = ft_cast_concentration(info, input, &buff);
     cma_free(buff.target);
     if (error)
         return ;
     pf_printf("%s cast hunters mark on %s\n", info->name, input[3]);
     ft_remove_spell_slot(&info->spell_slots, cast_at_level);
     return ;
 }
 
 int ft_cast_hunters_mark_apply_debuf(t_char *target, const char **input, t_buff *buff)
 {
 
     (void)buff;
     if (target)
     {
-        if (ft_is_caster_name_present(target->debufs.hunters_mark.caster_name, input[0]))
+        if (ft_is_caster_name_present(&target->debufs.hunters_mark.caster_name, input[0]))
         {
             pf_printf_fd(2, "102-Error: Caster name already present\n");
             return (1);
         }
         if (ft_update_caster_name(&target->debufs.hunters_mark.caster_name, input[0]))
             return (2);
     }
     if (DEBUG == 1 && target)
     {
-        int index = 0;
-        while (target->debufs.hunters_mark.caster_name
-                && target->debufs.hunters_mark.caster_name[index])
+        size_t              index;
+        size_t              count;
+        const ft_string    *names;
+
+        count = target->debufs.hunters_mark.caster_name.size();
+        if (count > 0)
         {
-            pf_printf("%s has cast hunter's mark\n", target->debufs.hunters_mark.caster_name[index]);
-            index++;
+            names = target->debufs.hunters_mark.caster_name.data();
+            if (names)
+            {
+                index = 0;
+                while (index < count)
+                {
+                    pf_printf("%s has cast hunter's mark\n", names[index].c_str());
+                    index++;
+                }
+            }
         }
     }
     target->debufs.hunters_mark.amount++;
     return (0);
 }
 
 void    ft_concentration_remove_hunters_mark(t_char *character, t_target_data *targets_data)
 {
     int target_index = 0;
-    int caster_index;
-
     while (targets_data->target[target_index])
     {
-        caster_index = 0;
-        while (targets_data->target[target_index]->debufs.hunters_mark.caster_name[caster_index])
+        ft_string                       caster_name(character->name);
+        ft_set<ft_string>               *caster_set;
+        const ft_string                *existing_name;
+
+        if (!caster_name.get_error())
         {
-            if (ft_strcmp(targets_data->target[target_index]->debufs.hunters_mark.caster_name
-                        [caster_index],
-                    character->name) == 0)
+            caster_set = &targets_data->target[target_index]->debufs.hunters_mark.caster_name;
+            existing_name = caster_set->find(caster_name);
+            if (existing_name)
             {
-                cma_free(targets_data->target[target_index]->debufs.hunters_mark.caster_name
-                        [caster_index]);
-                targets_data->target[target_index]->debufs.hunters_mark.caster_name[caster_index]
-                    = ft_nullptr;
-                targets_data->target[target_index]->debufs.hunters_mark.amount--;
+                caster_set->remove(caster_name);
+                if (targets_data->target[target_index]->debufs.hunters_mark.amount > 0)
+                    targets_data->target[target_index]->debufs.hunters_mark.amount--;
             }
-            caster_index++;
         }
         target_index++;
     }
     character->concentration.concentration = 0;
     character->concentration.spell_id = 0;
     character->concentration.dice_amount_mod = 0;
     character->concentration.dice_faces_mod = 0;
     character->concentration.base_mod = 0;
     character->concentration.targets = ft_nullptr;
     cma_free_double(character->concentration.targets);
     return ;
 }
diff --git a/cast_magic_drain.cpp b/cast_magic_drain.cpp
index 8020a331c6e141f4a567718a11ee2957ac5071cb..89e29bc299e989cec90e0ba727a29fc5f4ca8f4d 100644
--- a/cast_magic_drain.cpp
+++ b/cast_magic_drain.cpp
@@ -53,80 +53,89 @@ static bool generate_magic_drain_message(const t_char *info, ft_string &out_mess
 void    ft_cast_magic_drain(t_char *info, const char **input)
 {
     if (info->spells.magic_drain.cooldown != 0)
     {
         pf_printf("%s Magic Drain is on cooldown", info->name);
         return ;
     }
     ft_string message;
     if (generate_magic_drain_message(info, message))
         return ;
     if (ft_readline_confirm(message))
         return ;
     t_buff buff_info = MAKE_BUFF_MAGIC_DRAIN(info->spells.magic_drain, input[3]);
     int error = ft_cast_concentration(info, input, &buff_info);
     cma_free(buff_info.target);
     if (error)
         return ;
     info->spells.magic_drain.cooldown = 2;
 }
 
 int    ft_magic_drain_apply_debuff(t_char *target, const char **input, t_buff *buff)
 {
     (void)buff;
     if (target)
     {
-        if (ft_is_caster_name_present(target->debufs.magic_drain.caster, input[0]))
+        if (ft_is_caster_name_present(&target->debufs.magic_drain.caster, input[0]))
         {
             pf_printf_fd(2, "102-Error: Caster name already present\n");
             return (1);
         }
         if (ft_update_caster_name(&target->debufs.magic_drain.caster, input[0]))
             return (2);
     }
     if (DEBUG == 1 && target)
     {
-        int index = 0;
-        while (target->debufs.magic_drain.caster
-                && target->debufs.magic_drain.caster[index])
+        size_t              index;
+        size_t              count;
+        const ft_string    *names;
+
+        count = target->debufs.magic_drain.caster.size();
+        if (count > 0)
         {
-            pf_printf("%s has cast magic drain\n", target->debufs.magic_drain.caster[index]);
-            index++;
+            names = target->debufs.magic_drain.caster.data();
+            if (names)
+            {
+                index = 0;
+                while (index < count)
+                {
+                    pf_printf("%s has cast magic drain\n", names[index].c_str());
+                    index++;
+                }
+            }
         }
     }
     target->debufs.magic_drain.amount++;
     return (0);
 }
 
 void    ft_concentration_remove_magic_drain(t_char *character, t_target_data *targets_data)
 {
     int target_index = 0;
-    int caster_index;
-
     while (targets_data->target[target_index])
     {
-        caster_index = 0;
-        while (targets_data->target[target_index]->debufs.magic_drain.caster[caster_index])
+        ft_string                       caster_name(character->name);
+        ft_set<ft_string>               *caster_set;
+        const ft_string                *existing_name;
+
+        if (!caster_name.get_error())
         {
-            if (ft_strcmp(targets_data->target[target_index]->debufs.magic_drain.caster
-                        [caster_index],
-                    character->name) == 0)
+            caster_set = &targets_data->target[target_index]->debufs.magic_drain.caster;
+            existing_name = caster_set->find(caster_name);
+            if (existing_name)
             {
-                cma_free(targets_data->target[target_index]->debufs.magic_drain.caster
-                        [caster_index]);
-                targets_data->target[target_index]->debufs.magic_drain.caster[caster_index]
-                    = ft_nullptr;
-                targets_data->target[target_index]->debufs.magic_drain.amount--;
+                caster_set->remove(caster_name);
+                if (targets_data->target[target_index]->debufs.magic_drain.amount > 0)
+                    targets_data->target[target_index]->debufs.magic_drain.amount--;
             }
-            caster_index++;
         }
         target_index++;
     }
     character->concentration.concentration = 0;
     character->concentration.spell_id = 0;
     character->concentration.dice_amount_mod = 0;
     character->concentration.dice_faces_mod = 0;
     character->concentration.base_mod = 0;
     character->concentration.targets = ft_nullptr;
     cma_free_double(character->concentration.targets);
     return ;
 }
diff --git a/character.hpp b/character.hpp
index cdf281eec5f21faff7b1b6469412f167ee333781..35cb1070855556967d0e3c851732aab3492f7439 100644
--- a/character.hpp
+++ b/character.hpp
@@ -1,29 +1,31 @@
 #ifndef CHARACTER_H
 # define CHARACTER_H
 
 #include "libft/CPP_class/class_file.hpp"
+#include "libft/Template/set.hpp"
+#include "libft/CPP_class/class_string_class.hpp"
 
 # define ERROR_RESISTANCE 9999
 
 
 struct s_char;
 struct s_buff;
 struct s_name;
 struct s_equipment_id;
 struct s_loot;
 struct s_loot_item;
 
 typedef struct s_char t_char;
 typedef struct s_buff t_buff;
 typedef struct s_name t_name;
 typedef struct s_equipment_id t_equipment_id;
 typedef struct s_equipment_effect t_equipment_effect;
 typedef struct s_loot t_loot;
 typedef struct s_loot_item t_loot_item;
 typedef struct s_attack_info t_attack_info;
 
 typedef void    (*c_action)(t_char *, t_equipment_id *, int);
 typedef void    (*c_effect)(t_char *, t_equipment_id *,
                     t_equipment_effect *, t_attack_info *);
 typedef void    (*c_turn)(t_char *);
 typedef void    (*c_loot)(t_char *);
@@ -64,51 +66,51 @@ typedef struct    s_skills
     int    persuasion;
 }    t_skills;
 
 typedef struct    s_save
 {
     int    str;
     int    dex;
     int    inte;
     int    wis;
     int    cha;
     int    con;
 }    t_save;
 
 typedef struct    s_attack
 {
     int        attack_bonus;
     int        ranged_bonus;
 }    t_attack;
 
 typedef struct    s_buff_bless
 {
     int        duration;
     int        dice_amount_mod;
     int        dice_faces_mod;
     int        base_mod;
-    char    **caster_name;
+    ft_set<ft_string>    caster_name;
 }    t_buff_bless;
 
 typedef struct    s_buff_protective_winds
 {
     int    duration;
 }    t_buff_protective_winds;
 
 typedef struct    s_buff_lightning_strike
 {
     int    duration;
     int    amount;
     int distance;
     int    dice_amount;
     int    dice_faces;
     int    extra_damage;
 }    t_buff_lightning_strike;
 
 typedef struct s_buff_flame_geyser
 {
     int    amount;
     int duration;
     int    close_to_tower_d;
     int    tower_explode_d;
 }    t_buff_flame_geyser;
 
@@ -175,66 +177,66 @@ typedef struct    s_buff_rejuvenation
 
 typedef struct  s_buff_growth
 {
     int     stacks;
 }   t_buff_growth;
 
 typedef struct    s_bufs
 {
     t_buff_bless                bless;
     t_buff_protective_winds        protective_winds;
     t_buff_lightning_strike        lightning_strike;
     t_buff_lightning_strike        lightning_strikeV2;
     t_buff_flame_geyser            flame_geyser;
     t_buff_meteor_strike        meteor_strike;
     t_buff_chaos_armor            chaos_armor;
     t_buff_arcane_pounce        arcane_pounce;
     t_buff_earth_pounce            earth_pounce;
     t_buff_frost_breath            frost_breath;
     t_buff_shadow_illusion      shadow_illusion;
     t_buff_growth                growth;
     t_buff_rejuvenation            rejuvenation;
 }    t_bufs;
 
 typedef struct    s_debuff_magic_drain
 {
-    char    **caster;
+    ft_set<ft_string>    caster;
     int        amount;
     int        damage_flat;
     int        damage_dice_amount;
     int        damage_dice_faces;
     int        extra_damage_flat;
     int        extra_dice_amount;
     int        extra_dice_faces;
     int        spell_slot_total_level_drain;
     int        con_save;
 }    t_debuff_magic_drain;
 
 typedef struct    s_debuff_hunters_mark
 {
     int        amount;
-    char    **caster_name;
+    ft_set<ft_string>    caster_name;
 }    t_debuff_hunters_mark;
 
 typedef struct    s_debuff_blinded
 {
     int    duration;
 }    t_debuff_blinded;
 
 typedef struct    s_debuff_fell_poison
 {
     int duration;
 }    t_debuff_fell_poison;
 
 typedef struct s_debuff_shadow_touched
 {
     int    duration;
     int    stacks;
     int    armor_reduction_amount;
 }    t_debuff_shadow_touched;
 
 typedef struct s_debufs
 {
     t_debuff_hunters_mark    hunters_mark;
     t_debuff_blinded        blinded;
     t_debuff_magic_drain    magic_drain;
     t_debuff_fell_poison    fell_poison;
diff --git a/check_data.cpp b/check_data.cpp
index b0c16f05d4ab7bdf8676aa2463a522669458b122..dddf7004aa9db18f4896a9723f88fac7c3d1b534 100644
--- a/check_data.cpp
+++ b/check_data.cpp
@@ -222,70 +222,73 @@ static int check_buffs(t_char * info)
     error += check_range(info->debufs.magic_drain.damage_dice_amount, 0, 50, info->name,
             "magic drain dice amount (debuff)");
     error += check_range(info->debufs.magic_drain.damage_dice_faces, 0, 50, info->name,
             "magic drain dice faces (debuff)");
     error += check_range(info->debufs.magic_drain.spell_slot_total_level_drain, 0, 50, info->name,
             "magic drain spell slot total level drain (debuff)");
     error += check_range(info->debufs.magic_drain.con_save, 0, 50, info->name,
             "magic drain con save (debuff)");
     error += check_range(info->debufs.magic_drain.extra_damage_flat, 0, 50, info->name,
             "magic drain extra flat damage (debuff)");
     error += check_range(info->debufs.magic_drain.extra_dice_amount, 0, 50, info->name,
             "magic drain extra dice amount (debuff)");
     error += check_range(info->debufs.magic_drain.extra_dice_faces, 0, 50, info->name,
             "magic drain extra dice faces (debuff)");
     error += check_range(info->spells.magic_drain.learned, 0, 1, info->name,
             "magic drain learned (spell)");
     error += check_range(info->debufs.fell_poison.duration, 0, 50, info->name,
             "fell poison debuff duration");
     return (error);
 
 }
 
 static int check_other_buffs_debuffs(t_char * info)
 {
     int error = 0;
+    int caster_count;
     error += check_range(info->bufs.bless.duration, 0, 50, info->name, "bless duration");
     if (info->initiative < -50)
     {
         pf_printf("%s: initiative value (%d) is less than -50\n", info->name, info->initiative);
         error++;
     }
     if (info->bufs.lightning_strike.duration < 0)
     {
         pf_printf("%s: lightning strike duration (%d) is negative\n", info->name,
                 info->bufs.lightning_strike.duration);
         error++;
     }
+    caster_count = static_cast<int>(info->debufs.hunters_mark.caster_name.size());
     if (info->debufs.hunters_mark.amount < 0 || info->debufs.hunters_mark.amount
-            != ft_double_char_length(const_cast<const char **>(info->debufs.hunters_mark.caster_name)))
+            != caster_count)
     {
         pf_printf("%s: hunters mark data is not correct\n", info->name);
         error++;
     }
+    caster_count = static_cast<int>(info->debufs.magic_drain.caster.size());
     if (info->debufs.magic_drain.amount < 0 || info->debufs.magic_drain.amount
-            != ft_double_char_length(const_cast<const char **>(info->debufs.magic_drain.caster)))
+            != caster_count)
     {
         pf_printf("%s: magic drain data is not correct\n", info->name);
         error++;
     }
     if (info->bufs.protective_winds.duration < 0)
     {
         pf_printf("%s: protective winds duration (%d) is negative\n", info->name,
                 info->bufs.protective_winds.duration);
         error++;
     }
     if (info->bufs.chaos_armor.duration < 0)
     {
         pf_printf("%s: chaos armor duration (%d) is negative\n", info->name,
                 info->bufs.chaos_armor.duration);
         error++;
     }
     return (error);
 }
 
 static int ft_npc_check_info_2(t_char * info)
 {
     int error = 0;
     error += check_resistances(info);
     error += check_concentration(info);
     error += check_flags(info);
diff --git a/dnd_tools.hpp b/dnd_tools.hpp
index 08e3829641e3fa38d0e93901d3dfb1bcd170e963..69fee59b35f72ca66ef6bb189f04ee4ee414995e 100644
--- a/dnd_tools.hpp
+++ b/dnd_tools.hpp
@@ -339,92 +339,91 @@ void        ft_set_debuf_blinded(t_char * info, const char **input);
 void        ft_update_buf(t_char * info);
 void        ft_update_lightning_strike(t_char * info);
 void        ft_update_lightningV2_strike(t_char * info);
 void        ft_npc_update_lightning_strike(t_char * info, const char **input);
 void        ft_update_flame_geyser(t_char * info);
 void        ft_update_meteor_strike(t_char * info);
 void        ft_update_earth_pounce(t_char * info);
 void        ft_update_arcane_pounce(t_char * info);
 void        ft_update_frost_breath(t_char * info);
 void        ft_update_shadow_illusion(t_char * info);
 void        ft_update_buff_rejuvenation(t_char *info);
 void        ft_growth_stack(t_char * info, const char **input, int argc);
 
 // Feats
 void        ft_crackback(t_char * info, int number);
 
 // General buffs
 int         ft_check_bless(t_char * info);
 
 // Concentration
 void        ft_cast_hunters_mark(t_char *info, const char **input);
 int         ft_cast_concentration(t_char *info, const char **input, t_buff *buff);
 void        ft_check_concentration(t_char *info, int  damage);
 int         ft_remove_concentration(t_char *info);
 void        ft_cast_chaos_armor(t_char *info);
-int         ft_update_caster_name(char ***caster_name, const char *input_name);
+int         ft_update_caster_name(ft_set<ft_string> *caster_name, const char *input_name);
 int         ft_cast_concentration_multi_target_01(t_char *info, t_buff *buff, const char **input);
 void        ft_cast_concentration_multi_target_02(t_char *info,
                 t_target_data *target_data, const char **input);
-int         ft_is_caster_name_present(char **caster_name_list, const char *name);
+int         ft_is_caster_name_present(ft_set<ft_string> *caster_name_list, const char *name);
 
 // Hunters mark
 void        ft_concentration_remove_hunters_mark(t_char *character, t_target_data *targets_data);
 int         ft_cast_hunters_mark_apply_debuf(t_char *target, const char **input, t_buff *buff);
 
 // Bless
 void        ft_cast_bless(t_char *info, const char **input);
 int         ft_cast_bless_apply_debuf(t_char *target, const char **input, t_buff *buff);
 void        ft_concentration_remove_bless(t_char *character, t_target_data *targets_data);
 
 // Magic Drain
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
-char        **ft_resize_double_char(char **double_string, const char *string, size_t size);
 int         ft_double_char_length(const char **double_char);
 void        ft_dual_save_file(t_char * info, t_char * target);
 char        *ft_strtrim_prefix(const char *s1, const char *prefix);
 const char  *ft_ordinal_suffix(int number);
 int         ft_check_equipment_slots(t_char * character);
 void        ft_initialize_suggestions_readline();
 char        **ft_get_pc_list();
 void        ft_remove_element(char **array, char *element, bool free_element);
 void        ft_add_element(const char ***array, const char *element);
 void        ft_get_random_target(char **player_list, char **target_field);
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
diff --git a/free_info.cpp b/free_info.cpp
index 244aa6410ee0a3e1d86b52fe861d66f55d65ed82..ba1d0c5efba4dcfb5f76e8946c65e467accac059 100644
--- a/free_info.cpp
+++ b/free_info.cpp
@@ -1,23 +1,24 @@
 #include "libft/Printf/printf.hpp"
 #include "libft/CMA/CMA.hpp"
 #include "dnd_tools.hpp"
 #include <cstdlib>
 
 void    ft_free_info(t_char * info)
 {
     if (info && DEBUG == 1)
         pf_printf("freeing info %s\n", info->name);
-    cma_free_double(info->debufs.hunters_mark.caster_name);
+    info->bufs.bless.caster_name.clear();
+    info->debufs.hunters_mark.caster_name.clear();
     cma_free_double(info->concentration.targets);
-    cma_free_double(info->debufs.magic_drain.caster);
+    info->debufs.magic_drain.caster.clear();
     cma_free(info->bufs.meteor_strike.target_id);
     cma_free(info->bufs.frost_breath.target_id);
     cma_free(info->bufs.arcane_pounce.target_id);
     cma_free(info->bufs.earth_pounce.target_id);
     cma_free(info->loot.equipment);
     cma_free(info->loot.items);
     cma_free(info->spells.magic_drain.target);
     cma_free(info->save_file);
     cma_free(info);
     return ;
 }
diff --git a/initialize.hpp b/initialize.hpp
index 33ea11cb2097181c49f12997a06355d1a6d57f06..646d39417a40acf09cdc57bcc52f21363b864edc 100644
--- a/initialize.hpp
+++ b/initialize.hpp
@@ -167,51 +167,51 @@ static const    t_position INITIALIZE_POSITION =
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
 
 
 static const    t_buff_bless INITIALIZE_BUFF_BLESS =
 {
     .duration = 0,
     .dice_amount_mod = 0,
     .dice_faces_mod = 0,
     .base_mod = 0,
-    .caster_name = ft_nullptr,
+    .caster_name = ft_set<ft_string>(),
 };
 
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
@@ -279,61 +279,61 @@ static const    t_buff_growth INITIALIZE_BUFF_GROWTH =
 {
         .stacks = 0,
 };
 
 
 static const    t_bufs INITIALIZE_BUFFS =
 {
     .bless = INITIALIZE_BUFF_BLESS,
     .protective_winds = INITIALIZE_BUFF_PROTECTIVE_WINDS,
     .lightning_strike = INITIALIZE_BUFF_LIGHTNING_STRIKE,
     .lightning_strikeV2 = INITIALIZE_BUFF_LIGHTNING_STRIKE,
     .flame_geyser = INITIALIZE_BUFF_FLAME_GEYSER,
     .meteor_strike = INITIALIZE_BUFF_METEOR_STRIKE,
     .chaos_armor = INITIALIZE_BUFF_CHAOS_ARMOR,
     .arcane_pounce = INITIALIZE_BUFF_ARCANE_POUNCE,
     .earth_pounce = INITIALIZE_BUFF_EARTH_POUNCE,
     .frost_breath = INITIALIZE_BUFF_FROST_BREATH,
     .shadow_illusion = INITIALIZE_BUFF_SHADOW_ILLUSION,
     .growth = INITIALIZE_BUFF_GROWTH,
     .rejuvenation = INITIALIZE_BUFF_REJUVENATION,
 };
 
 static const    t_debuff_hunters_mark INITIALIZE_HUNTERS_MARK =
 {
     .amount = 0,
-    .caster_name = ft_nullptr,
+    .caster_name = ft_set<ft_string>(),
 };
 
 static const    t_debuff_blinded INITIALIZE_BLINDED =
 {
     .duration = 0,
 };
 
 static const    t_debuff_magic_drain INITIALIZE_DEBUFF_MAGIC_DRAIN =
 {
-    .caster = ft_nullptr,
+    .caster = ft_set<ft_string>(),
     .amount = 0,
     .damage_flat = 0,
     .damage_dice_amount = 0,
     .damage_dice_faces = 0,
     .extra_damage_flat = 0,
     .extra_dice_amount = 0,
     .extra_dice_faces = 0,
     .spell_slot_total_level_drain = 0,
     .con_save = 0,
 };
 
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
 
 static const    t_debufs INITIALIZE_DEBUFFS =
 {
diff --git a/libft b/libft
index c92d4f2f8829c26d1c929e95fd69c6615794b33d..7b56a9209436fbe6e7359d06b9c063633abbd34b 160000
--- a/libft
+++ b/libft
@@ -1 +1 @@
-Subproject commit c92d4f2f8829c26d1c929e95fd69c6615794b33d
+Subproject commit 7b56a9209436fbe6e7359d06b9c063633abbd34b
diff --git a/npc_set_stats.cpp b/npc_set_stats.cpp
index 7dcd097e737f970b1a5e1d6a6ffce9b037ebc487..a2a903097e0bc1fe7a340964c9c99ebee259f26e 100644
--- a/npc_set_stats.cpp
+++ b/npc_set_stats.cpp
@@ -2,50 +2,60 @@
 #include "libft/Printf/printf.hpp"
 #include "libft/CPP_class/class_nullptr.hpp"
 #include "treeNode.hpp"
 
 static int ft_handle_int_mapping(char **content, int index, t_char * info)
 {
     const t_treeNode_value *return_value
         = tree_node_search(*(ft_return_main_treeNode()), content[index]);
     if (!return_value)
         return (1);
     if (return_value->_return_field_integer && (return_value->_key_length != 0
                 && return_value->_return_field_integer != ft_nullptr)
                 && ((return_value->_unset_value == -1
                 || *(return_value->_return_field_integer) == return_value->_unset_value)))
     {
         *(return_value->_return_field_integer) = ft_check_stat(info, content[index],
                 return_value->_key_length);
         return (0);
     }
     else if (return_value->_return_field_double)
     {
         *return_value->_return_field_double = ft_set_stats_con_targets(content[index],
                 return_value->_key_length, *return_value->_return_field_double, info);
         return (0);
     }
+    else if (return_value->_return_field_string_set)
+    {
+        if (ft_update_caster_name(return_value->_return_field_string_set,
+                &content[index][return_value->_key_length]))
+        {
+            info->flags.error = 1;
+            return (1);
+        }
+        return (0);
+    }
     else if (return_value->_return_field_string)
     {
         ft_set_stat_player(return_value->_key_length,
                 const_cast<const char **>(return_value->_return_field_string), content[index]);
         return (0);
     }
     return (1);
 }
 
 int ft_set_stats(t_char * info, char **content)
 {
     if (initialize_stat_key_value_pairs(info))
         return (1);
     int index = 0;
     while (content[index])
     {
         if (ft_handle_int_mapping(content, index, info) == 0)
         {
             index++;
             continue ;
         }
         pf_printf_fd(2, "1-Something is wrong with the save file for %s at the line: %s"
                          ", please reinitialize the save\n", info->name, content[index]);
         info->flags.error = 1;
         return (1);
diff --git a/resize_double_char.cpp b/resize_double_char.cpp
deleted file mode 100644
index f6f3ceee9cdd963d7a78efc3c062c4969493d1f3..0000000000000000000000000000000000000000
--- a/resize_double_char.cpp
+++ /dev/null
@@ -1,52 +0,0 @@
-#include "dnd_tools.hpp"
-#include "libft/CMA/CMA.hpp"
-#include "libft/CPP_class/class_nullptr.hpp"
-#include <cstdlib>
-
-char **ft_resize_double_char(char **double_string, const char *string, size_t size)
-{
-    if (!double_string)
-        return (ft_nullptr);
-    size_t current_count = 0;
-    while (double_string[current_count])
-        current_count++;
-    char **resized_array = static_cast<char **>(cma_calloc(current_count + size + 1, sizeof(char *)));
-    if (!resized_array)
-        return (ft_nullptr);
-    size_t index = 0;
-    while (index < current_count)
-    {
-        resized_array[index] = cma_strdup(double_string[index]);
-        if (!resized_array[index])
-        {
-            index--;
-            while (index > 0)
-            {
-                cma_free(resized_array[index]);
-                index--;
-            }
-            cma_free(resized_array);
-            return (ft_nullptr);
-        }
-        index++;
-    }
-    resized_array[current_count] = cma_strdup(string);
-    if (!resized_array[current_count])
-    {
-        index = 0;
-        while (index < current_count)
-        {
-            cma_free(resized_array[index]);
-            index++;
-        }
-        cma_free(resized_array);
-        return (ft_nullptr);
-    }
-    size_t additional_index = current_count + 1;
-    while (additional_index < current_count + size + 1)
-    {
-        resized_array[additional_index] = ft_nullptr;
-        additional_index++;
-    }
-    return (resized_array);
-}
diff --git a/save_data.cpp b/save_data.cpp
index 0b4e76856a57f625ed8db263870bbdfcec66cf10..e0c4928e63ba71f9256a2bf0045847bc33571232 100644
--- a/save_data.cpp
+++ b/save_data.cpp
@@ -1,50 +1,74 @@
 #include "dnd_tools.hpp"
 #include "libft/CPP_class/class_nullptr.hpp"
 #include "libft/Printf/printf.hpp"
 #include "key_list.hpp"
 #include <fcntl.h>
 #include <unistd.h>
 #include <cerrno>
 
 static void ft_npc_write_file_double_char(const char *msg, char **targets, ft_file &file,
                                             t_char *info)
 {
     int index = 0;
     if (targets)
     {
         while (targets[index])
         {
             if (DEBUG == 1)
                 pf_printf_fd(1, "saving array %s %s%s\n", info->name, msg, targets[index]);
             file.printf("%s%s\n", msg, targets[index]);
             index++;
         }
     }
     return ;
 }
 
+static void ft_npc_write_file_string_set(const char *msg, const ft_set<ft_string> &targets,
+        ft_file &file, t_char *info)
+{
+    size_t              index;
+    size_t              count;
+    const ft_string    *names;
+
+    count = targets.size();
+    if (count == 0)
+        return ;
+    names = targets.data();
+    if (!names)
+        return ;
+    index = 0;
+    while (index < count)
+    {
+        if (DEBUG == 1)
+            pf_printf_fd(1, "saving array %s %s%s\n", info->name, msg, names[index].c_str());
+        file.printf("%s%s\n", msg, names[index].c_str());
+        index++;
+    }
+    return ;
+}
+
 static void ft_npc_write_spell_slots(t_char * info, ft_file &file)
 {
     file.printf("%s%i\n", LEVEL_1_AVAILABLE_KEY, info->spell_slots.level_1.available);
     file.printf("%s%i\n", LEVEL_1_TOTAL_KEY, info->spell_slots.level_1.total);
     file.printf("%s%i\n", LEVEL_1_LEVEL_KEY, info->spell_slots.level_1.level);
     file.printf("%s%i\n", LEVEL_1_REPLENISHING_SLOT_KEY,
             info->spell_slots.level_1.replenishing_slot);
     file.printf("%s%i\n", LEVEL_2_AVAILABLE_KEY, info->spell_slots.level_2.available);
     file.printf("%s%i\n", LEVEL_2_TOTAL_KEY, info->spell_slots.level_2.total);
     file.printf("%s%i\n", LEVEL_2_LEVEL_KEY, info->spell_slots.level_2.level);
     file.printf("%s%i\n", LEVEL_2_REPLENISHING_SLOT_KEY,
             info->spell_slots.level_2.replenishing_slot);
     file.printf("%s%i\n", LEVEL_3_AVAILABLE_KEY, info->spell_slots.level_3.available);
     file.printf("%s%i\n", LEVEL_3_TOTAL_KEY, info->spell_slots.level_3.total);
     file.printf("%s%i\n", LEVEL_3_LEVEL_KEY, info->spell_slots.level_3.level);
     file.printf("%s%i\n", LEVEL_3_REPLENISHING_SLOT_KEY,
             info->spell_slots.level_3.replenishing_slot);
     file.printf("%s%i\n", LEVEL_4_AVAILABLE_KEY, info->spell_slots.level_4.available);
     file.printf("%s%i\n", LEVEL_4_TOTAL_KEY, info->spell_slots.level_4.total);
     file.printf("%s%i\n", LEVEL_4_LEVEL_KEY, info->spell_slots.level_4.level);
     file.printf("%s%i\n", LEVEL_4_REPLENISHING_SLOT_KEY,
             info->spell_slots.level_4.replenishing_slot);
     file.printf("%s%i\n", LEVEL_5_AVAILABLE_KEY, info->spell_slots.level_5.available);
     file.printf("%s%i\n", LEVEL_5_TOTAL_KEY, info->spell_slots.level_5.total);
     file.printf("%s%i\n", LEVEL_5_LEVEL_KEY, info->spell_slots.level_5.level);
@@ -57,51 +81,51 @@ static void ft_npc_write_spell_slots(t_char * info, ft_file &file)
             info->spell_slots.level_6.replenishing_slot);
     file.printf("%s%i\n", LEVEL_7_AVAILABLE_KEY, info->spell_slots.level_7.available);
     file.printf("%s%i\n", LEVEL_7_TOTAL_KEY, info->spell_slots.level_7.total);
     file.printf("%s%i\n", LEVEL_7_LEVEL_KEY, info->spell_slots.level_7.level);
     file.printf("%s%i\n", LEVEL_7_REPLENISHING_SLOT_KEY,
             info->spell_slots.level_7.replenishing_slot);
     file.printf("%s%i\n", LEVEL_8_AVAILABLE_KEY, info->spell_slots.level_8.available);
     file.printf("%s%i\n", LEVEL_8_TOTAL_KEY, info->spell_slots.level_8.total);
     file.printf("%s%i\n", LEVEL_8_LEVEL_KEY, info->spell_slots.level_8.level);
     file.printf("%s%i\n", LEVEL_8_REPLENISHING_SLOT_KEY,
             info->spell_slots.level_8.replenishing_slot);
     file.printf("%s%i\n", LEVEL_9_AVAILABLE_KEY, info->spell_slots.level_9.available);
     file.printf("%s%i\n", LEVEL_9_TOTAL_KEY, info->spell_slots.level_9.total);
     file.printf("%s%i\n", LEVEL_9_LEVEL_KEY, info->spell_slots.level_9.level);
     file.printf("%s%i\n", LEVEL_9_REPLENISHING_SLOT_KEY,
             info->spell_slots.level_9.replenishing_slot);
     file.printf("%s%i\n", WARLOCK_AVAILABLE_KEY, info->spell_slots.warlock.available);
     file.printf("%s%i\n", WARLOCK_TOTAL_KEY, info->spell_slots.warlock.total);
     file.printf("%s%i\n", WARLOCK_LEVEL_KEY, info->spell_slots.warlock.level);
     file.printf("%s%i\n", WARLOCK_REPLENISHING_SLOT_KEY,
             info->spell_slots.warlock.replenishing_slot);
     file.printf("%s%i\n", BUFF_BLESS_BASE_MOD_KEY, info->bufs.bless.base_mod);
     file.printf("%s%i\n", BUFF_BLESS_DURATION_KEY, info->bufs.bless.duration);
     file.printf("%s%i\n", BUFF_BLESS_DICE_FACES_MOD_KEY, info->bufs.bless.dice_faces_mod);
     file.printf("%s%i\n", BUFF_BLESS_DICE_AMOUNT_MOD_KEY, info->bufs.bless.dice_amount_mod);
-    ft_npc_write_file_double_char(BUFF_BLESS_CASTER_NAME_KEY,
+    ft_npc_write_file_string_set(BUFF_BLESS_CASTER_NAME_KEY,
             info->bufs.bless.caster_name, file, info);
     file.printf("%s%i\n", BUFF_REJUVENATION_DURATION_KEY, info->bufs.rejuvenation.duration);
     file.printf("%s%i\n", BUFF_REJUVENATION_DICE_AMOUNT_KEY,
             info->bufs.rejuvenation.healing_dice_amount);
     file.printf("%s%i\n", BUFF_REJUVENATION_DICE_FACES_KEY,
             info->bufs.rejuvenation.healing_dice_faces);
     file.printf("%s%i\n",BUFF_REJUVENATION_EXTRA_KEY, info->bufs.rejuvenation.healing_extra);
     return ;
 }
 
 static void ft_npc_write_file_1(t_char * info, t_stats *stats, ft_file &file)
 {
     file.printf("%s%i\n", HEALTH_KEY, stats->health);
     file.printf("%s%i\n", MAX_HEALTH_KEY, info->dstats.health);
     file.printf("%s%i\n", TEMP_HP_KEY, stats->temp_hp);
     file.printf("%s%i\n", STR_KEY, stats->str);
     file.printf("%s%i\n", DEX_KEY, stats->dex);
     file.printf("%s%i\n", CON_KEY, stats->con);
     file.printf("%s%i\n", INT_KEY, stats->inte);
     file.printf("%s%i\n", WIS_KEY, stats->wis);
     file.printf("%s%i\n", CHA_KEY, stats->cha);
     file.printf("%s%i\n", TURN_KEY, stats->turn);
     file.printf("%s%i\n", PHASE_KEY, stats->phase);
     file.printf("%s%i\n", INITIATIVE_KEY, info->initiative);
     file.printf("%s%i\n", POSITION_X_KEY, info->position.x);
@@ -116,51 +140,51 @@ static void ft_npc_write_file_1(t_char * info, t_stats *stats, ft_file &file)
 static void ft_npc_write_file_2(t_char * info, t_resistance *resistance, ft_file &file)
 {
     file.printf("%s%i\n", ACID_RESISTANCE_KEY, resistance->acid);
     file.printf("%s%i\n", BLUDGEONING_RESISTANCE_KEY, resistance->bludgeoning);
     file.printf("%s%i\n", COLD_RESISTANCE_KEY, resistance->cold);
     file.printf("%s%i\n", FIRE_RESISTANCE_KEY, resistance->fire);
     file.printf("%s%i\n", FORCE_RESISTANCE_KEY, resistance->force);
     file.printf("%s%i\n", LIGHTNING_RESISTANCE_KEY, resistance->lightning);
     file.printf("%s%i\n", NECROTIC_RESISTANCE_KEY, resistance->necrotic);
     file.printf("%s%i\n", PIERCING_RESISTANCE_KEY, resistance->piercing);
     file.printf("%s%i\n", POISON_RESISTANCE_KEY, resistance->poison);
     file.printf("%s%i\n", PSYCHIC_RESISTANCE_KEY, resistance->psychic);
     file.printf("%s%i\n", RADIANT_RESISTANCE_KEY, resistance->radiant);
     file.printf("%s%i\n", SLASHING_RESISTANCE_KEY, resistance->slashing);
     file.printf("%s%i\n", THUNDER_RESISTANCE_KEY, resistance->thunder);
     file.printf("%s%i\n", CONCENTRATION_KEY, info->concentration.concentration);
     file.printf("%s%i\n", CONC_SPELL_ID_KEY, info->concentration.spell_id);
     file.printf("%s%i\n", CONC_DICE_AMOUNT_KEY, info->concentration.dice_amount_mod);
     file.printf("%s%i\n", CONC_DICE_FACES_KEY, info->concentration.dice_faces_mod);
     file.printf("%s%i\n", CONC_BASE_MOD_KEY, info->concentration.base_mod);
     file.printf("%s%i\n", CONC_DURATION_KEY, info->concentration.duration);
     ft_npc_write_file_double_char(CONC_TARGETS_KEY,
             info->concentration.targets, file, info);
     file.printf("%s%i\n", HUNTERS_MARK_AMOUNT_KEY,
             info->debufs.hunters_mark.amount);
-    ft_npc_write_file_double_char(HUNTERS_MARK_CASTER_KEY,
+    ft_npc_write_file_string_set(HUNTERS_MARK_CASTER_KEY,
             info->debufs.hunters_mark.caster_name, file, info);
     file.printf("%s%i\n", CHAOS_ARMOR_DURATION_KEY,
             info->bufs.chaos_armor.duration);
     file.printf("%s%i\n", PRONE_KEY,
             info->flags.prone);
     file.printf("%s%i\n", BLINDED_KEY,
             info->debufs.blinded.duration);
     file.printf("%s%i\n", FLAME_GEYSER_DURATION_KEY,
             info->bufs.flame_geyser.duration);
     file.printf("%s%i\n", FLAME_GEYSER_CLOSE_TO_TOWER_D_KEY,
             info->bufs.flame_geyser.close_to_tower_d);
     file.printf("%s%i\n", FLAME_GEYSER_TOWER_EXPLODE_D_KEY,
             info->bufs.flame_geyser.tower_explode_d);
     file.printf("%s%i\n", FLAME_GEYSER_AMOUNT_KEY,
             info->bufs.flame_geyser.amount);
     file.printf("%s%i\n", METEOR_STRIKE_DURATION_KEY,
             info->bufs.meteor_strike.duration);
     file.printf("%s%i\n", METEOR_STRIKE_ONE_TARGET_D_KEY,
             info->bufs.meteor_strike.one_target_d);
     file.printf("%s%i\n", METEOR_STRIKE_TWO_TARGETS_D_KEY,
             info->bufs.meteor_strike.two_targets_d);
     file.printf("%s%i\n", METEOR_STRIKE_THREE_TARGETS_D_KEY,
             info->bufs.meteor_strike.three_targets_d);
     file.printf("%s%i\n", METEOR_STRIKE_FOUR_TARGETS_D_KEY,
             info->bufs.meteor_strike.four_targets_d);
@@ -226,52 +250,52 @@ static void ft_npc_write_file_2(t_char * info, t_resistance *resistance, ft_file
             info->spells.magic_drain.damage_dice_amount);
     file.printf("%s%i\n", SPELL_MAGIC_DRAIN_DICE_FACES_KEY,
             info->spells.magic_drain.damage_dice_faces);
     file.printf("%s%i\n", SPELL_MAGIC_DRAIN_SPELL_SLOT_TOTAL_LEVEL_DRAIN_KEY,
             info->spells.magic_drain.spell_slot_total_level_drain);
     if (info->spells.magic_drain.target)
         file.printf("%s%s\n", SPELL_MAGIC_DRAIN_TARGET_KEY, info->spells.magic_drain.target);
     file.printf("%s%i\n", SPELL_MAGIC_DRAIN_DEX_SAVE_KEY, info->spells.magic_drain.dex_save);
     file.printf("%s%i\n", SPELL_MAGIC_DRAIN_TURNS_PASSED_FROM_LAST_CAST_KEY,
             info->spells.magic_drain.turns_passed_fron_last_cast);
     file.printf("%s%i\n", SPELL_MAGIC_DRAIN_EXTRA_DAMAGE_FLAT_KEY,
             info->spells.magic_drain.extra_damage_flat);
     file.printf("%s%i\n", SPELL_MAGIC_DRAIN_EXTRA_DICE_AMOUNT_KEY,
             info->spells.magic_drain.extra_dice_amount);
     file.printf("%s%i\n", SPELL_MAGIC_DRAIN_EXTRA_DICE_FACES_KEY,
             info->spells.magic_drain.extra_dice_faces);
     file.printf("%s%i\n", SPELL_MAGIC_DRAIN_COOLDOWN_KEY, info->spells.magic_drain.cooldown);
 
     file.printf("%s%i\n", DEBUFF_MAGIC_DRAIN_DAMAGE_FLAT_KEY, info->debufs.magic_drain.damage_flat);
     file.printf("%s%i\n", DEBUFF_MAGIC_DRAIN_DICE_AMOUNT_KEY,
             info->debufs.magic_drain.damage_dice_amount);
     file.printf("%s%i\n", DEBUFF_MAGIC_DRAIN_DICE_FACES_KEY,
             info->debufs.magic_drain.damage_dice_faces);
     file.printf("%s%i\n", DEBUFF_MAGIC_DRAIN_SPELL_SLOT_TOTAL_LEVEL_DRAIN_KEY,
             info->debufs.magic_drain.spell_slot_total_level_drain);
-    ft_npc_write_file_double_char(DEBUFF_MAGIC_DRAIN_CASTER_KEY, info->debufs.magic_drain.caster,
-            file, info);
+    ft_npc_write_file_string_set(DEBUFF_MAGIC_DRAIN_CASTER_KEY,
+            info->debufs.magic_drain.caster, file, info);
     file.printf("%s%i\n", DEBUFF_MAGIC_DRAIN_CON_SAVE_KEY, info->debufs.magic_drain.con_save);
     file.printf("%s%i\n", DEBUFF_MAGIC_DRAIN_EXTRA_DAMAGE_FLAT_KEY,
             info->debufs.magic_drain.extra_damage_flat);
     file.printf("%s%i\n", DEBUFF_MAGIC_DRAIN_EXTRA_DICE_AMOUNT_KEY,
             info->debufs.magic_drain.extra_dice_amount);
     file.printf("%s%i\n", DEBUFF_MAGIC_DRAIN_EXTRA_DICE_FACES_KEY,
             info->debufs.magic_drain.extra_dice_faces);
     file.printf("%s%i\n", SPELL_MAGIC_DRAIN_LEARNED_KEY, info->spells.magic_drain.learned);
     return ;
 }
 
 void ft_npc_write_file(t_char * info, t_stats *stats, t_resistance *resistance,
         ft_file &file)
 {
     if (DEBUG == 1)
         pf_printf("fd = %i\n", file.get_fd());
     if (info->flags.alreaddy_saved)
         return ;
     if (DEBUG == 1)
         pf_printf("saving %s %i\n", info->name, stats->health);
     ft_npc_write_file_1(info, stats, file);
     ft_npc_write_file_2(info, resistance, file);
     ft_npc_write_spell_slots(info, file);
     info->flags.alreaddy_saved = 1;
     return ;
diff --git a/treeNode.cpp b/treeNode.cpp
index 88a52fe2086826b03e88fb5db963edd234171264..cea986e3a90c03f16a5294fcefa155b7e6cc1fdf 100644
--- a/treeNode.cpp
+++ b/treeNode.cpp
@@ -11,103 +11,114 @@ TreeNode *tree_node_new(void)
         return (ft_nullptr);
     new (&node->_children) ft_unord_map<char, TreeNode*>();
     node->_data  = ft_nullptr;
     node->_error = 0;
     return (node);
 }
 
 void tree_node_delete(TreeNode *node)
 {
     if (!node)
         return ;
     auto it = node->_children.begin();
     while (it != node->_children.end())
     {
         tree_node_delete(it->second);
         ++it;
     }
     node->_children.~ft_unord_map<char, TreeNode*>();
     if (node->_data)
         cma_free(node->_data);
     cma_free(node);
     return ;
 }
 
 static int tree_node_insert_helper(TreeNode *node, const char *key, int unset_value,
-                              int *int_val, char **str_val, char ***dbl_val)
+                              int *int_val, char **str_val, char ***dbl_val,
+                              ft_set<ft_string> *set_val)
 {
     if (node->_error)
         return (1);
     size_t length = ft_strlen_size_t(key);
     TreeNode *current = node;
     const char *ptr = key;
     while (*ptr)
     {
         char ch = *ptr++;
         if (!current->_children[ch])
         {
             TreeNode *child = tree_node_new();
             if (!child)
             {
                 node->_error = 1;
                 return (1);
             }
             current->_children[ch] = child;
         }
         current = current->_children[ch];
     }
     if (!current->_data)
     {
         current->_data = static_cast<t_treeNode_value *>(cma_malloc(sizeof(t_treeNode_value)));
         if (!current->_data)
         {
             node->_error = 1;
             return (1);
         }
     }
     ft_bzero(current->_data, sizeof(t_treeNode_value));
     current->_data->_unset_value           = unset_value;
     current->_data->_key_length            = length;
     current->_data->_return_field_integer  = int_val;
     current->_data->_return_field_string   = str_val;
     current->_data->_return_field_double   = dbl_val;
+    current->_data->_return_field_string_set = set_val;
     return (0);
 }
 
 int tree_node_insert(TreeNode *node, const char *key, int *value, int unset_value)
 {
-    return (tree_node_insert_helper(node, key, unset_value, value, ft_nullptr, ft_nullptr));
+    return (tree_node_insert_helper(node, key, unset_value, value, ft_nullptr, ft_nullptr,
+            ft_nullptr));
 }
 
 int tree_node_insert(TreeNode *node, const char *key, char **value)
 {
-    return (tree_node_insert_helper(node, key, 0, ft_nullptr, value, ft_nullptr));
+    return (tree_node_insert_helper(node, key, 0, ft_nullptr, value, ft_nullptr,
+            ft_nullptr));
 }
 
 int tree_node_insert(TreeNode *node, const char *key, char ***value)
 {
-    return (tree_node_insert_helper(node, key, 0, ft_nullptr, ft_nullptr, value));
+    return (tree_node_insert_helper(node, key, 0, ft_nullptr, ft_nullptr, value,
+            ft_nullptr));
+}
+
+int tree_node_insert(TreeNode *node, const char *key, ft_set<ft_string> *value)
+{
+    return (tree_node_insert_helper(node, key, 0, ft_nullptr, ft_nullptr, ft_nullptr,
+            value));
 }
 
 const t_treeNode_value *tree_node_search(const TreeNode *node, const char *key)
 {
     if (node->_error)
         return (ft_nullptr);
     const TreeNode *current = node;
     while (*key != '=')
     {
         auto it = current->_children.find(*key);
         if (it == current->_children.end())
             return (ft_nullptr);
         current = it->second;
         key++;
     }
     if (*key == '=')
     {
         auto it = current->_children.find(*key);
         if (it == current->_children.end())
             return (ft_nullptr);
         current = it->second;
         key++;
     }
     else
         return (ft_nullptr);
diff --git a/treeNode.hpp b/treeNode.hpp
index 6e07f036eca49a12a1d6557cd2eca61fe99bb9d1..ee8ce067fb256e20e22178368353602f01b0846f 100644
--- a/treeNode.hpp
+++ b/treeNode.hpp
@@ -1,46 +1,50 @@
 #ifndef TREENODE_HPP
 #define TREENODE_HPP
 
 #ifndef DEBUG
 # define DEBUG 0
 #endif
 
 #include <csignal>
 #include "libft/Template/unordened_map.hpp"
+#include "libft/Template/set.hpp"
+#include "libft/CPP_class/class_string_class.hpp"
 
 typedef struct s_treeNode_value
 {
     size_t   _key_length;
     int       _unset_value;
     int       *_return_field_integer;
     char      **_return_field_string;
     char      ***_return_field_double;
+    ft_set<ft_string> *_return_field_string_set;
 } t_treeNode_value;
 
 typedef struct s_treeNode
 {
     t_treeNode_value *_data;
     int _error;
     ft_unord_map<char, struct s_treeNode*> _children;
 } TreeNode;
 
 // Function declarations for creating/destroying nodes:
 TreeNode *tree_node_new(void);
 void tree_node_delete(TreeNode *node);
 
 // Insertion functions:
 int tree_node_insert(TreeNode *node, const char *key, int *value, int unset_value);
 int tree_node_insert(TreeNode *node, const char *key, char **value);
 int tree_node_insert(TreeNode *node, const char *key, char ***value);
+int tree_node_insert(TreeNode *node, const char *key, ft_set<ft_string> *value);
 
 // Search function:
 const t_treeNode_value *tree_node_search(const TreeNode *node, const char *key);
 
 // Accessor for the error flag:
 int tree_node_get_error(const TreeNode *node);
 
 // Main tree functions (used by other parts of your code):
 TreeNode **ft_return_main_treeNode(void);
 void ft_cleanup_treeNode(void);
 
 #endif
diff --git a/utils02.cpp b/utils02.cpp
index 7c28e81d7d3ed08023289746bca2ffb830b187f7..3a5c4b1b1fb49e78587baade05bb891b3007991f 100644
--- a/utils02.cpp
+++ b/utils02.cpp
@@ -1,27 +1,32 @@
 #include "dnd_tools.hpp"
+#include "libft/Errno/errno.hpp"
 #include <fcntl.h>
 #include <unistd.h>
 
 int ft_double_char_length(const char **double_char)
 {
     if (!double_char)
         return (0);
     int index = 0;
     while (double_char[index])
         index++;
     return (index);
 }
 
-int ft_is_caster_name_present(char **caster_name_list, const char *name)
+int ft_is_caster_name_present(ft_set<ft_string> *caster_name_list, const char *name)
 {
+    const ft_string    *existing_name;
+    ft_string           search_value(name);
+
     if (!caster_name_list || !name)
         return (0);
-    int index = 0;
-    while (caster_name_list[index])
-    {
-        if (ft_strcmp(caster_name_list[index], name) == 0)
-            return (1);
-        index++;
-    }
+    if (search_value.get_error())
+        return (0);
+    existing_name = caster_name_list->find(search_value);
+    if (existing_name)
+        return (1);
+    if (caster_name_list->get_error() != SET_NOT_FOUND
+        && caster_name_list->get_error() != ER_SUCCESS)
+        return (1);
     return (0);
 }
 
EOF
)
