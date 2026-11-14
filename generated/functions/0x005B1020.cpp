// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B1020 rf_ui_window_hit_mask_value_at_screen_point
// UNREALRED VERIFIED [ui-frame-scroll-20261029]: Thiscall window,screen X,Y. No mask pointer+1240 returns-1. Subtracts window position+12/+16;inside half-open width+20,height+24 reads unsigned BYTE mask[localX+width*localY],returns0..255. Outside returns-1. Does not interpret0/255 transparency,validate mask allocation size or mutate state.
int __thiscall rf_ui_window_hit_mask_value_at_screen_point(_DWORD *this, int a2, int a3)
{
  int v4; // [esp+14h] [ebp+8h]
  int v5; // [esp+18h] [ebp+Ch]

  if ( !*(this + 310) )
    return -1;
  v4 = a2 - *(this + 3);
  v5 = a3 - *(this + 4);
  if ( v4 >= 0 && v5 >= 0 && v4 < *(this + 5) && v5 < *(this + 6) )
    return *(unsigned __int8 *)(*(this + 310) + v4 + *(this + 5) * v5);
  else
    return -1;
}

