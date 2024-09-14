#include "dnd_tools.hpp"
#include <iostream>

int ft_npc_check_info_2(t_char *info)
{
    int error = 0;

    if (info->c_resistance.bludgeoning < -500 || info->c_resistance.bludgeoning > 500)
        error += (std::cerr << info->name << " bludgeoning resistance value not found" << std::endl, 1) ;
    if (info->c_resistance.cold < -500 || info->c_resistance.cold > 500)
        error += (std::cerr << info->name << " cold resistance value not found" << std::endl, 1) ;
    if (info->c_resistance.fire < -500 || info->c_resistance.fire > 500)
        error += (std::cerr << info->name << " fire resistance value not found" << std::endl, 1) ;
    if (info->c_resistance.force < -500 || info->c_resistance.force > 500)
        error += (std::cerr << info->name << " force resistance value not found" << std::endl, 1) ;
    if (info->c_resistance.lightning < -500 || info->c_resistance.lightning > 500)
        error += (std::cerr << info->name << " lightning resistance value not found" << std::endl, 1) ;
    if (info->c_resistance.necrotic < -500 || info->c_resistance.necrotic > 500)
        error += (std::cerr << info->name << " necrotic resistance value not found" << std::endl, 1) ;
    if (info->c_resistance.piercing < -500 || info->c_resistance.piercing > 500)
        error += (std::cerr << info->name << " piercing resistance value not found" << std::endl, 1) ;
    if (info->c_resistance.poison < -500 || info->c_resistance.poison > 500)
        error += (std::cerr << info->name << " poison resistance value not found" << std::endl, 1) ;
    if (info->c_resistance.psychic < -500 || info->c_resistance.psychic > 500)
        error += (std::cerr << info->name << " psychic resistance value not found" << std::endl, 1) ;
    if (info->c_resistance.radiant < -500 || info->c_resistance.radiant > 500)
        error += (std::cerr << info->name << " radiant resistance value not found" << std::endl, 1) ;
    if (info->c_resistance.slashing < -500 || info->c_resistance.slashing > 500)
        error += (std::cerr << info->name << " slashing resistance value not found" << std::endl, 1) ;
    if (info->c_resistance.thunder < -500 || info->c_resistance.thunder > 500)
        error += (std::cerr << info->name << " thunder resistance value not found" << std::endl, 1) ;
    if (info->concentration.concentration < 0)
        error += (std::cerr << info->name << " concentration value is negative" << std::endl, 1) ;
    if (info->concentration.spell_id < 0)
        error += (std::cerr << info->name << " spell_id value is negative" << std::endl, 1) ;
    if (info->concentration.dice_amount_mod < 0)
        error += (std::cerr << info->name << " dice_amount_mod value is negative" << std::endl, 1) ;
    if (info->concentration.dice_faces_mod < 0)
        error += (std::cerr << info->name << " dice_faces_mod value is negative" << std::endl, 1) ;
    if (info->concentration.base_mod < 0)
        error += (std::cerr << info->name << " base_mod value is negative" << std::endl, 1) ;
    if (info->concentration.duration < -1)
        error += (std::cerr << info->name << " duration value is negative" << std::endl, 1) ;
    if (info->c_resistance.acid < -500 || info->c_resistance.acid > 500)
        error += (std::cerr << info->name << " acid resistance value not found" << std::endl, 1) ;
    if (info->flags.prone != 0 && info->flags.prone != 1)
        error += (std::cerr << info->name << " prone flag out of bounds" << std::endl, 1) ;
    if (info->debufs.blinded.duration < 0 || info->debufs.blinded.duration > 50)
        error += (std::cerr << info->name << " blinded debuff out of bounds" << std::endl, 1) ;
    return (error) ;
}

int ft_npc_check_info(t_char *info)
{
    int error = 0;

	if (info->stats.health <= -1 || info->stats.health > info->dstats.health)
        error += (std::cerr << info->name << " health value not found" << std::endl, 1);
	if (info->stats.health <= -1 || info->stats.temp_hp > 5000)
        error += (std::cerr << info->name << " temp health value not found" << std::endl, 1);
	if (info->stats.str <= -1 || info->stats.str > 30)
        error += (std::cerr << info->name << " strength value not found" << std::endl, 1);
	if (info->stats.dex <= -1 || info->stats.dex > 30)
        error += (std::cerr << info->name << " dexterity value not found" << std::endl, 1);
	if (info->stats.con <= -1 || info->stats.con > 30)
        error += (std::cerr << info->name << " constitution value not found" << std::endl, 1);
	if (info->stats.inte <= -1 || info->stats.inte > 30)
        error += (std::cerr << info->name << " intelligence value not found" << std::endl, 1);
	if (info->stats.wis <= -1 || info->stats.wis > 30)
        error += (std::cerr << info->name << " wisdom value not found" << std::endl, 1);
	if (info->stats.cha <= -1 || info->stats.cha > 30)
        error += (std::cerr << info->name << " charisma value not found" << std::endl, 1);
	if (info->stats.turn <= -1 || info->stats.turn > 30)
        error += (std::cerr << info->name << " turn value not found" << std::endl, 1);
	if (info->stats.phase <= -1 || info->stats.turn > 30)
        error += (std::cerr << info->name << " phase value not found" << std::endl, 1);
	if (info->bufs.bless.duration < 0 || info->bufs.bless.duration > 50)
        error += (std::cerr << info->name << " bless value outside of bounds" << std::endl, 1);
	if (info->initiative < -50)
        error += (std::cerr << info->name << " initiative value outside of bounds" << std::endl, 1);
	if (info->bufs.lightning_strike.duration < 0)
        error += (std::cerr << info->name << " lightning strike duration outside of bounds" << std::endl, 1);
	if (info->debufs.hunters_mark.amount < 0 || info->debufs.hunters_mark.amount
			!= ft_double_char_length(info->debufs.hunters_mark.caster_name))
        error += (std::cerr << info->name << " hunters mark data is not correct" << std::endl, 1);
	if (info->bufs.protective_winds.duration < 0)
        error += (std::cerr << info->name << " protective winds duration outside of bounds" << std::endl, 1);
	if (info->bufs.chaos_armor.duration < 0)
        error += (std::cerr << info->name << " chaos armor duration outside of bounds" << std::endl, 1);
	error += ft_check_equipment_slots(info);
    error += ft_npc_check_info_2(info);
    if (error)
        std::cerr << "2-" << info->name << " Error with the save file, please reinitialize it with the correct values" << std::endl;
    return (error) ;
}
