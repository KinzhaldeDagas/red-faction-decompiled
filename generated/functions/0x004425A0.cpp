// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004425A0 rf_debug_draw_frame_history_bars
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): Cdecl(signed screenX,screenY); saved int result is loop residue EAX16 after normal completion. Capture
// initial history index DWORD663ED0 once, add10 to local Y with32-bit wrap. Draw baseline572750(F32(signedX),F32(signedWrappedY-30.0),F32(signedX+80.0),sameY,DWORD187CC5C), with
// explicit FLOAT32 coordinate stores. Then EXACT16 iterations (signed counter0..<16): read history FLOAT18092A0[index] using raw initial/current index; compute
// reciprocal1/(sample+sample) in x87 then FLOAT32-round before567830; signed min40D680(convertedInteger,30) caps only above.
// Fill572CD0(currentX,wrappedY-height,4,height,DWORD182ABB8), even zero/negative height. Advance history index by32-bit wrapped+1 followed by SIGNED remainder16 (negative remainder
// is retained), and X by5 with32-bit wrap. Initial index is not normalized or sample-count-checked; no denominator/finite/negative/NULL validation or lower height clamp. Signed
// rectangle helper may normalize negative extents rather than decline them. Does not set/restore color, update global index/history or validate draw results; all16 delegate attempts
// occur on normal execution.
void __cdecl rf_debug_draw_frame_history_bars(int a1, int a2)
{
  int v2; // eax
  float v3; // [esp+0h] [ebp-30h]
  float v4; // [esp+14h] [ebp-1Ch]
  float v5; // [esp+1Ch] [ebp-14h]
  float v6; // [esp+20h] [ebp-10h]
  int v7; // [esp+24h] [ebp-Ch]
  int v8; // [esp+28h] [ebp-8h]
  int i; // [esp+2Ch] [ebp-4h]
  int v10; // [esp+3Ch] [ebp+Ch]

  v8 = dword_663ED0;
  v10 = a2 + 10;
  v6 = (double)v10 - 30.0;
  v5 = (double)a1 + 80.0;
  v3 = (float)a1;
  rf_renderer_draw_screen_line_clipped(v3, v6, v5, v6, dword_187CC5C);
  for ( i = 0; i < 16; ++i )
  {
    v4 = 1.0 / (flt_18092A0[v8] + flt_18092A0[v8]);
    v2 = rf_round_nonnegative_float_to_int(v4);
    v7 = rf_int_min_signed(v2, 30);
    rf_renderer_fill_rectangle_clipped(a1, v10 - v7, 4, v7, dword_182ABB8);
    v8 = (v8 + 1) % 16;
    a1 += 5;
  }
}

