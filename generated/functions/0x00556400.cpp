// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00556400 rf_generated_uv_set_default_bitmap_if_nonnegative
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid boundary topology, generated UV modes, selection transforms and independently recovered routine boundaries): If signed argument >=0, stores it to global663E54(default generated-face bitmap). Negative values leave global unchanged and EAX unspecified. No bitmap validation/loading.
int __stdcall rf_generated_uv_set_default_bitmap_if_nonnegative(int a1)
{
  int result; // eax

  if ( a1 >= 0 )
  {
    dword_663E54 = a1;
    return a1;
  }
  return result;
}

