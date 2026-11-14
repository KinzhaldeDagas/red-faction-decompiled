// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00452220 rf_input_binding_map_relative_mouse_axes
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, sequence panel and input/binding natives, credits/endgame parsing and Extras-menu X-motion/lifecycle, native
// callback and text-draw argument roles and native signed/x87/stack/callback ABI): Cdecl(context,outFourDWORDs). Calls58AD50 with local X atEBP-8,local Y atEBP-4,and wheel
// destinationcontext+8; helper reads cached relative deltas without consuming/clearing and its EAX is ignored. For i0..3, first zeroes out[i], then reads LIVE axis enableBYTE
// context+3600+16*i. ANY nonzero enabled: signed sourceDWORD+4>=0 loads DWORD[EBP-8+4*source] into out[i], with NO upper bound. Addressing uses raw32-bit WRAPPED4*source scaling:
// ordinary selectors0/1 read supplied X/Y locals,2 reads saved EBP rather than wheel,3 reads return address; larger admitted indices may read other frame memory OR wrap back. In
// particular0x40000000 aliases X and0x7FFFFFFF scales to-4, reading loop index atEBP-12. Negative source keeps output0. ANY nonzero invertBYTE+1 then wrapping-negates current output;
// disabled records skip inversion. Configuration/output are not snapshotted, so aliasing out with context may change later fields/reads; wheel was stored before all output writes.
// Always normal-return full EAX4 from loop increment. No scaling, clamp, initialized/input gate, source-range validation or wheel normalization.
int __cdecl rf_input_binding_map_relative_mouse_axes(int a1, int a2)
{
  int result; // eax
  int i; // [esp+0h] [ebp-Ch]
  int v4; // [esp+4h] [ebp-8h] BYREF
  int v5; // [esp+8h] [ebp-4h] BYREF

  result = rf_mouse_get_relative_deltas(&v4, &v5, (_DWORD *)(a1 + 8));
  for ( i = 0; i < 4; ++i )
  {
    *(_DWORD *)(a2 + 4 * i) = 0;
    if ( *(_BYTE *)(a1 + 16 * i + 3600) )
    {
      if ( *(int *)(a1 + 16 * i + 3604) >= 0 )
        *(_DWORD *)(a2 + 4 * i) = *(&v4 + *(_DWORD *)(a1 + 16 * i + 3604));
      if ( *(_BYTE *)(a1 + 16 * i + 3601) )
        *(_DWORD *)(a2 + 4 * i) = -*(_DWORD *)(a2 + 4 * i);
    }
    result = i + 1;
  }
  return result;
}

