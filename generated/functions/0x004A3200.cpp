// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A3200 rf_server_apply_join_request_payload2
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, join/browser/roster payload codecs, native admission predicates, item bitmaps, logging clock ABI and peer update arithmetic): 
// Cdecl(payload,sender), runtime1/authority exactly1 only, no current incoming xrefs/null/length check. Constructs two-RFString prefix in36-byte local request record. Protocol BYTE0
// must equal89h; otherwise sends rejection8 and destroys record without parsing strings. Name and password each scan entire input toNUL, strncpy255 then force byte254=0; after each
// cursor becomes uint16(old+full scanned length+1). Reads raw player field DWORD between strings, requestedRate DWORD after password, then A0,B0,A1,B1 signature DWORDs into record
// arrays+20/+28.
// Calls join_validate(sender,record); nonzero return sends LOW8 rejection code. Zero copies name as by-value8-byte RFString into
// admit_player(sender,name,rawPlayerField,requestedRate), native20-byte caller cleanup; callee consumes name. Record destroyed on all ordinary/SEH paths. No player allocation before
// validation; does not independently validate password/hash/count/duplicate endpoint beyond delegate.
// UNREALRED VERIFIED (2026-11-11; original PE bytes, compiled registry/dispatcher and native ABI refinement): Original PE descriptor at0x00662960 registers opcode2 (join_request), callback0x004A3200. Native dispatcher49FB50 indirectly calls it with(payload,source endpoint),8-byte caller cleanup,after envelope/source admission; handler receives NO payload length. Thus absence of IDA direct call/xrefs does not imply a dormant handler. Compiled registration and dispatch edge verified independently of earlier paired-layout inference; actual invocation still depends on runtime admission.
void __cdecl rf_server_apply_join_request_payload2(unsigned __int8 *a1, _DWORD *a2)
{
  int v2; // eax
  _DWORD v3[2]; // [esp-10h] [ebp-190h] BYREF
  int v4; // [esp-8h] [ebp-188h]
  int v5; // [esp-4h] [ebp-184h]
  int v6; // [esp+4h] [ebp-17Ch]
  int v7; // [esp+8h] [ebp-178h]
  unsigned __int8 *v8; // [esp+10h] [ebp-170h]
  unsigned __int8 *v9; // [esp+14h] [ebp-16Ch]
  int v10; // [esp+18h] [ebp-168h]
  unsigned __int8 *v11; // [esp+20h] [ebp-160h]
  unsigned __int8 *v12; // [esp+24h] [ebp-15Ch]
  _DWORD *v13; // [esp+28h] [ebp-158h]
  __int16 v14; // [esp+2Ch] [ebp-154h]
  __int16 v15; // [esp+30h] [ebp-150h]
  char Destination[254]; // [esp+34h] [ebp-14Ch] BYREF
  char v17; // [esp+132h] [ebp-4Eh]
  int v18; // [esp+13Ch] [ebp-44h]
  unsigned __int8 v19; // [esp+143h] [ebp-3Dh]
  _DWORD self[2]; // [esp+144h] [ebp-3Ch] BYREF
  char *v21[2]; // [esp+14Ch] [ebp-34h] BYREF
  int v22; // [esp+154h] [ebp-2Ch]
  _DWORD v23[4]; // [esp+158h] [ebp-28h]
  int v24; // [esp+168h] [ebp-18h]
  int i; // [esp+16Ch] [ebp-14h]
  int v26; // [esp+170h] [ebp-10h]
  int v27; // [esp+17Ch] [ebp-4h]

  if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
  {
    rf_two_rfstring_prefix_construct(self);
    v27 = 0;
    v26 = 0;
    v19 = *a1;
    v26 = 1;
    if ( v19 == 137 )
    {
      v11 = &a1[v26 + 1];
      v12 = &a1[v26 + 1 + strlen((const char *)&a1[v26])];
      v10 = v12 - v11;
      v15 = (_WORD)v12 - (_WORD)v11;
      strncpy(Destination, (const char *)&a1[v26], 0xFFu);
      v17 = 0;
      v26 = (unsigned __int16)(v26 + (_WORD)v12 - (_WORD)v11 + 1);
      rf_string_assign_from_cstr(v21, Destination);
      v22 = *(_DWORD *)&a1[v26];
      v26 += 4;
      v8 = &a1[v26 + 1];
      v9 = &a1[v26 + 1 + strlen((const char *)&a1[v26])];
      v7 = v9 - v8;
      v14 = (_WORD)v9 - (_WORD)v8;
      strncpy(Destination, (const char *)&a1[v26], 0xFFu);
      v17 = 0;
      v26 = (unsigned __int16)(v26 + (_WORD)v9 - (_WORD)v8 + 1);
      rf_string_assign_from_cstr(self, Destination);
      v18 = *(_DWORD *)&a1[v26];
      v26 += 4;
      for ( i = 0; i < 2; ++i )
      {
        v23[i] = *(_DWORD *)&a1[v26];
        v23[i] = v23[i];
        v26 += 4;
        v23[i + 2] = *(_DWORD *)&a1[v26];
        v23[i + 2] = v23[i + 2];
        v26 += 4;
      }
      v24 = rf_server_validate_join_request((int)a2, (int)self);
      if ( v24 )
      {
        rf_server_send_join_rejection_packet4((int)a2, v24);
      }
      else
      {
        v5 = v18;
        v4 = v22;
        v13 = v3;
        rf_string_copy_construct_from_object(v3, v21);
        v6 = v2;
        rf_server_admit_player_after_join(a2, v3[0], v3[1], v4, v5);
      }
      v27 = -1;
      rf_two_rfstring_prefix_destroy((char *)self);
    }
    else
    {
      rf_server_send_join_rejection_packet4((int)a2, 8);
      v27 = -1;
      rf_two_rfstring_prefix_destroy((char *)self);
    }
  }
}

