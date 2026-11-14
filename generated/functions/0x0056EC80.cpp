// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056EC80 rf_console_draw_window_gdi_when_dirty
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, console dispatch/lexing, history/ring layout, input/render paths, context-save calling convention and stream receivers): No args.300ms deadline expiration toggles cursor byte180930D and increments dirty counter. If dirty nonzero clears it BEFORE attempting HWND/GetDC;missing window/DC therefore consumes dirty request. Uses client rect,SetTextAlign8,stock brush4,draws bottom-up with4px left margin. Live mode starts prompt (optional underscore cursor),scroll mode starts marker,then traverses500 ring lines backward before blank filler. Splits bracket-delimited chunks,recognizes case-insensitive [$Red],[$Blue],[$White] only outside prompt,sets COLORREF C0,C00000,C0C0C0;other chunks measured and TextOutA-drawn with current color. Resets gray808080/black per output line;line height is maximum measured chunk height,no
// horizontal wrap. Fills left/right margins and2px bottom strip. Releases acquired DC. Fixed local string buffers receive unchecked copies;stored record colors are not used here. EAX incidental deadline/window/API result.
int rf_console_draw_window_gdi_when_dirty()
{
  int result; // eax
  HBRUSH StockObject; // eax
  char v2; // cl
  char v3; // cl
  char v4; // cl
  char v5; // dl
  HBRUSH v6; // eax
  HBRUSH v7; // eax
  CHAR *v8; // [esp+3Ch] [ebp-CFCh]
  char *v9; // [esp+40h] [ebp-CF8h]
  CHAR *p_String; // [esp+4Ch] [ebp-CECh]
  char *v11; // [esp+50h] [ebp-CE8h]
  CHAR *v12; // [esp+5Ch] [ebp-CDCh]
  char *v13; // [esp+60h] [ebp-CD8h]
  char v14; // [esp+7Fh] [ebp-CB9h]
  _WORD *v15; // [esp+80h] [ebp-CB8h]
  _BYTE *v16; // [esp+8Ch] [ebp-CACh]
  char *v17; // [esp+90h] [ebp-CA8h]
  struct tagSIZE psizl; // [esp+94h] [ebp-CA4h] BYREF
  char v19; // [esp+9Fh] [ebp-C99h]
  unsigned int v20; // [esp+A0h] [ebp-C98h]
  char v21; // [esp+A7h] [ebp-C91h]
  CHAR String; // [esp+A8h] [ebp-C90h] BYREF
  _BYTE v23[3]; // [esp+A9h] [ebp-C8Fh] BYREF
  COLORREF color; // [esp+4ACh] [ebp-88Ch]
  char v25; // [esp+4B3h] [ebp-885h]
  char *v26; // [esp+4B4h] [ebp-884h] BYREF
  _BYTE v27[1028]; // [esp+4B8h] [ebp-880h] BYREF
  LONG cy; // [esp+8BCh] [ebp-47Ch]
  char v29; // [esp+8C0h] [ebp-478h] BYREF
  _BYTE v30[1027]; // [esp+8C1h] [ebp-477h]
  char v31; // [esp+CCBh] [ebp-6Dh]
  int x; // [esp+CCCh] [ebp-6Ch]
  COLORREF v33; // [esp+CD0h] [ebp-68h]
  char *v34; // [esp+CD4h] [ebp-64h]
  HDC hdc; // [esp+CD8h] [ebp-60h]
  struct tagRECT Rect; // [esp+CDCh] [ebp-5Ch] BYREF
  RECT v37; // [esp+CECh] [ebp-4Ch] BYREF
  char v38; // [esp+CFFh] [ebp-39h]
  int v39; // [esp+D00h] [ebp-38h]
  char v40; // [esp+D07h] [ebp-31h]
  int v41; // [esp+D08h] [ebp-30h]
  char v42; // [esp+D0Fh] [ebp-29h]
  HWND hWnd; // [esp+D10h] [ebp-28h]
  RECT rc; // [esp+D14h] [ebp-24h] BYREF
  RECT v45; // [esp+D24h] [ebp-14h] BYREF
  int y; // [esp+D34h] [ebp-4h]

  result = rf_clock_deadline_has_elapsed_half_period(&unk_180A5A8);
  if ( (unsigned __int8)result == 1 )
  {
    result = (int)rf_clock_deadline_set_wrapped_offset(&unk_180A5A8, 300);
    ++unk_180A494;
    byte_180930D[0] = byte_180930D[0] != 1;
  }
  if ( unk_180A494 )
  {
    unk_180A494 = 0;
    result = (int)rf_window_get_main_hwnd();
    hWnd = (HWND)result;
    if ( result )
    {
      result = (int)GetDC(hWnd);
      hdc = (HDC)result;
      if ( result )
      {
        GetClientRect(hWnd, &Rect);
        SetTextAlign(hdc, 8u);
        v42 = 0;
        v40 = 0;
        v38 = 0;
        if ( dword_1809ABC < 0 )
        {
          v40 = 1;
          v39 = dword_1809920 - 1;
          if ( dword_1809920 - 1 < 0 )
            v39 = 499;
        }
        else
        {
          v39 = dword_1809ABC;
          v42 = 1;
        }
        v41 = v39;
        y = Rect.bottom;
        rc.top = Rect.bottom - 2;
        rc.bottom = Rect.bottom;
        rc.left = Rect.left;
        rc.right = Rect.right;
        StockObject = (HBRUSH)GetStockObject(4);
        FillRect(hdc, &rc, StockObject);
        for ( y -= 2; y >= Rect.top; y -= cy )
        {
          v31 = 0;
          v26 = nullptr;
          if ( v40 )
          {
            v40 = 0;
            v17 = (char *)&unk_180A4A0;
            v16 = v27;
            do
            {
              v2 = *v17;
              *v16++ = *v17++;
            }
            while ( v2 );
            if ( byte_180930D[0] == 1 )
            {
              v15 = (_WORD *)((char *)&v26 + 3);
              do
              {
                v14 = *((_BYTE *)v15 + 1);
                v15 = (_WORD *)((char *)v15 + 1);
              }
              while ( v14 );
              *v15 = 95;
            }
            v26 = v27;
            v31 = 1;
          }
          else if ( v42 )
          {
            v42 = 0;
            v26 = (char *)unk_88E28C;
          }
          else if ( v38 )
          {
            v26 = " ";
          }
          else
          {
            v26 = &unk_180A5B0[261 * v39--];
            if ( v39 < 0 )
              v39 = 499;
            if ( v39 == v41 )
              v38 = 1;
          }
          cy = 0;
          x = 4;
          color = (COLORREF)&unk_808080;
          v33 = 0;
          SetTextColor(hdc, (COLORREF)&unk_808080);
          SetBkColor(hdc, v33);
          v29 = 0;
          v34 = v26;
          v25 = 0;
          while ( !v25 )
          {
            String = 0;
            v21 = *v34++;
            v20 = strlen(&v29);
            if ( v21 )
            {
              if ( v21 == 91 )
              {
                v11 = &v29;
                p_String = &String;
                do
                {
                  v4 = *v11;
                  *p_String++ = *v11++;
                }
                while ( v4 );
                v29 = v21;
                v30[0] = 0;
              }
              else if ( v21 == 93 )
              {
                v30[v20 - 1] = 93;
                v30[v20] = 0;
                v9 = &v29;
                v8 = &String;
                do
                {
                  v5 = *v9;
                  *v8++ = *v9++;
                }
                while ( v5 );
                v29 = 0;
              }
              else
              {
                v30[v20 - 1] = v21;
                v30[v20] = 0;
              }
            }
            else
            {
              v25 = 1;
              v13 = &v29;
              v12 = &String;
              do
              {
                v3 = *v13;
                *v12++ = *v13++;
              }
              while ( v3 );
            }
            if ( &v23[strlen(&String)] != v23 )
            {
              v19 = 0;
              if ( !v31 )
              {
                if ( !_stricmp(&String, "[$Red]") )
                {
                  SetTextColor(hdc, 0xC0u);
                  SetBkColor(hdc, v33);
                  v19 = 1;
                }
                else if ( !_stricmp(&String, "[$Blue]") )
                {
                  SetTextColor(hdc, (COLORREF)&unk_C00000);
                  SetBkColor(hdc, v33);
                  v19 = 1;
                }
                else if ( !_stricmp(&String, "[$White]") )
                {
                  SetTextColor(hdc, (COLORREF)&unk_C0C0C0);
                  SetBkColor(hdc, v33);
                  v19 = 1;
                }
              }
              if ( !v19 )
              {
                GetTextExtentPoint32A(hdc, &String, strlen(&String), &psizl);
                TextOutA(hdc, x, y, &String, strlen(&String));
                if ( psizl.cy > cy )
                  cy = psizl.cy;
                x += psizl.cx;
              }
            }
          }
          v45.top = y - cy;
          v45.bottom = y;
          v45.left = 0;
          v45.right = 4;
          v6 = (HBRUSH)GetStockObject(4);
          FillRect(hdc, &v45, v6);
          v37.top = y - cy;
          v37.bottom = y;
          v37.left = x;
          v37.right = Rect.right;
          if ( Rect.right > x )
          {
            v7 = (HBRUSH)GetStockObject(4);
            FillRect(hdc, &v37, v7);
          }
        }
        return ReleaseDC(hWnd, hdc);
      }
    }
  }
  return result;
}

