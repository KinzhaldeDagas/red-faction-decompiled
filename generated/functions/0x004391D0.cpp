// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004391D0 sub_4391D0
// UNREALRED VERIFIED [combat-snapshot-optimization-20260930] Reserve query rejects null entity or negative weapon index, reads the weapon definition ammo index at0x912024+0x550*weapon, and reads Entity+0x2AC+4*ammo when that index is nonnegative. Loaded ammunition is separate and weapon-indexed in caller0x436310. Host snapshot reuse must still observe current shared reserve on every comparison; unchanged ownership or selected weapon cannot imply unchanged reserve. Unreal snapshot allocation policy is a host adaptation, not a recovered RF network format.
// UNREALRED VERIFIED [combat-ammo-identity-20261111]: Safe reserve view: nullentity/negativeweapon=>0; otherwise readweapon.AmmoID and return reserve[ID] only ifID>=0, else0. No own positive upperbounds. This safe negative rule must not be applied to raw grant/drop/reload/decrement owners.
int __cdecl sub_4391D0(int a1, int a2)
{
  if ( !a1 || a2 < 0 )
    return 0;
  if ( dword_912024[340 * a2] >= 0 )
    return *(_DWORD *)(a1 + 4 * dword_912024[340 * a2] + 684);
  return 0;
}

