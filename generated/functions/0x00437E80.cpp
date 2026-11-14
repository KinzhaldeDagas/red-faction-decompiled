// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00437E80 sub_437E80
// UNREALRED VERIFIED [combat-panic-movement-20261111]: Tests current movement descriptor858 index+4==run1 AND speedmode8C4==0.437EC0 tests the same current run descriptor with speedmode1. Class default Movemode and available animations are not substitutes for these current runtime fields.
bool __cdecl sub_437E80(int a1)
{
  if ( !a1 )
    return 0;
  return *(_DWORD *)(*(_DWORD *)(a1 + 2136) + 4) == 1 && !*(_DWORD *)(a1 + 2244);
}

