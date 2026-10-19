#include "data/blob_pieces.h"
#include "data/sprite_pointers.h"
#include "sprites_AI/sprites.h"
#include "gba/memory.h"

void AbilityAura(void);
void Arachnus(void);
void ArachnusArm1(void);
void ArachnusArm2(void);
void ArachnusFire(void);
void ArachnusHead(void);
void ArachnusShell(void);
void ArachnusSlash(void);
void ArachnusSlashTrail(void);
void AreaBanner(void);
void AtmosphericStabilizer(void);
void AtmosphericStabilizerCover(void);
void AtmosphericStabilizerParasite(void);
void BabyDachora(void);
void BeamCoreX(void);
void BeamCoreXEye(void);
void BeamCoreXGlowing(void);
void BeamCoreXShell(void);
void BlueX(void);
void BlueXAbsorbtion(void);
void Box(void);
void Box2(void);
void Box2BrainBottom(void);
void Box2BrainTop(void);
void Box2Missile(void);
void Box2Part(void);
void BoxBomb(void);
void BoxDebris(void);
void BoxFallingDebris(void);
void BoxFire(void);
void BoxMissile(void);
void BoxPart(void);
void Bull(void);
void BullSmoke(void);
void Choot(void);
void ChootSpit(void);
void ChozoStatue(void);
void ContinualXSpawner(void);
void CoreXAbility(void);
void CoreXAbilityBeforeVariaCore(void);
void CoreXChargeBeam(void);
void CoreXPlasmaBeam(void);
void CoreXShell(void);
void CoreXShellBeforeVariaCore(void);
void CoreXShellVaria(void);
void CoreXStaticBeforeVariaCore(void);
void CoreXWaveIceBeam(void);
void CoreXWideBeam(void);
void Dachora(void);
void DataPad(void);
void DataPadCenter(void);
void DataPadSides(void);
void Dessgeega(void);
void DessgeegaSpike(void);
void DestroyedDataPad(void);
void ElectricWater(void);
void ElectricWaterDamage(void);
void ElectricWaterDamageBox2(void); // asm
void ElectricWire(void);
void Etecoon(void);
void Evir(void);
void EvirCollision(void);
void EvirProjectile(void);
void FakeChozoBall(void);
void FrozenRidley(void);
void FrozenRidleyX(void);
void Fune(void);
void FuneSpit(void);
void Gadora(void);
void GadoraBeam(void);
void GadoraEye(void);
void GadoraRoots(void);
void Gadora_UnusedSprite(void);
void Gate(void);
void GateSwitch(void);
void Geega(void);
void Geemer(void);
void GeemerFlashingLight(void);
void Genesis(void);
void GenesisSpit(void);
void Geruboss(void);
void Geruta(void);
void GoldSciserDoorLock(void);
void GoldZebesianDoorLock(void);
void Gunship(void);
void GunshipBeam(void);
void GunshipEnd(void); // asm
void GunshipEndBeam(void); // asm
void GunshipEndBottom(void); // asm
void GunshipPart(void);
void HabitationGate(void);
void HabitationGateLight(void);
void Halzyn(void);
void HalzynWing(void);
void Hornoad(void);
void HornoadSpawner(void);
void HornoadSpit(void);
void IceBeamAbility(void);
void Kago(void);
void KagoInsect(void);
void KihunterBug(void);
void KihunterFlying(void);
void KihunterGround(void);
void KihunterHive(void);
void KihunterSpit(void);
void KihunterWings(void);
void LabDebris(void);
void LabExplosion(void);
void LavaPlume(void);
void LavaPlumeWarning(void);
void MegaX(void);
void MegaXShield(void);
void Memu(void);
void MessageBanner(void);
void Metroid(void);
void MetroidHusk(void);
void MimicEnergyTank(void);
void MimicMissileTank(void);
void MiscPad(void);
void MiscPadConsole(void);
void MissileGeron(void);
void MissileGeronStem(void);
void MissileHatch(void);
void MissileHatchDebris(void);
void Moto(void);
void MotoFront(void);
void MovablePlatform(void);
void Namihe(void);
void NamiheSpit(void);
void NavConsole(void);
void NavConsoleScreen(void);
void NavPad(void);
void NavScreen(void);
void Nettori(void);
void NettoriPart(void);
void NettoriPlasmaBeam(void);
void Nightmare(void);
void NightmareBeam(void);
void NightmareFallingArm(void);
void NightmarePart(void);
void OmegaMetroid(void);
void OmegaMetroidHusk(void);
void OmegaMetroidPart(void);
void OperationsRoomPad(void);
void OperationsRoomPadConsole(void);
void OperationsRoomPadConsoleScreen(void);
void OperationsRoomPadScreen(void);
void Owtch(void);
void Pillar(void);
void Powamp(void);
void PowerBombGeron(void);
void PowerBombGeronStem(void);
void PreBoxCeilingDebris(void);
void Puyo(void);
void RechargePad(void);
void RechargePadMonitor(void);
void RechargePadScreen(void);
void Reo(void);
void ReoWings(void);
void Ridley(void);
void RidleyFire(void);
void RidleyPart(void);
void RidleyPreSpawn(void);
void RidleyTailPart(void);
void Ripper(void);
void SaXArc(void);
void SaXBeam(void);
void SaXBoss(void);
void SaXElevator(void);
void SaXLab(void);
void SaXMissile(void);
void SaXMonster(void);
void SaXMonsterPart(void);
void SaXNoc(void);
void SaXOmega(void);
void SaXPowerBomb(void);
void SaXTro1(void);
void SaXTro2(void);
void SamusEater(void);
void SamusEaterBud(void);
void SamusEaterSpore(void);
void SavePad(void);
void SavePadHologram(void);
void SavePlatform(void);
void SaveYesNoCursor(void);
void Scientist(void);
void Sciser(void);
void SciserProjectile(void);
void SecurityPad(void);
void SecurityPadMonitor(void);
void SecurityPadScreen(void);
void ShakeTrigger(void);
void Sidehopper(void);
void Skree(void);
void Skultera(void);
void Sova(void);
void SovaFire(void);
void SuperMissileGeron(void);
void SuperMissileGeronStem(void);
void TireSwing(void);
void ToxicGas(void);
void ToxicGasExplosion(void);
void VariaSuitAbility(void);
void Waver(void);
void WaverExplosion(void);
void XParasite(void);
void XParasiteAquaZebesian(void);
void XParasiteBossFormation(void);
void XParasiteCoreXOrStabilizer(void);
void XParasiteInRoom(void);
void Yakuza(void);
void YakuzaFallingLeg(void);
void YakuzaPart(void);
void YakuzaProjectile(void);
void Yameba(void);
void Yard(void);
void YardProjectile(void);
void Zazabi(void);
void ZazabiPart(void);
void ZebesianAqua(void);
void ZebesianAquaProjectile(void);
void ZebesianBeam(void);
void ZebesianGround(void);
void ZebesianGroundBeam(void);
void ZebesianWall(void);
void Zeela(void);
void ZeelaProjectile(void);
void Zombie(void);
void Zoro(void);
void ZoroCocoon(void);
void ZoroHusk(void);
void Zozoro(void);
extern const u32 sAnimalsGfx[512 * 4];
extern const u16 sAnimalsPal[PAL_ROW * 4];
extern const u32 sArachnusGfx[512 * 8];
extern const u16 sArachnusPal[16 * 8];
extern const u32 sAreaBannerGfx[1 * 512];
extern const u16 sAreaBannerPal[1 * 16];
extern const u32 sAtmosphericStabilizerGfx[3 * 512];
extern const u16 sAtmosphericStabilizerPal[3 * 16];
extern const u8 sBlob_2e5cae_2e6160[1202];
extern const u8 sBlob_2e6382_2e6ba4[];
extern const u32 sBlueXGfx[1024];
extern const u16 sBlueXPal[2 * 16];
extern const u32 sBlueZoroGfx[1 * 512];
extern const u16 sBlueZoroPal[1 * 16];
extern const u32 sBox2Gfx[512 * 7];
extern const u16 sBox2Pal[PAL_ROW * 7];
extern const u32 sBoxGfx[512 * 8];
extern const u16 sBoxPal[16 * 8];
extern const u32 sBullGfx[512 * 1];
extern const u16 sBullPal[16 * 1];
extern const u32 sChargeBeamCoreXGfx[5 * 512];
extern const u16 sChargeBeamCoreXPal[5 * 16];
extern const u32 sChootGfx[512 * 1];
extern const u16 sChootPal[16 * 1];
extern const u32 sChozoStatueGfx[1 * 512];
extern const u16 sChozoStatuePal[1 * 16];
extern const u32 sControlPadGfx[2 * 512];
extern const u16 sControlPadPal[2 * 16];
extern const u32 sCoreXDownloadingVariaGfx[512 * 4];
extern const u16 sCoreXDownloadingVariaPal[16 * 4];
extern const u32 sDataPadGfx[512 * 3];
extern const u16 sDataPadPal[16 * 3];
extern const u32 sDessgeegaGfx[512 * 1];
extern const u16 sDessgeegaPal[16 * 1];
extern const u32 sDestroyedDataPadGfx[512];
extern const u16 sDestroyedDataPadPal[16 * 1];
extern const u32 sElectricWaterGfx[2 * 512];
extern const u16 sElectricWaterPal[2 * 16];
extern const u32 sEvirGfx[512 * 2];
extern const u16 sEvirPal[16 * 2];
extern const u32 sFrozenRidleyGfx[2 * 512];
extern const u16 sFrozenRidleyPal[2 * 16];
extern const u32 sFuneNamiheGfx[2 * 512];
extern const u16 sFuneNamihePal[2 * 16];
extern const u32 sGadoraGfx[1024];
extern const u16 sGadoraPal[2 * 16];
extern const u32 sGateGfx[1 * 512];
extern const u16 sGatePal[1 * 16];
extern const u32 sGeegaGfx[512 * 1];
extern const u16 sGeegaPal[16 * 1];
extern const u32 sGeemerGfx[512 * 2];
extern const u16 sGeemerPal[16 * 2];
extern const u32 sGenesisGfx[512 * 2];
extern const u16 sGenesisPal[16 * 2];
extern const u32 sGerubossGfx[512 * 1];
extern const u16 sGerubossPal[16 * 1];
extern const u32 sGerutaGfx[512 * 1];
extern const u16 sGerutaPal[16 * 1];
extern const u32 sGoldSciserGfx[512 * 2];
extern const u16 sGoldSciserPal[16 * 2];
extern const u32 sGoldZebesianGfx[512 * 3];
extern const u16 sGoldZebesianPal[16 * 3];
extern const u32 sGravityCoreXGfx[512 * 5];
extern const u16 sGravityCoreXPal[16 * 5];
extern const u32 sGunshipGfx[6 * 512];
extern const u16 sGunshipPal[6 * 16];
extern const u32 sHabitationPadGfx[1 * 512];
extern const u16 sHabitationPadPal[1 * 16];
extern const u32 sHalzynGfx[1024];
extern const u16 sHalzynPal[16 * 2];
extern const u32 sHiJumpCoreXGfx[512 * 5];
extern const u16 sHiJumpCoreXPal[16 * 5];
extern const u32 sHornoadGfx[512 * 3];
extern const u16 sHornoadPal[16 * 3];
extern const u32 sIceBeamAbilityOmegaGfx[512 * 2];
extern const u16 sIceBeamAbilityOmegaPal[16 * 1];
extern const u32 sIceBeamCoreXGfx[5 * 512];
extern const u16 sIceBeamCoreXPal[5 * 16];
extern const u32 sKagoGfx[2 * 512];
extern const u16 sKagoPal[2 * 16];
extern const u32 sKihunterGfx[3 * 512];
extern const u16 sKihunterPal[3 * 16];
extern const u32 sLabDebrisGfx[512 * 1];
extern const u16 sLabDebrisPal[PAL_ROW * 1];
extern const u32 sLavaPlumeGfx[1 * 512];
extern const u16 sLavaPlumePal[1 * 16];
extern const u32 sMegaXGfx[8 * 512];
extern const u16 sMegaXPal[8 * 16];
extern const u32 sMemuGfx[512 * 1];
extern const u16 sMemuPal[16 * 1];
extern const u32 sMessageBannerGfx[512 * 2];
extern const u16 sMessageBannerPal[16 * 2];
extern const u32 sMetroidGfx[512 * 1];
extern const u32 sMetroidHuskGfx[512 * 1];
extern const u16 sMetroidHuskPal[16 * 1];
extern const u16 sMetroidPal[PAL_ROW * 1];
extern const u32 sMimicEnergyTankGfx[1 * 512];
extern const u16 sMimicEnergyTankPal[1 * 16];
extern const u32 sMimicMissileTankGfx[1 * 512];
extern const u16 sMimicMissileTankPal[1 * 16];
extern const u32 sMissileGeronGfx[512 * 1];
extern const u16 sMissileGeronPal[16 * 1];
extern const u32 sMissileHatchGfx[512];
extern const u16 sMissileHatchPal[1 * 16];
extern const u32 sMorphBallCoreXGfx[512 * 5];
extern const u16 sMorphBallCoreXPal[16 * 5];
extern const u32 sMotoGfx[1536];
extern const u16 sMotoPal[48];
extern const u32 sMovablePlatformGfx[512];
extern const u16 sMovablePlatformPal[16 * 1];
extern const u32 sNavigationPadGfx[512 * 3];
extern const u16 sNavigationPadPal[16 * 3];
extern const u32 sNettoriGfx[4096];
extern const u16 sNettoriPal[8 * 16];
extern const u32 sNightmareGfx[512 * 8];
extern const u16 sNightmarePal[16 * 8];
extern const u32 sOmegaMetroidGfx[512 * 5];
extern const u32 sOmegaMetroidHuskGfx[512 * 2];
extern const u16 sOmegaMetroidHuskPal[16 * 2];
extern const u16 sOmegaMetroidPal[PAL_ROW * 5];
extern const u32 sOperationsRoomPadGfx[2 * 512];
extern const u16 sOperationsRoomPadPal[2 * 16];
extern const u32 sOwtchGfx[512];
extern const u16 sOwtchPal[16];
extern const u32 sPillarGfx[512 * 1];
extern const u16 sPillarPal[16 * 1];
extern const u32 sPlasmaBeamCoreXGfx[5 * 512];
extern const u16 sPlasmaBeamCoreXPal[5 * 16];
extern const u32 sPowampGfx[512 * 1];
extern const u16 sPowampPal[PAL_ROW * 1];
extern const u32 sPowerBombGeronGfx[1024];
extern const u16 sPowerBombGeronPal[2 * 16];
extern const u32 sPuyoGfx[1 * 512];
extern const u16 sPuyoPal[1 * 16];
extern const u32 sRechargePadGfx[3 * 512];
extern const u16 sRechargePadPal[3 * 16];
extern const u32 sRedZeelaGfx[2 * 512];
extern const u16 sRedZeelaPal[2 * 16];
extern const u32 sReoGfx[1 * 512];
extern const u16 sReoPal[1 * 16];
extern const u32 sRidleyGfx[512 * 8];
extern const u16 sRidleyPal[16 * 8];
extern const u32 sRidleyPreSpawnGfx[512 * 2];
extern const u16 sRidleyPreSpawnPal[16 * 2];
extern const u32 sRipperGfx[512];
extern const u16 sRipperPal[1 * 16];
extern const u32 sSaXLabExplosionsGfx[2 * 512];
extern const u16 sSaXLabExplosionsPal[2 * 16];
extern const u32 sSaXMonsterGfx[512 * 8];
extern const u16 sSaXMonsterPal[PAL_ROW * 8];
extern const u16 sSaXPalette_Default[2 * 16];
extern const u32 sSaXWeaponsGfx[2 * 512];
extern const u32 sSavePadGfx[3 * 512];
extern const u16 sSavePadPal[3 * 16];
extern const u32 sScientistGfx[2 * 512];
extern const u16 sScientistPal[2 * 16];
extern const u32 sSciserGfx[512 * 2];
extern const u16 sSciserPal[16 * 2];
extern const u32 sScrewAttackCoreXGfx[512 * 5];
extern const u16 sScrewAttackCoreXPal[16 * 5];
extern const u32 sSecurityPadGfx[3 * 512];
extern const u16 sSecurityPadPal[3 * 16];
extern const u32 sSidehopperGfx[512 * 1];
extern const u16 sSidehopperPal[16 * 1];
extern const u32 sSkreeGfx[512];
extern const u16 sSkreePal[16 * 1];
extern const u32 sSkulteraGfx[2 * 512];
extern const u16 sSkulteraPal[2 * 16];
extern const u32 sSovaGfx[3 * 512];
extern const u16 sSovaPal[3 * 16];
extern const u32 sSpaceJumpCoreXGfx[512 * 5];
extern const u16 sSpaceJumpCoreXPal[16 * 5];
extern const u32 sSpeedBoosterCoreXGfx[512 * 5];
extern const u16 sSpeedBoosterCoreXPal[16 * 5];
extern const u32 sSuperMissileGeronGfx[512];
extern const u16 sSuperMissileGeronPal[1 * 16];
extern const u32 sToxicGasGfx[2 * 512];
extern const u16 sToxicGasPal[2 * 16];
extern const u32 sWaveBeamCoreXGfx[5 * 512];
extern const u16 sWaveBeamCoreXPal[5 * 16];
extern const u32 sWaverGfx[2 * 512];
extern const u16 sWaverPal[2 * 16];
extern const u32 sWideBeamCoreXGfx[5 * 512];
extern const u16 sWideBeamCoreXPal[5 * 16];
extern const u32 sYakuzaGfx[512 * 8];
extern const u16 sYakuzaPal[16 * 8];
extern const u32 sYamebaGfx[2 * 512];
extern const u16 sYamebaPal[2 * 16];
extern const u32 sYardGfx[512 * 3];
extern const u16 sYardPal[16 * 3];
extern const u32 sZazabiGfx[4096];
extern const u16 sZazabiPal[8 * 16];
extern const u32 sZebesianAquaGfx[512 * 2];
extern const u16 sZebesianAquaPal[PAL_ROW * 2];
extern const u32 sZebesianGroundGfx[512 * 3];
extern const u16 sZebesianGroundPal[16 * 3];
extern const u32 sZebesianWallGfx[2 * 512];
extern const u16 sZebesianWallPal[2 * 16];
extern const u32 sZeelaGfx[2 * 512];
extern const u16 sZeelaPal[2 * 16];
extern const u32 sZombieGfx[512 * 3];
extern const u16 sZombiePal[16 * 3];
extern const u32 sZoroCocoonGfx[1024];
extern const u16 sZoroCocoonPal[2 * 16];
extern const u32 sZoroGfx[1 * 512];
extern const u32 sZoroHuskGfx[512];
extern const u16 sZoroHuskPal[1 * 16];
extern const u16 sZoroPal[1 * 16];
extern const u32 sZozoroGfx[2 * 512];
extern const u16 sZozoroPal[1 * 16];

const Func_T sPrimarySpritesAiPointers[PSPRITE_END] = {
    [PSPRITE_TARGET_CIRCLES] = TargetCircles,
	[PSPRITE_TARGET_DIAGONAL] = TargetDiagonal,
	[PSPRITE_TARGET_SIDEWAYS] = TargetSideways,
	[PSPRITE_UNUSED_3] = UnusedSprites,
	[PSPRITE_UNUSED_4] = UnusedSprites,
	[PSPRITE_UNUSED_5] = UnusedSprites,
	[PSPRITE_UNUSED_6] = UnusedSprites,
	[PSPRITE_UNUSED_7] = UnusedSprites,
	[PSPRITE_UNUSED_8] = UnusedSprites,
	[PSPRITE_UNUSED_9] = UnusedSprites,
	[PSPRITE_UNUSED_10] = UnusedSprites,
	[PSPRITE_UNUSED_11] = UnusedSprites,
	[PSPRITE_UNUSED_12] = UnusedSprites,
	[PSPRITE_UNUSED_13] = UnusedSprites,
	[PSPRITE_CORE_X_TARGET] = TargetCoreX,
	[PSPRITE_UNUSED_15] = UnusedSprites,
	[PSPRITE_UNUSED_16] = UnusedSprites,
	[PSPRITE_SA_X_ELEVATOR] = (Func_T)SaXElevator,
	[PSPRITE_HORNOAD] = (Func_T)Hornoad,
	[PSPRITE_HALZYN] = (Func_T)Halzyn,
	[PSPRITE_ZEBESIAN_WALL] = (Func_T)ZebesianWall,
	[PSPRITE_HORNOAD_SPAWNER] = (Func_T)HornoadSpawner,
	[PSPRITE_GATE] = (Func_T)Gate,
	[PSPRITE_MOVABLE_PLATFORM_1] = (Func_T)MovablePlatform,
	[PSPRITE_MOTO] = (Func_T)Moto,
	[PSPRITE_NAVIGATION_PAD] = (Func_T)NavPad,
	[PSPRITE_GUNSHIP] = (Func_T)Gunship,
	[PSPRITE_YAMEBA] = (Func_T)Yameba,
	[PSPRITE_SECURITY_PAD] = (Func_T)SecurityPad,
	[PSPRITE_AREA_BANNER] = (Func_T)AreaBanner,
	[PSPRITE_DATA_PAD] = (Func_T)DataPad,
	[PSPRITE_SAVE_PAD] = (Func_T)SavePad,
	[PSPRITE_PRE_BOX_CEILING_DEBRIS] = (Func_T)PreBoxCeilingDebris,
	[PSPRITE_MESSAGE_BANNER] = (Func_T)MessageBanner,
	[PSPRITE_KAGO] = (Func_T)Kago,
	[PSPRITE_ELECTRIC_WATER_DAMAGE] = (Func_T)ElectricWaterDamage,
	[PSPRITE_ELECTRIC_WATER] = (Func_T)ElectricWater,
	[PSPRITE_WIRE] = (Func_T)ElectricWire,
	[PSPRITE_SAMUS_EATER_BUD] = (Func_T)SamusEaterBud,
	[PSPRITE_SAMUS_EATER] = (Func_T)SamusEater,
	[PSPRITE_ENERGY_RECHARGE_PAD] = (Func_T)RechargePad,
	[PSPRITE_AMMO_RECHARGE_PAD] = (Func_T)RechargePad,
	[PSPRITE_ENERGY_AMMO_RECHARGE_PAD] = (Func_T)RechargePad,
	[PSPRITE_ATMOSPHERIC_STABILIZER_PARASITE] = (Func_T)AtmosphericStabilizerParasite,
	[PSPRITE_ATMOSPHERIC_STABILIZER_1] = (Func_T)AtmosphericStabilizer,
	[PSPRITE_ATMOSPHERIC_STABILIZER_2] = (Func_T)AtmosphericStabilizer,
	[PSPRITE_ATMOSPHERIC_STABILIZER_3] = (Func_T)AtmosphericStabilizer,
	[PSPRITE_ATMOSPHERIC_STABILIZER_4] = (Func_T)AtmosphericStabilizer,
	[PSPRITE_ATMOSPHERIC_STABILIZER_5] = (Func_T)AtmosphericStabilizer,
	[PSPRITE_ZEELA] = (Func_T)Zeela,
	[PSPRITE_X_PARASITE_CORE_X_OR_PARASITE] = (Func_T)XParasiteCoreXOrStabilizer,
	[PSPRITE_SKREE] = (Func_T)Skree,
	[PSPRITE_X_PARASITE_IN_ROOM] = (Func_T)XParasiteInRoom,
	[PSPRITE_TOXIC_GAS] = (Func_T)ToxicGas,
	[PSPRITE_X_PARASITE_IN_ROOM_PROXIMITY] = (Func_T)XParasiteInRoom,
	[PSPRITE_ZOMBIE] = (Func_T)Zombie,
	[PSPRITE_X_PARASITE] = (Func_T)XParasite,
	[PSPRITE_GEEMER] = (Func_T)Geemer,
	[PSPRITE_ARACHNUS] = (Func_T)Arachnus,
	[PSPRITE_WAVER] = (Func_T)Waver,
	[PSPRITE_SCISER] = (Func_T)Sciser,
	[PSPRITE_SIDEHOPPER] = (Func_T)Sidehopper,
	[PSPRITE_DESSGEEGA] = (Func_T)Dessgeega,
	[PSPRITE_MORPH_BALL_ABILITY] = (Func_T)CoreXAbility,
	[PSPRITE_X_PARASITE_CORE_X_FORMATION] = (Func_T)XParasiteBossFormation,
	[PSPRITE_GERON_MISSILE_1] = (Func_T)MissileGeron,
	[PSPRITE_GERON_MISSILE_2] = (Func_T)MissileGeron,
	[PSPRITE_GERON_MISSILE_3] = (Func_T)MissileGeron,
	[PSPRITE_HIGH_JUMP_ABILITY] = (Func_T)CoreXAbility,
	[PSPRITE_SPEEDBOOSTER_ABILITY] = (Func_T)CoreXAbility,
	[PSPRITE_VARIA_SUIT_ABILITY] = (Func_T)VariaSuitAbility,
	[PSPRITE_SPACE_JUMP_ABILITY] = (Func_T)CoreXAbility,
	[PSPRITE_GRAVITY_SUIT_ABILITY] = (Func_T)CoreXAbility,
	[PSPRITE_SCREW_ATTACK_ABILITY] = (Func_T)CoreXAbility,
	[PSPRITE_MOVABLE_PLATFORM_2] = (Func_T)MovablePlatform,
	[PSPRITE_ZAZABI] = (Func_T)Zazabi,
	[PSPRITE_OMEGA_METROID_HUSK] = (Func_T)OmegaMetroidHusk,
	[PSPRITE_ICE_BEAM_ABILITY] = (Func_T)IceBeamAbility,
	[PSPRITE_MOVABLE_PLATFORM_3] = (Func_T)MovablePlatform,
	[PSPRITE_MOVABLE_PLATFORM_4] = (Func_T)MovablePlatform,
	[PSPRITE_MOVABLE_PLATFORM_5] = (Func_T)MovablePlatform,
	[PSPRITE_YAKUZA] = (Func_T)Yakuza,
	[PSPRITE_CHOZO_STATUE] = (Func_T)ChozoStatue,
	[PSPRITE_SCIENTIST] = (Func_T)Scientist,
	[PSPRITE_NETTORI] = (Func_T)Nettori,
	[PSPRITE_BOX_2] = (Func_T)Box2,
	[PSPRITE_CHARGE_BEAM_CORE_X] = (Func_T)BeamCoreX,
	[PSPRITE_WIDE_BEAM_CORE_X] = (Func_T)BeamCoreX,
	[PSPRITE_PLASMA_BEAM_CORE_X] = (Func_T)BeamCoreX,
	[PSPRITE_WAVE_BEAM_CORE_X] = (Func_T)BeamCoreX,
	[PSPRITE_ZORO] = (Func_T)Zoro,
	[PSPRITE_KIHUNTER_FLYING] = (Func_T)KihunterFlying,
	[PSPRITE_KIHUNTER_GROUND] = (Func_T)KihunterGround,
	[PSPRITE_KIHUNTER_HIVE] = (Func_T)KihunterHive,
	[PSPRITE_REO] = (Func_T)Reo,
	[PSPRITE_LAVA_PLUME] = (Func_T)LavaPlume,
	[PSPRITE_NAHIME] = (Func_T)Namihe,
	[PSPRITE_FUNE] = (Func_T)Fune,
	[PSPRITE_BOX] = (Func_T)Box,
	[PSPRITE_BLUE_ZORO] = (Func_T)Zoro,
	[PSPRITE_GERUTA] = (Func_T)Geruta,
	[PSPRITE_PUMP_CONTROL_PAD] = (Func_T)MiscPad,
	[PSPRITE_BOILER_CONTROL_PAD] = (Func_T)MiscPad,
	[PSPRITE_AUXILARY_POWER_PAD] = (Func_T)MiscPad,
	[PSPRITE_HABITAION_PAD] = (Func_T)MiscPad,
	[PSPRITE_OPERATIONS_ROOM_PAD] = (Func_T)OperationsRoomPad,
	[PSPRITE_SKULTERA_LARGE] = (Func_T)Skultera,
	[PSPRITE_SKULTERA_SMALL_1] = (Func_T)Skultera,
	[PSPRITE_SOVA] = (Func_T)Sova,
	[PSPRITE_YARD] = (Func_T)Yard,
	[PSPRITE_EVIR] = (Func_T)Evir,
	[PSPRITE_BULL] = (Func_T)Bull,
	[PSPRITE_MEMU] = (Func_T)Memu,
	[PSPRITE_GERUBOSS] = (Func_T)Geruboss,
	[PSPRITE_CHOOT] = (Func_T)Choot,
	[PSPRITE_ZEBESIAN_GROUND] = (Func_T)ZebesianGround,
	[PSPRITE_BLUE_X] = (Func_T)BlueX,
	[PSPRITE_MISSILE_HATCH] = (Func_T)MissileHatch,
	[PSPRITE_QUARANTINE_BAY_HORNOAD] = (Func_T)Hornoad,
	[PSPRITE_BOX_DEBRIS] = (Func_T)BoxDebris,
	[PSPRITE_GERON_SUPER_MISSILE_1] = (Func_T)SuperMissileGeron,
	[PSPRITE_GERON_SUPER_MISSILE_2] = (Func_T)SuperMissileGeron,
	[PSPRITE_GERON_SUPER_MISSILE_3] = (Func_T)SuperMissileGeron,
	[PSPRITE_GERON_SUPER_MISSILE_4] = (Func_T)SuperMissileGeron,
	[PSPRITE_GERON_SUPER_MISSILE_5] = (Func_T)SuperMissileGeron,
	[PSPRITE_GERON_SUPER_MISSILE_6] = (Func_T)SuperMissileGeron,
	[PSPRITE_GERON_SUPER_MISSILE_7] = (Func_T)SuperMissileGeron,
	[PSPRITE_GERON_SUPER_MISSILE_8] = (Func_T)SuperMissileGeron,
	[PSPRITE_GERON_POWER_BOMB_1] = (Func_T)PowerBombGeron,
	[PSPRITE_GERON_POWER_BOMB_2] = (Func_T)PowerBombGeron,
	[PSPRITE_GERON_POWER_BOMB_3] = (Func_T)PowerBombGeron,
	[PSPRITE_GERON_POWER_BOMB_4] = (Func_T)PowerBombGeron,
	[PSPRITE_GERON_POWER_BOMB_5] = (Func_T)PowerBombGeron,
	[PSPRITE_GERON_POWER_BOMB_6] = (Func_T)PowerBombGeron,
	[PSPRITE_GERON_POWER_BOMB_7] = (Func_T)PowerBombGeron,
	[PSPRITE_GERON_POWER_BOMB_8] = (Func_T)PowerBombGeron,
	[PSPRITE_RIPPER] = (Func_T)Ripper,
	[PSPRITE_ZORO_COCOON] = (Func_T)ZoroCocoon,
	[PSPRITE_ZORO_HUSK] = (Func_T)ZoroHusk,
	[PSPRITE_GOLD_SCISER] = (Func_T)Sciser,
	[PSPRITE_SA_X_TRO_1] = (Func_T)SaXTro1,
	[PSPRITE_SA_X_NOC] = (Func_T)SaXNoc,
	[PSPRITE_PRE_DESTROYED_DATA_PAD] = (Func_T)DestroyedDataPad,
	[PSPRITE_GADORA_ARACHNUS] = (Func_T)Gadora,
	[PSPRITE_GADORA_CHARGE_BEAM] = (Func_T)Gadora,
	[PSPRITE_GADORA_ZAZABI] = (Func_T)Gadora,
	[PSPRITE_GADORA_SERRIS] = (Func_T)Gadora,
	[PSPRITE_GADORA_VARIA_CORE] = (Func_T)Gadora,
	[PSPRITE_GADORA_WIDE_BEAM] = (Func_T)Gadora,
	[PSPRITE_GADORA_NIGHTMARE] = (Func_T)Gadora,
	[PSPRITE_GADORA_RIDLEY] = (Func_T)Gadora,
	[PSPRITE_GADORA_NETTORI] = (Func_T)Gadora,
	[PSPRITE_GADORA_YAKUZA] = (Func_T)Gadora,
	[PSPRITE_GADORA_1] = (Func_T)Gadora,
	[PSPRITE_GADORA_2] = (Func_T)Gadora,
	[PSPRITE_GADORA_3] = (Func_T)Gadora,
	[PSPRITE_GADORA_4] = (Func_T)Gadora,
	[PSPRITE_GADORA_5] = (Func_T)Gadora,
	[PSPRITE_GADORA_6] = (Func_T)Gadora,
	[PSPRITE_SHAKE_TRIGGER] = (Func_T)ShakeTrigger,
	[PSPRITE_SA_X_ARC] = (Func_T)SaXArc,
	[PSPRITE_ELEVATOR_PAD] = ElevatorPad,
	[PSPRITE_GOLD_ZEBESIAN] = (Func_T)ZebesianGround,
	[PSPRITE_RED_ZEELA] = (Func_T)Zeela,
	[PSPRITE_OWTCH] = (Func_T)Owtch,
	[PSPRITE_GEEGA] = (Func_T)Geega,
	[PSPRITE_SERRIS] = Serris,
	[PSPRITE_PILLAR] = (Func_T)Pillar,
	[PSPRITE_GENESIS] = (Func_T)Genesis,
	[PSPRITE_PUYO] = (Func_T)Puyo,
	[PSPRITE_BUBBLES_1] = Bubbles1,
	[PSPRITE_BUBBLES_2] = Bubbles2,
	[PSPRITE_WATER_DROP] = WaterDrop,
	[PSPRITE_MIMIC_ENERGY_TANK] = (Func_T)MimicEnergyTank,
	[PSPRITE_MIMIC_MISSILE_TANK] = (Func_T)MimicMissileTank,
	[PSPRITE_CORE_X_ABILITY_BEFORE_VARIA_CORE] = (Func_T)CoreXAbilityBeforeVariaCore,
	[PSPRITE_BIG_FLASHING_NUMBER] = BigFlashingNumber,
	[PSPRITE_FLASHING_NUMBER] = FlashingNumber,
	[PSPRITE_DESTROYED_DATA_PAD] = (Func_T)DestroyedDataPad,
	[PSPRITE_ZEBESIAN_AQUA] = (Func_T)ZebesianAqua,
	[PSPRITE_ZEBESIAN_PRE_AQUA] = (Func_T)ZebesianGround,
	[PSPRITE_SKULTERA_SMALL_2] = (Func_T)Skultera,
	[PSPRITE_ETECOON] = (Func_T)Etecoon,
	[PSPRITE_TIRE_SWING] = (Func_T)TireSwing,
	[PSPRITE_DACHORA] = (Func_T)Dachora,
	[PSPRITE_X_PARASITE_AQUA_ZEBESIAN] = (Func_T)XParasiteAquaZebesian,
	[PSPRITE_METROID] = (Func_T)Metroid,
	[PSPRITE_LAB_DEBRIS] = (Func_T)LabDebris,
	[PSPRITE_SA_X_LAB] = (Func_T)SaXLab,
	[PSPRITE_POWAMP] = (Func_T)Powamp,
	[PSPRITE_ZOZORO] = (Func_T)Zozoro,
	[PSPRITE_CONTINUAL_X_SPAWNER] = (Func_T)ContinualXSpawner,
	[PSPRITE_SA_X_BOSS] = (Func_T)SaXBoss,
	[PSPRITE_SA_X_MONSTER] = (Func_T)SaXMonster,
	[PSPRITE_ICE_BEAM_CORE_X] = (Func_T)BeamCoreX,
	[PSPRITE_OMEGA_METROID] = (Func_T)OmegaMetroid,
	[PSPRITE_GUNSHIP_END] = (Func_T)GunshipEnd,
	[PSPRITE_ELECTRIC_WATER_DAMAGE_BOX_2] = (Func_T)ElectricWaterDamageBox2,
	[PSPRITE_FROZEN_RIDLEY] = (Func_T)FrozenRidley,
	[PSPRITE_GOLD_SCISER_DOOR_LOCK] = (Func_T)GoldSciserDoorLock,
	[PSPRITE_GOLD_ZEBESIAN_DOOR_LOCK] = (Func_T)GoldZebesianDoorLock,
	[PSPRITE_SA_X_OMEGA_CUTSCENE] = (Func_T)SaXOmega,
	[PSPRITE_METROID_HUSK] = (Func_T)MetroidHusk,
	[PSPRITE_RIDLEY] = (Func_T)Ridley,
	[PSPRITE_PRE_SPAWN] = (Func_T)RidleyPreSpawn,
	[PSPRITE_SA_X_TRO_2] = (Func_T)SaXTro2,
	[PSPRITE_NIGHTMARE] = (Func_T)Nightmare
};

const u32* const sSpritesGraphicsPointers[PSPRITE_END - 0x10] = {
    [PSPRITE_UNUSED_16 - 0x10] = (const u32*)((const u8*)sBlob_2e6382_2e6ba4 + 0x2),
	[PSPRITE_SA_X_ELEVATOR - 0x10] = (const u32*)sSaXWeaponsGfx,
	[PSPRITE_HORNOAD - 0x10] = (const u32*)sHornoadGfx,
	[PSPRITE_HALZYN - 0x10] = (const u32*)sHalzynGfx,
	[PSPRITE_ZEBESIAN_WALL - 0x10] = (const u32*)sZebesianWallGfx,
	[PSPRITE_HORNOAD_SPAWNER - 0x10] = (const u32*)sHornoadGfx,
	[PSPRITE_GATE - 0x10] = (const u32*)sGateGfx,
	[PSPRITE_MOVABLE_PLATFORM_1 - 0x10] = (const u32*)sMovablePlatformGfx,
	[PSPRITE_MOTO - 0x10] = (const u32*)sMotoGfx,
	[PSPRITE_NAVIGATION_PAD - 0x10] = (const u32*)sNavigationPadGfx,
	[PSPRITE_GUNSHIP - 0x10] = (const u32*)sGunshipGfx,
	[PSPRITE_YAMEBA - 0x10] = (const u32*)sYamebaGfx,
	[PSPRITE_SECURITY_PAD - 0x10] = (const u32*)sSecurityPadGfx,
	[PSPRITE_AREA_BANNER - 0x10] = (const u32*)sAreaBannerGfx,
	[PSPRITE_DATA_PAD - 0x10] = (const u32*)sDataPadGfx,
	[PSPRITE_SAVE_PAD - 0x10] = (const u32*)sSavePadGfx,
	[PSPRITE_PRE_BOX_CEILING_DEBRIS - 0x10] = (const u32*)((const u8*)sBlob_2e6382_2e6ba4 + 0x2),
	[PSPRITE_MESSAGE_BANNER - 0x10] = (const u32*)sMessageBannerGfx,
	[PSPRITE_KAGO - 0x10] = (const u32*)sKagoGfx,
	[PSPRITE_ELECTRIC_WATER_DAMAGE - 0x10] = (const u32*)sElectricWaterGfx,
	[PSPRITE_ELECTRIC_WATER - 0x10] = (const u32*)sElectricWaterGfx,
	[PSPRITE_WIRE - 0x10] = (const u32*)sElectricWaterGfx,
	[PSPRITE_SAMUS_EATER_BUD - 0x10] = (const u32*)sNettoriGfx,
	[PSPRITE_SAMUS_EATER - 0x10] = (const u32*)sNettoriGfx,
	[PSPRITE_ENERGY_RECHARGE_PAD - 0x10] = (const u32*)sRechargePadGfx,
	[PSPRITE_AMMO_RECHARGE_PAD - 0x10] = (const u32*)sRechargePadGfx,
	[PSPRITE_ENERGY_AMMO_RECHARGE_PAD - 0x10] = (const u32*)sRechargePadGfx,
	[PSPRITE_ATMOSPHERIC_STABILIZER_PARASITE - 0x10] = (const u32*)sAtmosphericStabilizerGfx,
	[PSPRITE_ATMOSPHERIC_STABILIZER_1 - 0x10] = (const u32*)sAtmosphericStabilizerGfx,
	[PSPRITE_ATMOSPHERIC_STABILIZER_2 - 0x10] = (const u32*)sAtmosphericStabilizerGfx,
	[PSPRITE_ATMOSPHERIC_STABILIZER_3 - 0x10] = (const u32*)sAtmosphericStabilizerGfx,
	[PSPRITE_ATMOSPHERIC_STABILIZER_4 - 0x10] = (const u32*)sAtmosphericStabilizerGfx,
	[PSPRITE_ATMOSPHERIC_STABILIZER_5 - 0x10] = (const u32*)sAtmosphericStabilizerGfx,
	[PSPRITE_ZEELA - 0x10] = (const u32*)sZeelaGfx,
	[PSPRITE_X_PARASITE_CORE_X_OR_PARASITE - 0x10] = (const u32*)((const u8*)sBlob_2e6382_2e6ba4 + 0x2),
	[PSPRITE_SKREE - 0x10] = (const u32*)sSkreeGfx,
	[PSPRITE_X_PARASITE_IN_ROOM - 0x10] = (const u32*)((const u8*)sBlob_2e6382_2e6ba4 + 0x2),
	[PSPRITE_TOXIC_GAS - 0x10] = (const u32*)sToxicGasGfx,
	[PSPRITE_X_PARASITE_IN_ROOM_PROXIMITY - 0x10] = (const u32*)((const u8*)sBlob_2e6382_2e6ba4 + 0x2),
	[PSPRITE_ZOMBIE - 0x10] = (const u32*)sZombieGfx,
	[PSPRITE_X_PARASITE - 0x10] = (const u32*)((const u8*)sBlob_2e6382_2e6ba4 + 0x2),
	[PSPRITE_GEEMER - 0x10] = (const u32*)sGeemerGfx,
	[PSPRITE_ARACHNUS - 0x10] = (const u32*)sArachnusGfx,
	[PSPRITE_WAVER - 0x10] = (const u32*)sWaverGfx,
	[PSPRITE_SCISER - 0x10] = (const u32*)sSciserGfx,
	[PSPRITE_SIDEHOPPER - 0x10] = (const u32*)sSidehopperGfx,
	[PSPRITE_DESSGEEGA - 0x10] = (const u32*)sDessgeegaGfx,
	[PSPRITE_MORPH_BALL_ABILITY - 0x10] = (const u32*)sMorphBallCoreXGfx,
	[PSPRITE_X_PARASITE_CORE_X_FORMATION - 0x10] = (const u32*)((const u8*)sBlob_2e6382_2e6ba4 + 0x2),
	[PSPRITE_GERON_MISSILE_1 - 0x10] = (const u32*)sMissileGeronGfx,
	[PSPRITE_GERON_MISSILE_2 - 0x10] = (const u32*)sMissileGeronGfx,
	[PSPRITE_GERON_MISSILE_3 - 0x10] = (const u32*)sMissileGeronGfx,
	[PSPRITE_HIGH_JUMP_ABILITY - 0x10] = (const u32*)sHiJumpCoreXGfx,
	[PSPRITE_SPEEDBOOSTER_ABILITY - 0x10] = (const u32*)sSpeedBoosterCoreXGfx,
	[PSPRITE_VARIA_SUIT_ABILITY - 0x10] = (const u32*)sMegaXGfx,
	[PSPRITE_SPACE_JUMP_ABILITY - 0x10] = (const u32*)sSpaceJumpCoreXGfx,
	[PSPRITE_GRAVITY_SUIT_ABILITY - 0x10] = (const u32*)sGravityCoreXGfx,
	[PSPRITE_SCREW_ATTACK_ABILITY - 0x10] = (const u32*)sScrewAttackCoreXGfx,
	[PSPRITE_MOVABLE_PLATFORM_2 - 0x10] = (const u32*)sMovablePlatformGfx,
	[PSPRITE_ZAZABI - 0x10] = (const u32*)sZazabiGfx,
	[PSPRITE_OMEGA_METROID_HUSK - 0x10] = (const u32*)sOmegaMetroidHuskGfx,
	[PSPRITE_ICE_BEAM_ABILITY - 0x10] = (const u32*)sIceBeamAbilityOmegaGfx,
	[PSPRITE_MOVABLE_PLATFORM_3 - 0x10] = (const u32*)sMovablePlatformGfx,
	[PSPRITE_MOVABLE_PLATFORM_4 - 0x10] = (const u32*)sMovablePlatformGfx,
	[PSPRITE_MOVABLE_PLATFORM_5 - 0x10] = (const u32*)sMovablePlatformGfx,
	[PSPRITE_YAKUZA - 0x10] = (const u32*)sYakuzaGfx,
	[PSPRITE_CHOZO_STATUE - 0x10] = (const u32*)sChozoStatueGfx,
	[PSPRITE_SCIENTIST - 0x10] = (const u32*)sScientistGfx,
	[PSPRITE_NETTORI - 0x10] = (const u32*)sNettoriGfx,
	[PSPRITE_BOX_2 - 0x10] = (const u32*)sBox2Gfx,
	[PSPRITE_CHARGE_BEAM_CORE_X - 0x10] = (const u32*)sChargeBeamCoreXGfx,
	[PSPRITE_WIDE_BEAM_CORE_X - 0x10] = (const u32*)sWideBeamCoreXGfx,
	[PSPRITE_PLASMA_BEAM_CORE_X - 0x10] = (const u32*)sPlasmaBeamCoreXGfx,
	[PSPRITE_WAVE_BEAM_CORE_X - 0x10] = (const u32*)sWaveBeamCoreXGfx,
	[PSPRITE_ZORO - 0x10] = (const u32*)sZoroGfx,
	[PSPRITE_KIHUNTER_FLYING - 0x10] = (const u32*)sKihunterGfx,
	[PSPRITE_KIHUNTER_GROUND - 0x10] = (const u32*)sKihunterGfx,
	[PSPRITE_KIHUNTER_HIVE - 0x10] = (const u32*)sKihunterGfx,
	[PSPRITE_REO - 0x10] = (const u32*)sReoGfx,
	[PSPRITE_LAVA_PLUME - 0x10] = (const u32*)sLavaPlumeGfx,
	[PSPRITE_NAHIME - 0x10] = (const u32*)sFuneNamiheGfx,
	[PSPRITE_FUNE - 0x10] = (const u32*)sFuneNamiheGfx,
	[PSPRITE_BOX - 0x10] = (const u32*)sBoxGfx,
	[PSPRITE_BLUE_ZORO - 0x10] = (const u32*)sBlueZoroGfx,
	[PSPRITE_GERUTA - 0x10] = (const u32*)sGerutaGfx,
	[PSPRITE_PUMP_CONTROL_PAD - 0x10] = (const u32*)sControlPadGfx,
	[PSPRITE_BOILER_CONTROL_PAD - 0x10] = (const u32*)sControlPadGfx,
	[PSPRITE_AUXILARY_POWER_PAD - 0x10] = (const u32*)sControlPadGfx,
	[PSPRITE_HABITAION_PAD - 0x10] = (const u32*)sHabitationPadGfx,
	[PSPRITE_OPERATIONS_ROOM_PAD - 0x10] = (const u32*)sOperationsRoomPadGfx,
	[PSPRITE_SKULTERA_LARGE - 0x10] = (const u32*)sSkulteraGfx,
	[PSPRITE_SKULTERA_SMALL_1 - 0x10] = (const u32*)sSkulteraGfx,
	[PSPRITE_SOVA - 0x10] = (const u32*)sSovaGfx,
	[PSPRITE_YARD - 0x10] = (const u32*)sYardGfx,
	[PSPRITE_EVIR - 0x10] = (const u32*)sEvirGfx,
	[PSPRITE_BULL - 0x10] = (const u32*)sBullGfx,
	[PSPRITE_MEMU - 0x10] = (const u32*)sMemuGfx,
	[PSPRITE_GERUBOSS - 0x10] = (const u32*)sGerubossGfx,
	[PSPRITE_CHOOT - 0x10] = (const u32*)sChootGfx,
	[PSPRITE_ZEBESIAN_GROUND - 0x10] = (const u32*)sZebesianGroundGfx,
	[PSPRITE_BLUE_X - 0x10] = (const u32*)sBlueXGfx,
	[PSPRITE_MISSILE_HATCH - 0x10] = (const u32*)sMissileHatchGfx,
	[PSPRITE_QUARANTINE_BAY_HORNOAD - 0x10] = (const u32*)sHornoadGfx,
	[PSPRITE_BOX_DEBRIS - 0x10] = (const u32*)sBoxGfx,
	[PSPRITE_GERON_SUPER_MISSILE_1 - 0x10] = (const u32*)sSuperMissileGeronGfx,
	[PSPRITE_GERON_SUPER_MISSILE_2 - 0x10] = (const u32*)sSuperMissileGeronGfx,
	[PSPRITE_GERON_SUPER_MISSILE_3 - 0x10] = (const u32*)sSuperMissileGeronGfx,
	[PSPRITE_GERON_SUPER_MISSILE_4 - 0x10] = (const u32*)sSuperMissileGeronGfx,
	[PSPRITE_GERON_SUPER_MISSILE_5 - 0x10] = (const u32*)sSuperMissileGeronGfx,
	[PSPRITE_GERON_SUPER_MISSILE_6 - 0x10] = (const u32*)sSuperMissileGeronGfx,
	[PSPRITE_GERON_SUPER_MISSILE_7 - 0x10] = (const u32*)sSuperMissileGeronGfx,
	[PSPRITE_GERON_SUPER_MISSILE_8 - 0x10] = (const u32*)sSuperMissileGeronGfx,
	[PSPRITE_GERON_POWER_BOMB_1 - 0x10] = (const u32*)sPowerBombGeronGfx,
	[PSPRITE_GERON_POWER_BOMB_2 - 0x10] = (const u32*)sPowerBombGeronGfx,
	[PSPRITE_GERON_POWER_BOMB_3 - 0x10] = (const u32*)sPowerBombGeronGfx,
	[PSPRITE_GERON_POWER_BOMB_4 - 0x10] = (const u32*)sPowerBombGeronGfx,
	[PSPRITE_GERON_POWER_BOMB_5 - 0x10] = (const u32*)sPowerBombGeronGfx,
	[PSPRITE_GERON_POWER_BOMB_6 - 0x10] = (const u32*)sPowerBombGeronGfx,
	[PSPRITE_GERON_POWER_BOMB_7 - 0x10] = (const u32*)sPowerBombGeronGfx,
	[PSPRITE_GERON_POWER_BOMB_8 - 0x10] = (const u32*)sPowerBombGeronGfx,
	[PSPRITE_RIPPER - 0x10] = (const u32*)sRipperGfx,
	[PSPRITE_ZORO_COCOON - 0x10] = (const u32*)sZoroCocoonGfx,
	[PSPRITE_ZORO_HUSK - 0x10] = (const u32*)sZoroHuskGfx,
	[PSPRITE_GOLD_SCISER - 0x10] = (const u32*)sGoldSciserGfx,
	[PSPRITE_SA_X_TRO_1 - 0x10] = (const u32*)sSaXWeaponsGfx,
	[PSPRITE_SA_X_NOC - 0x10] = (const u32*)sSaXWeaponsGfx,
	[PSPRITE_PRE_DESTROYED_DATA_PAD - 0x10] = (const u32*)sDataPadGfx,
	[PSPRITE_GADORA_ARACHNUS - 0x10] = (const u32*)sGadoraGfx,
	[PSPRITE_GADORA_CHARGE_BEAM - 0x10] = (const u32*)sGadoraGfx,
	[PSPRITE_GADORA_ZAZABI - 0x10] = (const u32*)sGadoraGfx,
	[PSPRITE_GADORA_SERRIS - 0x10] = (const u32*)sGadoraGfx,
	[PSPRITE_GADORA_VARIA_CORE - 0x10] = (const u32*)sGadoraGfx,
	[PSPRITE_GADORA_WIDE_BEAM - 0x10] = (const u32*)sGadoraGfx,
	[PSPRITE_GADORA_NIGHTMARE - 0x10] = (const u32*)sGadoraGfx,
	[PSPRITE_GADORA_RIDLEY - 0x10] = (const u32*)sGadoraGfx,
	[PSPRITE_GADORA_NETTORI - 0x10] = (const u32*)sGadoraGfx,
	[PSPRITE_GADORA_YAKUZA - 0x10] = (const u32*)sGadoraGfx,
	[PSPRITE_GADORA_1 - 0x10] = (const u32*)sGadoraGfx,
	[PSPRITE_GADORA_2 - 0x10] = (const u32*)sGadoraGfx,
	[PSPRITE_GADORA_3 - 0x10] = (const u32*)sGadoraGfx,
	[PSPRITE_GADORA_4 - 0x10] = (const u32*)sGadoraGfx,
	[PSPRITE_GADORA_5 - 0x10] = (const u32*)sGadoraGfx,
	[PSPRITE_GADORA_6 - 0x10] = (const u32*)sGadoraGfx,
	[PSPRITE_SHAKE_TRIGGER - 0x10] = (const u32*)((const u8*)sBlob_2e6382_2e6ba4 + 0x2),
	[PSPRITE_SA_X_ARC - 0x10] = (const u32*)sSaXWeaponsGfx,
	[PSPRITE_ELEVATOR_PAD - 0x10] = sElevatorPadGfx,
	[PSPRITE_GOLD_ZEBESIAN - 0x10] = (const u32*)sGoldZebesianGfx,
	[PSPRITE_RED_ZEELA - 0x10] = (const u32*)sRedZeelaGfx,
	[PSPRITE_OWTCH - 0x10] = (const u32*)sOwtchGfx,
	[PSPRITE_GEEGA - 0x10] = (const u32*)sGeegaGfx,
	[PSPRITE_SERRIS - 0x10] = sSerrisGfx,
	[PSPRITE_PILLAR - 0x10] = (const u32*)sPillarGfx,
	[PSPRITE_GENESIS - 0x10] = (const u32*)sGenesisGfx,
	[PSPRITE_PUYO - 0x10] = (const u32*)sPuyoGfx,
	[PSPRITE_BUBBLES_1 - 0x10] = (const u32*)((const u8*)sBlob_2e6382_2e6ba4 + 0x2),
	[PSPRITE_BUBBLES_2 - 0x10] = (const u32*)((const u8*)sBlob_2e6382_2e6ba4 + 0x2),
	[PSPRITE_WATER_DROP - 0x10] = (const u32*)((const u8*)sBlob_2e6382_2e6ba4 + 0x2),
	[PSPRITE_MIMIC_ENERGY_TANK - 0x10] = (const u32*)sMimicEnergyTankGfx,
	[PSPRITE_MIMIC_MISSILE_TANK - 0x10] = (const u32*)sMimicMissileTankGfx,
	[PSPRITE_CORE_X_ABILITY_BEFORE_VARIA_CORE - 0x10] = (const u32*)sCoreXDownloadingVariaGfx,
	[PSPRITE_BIG_FLASHING_NUMBER - 0x10] = sBigFlashingNumberGfx,
	[PSPRITE_FLASHING_NUMBER - 0x10] = sFlashingNumberGfx,
	[PSPRITE_DESTROYED_DATA_PAD - 0x10] = (const u32*)sDestroyedDataPadGfx,
	[PSPRITE_ZEBESIAN_AQUA - 0x10] = (const u32*)sZebesianAquaGfx,
	[PSPRITE_ZEBESIAN_PRE_AQUA - 0x10] = (const u32*)sZebesianGroundGfx,
	[PSPRITE_SKULTERA_SMALL_2 - 0x10] = (const u32*)sSkulteraGfx,
	[PSPRITE_ETECOON - 0x10] = (const u32*)sAnimalsGfx,
	[PSPRITE_TIRE_SWING - 0x10] = (const u32*)sAnimalsGfx,
	[PSPRITE_DACHORA - 0x10] = (const u32*)sAnimalsGfx,
	[PSPRITE_X_PARASITE_AQUA_ZEBESIAN - 0x10] = (const u32*)((const u8*)sBlob_2e6382_2e6ba4 + 0x2),
	[PSPRITE_METROID - 0x10] = (const u32*)sMetroidGfx,
	[PSPRITE_LAB_DEBRIS - 0x10] = (const u32*)sLabDebrisGfx,
	[PSPRITE_SA_X_LAB - 0x10] = (const u32*)sSaXLabExplosionsGfx,
	[PSPRITE_POWAMP - 0x10] = (const u32*)sPowampGfx,
	[PSPRITE_ZOZORO - 0x10] = (const u32*)sZozoroGfx,
	[PSPRITE_CONTINUAL_X_SPAWNER - 0x10] = (const u32*)((const u8*)sBlob_2e6382_2e6ba4 + 0x2),
	[PSPRITE_SA_X_BOSS - 0x10] = (const u32*)sSaXWeaponsGfx,
	[PSPRITE_SA_X_MONSTER - 0x10] = (const u32*)sSaXMonsterGfx,
	[PSPRITE_ICE_BEAM_CORE_X - 0x10] = (const u32*)sIceBeamCoreXGfx,
	[PSPRITE_OMEGA_METROID - 0x10] = (const u32*)sOmegaMetroidGfx,
	[PSPRITE_GUNSHIP_END - 0x10] = (const u32*)(((const u8*)((const u8*)sBlob_39aa34_39eb38 + 0x324))),
	[PSPRITE_ELECTRIC_WATER_DAMAGE_BOX_2 - 0x10] = (const u32*)(((const u8*)sBlob_39ec90_39f4b0)),
	[PSPRITE_FROZEN_RIDLEY - 0x10] = (const u32*)sFrozenRidleyGfx,
	[PSPRITE_GOLD_SCISER_DOOR_LOCK - 0x10] = (const u32*)((const u8*)sBlob_2e6382_2e6ba4 + 0x2),
	[PSPRITE_GOLD_ZEBESIAN_DOOR_LOCK - 0x10] = (const u32*)((const u8*)sBlob_2e6382_2e6ba4 + 0x2),
	[PSPRITE_SA_X_OMEGA_CUTSCENE - 0x10] = (const u32*)sSaXWeaponsGfx,
	[PSPRITE_METROID_HUSK - 0x10] = (const u32*)sMetroidHuskGfx,
	[PSPRITE_RIDLEY - 0x10] = (const u32*)sRidleyGfx,
	[PSPRITE_PRE_SPAWN - 0x10] = (const u32*)sRidleyPreSpawnGfx,
	[PSPRITE_SA_X_TRO_2 - 0x10] = (const u32*)sSaXWeaponsGfx,
	[PSPRITE_NIGHTMARE - 0x10] = (const u32*)sNightmareGfx
};

const u16* const sSpritesPalettePointers[PSPRITE_END - 0x10] = {
    [PSPRITE_UNUSED_16 - 0x10] = (const u16*)((const u8*)sBlob_2e6382_2e6ba4 + 0x802),
	[PSPRITE_SA_X_ELEVATOR - 0x10] = (const u16*)sSaXPalette_Default,
	[PSPRITE_HORNOAD - 0x10] = (const u16*)sHornoadPal,
	[PSPRITE_HALZYN - 0x10] = (const u16*)sHalzynPal,
	[PSPRITE_ZEBESIAN_WALL - 0x10] = (const u16*)sZebesianWallPal,
	[PSPRITE_HORNOAD_SPAWNER - 0x10] = (const u16*)sHornoadPal,
	[PSPRITE_GATE - 0x10] = (const u16*)sGatePal,
	[PSPRITE_MOVABLE_PLATFORM_1 - 0x10] = (const u16*)sMovablePlatformPal,
	[PSPRITE_MOTO - 0x10] = (const u16*)sMotoPal,
	[PSPRITE_NAVIGATION_PAD - 0x10] = (const u16*)sNavigationPadPal,
	[PSPRITE_GUNSHIP - 0x10] = (const u16*)sGunshipPal,
	[PSPRITE_YAMEBA - 0x10] = (const u16*)sYamebaPal,
	[PSPRITE_SECURITY_PAD - 0x10] = (const u16*)sSecurityPadPal,
	[PSPRITE_AREA_BANNER - 0x10] = (const u16*)sAreaBannerPal,
	[PSPRITE_DATA_PAD - 0x10] = (const u16*)sDataPadPal,
	[PSPRITE_SAVE_PAD - 0x10] = (const u16*)sSavePadPal,
	[PSPRITE_PRE_BOX_CEILING_DEBRIS - 0x10] = (const u16*)((const u8*)sBlob_2e6382_2e6ba4 + 0x802),
	[PSPRITE_MESSAGE_BANNER - 0x10] = (const u16*)sMessageBannerPal,
	[PSPRITE_KAGO - 0x10] = (const u16*)sKagoPal,
	[PSPRITE_ELECTRIC_WATER_DAMAGE - 0x10] = (const u16*)sElectricWaterPal,
	[PSPRITE_ELECTRIC_WATER - 0x10] = (const u16*)sElectricWaterPal,
	[PSPRITE_WIRE - 0x10] = (const u16*)sElectricWaterPal,
	[PSPRITE_SAMUS_EATER_BUD - 0x10] = (const u16*)sNettoriPal,
	[PSPRITE_SAMUS_EATER - 0x10] = (const u16*)sNettoriPal,
	[PSPRITE_ENERGY_RECHARGE_PAD - 0x10] = (const u16*)sRechargePadPal,
	[PSPRITE_AMMO_RECHARGE_PAD - 0x10] = (const u16*)sRechargePadPal,
	[PSPRITE_ENERGY_AMMO_RECHARGE_PAD - 0x10] = (const u16*)sRechargePadPal,
	[PSPRITE_ATMOSPHERIC_STABILIZER_PARASITE - 0x10] = (const u16*)sAtmosphericStabilizerPal,
	[PSPRITE_ATMOSPHERIC_STABILIZER_1 - 0x10] = (const u16*)sAtmosphericStabilizerPal,
	[PSPRITE_ATMOSPHERIC_STABILIZER_2 - 0x10] = (const u16*)sAtmosphericStabilizerPal,
	[PSPRITE_ATMOSPHERIC_STABILIZER_3 - 0x10] = (const u16*)sAtmosphericStabilizerPal,
	[PSPRITE_ATMOSPHERIC_STABILIZER_4 - 0x10] = (const u16*)sAtmosphericStabilizerPal,
	[PSPRITE_ATMOSPHERIC_STABILIZER_5 - 0x10] = (const u16*)sAtmosphericStabilizerPal,
	[PSPRITE_ZEELA - 0x10] = (const u16*)sZeelaPal,
	[PSPRITE_X_PARASITE_CORE_X_OR_PARASITE - 0x10] = (const u16*)((const u8*)sBlob_2e6382_2e6ba4 + 0x802),
	[PSPRITE_SKREE - 0x10] = (const u16*)sSkreePal,
	[PSPRITE_X_PARASITE_IN_ROOM - 0x10] = (const u16*)((const u8*)sBlob_2e6382_2e6ba4 + 0x802),
	[PSPRITE_TOXIC_GAS - 0x10] = (const u16*)sToxicGasPal,
	[PSPRITE_X_PARASITE_IN_ROOM_PROXIMITY - 0x10] = (const u16*)((const u8*)sBlob_2e6382_2e6ba4 + 0x802),
	[PSPRITE_ZOMBIE - 0x10] = (const u16*)sZombiePal,
	[PSPRITE_X_PARASITE - 0x10] = (const u16*)((const u8*)sBlob_2e6382_2e6ba4 + 0x802),
	[PSPRITE_GEEMER - 0x10] = (const u16*)sGeemerPal,
	[PSPRITE_ARACHNUS - 0x10] = (const u16*)sArachnusPal,
	[PSPRITE_WAVER - 0x10] = (const u16*)sWaverPal,
	[PSPRITE_SCISER - 0x10] = (const u16*)sSciserPal,
	[PSPRITE_SIDEHOPPER - 0x10] = (const u16*)sSidehopperPal,
	[PSPRITE_DESSGEEGA - 0x10] = (const u16*)sDessgeegaPal,
	[PSPRITE_MORPH_BALL_ABILITY - 0x10] = (const u16*)sMorphBallCoreXPal,
	[PSPRITE_X_PARASITE_CORE_X_FORMATION - 0x10] = (const u16*)((const u8*)sBlob_2e6382_2e6ba4 + 0x802),
	[PSPRITE_GERON_MISSILE_1 - 0x10] = (const u16*)sMissileGeronPal,
	[PSPRITE_GERON_MISSILE_2 - 0x10] = (const u16*)sMissileGeronPal,
	[PSPRITE_GERON_MISSILE_3 - 0x10] = (const u16*)sMissileGeronPal,
	[PSPRITE_HIGH_JUMP_ABILITY - 0x10] = (const u16*)sHiJumpCoreXPal,
	[PSPRITE_SPEEDBOOSTER_ABILITY - 0x10] = (const u16*)sSpeedBoosterCoreXPal,
	[PSPRITE_VARIA_SUIT_ABILITY - 0x10] = (const u16*)sMegaXPal,
	[PSPRITE_SPACE_JUMP_ABILITY - 0x10] = (const u16*)sSpaceJumpCoreXPal,
	[PSPRITE_GRAVITY_SUIT_ABILITY - 0x10] = (const u16*)sGravityCoreXPal,
	[PSPRITE_SCREW_ATTACK_ABILITY - 0x10] = (const u16*)sScrewAttackCoreXPal,
	[PSPRITE_MOVABLE_PLATFORM_2 - 0x10] = (const u16*)sMovablePlatformPal,
	[PSPRITE_ZAZABI - 0x10] = (const u16*)sZazabiPal,
	[PSPRITE_OMEGA_METROID_HUSK - 0x10] = (const u16*)sOmegaMetroidHuskPal,
	[PSPRITE_ICE_BEAM_ABILITY - 0x10] = (const u16*)sIceBeamAbilityOmegaPal,
	[PSPRITE_MOVABLE_PLATFORM_3 - 0x10] = (const u16*)sMovablePlatformPal,
	[PSPRITE_MOVABLE_PLATFORM_4 - 0x10] = (const u16*)sMovablePlatformPal,
	[PSPRITE_MOVABLE_PLATFORM_5 - 0x10] = (const u16*)sMovablePlatformPal,
	[PSPRITE_YAKUZA - 0x10] = (const u16*)sYakuzaPal,
	[PSPRITE_CHOZO_STATUE - 0x10] = (const u16*)sChozoStatuePal,
	[PSPRITE_SCIENTIST - 0x10] = (const u16*)sScientistPal,
	[PSPRITE_NETTORI - 0x10] = (const u16*)sNettoriPal,
	[PSPRITE_BOX_2 - 0x10] = (const u16*)sBox2Pal,
	[PSPRITE_CHARGE_BEAM_CORE_X - 0x10] = (const u16*)sChargeBeamCoreXPal,
	[PSPRITE_WIDE_BEAM_CORE_X - 0x10] = (const u16*)sWideBeamCoreXPal,
	[PSPRITE_PLASMA_BEAM_CORE_X - 0x10] = (const u16*)sPlasmaBeamCoreXPal,
	[PSPRITE_WAVE_BEAM_CORE_X - 0x10] = (const u16*)sWaveBeamCoreXPal,
	[PSPRITE_ZORO - 0x10] = (const u16*)sZoroPal,
	[PSPRITE_KIHUNTER_FLYING - 0x10] = (const u16*)sKihunterPal,
	[PSPRITE_KIHUNTER_GROUND - 0x10] = (const u16*)sKihunterPal,
	[PSPRITE_KIHUNTER_HIVE - 0x10] = (const u16*)sKihunterPal,
	[PSPRITE_REO - 0x10] = (const u16*)sReoPal,
	[PSPRITE_LAVA_PLUME - 0x10] = (const u16*)sLavaPlumePal,
	[PSPRITE_NAHIME - 0x10] = (const u16*)sFuneNamihePal,
	[PSPRITE_FUNE - 0x10] = (const u16*)sFuneNamihePal,
	[PSPRITE_BOX - 0x10] = (const u16*)sBoxPal,
	[PSPRITE_BLUE_ZORO - 0x10] = (const u16*)sBlueZoroPal,
	[PSPRITE_GERUTA - 0x10] = (const u16*)sGerutaPal,
	[PSPRITE_PUMP_CONTROL_PAD - 0x10] = (const u16*)sControlPadPal,
	[PSPRITE_BOILER_CONTROL_PAD - 0x10] = (const u16*)sControlPadPal,
	[PSPRITE_AUXILARY_POWER_PAD - 0x10] = (const u16*)sControlPadPal,
	[PSPRITE_HABITAION_PAD - 0x10] = (const u16*)sHabitationPadPal,
	[PSPRITE_OPERATIONS_ROOM_PAD - 0x10] = (const u16*)sOperationsRoomPadPal,
	[PSPRITE_SKULTERA_LARGE - 0x10] = (const u16*)sSkulteraPal,
	[PSPRITE_SKULTERA_SMALL_1 - 0x10] = (const u16*)sSkulteraPal,
	[PSPRITE_SOVA - 0x10] = (const u16*)sSovaPal,
	[PSPRITE_YARD - 0x10] = (const u16*)sYardPal,
	[PSPRITE_EVIR - 0x10] = (const u16*)sEvirPal,
	[PSPRITE_BULL - 0x10] = (const u16*)sBullPal,
	[PSPRITE_MEMU - 0x10] = (const u16*)sMemuPal,
	[PSPRITE_GERUBOSS - 0x10] = (const u16*)sGerubossPal,
	[PSPRITE_CHOOT - 0x10] = (const u16*)sChootPal,
	[PSPRITE_ZEBESIAN_GROUND - 0x10] = (const u16*)sZebesianGroundPal,
	[PSPRITE_BLUE_X - 0x10] = (const u16*)sBlueXPal,
	[PSPRITE_MISSILE_HATCH - 0x10] = (const u16*)sMissileHatchPal,
	[PSPRITE_QUARANTINE_BAY_HORNOAD - 0x10] = (const u16*)sHornoadPal,
	[PSPRITE_BOX_DEBRIS - 0x10] = (const u16*)sBoxPal,
	[PSPRITE_GERON_SUPER_MISSILE_1 - 0x10] = (const u16*)sSuperMissileGeronPal,
	[PSPRITE_GERON_SUPER_MISSILE_2 - 0x10] = (const u16*)sSuperMissileGeronPal,
	[PSPRITE_GERON_SUPER_MISSILE_3 - 0x10] = (const u16*)sSuperMissileGeronPal,
	[PSPRITE_GERON_SUPER_MISSILE_4 - 0x10] = (const u16*)sSuperMissileGeronPal,
	[PSPRITE_GERON_SUPER_MISSILE_5 - 0x10] = (const u16*)sSuperMissileGeronPal,
	[PSPRITE_GERON_SUPER_MISSILE_6 - 0x10] = (const u16*)sSuperMissileGeronPal,
	[PSPRITE_GERON_SUPER_MISSILE_7 - 0x10] = (const u16*)sSuperMissileGeronPal,
	[PSPRITE_GERON_SUPER_MISSILE_8 - 0x10] = (const u16*)sSuperMissileGeronPal,
	[PSPRITE_GERON_POWER_BOMB_1 - 0x10] = (const u16*)sPowerBombGeronPal,
	[PSPRITE_GERON_POWER_BOMB_2 - 0x10] = (const u16*)sPowerBombGeronPal,
	[PSPRITE_GERON_POWER_BOMB_3 - 0x10] = (const u16*)sPowerBombGeronPal,
	[PSPRITE_GERON_POWER_BOMB_4 - 0x10] = (const u16*)sPowerBombGeronPal,
	[PSPRITE_GERON_POWER_BOMB_5 - 0x10] = (const u16*)sPowerBombGeronPal,
	[PSPRITE_GERON_POWER_BOMB_6 - 0x10] = (const u16*)sPowerBombGeronPal,
	[PSPRITE_GERON_POWER_BOMB_7 - 0x10] = (const u16*)sPowerBombGeronPal,
	[PSPRITE_GERON_POWER_BOMB_8 - 0x10] = (const u16*)sPowerBombGeronPal,
	[PSPRITE_RIPPER - 0x10] = (const u16*)sRipperPal,
	[PSPRITE_ZORO_COCOON - 0x10] = (const u16*)sZoroCocoonPal,
	[PSPRITE_ZORO_HUSK - 0x10] = (const u16*)sZoroHuskPal,
	[PSPRITE_GOLD_SCISER - 0x10] = (const u16*)sGoldSciserPal,
	[PSPRITE_SA_X_TRO_1 - 0x10] = (const u16*)sSaXPalette_Default,
	[PSPRITE_SA_X_NOC - 0x10] = (const u16*)sSaXPalette_Default,
	[PSPRITE_PRE_DESTROYED_DATA_PAD - 0x10] = (const u16*)sDataPadPal,
	[PSPRITE_GADORA_ARACHNUS - 0x10] = (const u16*)sGadoraPal,
	[PSPRITE_GADORA_CHARGE_BEAM - 0x10] = (const u16*)sGadoraPal,
	[PSPRITE_GADORA_ZAZABI - 0x10] = (const u16*)sGadoraPal,
	[PSPRITE_GADORA_SERRIS - 0x10] = (const u16*)sGadoraPal,
	[PSPRITE_GADORA_VARIA_CORE - 0x10] = (const u16*)sGadoraPal,
	[PSPRITE_GADORA_WIDE_BEAM - 0x10] = (const u16*)sGadoraPal,
	[PSPRITE_GADORA_NIGHTMARE - 0x10] = (const u16*)sGadoraPal,
	[PSPRITE_GADORA_RIDLEY - 0x10] = (const u16*)sGadoraPal,
	[PSPRITE_GADORA_NETTORI - 0x10] = (const u16*)sGadoraPal,
	[PSPRITE_GADORA_YAKUZA - 0x10] = (const u16*)sGadoraPal,
	[PSPRITE_GADORA_1 - 0x10] = (const u16*)sGadoraPal,
	[PSPRITE_GADORA_2 - 0x10] = (const u16*)sGadoraPal,
	[PSPRITE_GADORA_3 - 0x10] = (const u16*)sGadoraPal,
	[PSPRITE_GADORA_4 - 0x10] = (const u16*)sGadoraPal,
	[PSPRITE_GADORA_5 - 0x10] = (const u16*)sGadoraPal,
	[PSPRITE_GADORA_6 - 0x10] = (const u16*)sGadoraPal,
	[PSPRITE_SHAKE_TRIGGER - 0x10] = (const u16*)((const u8*)sBlob_2e6382_2e6ba4 + 0x802),
	[PSPRITE_SA_X_ARC - 0x10] = (const u16*)sSaXPalette_Default,
	[PSPRITE_ELEVATOR_PAD - 0x10] = sElevatorPadPal,
	[PSPRITE_GOLD_ZEBESIAN - 0x10] = (const u16*)sGoldZebesianPal,
	[PSPRITE_RED_ZEELA - 0x10] = (const u16*)sRedZeelaPal,
	[PSPRITE_OWTCH - 0x10] = (const u16*)sOwtchPal,
	[PSPRITE_GEEGA - 0x10] = (const u16*)sGeegaPal,
	[PSPRITE_SERRIS - 0x10] = sSerrisPal,
	[PSPRITE_PILLAR - 0x10] = (const u16*)sPillarPal,
	[PSPRITE_GENESIS - 0x10] = (const u16*)sGenesisPal,
	[PSPRITE_PUYO - 0x10] = (const u16*)sPuyoPal,
	[PSPRITE_BUBBLES_1 - 0x10] = (const u16*)((const u8*)sBlob_2e6382_2e6ba4 + 0x802),
	[PSPRITE_BUBBLES_2 - 0x10] = (const u16*)((const u8*)sBlob_2e6382_2e6ba4 + 0x802),
	[PSPRITE_WATER_DROP - 0x10] = (const u16*)((const u8*)sBlob_2e6382_2e6ba4 + 0x802),
	[PSPRITE_MIMIC_ENERGY_TANK - 0x10] = (const u16*)sMimicEnergyTankPal,
	[PSPRITE_MIMIC_MISSILE_TANK - 0x10] = (const u16*)sMimicMissileTankPal,
	[PSPRITE_CORE_X_ABILITY_BEFORE_VARIA_CORE - 0x10] = (const u16*)sCoreXDownloadingVariaPal,
	[PSPRITE_BIG_FLASHING_NUMBER - 0x10] = sBigFlashingNumberPal,
	[PSPRITE_FLASHING_NUMBER - 0x10] = sFlashingNumberPal,
	[PSPRITE_DESTROYED_DATA_PAD - 0x10] = (const u16*)sDestroyedDataPadPal,
	[PSPRITE_ZEBESIAN_AQUA - 0x10] = (const u16*)sZebesianAquaPal,
	[PSPRITE_ZEBESIAN_PRE_AQUA - 0x10] = (const u16*)sZebesianGroundPal,
	[PSPRITE_SKULTERA_SMALL_2 - 0x10] = (const u16*)sSkulteraPal,
	[PSPRITE_ETECOON - 0x10] = (const u16*)sAnimalsPal,
	[PSPRITE_TIRE_SWING - 0x10] = (const u16*)sAnimalsPal,
	[PSPRITE_DACHORA - 0x10] = (const u16*)sAnimalsPal,
	[PSPRITE_X_PARASITE_AQUA_ZEBESIAN - 0x10] = (const u16*)((const u8*)sBlob_2e6382_2e6ba4 + 0x802),
	[PSPRITE_METROID - 0x10] = (const u16*)sMetroidPal,
	[PSPRITE_LAB_DEBRIS - 0x10] = (const u16*)sLabDebrisPal,
	[PSPRITE_SA_X_LAB - 0x10] = (const u16*)sSaXLabExplosionsPal,
	[PSPRITE_POWAMP - 0x10] = (const u16*)sPowampPal,
	[PSPRITE_ZOZORO - 0x10] = (const u16*)sZozoroPal,
	[PSPRITE_CONTINUAL_X_SPAWNER - 0x10] = (const u16*)((const u8*)sBlob_2e6382_2e6ba4 + 0x802),
	[PSPRITE_SA_X_BOSS - 0x10] = (const u16*)sSaXPalette_Default,
	[PSPRITE_SA_X_MONSTER - 0x10] = (const u16*)sSaXMonsterPal,
	[PSPRITE_ICE_BEAM_CORE_X - 0x10] = (const u16*)sIceBeamCoreXPal,
	[PSPRITE_OMEGA_METROID - 0x10] = (const u16*)sOmegaMetroidPal,
	[PSPRITE_GUNSHIP_END - 0x10] = (const u16*)(((const u8*)((const u8*)sBlob_39aa34_39eb38 + 0x3b24))),
	[PSPRITE_ELECTRIC_WATER_DAMAGE_BOX_2 - 0x10] = (const u16*)(((const u8*)((const u8*)sBlob_39ec90_39f4b0 + 0x800))),
	[PSPRITE_FROZEN_RIDLEY - 0x10] = (const u16*)sFrozenRidleyPal,
	[PSPRITE_GOLD_SCISER_DOOR_LOCK - 0x10] = (const u16*)((const u8*)sBlob_2e6382_2e6ba4 + 0x802),
	[PSPRITE_GOLD_ZEBESIAN_DOOR_LOCK - 0x10] = (const u16*)((const u8*)sBlob_2e6382_2e6ba4 + 0x802),
	[PSPRITE_SA_X_OMEGA_CUTSCENE - 0x10] = (const u16*)sSaXPalette_Default,
	[PSPRITE_METROID_HUSK - 0x10] = (const u16*)sMetroidHuskPal,
	[PSPRITE_RIDLEY - 0x10] = (const u16*)sRidleyPal,
	[PSPRITE_PRE_SPAWN - 0x10] = (const u16*)sRidleyPreSpawnPal,
	[PSPRITE_SA_X_TRO_2 - 0x10] = (const u16*)sSaXPalette_Default,
	[PSPRITE_NIGHTMARE - 0x10] = (const u16*)sNightmarePal
};

const Func_T sSecondarySpritesAiPointers[SSPRITE_END] = {
    [SSPRITE_SA_X_ICE_BEAM] = (Func_T)SaXBeam,
	[SSPRITE_SA_X_SUPER_MISSILE] = (Func_T)SaXMissile,
	[SSPRITE_HORNOAD_SPIT] = (Func_T)HornoadSpit,
	[SSPRITE_HALZYN_WING] = (Func_T)HalzynWing,
	[SSPRITE_SCISER_PROJECTILE] = (Func_T)SciserProjectile,
	[SSPRITE_ZEBESIAN_BEAM] = (Func_T)ZebesianBeam,
	[SSPRITE_GUNSHIP_PART] = (Func_T)GunshipPart,
	[SSPRITE_NAVIGATION_CONSOLE] = (Func_T)NavConsole,
	[SSPRITE_NAVIGATION_CONSOLE_SCREEN] = (Func_T)NavConsoleScreen,
	[SSPRITE_NAVIGATION_SCREEN] = (Func_T)NavScreen,
	[SSPRITE_SAVE_PLATFORM] = (Func_T)SavePlatform,
	[SSPRITE_MOTO_FRONT] = (Func_T)MotoFront,
	[SSPRITE_GEEMER_FLASHING_LIGHT] = (Func_T)GeemerFlashingLight,
	[SSPRITE_GUNSHIP_BEAM] = (Func_T)GunshipBeam,
	[SSPRITE_E] = (Func_T)KagoInsect,
	[SSPRITE_GATE_SWITCH] = (Func_T)GateSwitch,
	[SSPRITE_KIHUNTER_WINGS] = (Func_T)KihunterWings,
	[SSPRITE_KIHUNTER_SPIT] = (Func_T)KihunterSpit,
	[SSPRITE_12] = (Func_T)SecurityPadScreen,
	[SSPRITE_ATMOSPHERIC_STABILIZER_COVER_DOWN] = (Func_T)AtmosphericStabilizerCover,
	[SSPRITE_14] = (Func_T)BoxMissile,
	[SSPRITE_ARACHNUS_SHELL] = (Func_T)ArachnusShell,
	[SSPRITE_ARACHNUS_BEAM] = (Func_T)ArachnusSlash,
	[SSPRITE_ARACHNUS_HEAD] = (Func_T)ArachnusHead,
	[SSPRITE_ARACHNUS_LEFT_ARM] = (Func_T)ArachnusArm1,
	[SSPRITE_ARACHNUS_RIGHT_ARM] = (Func_T)ArachnusArm2,
	[SSPRITE_ARACHNUS_FIRE_BALL] = (Func_T)ArachnusFire,
	[SSPRITE_CORE_X_SHELL_MORPH_BALL] = (Func_T)CoreXShell,
	[SSPRITE_ABILITY_AURA] = (Func_T)AbilityAura,
	[SSPRITE_GERON_MISSILE_STEM] = (Func_T)MissileGeronStem,
	[SSPRITE_DATA_PAD_CENTER] = (Func_T)DataPadCenter,
	[SSPRITE_DATA_PAD_SIDES] = (Func_T)DataPadSides,
	[SSPRITE_ARACHNUS_BEAM_TRAIL] = (Func_T)ArachnusSlashTrail,
	[SSPRITE_RECHARGE_PAD_MONITOR] = (Func_T)RechargePadMonitor,
	[SSPRITE_RECHARGE_PAD_SCREEN] = (Func_T)RechargePadScreen,
	[SSPRITE_ATMOSPHERIC_STABILIZER_COVER_RIGHT] = (Func_T)AtmosphericStabilizerCover,
	[SSPRITE_ATMOSPHERIC_STABILIZER_COVER_LEFT] = (Func_T)AtmosphericStabilizerCover,
	[SSPRITE_SECURITY_PAD_MONITOR] = (Func_T)SecurityPadMonitor,
	[SSPRITE_SAVE_YES_NO_CURSOR] = (Func_T)SaveYesNoCursor,
	[SSPRITE_FAKE_CHOZO_BALL] = (Func_T)FakeChozoBall,
	[SSPRITE_CHARGE_BEAM_CORE_X_SHELL] = (Func_T)BeamCoreXShell,
	[SSPRITE_CHARGE_BEAM_CORE_X_EYE] = (Func_T)BeamCoreXEye,
	[SSPRITE_TOXIC_GAS_EXPLOSION] = (Func_T)ToxicGasExplosion,
	[SSPRITE_KIHUNTER_BUG] = (Func_T)KihunterBug,
	[SSPRITE_REO_WING] = (Func_T)ReoWings,
	[SSPRITE_LAVA_PLUME_WARNING] = (Func_T)LavaPlumeWarning,
	[SSPRITE_NAMIHE_SPIT] = (Func_T)NamiheSpit,
	[SSPRITE_FUNE_SPIT] = (Func_T)FuneSpit,
	[SSPRITE_SAVE_PAD_HOLOGRAM] = (Func_T)SavePadHologram,
	[SSPRITE_BOX_PART] = (Func_T)BoxPart,
	[SSPRITE_DESSGEEGA_SPIKE] = (Func_T)DessgeegaSpike,
	[SSPRITE_33] = (Func_T)MiscPadConsole,
	[SSPRITE_OPERATIONS_ROOM_PAD_CONSOLE] = (Func_T)OperationsRoomPadConsole,
	[SSPRITE_OPERATIONS_ROOM_PAD_CONSOLE_SCREEN] = (Func_T)OperationsRoomPadConsoleScreen,
	[SSPRITE_OPERATIONS_ROOM_PAD_SCREEN] = (Func_T)OperationsRoomPadScreen,
	[SSPRITE_WAVER_DEBRIS] = (Func_T)WaverExplosion,
	[SSPRITE_ZEELA_PROJECTILE] = (Func_T)ZeelaProjectile,
	[SSPRITE_SOVA_FIRE] = (Func_T)SovaFire,
	[SSPRITE_YARD_PROJECTILE] = (Func_T)YardProjectile,
	[SSPRITE_EVIR_COLLISION] = (Func_T)EvirCollision,
	[SSPRITE_EVIR_PROJECTILE] = (Func_T)EvirProjectile,
	[SSPRITE_BULL_SMOKE] = (Func_T)BullSmoke,
	[SSPRITE_CHOOT_SPIT] = (Func_T)ChootSpit,
	[SSPRITE_ZEBESIAN_GROUND_BEAM] = (Func_T)ZebesianGroundBeam,
	[SSPRITE_BLUE_X_ABSORPTION] = (Func_T)BlueXAbsorbtion,
	[SSPRITE_41] = (Func_T)MissileHatchDebris,
	[SSPRITE_GERON_SUPER_MISSILE_STEM] = (Func_T)SuperMissileGeronStem,
	[SSPRITE_GERON_POWER_BOMB_STEM] = (Func_T)PowerBombGeronStem,
	[SSPRITE_SA_X_POWER_BOMB] = (Func_T)SaXPowerBomb,
	[SSPRITE_GADORA_ROOTS] = (Func_T)GadoraRoots,
	[SSPRITE_GADORA_BEAM] = (Func_T)GadoraBeam,
	[SSPRITE_GADORA_EYE] = (Func_T)GadoraEye,
	[SSPRITE_48] = (Func_T)Gadora_UnusedSprite,
	[SSPRITE_NIGHTMARE_FALLING_ARM] = (Func_T)NightmareFallingArm,
	[SSPRITE_MEGA_X_SHIELD] = (Func_T)MegaXShield,
	[SSPRITE_BOX_FALLING_DEBRIS] = (Func_T)BoxFallingDebris,
	[SSPRITE_NETTORI_PART] = (Func_T)NettoriPart,
	[SSPRITE_4D] = (Func_T)BeamCoreXGlowing,
	[SSPRITE_BEAM_CORE_X_CHARGE_BEAM] = (Func_T)CoreXChargeBeam,
	[SSPRITE_BEAM_CORE_X_WIDE_BEAM] = (Func_T)CoreXWideBeam,
	[SSPRITE_BEAM_CORE_X_PLASMA_BEAM] = (Func_T)CoreXPlasmaBeam,
	[SSPRITE_BEAM_CORE_X_WAVE_BEAM] = (Func_T)CoreXWaveIceBeam,
	[SSPRITE_SAMUS_EATER_SPORE] = (Func_T)SamusEaterSpore,
	[SSPRITE_NETTORI_PLASMA_BEAM] = (Func_T)NettoriPlasmaBeam,
	[SSPRITE_WIDE_BEAM_CORE_X_SHELL] = (Func_T)BeamCoreXShell,
	[SSPRITE_WIDE_BEAM_CORE_X_EYE] = (Func_T)BeamCoreXEye,
	[SSPRITE_PLASMA_BEAM_CORE_X_SHELL] = (Func_T)BeamCoreXShell,
	[SSPRITE_PLASMA_BEAM_CORE_X_EYE] = (Func_T)BeamCoreXEye,
	[SSPRITE_WAVE_BEAM_CORE_X_SHELL] = (Func_T)BeamCoreXShell,
	[SSPRITE_WAVE_BEAM_CORE_X_EYE] = (Func_T)BeamCoreXEye,
	[SSPRITE_ZAZABI_PART] = (Func_T)ZazabiPart,
	[SSPRITE_SERRIS_PART] = SerrisPart,
	[SSPRITE_CORE_X_STATIC_BEFORE_VARIA_CORE] = (Func_T)CoreXStaticBeforeVariaCore,
	[SSPRITE_CORE_X_SHELL_BEFORE_VARIA_CORE] = (Func_T)CoreXShellBeforeVariaCore,
	[SSPRITE_CORE_X_SHELL_HIGH_JUMP] = (Func_T)CoreXShell,
	[SSPRITE_CORE_X_SHELL_SPEEDBOOSTER] = (Func_T)CoreXShell,
	[SSPRITE_CORE_X_SHELL_VARIA] = (Func_T)CoreXShellVaria,
	[SSPRITE_CORE_X_SHELL_SPACE_JUMP] = (Func_T)CoreXShell,
	[SSPRITE_CORE_X_SHELL_GRAVITY] = (Func_T)CoreXShell,
	[SSPRITE_CORE_X_SHELL_SCREW_ATTACK] = (Func_T)CoreXShell,
	[SSPRITE_YAKUZA_PART] = (Func_T)YakuzaPart,
	[SSPRITE_GENESIS_SPIT] = (Func_T)GenesisSpit,
	[SSPRITE_ZEBESIAN_AQUA_PROJECTILE] = (Func_T)ZebesianAquaProjectile,
	[SSPRITE_HABITATION_GATE] = (Func_T)HabitationGate,
	[SSPRITE_HABITATION_GATE_LIGHT] = (Func_T)HabitationGateLight,
	[SSPRITE_BABY_DACHORA] = (Func_T)BabyDachora,
	[SSPRITE_SA_X_SHOOTING_AT_LAB_EXPLOSION] = (Func_T)LabExplosion,
	[SSPRITE_SA_X_MONSTER_PART] = (Func_T)SaXMonsterPart,
	[SSPRITE_BOX_2_PART] = (Func_T)Box2Part,
	[SSPRITE_BOX_2_MISSILE] = (Func_T)Box2Missile,
	[SSPRITE_BOX_2_BRAIN_TOP] = (Func_T)Box2BrainTop,
	[SSPRITE_BOX_2_BRAIN_BOTTOM] = (Func_T)Box2BrainBottom,
	[SSPRITE_OMEGA_METROID_PART] = (Func_T)OmegaMetroidPart,
	[SSPRITE_BOX_BOMB] = (Func_T)BoxBomb,
	[SSPRITE_BOX_FIRE] = (Func_T)BoxFire,
	[SSPRITE_FROZEN_RIDLEY_X] = (Func_T)FrozenRidleyX,
	[SSPRITE_BEAM_CORE_X_ICE_BEAM] = (Func_T)CoreXWaveIceBeam,
	[SSPRITE_ICE_BEAM_CORE_X_SHELL] = (Func_T)BeamCoreXShell,
	[SSPRITE_ICE_BEAM_CORE_X_EYE] = (Func_T)BeamCoreXEye,
	[SSPRITE_SERRIS_BLOCK] = (Func_T)SerrisBlock,
	[SSPRITE_MEGA_X] = (Func_T)MegaX,
	[SSPRITE_GUNSHIP_END_BEAM] = (Func_T)GunshipEndBeam,
	[SSPRITE_7A] = (Func_T)GunshipEndBottom,
	[SSPRITE_RIDLEY_PART] = (Func_T)RidleyPart,
	[SSPRITE_RIDLEY_TAIL_PART] = (Func_T)RidleyTailPart,
	[SSPRITE_RIDLEY_FIRE] = (Func_T)RidleyFire,
	[SSPRITE_YAKUZA_PROJECTILE] = (Func_T)YakuzaProjectile,
	[SSPRITE_YAKUZA_FALLING_LEG] = (Func_T)YakuzaFallingLeg,
	[SSPRITE_NIGHTMARE_PART] = (Func_T)NightmarePart,
	[SSPRITE_NIGHTMARE_BEAM] = (Func_T)NightmareBeam
};

const u8* const sSpritesetPointers[130] = {
    [0] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x2),
	[1] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0xa),
	[2] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0xe),
	[3] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x2c),
	[4] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x30),
	[5] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x48),
	[6] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x4c),
	[7] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x52),
	[8] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x5a),
	[9] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x60),
	[10] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x64),
	[11] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x76),
	[12] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x7e),
	[13] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x88),
	[14] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x90),
	[15] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0xa0),
	[16] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0xac),
	[17] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0xba),
	[18] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0xd2),
	[19] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0xe2),
	[20] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0xee),
	[21] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0xf2),
	[22] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0xf6),
	[23] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x102),
	[24] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x10e),
	[25] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x11e),
	[26] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x130),
	[27] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x134),
	[28] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x142),
	[29] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x14c),
	[30] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x15e),
	[31] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x16c),
	[32] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x170),
	[33] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x17c),
	[34] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x180),
	[35] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x18a),
	[36] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x1a4),
	[37] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x1ac),
	[38] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x1b2),
	[39] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x1c2),
	[40] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x1d0),
	[41] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x1de),
	[42] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x1e2),
	[43] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x1f0),
	[44] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x1f8),
	[45] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x1fe),
	[46] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x208),
	[47] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x20e),
	[48] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x218),
	[49] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x224),
	[50] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x22a),
	[51] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x23c),
	[52] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x246),
	[53] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x254),
	[54] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x264),
	[55] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x268),
	[56] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x278),
	[57] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x284),
	[58] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x28c),
	[59] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x290),
	[60] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x29a),
	[61] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x2aa),
	[62] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x2b4),
	[63] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x2c4),
	[64] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x2d0),
	[65] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x2e2),
	[66] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x2f2),
	[67] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x2fe),
	[68] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x30a),
	[69] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x318),
	[70] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x328),
	[71] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x32c),
	[72] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x336),
	[73] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x340),
	[74] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x346),
	[75] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x35c),
	[76] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x36e),
	[77] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x378),
	[78] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x380),
	[79] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x38a),
	[80] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x390),
	[81] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x398),
	[82] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x3a6),
	[83] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x3ae),
	[84] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x3ba),
	[85] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x3be),
	[86] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x3cc),
	[87] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x3d8),
	[88] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x3ec),
	[89] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x3f4),
	[90] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x3fc),
	[91] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x402),
	[92] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x406),
	[93] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x410),
	[94] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x41a),
	[95] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x428),
	[96] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x434),
	[97] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x442),
	[98] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x450),
	[99] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x454),
	[100] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x460),
	[101] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x464),
	[102] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x46c),
	[103] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x470),
	[104] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x480),
	[105] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x482),
	[106] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x484),
	[107] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x486),
	[108] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x488),
	[109] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x48a),
	[110] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x48c),
	[111] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x48e),
	[112] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x490),
	[113] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x492),
	[114] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x494),
	[115] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x496),
	[116] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x498),
	[117] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x49a),
	[118] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x49c),
	[119] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x49e),
	[120] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x4a0),
	[121] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x4a2),
	[122] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x4a4),
	[123] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x4a6),
	[124] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x4a8),
	[125] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x4aa),
	[126] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x4ac),
	[127] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x4ae),
	[128] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x4b0),
	[129] = (const u8*)((const u8*)sBlob_2e5cae_2e6160 + 0x8)
};
