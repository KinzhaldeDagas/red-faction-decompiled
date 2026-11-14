// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043EFD0 rf_burn_effect_release_record
// UNREALRED VERIFIED [combat-burn-owner-20261104]: Releases4emitter handles, stops retained voice, clears matching entity/corpse fire association and appends freed record to free tail unless reset mode. Native emitter destruction detaches surviving particles for ordinary expiry; clearing all particles is a level-pool reset behavior, not ordinary burn release.
// [UnrealRed burn initialization availability 2026-11-12; full original-byte ASM] External cleanup handles four emitter pointers conditionally: disable/destroy4CEDE0/zero each nonNULL, reset owner/bones/voice/fade, clear matching Entity13D8/Corpse2D0 reference, move active->free unless bulkarg. Host pending/reserved cleanup must revoke exact owner+serial before callbacks, release completed resources once and preserve already emitted/RNG prefixes; never let late completion publish into reused slot.
float *__cdecl rf_burn_effect_release_record(float *a1, unsigned __int8 a2)
{
  float *result; // eax
  int j; // [esp+0h] [ebp-Ch]
  int i; // [esp+4h] [ebp-8h]
  char v5; // [esp+Bh] [ebp-1h]

  if ( *(_DWORD *)a1 )
  {
    rf_particle_emitter_disable(*(_BYTE **)a1);
    rf_particle_emitter_destroy(*(_DWORD *)a1);
    *a1 = 0.0;
  }
  if ( *((_DWORD *)a1 + 1) )
  {
    rf_particle_emitter_disable(*((_BYTE **)a1 + 1));
    rf_particle_emitter_destroy(*((_DWORD *)a1 + 1));
    a1[1] = 0.0;
  }
  if ( *((_DWORD *)a1 + 2) )
  {
    rf_particle_emitter_disable(*((_BYTE **)a1 + 2));
    rf_particle_emitter_destroy(*((_DWORD *)a1 + 2));
    a1[2] = 0.0;
  }
  if ( *((_DWORD *)a1 + 3) )
  {
    rf_particle_emitter_disable(*((_BYTE **)a1 + 3));
    rf_particle_emitter_destroy(*((_DWORD *)a1 + 3));
    a1[3] = 0.0;
  }
  a1[4] = NAN;
  a1[5] = NAN;
  a1[6] = NAN;
  a1[7] = NAN;
  a1[8] = NAN;
  if ( *((_DWORD *)a1 + 9) != -1 )
    rf_gamesound_stop_voice_handle(*((_DWORD *)a1 + 9));
  a1[9] = NAN;
  a1[10] = 0.0;
  *((_BYTE *)a1 + 44) = 0;
  a1[12] = 0.0;
  v5 = 0;
  for ( i = unk_68211C; (_UNKNOWN *)i != &unk_681E90; i = *(_DWORD *)(i + 652) )
  {
    if ( *(float **)(i + 5080) == a1 )
    {
      *(_DWORD *)(i + 5080) = 0;
      v5 = 1;
      break;
    }
  }
  if ( !v5 )
  {
    for ( j = rf_corpse_list_head; (_UNKNOWN *)j != &unk_681AF8; j = *(_DWORD *)(j + 652) )
    {
      if ( *(float **)(j + 720) == a1 )
      {
        *(_DWORD *)(j + 720) = 0;
        break;
      }
    }
  }
  result = (float *)a2;
  if ( !a2 )
  {
    if ( (float *)unk_6E6508 == a1 )
    {
      if ( *((float **)a1 + 14) == a1 )
      {
        a1[14] = 0.0;
        a1[15] = 0.0;
        unk_6E6508 = 0;
LABEL_28:
        if ( unk_6E650C )
        {
          a1[15] = *(float *)(unk_6E650C + 60);
          *((_DWORD *)a1 + 14) = unk_6E650C;
          *(_DWORD *)(*(_DWORD *)(unk_6E650C + 60) + 56) = a1;
          *(_DWORD *)(unk_6E650C + 60) = a1;
        }
        else
        {
          *((_DWORD *)a1 + 14) = a1;
          *((_DWORD *)a1 + 15) = a1;
          unk_6E650C = a1;
        }
        return a1;
      }
      unk_6E6508 = *((_DWORD *)a1 + 14);
    }
    *(float *)(*((_DWORD *)a1 + 15) + 56) = a1[14];
    *(float *)(*((_DWORD *)a1 + 14) + 60) = a1[15];
    a1[14] = 0.0;
    a1[15] = 0.0;
    goto LABEL_28;
  }
  return result;
}

