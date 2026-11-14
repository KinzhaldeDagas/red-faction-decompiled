// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040D600 rf_float_maximum_two_values
// UNREALRED VERIFIED [decal-projection-20261028]: Returns second argument when second>=first OR comparison is unordered; otherwise returns first. Literal x87 comparison semantics retained; no explicit finite/NaN normalization or clamping.
// UNREALRED VERIFIED (2026-11-11; fresh native unordered refinement): Loads first then second, FCOMPP, TEST AH,5 / JP0x40D619; unordered selects SECOND just like ordered second>=first. Used as max_literal(x,0) by glare tint, where NaN x therefore selects0; this is not a symmetric NaN-propagating maximum.
double __cdecl rf_float_maximum_two_values(float a1, float a2)
{
  if ( a2 >= (double)a1 )
    return a2;
  else
    return a1;
}

