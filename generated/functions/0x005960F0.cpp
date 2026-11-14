// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005960F0 rf_scene_point_pool_mark_all_unused
// UNREALRED VERIFIED [transfer-scene-20261028]: Scans50 records at0x1BC2160 stride140 (0x8C), writes BYTE+0=0xFF sentinel only. Leaves vectors, scalar channels, auxiliary fields and other flags unchanged. EAX is incidental loop result, not initialization status. Assembly confirms BYTE sentinel and140-byte stride, despite mixed Hex-Rays array element scales.
int rf_scene_point_pool_mark_all_unused()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 50; ++i )
  {
    unk_1BC2160[140 * i] = -1;
    result = i + 1;
  }
  return result;
}

