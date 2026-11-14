// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00454890 rf_save_list_a_select_or_activate_row
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl(raw X,raw Y), signed DWORDs. Only BOTH>0 compute row=(Y-convert_x87(absoluteY(6F235C)*uiScaleY))/signed rowHeight6F299C using CDQ/IDIV truncation
// and32-bit subtraction; otherwise use current selected6F1FA0-scroll6F1F9C. No X geometry use beyond sign test, row clipping or divisor0/overflow guard. Different row always
// selects/rearms. Same row calls deadline predicate55F2B0(6F21FC): if predicateAL0 OR rawX<0, invokes4545C0 with X/Y outgoing slots (callee reads none), with no own rearm. Otherwise
// forms wrapped candidate=scroll+row, updates selected ONLY if signed candidate<LIVE array6F21AC count; NO candidate>=0 check. Rearms deadline400 via55F1F0 even if upper-bound
// rejection. No sound or uniform status return. Negative-X keyboard activation bypasses elapsed admission on same row; this differs from4569B0.
void __cdecl rf_save_list_a_select_or_activate_row(int a1, int a2)
{
  int v2; // esi
  int v3; // [esp+Ch] [ebp-4h]

  if ( a1 <= 0 || a2 <= 0 )
    v3 = unk_6F1FA0 - unk_6F1F9C;
  else
    v3 = (a2 - (int)((double)rf_ui_control_absolute_y(&dword_6F235C) * rf_ui_scale_y)) / unk_6F299C;
  if ( v3 != unk_6F1FA0 - unk_6F1F9C || rf_clock_deadline_has_elapsed_half_period(&dword_6F21FC) && a1 >= 0 )
  {
    v2 = v3 + unk_6F1F9C;
    if ( v2 < rf_receiver_get_first_dword(dword_6F21AC) )
      unk_6F1FA0 = v3 + unk_6F1F9C;
    rf_clock_deadline_set_wrapped_offset(&dword_6F21FC, 400);
  }
  else
  {
    rf_save_list_a_load_selected();
  }
}

