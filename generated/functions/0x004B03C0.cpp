// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B03C0 rf_client_apply_players_payload6
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet6/9/10/11/23 bindings, endpoint/source use, roster tags, readiness transitions, team sorting
// and native string/color ABI): Recovered4B03C0..4B0633, lastRET4B0632; descriptor6. Cdecl(payload,sourceEndpoint), TWO consumed args: source read only for host-flagged records. No
// payload length/runtime/authority gate. Read tagBYTE:0 creates new nonlocal player FIRST, no allocation NULL check, then consumes idBYTE,netflagsDWORD,IPv4DWORD,portWORD,NUL
// name,teamBYTE. Does not find/reuse existing IDs. Full name scan BEFORE strncpy255 to256-byte local, force index254NUL; cursor advances using original length+1 modulo16 while other
// field advances useDWORD. Assign truncated name to Player+8, raw teamBYTE to+48. If incoming netflags mask0x1 set, overwrite BOTH endpointDWORD0 andDWORD4 from source[0]/source[1],
// including high16 of second word; not just IPv4/WORD port. No mask/trust filtering on incoming flags/team. Loop until nonzero tag. Tag2 invokes4B0790(authority0 then
// level-entry/panel5); tag1 or ANY OTHER nonzero simply stops, no completion. No rollback on partial roster or failure, no timer arm in this callback.
void __cdecl rf_client_apply_players_payload6(const unsigned __int8 *payload, const void *source)
{
  int v2; // edx
  _DWORD *v3; // eax
  __int16 v4; // [esp+8h] [ebp-120h]
  const unsigned __int8 *v5; // [esp+Ch] [ebp-11Ch]
  _DWORD *runtime; // [esp+18h] [ebp-110h]
  unsigned __int8 v7; // [esp+1Fh] [ebp-109h]
  char Destination[256]; // [esp+20h] [ebp-108h] BYREF
  int v9; // [esp+124h] [ebp-4h]

  v9 = 0;
  while ( 1 )
  {
    v7 = payload[v9++];
    if ( v7 )
      break;
    runtime = rf_player_create_runtime(0);
    *(_BYTE *)(runtime[1152] + 20) = payload[v9];
    *(_DWORD *)(runtime[1152] + 8) = *(_DWORD *)&payload[++v9];
    *(_DWORD *)(runtime[1152] + 8) = *(_DWORD *)(runtime[1152] + 8);
    v9 += 4;
    *(_DWORD *)runtime[1152] = *(_DWORD *)&payload[v9];
    *(_DWORD *)runtime[1152] = *(_DWORD *)runtime[1152];
    v9 += 4;
    *(_WORD *)(runtime[1152] + 4) = *(_WORD *)&payload[v9];
    *(_WORD *)(runtime[1152] + 4) = *(_WORD *)(runtime[1152] + 4);
    v9 += 2;
    v4 = v9 + (_WORD)payload + 1;
    v5 = &payload[v9 + 1 + strlen((const char *)&payload[v9])];
    strncpy(Destination, (const char *)&payload[v9], 0xFFu);
    Destination[254] = 0;
    v9 = (unsigned __int16)(v9 + (_WORD)v5 - v4 + 1);
    rf_string_assign_from_cstr(runtime + 2, Destination);
    *((_BYTE *)runtime + 48) = payload[v9++];
    if ( (*(_DWORD *)(runtime[1152] + 8) & 1) != 0 )
    {
      v2 = *((_DWORD *)source + 1);
      v3 = (_DWORD *)runtime[1152];
      *v3 = *(_DWORD *)source;
      v3[1] = v2;
    }
  }
  if ( v7 == 2 )
    rf_client_roster_complete_begin_level_entry();
}

