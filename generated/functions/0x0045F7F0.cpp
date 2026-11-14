// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045F7F0 rf_multiplayer_setup_apply_mode_control_flags
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, multiplayer level catalog/control call chains, native header/string ABI, original setup tables, slider
// arithmetic, callback stack reuse and RFString array ownership): Cdecl FULL modeDWORD,existing stored int(int) prototype retained;decompiler pointer inference false. EXACT0:set
// state9 meta6F4798/control6F3D40;clear meta6F46E8/control6F4218 and controls6F3E78,6F41D8,6F43D8,6F4618. EXACT1:clear4798/3D40,set46E8/4218 and all four shared controls.
// EXACT2:set4798/3D40,clear46E8/4218,set all four shared controls. Other modeDWORDs no calls/writes. Meta delegates also own child state propagation;not merely a standalone bool.
// Does not change selected mode,filtered/master levels,rotation,registry or network state. EAX last delegate/raw mode residue,not uniform success.
_BYTE *__cdecl rf_multiplayer_setup_apply_mode_control_flags(_BYTE *a1)
{
  _BYTE *result; // eax

  result = a1;
  if ( a1 )
  {
    if ( a1 == (_BYTE *)1 )
    {
      rf_ui_meta_control_clear_flag9(&dword_6F4798);
      rf_ui_control_clear_state_byte9(dword_6F3D40);
      rf_ui_meta_control_set_flag9(&unk_6F46E8);
      rf_ui_control_set_state_byte9(dword_6F4218);
      rf_ui_control_set_state_byte9(&unk_6F3E78);
      rf_ui_control_set_state_byte9(dword_6F41D8);
      rf_ui_control_set_state_byte9(&unk_6F43D8);
      return rf_ui_control_set_state_byte9(dword_6F4618);
    }
    else if ( a1 == (_BYTE *)2 )
    {
      rf_ui_meta_control_set_flag9(&dword_6F4798);
      rf_ui_control_set_state_byte9(dword_6F3D40);
      rf_ui_meta_control_clear_flag9(&unk_6F46E8);
      rf_ui_control_clear_state_byte9(dword_6F4218);
      rf_ui_control_set_state_byte9(&unk_6F3E78);
      rf_ui_control_set_state_byte9(dword_6F41D8);
      rf_ui_control_set_state_byte9(&unk_6F43D8);
      return rf_ui_control_set_state_byte9(dword_6F4618);
    }
  }
  else
  {
    rf_ui_meta_control_set_flag9(&dword_6F4798);
    rf_ui_control_set_state_byte9(dword_6F3D40);
    rf_ui_meta_control_clear_flag9(&unk_6F46E8);
    rf_ui_control_clear_state_byte9(dword_6F4218);
    rf_ui_control_clear_state_byte9(&unk_6F3E78);
    rf_ui_control_clear_state_byte9(dword_6F41D8);
    rf_ui_control_clear_state_byte9(&unk_6F43D8);
    return rf_ui_control_clear_state_byte9(dword_6F4618);
  }
  return result;
}

