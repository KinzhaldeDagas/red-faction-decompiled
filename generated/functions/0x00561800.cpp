// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00561800 rf_text_log_buffer_clear
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, relative timestamp serialization, RFString extent/buffer ownership, bounded text-log branches and tagged model lookups): Unconditionally writes NUL to buffer0[0],sets used12=0 and lineCount20=1, returns record. Capacity/maxLines/ownership unchanged. No null/capacity check and no full-buffer wipe.
_DWORD *__thiscall rf_text_log_buffer_clear(_DWORD *this)
{
  *(_BYTE *)*this = 0;
  *(this + 3) = 0;
  *(this + 5) = 1;
  return this;
}

