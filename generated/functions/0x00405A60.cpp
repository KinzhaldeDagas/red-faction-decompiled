// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00405A60 rf_ai_propagate_target_to_linked_entities
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI weighted-target/mode11/15/16/speech/stimulus chains, original dispatch/float constants and native field
// lifetime and native signed/x87/stack/callback ABI): One AI block. Resolve COMMON source target+704 once; miss exits. Walk entity list next+652 AFTER effects. Admit entity
// DWORD+1896==source owner handle+44 AND inactive predicate!=EXACT1; no source-pointer exclusion or dead/friendliness filter. If current mode(entity+1312)2/4 call40B2D0(entityAI),
// then40BA80(entityAI,source block target+704 reread). Independently RE-READ mode; if13 compute unnormalized target COMMON+60 minus candidate COMMON+60, dot candidate common FORWARD
// row+96, roundfloat32; ordered dot<0 calls40C340 association prelude,40B2D0,40BA80 with reread source target. The two mode branches are separate IFs, so callbacks changing mode can
// admit both in one iteration. No geometry query, distance cap, copied target-position or own multiplayer gate. EAX incidental traversal state.
int __cdecl rf_ai_propagate_target_to_linked_entities(int *a1)
{
  int result; // eax
  float out_vector[3]; // [esp+0h] [ebp-18h] BYREF
  float v3; // [esp+Ch] [ebp-Ch]
  int i; // [esp+10h] [ebp-8h]
  int v5; // [esp+14h] [ebp-4h]

  result = rf_object_resolve_handle(a1[176]);
  v5 = result;
  if ( result )
  {
    for ( i = unk_68211C; (_UNKNOWN *)i != &unk_681E90; i = *(_DWORD *)(i + 652) )
    {
      if ( *(_DWORD *)(i + 1896) == *(_DWORD *)(*a1 + 44) && !rf_object_has_respawn_inactive_flag(i) )
      {
        if ( *(_DWORD *)(i + 1312) == 2 || *(_DWORD *)(i + 1312) == 4 )
        {
          sub_40B2D0((int *)(i + 672));
          sub_40BA80((int *)(i + 672), a1[176]);
        }
        if ( *(_DWORD *)(i + 1312) == 13 )
        {
          rf_vector_subtract((const float *)(v5 + 60), out_vector, (const float *)(i + 60));
          v3 = rf_vector_dot((float *)(i + 96), out_vector);
          if ( v3 < 0.0 )
          {
            sub_40C340((int *)(i + 672));
            sub_40B2D0((int *)(i + 672));
            sub_40BA80((int *)(i + 672), a1[176]);
          }
        }
      }
      result = i;
    }
  }
  return result;
}

