// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00471300 rf_ui_checkbox_initialize_471300
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, UI widget constructor/render/input chains, original keypad selectors and native object layouts and native
// signed/x87/stack/callback ABI): thiscall(normalFile,selectedFile,checkedFile,x,y,hotkey,label,font), RET32. Delegates button initialization470C50 with seven corresponding args; if
// checkedFile nonempty loads(-1,0) into bitmap+68 and adds reference. Empty checkedFile preserves old handle; no own dimensions query, old-handle release, parent assignment or
// checked BYTE72 initialization/toggle.
char *__thiscall rf_ui_checkbox_initialize_471300(
        int *this,
        char *a2,
        char *a3,
        char *a4,
        int a5,
        int a6,
        int a7,
        char *Source,
        int a9)
{
  char *result; // eax
  char *v11; // [esp+Ch] [ebp-8h]

  rf_ui_image_button_initialize(this, a2, a3, a5, a6, a7, Source, a9);
  v11 = a4;
  do
    result = v11;
  while ( *v11++ );
  if ( v11 != a4 + 1 )
  {
    *(this + 17) = rf_bitmap_load_with_optional_mipmap_generation(a4, (void *)0xFFFFFFFF, 0);
    return (char *)rf_bitmap_texture_add_reference_backend_dispatch(*(this + 17));
  }
  return result;
}

