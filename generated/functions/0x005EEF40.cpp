// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005EEF40 rf_scrollbar_recompute_thumb_length
// UNREALRED VERIFIED [text-layout-20261029]: Computes float fraction=page/(range+page-1),where page=DWORD+680 and range=DWORD+648,clamps ordered result0..1. Horizontal BYTE+664 chooses outer width+20,else height+24; integer truncation of track dimension*fraction becomes thumb length,minimum7. Writes through0x5EEA90. No denominator-zero,NaN,negative-size or minimum-track-length guard; minimum7 can exceed short track. Does not clamp scroll position.
_DWORD *__thiscall rf_scrollbar_recompute_thumb_length(int this)
{
  float v2; // [esp+8h] [ebp-8h]
  int v3; // [esp+Ch] [ebp-4h]

  v2 = (double)*(int *)(this + 680) / (double)(*(_DWORD *)(this + 648) + *(_DWORD *)(this + 680) - 1);
  if ( v2 < 0.0 )
    v2 = 0.0;
  if ( v2 > 1.0 )
    v2 = 1.0;
  if ( *(_BYTE *)(this + 664) )
    v3 = (int)((double)*(int *)(this + 20) * v2);
  else
    v3 = (int)((double)*(int *)(this + 24) * v2);
  if ( v3 < 7 )
    v3 = 7;
  return rf_scrollbar_set_thumb_length((_DWORD *)this, v3);
}

