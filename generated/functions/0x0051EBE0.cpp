// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051EBE0 rf_embedded_array_construct_count_only_51ebe0
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, solid/room construction,primitive topology and centering,lightmap wire/preset/marking paths,shared ownership helpers,original ECX/stack ABI and PE bytes): Thiscall no stack args. Calls shared array count-clear/keep-storage helper on receiver,returns receiver. Does not allocate,free,clear element payload or initialize whole embedded region. Used at solid+240;member storage after count is left untouched by this wrapper.
_DWORD *__thiscall rf_embedded_array_construct_count_only_51ebe0(_DWORD *this)
{
  rf_pointer_array_clear_count_keep_storage(this);
  return this;
}

