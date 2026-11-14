// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048C630 rf_server_apply_rcon_command_payload51
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet12/50/51/52/53/54 registry, sound/score/glass layouts, chat routing, RCON source admission and
// native string bounds): Recovered48C630..48C88E,lastRET48C88D; descriptor51 rcon. Cdecl(payload,sourceEndpoint). Require dedicated markerBYTE704E83 EXACT1,source endpoint resolves
// player with net4608 and netDWORD8 mask100. No separate runtime/authority/password recheck. Full incoming Cstring scan precedes strncpy512 into local buffer;force index511 NUL. Copy
// bounded string including NUL into separate512-byte scratch, strtok(scratch," ") uses ONLY ASCII space delimiters. First nonempty token must case-sensitively equal one of four
// original PE strings in662870: kick,level,ban,ban_ip. On match call console_execute_command_line with ORIGINAL bounded string,not tokenized scratch,then exit. Empty/unlisted token
// silent; no loop over subsequent commands or interpretation of delegated console syntax here. No payload-length bound on initial scan or sender ID field.
void __cdecl rf_server_apply_rcon_command_payload51(const unsigned __int8 *payload, const void *source)
{
  char v2; // [esp+17h] [ebp-439h]
  char *v3; // [esp+1Ch] [ebp-434h]
  char *v4; // [esp+20h] [ebp-430h]
  __int16 v5; // [esp+2Ch] [ebp-424h]
  const unsigned __int8 *v6; // [esp+30h] [ebp-420h]
  char String[512]; // [esp+38h] [ebp-418h] BYREF
  char Destination[516]; // [esp+238h] [ebp-218h] BYREF
  int i; // [esp+440h] [ebp-10h]
  _DWORD *v10; // [esp+444h] [ebp-Ch]
  int v11; // [esp+448h] [ebp-8h]
  char *v12; // [esp+44Ch] [ebp-4h]

  v11 = 0;
  if ( byte_704E83 == 1 )
  {
    v10 = rf_player_find_by_network_endpoint((int)source);
    if ( v10 )
    {
      if ( v10[1152] )
      {
        if ( (*(_DWORD *)(v10[1152] + 8) & 0x100) != 0 )
        {
          v5 = v11 + (_WORD)payload + 1;
          v6 = &payload[v11 + 1 + strlen((const char *)&payload[v11])];
          strncpy(Destination, (const char *)&payload[v11], 0x200u);
          Destination[511] = 0;
          v11 = (unsigned __int16)(v11 + (_WORD)v6 - v5 + 1);
          v4 = Destination;
          v3 = String;
          do
          {
            v2 = *v4;
            *v3++ = *v4++;
          }
          while ( v2 );
          v12 = strtok(String, " ");
          if ( v12 )
          {
            for ( i = 0; i < 4; ++i )
            {
              if ( !strcmp(v12, off_662870[i]) )
              {
                rf_console_execute_command_line(Destination);
                return;
              }
            }
          }
        }
      }
    }
  }
}

