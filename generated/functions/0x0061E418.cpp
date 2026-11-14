// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061E418 ___free_lconv_mon
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review):
// Cdecl(lconvPointer),void;correctedfalseintargumenttopointer. NULL->return.
// IndependentlyfreeSEVENpointerfieldsat12,16,20,24,28,32,36UNLESSeachmatchesLIVEdefaultpointerVALUEfrom666088,66608C,666090,666094,666098,66609C,6660A0respectively.
// Noaddress-ofconfusion,outerobjectfree,fieldclear,refcountcheck,lock,duplicate/aliasguardorownerrno/invalidcallback. Numericfields0..8andbytefieldsbeyond36untouched.
void __cdecl __free_lconv_mon(void **a1)
{
  void *v1; // esi

  if ( a1 )
  {
    if ( a1[3] != off_666088 )
      free(a1[3]);
    if ( a1[4] != off_66608C )
      free(a1[4]);
    if ( a1[5] != off_666090 )
      free(a1[5]);
    if ( a1[6] != off_666094 )
      free(a1[6]);
    if ( a1[7] != off_666098 )
      free(a1[7]);
    if ( a1[8] != off_66609C )
      free(a1[8]);
    v1 = a1[9];
    if ( v1 != off_6660A0 )
      free(v1);
  }
}

