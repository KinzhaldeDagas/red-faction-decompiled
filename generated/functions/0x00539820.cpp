// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00539820 rf_record16_array_initialize_capacity
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, UV descriptors and rebasing, lightmap sampling, array capacity/ownership, liquid fallback and original PE bytes): Zeros header count/capacity/backing,then calls539860 if requested capacity nonzero. Does not release preexisting backing first;intended initialization,not safe reusable reset. No range/overflow validation or initialized elements.
void __thiscall rf_record16_array_initialize_capacity(_DWORD *this, int a2)
{
  *this = 0;
  *(this + 1) = 0;
  *(this + 2) = 0;
  if ( a2 )
    rf_record16_array_reallocate_capacity_unchecked(this, a2);
}

