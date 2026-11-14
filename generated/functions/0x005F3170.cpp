// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F3170 rf_ui_container_load_mask_bitmap
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Loads named bitmap with rf_bitmap_load_with_optional_mipmap_generation(filename,-1,1). Negative handle formats260-byte diagnostic and fatally exits at original container.cpp:266. Otherwise forwards(handle,filename) to0x5F3210. No NULL filename or snprintf bound;does not separately validate dimensions/format.
int __thiscall rf_ui_container_load_mask_bitmap(int *this, char *a2)
{
  int v4; // [esp+4h] [ebp-10Ch]
  char Buffer[260]; // [esp+8h] [ebp-108h] BYREF

  v4 = rf_bitmap_load_with_optional_mipmap_generation(a2, (void *)0xFFFFFFFF, 1);
  if ( v4 < 0 )
  {
    sprintf(Buffer, "Could not load in \"%s\"!", a2);
    rf_fatal_error_show_message_and_exit("D:\\projects\\rf_pc\\vsdk\\ui\\container.cpp", 266, Buffer);
  }
  return rf_ui_container_set_mask_bitmap(this, v4, a2);
}

