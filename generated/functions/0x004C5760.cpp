// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C5760 rf_glass_face_break_nondirectional
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, original fragment spawn and bounded pool, eight-vertex twelve-triangle layout, fourteen-ray scoring, full room-pointer ABI and native glass branching): 
// Cdecl(face,impactPosition,lowBYTEforce). Entry suppressed ONLY when multiplayer BYTE exactly1 AND authority BYTE0 AND forceBYTE0. Nonzero authority values admit, other multiplayer
// values admit. Requires validate_register4C5800 AL nonzero; failure returns without sound/shatter/broadcast. Then smash_sound at impactPosition,
// shatter_dispatch(face,impactPosition,NULLdirection). Registry mutation and sound survive dispatch failure to resolve room; no rollback. Finally
// broadcast494F20(ownerObject36,impactPosition,listener17F10B0,1) ONLY multiplayer==1 AND authority==1 EXACT AND face.owner68 nonnull. Authority2 admits local break but suppresses
// broadcast. No independent actual-glass/material/health test, face lifetime ownership or network failure rollback.
void __cdecl rf_glass_face_break_nondirectional(int a1, float *a2, char a3)
{
  if ( rf_multiplayer_runtime_mode != 1 || rf_multiplayer_server_authority || a3 )
  {
    if ( rf_glass_face_validate_and_register(a1) )
    {
      rf_glass_smash_sound_play((int)a2);
      rf_glass_face_shatter_dispatch(a1, (int)a2, 0);
      if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
      {
        if ( *(_DWORD *)(a1 + 68) )
          rf_server_send_glass_break_packet54(*(_DWORD *)(*(_DWORD *)(a1 + 68) + 36), a2, flt_17F10B0, 1u);
      }
    }
  }
}

