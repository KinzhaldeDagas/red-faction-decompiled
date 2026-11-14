// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060CDDE crt_return_static_address_00664de0
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Six native bytes MOV EAX,OFFSET664DE0; RET. Returns address of static object itself, not DWORD loaded FROM it. Does not read any variadic/stack arguments,
// parse format strings, allocate, dereference receiver or modify globals. Corrected no-argument pointer-return ABI; global object contents/type semantics not
// inferred solely from old off_ label.
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): ABI refinement: native MOV EAX,OFFSET664DE0;RET accepts ZERO arguments andreturnsstaticstream-table basepointer. Oldconstchar*/variadic signature caused
// MERR_CALL(-12) at6095A2,610724,616325. Correcting ONLY thisprototype makes printf60956B,flsbuf61069F andstbuf61630A freshlydecompile successfully; disposabletrial
// preservedALL36target nativechunks andeverySPdelta. No instruction patch,manualSPadjustment,functionboundary change ornewlocaltype. Static32-byteFILE slots+32/+64 areconsumed
// byprintf/tempbuffer paths; earliernativeaddress-return contractretained withstaleprototype-retention phrasecorrected.
void *__cdecl crt_return_static_address_00664de0()
{
  return &off_664DE0;
}

