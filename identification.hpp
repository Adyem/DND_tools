#ifndef IDENTIFICATION_H
# define IDENTIFICATION_H

typedef enum {
    WTYPE_CLUB = 1,
    WTYPE_DAGGER,
    WTYPE_GREATCLUB,
    WTYPE_HANDAXE,
    WTYPE_JAVELIN,
    WTYPE_LIGHT_HAMMER,
    WTYPE_MACE,
    WTYPE_QUARTERSTAFF,
    WTYPE_SICKLE,
    WTYPE_SPEAR,
    WTYPE_LIGHT_CROSSBOW,
    WTYPE_DART,
    WTYPE_SHORTBOW,
    WTYPE_SLING,
    WTYPE_BATTLEAXE,
    WTYPE_FLAIL,
    WTYPE_GLAIVE,
    WTYPE_GREATSWORD,
    WTYPE_HALBERD,
    WTYPE_LANCE,
    WTYPE_LONGSWORD,
    WTYPE_MAUL,
    WTYPE_MORNINGSTAR,
    WTYPE_PIKE,
    WTYPE_RAPIER,
    WTYPE_SCIMITAR,
    WTYPE_SHORTSWORD,
    WTYPE_TRIDENT,
    WTYPE_WAR_PICK,
    WTYPE_WARHAMMER,
    WTYPE_WHIP,
    WTYPE_BLOWGUN,
    WTYPE_HAND_CROSSBOW,
    WTYPE_HEAVY_CROSSBOW,
    WTYPE_LONGBOW,
    WTYPE_NET,
    WTYPE_WAND,

	WTYPE_CLAW,
    
    ATYPE_PADDED = 10001,
    ATYPE_LEATHER,
    ATYPE_STUDDED_LEATHER,
    ATYPE_HIDE,
    ATYPE_CHAIN_SHIRT,
    ATYPE_SCALE_MAIL,
    ATYPE_BREASTPLATE,
    ATYPE_HALF_PLATE,
    ATYPE_RING_MAIL,
    ATYPE_CHAIN_MAIL,
    ATYPE_SPLINT,
    ATYPE_PLATE,
    ATYPE_SHIELD,

    STEEL_SWORD_ID = 20001,
	STEEL_BATTLE_AXE_ID,
    WOODEN_BOW_ID,
	WOODEN_CLUB_ID,
    CHAOS_WAND_ID,
	CLAW_ID,

    LEATHER_ARMOR_ID = 30001,
} ItemID;

typedef enum e_equipment_slot
{
	SLOT_NONE            = 0,
	SLOT_WEAPON          = 1 << 0,
	SLOT_OFFHAND_WEAPON  = 1 << 1,
	SLOT_RANGED_WEAPON   = 1 << 2,
	SLOT_ARMOR           = 1 << 3,
	SLOT_HELMET          = 1 << 4,
	SLOT_SHIELD          = 1 << 5,
	SLOT_BOOTS           = 1 << 6,
	SLOT_GLOVES          = 1 << 7,
	SLOT_AMULET          = 1 << 8,
	SLOT_RING_01         = 1 << 9,
	SLOT_RING_02         = 1 << 10,
	SLOT_BELT            = 1 << 11,
}	t_equipment_slot;

# define HUNTERS_MARK_ID 1
# define HUNTERS_MARK_NAME "hunters mark"
# define BLESS_ID 2
# define BLESS_NAME "bless"
# define CHAOS_ARMOR_ID 3
# define CHAOS_ARMOR_NAME "chaos_armor"

# define DAMAGE_TYPE_BLUDGEONING	"bludgeoning"
# define DAMAGE_TYPE_PIERCING		"piercing"
# define DAMAGE_TYPE_SLASHING		"slashing"
# define DAMAGE_TYPE_FIRE			"fire"
# define DAMAGE_TYPE_COLD			"cold"
# define DAMAGE_TYPE_LIGHTNING		"lightning"
# define DAMAGE_TYPE_ACID			"acid"
# define DAMAGE_TYPE_POISON			"poison"
# define DAMAGE_TYPE_FORCE			"force"
# define DAMAGE_TYPE_RADIANT		"radiant"
# define DAMAGE_TYPE_NECROTIC		"necrotic"
# define DAMAGE_TYPE_THUNDER		"thunder"
# define DAMAGE_TYPE_PSYCHIC		"psychic"

# define STAT_STR "strength"
# define STAT_DEX "dexterity"
# define STAT_CON "constitution"
# define STAT_INT "intelligence"
# define STAT_WIS "wisdom"
# define STAT_CHA "charisma"

# define FINESSE "finesse"

#define DATA_FOLDER "data"
#define PREFIX_TO_SKIP "data--"
#define EXCLUDE_PREFIX "pc--"
#define PC_PREFIX "pc--"

#endif
