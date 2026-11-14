// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00451F70 rf_input_binding_poll_pressed_or_held
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, sequence panel and input/binding natives, credits/endgame parsing and Extras-menu X-motion/lifecycle, native
// callback and text-draw argument roles and native signed/x87/stack/callback ABI): Cdecl(context,actionIndex,optional newPressBYTE*), returns AL0/1. Signed actionIndex>=LIVE
// context+3596 returnsAL0 BEFORE touching optional output; no negative-index guard. Otherwise caches row=context+12+28*index, clears nonnull outputBYTE0, and reads DWORD row+8:
// EXACT1 enables held-or-press behavior; EVERY other mode uses press-only. Both modes examine CURRENT signed keyboard WORDs row+20 then+22, skipping negatives. Each key queries
// chat-active BYTE; ANY nonzero chat plus nonzero451ED0(key) consumes58BB80 press count and discards it, then skips held state. Otherwise queries console-visible BYTE; ANY nonzero
// suppresses that keyboard slot WITHOUT consuming its press count. Unsuppressed key consumes58BB80: ANY nonzero full EAX sets output1 and returnsAL1 immediately; mode1 additionally
// queries raw scan-state58BC90 on zero press USING THE SAME captured key, returningAL1 on ANY nonzero AL and leaving output0. Early success skips later keyboard/mouse slots. After
// both keys, signed mouse WORD row+24<0 returns0. Captured code3 returns1 iff signed context+8>0; code4 returns1 iff signed context+8<0; wheel success never sets newPress output.
// Other nonnegative mouse codes re-read field for snapshot press count58ACB0: ANY nonzero EAX sets output1/returns1. Only mode1, on zero mouse press, re-reads field for
// heldBYTE58AC50 and returns1 for ANY nonzero AL, output0. No chat/console suppression for mouse/wheel, no mouse upper bound, no wheel/count clearing, no FIFO dequeue, and mouse
// press getter itself does not consume count. Row address/initial mode choice are cached; keyboard/chat/console and nonwheel mouse arguments are sampled along the stated branches,
// without a full binding snapshot.
bool __cdecl rf_input_binding_poll_pressed_or_held(int a1, int a2, _BYTE *a3)
{
  int v4; // [esp+0h] [ebp-14h]
  int v5; // [esp+4h] [ebp-10h]
  unsigned int v6; // [esp+8h] [ebp-Ch]
  int v7; // [esp+Ch] [ebp-8h]
  int i; // [esp+10h] [ebp-4h]
  int j; // [esp+10h] [ebp-4h]

  if ( a2 >= *(_DWORD *)(a1 + 3596) )
    return 0;
  v7 = a1 + 28 * a2 + 12;
  if ( a3 )
    *a3 = 0;
  if ( *(_DWORD *)(a1 + 28 * a2 + 20) == 1 )
  {
    for ( i = 0; i < 2; ++i )
    {
      if ( *(__int16 *)(v7 + 2 * i + 20) >= 0 )
      {
        if ( rf_multiplayer_chat_active_byte_get() && rf_input_scan_code_is_chat_reserved(*(__int16 *)(v7 + 2 * i + 20)) )
        {
          rf_input_take_press_count(*(__int16 *)(v7 + 2 * i + 20));
        }
        else if ( !rf_console_get_visible_byte() )
        {
          v6 = *(__int16 *)(v7 + 2 * i + 20);
          if ( rf_input_take_press_count(v6) )
          {
            if ( a3 )
              *a3 = 1;
            return 1;
          }
          if ( rf_input_get_scan_code_state_byte(v6) )
            return 1;
        }
      }
    }
    if ( *(__int16 *)(a1 + 28 * a2 + 36) >= 0 )
    {
      v5 = *(__int16 *)(a1 + 28 * a2 + 36);
      if ( v5 == 3 )
      {
        if ( *(int *)(a1 + 8) > 0 )
          return 1;
      }
      else if ( v5 == 4 )
      {
        if ( *(int *)(a1 + 8) < 0 )
          return 1;
      }
      else
      {
        if ( rf_mouse_get_button_press_count(*(__int16 *)(a1 + 28 * a2 + 36)) )
        {
          if ( a3 )
            *a3 = 1;
          return 1;
        }
        if ( rf_mouse_get_button_held_byte(*(__int16 *)(a1 + 28 * a2 + 36)) )
          return 1;
      }
    }
    return 0;
  }
  for ( j = 0; j < 2; ++j )
  {
    if ( *(__int16 *)(v7 + 2 * j + 20) >= 0 )
    {
      if ( rf_multiplayer_chat_active_byte_get() && rf_input_scan_code_is_chat_reserved(*(__int16 *)(v7 + 2 * j + 20)) )
      {
        rf_input_take_press_count(*(__int16 *)(v7 + 2 * j + 20));
      }
      else if ( !rf_console_get_visible_byte() && rf_input_take_press_count(*(__int16 *)(v7 + 2 * j + 20)) )
      {
        if ( a3 )
          *a3 = 1;
        return 1;
      }
    }
  }
  if ( *(__int16 *)(a1 + 28 * a2 + 36) < 0 )
    return 0;
  v4 = *(__int16 *)(a1 + 28 * a2 + 36);
  if ( v4 == 3 )
    return *(int *)(a1 + 8) > 0;
  if ( v4 == 4 )
    return *(int *)(a1 + 8) < 0;
  if ( !rf_mouse_get_button_press_count(*(__int16 *)(a1 + 28 * a2 + 36)) )
    return 0;
  if ( a3 )
    *a3 = 1;
  return 1;
}

