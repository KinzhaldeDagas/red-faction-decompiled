// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F68E0 rf_snapshot_unpack_vector_s16_div32
// UNREALRED VERIFIED [object-entity-snapshot-continuation-20261027] Interpret three consecutive SIGNED16-bit words and dequantize each with0x4F6790 into destination floats. Same scalar helper is used for authored event-delay seconds elsewhere; units derive from caller, not the arithmetic routine.
int __cdecl rf_snapshot_unpack_vector_s16_div32(__int16 *a1, float *a2)
{
  int result; // eax

  *a2 = rf_snapshot_dequantize_s16_div32(*a1);
  a2[1] = rf_snapshot_dequantize_s16_div32(a1[1]);
  a2[2] = rf_snapshot_dequantize_s16_div32(a1[2]);
  return result;
}

