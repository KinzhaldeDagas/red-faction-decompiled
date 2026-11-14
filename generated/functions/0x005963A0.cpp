// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005963A0 rf_scene_point_pool_release_index
// UNREALRED VERIFIED [transfer-scene-20261028]: Signed index, no bounds check. If BYTE at0x1BC2160+140*index differs from0xFF, writes0xFF. Does not clear any other fields or destroy resources. Returns incidental140*index, not a release count.
int __cdecl rf_scene_point_pool_release_index(int a1)
{
  int result; // eax

  result = 140 * a1;
  if ( unk_1BC2160[140 * a1] != -1 )
    unk_1BC2160[140 * a1] = -1;
  return result;
}

