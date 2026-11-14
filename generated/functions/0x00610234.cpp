// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00610234 _fastzero_I
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(destination,raw unsigned byte count), void
// vector kernel. ECX=count>>7; body executes BEFORE any zero test, stores eight aligned16-byte zero XMM0 vectors at offsets0..112, advances destination128, DEC/JNZ. Thus count>=128
// writes exactly128*floor(count/128), ignoring low7 bits; count<128 starts zero iteration count then underflows and runs until fault or2^32 iterations, not a no-op. MOVDQA
// requires16-byte-aligned writable destination; no own alignment/size/CPU checks or tail handling. EDI preserved, XMM0 clobbered; EAX not assigned a semantic result. Dispatcher61028B
// supplies aligned, nonzero multiples128.
void __cdecl fastzero_I(_OWORD *a1, unsigned int a2)
{
  unsigned int v3; // ecx

  v3 = a2 >> 7;
  do
  {
    *a1 = 0;
    a1[1] = 0;
    a1[2] = 0;
    a1[3] = 0;
    a1[4] = 0;
    a1[5] = 0;
    a1[6] = 0;
    a1[7] = 0;
    a1 += 8;
    --v3;
  }
  while ( v3 );
}

