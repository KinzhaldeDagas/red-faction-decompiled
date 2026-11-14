// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004978F0 rf_ctf_blue_capture_increment_and_assists
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, CTF carrier transforms, return/capture ordering, scoring and packet layouts): 
// No-argument caller-cleaned helper. Increments blue capture BYTE77D6E1 modulo256 BEFORE any mode/authority check. Only runtime mode1 and authority exactly1 traverses ALL players,
// including local, and awards +1 frag to team byte+48 exactly1 with score DWORD+44 byte+6 exactly1. Does not clear contribution bytes, check alive/connected/current carrier or
// broadcast. Calls outside CTF still increment counter; return AL is traversal artifact.
char rf_ctf_blue_capture_increment_and_assists()
{
  int v0; // eax
  int v2; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  LOBYTE(v0) = ++byte_77D6E1;
  if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
  {
    LOBYTE(v0) = dword_87C324;
    for ( i = dword_87C324; i; i = v2 )
    {
      LOBYTE(v0) = i;
      if ( *(_BYTE *)(i + 48) == 1 )
      {
        v0 = *(_DWORD *)(i + 44);
        if ( *(_BYTE *)(v0 + 6) == 1 )
          LOBYTE(v0) = rf_multiplayer_player_add_frags(i, 1);
      }
      if ( *(_DWORD *)i == dword_87C324 )
      {
        v2 = 0;
      }
      else
      {
        LOBYTE(v0) = i;
        v2 = *(_DWORD *)i;
      }
    }
  }
  return v0;
}

