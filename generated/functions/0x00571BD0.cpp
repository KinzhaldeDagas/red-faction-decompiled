// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00571BD0 rf_renderer_get_viewport_rectangle
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, clipping arithmetic, stack ABI and callers): Writes current origin X/Y and effective width/height to four mandatory output DWORD pointers from187CCBC/CCC0/CCC4/CCC8. Returns the fourth pointer incidentally. No backend query or NULL checks.
_DWORD *__cdecl rf_renderer_get_viewport_rectangle(_DWORD *a1, _DWORD *a2, _DWORD *a3, _DWORD *a4)
{
  *a1 = unk_187CCBC;
  *a2 = unk_187CCC0;
  *a3 = unk_187CCC4;
  *a4 = unk_187CCC8;
  return a4;
}

