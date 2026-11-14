// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046F3E0 rf_ui_show_choice_modal
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, history/modal/upsell control chains, original layout/duration constants and native signed/x87/stack/callback
// ABI): cdecl(title,body,count,captionPointers,callbackPointers,defaultFocus,hotkeyPointers). Rejects active!=0 or BYTE704E83==EXACT1. Initializes title and reads bottomY from
// original DWORD table662438[count] BEFORE any count bound; table0..4=(72,110,148,186,224). Wraps body/hides edit meta. For signed i<count AND i<4 enables action, copies caption[i];
// nonnull hotkey/callback arrays overwrite respective values, NULL arrays RETAIN old values. Hide loop starts at RAW count and runs while i<4, clearing BYTE9/hotkey-1 but retaining
// user callbacks: negative count indexes before action array; count>4 still reads table out of range before enabling first4. Stores unvalidated defaultFocus, active1/flag850. No own
// caption-array/null/count validity checks; return incidental.
int __cdecl rf_ui_show_choice_modal(const char *a1, char *a2, int a3, int a4, int a5, int a6, int a7)
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]
  int j; // [esp+0h] [ebp-4h]

  result = unk_6F8C84;
  if ( !unk_6F8C84 && byte_704E83 != 1 )
  {
    rf_ui_modal_text_surface_initialize(dword_6F8FA0, a1, unk_6F29A8);
    unk_6F8E38 = dword_662438[a3];
    result = rf_ui_modal_wrap_body_text(a2);
    for ( i = 0; i < a3 && i < 4; ++i )
    {
      rf_ui_control_set_state_byte9(&dword_6F8FE0[18 * i]);
      result = (int)rf_ui_button_build_centered_label(&dword_6F8FE0[18 * i], *(const char **)(a4 + 4 * i), unk_6F29A8);
      if ( a7 )
      {
        result = a7;
        unk_6F8FFC[18 * i] = *(_DWORD *)(a7 + 4 * i);
      }
      if ( a5 )
      {
        result = 72 * i;
        *(&unk_6F9024 + 18 * i) = *(int (**)(void))(a5 + 4 * i);
      }
    }
    for ( j = a3; j < 4; ++j )
    {
      rf_ui_control_clear_state_byte9(&dword_6F8FE0[18 * j]);
      unk_6F8FFC[18 * j] = -1;
      result = j + 1;
    }
    unk_6F8C80 = a6;
    unk_6F8C84 = 1;
    unk_6F8C85 = 0;
  }
  return result;
}

