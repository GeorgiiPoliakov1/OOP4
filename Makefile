all: main.o Ship.o ShipManager.o Cell.o PlayingField.o DoubleDamage.o Shelling.o Segment.o Scanner.o AbilityManager.o GameMessage.o Game.o FieldDrawer.o GameState.o FileHandler.o CommandHandler.o
	g++  main.o Ship.o ShipManager.o Cell.o PlayingField.o DoubleDamage.o Shelling.o Segment.o Scanner.o AbilityManager.o GameMessage.o Game.o FieldDrawer.o GameState.o FileHandler.o CommandHandler.o -o game
main.o: print/InputHandler.hpp print/GameDrawer.hpp print/FieldDrawer.h print/GameHandler.hpp play/Game.h
	g++ -c play/main.cpp
Ship.o: ships/Ship.cpp ships/Ship.h ships/Segment.h
	g++ -c ships/Ship.cpp
ShipManager.o: ships/ShipManager.cpp ships/ShipManager.h ships/Ship.h save/GameState.h
	g++ -c ships/ShipManager.cpp
Cell.o: field/Cell.cpp field/Cell.h ships/Ship.h
	g++ -c field/Cell.cpp
PlayingField.o: field/PlayingField.cpp field/PlayingField.h field/Cell.h exceptions/Exceptions.h
	g++ -c field/PlayingField.cpp
DoubleDamage.o: abilities/DoubleDamage.cpp abilities/DoubleDamage.h abilities/Ability.h
	g++ -c abilities/DoubleDamage.cpp
Shelling.o: abilities/Shelling.cpp abilities/Shelling.h abilities/Ability.h
	g++ -c abilities/Shelling.cpp
Segment.o: ships/Segment.cpp ships/Segment.h
	g++ -c ships/Segment.cpp
Scanner.o: abilities/Scanner.cpp abilities/Scanner.h abilities/Ability.h
	g++ -c abilities/Scanner.cpp
AbilityManager.o: abilities/AbilityManager.cpp abilities/AbilityManager.h abilities/Ability.h abilities/Scanner.h abilities/DoubleDamage.h abilities/Shelling.h exceptions/Exceptions.h abilities/AbilityFactory.h
	g++ -c abilities/AbilityManager.cpp
GameMessage.o: print/GameMessage.cpp print/GameMessage.h ships/Ship.h
	g++ -c print/GameMessage.cpp
Game.o: play/Game.cpp play/Game.h field/PlayingField.h abilities/AbilityManager.h ships/ShipManager.h print/GameMessage.h print/FieldDrawer.h save/GameState.h
	g++ -c play/Game.cpp
GameState.o: save/GameState.cpp save/GameState.h abilities/AbilityManager.h ships/ShipManager.h save/FileHandler.h print/GameMessage.h
	g++ -c save/GameState.cpp
FileHandler.o: save/FileHandler.cpp save/FileHandler.h
	g++ -c save/FileHandler.cpp
CommandHandler.o: print/CommandHandler.cpp print/CommandHandler.h 
	g++ -c print/CommandHandler.cpp
FieldDrawer.o: print/FieldDrawer.cpp print/FieldDrawer.h field/PlayingField.h
	g++ -c print/FieldDrawer.cpp
