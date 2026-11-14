// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005EE550 rf_ui_slider_initialize
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Args owner,x,y,w,h,horizontalBYTE,thumbLength,positionCount,id,flagsBYTE,raw base flag. Clears arrow pointers676/672. Flags bit1 reserves two square arrow buttons:horizontal x+=h+1,w-=2*h+2;vertical y+=w+1,h-=2*w+2. Initializes gadget type7. If bit1,allocates two1104-byte buttons unchecked,initializes and reparents:decrement676 at(-h-1,0) flags258 or(0,-w-1) flags66;increment672 at(w+1,0) flags514 or(0,h+1) flags130;id-1,raw1. Direction flags include repeat2. Sets orientation664 raw,thumb656=input,range648=positionCount,position652=0,pageStep660=1,state632=0,palette668=0x1CF75E4. Does NOT store flagsBYTE or implement bits4 Dot slider/8 No process;does not initialize scrollbar extra680. No extent/range/thumb/allocation guards;return incidental palette store.
int __thiscall rf_ui_slider_initialize(
        int this,
        int a2,
        int a3,
        int a4,
        int a5,
        int a6,
        char a7,
        int a8,
        int a9,
        int a10,
        char a11,
        char a12)
{
  int v13; // [esp+4h] [ebp-40h]
  int v14; // [esp+8h] [ebp-3Ch]
  int v15; // [esp+Ch] [ebp-38h]
  int v16; // [esp+10h] [ebp-34h]
  void *v18; // [esp+18h] [ebp-2Ch]
  void *v19; // [esp+20h] [ebp-24h]
  void *v20; // [esp+28h] [ebp-1Ch]
  void *v21; // [esp+30h] [ebp-14h]

  *(_DWORD *)(this + 676) = 0;
  *(_DWORD *)(this + 672) = 0;
  if ( (a11 & 1) != 0 )
  {
    if ( a7 )
    {
      a3 += a6 + 1;
      a5 -= 2 * a6 + 2;
    }
    else
    {
      a4 += a5 + 1;
      a6 -= 2 * a5 + 2;
    }
  }
  rf_ui_gadget_initialize(this, a2, 7, a3, a4, a5, a6, a10, a12);
  if ( (a11 & 1) != 0 )
  {
    if ( a7 )
    {
      v21 = operator new(0x450u);
      if ( v21 )
        v16 = rf_ui_button_construct((int)v21);
      else
        v16 = 0;
      *(_DWORD *)(this + 676) = v16;
      rf_ui_button_initialize_in_window(*(_DWORD *)(this + 676), a2, -a6 - 1, 0, a6, a6, -1, 258, 1);
      rf_ui_gadget_set_parent(*(_DWORD **)(this + 676), this);
      v20 = operator new(0x450u);
      if ( v20 )
        v15 = rf_ui_button_construct((int)v20);
      else
        v15 = 0;
      *(_DWORD *)(this + 672) = v15;
      rf_ui_button_initialize_in_window(*(_DWORD *)(this + 672), a2, a5 + 1, 0, a6, a6, -1, 514, 1);
      rf_ui_gadget_set_parent(*(_DWORD **)(this + 672), this);
    }
    else
    {
      v19 = operator new(0x450u);
      if ( v19 )
        v14 = rf_ui_button_construct((int)v19);
      else
        v14 = 0;
      *(_DWORD *)(this + 676) = v14;
      rf_ui_button_initialize_in_window(*(_DWORD *)(this + 676), a2, 0, -a5 - 1, a5, a5, -1, 66, 1);
      rf_ui_gadget_set_parent(*(_DWORD **)(this + 676), this);
      v18 = operator new(0x450u);
      if ( v18 )
        v13 = rf_ui_button_construct((int)v18);
      else
        v13 = 0;
      *(_DWORD *)(this + 672) = v13;
      rf_ui_button_initialize_in_window(*(_DWORD *)(this + 672), a2, 0, a6 + 1, a5, a5, -1, 130, 1);
      rf_ui_gadget_set_parent(*(_DWORD **)(this + 672), this);
    }
  }
  *(_BYTE *)(this + 664) = a7;
  *(_DWORD *)(this + 656) = a8;
  *(_DWORD *)(this + 648) = a9;
  *(_DWORD *)(this + 652) = 0;
  *(_DWORD *)(this + 660) = 1;
  *(_DWORD *)(this + 632) = 0;
  *(_DWORD *)(this + 668) = byte_1CF75E4;
  return this;
}

