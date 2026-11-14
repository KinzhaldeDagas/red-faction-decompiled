// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00559300 rf_vector_normalize
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, atlas ownership, lightmap seam lifecycle, selected-face topology, SDK misidentification, x87 return ABI and PE bytes): Three-float in-place normalization. Computes float sumSquares and sqrt length;if ordered length>0,multiplies components by rounded reciprocal1/length. Otherwise writes(1,0,0),including zero/NaN length. Returns receiver,not original length. No infinity guard:infinite components may produce NaN under inf*0. Used for incident-face-normal sums by5526C0;canceling/empty sums become unitX. Distinct from 2D normalizer558B00,which returns original nonzero length or1 on zero.
float *__thiscall rf_vector_normalize(float *this)
{
  float v2; // [esp+4h] [ebp-10h]
  float v4; // [esp+Ch] [ebp-8h]
  float v5; // [esp+10h] [ebp-4h]

  v2 = *this * *this + *(this + 1) * *(this + 1) + *(this + 2) * *(this + 2);
  v5 = rf_sqrt_float(v2);
  if ( v5 > 0.0 )
  {
    v4 = 1.0 / v5;
    *this = *this * v4;
    *(this + 1) = *(this + 1) * v4;
    *(this + 2) = *(this + 2) * v4;
    return this;
  }
  else
  {
    *this = 1.0;
    *(this + 1) = 0.0;
    *(this + 2) = 0.0;
    return this;
  }
}

