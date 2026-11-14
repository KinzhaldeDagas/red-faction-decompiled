// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058A040 rf_character_primary_bone_record_construct
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): For76-byte primary-bone record, calls no-op affine constructor at+24 then writes parent-index DWORD+72=-1. Returns this. Name bytes and affine data remain untouched here.
_DWORD *__thiscall rf_character_primary_bone_record_construct(_DWORD *this)
{
  rf_affine3x4_default_construct_noop(this + 6);
  *(this + 18) = -1;
  return this;
}

