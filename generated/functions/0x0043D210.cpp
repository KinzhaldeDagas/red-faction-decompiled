// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043D210 rf_inline_record40_array8_construct
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): Thiscall ECX required receiver, no stack args, returns original receiver fullEAX. Calls
// stdcall40DBD0(base=receiver+4,stride40,count8,constructor569350), in increasing element order0..7. Each callback only invokes no-op vector constructor at element+24 and returns
// element, so initializes NO payload bytes. Then518120(receiver) sets ONLY firstDWORD count=0; other header/payload bytes remain prior data, no capacity/backing pointer
// allocation/free. Explicit reload returns receiver. No pointer validation, clearing320-byte payload, element/resource creation or identity/radius initialization.
char *__thiscall rf_inline_record40_array8_construct(char *this)
{
  rf_vector_construct_no_unwind(
    this + 4,
    0x28u,
    8,
    (void *(__thiscall *)(void *))rf_record_vector_at24_default_construct_noop);
  rf_pointer_array_clear_count_keep_storage(this);
  return this;
}

