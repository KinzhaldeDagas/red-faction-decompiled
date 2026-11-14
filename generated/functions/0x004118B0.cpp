// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004118B0 rf_view_wrapper_get_dword8
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, clutter runtime teardown/render admission, DWORD-category glass callback, cached model binding and signed-counter clock-hand geometry): Cdecl view-wrapper pointer,one stackslot. Returns DWORD[wrapper+8] inEAX;does not dereference embedded entity pointer,convert tobool,allocate,validateNULL or mutate. Used as one admission value in local riot-shield render suppression;does not itself establish third-person/first-person semantics.
int __cdecl rf_view_wrapper_get_dword8(int a1)
{
  return *(_DWORD *)(a1 + 8);
}

