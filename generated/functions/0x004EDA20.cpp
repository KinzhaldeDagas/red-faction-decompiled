// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EDA20 rf_player_release_weapon_screen_bitmap
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, model cache fallback, material replacement, leg animation transitions and native caller ABI): Assumes nonNULL player. If signed bitmap field4232>=0, calls bitmap recycle helper and forwards EAX; otherwise returns incidental player pointer in EAX. Does not clear or invalidate field4232 or any other player state.
int __cdecl rf_player_release_weapon_screen_bitmap(int a1)
{
  int result; // eax

  result = a1;
  if ( *(int *)(a1 + 4232) >= 0 )
    return rf_bitmap_handle_recycle_slot_or_animation_entry(*(_DWORD *)(a1 + 4232));
  return result;
}

