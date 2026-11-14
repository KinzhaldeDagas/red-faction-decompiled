// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00589F30 rf_v3c_get_aux_transform_records
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): Returns pointer DWORD+92 from V3C descriptor. No count/output/state change. Corrected old int return to pointer ABI representation; source caller indexes100-byte records.
void *__thiscall rf_v3c_get_aux_transform_records(const void *this)
{
  return *((void **)this + 23);
}

