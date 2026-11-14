// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00513AB0 rf_projected_shadows_dispatch_frame
// VERIFIED: Per-frame projected-shadow dispatcher. Resets global work counter, walks the renderer-provided room list, and stops after eight accepted projector work entries.
// UNREALRED VERIFIED [general-gap-20260830]: Resets the projected-shadow work count, walks the renderer-provided room list, and stops after eight accepted projector entries.
int rf_projected_shadows_dispatch_frame()
{
  int result; // eax
  void **out_rooms; // [esp+0h] [ebp-Ch] BYREF
  int out_count; // [esp+4h] [ebp-8h] BYREF
  int i; // [esp+8h] [ebp-4h]

  rf_renderer_get_visible_room_array(&out_rooms, &out_count);
  rf_projected_shadow_work_count = 0;
  for ( i = 0; ; ++i )
  {
    result = i;
    if ( i >= out_count || rf_projected_shadow_work_count >= 8 )
      break;
    rf_projected_shadows_submit_room((int)out_rooms[i]);
  }
  return result;
}

