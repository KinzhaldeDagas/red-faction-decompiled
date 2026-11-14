// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00598840 rf_audio_environment_set_preset_by_mutable_name
// UNREALRED VERIFIED [audio-properties-20261028]: Argument writable NUL-terminated name. Empty name comparison uses byte0x6423AB (zero); empty input overwritten with8 bytes generic plusNUL from0x642598/0x64259C,regardless mute flag. Second DWORD is ASCII ric-NUL,NOT a pointer to the unrelated message suggested by offset annotation. Nonempty name while cached muted flag set returns0 without searching/changing preset. Otherwise case-insensitive search of26 static names at pointer table0x6647A8; match stores index0x1BCA308 BEFORE calling0x5988D0,so failed/not-ready Set still changes cached index. Unknown name-1. No input buffer length/writability check; empty input requires8 writable bytes. PE-verified mapping: 0=generic, 1=paddedcell, 2=room, 3=bathroom, 4=livingroom, 5=stoneroom, 6=auditorium, 7=concerthall, 8=cave, 9=arena, 10=hangar, 11=carpetedhallway, 12=hallway, 13=stonecorridor,
// 14=alley, 15=forest, 16=city, 17=mountains, 18=quarry, 19=plain, 20=parkinglot, 21=sewerpipe, 22=underwater, 23=drugged, 24=dizzy, 25=psychotic.
int __cdecl rf_audio_environment_set_preset_by_mutable_name(char *String1)
{
  int i; // [esp+0h] [ebp-4h]

  if ( !_stricmp(String1, &byte_6423AB) )
  {
    *(_DWORD *)String1 = 1701733735;
    *((_DWORD *)String1 + 1) = "You must run Red Faction without an active mod in order to join that server.";
  }
  else if ( rf_audio_environment_is_muted_cached() )
  {
    return 0;
  }
  for ( i = 0; i < 26; ++i )
  {
    if ( !_stricmp((&off_6647A8)[i], String1) )
    {
      unk_1BCA308 = i;
      return rf_audio_environment_set_preset_id(i);
    }
  }
  return -1;
}

