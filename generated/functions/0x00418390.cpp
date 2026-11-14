// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00418390 rf_physical_debris_contact_effect
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, monitor lifetime, debris lifecycle/contact audio, native render ABI and mixed spawn descriptor): Uses outer physics radius+384. Effect size is float(2*r), clamped upward to0.5 only on ordered size<0.5. Radius bands <0.1, [0.1,1.5), [1.5,3), >=3 select globals0x90B830,0x90B824,0x90B834,0x90B828 respectively; NaN selects the last and retains NaN size. Spawns vclip with object room DWORD0, common position+60, contact point+436, size,-1,0,1. Always returns AL1 regardless of spawn result. No rate limit or contact-state reset.
char __cdecl rf_physical_debris_contact_effect(float *a1)
{
  int first_dword; // eax
  float v3; // [esp+10h] [ebp-8h]
  unsigned int v4; // [esp+14h] [ebp-4h]

  v3 = a1[96] + a1[96];
  if ( v3 < 0.5 )
    v3 = 0.5;
  if ( a1[96] >= 0.1000000014901161 )
  {
    if ( a1[96] >= 1.5 )
    {
      if ( a1[96] >= 3.0 )
        v4 = unk_90B828;
      else
        v4 = unk_90B834;
    }
    else
    {
      v4 = unk_90B824;
    }
  }
  else
  {
    v4 = unk_90B830;
  }
  first_dword = rf_receiver_get_first_dword(a1);
  rf_vclip_spawn_runtime_effect(v4, first_dword, (int)(a1 + 15), (int)(a1 + 109), v3, -1, 0, 1);
  return 1;
}

