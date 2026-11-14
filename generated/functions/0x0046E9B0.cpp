// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046E9B0 rf_ui_modal_wrap_body_text
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, history/modal/upsell control chains, original layout/duration constants and native signed/x87/stack/callback
// ABI): cdecl body-text helper(text pointer). Wraps into up to3 offset/length pairs using width6F8C9C and font6F29A8. For i0..2 below returned line count, strncpy copies length[i]
// from text+offset[i] into256-byte stack buffer, writes NUL at buffer[length[i]], initializes 64-byte widget6F8C88+64*i and sets BYTE9. Other widgets clear BYTE9. Finally clears edit
// meta6F8E58 flag9. No own source/null or length<=255/nonnegative validation; relies on wrap delegate constraints. Stored integer pointer ABI retained.
int __cdecl rf_ui_modal_wrap_body_text(char *text)
{
  int i; // [esp+0h] [ebp-124h]
  int v3; // [esp+4h] [ebp-120h]
  int line_offsets[3]; // [esp+8h] [ebp-11Ch] BYREF
  char Destination[256]; // [esp+14h] [ebp-110h] BYREF
  size_t Count[3]; // [esp+118h] [ebp-Ch] BYREF

  v3 = rf_text_wrap_into_offset_length_arrays((int *)Count, line_offsets, text, dword_6F8C9C, 3, 0, unk_6F29A8);
  for ( i = 0; i < 3; ++i )
  {
    if ( i >= v3 )
    {
      rf_ui_control_clear_state_byte9((_BYTE *)&unk_6F8C88 + 64 * i);
    }
    else
    {
      strncpy(Destination, &text[line_offsets[i]], Count[i]);
      Destination[Count[i]] = 0;
      rf_ui_modal_text_surface_initialize((int *)&unk_6F8C88 + 16 * i, Destination, unk_6F29A8);
      rf_ui_control_set_state_byte9((_BYTE *)&unk_6F8C88 + 64 * i);
    }
  }
  return rf_ui_meta_control_clear_flag9(unk_6F8E58);
}

