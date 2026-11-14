// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006173E1 crt_run_empty_callback_span_00657ddc
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No consumed arguments. Native sets BOTH begin and end registers to identical fixed address00657DDC, copies begin to scan pointer, unsigned CMP/JNB
// immediately skips loop. Unreachable native loop would read nonNULL callback, CALL EAX and advance4, but current fixed equal bounds mean NO memory read/callback invocation. EAX
// retains00657DDC; ESI/EDI saved/restored. Not dynamic range lookup and not a generic callback traversal under current bytes. No global update or argument-dependent branch. Original
// PE static span boundary bytes independently captured.
void __cdecl crt_run_empty_callback_span_00657ddc()
{
  ;
}

