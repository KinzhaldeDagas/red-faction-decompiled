// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061ADCF __whiteout
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Mixed ABI ESI=DWORD read-counter pointer, one
// caller-popped stack FILE*, EAX first nonspace byte or EOF. Entry ECX is NOT an input; removed phantom argument. Increment counter BEFORE EVERY __inc(EDX=FILE) attempt including
// EOF; wraps32. EOF exits directly; otherwise GLOBAL isspace(unsigned lowBYTE), loop on nonzero. Consumes returned byte, no unget or counter correction. Saves EBX/EBP, ESI unchanged;
// plain RET. No own pointer validation, locking, locale snapshot or errno guard; stream/classification behavior delegated.
int __usercall _whiteout@<eax>(_DWORD *a1@<esi>, FILE *stream)
{
  int v2; // ebx

  do
  {
    ++*a1;
    v2 = _inc(stream);
  }
  while ( v2 != -1 && isspace((unsigned __int8)v2) );
  return v2;
}

