// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00451180 rf_direction_sequence6EFE18_consume_input
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, sequence panel and input/binding natives, credits/endgame parsing and Extras-menu X-motion/lifecycle, native
// callback and text-draw argument roles and native signed/x87/stack/callback ABI): No arguments, void/shared panel state. ANY nonzero pause BYTE6EFE78 exits before all key/mouse
// queries. Otherwise clear four local direction flags, consume keyboard press counters in short-circuit order scan200(U),203(L),208(D),205(R): ONLY fullEAX EXACT1 sets a flag; other
// returned counts are consumed/discarded and processing continues to next key. A successful earlier key leaves later counters UNREAD. Then independently test mouse button0
// press-count predicate ANY nonzero; this predicate does NOT consume the mouse count. On admission58AB60 writes local signed X/Y plus cumulative WHEEL/Z snapshot into global193A03C;
// return ignored. Test four FLOAT rectangle groups in order U,L,D,R using FILD signed integer coordinates and STRICT ORDERED interior comparisons, edges/NaNs reject: U
// minX40/maxX44/minY38/maxY3C, L60/64/58/5C, D50/54/48/4C, R70/74/68/6C, all listed suffix offsets are HEX from0x6EFE00. Only first mouse hit sets its corresponding flag; existing
// keyboard flags are NOT cleared. Final chosen direction priority is again U,L,D,R, so an earlier keyboard flag can override a later-direction mouse hit. No direction returns without
// sequence/sound mutation (wheel snapshot may already have changed). Read unchecked 6EFE18[DWORD6EFDA0], compare selected code U0/L2/D3/R1. Match increments shared cursor6EFDA0
// with32-bit wrap THEN568050(event52,group0,FLOAT0,FLOAT1). Mismatch writes cursor0 THEN same sound helper event53. No own expected-table length/completion/difficulty/negative-index
// check, success/failure latch, timer update, sound-result gate or rollback. Button count is not reset here, and both sequence variants share cursor/pause/rectangles. Native layouts
// of450E00 and451180 are instruction-identical after call relocation except four expected-table operands; every paired instruction/callee was compared. Return registers are
// incidental.
void rf_direction_sequence6EFE18_consume_input()
{
  int v0; // [esp+8h] [ebp-Ch] BYREF
  int v1; // [esp+Ch] [ebp-8h] BYREF
  char v2; // [esp+10h] [ebp-4h]
  char v3; // [esp+11h] [ebp-3h]
  char v4; // [esp+12h] [ebp-2h]
  bool v5; // [esp+13h] [ebp-1h]

  if ( !unk_6EFE78 )
  {
    v2 = 0;
    v3 = 0;
    v4 = 0;
    v5 = 0;
    if ( rf_input_take_press_count(0xC8u) == 1 )
    {
      v2 = 1;
    }
    else if ( rf_input_take_press_count(0xCBu) == 1 )
    {
      v4 = 1;
    }
    else if ( rf_input_take_press_count(0xD0u) == 1 )
    {
      v3 = 1;
    }
    else
    {
      v5 = rf_input_take_press_count(0xCDu) == 1;
    }
    if ( rf_mouse_button_has_press_count(0) )
    {
      rf_mouse_get_absolute_state(&v0, &v1, &unk_193A03C);
      if ( unk_6EFE44 <= (double)v0 || unk_6EFE40 >= (double)v0 || unk_6EFE38 >= (double)v1 || unk_6EFE3C <= (double)v1 )
      {
        if ( unk_6EFE64 <= (double)v0
          || unk_6EFE60 >= (double)v0
          || unk_6EFE58 >= (double)v1
          || unk_6EFE5C <= (double)v1 )
        {
          if ( unk_6EFE54 <= (double)v0
            || unk_6EFE50 >= (double)v0
            || unk_6EFE48 >= (double)v1
            || unk_6EFE4C <= (double)v1 )
          {
            if ( unk_6EFE74 > (double)v0
              && unk_6EFE70 < (double)v0
              && unk_6EFE68 < (double)v1
              && unk_6EFE6C > (double)v1 )
            {
              v5 = 1;
            }
          }
          else
          {
            v3 = 1;
          }
        }
        else
        {
          v4 = 1;
        }
      }
      else
      {
        v2 = 1;
      }
    }
    if ( v2 )
    {
      if ( !dword_6EFE18[dword_6EFDA0] )
        goto LABEL_42;
    }
    else if ( v4 )
    {
      if ( dword_6EFE18[dword_6EFDA0] == 2 )
        goto LABEL_42;
    }
    else if ( v3 )
    {
      if ( dword_6EFE18[dword_6EFDA0] == 3 )
      {
LABEL_42:
        ++dword_6EFDA0;
        rf_gamesound_play_event(52, 0, 0.0, 1.0);
        return;
      }
    }
    else
    {
      if ( !v5 )
        return;
      if ( dword_6EFE18[dword_6EFDA0] == 1 )
        goto LABEL_42;
    }
    dword_6EFDA0 = 0;
    rf_gamesound_play_event(53, 0, 0.0, 1.0);
  }
}

