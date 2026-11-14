// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F60F0 rf_ui_radio_button_initialize_in_group
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Args parent,x,y,boxW,boxH,label,labelDX,labelDY,font,id,raw base flag. Measures(label,font,-1),so configured font is passed as MAX BYTES and measurement uses default font-1 (same mismatch as checkbox initializer). Width=measuredW+labelDX+boxW;height=max(boxH,labelDY+measuredH). Gets owner from parent,initializes gadget type5. Checked BYTE628=1 iff parent has NO first child (any type);otherwise0. Stores box632/636,unbounded label640,font896,offsets900/904,bitmaps916..928=-1,palette912=0x1CF7BA0;finally reparents. Does not reset visual908 or exclusively clear prior radios. No NULL parent/allocation/label guard;return parent setter result.
_DWORD *__thiscall rf_ui_radio_button_initialize_in_group(
        int this,
        _DWORD *a2,
        int a3,
        int a4,
        int a5,
        int a6,
        unsigned __int8 *a7,
        int a8,
        int a9,
        int a10,
        int a11,
        char a12)
{
  int owner_window; // eax
  unsigned __int8 v13; // al
  _BYTE *v15; // [esp+8h] [ebp-20h]
  unsigned __int8 *v16; // [esp+Ch] [ebp-1Ch]
  int v17; // [esp+10h] [ebp-18h]
  int v19; // [esp+18h] [ebp-10h]
  int v20; // [esp+20h] [ebp-8h] BYREF
  int v21; // [esp+24h] [ebp-4h] BYREF

  rf_font_measure_text_extent(&v21, &v20, a7, a10, -1);
  v19 = v21 + a8 + a5;
  if ( a6 <= a9 + v20 )
    v17 = a9 + v20;
  else
    v17 = a6;
  owner_window = rf_ui_gadget_get_owner_window(a2);
  rf_ui_gadget_initialize(this, owner_window, 5, a3, a4, v19, v17, a11, a12);
  if ( rf_ui_gadget_get_first_child(a2) )
    *(_BYTE *)(this + 628) = 0;
  else
    *(_BYTE *)(this + 628) = 1;
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
  return rf_ui_gadget_set_parent((_DWORD *)this, (int)a2);
}

