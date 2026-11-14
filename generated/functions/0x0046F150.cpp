// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046F150 rf_ui_show_ok_modal
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, history/modal/upsell control chains, original layout/duration constants and native signed/x87/stack/callback
// ABI): cdecl(title,body,userCallback,editable LOW BYTE). Rejects without edits when active6F8C84!=0 OR BYTE704E83==EXACT1. Initializes title/font6F29A8; bottom logicalY6F8E38=110
// (original modal table index1). Editable nonzero enables edit meta, sets edit6F8DC0 to EMPTY text (body ignored); supplied font6F29AC is ignored by4706C0, leaving stored font
// unchanged, hides3 body widgets, focus=4. Otherwise wraps body, hides edit meta, focus=0. Enables action0 with localized OK, hotkey24 and user callback; hides actions1..3/hotkeys-1
// but retains their old user callbacks. Sets active1/flag6F8C85=0. Return is register residue, not a success boolean; stored ABI retained.
int __cdecl rf_ui_show_ok_modal(const char *a1, char *a2, int (*a3)(void), char a4)
{
  int result; // eax
  int i; // [esp+4h] [ebp-4h]
  int j; // [esp+4h] [ebp-4h]

  result = unk_6F8C84;
  if ( !unk_6F8C84 && byte_704E83 != 1 )
  {
    rf_ui_modal_text_surface_initialize(dword_6F8FA0, a1, unk_6F29A8);
    unk_6F8E38 = dword_66243C;
    if ( a4 )
    {
      rf_ui_meta_control_set_flag9(unk_6F8E58);
      rf_ui_edit_set_text_bounded(byte_6F8DC0, (char *)byte_637F2D, unk_6F29AC);
      for ( i = 0; i < 3; ++i )
        rf_ui_control_clear_state_byte9((_BYTE *)&unk_6F8C88 + 64 * i);
      unk_6F8C80 = 4;
    }
    else
    {
      rf_ui_modal_wrap_body_text(a2);
      unk_6F8C80 = 0;
    }
    rf_ui_control_set_state_byte9(dword_6F8FE0);
    result = (int)rf_ui_button_build_centered_label(dword_6F8FE0, unk_88DCB4, unk_6F29A8);
    unk_6F8FFC[0] = 24;
    unk_6F9024 = a3;
    for ( j = 1; j < 4; ++j )
    {
      rf_ui_control_clear_state_byte9(&dword_6F8FE0[18 * j]);
      result = 72 * j;
      unk_6F8FFC[18 * j] = -1;
    }
    unk_6F8C84 = 1;
    unk_6F8C85 = 0;
  }
  return result;
}

