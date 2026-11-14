// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B2490 rf_multiplayer_apply_use_key_pressed_payload16
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled action packet15/16/20/28/36/46/47 registry, consumed source arguments, ownership, reload ordering and
// projectile traversal): Recovered4B2490..4B24F3,lastRET4B24F2; descriptor16 use_key_pressed. Cdecl payloadBYTE0 is CLAIMED network player ID; source ignored, no length. Find player
// by that ID; missing returns. Resolve player's current handle+20 using generic object resolver, not entity-specific resolver; only require nonNULL, then
// dispatch_use_if_nonnull(player). No own runtime/server/mode, source-ID ownership, alive, object-type or use-distance check here; delegate owns subsequent use admission. No response
// or meaningful callback result. Sender23C0 transports caller BYTE as playerID via4-byte unreliable packet16.
void __cdecl rf_multiplayer_apply_use_key_pressed_payload16(const unsigned __int8 *payload)
{
  _DWORD *v1; // [esp+8h] [ebp-8h]

  v1 = rf_player_find_by_network_id(*payload);
  if ( v1 )
  {
    if ( rf_object_resolve_handle(v1[5]) )
      rf_player_dispatch_use_if_nonnull((int)v1);
  }
}

