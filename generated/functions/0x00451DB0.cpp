// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00451DB0 rf_input_binding_active_time_sum_clamped
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, sequence panel and input/binding natives, credits/endgame parsing and Extras-menu X-motion/lifecycle, native
// callback and text-draw argument roles and native signed/x87/stack/callback ABI): Cdecl(context,actionIndex), returns x87 floating value. Initializes local FLOAT32 accumulator0;
// signed actionIndex>=LIVE count context+3596 returns0, but no negative-index guard. Computes row=context+12+28*index and calls451F70(context,index,NULL); AL0 returns0 AFTER that
// predicate's input-counter side effects. On any nonzero AL, examines row's two CURRENT signed keyboard WORDs+20/+22 in order. Negative skips. For each nonnegative key, queries
// chat-active BYTE; when ANY nonzero and451ED0(key) AL nonzero, STILL calls58B850(key) and discards ST0, consuming its timestamp/down-time state without adding. Otherwise calls58B850
// and adds result to accumulator with a FLOAT32 store after EACH addition. Console visibility is not re-tested in this summing phase. Then CURRENT signed mouse WORD+24>=0
// calls58AC90(mouse), converts its SIGNED integer click-age result via FILD, adds it directly to accumulator with FLOAT32 rounding; this includes codes3/4 and is not a normalized
// mouse fraction or wheel delta. Finally40D620 clamps ordered accumulator to[0,1], preserving NaN, and returns loaded FLOAT32 through ST0. No own units conversion, finite check,
// output pointer or input-state restoration; querying can consume press counts through451F70 and down-time through58B850, even for suppressed chat keys.
double __cdecl rf_input_binding_active_time_sum_clamped(int a1, int a2)
{
  int i; // [esp+Ch] [ebp-Ch]
  int v4; // [esp+10h] [ebp-8h] BYREF
  int v5; // [esp+14h] [ebp-4h]

  *(float *)&v4 = 0.0;
  if ( a2 >= *(_DWORD *)(a1 + 3596) )
    return 0.0;
  v5 = a1 + 28 * a2 + 12;
  if ( !rf_input_binding_poll_pressed_or_held(a1, a2, nullptr) )
    return 0.0;
  for ( i = 0; i < 2; ++i )
  {
    if ( *(__int16 *)(v5 + 2 * i + 20) >= 0 )
    {
      if ( rf_multiplayer_chat_active_byte_get() && rf_input_scan_code_is_chat_reserved(*(__int16 *)(v5 + 2 * i + 20)) )
        rf_input_query_down_time_fraction(*(__int16 *)(v5 + 2 * i + 20));
      else
        *(float *)&v4 = rf_input_query_down_time_fraction(*(__int16 *)(v5 + 2 * i + 20)) + *(float *)&v4;
    }
  }
  if ( *(__int16 *)(v5 + 24) >= 0 )
    *(float *)&v4 = (double)rf_mouse_button_snapshot_click_age(*(__int16 *)(v5 + 24)) + *(float *)&v4;
  rf_float_clamp_in_place((float *)&v4, 0.0, 1.0);
  return *(float *)&v4;
}

