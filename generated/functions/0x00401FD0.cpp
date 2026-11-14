// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00401FD0 rf_ai_resolve_attack_range
// VERIFIED [custom-attack-range]: RF AI attack-range resolver. When AI-block byte +0x528 equals 1, returns the entity custom attack-range float at block +0x52C directly. Otherwise nonzero argument selects primary weapon index +4, zero selects secondary index +8, and a positive index returns the selected weapons.tbl runtime AI attack range at weapon-record +0x514; fallback is 0.5 RF units. The block is owner +0x2A0, so the entity fields are owner +0x7C8/+0x7CC.
// UNREALRED VERIFIED [general-gap-20260830]: Returns the custom AI attack-range override when enabled; otherwise selects the primary or secondary weapons.tbl AI range and falls back to 0.5 RF units.
double __cdecl rf_ai_resolve_attack_range(int a1, char a2)
{
  int v3; // [esp+0h] [ebp-8h]
  float v4; // [esp+4h] [ebp-4h]

  v4 = 0.5;
  if ( *(_BYTE *)(a1 + 1320) == 1 )
  {
    return *(float *)(a1 + 1324);
  }
  else
  {
    if ( a2 )
      v3 = *(_DWORD *)(a1 + 4);
    else
      v3 = *(_DWORD *)(a1 + 8);
    if ( v3 > 0 )
      return *((float *)&unk_912514 + 340 * v3);
  }
  return v4;
}

