// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0049D230 rf_multiplayer_countdown_tick_and_render
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, item/cutscene/HUD caller chains, original float constants, RFString ownership and false SDK classifications
// and native signed/x87/stack/callback ABI): Native cdecl LOW-BYTE drawDigits parameter, caller-cleaned stack slot; no pointer dereference. Former std::locale::facet pointer
// type/library classification corrected. Only runs when hours77FE40==0 AND minutes77FE44==0. Signed seconds77FE48>=55 and latch77FE3B==0 ->sound81(0,0.0,1.0),latch1; seconds26..30
// and latch77FE3A==0 ->sound82,latch1. Seconds1..10 ->sound(seconds+67) once via BYTE77FE2F[seconds]. If last-secondDWORD662938 equals seconds, float
// alpha66293C=round32(alpha-frameDelta*500), ordered negative clamps0; changed second resets255. Sounds/alpha/last-second update run EVEN drawDigits==0. Nonzero low byte draws white
// with trunc(alpha), formats decimal seconds into owned RFString, measures bigfont662940, draws aligned(mode1,x=viewportWidth/2,y=viewportHeight/2+73), destroys temporary. Updates
// last-second after optional drawing. No timer recomputation, new-second crossing recovery or rendering beyond10..1; float unordered comparisons do not clamp NaN.
void __cdecl rf_multiplayer_countdown_tick_and_render(unsigned __int8 a1)
{
  unsigned __int8 *v1; // eax
  int viewport_width; // eax
  int v3; // [esp-8h] [ebp-30h]
  unsigned __int8 *v4; // [esp-4h] [ebp-2Ch]
  int v5; // [esp+0h] [ebp-28h]
  int v6; // [esp+4h] [ebp-24h]
  int v7; // [esp+4h] [ebp-24h]
  int v8; // [esp+Ch] [ebp-1Ch] BYREF
  int v9; // [esp+10h] [ebp-18h] BYREF
  _DWORD v10[2]; // [esp+14h] [ebp-14h] BYREF
  int v11; // [esp+24h] [ebp-4h]

  if ( !rf_multiplayer_time_left_hours && !rf_multiplayer_time_left_minutes )
  {
    if ( rf_multiplayer_time_left_seconds >= 55 && !unk_77FE3B )
    {
      rf_gamesound_play_event(81, 0, 0.0, 1.0);
      unk_77FE3B = 1;
    }
    if ( rf_multiplayer_time_left_seconds <= 30 && rf_multiplayer_time_left_seconds > 25 && !unk_77FE3A )
    {
      rf_gamesound_play_event(82, 0, 0.0, 1.0);
      unk_77FE3A = 1;
    }
    if ( rf_multiplayer_time_left_seconds <= 10 && rf_multiplayer_time_left_seconds > 0 )
    {
      if ( !unk_77FE2F[rf_multiplayer_time_left_seconds] )
      {
        rf_gamesound_play_event(rf_multiplayer_time_left_seconds + 67, 0, 0.0, 1.0);
        unk_77FE2F[rf_multiplayer_time_left_seconds] = 1;
      }
      if ( dword_662938 == rf_multiplayer_time_left_seconds )
      {
        flt_66293C = flt_66293C - rf_frame_delta_seconds * 500.0;
        if ( flt_66293C < 0.0 )
          flt_66293C = 0.0;
      }
      else
      {
        flt_66293C = 255.0;
      }
      if ( a1 )
      {
        v9 = 0;
        v8 = 0;
        rf_render_color_set_rgba8(255, 255, 255, (int)flt_66293C);
        rf_string_format_int32_decimal(v10, rf_multiplayer_time_left_seconds);
        v11 = 0;
        v6 = dword_662940;
        v1 = (unsigned __int8 *)rf_string_object_c_str_or_empty(v10);
        rf_font_measure_text_extent(&v9, &v8, v1, -1, v6);
        v7 = dword_182ABBC;
        v5 = dword_662940;
        v4 = (unsigned __int8 *)rf_string_object_c_str_or_empty(v10);
        v3 = rf_renderer_get_viewport_height() / 2 + 73;
        viewport_width = rf_renderer_get_viewport_width();
        rf_font_draw_text_aligned(1, viewport_width / 2, v3, v4, v5, v7);
        v11 = -1;
        rf_string_destroy_buffer(v10);
      }
      dword_662938 = rf_multiplayer_time_left_seconds;
    }
  }
}

