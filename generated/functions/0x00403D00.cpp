// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00403D00 sub_403D00
// UNREALRED VERIFIED [combat-ammo-identity-20261111]: Native fireownership admission reads nonzeroAI+18C[weaponID] only for0<=ID<64. Fresh431FD0 calls this at432384 and falsejumps433A89 beforefire. Do not confuse lackofownership test indrop439220 with fire; literal3 can remain selected/unowned but cannotfire throughthisgate.
bool __cdecl sub_403D00(int a1, unsigned int a2)
{
  return a2 < 0x40 && *(_BYTE *)(a2 + a1 + 396) != 0;
}

