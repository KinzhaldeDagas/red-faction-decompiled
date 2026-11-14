// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DBBA0 rf_player_weapon_preference_rank
// UNREALRED VERIFIED [weapon-autoselect] Returns the zero-based position of a weapon index in the Player+0x1154 preference order, or -1 when absent.
int __cdecl rf_player_weapon_preference_rank(int a1, int a2)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 32; ++i )
  {
    if ( *(_DWORD *)(a1 + 4 * i + 4436) == a2 )
      return i;
  }
  return -1;
}

