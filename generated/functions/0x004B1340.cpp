// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B1340 rf_multiplayer_count_team_player_bytes
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, join/browser/roster payload codecs, native admission predicates, item bitmaps, logging clock ABI and peer update arithmetic): 
// Cdecl(out team0 BYTE*,out team1 BYTE*). Zeros both outputs then counts ALL circular-list players: team byte+48 exactly0 increments first output, exactly1 increments second, every
// other value ignored. Increments wrap modulo256; no local/connection/alive/runtime/game-mode filtering or output-null guard. Aliased outputs naturally accumulate both recognized
// teams in same byte. EAX is traversal artifact, not total count.
_BYTE *__cdecl rf_multiplayer_count_team_player_bytes(_BYTE *a1, _BYTE *a2)
{
  _BYTE *result; // eax
  _BYTE *v3; // [esp+0h] [ebp-8h]
  _BYTE *i; // [esp+4h] [ebp-4h]

  result = a1;
  *a1 = 0;
  *a2 = 0;
  for ( i = (_BYTE *)dword_87C324; i; i = v3 )
  {
    if ( i[48] )
    {
      if ( i[48] == 1 )
        ++*a2;
    }
    else
    {
      ++*a1;
    }
    result = i;
    if ( *(_DWORD *)i == dword_87C324 )
    {
      v3 = nullptr;
    }
    else
    {
      result = *(_BYTE **)i;
      v3 = *(_BYTE **)i;
    }
  }
  return result;
}

