// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005EF120 rf_ui_button_can_accept_active_drag
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Requires nonNULL global drag source0x1CF75D0 and target flags628&0x10. True if(target accept-mask1080 & source offer-mask1076)!=0 and(target capacity1088<0 OR source amount1092+target count1084<=target capacity1088). Signed comparisons/addition,no overflow protection,self exclusion,visibility check or source mask check beyond intersection.
bool __thiscall rf_ui_button_can_accept_active_drag(_DWORD *this)
{
  if ( !dword_1CF75D0 || (*(this + 157) & 0x10) == 0 )
    return 0;
  return (*(this + 270) & *((_DWORD *)dword_1CF75D0 + 269)) != 0
      && ((int)*(this + 272) < 0 || *((_DWORD *)dword_1CF75D0 + 273) + *(this + 271) <= *(this + 272));
}

