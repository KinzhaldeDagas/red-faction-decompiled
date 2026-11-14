// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00532FC0 rf_geomod_fragment_class_flood_fill
// UNREALRED VERIFIED [geomod-classification-20261028] Spatial-classifier gate at 0x532FCA bypasses all flood. Linear fallback visits shared-VERTEX incident faces; class_get at 0x5330FC skips every already-resolved neighbor. Only class-zero, eligible, same-operand, non-0x08000000 neighbors receive the seed class at 0x533157. No polygon-area vote exists; resolved classes must not be overwritten by connected-component area majority. Host area reconciliation is an explicit incomplete approximation: removing it before finite paired-boundary completion exposes additional seams. Verified ray-query corrections are implemented separately; no native-area-vote claim is made.
void __thiscall rf_geomod_fragment_class_flood_fill(__int16 *this)
{
  BOOL v1; // esi
  unsigned int v2; // eax
  _DWORD *v3; // [esp+4h] [ebp-24h]
  int v5; // [esp+Ch] [ebp-1Ch]
  int v6; // [esp+10h] [ebp-18h]
  int j; // [esp+14h] [ebp-14h]
  int v8; // [esp+18h] [ebp-10h]
  _DWORD *i; // [esp+1Ch] [ebp-Ch]
  int v10; // [esp+20h] [ebp-8h]
  int v11; // [esp+24h] [ebp-4h]

  if ( !rf_geomod_spatial_classifier_enabled
    && (rf_geomod_face_boolean_class_get((_DWORD *)this + 10) == 1
     || rf_geomod_face_boolean_class_get((_DWORD *)this + 10) == 2)
    && !rf_geomod_face_flag_08000000_is_set((_DWORD *)this + 10)
    && rf_geomod_terrain_component_face_eligible(this + 20) )
  {
    rf_geomod_fragment_flood_stack[0] = (int)this;
    v11 = 1;
    while ( v11 > 0 )
    {
      v10 = rf_geomod_fragment_flood_stack[--v11];
      for ( i = *(_DWORD **)(v10 + 64); i; i = v3 )
      {
        v8 = *i;
        if ( !*(_BYTE *)(*i + 28) )
        {
          v6 = 0;
          for ( j = 0; j < rf_receiver_get_first_dword((void *)(v8 + 32)); ++j )
          {
            v5 = *(_DWORD *)sub_552200((_DWORD *)(v8 + 32), j);
            if ( rf_geomod_face_boolean_class_get((_DWORD *)(v5 + 40))
              || !rf_geomod_terrain_component_face_eligible((__int16 *)(v5 + 40)) )
            {
              ++v6;
            }
            else if ( !rf_geomod_face_flag_08000000_is_set((_DWORD *)(v5 + 40)) )
            {
              v1 = rf_geomod_face_operand_get((_DWORD *)(v5 + 40));
              if ( v1 == rf_geomod_face_operand_get((_DWORD *)this + 10) )
              {
                v2 = rf_geomod_face_boolean_class_get((_DWORD *)this + 10);
                rf_geomod_face_boolean_class_set((int *)(v5 + 40), v2);
                if ( v11 < 0x4000 )
                  rf_geomod_fragment_flood_stack[v11++] = v5;
              }
            }
          }
          if ( v6 == rf_receiver_get_first_dword((void *)(v8 + 32)) )
            *(_BYTE *)(v8 + 28) = 1;
        }
        if ( i[5] == *(_DWORD *)(v10 + 64) )
          v3 = nullptr;
        else
          v3 = (_DWORD *)i[5];
      }
    }
  }
}

