// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046FD00 rf_ui_panel_initialize_bitmap
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, UI widget constructor/render/input chains, original keypad selectors and native object layouts and native
// signed/x87/stack/callback ABI): thiscall(bitmapFilename,logicalX,logicalY), RET12. Writes X/Y DWORD+12/+16, loads bitmap(filename,-1,0) to handle+40, obtains dimensions into
// logical width/height+20/+24, then adds bitmap texture reference. No own empty-name/null/load-failure guard, parent/state change or old-handle release; return is delegate residue.
int __thiscall rf_ui_panel_initialize_bitmap(_DWORD *this, char *a2, int a3, int a4)
{
  *(this + 3) = a3;
  *(this + 4) = a4;
  *(this + 10) = rf_bitmap_load_with_optional_mipmap_generation(a2, (void *)0xFFFFFFFF, 0);
  rf_bitmap_get_resolved_dimensions(*(this + 10), this + 5, this + 6);
  return rf_bitmap_texture_add_reference_backend_dispatch(*(this + 10));
}

