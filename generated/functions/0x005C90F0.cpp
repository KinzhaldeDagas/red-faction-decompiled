// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C90F0 rf_material_texture_slot_select_frame
// UNREALRED VERIFIED [material-animation-20260903]: Selects the bitmap handle for one 52-byte material texture slot at a given 15-Hz render time. Single-frame slots return their base handle. Animated slots derive floor(max(0,(time-start)/15 * fps * speed)); modes 0 and 2 loop, mode 1 holds the final frame, and multi-frame handles are base+frame+1.
int __thiscall rf_material_texture_slot_select_frame(int this, float a2)
{
  double v3; // st7
  int v4; // [esp+4h] [ebp-1Ch]
  float value; // [esp+8h] [ebp-18h]
  int v7; // [esp+10h] [ebp-10h]
  int v8; // [esp+14h] [ebp-Ch]
  float v9; // [esp+18h] [ebp-8h] BYREF
  float v10; // [esp+1Ch] [ebp-4h]

  if ( *(int *)this < 0 )
    return -1;
  v7 = rf_bitmap_animation_metadata_query(*(_DWORD *)this, &v9);
  if ( v7 == 1 )
    return *(_DWORD *)this;
  v10 = (double)v7 / v9 * *(float *)(this + 44);
  value = (a2 - (double)*(int *)(this + 40)) / 15.0 * v10;
  v3 = rf_floor_float(value);
  v8 = rf_int_max(0, (int)v3);
  v4 = *(_DWORD *)(this + 48);
  switch ( v4 )
  {
    case 0:
      goto LABEL_8;
    case 1:
      if ( v8 >= v7 )
        v8 = v7 - 1;
      break;
    case 2:
LABEL_8:
      if ( v8 >= v7 )
        v8 %= v7;
      break;
  }
  if ( v8 >= v7 )
    v8 = v7 - 1;
  return *(_DWORD *)this + v8 + 1;
}

