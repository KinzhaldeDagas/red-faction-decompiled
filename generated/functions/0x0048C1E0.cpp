// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048C1E0 rf_server_apply_rcon_request_payload50
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet12/50/51/52/53/54 registry, sound/score/glass layouts, chat routing, RCON source admission and
// native string bounds): Recovered48C1E0..48C4BE,lastRET48C4BD; descriptor50 rcon_request. Cdecl(payload,sourceEndpoint),both consumed. Require dedicated markerBYTE704E83 EXACT1 and
// configured password Cstring704E94 nonempty; no separate runtime/authority test. Resolve source endpoint to player and require net4608. Scan FULL incoming password to NUL BEFORE
// strncpy256 into local256,force index255 NUL; cursor modulo16 unused afterward. Case-sensitive exact comparison of bounded local string against configured password. Mismatch silent.
// Match: traverse all circular players, clear netDWORD8 mask100 for each nonNULL net,then set requester net mask100; exclusive RCON grant. Format localized88E26C with requester
// RFString name+8 via unbounded sprintf into same256-byte local,then chat sender45A3F0(text,0). No password transmission back, length validation or rollback. Grant occurs before
// formatting/announcement. Static analysis only; configured runtime password value not read.
void __cdecl rf_server_apply_rcon_request_payload50(const unsigned __int8 *payload, const void *source)
{
  const char *v2; // [esp-4h] [ebp-154h]
  char *Format; // [esp+0h] [ebp-150h]
  _DWORD *v4; // [esp+4h] [ebp-14Ch]
  _DWORD *i; // [esp+3Ch] [ebp-114h]
  _DWORD *v6; // [esp+44h] [ebp-10Ch]
  char Destination[256]; // [esp+48h] [ebp-108h] BYREF
  int v8; // [esp+14Ch] [ebp-4h]

  if ( byte_704E83 == 1 && &byte_704E94[strlen(byte_704E94) + 1] != &byte_704E94[1] )
  {
    v6 = rf_player_find_by_network_endpoint((int)source);
    if ( v6 )
    {
      if ( v6[1152] )
      {
        v8 = 0;
        strncpy(Destination, (const char *)payload, 0x100u);
        Destination[255] = 0;
        v8 = (unsigned __int16)(v8 + strlen((const char *)payload) + 1);
        if ( !strcmp(Destination, byte_704E94) )
        {
          for ( i = (_DWORD *)dword_87C324; i; i = v4 )
          {
            if ( i[1152] )
              *(_DWORD *)(i[1152] + 8) &= ~0x100u;
            if ( *i == dword_87C324 )
              v4 = nullptr;
            else
              v4 = (_DWORD *)*i;
          }
          *(_DWORD *)(v6[1152] + 8) |= 0x100u;
          Format = (char *)dword_88E26C;
          v2 = rf_string_object_c_str_or_empty(v6 + 2);
          sprintf(Destination, Format, v2);
          rf_multiplayer_send_chat_line_packet12(Destination, 0);
        }
      }
    }
  }
}

