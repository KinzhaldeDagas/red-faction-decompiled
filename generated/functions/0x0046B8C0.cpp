// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046B8C0 rf_gameplay_priority_list_select_from_pointer
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, gameplay priority/audio call chains, original selector/geometry/constant data and native
// signed/x87/stack/callback ABI): Cdecl(x,y). ONLY both coordinates>0:row=(y-trunc(absListY6F7C94*scaleY))/pixelRowHeight via signed IDIV;selected6F7B88=scroll6F7B84+row. X only
// gates positivity. No row>=0/visibleRows/qualifyingCount/physical32 bounds or player lookup,ensure-visible,swap,sound. Any coordinate<=0 leaves selection unchanged (keyboard
// sentinels do not activate a row).
void __cdecl rf_gameplay_priority_list_select_from_pointer(int a1, int a2)
{
  if ( a1 > 0 && a2 > 0 )
    unk_6F7B88 = unk_6F7B84
               + (a2 - (int)((double)rf_ui_control_absolute_y(&dword_6F7C94) * rf_ui_scale_y)) / dword_6F299C;
}

