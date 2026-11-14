// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043CB10 rf_model_read_selected_action_index_if_enabled
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): Thiscall required model-like receiver, one required DWORD output pointer, RET4. ANY nonzero BYTE7500 selects
// raw DWORD at receiver4820+12*DWORD7420 and stores it to caller output, then explicitAL1. BYTE7500==0 storesEXACT-1 to caller output thenAL0. The stored index itself may be-1 even
// on AL1; no check of count4816, selected index sign/range, underlying clip pointer, animation activity or output pointer, and no receiver mutation. Output store precedes Boolean AL
// overwrite.
char __thiscall rf_model_read_selected_action_index_if_enabled(int this, _DWORD *a2)
{
  if ( *(_BYTE *)(this + 7500) )
  {
    *a2 = *(_DWORD *)(this + 12 * *(_DWORD *)(this + 7420) + 4820);
    return 1;
  }
  else
  {
    *a2 = -1;
    return 0;
  }
}

