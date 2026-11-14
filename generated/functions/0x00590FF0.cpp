// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00590FF0 rf_dsound_get_paused_slot_play_handle
// UNREALRED VERIFIED [dsound-buffers-20261028]: Argument backend slot. Returns stored play handle+16 ONLY when0x5905B0 reports pause mask2; otherwise-1. Does not accept play handle or report active playing buffer handle.
int __cdecl rf_dsound_get_paused_slot_play_handle(int a1)
{
  int v2; // [esp+0h] [ebp-4h]

  v2 = -1;
  if ( rf_dsound_buffer_slot_pause_mask(a1) )
    return unk_1BA1830[11 * a1];
  return v2;
}

