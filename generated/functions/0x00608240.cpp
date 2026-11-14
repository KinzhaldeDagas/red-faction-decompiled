// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00608240 _shortsort
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Internal short-sort ABI: EAX inclusive high-element
// address; three caller-cleaned stack slots are low-element address, byte width, comparator. If unsigned high<=low, return immediately without callback. Otherwise repeatedly scan
// low+width through high inclusive, comparing(candidate,currentMax) as signed int; replace max only on >0, byte-swap max with high when distinct and width nonzero, then subtract
// width from high until high<=low. This is maximum-selection sort for small ascending intervals, not insertion sort. Swaps have exactly width forward byte iterations; equal elements
// are not promised stable. Qsort6082D0 supplies nonzero width and <=8 elements. No own NULL/width/overflow/ordering guard; width0 with high>low cannot progress. EAX is native
// pointer/comparator residue, not a guaranteed result-array pointer; qsort ignores it.
_BYTE *__usercall shortsort@<eax>(
        _BYTE *result@<eax>,
        unsigned int a2,
        int a3,
        int (__cdecl *a4)(unsigned int, unsigned int))
{
  unsigned int v4; // edx
  _BYTE *v5; // edi
  int v6; // ecx
  unsigned int v7; // esi
  unsigned int v8; // ebx
  int v9; // esi
  unsigned int v10; // ecx
  char v11; // dl

  v4 = a2;
  v5 = result;
  if ( (unsigned int)result > a2 )
  {
    v6 = a3;
    do
    {
      v7 = a2 + a3;
      v8 = v4;
      if ( a2 + a3 <= (unsigned int)v5 )
      {
        do
        {
          if ( a4(v7, v8) > 0 )
            v8 = v7;
          v7 += a3;
        }
        while ( v7 <= (unsigned int)v5 );
        v6 = a3;
        v4 = a2;
      }
      v9 = v6;
      result = v5;
      if ( (_BYTE *)v8 != v5 && v6 )
      {
        v10 = v8 - (_DWORD)v5;
        do
        {
          v11 = result[v10];
          result[v10] = *result;
          --v9;
          *result++ = v11;
        }
        while ( v9 );
        v6 = a3;
        v4 = a2;
      }
      v5 -= v6;
    }
    while ( (unsigned int)v5 > v4 );
  }
  return result;
}

