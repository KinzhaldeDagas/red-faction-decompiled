// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00415F90 rf_clutter_play_class_use_sound
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, clutter runtime teardown/render admission, DWORD-category glass callback, cached model binding and signed-counter clock-hand geometry): Cdecl clutter pointer,void. NULL skips;otherwise reads class660 soundset84 and only exact-1 skips. Chooses randomfoley andplays positional event at common60 with volume1/shared17F10B0/flags0;storesreturned voice/result in720 even failure. No previous-voice stop/playing guard,range/classpointer checks or duplicate suppression;can overwrite saved voice handle. Does not alter ambientvoice672.
void __cdecl rf_clutter_play_class_use_sound(int a1)
{
  int v1; // eax

  if ( a1 )
  {
    if ( *(_DWORD *)(*(_DWORD *)(a1 + 660) + 84) != -1 )
    {
      v1 = rf_foley_choose_random_sound(*(_DWORD *)(*(_DWORD *)(a1 + 660) + 84));
      *(_DWORD *)(a1 + 720) = rf_gamesound_play_positional_event(v1, (float *)(a1 + 60), 1.0, (int)&unk_17F10B0, 0);
    }
  }
}

