#include "libft/Printf/ft_printf.hpp"
#include "dnd_tools.hpp"

int ft_npc_check_info_2(t_char *info)
{
    int error = 0;

	if (info->c_resistance.bludgeoning < -500 || info->c_resistance.bludgeoning > 500)
        error += (ft_printf("%s bludgeoning resistance value not found\n", info->name), 1);
	if (info->c_resistance.cold < -500 || info->c_resistance.cold > 500)
        error += (ft_printf("%s cold resistance value not found\n", info->name), 1);
	if (info->c_resistance.fire < -500 || info->c_resistance.fire > 500)
        error += (ft_printf("%s fire resistance value not found\n", info->name), 1);
	if (info->c_resistance.force < -500 || info->c_resistance.force > 500)
        error += (ft_printf("%s force resistance value not found\n", info->name), 1);
	if (info->c_resistance.lightning < -500 || info->c_resistance.lightning > 500)
        error += (ft_printf("%s lightning resistance value not found\n", info->name), 1);
	if (info->c_resistance.necrotic < -500 || info->c_resistance.necrotic > 500)
        error += (ft_printf("%s necrotic resistance value not found\n", info->name), 1);
	if (info->c_resistance.piercing < -500 || info->c_resistance.piercing > 500)
        error += (ft_printf("%s piercing resistance value not found\n", info->name), 1);
	if (info->c_resistance.poison < -500 || info->c_resistance.poison > 500)
        error += (ft_printf("%s poison resistance value not found\n", info->name), 1);
	if (info->c_resistance.psychic < -500 || info->c_resistance.psychic > 500)
        error += (ft_printf("%s psychic resistance value not found\n", info->name), 1);
	if (info->c_resistance.radiant < -500 || info->c_resistance.radiant > 500)
        error += (ft_printf("%s radiant resistance value not found\n", info->name), 1);
	if (info->c_resistance.slashing < -500 || info->c_resistance.slashing > 500)
        error += (ft_printf("%s slashing resistance value not found\n", info->name), 1);
	if (info->c_resistance.thunder < -500 || info->c_resistance.thunder > 500)
        error += (ft_printf("%s thunder resistance value not found\n", info->name), 1);
	if (info->concentration.concentration < 0)
        error += (ft_printf("%s concentration value is negative\n", info->name), 1);
	if (info->concentration.spell_id < 0)
        error += (ft_printf("%s spell_id value is negative\n", info->name), 1);
	if (info->concentration.dice_amount_mod < 0)
        error += (ft_printf("%s dice_amount_mod value is negative\n", info->name), 1);
	if (info->concentration.dice_faces_mod < 0)
        error += (ft_printf("%s dice_faces_mod value is negative\n", info->name), 1);
	if (info->concentration.base_mod < 0)
        error += (ft_printf("%s base_mod value is negative\n", info->name), 1);
	if (info->concentration.duration < -1)
        error += (ft_printf("%s duration value is negative\n", info->name), 1);
	if (info->c_resistance.acid < -500 || info->c_resistance.acid > 500)
        error += (ft_printf("%s acid resistance value not found\n", info->name), 1);
	if (info->flags.prone != 0 && info->flags.prone != 1)
        error += (ft_printf("%s prone flag out of bounds\n", info->name), 1);
	if (info->debufs.blinded.duration < 0 || info->debufs.blinded.duration > 50)
        error += (ft_printf("%s blinded debuff out of bounds\n", info->name), 1);
	if (info->bufs.flame_geyser.duration < 0 || info->bufs.flame_geyser.duration > 100)
        error += (ft_printf("%s flame geyser duration out of bounds\n", info->name), 1);
	if (info->bufs.flame_geyser.close_to_tower_d < 0 ||
			info->bufs.flame_geyser.close_to_tower_d > 100)
        error += (ft_printf("%s flame geyser close_to_tower_d out of bounds\n", info->name), 1);
	if (info->bufs.flame_geyser.tower_explode_d < 0 || info->bufs.flame_geyser.tower_explode_d > 100)
        error += (ft_printf("%s flame geyser tower_explode_d out of bounds\n", info->name), 1);
	if (info->bufs.flame_geyser.amount < 0 || info->bufs.flame_geyser.amount > 5)
        error += (ft_printf("%s flame geyser tower_explode_d out of bounds\n", info->name), 1);
	if (info->bufs.meteor_strike.duration < 0 || info->bufs.meteor_strike.duration > 100)
        error += (ft_printf("%s meteor strike duration out of bounds\n", info->name), 1);
	if (info->bufs.meteor_strike.one_target_d < 0 || info->bufs.meteor_strike.one_target_d > 100)
        error += (ft_printf("%s meteor strike one_target_d out of bounds\n", info->name), 1);
	if (info->bufs.meteor_strike.two_targets_d < 0 || info->bufs.meteor_strike.two_targets_d > 100)
        error += (ft_printf("%s meteor strike two_targets_d out of bounds\n", info->name), 1);
	if (info->bufs.meteor_strike.three_targets_d < 0 ||
			info->bufs.meteor_strike.three_targets_d > 100)
        error += (ft_printf("%s meteor strike three_targets_d out of bounds\n", info->name), 1);
	if (info->bufs.meteor_strike.four_targets_d < 0 || info->bufs.meteor_strike.four_targets_d > 100)
        error += (ft_printf("%s meteor strike four_targets_d out of bounds\n", info->name), 1);
	if (info->bufs.meteor_strike.five_targets_d < 0 || info->bufs.meteor_strike.five_targets_d > 100)
        error += (ft_printf("%s meteor strike five_targets_d out of bounds\n", info->name), 1);
	if (info->bufs.lightning_strike.duration < 0 || info->bufs.lightning_strike.duration > 100)
        error += (ft_printf("%s lightning strike duration out of bounds\n", info->name), 1);
	if (info->bufs.lightning_strike.amount < 0 || info->bufs.lightning_strike.amount > 100)
        error += (ft_printf("%s lightning strike amount out of bounds\n", info->name), 1);
	if (info->bufs.lightning_strike.distance < 0 || info->bufs.lightning_strike.distance > 1000)
        error += (ft_printf("%s lightning strike distance out of bounds\n", info->name), 1);
	if (info->bufs.lightning_strike.dice_amount < 0 || info->bufs.lightning_strike.dice_amount > 100)
        error += (ft_printf("%s lightning strike dice_amount out of bounds\n", info->name), 1);
	if (info->bufs.lightning_strike.dice_faces < 0 || info->bufs.lightning_strike.dice_faces > 100)
        error += (ft_printf("%s lightning strike dice_faces out of bounds\n", info->name), 1);
	if (info->bufs.lightning_strike.extra_damage < 0 ||
			info->bufs.lightning_strike.extra_damage > 1000)
	    error += (ft_printf("%s lightning strike extra_damage out of bounds\n", info->name), 1);
	if (info->bufs.lightning_strikeV2.duration < 0 || info->bufs.lightning_strikeV2.duration > 100)
        error += (ft_printf("%s lightning strike V2 duration out of bounds\n", info->name), 1);
	if (info->bufs.lightning_strikeV2.amount < 0 || info->bufs.lightning_strikeV2.amount > 100)
        error += (ft_printf("%s lightning strike V2 amount out of bounds\n", info->name), 1);
	if (info->bufs.lightning_strikeV2.distance < 0 || info->bufs.lightning_strikeV2.distance > 1000)
        error += (ft_printf("%s lightning strike V2 distance out of bounds\n", info->name), 1);
	if (info->bufs.lightning_strikeV2.dice_amount < 0 ||
			info->bufs.lightning_strikeV2.dice_amount > 100)
        error += (ft_printf("%s lightning strike V2 dice_amount out of bounds\n", info->name), 1);
	if (info->bufs.lightning_strikeV2.dice_faces < 0 ||
			info->bufs.lightning_strikeV2.dice_faces > 100)
        error += (ft_printf("%s lightning strike V2 dice_faces out of bounds\n", info->name), 1);
	if (info->bufs.lightning_strikeV2.extra_damage < 0 ||
			info->bufs.lightning_strikeV2.extra_damage > 1000)
        error += (ft_printf("%s lightning strike V2 extra_damage out of bounds\n", info->name), 1);
	if (info->bufs.earth_pounce.active < 0 || info->bufs.earth_pounce.active > 1)
		error += ft_printf("%s earth pounce active is out of bounds\n", info->name);
	if (info->bufs.earth_pounce.base_damage < 0 || info->bufs.earth_pounce.base_damage > 1000)
		error += ft_printf("%s earth pounce base damage is out of bounds\n", info->name);
	if (info->bufs.arcane_pounce.active < 0 || info->bufs.arcane_pounce.active > 1)
		error += ft_printf("%s arcane pounce active is out of bounds\n", info->name);
	if (info->bufs.arcane_pounce.erea_damage < 0 || info->bufs.arcane_pounce.erea_damage > 1000)
		error += ft_printf("%s arcane pounce erea damage is out of bounds\n", info->name);
	if (info->bufs.arcane_pounce.magic_damage < 0 || info->bufs.arcane_pounce.magic_damage > 1000)
		error += ft_printf("%s arcane pounce magic damage is out of bounds\n", info->name);
	if (ft_double_char_length(info->bufs.arcane_pounce.target_id) > 1)
		error += ft_printf("%s arcane pounce too manny targets\n", info->name);
	if (ft_double_char_length(info->bufs.earth_pounce.target_id) > 1)
		error += ft_printf("%s earth pounce too manny targets\n", info->name);
	if (ft_double_char_length(info->bufs.meteor_strike.target_id) > 1)
		error += ft_printf("invalid amount of targets for meteor strike\n");
    return (error);
}

int ft_npc_check_info(t_char *info)
{
    int error = 0;

	if (info->stats.health <= -1 || info->stats.health > info->dstats.health)
        error += (ft_printf("%s health value not found\n", info->name), 1);
	if (info->stats.health <= -1 || info->stats.temp_hp > 5000)
		error += (ft_printf("%s temp health value not found\n", info->name), 1);
	if (info->stats.str <= -1 || info->stats.str > 30)
        error += (ft_printf("%s strength value not found\n", info->name), 1);
	if (info->stats.dex <= -1 || info->stats.dex > 30)
        error += (ft_printf("%s dexterity value not found\n", info->name), 1);
	if (info->stats.con <= -1 || info->stats.con > 30)
        error += (ft_printf("%s constitution value not found\n", info->name), 1);
	if (info->stats.inte <= -1 || info->stats.inte > 30)
        error += (ft_printf("%s intelligence value not found\n", info->name), 1);
	if (info->stats.wis <= -1 || info->stats.wis > 30)
        error += (ft_printf("%s wisdom value not found\n", info->name), 1);
	if (info->stats.cha <= -1 || info->stats.cha > 30)
        error += (ft_printf("%s charisma value not found\n", info->name), 1);
	if (info->stats.turn <= -1 || info->stats.turn > 30)
        error += (ft_printf("%s turn value not found\n", info->name), 1);
	if (info->stats.phase <= -1 || info->stats.turn > 30)
        error += (ft_printf("%s phase value not found\n", info->name), 1);
	if (info->bufs.bless.duration < 0 || info->bufs.bless.duration > 50)
        error += (ft_printf("%s bless value outside of bounds\n", info->name), 1);
	if (info->initiative < -50)
        error += (ft_printf("%s initiative value outside of bounds\n", info->name), 1);
	if (info->bufs.lightning_strike.duration < 0)
        error += (ft_printf("%s lightning strike duration outside of bounds\n", info->name), 1);
	if (info->debufs.hunters_mark.amount < 0 || info->debufs.hunters_mark.amount
			!= ft_double_char_length(info->debufs.hunters_mark.caster_name))
        error += (ft_printf("%s hunters mark data is not correct\n", info->name), 1);
    if (info->bufs.protective_winds.duration < 0)
        error += (ft_printf("%s protective winds duration outside of bounds\n", info->name), 1);
    if (info->bufs.chaos_armor.duration < 0)
        error += (ft_printf("%s chaos armor duration outside of bounds\n", info->name), 1);
    error += ft_check_equipment_slots(info);
    error += ft_npc_check_info_2(info);
    if (error)
        ft_printf("2-%s Error with the save file, please reinitialize it with the correct values\n", info->name);
    return (error);
}
