#include "identification.hpp"
#include "dnd_tools.hpp"

// Define the global map pointer
ft_unordened_map* g_map = nullptr;

// Function to initialize the global map
bool initialize_global_map() {
    // Define the initial capacity based on the number of keys
    // Adjust this number if you add more keys to minimize collisions
    const size_t initial_capacity = 256;
    
    // Define whether the map is critical (set as needed)
    const bool is_critical = false;
    
    // Allocate memory for the map
    g_map = new (std::nothrow) ft_unordened_map(initial_capacity, is_critical);
    if (!g_map) {
        std::cerr << "Failed to allocate memory for the global map." << std::endl;
        return false;
    }
    
    // Define all keys in an array
    const char* keys[] = {
        HEALTH_KEY,
        TEMP_HP_KEY,
        STR_KEY,
        DEX_KEY,
        CON_KEY,
        INT_KEY,
        WIS_KEY,
        CHA_KEY,
        TURN_KEY,
        INITIATIVE_KEY,
        BLESS_DUR_KEY,
        PHASE_KEY,
        CONCENTRATION_KEY,
        
        HUNTERS_MARK_AMOUNT_KEY,
        HUNTERS_MARK_CASTER_KEY,
        CHAOS_ARMOR_DURATION_KEY,
        
        PRONE_KEY,
        BLINDED_KEY,
        REACTION_USED_KEY,
        
        LIGHTNING_STRIKE_DUR_KEY,
        PROTECTIVE_WINDS_DUR_KEY,
        ACID_RESISTANCE_KEY,
        BLUDGEONING_RESISTANCE_KEY,
        COLD_RESISTANCE_KEY,
        FIRE_RESISTANCE_KEY,
        FORCE_RESISTANCE_KEY,
        LIGHTNING_RESISTANCE_KEY,
        NECROTIC_RESISTANCE_KEY,
        PIERCING_RESISTANCE_KEY,
        POISON_RESISTANCE_KEY,
        PSYCHIC_RESISTANCE_KEY,
        RADIANT_RESISTANCE_KEY,
        SLASHING_RESISTANCE_KEY,
        THUNDER_RESISTANCE_KEY,
        
        CONC_TARGETS_KEY,
        CONC_SPELL_ID_KEY,
        CONC_DICE_AMOUNT_KEY,
        CONC_DICE_FACES_KEY,
        CONC_BASE_MOD_KEY,
        CONC_DURATION_KEY,
        
        FLAME_GEYSER_DURATION_KEY,
        FLAME_GEYSER_AMOUNT_KEY,
        FLAME_GEYSER_CLOSE_TO_TOWER_D_KEY,
        FLAME_GEYSER_TOWER_EXPLODE_D_KEY,
        
        METEOR_STRIKE_DURATION_KEY,
        METEOR_STRIKE_ONE_TARGET_D_KEY,
        METEOR_STRIKE_TWO_TARGETS_D_KEY,
        METEOR_STRIKE_THREE_TARGETS_D_KEY,
        METEOR_STRIKE_FOUR_TARGETS_D_KEY,
        METEOR_STRIKE_FIVE_TARGETS_D_KEY,
        METEOR_STRIKE_TARGET_KEY,
        
        LIGHTNING_STRIKE_DURATION_KEY,
        LIGHTNING_STRIKE_AMOUNT_KEY,
        LIGHTNING_STRIKE_DISTANCE_KEY,
        LIGHTNING_STRIKE_DICE_AMOUNT_KEY,
        LIGHTNING_STRIKE_DICE_FACES_KEY,
        LIGHTNING_STRIKE_EXTRA_DAMAGE_KEY,
        
        LIGHTNING_STRIKEV2_DURATION_KEY,
        LIGHTNING_STRIKEV2_AMOUNT_KEY,
        LIGHTNING_STRIKEV2_DISTANCE_KEY,
        LIGHTNING_STRIKEV2_DICE_AMOUNT_KEY,
        LIGHTNING_STRIKEV2_DICE_FACES_KEY,
        LIGHTNING_STRIKEV2_EXTRA_DAMAGE_KEY,
        
        EARTH_POUNCE_ACTIVE_KEY,
        EARTH_POUNCE_BASE_DAMAGE_KEY,
        EARTH_POUNCE_TARGET_ID_KEY,
        
        ARCANE_POUNCE_ACTIVE_KEY,
        ARCANE_POUNCE_MAGIC_DAMAGE_KEY,
        ARCANE_POUNCE_EREA_DAMAGE_KEY,
        ARCANE_POUNCE_TARGET_ID_KEY,
        
        FROST_BREATH_ACTIVE_KEY,
        FROST_BREATH_DAMAGE_KEY,
        FROST_BREATH_TARGET_ID_KEY,
        
        LEVEL_1_AVAILABLE_KEY,
        LEVEL_1_TOTAL_KEY,
        LEVEL_1_LEVEL_KEY,
        LEVEL_1_REPLENISHING_SLOT_KEY,
        
        LEVEL_2_AVAILABLE_KEY,
        LEVEL_2_TOTAL_KEY,
        LEVEL_2_LEVEL_KEY,
        LEVEL_2_REPLENISHING_SLOT_KEY,
        
        LEVEL_3_AVAILABLE_KEY,
        LEVEL_3_TOTAL_KEY,
        LEVEL_3_LEVEL_KEY,
        LEVEL_3_REPLENISHING_SLOT_KEY,
        
        LEVEL_4_AVAILABLE_KEY,
        LEVEL_4_TOTAL_KEY,
        LEVEL_4_LEVEL_KEY,
        LEVEL_4_REPLENISHING_SLOT_KEY,
        
        LEVEL_5_AVAILABLE_KEY,
        LEVEL_5_TOTAL_KEY,
        LEVEL_5_LEVEL_KEY,
        LEVEL_5_REPLENISHING_SLOT_KEY,
        
        LEVEL_6_AVAILABLE_KEY,
        LEVEL_6_TOTAL_KEY,
        LEVEL_6_LEVEL_KEY,
        LEVEL_6_REPLENISHING_SLOT_KEY,
        
        LEVEL_7_AVAILABLE_KEY,
        LEVEL_7_TOTAL_KEY,
        LEVEL_7_LEVEL_KEY,
        LEVEL_7_REPLENISHING_SLOT_KEY,
        
        LEVEL_8_AVAILABLE_KEY,
        LEVEL_8_TOTAL_KEY,
        LEVEL_8_LEVEL_KEY,
        LEVEL_8_REPLENISHING_SLOT_KEY,
        
        LEVEL_9_AVAILABLE_KEY,
        LEVEL_9_TOTAL_KEY,
        LEVEL_9_LEVEL_KEY,
        LEVEL_9_REPLENISHING_SLOT_KEY,
        
        WARLOCK_AVAILABLE_KEY,
        WARLOCK_TOTAL_KEY,
        WARLOCK_LEVEL_KEY,
        WARLOCK_REPLENISHING_SLOT_KEY
    };
    
    // Calculate the number of keys
    const size_t num_keys = sizeof(keys) / sizeof(keys[0]);
    
    // Insert all keys with default values (e.g., empty strings)
    for (size_t i = 0; i < num_keys; ++i) {
        bool success = g_map->insert(keys[i], "");
        if (!success) {
            std::cerr << "Failed to insert key: " << keys[i] << std::endl;
            // Optionally, handle the error (e.g., clean up and return)
            // For this example, we'll continue inserting other keys
        }
    }
    
    return true;
}
