// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005563B0 rf_generated_uv_initialize_default_settings
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid boundary topology, generated UV modes, selection transforms and independently recovered routine boundaries): Sets projection mode663E50=4, loads Rck_Default.tga through bitmap loader(handle hint -1,mipmap flag1), assigns returned handle to default663E54 and both Y-direction handles663E58/5C, and sets world scale663E60=32.0. No prior-resource release or load-failure guard; returns loaded handle.
int __cdecl rf_generated_uv_initialize_default_settings()
{
  dword_663E50 = 4;
  dword_663E54 = rf_bitmap_load_with_optional_mipmap_generation("Rck_Default.tga", (void *)0xFFFFFFFF, 1);
  dword_663E58 = dword_663E54;
  dword_663E5C = dword_663E54;
  flt_663E60 = 32.0;
  return dword_663E54;
}

