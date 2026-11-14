// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E4C80 rf_vani_player_advance_and_draw
// UNREALRED VERIFIED [texture-conversion-20261028]: Argumentdeltatime. Ifplayingflag0x40clearreturns0. Negativebitmaphandletriggerscache0x5E4BE0; failure-1. Unlesspausedflag0x80,addsdelta toelapsed+108. Ifelapsed>duration+104: loopflag1resetstimeEXACTLY0(discardsoverflow),elseholdflag8selectslastframe,elsestopsplayingandreturns0WITHOUTdrawingterminalframe. Equalitydurationstilldrawsafterclamp. Normalframe=int(framecount*elapsed/duration),reverseflag2usescount-1-index,thenclamps0..count-1. Hold-lastignoresreverse. Nonstreamingbitmap=basehandle+frame. Streamingflag0x10: onframeindexchange releasesoldbitmap0x5781E0,readsframe0x5E52D0intoexistingbuffers112/116,IGNORESdecoderresult,createsnewuserbitmap(format,width,height); noexplicitpixeluploadinbody. Drawsresultatposition96/100via rf_bitmap_draw_unscaled_clipped,state0x187CD38ifflag4else0x187CC7C. Returns0afterdraw,ignoresdrawresult. No
// durationzero,negativeframecount/delta orbufferallocationguards.
int __thiscall rf_vani_player_advance_and_draw(int this, float a2)
{
  char v4; // [esp+7h] [ebp-9h]
  unsigned int v5; // [esp+8h] [ebp-8h]
  int v6; // [esp+Ch] [ebp-4h]

  v6 = *(_DWORD *)(this + 400);
  v4 = 0;
  if ( (*(_DWORD *)(this + 404) & 0x40) == 0 )
    return 0;
  if ( *(int *)(this + 92) < 0 && rf_vani_player_cache_loaded_animation(this) )
    return -1;
  if ( (*(_DWORD *)(this + 404) & 0x80) == 0 )
    *(float *)(this + 108) = *(float *)(this + 108) + a2;
  if ( *(float *)(this + 104) < (double)*(float *)(this + 108) )
  {
    if ( (*(_DWORD *)(this + 404) & 1) != 0 )
    {
      *(float *)(this + 108) = 0.0;
    }
    else
    {
      if ( (*(_DWORD *)(this + 404) & 8) == 0 )
      {
        *(_DWORD *)(this + 404) &= ~0x40u;
        return 0;
      }
      v4 = 1;
    }
  }
  if ( v4 )
  {
    *(_DWORD *)(this + 400) = *(_DWORD *)(this + 84) - 1;
  }
  else
  {
    *(_DWORD *)(this + 400) = (int)((double)*(int *)(this + 84) * *(float *)(this + 108) / *(float *)(this + 104));
    if ( (*(_DWORD *)(this + 404) & 2) != 0 )
      *(_DWORD *)(this + 400) = *(_DWORD *)(this + 84) - 1 - *(_DWORD *)(this + 400);
    if ( *(int *)(this + 400) < 0 )
      *(_DWORD *)(this + 400) = 0;
    if ( *(_DWORD *)(this + 400) >= *(_DWORD *)(this + 84) )
      *(_DWORD *)(this + 400) = *(_DWORD *)(this + 84) - 1;
  }
  v5 = *(_DWORD *)(this + 400) + *(_DWORD *)(this + 92);
  if ( (*(_DWORD *)(this + 404) & 0x10) != 0 )
  {
    if ( v6 != *(_DWORD *)(this + 400) )
    {
      rf_bitmap_handle_recycle_slot_or_animation_entry(*(_DWORD *)(this + 92));
      rf_vani_player_read_frame_pixels(this, *(_DWORD *)(this + 400), *(void **)(this + 112), *(void **)(this + 116));
      *(_DWORD *)(this + 92) = rf_bitmap_create_user_bitmap(
                                 *(_DWORD *)(this + 80),
                                 *(_DWORD *)(this + 68),
                                 *(_DWORD *)(this + 72));
    }
    v5 = *(_DWORD *)(this + 92);
  }
  if ( (*(_DWORD *)(this + 404) & 4) != 0 )
    rf_bitmap_draw_unscaled_clipped(v5, *(_DWORD *)(this + 96), *(_DWORD *)(this + 100), unk_187CD38);
  else
    rf_bitmap_draw_unscaled_clipped(v5, *(_DWORD *)(this + 96), *(_DWORD *)(this + 100), dword_187CC7C);
  return 0;
}

