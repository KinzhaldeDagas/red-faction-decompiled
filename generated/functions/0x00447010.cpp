// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00447010 rf_foley_choose_random_sound
// UNREALRED VERIFIED [combat-entity-speech-20261111]: Foley chooser: invalid signed set index returns-1 with no RNG. Declared count<=1 chooses index0 without RNG; larger count uses raw rand()%count exactly once. Then dereference stored SoundID at that variant. Do not draw again in an audio backend after persona selection. Count0 is not a proved empty no-sound return; it dereferences allocation index0.
int __cdecl rf_foley_choose_random_sound(int a1)
{
  int v2; // [esp+0h] [ebp-Ch]
  char *v3; // [esp+8h] [ebp-4h]

  if ( a1 < 0 || a1 >= unk_6EDC30 )
    return -1;
  v3 = (char *)&unk_6E6E30 + 44 * a1;
  if ( *((int *)v3 + 9) <= 1 )
    v2 = 0;
  else
    v2 = rand() % *((_DWORD *)v3 + 9);
  return *(_DWORD *)(*((_DWORD *)v3 + 10) + 4 * v2);
}

