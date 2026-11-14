// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F6840 rf_snapshot_pack_vector_s16_times32
// UNREALRED VERIFIED [object-entity-snapshot-continuation-20261027] For three source floats independently call arithmetic0x4F6770 and store LOW16 bits into consecutive signed-vector words. No normalization, magnitude guard or saturation in this helper; common-header caller separately substitutes zero for magnitude>=1024.
int __cdecl rf_snapshot_pack_vector_s16_times32(float *a1, _WORD *a2)
{
  int result; // eax

  *a2 = rf_snapshot_quantize_float_times32(*a1);
  a2[1] = rf_snapshot_quantize_float_times32(a1[1]);
  result = rf_snapshot_quantize_float_times32(a1[2]);
  a2[2] = result;
  return result;
}

