// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00616AC3 ctranexit
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Seven-byte INTERNAL fall-through entry, not complete standalone integer-return body: AND BYTE[EBP-712],0xFE clears mask1, then NEXT native instruction616ACA
// is cintrinexit entry. Carries caller-owned frame in EBP and live x87 ST0 through shared exit; shared normal/error paths restore saved CW and return ST0, not EAX. No own
// PUSH/RET/frame allocation, stack argument, numeric computation or direct cleanup call. Existing separate IDA function boundary retained; fresh PE-backed raw616AC3..616C10
// explicitly captures fall-through and shared RET. Correct custom floating ABI prevents callers mistaking EAX scratch for result.
long double __usercall ctranexit@<st0>(void *frame@<ebp>, long double value@<st0>)
{
  *((char *)frame - 712) &= ~1u;
  return cintrinexit((long double *)frame, value);
}

