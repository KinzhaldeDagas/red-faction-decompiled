// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0042B600 rf_entity_apply_room_kind_frame_damage
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity node pose/physics, VFX rendering, secondary ammunition and attachment/detach native chains and native
// signed/x87/stack/callback ABI): Cdecl(required entity pointer), void; no own NULL guard. Attached-use-vehicle436A80 EXACT AL1 exits, every other byte continues. Requires entity
// DWORD+2064 mask0x3000 ANY set. Reads current room as DWORD[entity+0] through ECX getter486DE0, captures pointer; NULL room exits. If captured room DWORD+384==2 AND entity
// DWORD+508==3, computes FLOAT32(frame seconds663EC8 * FLOAT681E2C), calls4BB070(entity full handle,amount,-1,-1,type4,0,-1,LOWBYTE0) and discards ST0. Independently RE-READS
// captured room DWORD+384 afterwards: if now3 computes FLOAT32(frame seconds * FLOAT681E30), dispatches same eight slots with type7 and discards ST0. This is two independent tests,
// so delegate mutation of captured room kind can admit both calls; room pointer itself is not re-resolved. Room kind3 does not require entity+508==3. No own amount
// positivity/finite/player/humanoid/dead/invulnerability gate, cooldown or rollback; delegated common damage admission remains separate.
void __cdecl rf_entity_apply_room_kind_frame_damage(int *a1)
{
  float v1; // [esp+1Ch] [ebp-Ch]
  float v2; // [esp+20h] [ebp-8h]
  int first_dword; // [esp+24h] [ebp-4h]

  if ( !rf_entity_has_attached_use_vehicle((int)a1) && (a1[516] & 0x3000) != 0 )
  {
    first_dword = rf_receiver_get_first_dword(a1);
    if ( first_dword )
    {
      if ( *(_DWORD *)(first_dword + 384) == 2 && a1[127] == 3 )
      {
        v2 = rf_frame_delta_seconds * unk_681E2C;
        rf_damage_dispatch(a1[11], v2, -1, -1, 4, 0, -1, 0);
      }
      if ( *(_DWORD *)(first_dword + 384) == 3 )
      {
        v1 = rf_frame_delta_seconds * unk_681E30;
        rf_damage_dispatch(a1[11], v1, -1, -1, 7, 0, -1, 0);
      }
    }
  }
}

