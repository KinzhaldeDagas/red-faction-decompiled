// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044A550 rf_geomod_cutter_resolve
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): Cdecl signed cutter index. Require signed0<=index<DWORD6EDEDC; invalid returns fullEAX0 without a lookup. Valid index computes
// native32-bit12*index and returns rawDWORD[6EDEE8+12*index] unchanged (stored pointer/handle), not the address of that field or record itself. No NULL/nonzero/type validation of
// selected value, no generation check, registry mutation or resolution callback. Existing cutter/solid context retained; stored entry may itself0.
int __cdecl rf_geomod_cutter_resolve(int a1)
{
  if ( a1 >= 0 && a1 < dword_6EDEDC )
    return unk_6EDEE8[3 * a1];
  else
    return 0;
}

