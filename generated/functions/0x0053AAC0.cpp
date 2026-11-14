// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0053AAC0 rf_procedural_bitmap_get_dimensions_unchecked
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, embedded cutter literal geometry,all vertex/index/UV words and registry/procedural accessors,original ECX/stack flow and PE bytes): Cdecl signed record index,outWidthDWORD*,outHeightDWORD*,caller pops12. Compute record=0x14262D8+56*index using32-bit IMUL/address arithmetic; copy record+16 to*outWidth, then reload record+20 to*outHeight,return second loaded DWORD inEAX. Caller517470/52D560 use dimensions for generated liquid-surface UV denominators;index refers procedural RECORD,not generated bitmap handle. No index/count/live-state,output-pointer,positive-dimension or division checks; outputs are sequential writes,not an alias-safe snapshot.
int __cdecl rf_procedural_bitmap_get_dimensions_unchecked(int a1, _DWORD *a2, _DWORD *a3)
{
  int result; // eax

  *a2 = *((_DWORD *)&unk_14262D8 + 14 * a1 + 4);
  result = *((_DWORD *)&unk_14262D8 + 14 * a1 + 5);
  *a3 = result;
  return result;
}

