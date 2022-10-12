#include <unordered_map>
#include "Framework.h"
#pragma once

// assets paths
const std::unordered_map<const char*, const char*> assetPath =
{
	//tiles
	{"aquaTile", "data\\Aqua_Tile.png"},
	{"blueTile", "data\\Blue_Tile.png"},
	{"goldenTile", "data\\Golden_Tile.png"},
	{"greenTile", "data\\Green_Tile.png"},
	{"limeTile", "data\\Lime_Tile.png"},
	{"orangeTile", "data\\Orange_Tile.png"},
	{"redTile", "data\\Red_Tile.png"},
	{"grayTile", "data\\Gray_Tile.png"},

	//broken tiles
	//{"aquaTileBroken", "data\\Aqua_Tile_Broken.png"},
	//{"blueTileBroken", "data\\Blue_Tile_Broken.png"},
	//{"greenTileBroken", "data\\Green_Tile_Broken.png"},
	//{"limeTileBroken", "data\\Lime_Tile_Broken.png"},
	{"orangeTileBroken", "data\\Orange_Tile_Broken.png"},
	{"redTileBroken", "data\\Red_Tile_Broken.png"},
	{"grayTileBroken", "data\\Gray_Tile_Broken.png"},

	//platforms
	{"platformLong", "data\\Platform_Long.png"},
	{"platformNormal1", "data\\Platform_Normal_1.png"},
	{"platformShort", "data\\Platform_Short.png"},

	//balls
	{"ballSizeMax", "data\\Ball_Size_Max.png"},

	//life
	{"life", "data\\Life.png"},

	//abilities
	{"abilityPlatformLong", "data\\Ability_Platform_Long.png"},
	{"abilityPlatformShort", "data\\Ability_Platform_Short.png"},
	{"abilityBallBig", "data\\Ability_Ball_Big.png"},
	{"abilityBallSmall", "data\\Ability_Ball_Small.png"}
};