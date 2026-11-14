// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E47B0 rf_vani_player_release_streaming_resources
// UNREALRED VERIFIED [texture-conversion-20261028]: Releasespixel/palettebuffers0x5E4750; ifbitmaphandle+92>=0,passes to0x5781E0. If embeddedvfile+120openvia0x5935C0,closesit. Sets bitmaphandle=-1. Returnincidentalopen/closeresult; frameindex,time,flagsunchanged.
int __thiscall rf_vani_player_release_streaming_resources(int this)
{
  int result; // eax

  rf_vani_player_release_pixel_palette_buffers((void **)this);
  if ( *(int *)(this + 92) >= 0 )
    rf_bitmap_handle_recycle_slot_or_animation_entry(*(_DWORD *)(this + 92));
  result = rf_vfile_has_nonnegative_stream_slot((_DWORD *)(this + 120));
  if ( (_BYTE)result )
    result = rf_vfile_close_stdio_or_vpp((int *)(this + 120));
  *(_DWORD *)(this + 92) = -1;
  return result;
}

