// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004741A0 rf_item_start_one_second_fade
// UNREALRED VERIFIED [item-pickups-20261028]: If retention flag0x10 is clear, ORs flags+700 with4 and sets float lifetime+692=1.0. When MP mode==1 AND server authority==1 calls0x4A05E0 with leading0,item handle+44 and four-1 fields. Protected items unchanged. Does not reject already-fading item, so repeat resets its timer. Return branch-dependent, not boolean success.
char __cdecl rf_item_start_one_second_fade(int a1)
{
  char result; // al

  result = rf_item_has_retention_flag10(a1);
  if ( !result )
  {
    *(_DWORD *)(a1 + 700) |= 4u;
    *(float *)(a1 + 692) = 1.0;
    result = rf_multiplayer_runtime_mode;
    if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
      return rf_multiplayer_send_item_apply_packet40(0, *(_DWORD *)(a1 + 44), -1, -1, -1, -1);
  }
  return result;
}

