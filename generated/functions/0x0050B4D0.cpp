// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0050B4D0 sub_50B4D0
// UNREALRED VERIFIED [combat-particle-emission-20261104]: Weapon projectile liquid-contact VClip call at50B557 passes optional direction NULL (push0 at50B533), despite retaining contact position atprojectile+0x1B4. Inline uses authored direction; graph defaults RF+Y. Ordinary weapon-hit510670 direction forwarding is a different branch.
char __cdecl sub_50B4D0(int a1)
{
  void *first_dword; // eax
  float v3; // [esp+10h] [ebp-8h]
  unsigned int v4; // [esp+14h] [ebp-4h]

  v3 = *(float *)(a1 + 120) + *(float *)(a1 + 120);
  if ( v3 < 0.5 )
    v3 = 0.5;
  if ( *(_DWORD *)(*(_DWORD *)(a1 + 660) + 1324) == 1 || *(_DWORD *)(*(_DWORD *)(a1 + 660) + 1324) == 2 )
    v4 = unk_90B82C;
  else
    v4 = unk_90B824;
  first_dword = (void *)rf_receiver_get_first_dword((void *)a1);
  rf_vclip_spawn_runtime_effect(v4, first_dword, nullptr, (float *)(a1 + 436), (float *)LODWORD(v3), -1, nullptr, 1);
  if ( (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 612) & 0x10000) != 0 )
    *(float *)(a1 + 52) = 0.0;
  return 1;
}

