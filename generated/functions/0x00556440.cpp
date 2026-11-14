// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00556440 rf_generated_uv_set_positive_y_bitmap_if_nonnegative
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid boundary topology, generated UV modes, selection transforms and independently recovered routine boundaries): If signed argument >=0, stores global663E5C used by dominant-Y nonnegative-normal projection mode4. Negative values do nothing and leave return unspecified. No bitmap validation.
int __stdcall rf_generated_uv_set_positive_y_bitmap_if_nonnegative(int a1)
{
  int result; // eax

  if ( a1 >= 0 )
  {
    dword_663E5C = a1;
    return a1;
  }
  return result;
}

