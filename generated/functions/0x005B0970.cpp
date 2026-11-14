// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B0970 rf_ui_window_set_background_bitmap_handle
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, UI window construction/navigation/parsing/drawing/cleanup, exact flag and list operations, original stack ABI and call sites): Thiscall window,new handle,unused extra stack DWORD,RET8. If handle differs from background1236,stores it and queries resolved dimensions into discarded locals. Unlike mask setter,does NOT unlock or release old handle. Unchanged path returns receiver,changed path returns dimension helper residue. No new handle validation,window resizing or name copy.
unsigned int *__thiscall rf_ui_window_set_background_bitmap_handle(unsigned int *this, unsigned int a2, int a3)
{
  unsigned int *result; // eax
  int v4; // [esp+4h] [ebp-8h] BYREF
  int v5; // [esp+8h] [ebp-4h] BYREF

  result = this;
  if ( a2 != *(this + 309) )
  {
    *(this + 309) = a2;
    return (unsigned int *)rf_bitmap_get_resolved_dimensions(*(this + 309), &v4, &v5);
  }
  return result;
}

