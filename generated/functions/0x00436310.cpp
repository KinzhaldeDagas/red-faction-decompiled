// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00436310 sub_436310
// UNREALRED VERIFIED [combat-fire-exhaustion-20260930] With a selected weapon, returns that weapon-indexed loaded count at Entity+0x32C+4*weapon plus reserve helper 0x4391D0. No selected weapon returns zero. The failed-fire recovery condition in 0x431FD0 tests this total, not an empty magazine alone.
// UNREALRED VERIFIED [combat-ammo-identity-20261111]: Total selected ammo is wrapping32bit selected-weapon loaded+safe4391D0 reserve. Only selectedPRIMARY==-1 returns0 beforeread; no saturating sum, pool alias matching or magazine-only substitution. Rawdrop439220 uses different direct reserve addressing.
int __cdecl sub_436310(int a1)
{
  if ( *(_DWORD *)(a1 + 676) == -1 )
    return 0;
  else
    return *(_DWORD *)(a1 + 4 * *(_DWORD *)(a1 + 676) + 812) + sub_4391D0(a1, *(_DWORD *)(a1 + 676));
}

