// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045AC90 rf_multiplayer_chat_handle_key
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, chat input/console call chains, native500ms throttle, exact key predicates, original key maps/level prefixes,
// RFString ownership and static registration boundaries): Cdecl FULL keyDWORD dispatch,existing stored int return type preserved;EAX incidental rather than a uniform status. EXACT1
// cancel ->clear input and both active/init bytes45AD20. EXACT28 submit: only signed current input length>0 obtains Cstring and stored mode6F2CC4, calls shared500ms throttle;then
// resets all input keys/events and plays sound4(0,0.0,1.0) REGARDLESS send admission. Always cancel/clear afterward,including empty input (empty skips reset/sound). EXACT14 backspace
// ->remove final byte45AD50 THEN fall through to ordinary key mapping45ADF0 for SAME key. All other keys map directly; flagged variants of1/14/28 do not match full-DWORD special
// cases. No own active/runtime/pause/authority test; caller441490 supplies gates. Sender decline does not retain pending text or chat-open state.
_DWORD *__cdecl rf_multiplayer_chat_handle_key(int a1)
{
  char *v1; // eax
  int v3; // [esp+4h] [ebp-8h]

  if ( a1 == 1 )
    return rf_multiplayer_chat_cancel_and_clear();
  if ( a1 != 14 )
  {
    if ( a1 != 28 )
      return (_DWORD *)rf_multiplayer_chat_append_mapped_key(a1);
    if ( (int)rf_string_length_from_cstr((const char **)unk_6F2CDC) > 0 )
    {
      v3 = unk_6F2CC4;
      v1 = (char *)rf_string_object_c_str_or_empty(unk_6F2CDC);
      rf_multiplayer_send_chat_with_500ms_throttle(v1, v3);
      rf_input_reset_all_key_and_event_state();
      rf_gamesound_play_event(4, 0, 0.0, 1.0);
    }
    return rf_multiplayer_chat_cancel_and_clear();
  }
  rf_multiplayer_chat_remove_last_byte();
  return (_DWORD *)rf_multiplayer_chat_append_mapped_key(a1);
}

