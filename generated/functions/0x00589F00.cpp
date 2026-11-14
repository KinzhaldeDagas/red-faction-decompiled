// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00589F00 rf_v3c_get_aux_transform_records_with_count
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): Writes descriptor DWORD+88 to mandatory count output through getter589F50, then returns array pointer+92 via589F30. No allocation or NULL checks. Records have100-byte stride at character binding callers. Old VirtualProcessor class inference was false.
void *__thiscall rf_v3c_get_aux_transform_records_with_count(const void *this, int *a2)
{
  *a2 = rf_v3c_get_aux_transform_count(this);
  return rf_v3c_get_aux_transform_records(this);
}

