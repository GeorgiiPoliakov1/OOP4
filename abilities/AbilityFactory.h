#ifndef ABILITY_FACTORY_H
#define ABILITY_FACTORY_H
#include "Ability.h"
#include "DoubleDamage.h"
#include "Scanner.h"
#include "Shelling.h"

class AbilityFactory{
public:
    virtual Ability* createAbility() = 0;
    virtual ~AbilityFactory(){}
};

class DoubleDamageFactory : public AbilityFactory {
public:
    Ability* createAbility() override {return new DoubleDamage();}     
};

class ScannerFactory : public AbilityFactory {
public:
    Ability* createAbility() override {return new Scanner();}     
};

class ShellingFactory : public AbilityFactory {
public:
    Ability* createAbility() override {return new Shelling();}     
};
#endif