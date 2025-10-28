#include "dnd_tools.hpp"
#include "libft/Printf/printf.hpp"

void print_meteor_strike(const t_char * info)
{
    const char *target;

    if (info->bufs.meteor_strike.target_id)
        target = info->bufs.meteor_strike.target_id;
    else
        target = "the target";
    pf_printf("Meteor Strike: Create a circle around %s with arrows " \
            "pointing towards the center (10ft radius)", target);
    pf_printf("at the start of the next turn a meteor hits the target dealing " \
            "damage dependent on the number of targets hit.\n");
    pf_printf("(Cannot be the same target as Arcane Pounce or Earth Pounce)\n");
    pf_printf("1 target\t\t%d fire damage\n", info->bufs.meteor_strike.one_target_d);
    pf_printf("2 targets\t\t%d fire damage each\n",
            info->bufs.meteor_strike.two_targets_d);
    pf_printf("3 targets\t\t%d fire damage each\n",
            info->bufs.meteor_strike.three_targets_d);
    pf_printf("4 or more targets\t%d fire damage each\n",
            info->bufs.meteor_strike.four_targets_d);
    return ;
}

void print_lightning_strike(const t_char * info)
{
    pf_printf("Lightning Strike: The boss's skin will flare with electricity at " \
            "the start of the boss's next turn ");
    pf_printf("and will deal %d lightning damage to anyone within %d ft.\n", 
              info->bufs.lightning_strike.amount * 4,
              info->bufs.lightning_strike.distance);
    return ;
}

void print_flame_geyser(const t_char * info)
{
    pf_printf("Flame Geyser: %d red towers spawn at random locations. If no one " \
            "stands underneath a tower at the start of the boss's next turn, it " \
            "will explode, dealing %d fire damage to every member in the " \
            "party. If one or more players stand underneath a tower, it deals %d " \
            "fire damage to each of those players.\n", 
              info->bufs.flame_geyser.amount, info->bufs.flame_geyser.tower_explode_d,
              info->bufs.flame_geyser.close_to_tower_d);
    pf_printf("(Be careful with placement on the flame geyser’s so they don’t " \
            "appear in areas where other abilities are going to hit)\n");
    return ;
}

void print_frost_breath(const t_char * info)
{
    const char *target;

    if (info->bufs.frost_breath.target_id)
        target = info->bufs.frost_breath.target_id;
    else
        target = "a random target";
    pf_printf("Frost Breath: The boss looks at %s and takes a deep breath and breathes " \
            "out on its next turn, dealing %i cold damage to anyone in a 90-degree "
            "cone in front of him.\n", target, info->bufs.frost_breath.damage);
    pf_printf("(Be clear about what way the boss is facing when " \
            "he starts casting the ability)\n");
    return ;
}

void print_lightning_strike_v2(const t_char * info)
{
    pf_printf("Lightning Strike V2: A marker appears at a random location, " \
            "indicating where lightning will strike.\n");
    pf_printf("At the start of the boss's next turn, it deals %d lightning " \
            "damage to everyone, reduced by 2 for each 5ft of distance " \
            "from the marker up to a minimum of %d.\n",
              info->bufs.lightning_strikeV2.dice_amount * 6,
              info->bufs.lightning_strikeV2.distance);
    pf_printf("(Be careful with placement on Lightning Strike V2 so it isn’t " \
            "on top of flame geysers)\n");
        return ;
}

void print_arcane_pounce(const t_char * info)
{
    const char *target;

    if (info->bufs.arcane_pounce.target_id)
        target = info->bufs.arcane_pounce.target_id;
    else
        target = "the target";
    pf_printf("Arcane Pounce: Targets a random player. At the start of the boss's " \
            "next turn, ");
    pf_printf("leaps to %s, landing in front of him/her and pounces, " \
            "dealing %d magic damage and %d magic damage to anyone within 5ft.\n",
            target, info->bufs.arcane_pounce.magic_damage,
            info->bufs.arcane_pounce.erea_damage);
    return ;
}

void print_earth_pounce(const t_char * info)
{
    const char *target;

    if (info->bufs.earth_pounce.target_id)
        target = info->bufs.earth_pounce.target_id;
    else
        target = "the target";
    pf_printf("Earth Pounce: Targets the player with the highest Armor Class " \
                "(AC). ");
    pf_printf("At the start of the boss's next turn, jumps towards the %s " \
            "and deals %d bludgeoning damage reduced by 1 for each AC the %s has.\n",
            target, info->bufs.earth_pounce.base_damage, target);
        return ;
}

void print_shadow_illusion(const t_char * info)
{
    pf_printf("Shadow Illusion: Xavius creates an illusory copy of himself for " \
            "%d turn(s).\n",
              info->bufs.shadow_illusion.duration);
    pf_printf("The next attack against him has a 50%% chance to strike the illusion " \
            "instead.\n");
    return ;
}

void print_protective_winds(const t_char * info)
{
    if (info->bufs.protective_winds.duration == 1)
        pf_printf("Protective Winds: Howling gusts surround the boss for 1 turn, " \
                "deflecting ranged attacks back at their originator.\n");
    else
        pf_printf("Protective Winds: Howling gusts surround the boss for %d turns, " \
                "deflecting ranged attacks back at their originator.\n",
                info->bufs.protective_winds.duration);
    pf_printf("While the winds persist, any projectile that hits the barrier is " \
            "hurled at the attacker instead.\n");
    return ;
}

void print_chaos_armor(const t_char * info)
{
    if (info->bufs.chaos_armor.duration == 1)
        pf_printf("Chaos Armor: Unstable elemental energy coats the target for 1 " \
                "turn.\n");
    else
        pf_printf("Chaos Armor: Unstable elemental energy coats the target for %d " \
                "turns.\n", info->bufs.chaos_armor.duration);
    pf_printf("Whenever the wearer is struck, roll on the chaos surge table to " \
            "determine the retaliatory elemental backlash.\n");
    return ;
}

void print_rejuvenation(const t_char * info)
{
    pf_printf("Rejuvenation: At the start of the affected creature's turn it heals " \
            "for %d d%d + %d for the next %d turn(s).\n",
            info->bufs.rejuvenation.healing_dice_amount,
            info->bufs.rejuvenation.healing_dice_faces,
            info->bufs.rejuvenation.healing_extra,
            info->bufs.rejuvenation.duration);
    pf_printf("The healing dice and bonus were set when the spell was cast and do " \
            "not change while the buff lasts.\n");
    return ;
}

void print_sanctuary(const t_char * info)
{
    if (info->bufs.sanctuary.duration <= 0)
        pf_printf("Sanctuary: %s is no longer sheltered by sacred warding.\n",
                info->name);
    else if (info->bufs.sanctuary.duration == 1)
        pf_printf("Sanctuary: %s is warded for 1 turn; foes must hesitate before " \
                "attacking.\n", info->name);
    else
        pf_printf("Sanctuary: %s is warded for %d turns; foes must hesitate before " \
                "attacking.\n", info->name, info->bufs.sanctuary.duration);
    if (info->bufs.sanctuary.duration > 0)
    {
        if (info->bufs.sanctuary.save_dc > 0)
            pf_printf("Hostile creatures must succeed on a DC %d Wisdom save before " \
                    "they can target the warded creature.\n",
                    info->bufs.sanctuary.save_dc);
        else
            pf_printf("Hostile creatures must succeed on a Wisdom save before they can " \
                    "target the warded creature.\n");
        pf_printf("Making an attack or casting a harmful spell ends the sanctuary " \
                "early.\n");
    }
    else
        pf_printf("No sanctuary magic protects them until the blessing is recast.\n");
    return ;
}

void print_growth(const t_char * info)
{
    if (info->bufs.growth.stacks == 0)
        pf_printf("Growth: The target currently has no growth stacks.\n");
    else if (info->bufs.growth.stacks == 1)
        pf_printf("Growth: The target carries 1 stack, reducing the next incoming " \
                "damage by 1.\n");
    else
        pf_printf("Growth: The target carries %d stacks, reducing incoming damage " \
                "by that amount (up to a maximum of 10).\n",
                info->bufs.growth.stacks);
    pf_printf("Stacks are consumed automatically as damage is taken and can be " \
            "built up through the growth ability.\n");
    return ;
}

void print_bless(const t_char * info)
{
    int caster_count;

    caster_count = static_cast<int>(info->bufs.bless.caster_name.size());
    if (info->bufs.bless.duration <= 0)
        pf_printf("Bless: %s currently has no active blessing.\n", info->name);
    else if (info->bufs.bless.duration == 1)
        pf_printf("Bless: %s is under divine favor for 1 turn.\n", info->name);
    else
        pf_printf("Bless: %s is under divine favor for %d turns.\n", info->name,
                info->bufs.bless.duration);
    if (info->bufs.bless.dice_amount_mod > 0
            && info->bufs.bless.dice_faces_mod > 0)
        pf_printf("Each attack roll or saving throw gains +%dd%d plus %d from the " \
                "blessing.\n", info->bufs.bless.dice_amount_mod,
                info->bufs.bless.dice_faces_mod, info->bufs.bless.base_mod);
    else if (info->bufs.bless.base_mod != 0)
        pf_printf("Each attack roll or saving throw gains +%d from the " \
                "blessing.\n", info->bufs.bless.base_mod);
    else
        pf_printf("The blessing currently grants no bonus dice or flat modifier.\n");
    if (caster_count == 0)
        pf_printf("No casters are maintaining the effect right now.\n");
    else if (caster_count == 1)
        pf_printf("1 caster is concentrating on the blessing.\n");
    else
        pf_printf("%d casters are concentrating on the blessing.\n", caster_count);
    return ;
}

void print_hunters_mark(const t_char * info)
{
    int mark_count;
    int caster_count;

    mark_count = info->debufs.hunters_mark.amount;
    caster_count = static_cast<int>(info->debufs.hunters_mark.caster_name.size());
    if (mark_count <= 0)
        pf_printf("Hunter's Mark: No hunters are tracking %s at the moment.\n",
                info->name);
    else if (mark_count == 1)
        pf_printf("Hunter's Mark: %s is tracked by a single hunter; their next " \
                "hits deal extra damage.\n", info->name);
    else
        pf_printf("Hunter's Mark: %s is tracked by %d hunters; their weapon hits " \
                "deal extra damage equal to the number of marks.\n",
                info->name, mark_count);
    if (caster_count == 0)
        pf_printf("No casters are sustaining the mark.\n");
    else if (caster_count == 1)
        pf_printf("Maintained by 1 hunter focusing on the prey.\n");
    else
        pf_printf("Maintained by %d hunters focusing on the prey.\n", caster_count);
    return ;
}

void print_magic_drain(const t_char * info)
{
    int stack_count;
    int caster_count;

    stack_count = info->debufs.magic_drain.amount;
    caster_count = static_cast<int>(info->debufs.magic_drain.caster.size());
    pf_printf("Magic Drain: Arcane tendrils siphon power from %s.\n", info->name);
    if (stack_count <= 0)
        pf_printf("No siphons are currently active.\n");
    else if (stack_count == 1)
        pf_printf("1 siphon is active, ready to erupt when triggered.\n");
    else
        pf_printf("%d siphons are active, each primed to erupt when triggered.\n",
                stack_count);
    if (info->debufs.magic_drain.damage_dice_amount > 0
            && info->debufs.magic_drain.damage_dice_faces > 0)
        pf_printf("Each siphon deals %dd%d + %d damage on activation.\n",
                info->debufs.magic_drain.damage_dice_amount,
                info->debufs.magic_drain.damage_dice_faces,
                info->debufs.magic_drain.damage_flat);
    else if (info->debufs.magic_drain.damage_flat > 0)
        pf_printf("Each siphon deals %d damage on activation.\n",
                info->debufs.magic_drain.damage_flat);
    else
        pf_printf("The siphons currently have no damage configured.\n");
    if (info->debufs.magic_drain.extra_dice_amount > 0
            && info->debufs.magic_drain.extra_dice_faces > 0)
        pf_printf("Failed saves add %dd%d + %d additional damage.\n",
                info->debufs.magic_drain.extra_dice_amount,
                info->debufs.magic_drain.extra_dice_faces,
                info->debufs.magic_drain.extra_damage_flat);
    else if (info->debufs.magic_drain.extra_damage_flat > 0)
        pf_printf("Failed saves add %d additional damage.\n",
                info->debufs.magic_drain.extra_damage_flat);
    if (info->debufs.magic_drain.spell_slot_total_level_drain > 0
            && info->debufs.magic_drain.con_save > 0)
        pf_printf("Failing the DC %d Constitution save drains spell slots totaling " \
                "%d levels.\n", info->debufs.magic_drain.con_save,
                info->debufs.magic_drain.spell_slot_total_level_drain);
    else if (info->debufs.magic_drain.con_save > 0)
        pf_printf("A DC %d Constitution save can resist the siphon.\n",
                info->debufs.magic_drain.con_save);
    if (caster_count == 0)
        pf_printf("No casters are sustaining the drain at this time.\n");
    else if (caster_count == 1)
        pf_printf("Maintained by 1 spellcaster.\n");
    else
        pf_printf("Maintained by %d spellcasters.\n", caster_count);
    return ;
}

void print_blinded(const t_char * info)
{
    if (info->debufs.blinded.duration <= 0)
        pf_printf("Blinded: %s can see again.\n", info->name);
    else if (info->debufs.blinded.duration == 1)
        pf_printf("Blinded: %s stumbles sightless for 1 turn, attacking at " \
                "disadvantage and failing sight-based checks.\n", info->name);
    else
        pf_printf("Blinded: %s is sightless for %d turns, attacking at disadvantage " \
                "and failing sight-based checks.\n", info->name,
                info->debufs.blinded.duration);
    return ;
}

void print_faerie_fire(const t_char * info)
{
    if (info->debufs.faerie_fire.duration <= 0)
        pf_printf("Faerie Fire: %s is no longer limned in sparkling light.\n",
                info->name);
    else if (info->debufs.faerie_fire.duration == 1)
        pf_printf("Faerie Fire: %s glows with violet starlight for 1 turn, granting " \
                "advantage to attacks and canceling invisibility.\n", info->name);
    else
        pf_printf("Faerie Fire: %s shines with violet starlight for %d turns, " \
                "granting advantage to attacks and canceling invisibility.\n",
                info->name, info->debufs.faerie_fire.duration);
    pf_printf("Outlined creatures cannot benefit from invisibility while the " \
            "sparkles dance around them.\n");
    return ;
}
