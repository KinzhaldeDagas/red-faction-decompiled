// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C0220 rf_sound_find_or_register
// UNREALRED VERIFIED [mission-mover-effects-20261013] CORRECTION to older streaming label: resource byte+0x3E is bluebeard.bty +Looping Sound (metadata+0xA8 bit0x40000000). It routes common gamesound0x568050 to backend loop/nonloop starts. Byte+0x3C is +Music Track; distinct from looping. Resource registration does not transfer the low27-bit Loop Start offset into the PC voice-start path.
// UNREALRED VERIFIED [combat-speech-providers-20261111]: Resource dedup uses filename only, case-insensitive; existing resource returns before new-file probe/cap and preserves first registration parameters. A new filename requires count<2600 and5C1740 virtual-file availability; failure returns-1 without adding. Nonpositive minDistance stores1, volume/rolloff retained. Registration missing-file-1 must be resolved before4376C0 early invalid-sound gate; lazy playback failure has different committed phases.
// UNREALRED VERIFIED [combat-native-pickup-runtime-20261111]: Item direct sounds join SAME filename-only CI registration after native startup globals/Foley/material/weapon phases. Existing filename returns first params before cap/probe; new count<2600 plus5C1740 VFile availability required, failure-1 leaves itemrow valid and permits default0/12. PCM decode failure later is not registration failure. minDistance<=0 stores1; volume/rolloff retained. Byte3E is bluebeard LoopingSound, byte3C MusicTrack; no filename-based looping inference. Global51 uses loop/nonloop common voice paths accordingly.
int __cdecl rf_sound_find_or_register(char *a1, float a2, float a3, float a4, int a5)
{
  char v5; // al
  char v7; // dl
  double v8; // st7
  char *v9; // [esp+14h] [ebp-130h]
  char *v10; // [esp+18h] [ebp-12Ch]
  char *v11; // [esp+24h] [ebp-120h]
  char String2[260]; // [esp+2Ch] [ebp-118h] BYREF
  char *v14; // [esp+134h] [ebp-10h]
  int v15; // [esp+138h] [ebp-Ch]
  char *v16; // [esp+13Ch] [ebp-8h]
  int i; // [esp+140h] [ebp-4h]

  v15 = -1;
  v11 = String2;
  do
  {
    v5 = *a1;
    *v11++ = *a1++;
  }
  while ( v5 );
  if ( !String2 || !String2[0] )
    return -1;
  v16 = (char *)rf_bluebeard_sound_metadata_find(String2);
  if ( !v16 )
    v16 = aBadSoundWav;
  for ( i = 0; i < rf_sound_resource_count; ++i )
  {
    if ( !_stricmp(&rf_sound_resource_registry[64 * i], String2) )
      return i;
  }
  v15 = rf_sound_resource_count;
  if ( rf_sound_resource_count >= 2600 )
    return -1;
  if ( !rf_sound_file_probe(String2) )
    return -1;
  v14 = &rf_sound_resource_registry[64 * v15];
  v10 = String2;
  v9 = v14;
  do
  {
    v7 = *v10;
    *v9++ = *v10++;
  }
  while ( v7 );
  *((float *)v14 + 8) = a3;
  *((_DWORD *)v14 + 13) = a5;
  if ( a2 <= 0.0 )
    a2 = 1.0;
  *((float *)v14 + 9) = a2;
  *((float *)v14 + 11) = a4;
  v8 = rf_sound_compute_max_audible_distance(a2, a4, a3);
  *((float *)v14 + 10) = v8;
  v14[60] = (*((_DWORD *)v16 + 43) & 0x20000000) != 0;
  v14[62] = (*((_DWORD *)v16 + 42) & 0x40000000) != 0;
  ++rf_sound_resource_count;
  return v15;
}

