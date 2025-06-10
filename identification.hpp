#ifndef IDENTIFICATION_H
# define IDENTIFICATION_H

#define NONE 0

typedef enum
{
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
	WAND_OF_DRAINING_ID,
	CLAW_ID,
	FELBEAST_CLAW_ID,
	FELBEAST_CLAW_OH_ID,
	ANCIENT_PREDATORY_BEAST_CLAW_ID,
	SNOWBALL_WAND_ID,
	ICY_BLADE_ID,
	SHADOW_CLAW_ID,

    LEATHER_ARMOR_ID = 30001,
	STEEL_ARMOR_ID,
	GHOST_ARNOR_ID,
	FELBEAST_HIDE_ID,
	WOLF_PELT_ID,
	MAGIC_STEEL_ARMOR_ID,

	ETYPE_FEL_POISON = 40001,
	ETYPE_ANCIENT_PREDATORY_BEAST_MULTI_ATTACK,
	ETYPE_SNOWBALL_WAND_SLOW,
} ItemID;

typedef enum e_equipment_slot
{
	SLOT_NONE				= 0,
	SLOT_WEAPON				= 1 << 0,
	SLOT_OFFHAND_WEAPON		= 1 << 1,
	SLOT_RANGED_WEAPON		= 1 << 2,
	SLOT_ARMOR				= 1 << 3,
	SLOT_HELMET				= 1 << 4,
	SLOT_SHIELD				= 1 << 5,
	SLOT_BOOTS				= 1 << 6,
	SLOT_GLOVES				= 1 << 7,
	SLOT_AMULET				= 1 << 8,
	SLOT_RING_01			= 1 << 9,
	SLOT_RING_02			= 1 << 10,
	SLOT_BELT				= 1 << 11,
	SLOT_TWO_HANDED_WEAPON	= 1 << 12,
}	t_equipment_slot;

#define ABILITY_LIST \
    X(HUNTERS_MARK, 1, "hunters mark") \
    X(BLESS, 2, "bless") \
    X(CHAOS_ARMOR, 3, "chaos armor") \
    X(MAGIC_DRAIN, 4, "magic drain")

#define X(name, id, str)  enum { name##_ID = id };
ABILITY_LIST
#undef X

#define X(name, id, str)  [[maybe_unused]] static const char* name##_NAME = str;
ABILITY_LIST
#undef X

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

# define DAMAGE_TYPE_BLUDGEONING_ID  0
# define DAMAGE_TYPE_PIERCING_ID     1
# define DAMAGE_TYPE_SLASHING_ID     2
# define DAMAGE_TYPE_FIRE_ID         3
# define DAMAGE_TYPE_COLD_ID         4
# define DAMAGE_TYPE_LIGHTNING_ID    5
# define DAMAGE_TYPE_ACID_ID         6
# define DAMAGE_TYPE_POISON_ID       7
# define DAMAGE_TYPE_FORCE_ID        8
# define DAMAGE_TYPE_RADIANT_ID      9
# define DAMAGE_TYPE_NECROTIC_ID    10
# define DAMAGE_TYPE_THUNDER_ID     11
# define DAMAGE_TYPE_PSYCHIC_ID     12

# define STAT_STR "strength"
# define STAT_DEX "dexterity"
# define STAT_CON "constitution"
# define STAT_INT "intelligence"
# define STAT_WIS "wisdom"
# define STAT_CHA "charisma"

# define FINESSE "finesse"

# define DATA_FOLDER "data"
# define PREFIX_TO_SKIP "data--"
# define EXCLUDE_PREFIX "pc--"
# define PC_PREFIX "pc--"

#endif
