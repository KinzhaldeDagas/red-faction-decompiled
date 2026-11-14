// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00452ED0 rf_credits_render_bitmap_fade_and_newline_text
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, sequence panel and input/binding natives, credits/endgame parsing and Extras-menu X-motion/lifecycle, native
// callback and text-draw argument roles and native signed/x87/stack/callback ABI): No arguments; normal terminator return is fullEAX0, not aggregate renderer status (last global byte
// load is NUL, normal605EE4 cookie check preserves EAX). Fade-outBYTE6EFEB0 ANYnonzero has precedence over fade-inBYTE6EFEB1: setRGBA(0,0,0,255), clear-color backend571C40, then
// fade6EFEA4=F32(oldFade-frameFLOATseconds/DOUBLE1). Only ORDERED fade<0 stores+0 and clears fade-outBYTE; equality0 and NaN retain flag. Otherwise if fade-inANYnonzero,
// fade=F32(oldFade+delta/1); only ORDERED fade>1 stores1 and clears fade-in; equality1/NaN retain flag. Fade-out never clears fade-in; both can remain set. Neither branch clamps the
// opposite endpoint. For either active branch compute x87 fade*DOUBLE185, temporarily set rounding-control bits0xC00 for FISTP signed32 truncation, restore original control word,
// take LOWBYTE integer and grey=LOWBYTE(255-thatByte). This wraps rather than clamps; masked invalid FISTP produces integer-indefinite0x80000000/lowbyte0. If neither phase active
// grey=70 without changing fade.  CallRGBA(grey,grey,grey,EAXfrom native605F00 conversion of current fade*DOUBLE255), with no caller finite/range clamp. Always572180 blits raw
// bitmap6EFEA8, destination(0,0,cached viewport width6EFEAC,height6EFE9C),source(0,0,cached bitmap width6EFE98,height6EFEA0),flipBYTE0,0,modeCURRENT187CC7C. No bitmap sign/success
// guard or cached-dimension refresh. Next convert current scrollY6EFEB4 through605F00 into signed32 y, select font663048 via58C090 and capture returned font height. Scan LIVE global
// credits bytes6EFEC0 from index0 to firstNUL, building unbounded stack line buffer. Ordinary bytes append; LF writesNUL at current line length, then only SIGNEDy>0 draws it. No
// y<screenHeight/capacity/source-length check, and a final unterminated line is discarded at globalNUL.  For each drawn LF line, query physical height TWICE: A=F32(abs(exact
// signedy-DOUBLE0.5*SIGNED firstHeight)); promoteA toF64; B=F32(DOUBLE0.5*SIGNED secondHeight). Set f=F32(A/B), then f=F32(1-f). No zero-height/finite guard or screen-height
// snapshot. Compute fade*DOUBLE255*f without an intervening F32 store, FISTP signed32 with temporary truncation-control/restoration, pass ZERO-EXTENDED LOWBYTE result as alpha with
// RGB255. Offscreen-below-bottom/negative f wraps alpha rather than clamping; NaN/invalid conversion inherits x87 masked-indefinite behavior.
// Draw58CFC0(centerX0x8000,y,line,fontCURRENT663048,modeCURRENT182ABBC). After EACH LF even undrawn, y+=capturedFontHeight with32-bit wrap, clear first local byte, reset local
// length0; global scan index increments. Globals/font/color/viewport are not restored, and render helpers can mutate state before later rereads. No own pause/input flag,
// clipping-to-text-rectangle or rollback.
int rf_credits_render_bitmap_fade_and_newline_text()
{
  int result; // eax
  float v1; // [esp+Ch] [ebp-154h]
  float v2; // [esp+1Ch] [ebp-144h]
  unsigned __int8 v3; // [esp+43h] [ebp-11Dh]
  int height_select_current; // [esp+44h] [ebp-11Ch]
  float v5; // [esp+48h] [ebp-118h]
  float v6; // [esp+48h] [ebp-118h]
  int v7; // [esp+4Ch] [ebp-114h]
  unsigned __int8 v8[260]; // [esp+50h] [ebp-110h] BYREF
  int v9; // [esp+158h] [ebp-8h]
  int v10; // [esp+15Ch] [ebp-4h]

  if ( unk_6EFEB0 )
  {
    rf_render_color_set_rgba8(0, 0, 0, 255);
    rf_renderer_clear_color_backend_dispatch();
    unk_6EFEA4 = unk_6EFEA4 - rf_frame_delta_seconds / 1.0;
    if ( unk_6EFEA4 < 0.0 )
    {
      unk_6EFEA4 = 0.0;
      unk_6EFEB0 = 0;
    }
    v3 = -1 - (int)(unk_6EFEA4 * 185.0);
  }
  else if ( unk_6EFEB1 )
  {
    unk_6EFEA4 = rf_frame_delta_seconds / 1.0 + unk_6EFEA4;
    if ( unk_6EFEA4 > 1.0 )
    {
      unk_6EFEA4 = 1.0;
      unk_6EFEB1 = 0;
    }
    v3 = -1 - (int)(unk_6EFEA4 * 185.0);
  }
  else
  {
    v3 = 70;
  }
  rf_render_color_set_rgba8(v3, v3, v3, (int)(unk_6EFEA4 * 255.0));
  rf_bitmap_blit_subrectangle_backend_dispatch(
    dword_6EFEA8,
    0,
    0,
    unk_6EFEAC,
    dword_6EFE9C,
    0,
    0,
    dword_6EFE98,
    dword_6EFEA0,
    0,
    0,
    dword_187CC7C);
  v9 = (int)unk_6EFEB4;
  height_select_current = rf_font_get_height_select_current(dword_663048);
  v7 = 0;
  v10 = 0;
  v8[0] = 0;
  while ( 1 )
  {
    result = *((char *)&dword_6EFEBC[1] + v7);
    if ( !*((_BYTE *)&dword_6EFEBC[1] + v7) )
      break;
    if ( *((_BYTE *)&dword_6EFEBC[1] + v7) == 10 )
    {
      v8[v10++] = 0;
      if ( v9 > 0 )
      {
        v2 = fabs((double)v9 - (double)rf_renderer_get_physical_screen_height() * 0.5);
        v1 = (double)rf_renderer_get_physical_screen_height() * 0.5;
        v5 = v2 / v1;
        v6 = 1.0 - v5;
        rf_render_color_set_rgba8(255, 255, 255, (unsigned __int8)(int)(unk_6EFEA4 * 255.0 * v6));
        rf_font_draw_text_screen(0x8000, v9, v8, dword_663048, dword_182ABBC);
      }
      v9 += height_select_current;
      v8[0] = 0;
      v10 = 0;
    }
    else
    {
      v8[v10++] = *((_BYTE *)&dword_6EFEBC[1] + v7);
    }
    ++v7;
  }
  return result;
}

