// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040D680 rf_int_min_signed
// UNREALRED VERIFIED [lightmap-shadows-20261028]: Returns smaller of two signed32-bit arguments. Equality returns secondargument. No clamping,absolutevalue or sideeffects.
int __cdecl rf_int_min_signed(int a1, int a2)
{
  if ( a1 >= a2 )
    return a2;
  else
    return a1;
}

