// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004181B0 rf_monitor_record_scalar_deleting_destructor
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, monitor lifetime, debris lifecycle/contact audio, native render ABI and mixed spawn descriptor): Always invokes member destructor 0x4181E0; if low-byte flags bit1 is set, operator-delete(receiver). Other bits ignored; thiscall one DWORD argument, RET4. Returns original receiver bits even after deletion. No array cookie handling, bitmap release or list unlink.
void *__thiscall rf_monitor_record_scalar_deleting_destructor(void *this, char a2)
{
  rf_monitor_record_destroy_array_member((int)this);
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}

