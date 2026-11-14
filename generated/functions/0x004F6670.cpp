// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F6670 rf_snapshot_pack_normalized_vector_s16
// UNREALRED VERIFIED [save-validation-20261028]: Normalizes source vec3 IN PLACE with rf_vector_normalize, then truncates each component*32767.0 toward zero and stores low16 bits to output. Does not saturate; return register is final conversion, not success flag.
int __cdecl rf_snapshot_pack_normalized_vector_s16(float *a1, _WORD *a2)
{
  int result; // eax

  rf_vector_normalize(a1);
  *a2 = (int)(*a1 * 32767.0);
  a2[1] = (int)(a1[1] * 32767.0);
  result = (int)(a1[2] * 32767.0);
  a2[2] = result;
  return result;
}

