// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046F2A0 rf_ui_show_yes_no_modal
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, history/modal/upsell control chains, original layout/duration constants and native signed/x87/stack/callback
// ABI): cdecl(title,body,yesCallback,noCallback,defaultFocus). Same interlock: active!=0 OR BYTE704E83==EXACT1 rejects. Sets title/font6F29A8, bottomY148 (original table index2),
// wraps body/hides edit meta. Action0=localized NO, hotkey49, noCallback(arg3); action1=localized YES, hotkey21, yesCallback(arg2). Hides actions2..3 and sets hotkeys-1 without
// clearing their user callbacks. Copies raw defaultFocus without range/enabled validation; sets active1/flag6F8C85=0. Return is incidental current EAX, not a normalized creation
// result.
int __cdecl rf_ui_show_yes_no_modal(const char *a1, char *a2, int (*a3)(void), int (*a4)(void), int a5)
{
  int result; // eax
  int i; // [esp+8h] [ebp-4h]

  result = unk_6F8C84;
  if ( !unk_6F8C84 && byte_704E83 != 1 )
  {
    rf_ui_modal_text_surface_initialize(dword_6F8FA0, a1, unk_6F29A8);
    unk_6F8E38 = dword_662440;
    rf_ui_modal_wrap_body_text(a2);
    rf_ui_control_set_state_byte9(dword_6F8FE0);
    rf_ui_button_build_centered_label(dword_6F8FE0, unk_88D56C, unk_6F29A8);
    unk_6F8FFC[0] = 49;
    unk_6F9024 = a4;
    rf_ui_control_set_state_byte9(&dword_6F9028);
    rf_ui_button_build_centered_label(&dword_6F9028, unk_88D568, unk_6F29A8);
    unk_6F9044 = 21;
    unk_6F906C = a3;
    for ( i = 2; i < 4; ++i )
    {
      rf_ui_control_clear_state_byte9(&dword_6F8FE0[18 * i]);
      unk_6F8FFC[18 * i] = -1;
    }
    unk_6F8C80 = a5;
    unk_6F8C84 = 1;
    unk_6F8C85 = 0;
    return a5;
  }
  return result;
}

