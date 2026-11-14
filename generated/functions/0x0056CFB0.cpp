// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056CFB0 rf_frame_clock_update_delta_and_history
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, ray candidate planes, normalized-direction sphere queries, frame timing, pause depths and x87 return flow): cdecl no args. Lazy-calls56CF30 once when byte18092F0==0,then sets byte1. Nonzero signed pause-depth18092F4 skips ALL sampling,history,game/unpaused-clock advance and accumulation. Samples5673A0(1000000) as signed32 QPC-derived microseconds. If sample>=last uses signed subtraction;otherwise uses sample itself,and if negative uses trunc(previous EFFECTIVE delta*1e6). Stores raw float seconds663EC4 and initially copies to effective663EC8. At most TWO samples: if first delta<min663ED8,optionally Sleep(trunc((min-delta)*1000)) only when shortfall<.5s,then resample;second short sample forces effective=min and skips max-clamp branch without waiting again,so minimum is a reported-duration floor,not guaranteed elapsed
// wall time. A sufficiently long sample is clamped to max663EDC. Last sample18092E8 updated. Initializes16 history slots only if index==-1,subtracts overwritten duration/adds effective duration BEFORE divisor,stores slot,advances signed modulo16. FPS663ECC=0 when sum==0,else(min(SIGNED frameCounter,16))/sum,using counter BEFORE increment,so first initialized frame FPS0 and warmup numerator one less than stored-duration count. Then divides effective delta by unchecked scalar663ED4,increments32bit frameCounter,converts scaled delta*1000 to signed integer by truncation and calls55EE80 advance game/unpaused millisecond clocks. Adds same integer to18092E4 ONLY if accumulator-suspend depth18092F8==0. Discarded fractional milliseconds do not carry. No own clock-ready/divisor/limit/overflow/finite guard; a not-ready helper returning0 can still reach the forced minimum and advance clocks.
// Pause-counter underflow remains nonzero and suppresses updates. Raw delta is unscaled/unclamped; FPS uses limited but unscaled durations.
void rf_frame_clock_update_delta_and_history()
{
  double v0; // st7
  int i; // [esp+0h] [ebp-18h]
  float v2; // [esp+4h] [ebp-14h]
  int v3; // [esp+8h] [ebp-10h]
  int v4; // [esp+Ch] [ebp-Ch]
  int v5; // [esp+10h] [ebp-8h]
  int v6; // [esp+14h] [ebp-4h]

  if ( !unk_18092F0 )
  {
    rf_frame_clock_reset_defaults();
    unk_18092F0 = 1;
  }
  if ( !dword_18092F4 )
  {
    v3 = 0;
    while ( 1 )
    {
      ++v3;
      v5 = rf_performance_clock_elapsed_scaled(1000000);
      if ( v5 >= dword_18092E8 )
      {
        v4 = v5 - dword_18092E8;
      }
      else
      {
        v4 = v5;
        if ( v5 < 0 )
          v4 = (int)(rf_frame_delta_seconds * 1000000.0);
      }
      flt_663EC4 = (double)v4 / 1000000.0;
      rf_frame_delta_seconds = flt_663EC4;
      if ( flt_663ED8 <= (double)flt_663EC4 )
        break;
      v2 = flt_663ED8 - rf_frame_delta_seconds;
      if ( v3 != 1 )
      {
        rf_frame_delta_seconds = flt_663ED8;
        goto LABEL_18;
      }
      if ( v2 < 0.5 )
        rf_thread_sleep_milliseconds((int)(v2 * 1000.0));
    }
    if ( flt_663EDC < (double)rf_frame_delta_seconds )
      rf_frame_delta_seconds = flt_663EDC;
LABEL_18:
    dword_18092E8 = v5;
    if ( dword_663ED0 == -1 )
    {
      for ( i = 0; i < 16; ++i )
        flt_18092A0[i] = 0.0;
      unk_18092EC = 0.0;
      dword_663ED0 = 0;
    }
    unk_18092EC = unk_18092EC - flt_18092A0[dword_663ED0];
    unk_18092EC = unk_18092EC + rf_frame_delta_seconds;
    flt_18092A0[dword_663ED0] = rf_frame_delta_seconds;
    dword_663ED0 = (dword_663ED0 + 1) % 16;
    if ( unk_18092EC == 0.0 )
    {
      flt_663ECC = 0.0;
    }
    else
    {
      if ( SLODWORD(flt_18092A0[16]) < 16 )
        v0 = (double)SLODWORD(flt_18092A0[16]) / unk_18092EC;
      else
        v0 = 16.0 / unk_18092EC;
      flt_663ECC = v0;
    }
    rf_frame_delta_seconds = rf_frame_delta_seconds / flt_663ED4;
    ++LODWORD(flt_18092A0[16]);
    v6 = (int)(rf_frame_delta_seconds * 1000.0);
    rf_advance_game_and_unpaused_clocks_milliseconds(v6);
    if ( !unk_18092F8 )
      unk_18092E4 += v6;
  }
}

