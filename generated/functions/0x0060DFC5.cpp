// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060DFC5 __check_overflow_exit
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Internal overflow-exit adapter. Reserve8 temporary bytes,FST QWORD currentST0 WITHOUT pop; load saved highDWORD intoEAX,restoreESP,maskEAX&0x7FF00000; JMP
// shared60DFED check_overflow_start. No own RET/CW restore/result normalization or full range-error handling. Transient64-bit store may set floating status; original ST0 remains
// live. Shared successor belongs to larger range-exit flow.
void _check_overflow_exit()
{
  __asm { fst     [esp+8+var_8] }
  JUMPOUT(0x60DFED);
}

