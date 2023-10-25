///////////////////////////////////////////////////////////
///// Towers! game - Stats for Monster and Towers
///////////////////////////////////////////////////////////

#pragma once

// headers
#include "Percentage.h"

// Stats for Monster , HP , Damege , Speed
class MonsterStats {
public:
	float MonsterHP = 0;
	float MonsterDamage = 0;
	float MonsterSpeed = 0;
	unsigned KilledValue = 0;
	MonsterStats(){}
	MonsterStats(const float hp,const float damage ,const float speed,const unsigned killedValue);
};
// Stats for Tower , Range , Damege , Speed/Cooldown , Level of upgrading , prices , upgrading ratio
class TowerStats {
public:
	float TowerRange = 0;
	float TowerDamage = 0;
	float TowerSpeed = 0;
	unsigned UpgradePrice = 0;
	unsigned SellPrice = 0;
	unsigned Level = 1;
	float TowerRangeUpgradeRatio = 1;
	float TowerDamageUpgradeRatio = 1;
	float TowerSpeedUpgradeRatio = 1;
	float PriceUpgradeRatio = 1;
	TowerStats() {};
	TowerStats(const float range,const float damage,const float speed,const unsigned upgradePrice,const unsigned sellPrice,const float rangeUpgrade,const float damageUpgrade,const float speedUpgrade,const float upgradePriceUpgrade);
	void EditStats(const float range, const float damage, const float speed, const unsigned upgradePrice, const unsigned sellPrice, const float rangeUpgrade, const float damageUpgrade, const float speedUpgrade, const float upgradePriceUpgrade);
	void Upgrade();
};