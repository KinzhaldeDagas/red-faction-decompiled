// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055E780 rf_packed3x4_identity_to_output
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, 48-byte layout permutations, interpolation aliasing, packed3x4 template/stack offsets and wrapped game clocks): cdecl48byte output. Calls no-op vector constructor on local then copies verified PE template6407A8 via55EE10, finally copies48bytes to output. Template rows of4floats are(1,0,0,0),(0,1,0,0),(0,0,1,0). Distinct from affine layout with contiguous3x3 then translation. Returns output.
float *__cdecl rf_packed3x4_identity_to_output(float *a1)
{
  _BYTE v2[48]; // [esp+8h] [ebp-30h] BYREF

  rf_vector3_default_construct_noop(v2);
  rf_packed3x4_copy_static_identity(v2);
  qmemcpy(a1, v2, 0x30u);
  return a1;
}

