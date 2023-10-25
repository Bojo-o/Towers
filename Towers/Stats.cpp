///////////////////////////////////////////////////////////
///// Towers! game - Stats for Monster and Towers
///////////////////////////////////////////////////////////

// headers
#include "Stats.h"

MonsterStats::MonsterStats(const float hp, const float damage, const float speed, const unsigned killedValue) {
	MonsterHP = hp;
	MonsterDamage = damage;
	MonsterSpeed = speed;
	KilledValue = killedValue;
}
TowerStats::TowerStats(const float range, const float damage, const float speed, const unsigned upgradePrice, const unsigned sellPrice, const float rangeUpgrade, const float damageUpgrade, const float speedUpgrade, const float upgradePriceUpgrade) {
	TowerRange = range;
	TowerDamage = damage;
	TowerSpeed = speed;
	UpgradePrice = upgradePrice;
	SellPrice = sellPrice;
	TowerRangeUpgradeRatio = rangeUpgrade;
	TowerDamageUpgradeRatio = damageUpgrade;
	TowerSpeedUpgradeRatio = speedUpgrade;
	PriceUpgradeRatio = upgradePriceUpgrade;
}
void TowerStats::EditStats(const float range, const float damage, const float speed, const unsigned upgradePrice, const unsigned sellPrice, const float rangeUpgrade, const float damageUpgrade, const float speedUpgrade, const float upgradePriceUpgrade) {
	TowerRange = range;
	TowerDamage = damage;
	TowerSpeed = speed;
	UpgradePrice = upgradePrice;
	SellPrice = sellPrice;
	TowerRangeUpgradeRatio = rangeUpgrade;
	TowerDamageUpgradeRatio = damageUpgrade;
	TowerSpeedUpgradeRatio = speedUpgrade;
	PriceUpgradeRatio = upgradePriceUpgrade;
}
void TowerStats::Upgrade() {
	TowerRange *= TowerRangeUpgradeRatio;
	TowerDamage *= TowerDamageUpgradeRatio;
	TowerSpeed /= TowerSpeedUpgradeRatio;
	UpgradePrice = static_cast<unsigned>(UpgradePrice * PriceUpgradeRatio);
	SellPrice = static_cast<unsigned>(SellPrice * PriceUpgradeRatio);
	Level += 1;
}