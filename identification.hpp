#ifndef IDENTIFICATION_H
# define IDENTIFICATION_H

typedef enum {
    // Weapon Types
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
    
    // Armor Types
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

    // Weapon IDs
    STEEL_SWORD_ID = 20001,
	STEEL_BATTLE_AXE_ID,
    WOODEN_BOW_ID,
    CHAOS_WAND_ID,

    // Armor IDs
    LEATHER_ARMOR_ID = 30001
} ItemID;

//Concentration ID
# define HUNTERS_MARK_ID 1
# define HUNTERS_MARK_NAME "hunters mark"
# define BLESS_ID 2
# define BLESS_NAME "bless"
# define CHAOS_ARMOR_ID 3
# define CHAOS_ARMOR_NAME "chaos_armor"

//Damage types
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

//Stats
# define STAT_STR "strength"
# define STAT_DEX "dexterity"
# define STAT_CON "constitution"
# define STAT_INT "intelligence"
# define STAT_WIS "wisdom"
# define STAT_CHA "charisma"

//Other
# define FINESSE "finesse"

//Data
#define DATA_FOLDER "data"
#define PREFIX_TO_SKIP "data--"
#define EXCLUDE_PREFIX "pc--"
#define PC_PREFIX "pc--"

#endif
