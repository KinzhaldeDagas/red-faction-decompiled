// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FBDD0 rf_scene_material_pool_cursors_construct_empty
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Zeroes sixDWORDs at0..20 and returns this. Legacy material reader0x5FBE80 interprets pairs as{usedCountPointer,basePointer} for200-byte material records,per-frame float values,andextra float values. No allocation,capacity or pointee writes.
_DWORD *__thiscall rf_scene_material_pool_cursors_construct_empty(_DWORD *this)
{
  *this = 0;
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *(this + 5) = 0;
  return this;
}

