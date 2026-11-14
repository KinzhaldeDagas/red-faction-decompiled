// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00442360 rf_debug_draw_frame_timing_text_and_history
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): Cdecl(signed screenX,screenY). First56D3C0(&min,&max) obtains biased history extrema (initial1/0, limited
// signed sample count), then sets current RGBA to255,255,255,255. All text uses unbounded sprintf into32-byte stack Buffer and58CFC0(x,y,Buffer,-1,DWORD182ABBC). BYTE88E446 ANY
// nonzero draws "60/%d" using round567830(F32(60.0/FLOAT663ECC)); zero instead draws "%.2f" from FLOAT663ECC promoted to outgoing DOUBLE. Both advance local X by45 with32-bit wrap.
// BYTE6E6ACA ANY nonzero then calls4425A0(advancedX,y), skips remaining text and forwards its incidental result. Otherwise nonzero88E446 computes rounded F32(60/min) FIRST but
// formats "[%d-%d]" in order round(60/max),round(60/min), drawing at advancedX. Zero88E446 formats "[%.2f-%.2f]" in order1/max,1/min, reciprocals rounded only to outgoing DOUBLE
// rather than an extra FLOAT32; draws at advancedX. Only this latter branch additionally calls567490(DWORD6663C8), explicitly rounds returnedST0 toFLOAT32, divides by frame-delta
// FLOAT663EC8 without another FLOAT32 store, formats outgoingDOUBLE "[%.2f]", draws at originalX-75 (advancedX-120). No zero/finite/sign validation before divisions/conversions,
// sample-count guard, bounded formatting or color restoration. Native saved int result follows final draw/graph residue, not a consistent status; common tail performs security-cookie
// validation.
int __cdecl rf_debug_draw_frame_timing_text_and_history(int a1, int a2)
{
  int v2; // eax
  int v4; // eax
  int v5; // [esp+Ch] [ebp-40h]
  float v6; // [esp+10h] [ebp-3Ch]
  float v7; // [esp+14h] [ebp-38h]
  float v8; // [esp+18h] [ebp-34h]
  float v9; // [esp+1Ch] [ebp-30h]
  float v10; // [esp+20h] [ebp-2Ch] BYREF
  char Buffer[32]; // [esp+24h] [ebp-28h] BYREF
  float v12; // [esp+48h] [ebp-4h] BYREF
  int v13; // [esp+54h] [ebp+8h]

  rf_frame_clock_history_get_biased_min_max(&v12, &v10);
  rf_render_color_set_rgba8(255, 255, 255, 255);
  if ( unk_88E446 )
  {
    v8 = 60.0 / flt_663ECC;
    v2 = rf_round_nonnegative_float_to_int(v8);
    sprintf(Buffer, "60/%d", v2);
    rf_font_draw_text_screen(a1, a2, (unsigned __int8 *)Buffer, -1, unk_182ABBC);
    v13 = a1 + 45;
    if ( unk_6E6ACA )
      return rf_debug_draw_frame_history_bars(v13, a2);
    v7 = 60.0 / v12;
    v5 = rf_round_nonnegative_float_to_int(v7);
    v6 = 60.0 / v10;
    v4 = rf_round_nonnegative_float_to_int(v6);
    sprintf(Buffer, "[%d-%d]", v4, v5);
    return rf_font_draw_text_screen(v13, a2, (unsigned __int8 *)Buffer, -1, unk_182ABBC);
  }
  else
  {
    sprintf(Buffer, "%.2f", flt_663ECC);
    rf_font_draw_text_screen(a1, a2, (unsigned __int8 *)Buffer, -1, unk_182ABBC);
    v13 = a1 + 45;
    if ( unk_6E6ACA )
      return rf_debug_draw_frame_history_bars(v13, a2);
    sprintf(Buffer, "[%.2f-%.2f]", 1.0 / v10, 1.0 / v12);
    rf_font_draw_text_screen(v13, a2, (unsigned __int8 *)Buffer, -1, unk_182ABBC);
    v9 = rf_tsc_delta_to_seconds_calibrated(dword_6663C8);
    sprintf(Buffer, "[%.2f]", v9 / rf_frame_delta_seconds);
    return rf_font_draw_text_screen(v13 - 120, a2, (unsigned __int8 *)Buffer, -1, unk_182ABBC);
  }
}

