// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045AE50 rf_multiplayer_chat_input_prompt_render
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, original55-entry packet registry and dispatcher bounds, departure/limbo ordering, native string ABI, flag-node cleanup and netgame-update versus ping/pong identities): 
// No arguments. If initialization BYTE6F2CC9 zero calls45AF60 then latches1; does not otherwise infer initialization delegate semantics. Constructs prefix RFString: chat-mode
// DWORD6F2CC4 exactly0 chooses localized To all88DF18,exactly1 To team88E074,others leave empty. Copies global input RFString6F2CDC and prefix into TWO owned by-value8-byte stack
// objects, calls chat_input_bar_render,cleans16 native argument bytes,then destroys original local prefix. No runtime/authority/chat-active admission check, network send or input
// reset here; renderer consumes passed copies. Caller confirms corrected renderer ABI.
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, chat input/console call chains, native500ms throttle, exact key predicates, original key maps/level prefixes,
// RFString ownership and static registration boundaries): Delegate45AF60 now decoded: when initBYTE6F2CC9 is zero, prompt clears ONLY input RFString6F2CDC,then sets init1. It does
// not itself set active or reset throttle. Cancel45AD20 clears input/init/active;begin45B470 sets active/mode but does not clear init or input. Thus prompt initialization is deferred
// until drawing;mode changes alone do not erase an already initialized edit. Existing owned-RFString renderer ABI and prefix routing preserved.
void rf_multiplayer_chat_input_prompt_render()
{
  int v0; // eax
  int v1; // eax
  int v2[2]; // [esp-10h] [ebp-48h] BYREF
  int v3[8]; // [esp-8h] [ebp-40h] BYREF
  int v4; // [esp+18h] [ebp-20h]
  int *v5; // [esp+1Ch] [ebp-1Ch]
  void *v6; // [esp+20h] [ebp-18h]
  char *v7[2]; // [esp+24h] [ebp-14h] BYREF
  int v8; // [esp+34h] [ebp-4h]

  if ( !unk_6F2CC9 )
  {
    rf_multiplayer_chat_clear_input_buffer_only();
    unk_6F2CC9 = 1;
  }
  rf_string_construct_empty(v7);
  v8 = 0;
  v4 = unk_6F2CC4;
  if ( unk_6F2CC4 )
  {
    if ( v4 == 1 )
    {
      v3[6] = (int)dword_88E074;
      rf_string_assign_from_cstr(v7, dword_88E074);
    }
  }
  else
  {
    v3[7] = (int)dword_88DF18;
    rf_string_assign_from_cstr(v7, dword_88DF18);
  }
  v6 = v3;
  rf_string_copy_construct_from_object(v3, (char **)unk_6F2CDC);
  v3[5] = v0;
  v3[4] = v0;
  LOBYTE(v8) = 1;
  v5 = v2;
  rf_string_copy_construct_from_object(v2, v7);
  v3[3] = v1;
  LOBYTE(v8) = 0;
  rf_multiplayer_chat_input_bar_render(v2[0], v2[1], v3[0], v3[1]);
  v8 = -1;
  rf_string_destroy_buffer(v7);
}

