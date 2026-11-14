// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B0890 rf_ui_window_set_mask_bitmap_handle
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, UI window construction/navigation/parsing/drawing/cleanup, exact flag and list operations, original stack ABI and call sites): Thiscall window,new handle,unused extra stack DWORD,RET8. If handle unchanged,does nothing and returns receiver. If changed,unlocks OLD handle throughthe existing bitmap unlock wrapper only when signed old1232>=0,stores new1232,queries resolved dimensions into two discarded locals. Does not change rectangle,validate new handle,copy filename or retain queried dimensions. Changed-path EAX is dimension helper residue,not object pointer contract.
unsigned int *__thiscall rf_ui_window_set_mask_bitmap_handle(unsigned int *this, unsigned int a2, int a3)
{
  unsigned int *result; // eax
  int v5; // [esp+4h] [ebp-8h] BYREF
  int v6; // [esp+8h] [ebp-4h] BYREF

  result = this;
  if ( a2 != *(this + 308) )
  {
    if ( (*(this + 308) & 0x80000000) == 0 )
      rf_bitmap_unlock_cpu_handle_wrapper(*(this + 308));
    *(this + 308) = a2;
    return (unsigned int *)rf_bitmap_get_resolved_dimensions(*(this + 308), &v5, &v6);
  }
  return result;
}

