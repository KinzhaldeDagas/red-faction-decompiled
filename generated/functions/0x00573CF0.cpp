// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00573CF0 rf_bitmap_texture_add_reference_backend_dispatch
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, clipping arithmetic, stack ABI and callers): Backend102 increments backend bitmap texture reference through rf_d3d8_bitmap_texture_add_reference. Other backends do nothing and leave backend code in EAX. Does not increment a CPU bitmap handle count here.
int __cdecl rf_bitmap_texture_add_reference_backend_dispatch(unsigned int a1)
{
  int result; // eax

  result = dword_187CC9C;
  if ( dword_187CC9C == 102 )
    return rf_d3d8_bitmap_texture_add_reference(a1);
  return result;
}

