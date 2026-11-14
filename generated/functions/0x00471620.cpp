// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00471620 rf_ui_slider_initialize_471620
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, UI widget constructor/render/input chains, original keypad selectors and native object layouts and native
// signed/x87/stack/callback ABI): thiscall(parent,normalFile,selectedFile,x,y,trackWidth,trackHeight,minFLOAT,maxFLOAT), RET36. Sets parent/geometry, orientationBYTE40=(SIGNED
// trackWidth<trackHeight), so equality is horizontal. Stores binary32 min+64/max+68/current+52=min without range ordering/clamp. Nonempty normalFile loads handle+56, probes FILE
// dimensions into knobWH+44/+48 and adds reference; empty preserves handle/dimensions. Nonempty selectedFile loads handle+60; ONLY when normal handle<0 probes selected file knob
// dimensions; adds reference regardless load result. No callback setup, old-resource release, own source/size/finite/range/failure guard.
char *__thiscall rf_ui_slider_initialize_471620(
        int this,
        int a2,
        char *a3,
        char *a4,
        int a5,
        int a6,
        int a7,
        int a8,
        float a9,
        float a10)
{
  char *result; // eax
  char *v12; // [esp+Ch] [ebp-18h]

  *(_DWORD *)(this + 4) = a2;
  *(_DWORD *)(this + 12) = a5;
  *(_DWORD *)(this + 16) = a6;
  *(_DWORD *)(this + 20) = a7;
  *(_DWORD *)(this + 24) = a8;
  *(_BYTE *)(this + 40) = *(_DWORD *)(this + 20) < *(_DWORD *)(this + 24);
  *(float *)(this + 64) = a9;
  *(float *)(this + 68) = a10;
  *(float *)(this + 52) = a9;
  if ( strlen(a3) )
  {
    *(_DWORD *)(this + 56) = rf_bitmap_load_with_optional_mipmap_generation(a3, (void *)0xFFFFFFFF, 0);
    rf_bitmap_probe_dimensions_and_nonzero_format(a3, (int *)(this + 44), (int *)(this + 48));
    rf_bitmap_texture_add_reference_backend_dispatch(*(_DWORD *)(this + 56));
  }
  v12 = a4;
  do
    result = v12;
  while ( *v12++ );
  if ( v12 != a4 + 1 )
  {
    *(_DWORD *)(this + 60) = rf_bitmap_load_with_optional_mipmap_generation(a4, (void *)0xFFFFFFFF, 0);
    if ( *(int *)(this + 56) < 0 )
      rf_bitmap_probe_dimensions_and_nonzero_format(a4, (int *)(this + 44), (int *)(this + 48));
    return (char *)rf_bitmap_texture_add_reference_backend_dispatch(*(_DWORD *)(this + 60));
  }
  return result;
}

