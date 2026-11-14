// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004569B0 rf_save_list_b_select_or_activate_row
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl rawX/rawY signedDWORDs. Both>0 compute (Y-convert_x87(absoluteY(control6F2590)*uiScaleY))/rowHeight6F299C by signed IDIV; otherwise use
// selected6F23EC-scroll6F23E8. Same relative row AND deadline55F2B0(6F2664) AL0 calls456720 with original X/Y. Any different row OR nonzero elapsed predicate instead forms wrapped
// scroll+row; only signed candidate<LIVE array6F26AC count admits selected write, with NO nonnegative check. Admitted candidate then fetches record filename
// and4706C0(edit6F2748,filename,font6F29AC); no copy/validation here. Always rearms400 on selection path even when candidate rejected. Unlike454890 there is no rawX<0 override to
// force activation after elapsed timer. No X bounds/row clip/divisor0 guard, sound, readiness test or normalized result.
int __cdecl rf_save_list_b_select_or_activate_row(int a1, int a2)
{
  int v3; // esi
  char *v4; // eax
  int v5; // [esp-4h] [ebp-14h]
  int v6; // [esp+Ch] [ebp-4h]

  if ( a1 <= 0 || a2 <= 0 )
    v6 = unk_6F23EC - unk_6F23E8;
  else
    v6 = (a2 - (int)((double)rf_ui_control_absolute_y(&dword_6F2590) * rf_ui_scale_y)) / dword_6F299C;
  if ( v6 == unk_6F23EC - unk_6F23E8 && !rf_clock_deadline_has_elapsed_half_period(&dword_6F2664) )
    return rf_save_list_b_request_save();
  v3 = v6 + unk_6F23E8;
  if ( v3 < rf_receiver_get_first_dword(dword_6F26AC) )
  {
    unk_6F23EC = v6 + unk_6F23E8;
    v5 = unk_6F29AC;
    v4 = (char *)rf_record272_array_element_address_unchecked(dword_6F26AC, v6 + unk_6F23E8);
    rf_ui_edit_set_text_bounded(byte_6F2748, v4, v5);
  }
  return rf_clock_deadline_set_wrapped_offset(&dword_6F2664, 400);
}

