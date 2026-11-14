// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DBB50 rf_player_initialize_weapon_preference_order
// UNREALRED VERIFIED [weapon-autoselect] Copies all 32 entries of the table-authored default weapon preference order into Player+0x1154.
int __cdecl rf_player_initialize_weapon_preference_order(int a1)
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  if ( a1 )
  {
    for ( i = 0; i < 32; ++i )
    {
      *(_DWORD *)(a1 + 4 * i + 4436) = rf_default_weapon_preference_order[i];
      result = i + 1;
    }
  }
  return result;
}

