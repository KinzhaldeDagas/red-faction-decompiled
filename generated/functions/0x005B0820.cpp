// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B0820 rf_ui_window_load_mask_bitmap
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, UI window construction/navigation/parsing/drawing/cleanup, exact flag and list operations, original stack ABI and call sites): Thiscall window,path,RET4. Loads bitmap with fallback handle-1 and option1. Negative handle formats global18CD828 and fatals at window.cpp2521. Otherwise delegates5B0890 with handle and original path; path argument is unused by setter. Does not duplicate filename or validate dimensions; return is setter residue.
int __thiscall rf_ui_window_load_mask_bitmap(int *this, char *a2)
{
  int v4; // [esp+4h] [ebp-4h]

  v4 = rf_bitmap_load_with_optional_mipmap_generation(a2, (void *)0xFFFFFFFF, 1);
  if ( v4 < 0 )
  {
    sprintf(&unk_18CD828, "Could not load in \"%s\"!", a2);
    rf_fatal_error_show_message_and_exit("D:\\projects\\rf_pc\\vsdk\\ui\\window.cpp", 2521, &unk_18CD828);
  }
  return rf_ui_window_set_mask_bitmap_handle(this, v4, (int)a2);
}

