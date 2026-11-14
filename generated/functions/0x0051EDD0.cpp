// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051EDD0 rf_world_flush_see_through_face_batch
// UNREALRED VERIFIED [room-render-20261028]: If batch count0xA420B4>0 adds it to rendered-face statistic0xA42058 then renders context0xA420B8 with room0,face pointers0x930A40,trailing flags0,1. Global0xA42088 bit2 uses0x580090 after setting color(8,32,8,255),otherwise0x580040. Always clears batch count and context after call. Empty-batch return AL uninitialized/incidental; no reliable success boolean. Does not restore prior color.
char rf_world_flush_see_through_face_batch()
{
  char result; // al

  if ( dword_A420B4 > 0 )
  {
    *(_DWORD *)&byte_98967F[756185] += dword_A420B4;
    if ( (unk_A42088 & 2) != 0 )
    {
      rf_render_color_set_rgba8(8, 32, 8, 255);
      result = rf_renderer_draw_face_batch_alternate_dispatch(dword_A420B8, 0, dword_A420B4, (int)unk_930A40, 0, 1);
    }
    else
    {
      result = rf_renderer_draw_face_batch_backend_dispatch(dword_A420B8, 0, dword_A420B4, (int)unk_930A40, 0, 1);
    }
  }
  dword_A420B4 = 0;
  dword_A420B8 = 0;
  return result;
}

