// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00564AB0 rf_character_select_lod_container
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): cdecl(characterDefinition,lodMode,distanceFloat). LOD array at6592,stride148,count6588. Auto modes are-1,less than-2,or greater than2:if count>1 returns FIRST container whose float(*(container+84)+16)>distance; no match falls back FIRST container, not last. Mode-2 returns last only when count>1. Explicit0..2 returns indexed container if count>1 and mode<count,elseNULL; count<=1 always returns first even explicit mode2/count0. No finite/count/layout validation.
int __cdecl rf_character_select_lod_container(int a1, int a2, float a3)
{
  int i; // [esp+8h] [ebp-4h]

  if ( a2 == -1 || a2 < -2 || a2 > 2 )
  {
    if ( *(int *)(a1 + 6588) > 1 )
    {
      for ( i = 0; i < *(_DWORD *)(a1 + 6588); ++i )
      {
        if ( *(float *)(*((_DWORD *)rf_vector3_default_construct_noop((void *)(a1 + 148 * i + 6592)) + 21) + 16) > (double)a3 )
          return a1 + 148 * i + 6592;
      }
    }
    return a1 + 6592;
  }
  if ( a2 == -2 )
  {
    if ( *(int *)(a1 + 6588) > 1 )
      return a1 + 148 * (*(_DWORD *)(a1 + 6588) - 1) + 6592;
    return a1 + 6592;
  }
  if ( *(int *)(a1 + 6588) <= 1 )
    return a1 + 6592;
  if ( *(_DWORD *)(a1 + 6588) > a2 )
    return a1 + 148 * a2 + 6592;
  else
    return 0;
}

