// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060ACE6 __alloca_probe_8
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native alloca alignment/probe adapter. Incoming requested bytes EAX; PUSH ECX saves caller ECX, LEA ECX to original caller pre-CALL top (entryESP+4),
// subtract requested EAX and AND7 obtains padding for8-byte alignment. ADD padding to EAX; unsigned carry makes SBB ECX,ECX=-1 then OR forces request0xFFFFFFFF. Without carry
// request=bytes+padding. Restore original ECX, TAIL JMP __alloca_probe; no own allocation result, normal prologue or RET. Actual page touching/ESP relocation/overflow fault belongs
// to probe, not this22-byte adapter. High request overflow is saturated, not unchecked wrapped-small allocation.
void *__usercall _alloca_probe_8@<eax>(int a1@<eax>, int a2@<ecx>)
{
  char v2; // sp
  int v3; // ecx

  v3 = (v2 + 8 - (_BYTE)a1) & 7;
  return _alloca_probe(__CFADD__(v3, a1) ? -1 : v3 + a1, a2);
}

