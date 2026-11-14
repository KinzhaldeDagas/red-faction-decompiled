// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00513B10 rf_projected_shadow_build_entity_packet
// UNREALRED VERIFIED [projected-shadow-cone-20260903]: Copies entity radius, render/model handles, world position, and the 3x3 entity orientation into the projected-shadow source packet.
int __cdecl rf_projected_shadow_build_entity_packet(int a1, int a2)
{
  float copy_result[3]; // [esp+0h] [ebp-Ch] BYREF

  *(float *)a2 = *(float *)(a1 + 120);
  *(_DWORD *)(a2 + 4) = *(_DWORD *)(a1 + 128);
  *(_DWORD *)(a2 + 8) = *(_DWORD *)(a1 + 620);
  rf_vector_copy((float *)(a2 + 12), copy_result, (const float *)(a1 + 60));
  return rf_matrix3_copy((float *)(a2 + 24), (const float *)(a1 + 72));
}

