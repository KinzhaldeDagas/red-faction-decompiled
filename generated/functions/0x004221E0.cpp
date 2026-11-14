// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004221E0 rf_character_resolve_sp_armor_absorption
// UNREALRED VERIFIED [combat-pool-and-radius-20260923]: Returns SP armor absorption, not total damage. Armor<=0 returns 0; damage type 5 (energy) or 6 (electrical) returns 0; type 4 (fire) returns min(current armor, scaled damage). Other types, including -1, multiply scaled damage by binary64[0x633008]=0.5199999809265137 (exact widened 0.52f), round that product to float at 0x42223D, and cap it at current armor. Caller 0x421BA0 separately subtracts returned absorption from armor and the remaining damage from life. Names are verified by the pointer table at 0x662D94 and the shared case-insensitive damage-type parser.
double __cdecl rf_character_resolve_sp_armor_absorption(int a1, float a2, int a3)
{
  float v4; // [esp+0h] [ebp-4h]

  if ( *(float *)(a1 + 56) <= 0.0 )
    return 0.0;
  if ( a3 == 6 || a3 == 5 )
    return 0.0;
  if ( a3 == 4 )
  {
    if ( *(float *)(a1 + 56) - a2 > 0.0 )
      return a2;
    else
      return *(float *)(a1 + 56);
  }
  else
  {
    v4 = a2 * 0.5199999809265137;
    if ( *(float *)(a1 + 56) - v4 <= 0.0 )
      return *(float *)(a1 + 56);
    return v4;
  }
}

