// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00437B70 rf_entity_spawn_class_tag_debris
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): Cdecl(entity pointer,second required pointer), void/incidental result. NULL either input exits before
// initialization/RNG. Constructs100-byte physical-debris config419580: position0,orientation identity,linear/angular0,lifetime72=1000,raw76=0,80=-1,84/88/92/96=0; constructs no-write
// local matrix/vector, then copies entity COMMON matrix72 into an otherwise UNUSED local matrix. Builds FLOAT32 direction=(second pointer vector+96)+(0,1,0) and unchecked
// reciprocal-sqrt normalizes. Calls5597C0 with ECX=config linear velocity+48, normalized XYZ passed BY VALUE and minimumDot exact FLOAT0.9919999837875366 (RET16); no extra output
// argument. Scales sampled cone vector byFLOAT4 with component stores, then adds separately float32-scaled0.5*entity linear vector324 componentwise. Samples independent random unit
// vector into config angular velocity+60, then always calls5677D0(FLOAT10,FLOAT25) and scales angular vector by returned float-rounded range value. Shared RNG/normalization work
// occurs BEFORE tag/model admission, even when no debris will be created; no finite/coincident-direction guard.  Only afterwards requires signed class(+660) tagDWORD+1764>=0 and
// entity model-slotDWORD+5136 NONNULL. Either failure returns after prior RNG/reads but BEFORE own entity mask clear. Presence slot5136 is a gate ONLY: transform compose5651D0 uses
// BASE entity model128, selected tag1764, COMMON matrix72/position60, writing config orientation+12/position+0; it does not use5136 as compose model. Compose result ignored with no
// success-result branch; config starts at zero position/identity orientation, and transform delegates can partially overwrite it before failure. Config then overwrites raw
// DWORD+72=20000 lifetimeMS,+76=2,+80=0xFFFFFFFF,+84=12,+88=0x10000,+96=global681E7C contact-event ID; remaining fields retain initializer/current motion values. The DWORD-1 at+80 is
// not a floating NaN policy. Calls4187B0(-1,class RFString+56 C-string,FLOAT0.4000000059604645 MASS,&config,DWORD0,FLOAT-1), six slots, ignores return/allocation result. THEN
// unconditionally clears entity DWORD+2064 mask0x00200000. Does not clear/release model-slot5136, assign created piece handle or rollback sampled motion/mask on failure. No
// owner/target association mutation or entity velocity transfer/clear: entity vector324 is only sampled for debris velocity.
void __cdecl rf_entity_spawn_class_tag_debris(const float *a1, int a2)
{
  float *v2; // eax
  float *v3; // eax
  char *v4; // eax
  float v5; // [esp+0h] [ebp-E0h] BYREF
  float *v6; // [esp+4h] [ebp-DCh]
  int v7; // [esp+8h] [ebp-D8h]
  float scalar; // [esp+Ch] [ebp-D4h]
  float scaled_result[4]; // [esp+10h] [ebp-D0h] BYREF
  float copy_result[3]; // [esp+20h] [ebp-C0h] BYREF
  float sum_result[3]; // [esp+2Ch] [ebp-B4h] BYREF
  float destination[3]; // [esp+38h] [ebp-A8h] BYREF
  float rhs[3]; // [esp+44h] [ebp-9Ch] BYREF
  int v14[3]; // [esp+50h] [ebp-90h] BYREF
  _BYTE v15[36]; // [esp+5Ch] [ebp-84h] BYREF
  float v16[3]; // [esp+80h] [ebp-60h] BYREF
  float v17[12]; // [esp+8Ch] [ebp-54h] BYREF
  float v18[9]; // [esp+BCh] [ebp-24h] BYREF

  if ( a1 )
  {
    if ( a2 )
    {
      rf_geomod_debris_spawn_config_init((int)v14);
      rf_matrix3_construct((char *)v18);
      rf_vector3_default_construct_noop(destination);
      rf_vector3_set_components_return_destination(rhs, 0.0, 1.0, 0.0);
      rf_matrix3_copy(v18, a1 + 18);
      v2 = rf_vector_add((const float *)(a2 + 96), sum_result, rhs);
      rf_vector_copy(destination, copy_result, v2);
      rf_vector_normalize_reciprocal_sqrt(destination);
      scalar = 0.99199998;
      rf_vector3_copy_return_destination(&v5, destination);
      rf_random_unit_vector_in_cone(v16, v5, *(float *)&v6, *(float *)&v7, scalar);
      rf_vector3_scale_in_place_return_self(v16, 4.0);
      v3 = rf_vector_multiply_scalar(a1 + 81, scaled_result, 0.5);
      rf_vector_accumulate(v16, v3);
      rf_random_unit_vector(v17);
      scalar = rf_random_float_range(10.0, 25.0);
      rf_vector3_scale_in_place_return_self(v17, scalar);
      if ( *(int *)(*((_DWORD *)a1 + 165) + 1764) >= 0 )
      {
        if ( *((_DWORD *)a1 + 1284) )
        {
          rf_vmesh_compose_prop_world_transform(
            *((_DWORD *)a1 + 32),
            *(_DWORD *)(*((_DWORD *)a1 + 165) + 1764),
            (float *)a1 + 18,
            (int)(a1 + 15),
            (int)v15,
            (float *)v14);
          LODWORD(v17[11]) = 20000;
          LODWORD(v17[3]) = 20000;
          LODWORD(v17[4]) = 2;
          v17[5] = NAN;
          LODWORD(v17[6]) = 12;
          LODWORD(v17[7]) = 0x10000;
          LODWORD(v17[9]) = unk_681E7C;
          scalar = -1.0;
          v7 = 0;
          v6 = (float *)v14;
          v5 = 0.40000001;
          v4 = (char *)rf_string_object_c_str_or_empty((const void *)(*((_DWORD *)a1 + 165) + 56));
          rf_physical_debris_piece_create(-1, v4, (void *)LODWORD(v5), v6, v7, (void *)LODWORD(scalar));
          *((_DWORD *)a1 + 516) &= ~0x200000u;
        }
      }
    }
  }
}

