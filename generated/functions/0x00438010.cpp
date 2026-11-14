// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00438010 sub_438010
// UNREALRED VERIFIED [combat-panic-movement-20261111]: Current grounded movement classification predicate: current858 descriptor index+4 is run1 or apc5.438050 instead tests run1 or climb2; these are current descriptor values, independent of humanoid/class-default-name checks.
bool __cdecl sub_438010(int a1)
{
  if ( !a1 )
    return 0;
  return *(_DWORD *)(*(_DWORD *)(a1 + 2136) + 4) == 1 || *(_DWORD *)(*(_DWORD *)(a1 + 2136) + 4) == 5;
}

