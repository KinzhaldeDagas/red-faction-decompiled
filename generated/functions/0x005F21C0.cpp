// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F21C0 rf_ui_checkbox_initialize
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Arguments owner,x,y,boxW,boxH,label,labelDX,labelDY,font,checkedBYTE,id,raw base flag. Calls text measure(width,height,label,font,-1):font argument is passed as signed MAX BYTES,while measurement font is default-1. Nonnegative font IDs truncate measured text to that many bytes;negative measures full label. Initializes gadget type4,width=measuredW+labelDX+boxW,height=max(boxH,labelDY+measuredH). Stores checked628 raw,boxW632,boxH636,unbounded label copy640,font896,labelDX900,labelDY904,bitmap916/920/924/928=-1,palette912=0x1CF7BA0. Does not reset visual state908. Returns this;no capacity or negative-dimension guards.
int __thiscall rf_ui_checkbox_initialize(
        int this,
        int a2,
        int a3,
        int a4,
        int a5,
        int a6,
        unsigned __int8 *a7,
        int a8,
        int a9,
        int a10,
        char a11,
        int a12,
        char a13)
{
  unsigned __int8 v13; // cl
  _BYTE *v15; // [esp+8h] [ebp-20h]
  unsigned __int8 *v16; // [esp+Ch] [ebp-1Ch]
  int v17; // [esp+10h] [ebp-18h]
  int v19; // [esp+20h] [ebp-8h] BYREF
  int v20; // [esp+24h] [ebp-4h] BYREF

  rf_font_measure_text_extent(&v20, &v19, a7, a10, -1);
  if ( a6 <= a9 + v19 )
    v17 = a9 + v19;
  else
    v17 = a6;
  rf_ui_gadget_initialize(this, a2, 4, a3, a4, v20 + a8 + a5, v17, a12, a13);
  *(_BYTE *)(this + 628) = a11;
  *(_DWORD *)(this + 632) = a5;
  *(_DWORD *)(this + 636) = a6;
  v16 = a7;
  v15 = (_BYTE *)(this + 640);
  do
  {
    v13 = *v16;
    *v15++ = *v16++;
  }
  while ( v13 );
  *(_DWORD *)(this + 896) = a10;
  *(_DWORD *)(this + 900) = a8;
  *(_DWORD *)(this + 904) = a9;
  *(_DWORD *)(this + 916) = -1;
  *(_DWORD *)(this + 920) = -1;
  *(_DWORD *)(this + 924) = -1;
  *(_DWORD *)(this + 928) = -1;
  *(_DWORD *)(this + 912) = byte_1CF7BA0;
  return this;
}

