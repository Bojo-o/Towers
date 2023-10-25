///////////////////////////////////////////////////////////
///// Towers! game - All types of attack at monster units
///////////////////////////////////////////////////////////

#pragma once

struct ArcherAttack{
	ArcherAttack(const float val) { value = val; }
	float value;
};
struct CanonAttack {
	CanonAttack(const float val) { value = val; }
	float value;
};
struct TurretAttack {
	TurretAttack(const float val) { value = val; }
	float value;
};
struct AirAttack {
	AirAttack(const float val) { value = val; }
	float value;
};
struct AirTurretAttack {
	AirTurretAttack(const float val) { value = val; }
	float value;
};
struct IceAttack {
	IceAttack(const Percentage val) { value = val; }
	Percentage value;
};
struct WindAttack {
	WindAttack(Percentage val) { value = val; }
	Percentage value;
};
struct FireAttack {
	FireAttack(const float val) { value = val; }
	float value;
};
struct PoisonAttack {
	PoisonAttack(const float val) { value = val; }
	float value;
};
struct StormAttack {
	StormAttack(const float val) { value = val; }
	float value;
};
struct ExplodeAttack {
	ExplodeAttack(const float val) { value = val; }
	float value;
};