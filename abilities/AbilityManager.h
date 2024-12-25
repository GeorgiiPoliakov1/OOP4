#ifndef ABILITY_MANAGER_H
#define ABILITY_MANAGER_H
#include "Ability.h"
#include <queue>
#include "../field/PlayingField.h"
#include "AbilityFactory.h"
#include "../save/nlohmann/json.hpp"
using json = nlohmann::json;

enum AbilityNames{
    NOABILITY = 0,
    SHELLING = 1,
    DOUBLE_DAMAGE = 2,
    SCANNER = 3
};
class AbilityManager {
 private:
    std::queue<Ability*> abilities;
    int countAbilities = 3;
    DoubleDamageFactory doubleDamageFactory;
    ScannerFactory scannerFactory;
    ShellingFactory shellingFactory;
 public:
    AbilityManager();
    bool applyAbility(PlayingField& field, ShipManager& manager, int x, int y);
    int getCountAbilities();
    std::queue<Ability*> getAbilitiesQueue();
    AbilityNames getFrontAbilityName();
    Ability* addNewRandomAbility();
    json toJson() const;
    void fromJson(const json& jsonFile);
};
#endif