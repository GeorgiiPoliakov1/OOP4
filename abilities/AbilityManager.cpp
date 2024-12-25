#include "AbilityManager.h"

AbilityManager::AbilityManager(){
    srand(time(NULL));
    std::vector<short> randomNumbers = {-1, -1, -1};
    while (abilities.size()!=3)
    {
        short number = rand()%3;
        if (randomNumbers[number] == -1){
            randomNumbers[number] = 1;
            switch (number)
            {
            case 0:
                abilities.push(doubleDamageFactory.createAbility());
                break;
            case 1:
                abilities.push(shellingFactory.createAbility());
                break;
            case 2:
                abilities.push(scannerFactory.createAbility());
                break;
            default:
                break;
            }
        }
    }
}

int AbilityManager::getCountAbilities(){
    return countAbilities;
}

std::queue<Ability*> AbilityManager::getAbilitiesQueue(){
    return abilities;
}

AbilityNames AbilityManager::getFrontAbilityName(){
    Ability* ability = abilities.front();
    if (dynamic_cast<DoubleDamage*>(ability)){
        return DOUBLE_DAMAGE;
    }else if (dynamic_cast<Shelling*>(ability)){
        return SHELLING;
    }else if (dynamic_cast<Scanner*>(ability)){
        return SCANNER;
    }else{
        return NOABILITY;
    }
}

Ability* AbilityManager::addNewRandomAbility(){
    srand(time(NULL));
    short number = rand()%3;
    switch (number){
        case 0:
            abilities.push(doubleDamageFactory.createAbility());
            break;
        case 1:
            abilities.push(shellingFactory.createAbility());
            break;
        case 2:
            abilities.push(scannerFactory.createAbility());
            break;
        default:
            break;
    }
    countAbilities++;
    return abilities.front();
}

bool AbilityManager::applyAbility(PlayingField& field, ShipManager& manager, int x, int y){
    bool result = false;
    try{
        if (countAbilities == 0){
            throw NoAbilitiesException("You have no more abilities left");
        }
        if (abilities.front()->apply(field, manager, x, y)){
            result = true;
        }
        abilities.pop();
        countAbilities--;
    }catch(NoAbilitiesException& exception){
        std::cerr << exception.what() << std::endl;
    }
    return result;
}

json AbilityManager::toJson() const {
  json jsonFile;
  jsonFile["countAbilities"] = countAbilities;
  std::queue<Ability*> abilitiesToSave = abilities;
  for (int i = 0; i < countAbilities; ++i) {
    Ability* ability = abilitiesToSave.front();
    abilitiesToSave.pop();
    vector<int> jsonAbility;
    if (dynamic_cast<DoubleDamage*>(ability)){
        jsonFile["abilities"].push_back(2);
    }else if (dynamic_cast<Shelling*>(ability)){
        jsonFile["abilities"].push_back(1);
    }else{
        jsonFile["abilities"].push_back(3);
    }
  }
  return jsonFile;
}

void AbilityManager::fromJson(const json& jsonFile){
    countAbilities = jsonFile["countAbilities"];
    std::queue<Ability*> savedAbilities;
    for (int i = 0; i < jsonFile["countAbilities"]; i++){
        AbilityNames abilityName = jsonFile["abilities"][i];
        switch (abilityName)
        {
        case DOUBLE_DAMAGE:
            savedAbilities.push(doubleDamageFactory.createAbility());
            break;
        case SHELLING:
            savedAbilities.push(shellingFactory.createAbility());
            break;
        case SCANNER:
            savedAbilities.push(scannerFactory.createAbility());
            break;
        default:
            break;
        }
    }
    abilities = savedAbilities; 
}
