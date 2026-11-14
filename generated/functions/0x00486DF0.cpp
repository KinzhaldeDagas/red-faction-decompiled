// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00486DF0 rf_dword_vector_construct_zero_capacity
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, material/foley parse and ownership, RFString input ABI, bitmap cache, property fallback and directional sound numbering): 
// Thiscall wrapper, no stack args. Pushes signed capacity0 and delegates to rf_dword_array_construct_capacity; preserves delegate EAX. Static constructor iterator refers to this
// wrapper at0x62C1F8. Sets up an empty DWORD vector through shared constructor; not a destructor and does not construct/delete pointed payload objects.
void *__thiscall rf_dword_vector_construct_zero_capacity(void *this)
{
  return rf_dword_array_construct_capacity(this, 0);
}

