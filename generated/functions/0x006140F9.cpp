// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006140F9 _fastcopy_I
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(destination,source,unsigned byte count), void
// aligned SSE copy kernel. Loop count=count>>7, BODY runs before zero test. Each iteration loads first four16-byte vectors then stores them, then loads/stores next four; advance
// both128, DEC/JNZ. Count>=128 copies floor(count/128)*128 bytes, low7 ignored; count<128 underflows after first iteration and does not no-op. Both addresses require16-byte alignment
// for MOVDQA; no bounds/CPU/overlap checks or tail. Forward copy can corrupt harmful forward overlaps; parent memcpy tests direction before dispatch. ESI/EDI preserved, XMM0..7 and
// ECX clobbered; no EAX result guarantee.
void __cdecl fastcopy_I(__m128i *a1, const __m128i *a2, unsigned int a3)
{
  unsigned int v5; // ecx
  __m128i si128; // xmm1
  __m128i v7; // xmm2
  __m128i v8; // xmm3
  __m128i v9; // xmm5
  __m128i v10; // xmm6
  __m128i v11; // xmm7

  v5 = a3 >> 7;
  do
  {
    si128 = _mm_load_si128(a2 + 1);
    v7 = _mm_load_si128(a2 + 2);
    v8 = _mm_load_si128(a2 + 3);
    *a1 = _mm_load_si128(a2);
    a1[1] = si128;
    a1[2] = v7;
    a1[3] = v8;
    v9 = _mm_load_si128(a2 + 5);
    v10 = _mm_load_si128(a2 + 6);
    v11 = _mm_load_si128(a2 + 7);
    a1[4] = _mm_load_si128(a2 + 4);
    a1[5] = v9;
    a1[6] = v10;
    a1[7] = v11;
    a2 += 8;
    a1 += 8;
    --v5;
  }
  while ( v5 );
}

