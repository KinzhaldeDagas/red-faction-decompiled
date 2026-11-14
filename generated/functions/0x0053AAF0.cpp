// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0053AAF0 rf_procedural_bitmap_get_generated_handle_unchecked
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, embedded cutter literal geometry,all vertex/index/UV words and registry/procedural accessors,original ECX/stack flow and PE bytes): Cdecl signed procedural record index,caller pops4. Return raw DWORD at0x14262D8+56*index+24 inEAX; equivalent0x14262F0+56*index. This is generated bitmap handle consumed as face texture by517470/52D560 when liquid procedural-record index>=0. No record bounds/live-state,handle validity,animation update,allocation or output writes.
int __cdecl rf_procedural_bitmap_get_generated_handle_unchecked(int a1)
{
  return unk_14262F0[14 * a1];
}

