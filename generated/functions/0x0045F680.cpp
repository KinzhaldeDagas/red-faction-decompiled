// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045F680 rf_multiplayer_rules_apply_ui_state
// UNREALRED VERIFIED [lan-match-flow-20261028] Advanced-server rule apply converts the selected integer minute value to float seconds by multiplying 60.0 and stores directly at 0x704EE4. It directly stores selected frag and capture counts at 0x704EE8/0x704EF0. Disassembly at 0x45F6A8/0x45F6BA proves direct dword stores despite the current decompiler pointer presentation.
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, allocation/header ownership, exception and callback stack ABI, original rule tables and UI/flag apply
// ordering): Existing direct limit-store note confirmed;full flag mapping now verified against native instructions,original choice tables and builder labels. No own
// runtime/authority/mode gate or selected-index bound. Read time table661F20[index6F3C64],x87 multiply original DOUBLE60.0,round/store binary32 seconds704EE4;direct DWORD stores kill
// table661F3C[index6F41D4] ->704EE8 and capture661F70[index6F4614] ->704EF0 (not indirect through pointer-looking decompiler globals). For each raw checkedBYTE ANY nonzero
// enables,zero clears:team damage6F3EC0 separately writes bits40 then200;fall damage6F43D0 controls80 and BOTH branches then clear100 unconditionally;weapons stay6F4060
// controls10;force respawn6F3F80 controls20;balance teams6F4420 controls2000. Other bits preserved. Stores occur in stated order,no atomic aggregate assignment,sound,registry
// write,network broadcast or UI normalization. EAX is zero-extended balance checkbox raw byte at final test,not normalized success. Choice controls/toggles mutate UI only until this
// apply runs.
int rf_multiplayer_rules_apply_ui_state()
{
  int result; // eax

  *(float *)&dword_704EE4 = (double)dword_661F20[unk_6F3C64] * 60.0;
  *(_DWORD *)unk_704EE8 = dword_661F3C[unk_6F41D4];
  *(_DWORD *)unk_704EF0 = dword_661F70[unk_6F4614];
  if ( byte_6F3EC0[0] )
  {
    rf_multiplayer_game_flags |= 0x40u;
    rf_multiplayer_game_flags |= 0x200u;
  }
  else
  {
    rf_multiplayer_game_flags &= ~0x40u;
    rf_multiplayer_game_flags &= ~0x200u;
  }
  if ( byte_6F43D0[0] )
    rf_multiplayer_game_flags |= 0x80u;
  else
    rf_multiplayer_game_flags &= ~0x80u;
  rf_multiplayer_game_flags &= ~0x100u;
  if ( byte_6F4060[0] )
    rf_multiplayer_game_flags |= 0x10u;
  else
    rf_multiplayer_game_flags &= ~0x10u;
  if ( byte_6F3F80[0] )
    rf_multiplayer_game_flags |= 0x20u;
  else
    rf_multiplayer_game_flags &= ~0x20u;
  result = byte_6F4420[0];
  if ( byte_6F4420[0] )
    rf_multiplayer_game_flags |= 0x2000u;
  else
    rf_multiplayer_game_flags &= ~0x2000u;
  return result;
}

