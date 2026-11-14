// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F2F30 rf_ui_container_destroy
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): If mask handle DWORD888>=0,unlocks CPU bitmap handle then stores888=-1. Does not explicitly zero mask pixel pointer892 or release bitmap asset. Then calls full gadget destroy0x5AB7B0;return forwarded.
int __thiscall rf_ui_container_destroy(unsigned int *this)
{
  if ( (*(this + 222) & 0x80000000) == 0 )
  {
    rf_bitmap_unlock_cpu_handle_wrapper(*(this + 222));
    *(this + 222) = -1;
  }
  return rf_ui_gadget_destroy(this);
}

