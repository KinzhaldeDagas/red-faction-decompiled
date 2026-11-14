// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00461080 rf_browser_allocate_record_and_index_arrays_once
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, menu/profile call chains, endpoint/index sorting, native allocation/float/callback ABI and original
// switch/registry data): Cdecl requestedCountDWORD. Signed count<2 becomes2. Only if PRIMARY record pointer6F52CC NULL:operator-new(108*count) ->6F52CC,then new(4*count)->6F52D4,then
// new(4*count)->6F52D0. EACH native UNSIGNED MUL has overflow check:overflow saturates allocation request toFFFFFFFF,not a small wrapped size. No zero-initialization,element
// constructor,capacity-global update,old-count adjustment,growth/retry or NULL-result check between allocations. Primary pointer is published before secondary allocations;later
// exception/partial allocation has no cleanup/rollback here and nonNULL primary suppresses future calls. No runtime/network action.
void __cdecl rf_browser_allocate_record_and_index_arrays_once(int a1)
{
  if ( a1 < 2 )
    a1 = 2;
  if ( !unk_6F52CC )
  {
    unk_6F52CC = operator new(108 * a1);
    MEMORY[0x6F52D4] = operator new(4 * a1);
    unk_6F52D0 = operator new(4 * a1);
  }
}

