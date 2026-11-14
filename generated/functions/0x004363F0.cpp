// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004363F0 sub_4363F0
// UNREALRED VERIFIED [combat-ammo-roles-pickups-20261111]: Full-magazine predicate is selectedprimary!=-1 ANDloaded[selectedID]==activeClip EXACT equality. Overfull isnot full and can enter431790 staging with NEGATIVE needed count, moving excessbacktopendingreserve before role-specific NPCreserve restoration. Do not replace with>= or positiveclip-only gate.
bool __cdecl sub_4363F0(int a1)
{
  return *(_DWORD *)(a1 + 676) != -1
      && *(_DWORD *)(a1 + 4 * *(_DWORD *)(a1 + 676) + 812) == unk_912088[340 * *(_DWORD *)(a1 + 676)];
}

