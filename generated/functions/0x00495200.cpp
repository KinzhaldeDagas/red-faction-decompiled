// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00495200 rf_multiplayer_apply_glass_kill_payload54
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet12/50/51/52/53/54 registry, sound/score/glass layouts, chat routing, RCON source admission and
// native string bounds): Recovered495200..495394,lastRET495393; descriptor54 glass_kill. Cdecl payload only,source ignored,no length or own runtime/authority guard. Payload29 bytes:
// saved geometryID DWORD0,raw flagBYTE4,impact XYZ floats5/9/13,direction XYZ17/21/25. Normalize direction BEFORE checking global world solid, including nondirectional branch. If
// world exists lookup geometry by savedID, then unguardedly use returned record+40 first-DWORD getter as face head; no returned-record NULL admission. If head nonNULL, flag!=0 calls
// nondirectional glass break(head,impact,1),else directional(head,impact,normalizedDirection,1). Only FIRST face: native jumps to exit after either break, making apparent next-face
// loop unreachable. No source-ID binding, finite vector check or callback success handling here; delegates own glass admission/effects. Sender494F20 identical29-byte payload/32-byte
// reliable envelope.
void __cdecl rf_multiplayer_apply_glass_kill_payload54(const unsigned __int8 *payload)
{
  int geometry_record_by_saved_id; // [esp+0h] [ebp-2Ch]
  int first_dword; // [esp+4h] [ebp-28h]
  float v3[3]; // [esp+8h] [ebp-24h] BYREF
  float v4[3]; // [esp+14h] [ebp-18h] BYREF
  int v5; // [esp+20h] [ebp-Ch]
  int v6; // [esp+24h] [ebp-8h]
  unsigned __int8 v7; // [esp+2Bh] [ebp-1h]

  v6 = 0;
  rf_vector3_default_construct_noop(v3);
  rf_vector3_default_construct_noop(v4);
  v5 = *(_DWORD *)&payload[v6];
  v6 += 4;
  v7 = payload[v6];
  v3[0] = *(float *)&payload[++v6];
  v6 += 4;
  v3[1] = *(float *)&payload[v6];
  v6 += 4;
  v3[2] = *(float *)&payload[v6];
  v6 += 4;
  v4[0] = *(float *)&payload[v6];
  v6 += 4;
  v4[1] = *(float *)&payload[v6];
  v6 += 4;
  v4[2] = *(float *)&payload[v6];
  v6 += 4;
  rf_vector_normalize_reciprocal_sqrt(v4);
  if ( rf_world_solid )
  {
    geometry_record_by_saved_id = rf_solid_find_geometry_record_by_saved_id((_DWORD *)rf_world_solid, v5);
    first_dword = rf_receiver_get_first_dword((void *)(geometry_record_by_saved_id + 40));
    if ( first_dword )
    {
      if ( v7 )
        rf_glass_face_break_nondirectional(first_dword, v3, 1);
      else
        rf_glass_face_break_directional(first_dword, v3, v4, 1);
    }
  }
}

