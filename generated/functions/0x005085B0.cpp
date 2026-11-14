// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005085B0 sub_5085B0
// UNREALRED VERIFIED [combat-native-weapon-registry-20261111]: Resource-free final weapon postprocess copies SP source fields into runtime fields: +258->260 maxammo,+50C->514 AIrange,+80->88 clip,+D8->E0 spread,+E4->EC altspread,+F0->F8 AIspread,+FC->104 AIaltspread,+118->120 AIdamageScale,+20C->208 damageRadius,+B4->B0 lifetime,+C8->C0 velocity, global6612A8->6612A4. No further cursor validation/EOF consumption here.
// UNREALRED VERIFIED [original-ai-difficulty-profile-20261112]: SP weapon profile postprocess first copies CONFIGURED6612A8 into ACTIVE6612A4; four-entry acquisition cadence and weighted player distance consume ACTIVE. Normal mission-byte reset4EF150 is not a difficulty reset. Keep configured and active distinct across multiplayer profile teardown.
char *sub_5085B0()
{
  char *result; // eax
  char *v1; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  result = (char *)dword_6612A8;
  dword_6612A4 = dword_6612A8;
  for ( i = 0; i < dword_911C68; ++i )
  {
    v1 = (char *)&rf_weapon_records + 1360 * i;
    *((_DWORD *)v1 + 152) = *((_DWORD *)v1 + 150);
    *((float *)v1 + 325) = *((float *)v1 + 323);
    *((_DWORD *)v1 + 34) = *((_DWORD *)v1 + 32);
    *((float *)v1 + 56) = *((float *)v1 + 54);
    *((float *)v1 + 59) = *((float *)v1 + 57);
    *((float *)v1 + 62) = *((float *)v1 + 60);
    *((float *)v1 + 65) = *((float *)v1 + 63);
    *((float *)v1 + 72) = *((float *)v1 + 70);
    *((float *)v1 + 130) = *((float *)v1 + 131);
    *((float *)v1 + 44) = *((float *)v1 + 45);
    result = v1;
    *((float *)v1 + 48) = *((float *)v1 + 50);
  }
  return result;
}

