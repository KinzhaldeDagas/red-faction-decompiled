// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00442950 rf_render_local_player_auxiliary_views_and_visibility_union
// [UnrealRed combat room owner 2026-11-12; verified original-byte ASM] Clears authored room352 ONCE then loops local players, thermal weapon screen/monitor/scanner rendering; final main player views follow caller.352 accumulates across every contributing rendered pass in that group. Per-pass520950 resets353/depth/portal cache only, not352. Last-view overwrite and all-loaded-room substitutes are not native admission.
// [UnrealRed combat room contributors 2026-11-12; full original-byte caller/callee closure] Qualifies render-group union: thermal4EDA50 and scanner4EC140 set camera/viewport and render entity/corpse content but DO NOT call world-room520740/520950/520A70 or writeROOM352. They are not visibility352 contributors. Actual monitor417740->417780 mode0->417FA0 DOES render world rooms and contributes; monitor modes1 black/2 noise do not. Main player world passes also contribute. Count only evidenced world-room passes, while retaining intermediate renderer state changes until next explicit camera/setup.
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): No stack arguments and no consumed incoming ECX receiver: first meaningful ECX is global solid6FC420
// for51E850, which clears authored ROOM byte352 ONCE before any local-player pass. Iterate signed index0 while index<live DWORD87C638, reloading count. For each index: query476D00
// owner-present; only AL0 calls thermal4EDA50(entry). Always call monitor417740(entry), regardless owner. Then if BYTE[entry+4016] is EXACT1, set BYTE[entry+4017]=1, call
// scanner4EC140(entry), and afterward write BYTE[entry+4017]=0. Entry pointer is re-read from global array87C5B0 before every lookup/call/flag write, INCLUDING after scanner
// callback; replacing that array slot can leave old player flag set while clearing replacement player. No local count/pointer snapshot, NULL validation or preservation of prior4017
// value. After all iterations always reset viewport full-screen571C20, query owner-present AGAIN, and only anynonzero AL sets blackRGBA(0,0,0,255) and clears color571C40. Returns
// incidental final AL/delegate residue, not an auxiliary-render success. Correct prior room352 union qualification retained: thermal/scanner alter camera/viewport and render selected
// content but do not contribute world-room352; monitor world-render mode0 can contribute, monitor black/noise modes cannot, and later main world passes contribute. No per-player
// room352 clear or restoration of camera/projection/current player/color; viewport reset does not restore those states.
char __cdecl rf_render_local_player_auxiliary_views_and_visibility_union()
{
  char result; // al
  int i; // [esp+0h] [ebp-4h]

  rf_solid_clear_authored_room_visibility_byte352(rf_world_solid);
  for ( i = 0; i < rf_local_player_entry_count; ++i )
  {
    if ( !rf_unhide_global_owner_present() )
      rf_player_render_thermal_weapon_screen(rf_local_player_entries[i]);
    rf_monitor_update_records_for_player(rf_local_player_entries[i]);
    if ( *(_BYTE *)(rf_local_player_entries[i] + 4016) == 1 )
    {
      *(_BYTE *)(rf_local_player_entries[i] + 4017) = 1;
      rf_player_render_scanner_to_capture_bitmap((_DWORD *)rf_local_player_entries[i]);
      *(_BYTE *)(rf_local_player_entries[i] + 4017) = 0;
    }
  }
  rf_renderer_reset_viewport_full_screen();
  result = rf_unhide_global_owner_present();
  if ( result )
  {
    rf_render_color_set_rgba8(0, 0, 0, 255);
    return rf_renderer_clear_color_backend_dispatch();
  }
  return result;
}

