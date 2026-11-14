// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00558B00 rf_vector2_normalize_length_or_unit_x
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, lightmap clusters, tile mapping, atlas placement, seam blend snapshots, recovered halfplanes and original PE bytes): Thiscall2-float vector. Computes float-rounded length through vector2_length;exact0 sets vector(1,0),returns ST0=1,not original0 length. Nonzero divides both components by computed length and returns that original nonzero float length via ST0. NaN/inf not guarded;no epsilon cutoff or allocation. Used by recovered cell halfplane test,so coincident vectors become unitX.
double __thiscall rf_vector2_normalize_length_or_unit_x(float *this)
{
  float v3; // [esp+4h] [ebp-4h]

  v3 = rf_vector2_length(this);
  if ( v3 == 0.0 )
  {
    *this = 1.0;
    *(this + 1) = 0.0;
    return 1.0;
  }
  else
  {
    *this = *this / v3;
    *(this + 1) = *(this + 1) / v3;
    return v3;
  }
}

