// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BA3A0 rf_animation_clip_release_if_requested
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): Zero release byte returns immediately without reading clip. Nonzero: if data pointer+120 exists AND ownership byte+108 is nonzero, operator delete data and NULL pointer. Then clears name[0] and DWORD+112. Borrowed pointer+120 is left intact when ownership byte is0. Does not free clip object or perform a reference search itself; base-character release computes the flag by checking all other loaded records.
int __cdecl rf_animation_clip_release_if_requested(int a1, unsigned __int8 a2)
{
  int result; // eax

  result = a2;
  if ( a2 )
  {
    if ( *(_DWORD *)(a1 + 120) )
    {
      if ( *(_BYTE *)(a1 + 108) )
      {
        operator delete(*(void **)(a1 + 120));
        *(_DWORD *)(a1 + 120) = 0;
      }
    }
    *(_BYTE *)a1 = 0;
    *(_DWORD *)(a1 + 112) = 0;
    return a1;
  }
  return result;
}

