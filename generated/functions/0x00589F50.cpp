// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00589F50 rf_v3c_get_aux_transform_count
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): Returns integer DWORD+88. CORRECTION: inherited Concurrency::VirtualProcessor::GetOwningRoot label and pointer return were false; character callers use this as an array COUNT, not a virtual-processor root. Corrected to int thiscall with opaque descriptor receiver.
int __thiscall rf_v3c_get_aux_transform_count(const void *this)
{
  return *((_DWORD *)this + 22);
}

