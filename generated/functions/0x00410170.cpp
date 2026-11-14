// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00410170 rf_ai_segment_intersects_same_friendliness_entity
// UNREALRED VERIFIED [lan-ai-relations-20261028] The native corridor veto is a represented-faction relation, not a blanket AI category test: after resolving owner/target, candidates must share owner friendliness at +0x1F8 and that code must not be 3, in addition to the owner/target/link, active, collision and life gates. A synthetic Unreal LAN bot does not acquire ally status merely by being controlled by AI. This observation does not recover native multiplayer-bot policy or assign names to numeric friendliness codes.
// UNREALRED VERIFIED [combat-named-sphere-capacity-20261112]: Ally corridor narrowphase iteratesperbody24bytephysicalrecordarrayObject+184, centers=commonposition3C+recordXYZ (norender/livebonequeryandnobodymatrixrotationhere),radius=record+C. Broadphaseusescommonposition3C/radius78. This is distinctfrom43C180live modelcenter pluscachedclass40radius. Existinghostposedmeshsphere allyhelper remainsanadapter evenaftername/radiusbindingcorrection.
// [UnrealRed physical spheres 2026-11-12; verified ASM] Ally corridor first requires cached ROOM pointer returned by486DE0 and ROOM byte+0x160!=0 (NOT an AI+160 field). Native569C10 base(common+3C,common+78) AND at least one physical24(partXYZ+common3C,radius+12). Zero physical count cannot block. No live model/bone query, common48 rotation, render scale, or auxEntity13DC array is consumed. Native room352 render-visibility owner remains separate from host geometry admission.
char __cdecl rf_ai_segment_intersects_same_friendliness_entity(int a1, int a2, int a3, int a4)
{
  int v5; // eax
  const float *element_address_unchecked; // eax
  int v7; // eax
  const float *v8; // [esp+0h] [ebp-30h]
  float sum_result[3]; // [esp+4h] [ebp-2Ch] BYREF
  int j; // [esp+10h] [ebp-20h]
  int first_dword; // [esp+14h] [ebp-1Ch]
  int v12[3]; // [esp+18h] [ebp-18h] BYREF
  char *i; // [esp+24h] [ebp-Ch]
  char *v14; // [esp+28h] [ebp-8h]
  char *v15; // [esp+2Ch] [ebp-4h]

  v14 = (char *)rf_entity_resolve_handle(a1);
  v15 = (char *)rf_entity_resolve_handle(a2);
  if ( !v14 || !v15 )
    return 0;
  for ( i = (char *)unk_68211C; i != (char *)&unk_681E90; i = *((char **)i + 163) )
  {
    if ( v15 != i
      && v14 != i
      && *((_DWORD *)v14 + 12) != *((_DWORD *)i + 11)
      && *((_DWORD *)i + 126) == *((_DWORD *)v14 + 126)
      && *((_DWORD *)i + 126) != 3
      && !rf_object_has_respawn_inactive_flag((int)i) )
    {
      first_dword = rf_receiver_get_first_dword(i);
      if ( first_dword )
      {
        if ( *(_BYTE *)(first_dword + 352) )
        {
          if ( !rf_entity_is_dead((int)i) )
          {
            rf_vector3_default_construct_noop(v12);
            if ( rf_segment_sphere_intersection((int)v12, a3, a4, (int)(i + 60), *((float *)i + 30)) )
            {
              for ( j = 0; ; ++j )
              {
                v5 = rf_receiver_get_first_dword(i + 388);
                if ( j >= v5 )
                  break;
                v8 = (const float *)(i + 60);
                element_address_unchecked = (const float *)rf_array24_get_element_address_unchecked((_DWORD *)i + 97, j);
                rf_vector_add(element_address_unchecked, sum_result, v8);
                v7 = rf_array24_get_element_address_unchecked((_DWORD *)i + 97, j);
                if ( rf_segment_sphere_intersection((int)v12, a3, a4, (int)sum_result, *(float *)(v7 + 12)) )
                  return 1;
              }
            }
          }
        }
      }
    }
  }
  return 0;
}

