// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00497860 rf_ctf_red_capture_increment_and_assists
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, CTF carrier transforms, return/capture ordering, scoring and packet layouts): 
// No-argument caller-cleaned helper. Increments red capture BYTE77D6E0 modulo256 BEFORE any mode/authority check. Only runtime mode1 and authority exactly1 traverses the circular
// list of ALL players, including local player, and awards +1 frag to team byte+48 exactly0 with score DWORD+44 byte+6 exactly1. Does not clear contribution bytes, require
// alive/connected/current carrier, or broadcast. Standalone calls outside CTF still increment counter. Return AL is an artifact and is not reliably the new counter after server
// traversal.
char rf_ctf_red_capture_increment_and_assists()
{
  int v0; // eax
  int v2; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  LOBYTE(v0) = ++byte_77D6E0;
  if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
  {
    LOBYTE(v0) = dword_87C324;
    for ( i = dword_87C324; i; i = v2 )
    {
      LOBYTE(v0) = i;
      if ( !*(_BYTE *)(i + 48) )
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

