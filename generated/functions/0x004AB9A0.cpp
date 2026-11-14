// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AB9A0 rf_multiplayer_apply_clutter_kill_payload30
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, packet registry/function recovery, kill/download routing, native CRC/UI/startup and original geometry
// constants and native signed/x87/stack/callback ABI): Recovered callback [4AB9A0,4ABE6C), registry row30 at662AB0. Cdecl(payload,ignored source); no own runtime/authority/length
// gate. Reads authored identifierDWORD0 and signed parameterDWORD4; scans clutter list to sentinel666D18 by next652 and applies ONLY first object whose DWORD32 matches. Let
// cls=objectDWORD660. If cls+88!=-1, calls507830(effectID) and remembers result>0, transforms cls+100 offset by object matrix72 then adds position60,
// calls448DC0(effectID,object-firstDWORD,0,effectPosition,clsFLOAT92,clsFLOAT96,0), arms cls deadline+112 for50ms. Default controls: debrisAllowed1,replacementAllowed1,sparkles0. If
// clsDWORD116 bit0x10: parameter0..2 sets debrisAllowed0,replacementAllowed1,sparkles1; every other signed parameter marks deferred-delete
// immediately,debrisAllowed1,replacementAllowed0. Sparkles run only when sparkles==1 AND objectBYTE716==0; sets byte1 BEFORE loads/spawns. Builds partly initialized76-byte particle
// descriptor: FLOAT+24=.2,+28=0,+32=0,+36=1,+40=3,bitmap+44=glasshard_A.tga loaded(-1,1),DWORD+48=1,colors+52 white255/+56 white0,DWORD+60=0x20C,+64=0,+72=0; +68 not written by this
// no-op constructor path. Particle origin uses mesh prop transform when signed clsDWORD152>-1, else objectPos60. For16 attempts position=origin+objectVector84*FLOAT.1+three567730
// random values; velocity=random_unit_vector_in_cone(out,by-value objectVector84,FLOAT.44) scaled by random_float_range(1,5). Allocator gets SEVEN explicit
// args(0,&descriptor,object-firstDWORD,&origin,-1,0,0); by-value vector and reused float slots explain decompiler fake scalar/NaN arguments. If replacementAllowed, optional
// replacement type object668!=-1 creates clutter(type,empty63B0D1,handle44,pos60,matrix72,0), then deferred-deletes original regardless creation success. If
// debrisAllowed==EXACT1,507830 result was NOT positive,and cls RFString24 nonempty, calls authored_debris(object,name,-1,4000,clsFLOAT120,&clsRFString32). Returns after matched
// object; no full-list bulk kill, authority validation, immediate unlink or registry mutation. Callbacks may operate on same object after deferred-delete request, as native ordering
// shows.
void __cdecl rf_multiplayer_apply_clutter_kill_payload30(void *a1, void *a2)
{
  float *v2; // eax
  int v3; // ecx
  int v4; // eax
  int first_dword; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  int v9; // eax
  int v10; // edx
  char *v11; // eax
  int v12; // [esp-4h] [ebp-118h] BYREF
  int scalar; // [esp+0h] [ebp-114h]
  float v14; // [esp+4h] [ebp-110h]
  float v15; // [esp+8h] [ebp-10Ch]
  int v16; // [esp+Ch] [ebp-108h]
  float v17[3]; // [esp+14h] [ebp-100h] BYREF
  float v18[3]; // [esp+20h] [ebp-F4h] BYREF
  float v19[3]; // [esp+2Ch] [ebp-E8h] BYREF
  float scaled_result[3]; // [esp+38h] [ebp-DCh] BYREF
  float copy_result[3]; // [esp+44h] [ebp-D0h] BYREF
  float v22[3]; // [esp+50h] [ebp-C4h] BYREF
  float rhs[3]; // [esp+5Ch] [ebp-B8h] BYREF
  int j; // [esp+68h] [ebp-ACh]
  char v25[36]; // [esp+6Ch] [ebp-A8h] BYREF
  float destination[3]; // [esp+90h] [ebp-84h] BYREF
  float v27[3]; // [esp+9Ch] [ebp-78h] BYREF
  float v28[10]; // [esp+A8h] [ebp-6Ch] BYREF
  _BYTE v29[4]; // [esp+D0h] [ebp-44h] BYREF
  _BYTE v30[4]; // [esp+D4h] [ebp-40h] BYREF
  int v31; // [esp+D8h] [ebp-3Ch]
  int v32; // [esp+DCh] [ebp-38h]
  int v33; // [esp+E4h] [ebp-30h]
  float sum_result[3]; // [esp+F0h] [ebp-24h] BYREF
  int v35; // [esp+FCh] [ebp-18h]
  bool v36; // [esp+100h] [ebp-14h]
  char v37; // [esp+101h] [ebp-13h]
  char v38; // [esp+102h] [ebp-12h]
  char v39; // [esp+103h] [ebp-11h]
  int v40; // [esp+104h] [ebp-10h]
  int v41; // [esp+108h] [ebp-Ch]
  int i; // [esp+10Ch] [ebp-8h]
  int v43; // [esp+110h] [ebp-4h]

  v41 = 0;
  v40 = *(_DWORD *)a1;
  v41 = 4;
  v43 = *((_DWORD *)a1 + 1);
  v41 = 8;
  for ( i = rf_clutter_list_head; (_UNKNOWN *)i != &unk_666D18; i = *(_DWORD *)(i + 652) )
  {
    if ( *(_DWORD *)(i + 32) == v40 )
    {
      v36 = 0;
      if ( *(_DWORD *)(*(_DWORD *)(i + 660) + 88) != -1 )
      {
        v35 = sub_507830(*(_DWORD *)(*(_DWORD *)(i + 660) + 88));
        v36 = v35 > 0;
        v2 = rf_vector3_transform_by_matrix_rows((float *)(*(_DWORD *)(i + 660) + 100), v22, (float *)(i + 72));
        rf_vector_add((const float *)(i + 60), sum_result, v2);
        v15 = 0.0;
        v3 = *(_DWORD *)(i + 660);
        v14 = *(float *)&v3;
        v14 = *(float *)(v3 + 96);
        v4 = *(_DWORD *)(i + 660);
        scalar = v3;
        scalar = *(int *)(v4 + 92);
        first_dword = rf_receiver_get_first_dword((void *)i);
        sub_448DC0(*(_DWORD *)(*(_DWORD *)(i + 660) + 88), first_dword, 0, sum_result, *(float *)&scalar, v14, 0);
        rf_replicator_arm_milliseconds((int *)(*(_DWORD *)(i + 660) + 112), 50);
      }
      v37 = 1;
      v39 = 1;
      v38 = 0;
      if ( (*(_DWORD *)(*(_DWORD *)(i + 660) + 116) & 0x10) != 0 )
      {
        v16 = v43;
        if ( v43 < 0 || v16 > 2 )
        {
          v37 = 1;
          v39 = 0;
          v38 = 0;
          rf_object_mark_for_deferred_delete(i);
        }
        else
        {
          v37 = 0;
          v39 = 1;
          v38 = 1;
        }
      }
      if ( v38 == 1 && !*(_BYTE *)(i + 716) )
      {
        *(_BYTE *)(i + 716) = 1;
        rf_particle_descriptor76_construct_noop((int)v27);
        v28[5] = 0.0;
        LODWORD(v28[8]) = rf_bitmap_load_with_optional_mipmap_generation("glasshard_A.tga", (void *)0xFFFFFFFF, 1);
        rf_color4_set_bytes_return_destination(v29, 255, 255, 255, 255);
        v31 = 524;
        v32 = 0;
        v28[6] = 1.0;
        rf_color4_set_bytes_return_destination(v30, 255, 255, 255, 0);
        v28[4] = 0.0;
        v28[7] = 3.0;
        LODWORD(v28[9]) = 1;
        v28[3] = 0.2;
        v33 = 0;
        rf_vector3_default_construct_noop(destination);
        if ( *(int *)(*(_DWORD *)(i + 660) + 152) <= -1 )
        {
          rf_vector_copy(destination, copy_result, (const float *)(i + 60));
        }
        else
        {
          rf_matrix3_construct(v25);
          rf_vmesh_compose_prop_world_transform(
            *(_DWORD *)(i + 128),
            *(_DWORD *)(*(_DWORD *)(i + 660) + 152),
            (float *)(i + 72),
            i + 60,
            (int)v25,
            destination);
        }
        for ( j = 0; j < 16; ++j )
        {
          rf_vector3_default_construct_noop(rhs);
          rhs[0] = sub_567730();
          rhs[1] = sub_567730();
          rhs[2] = sub_567730();
          v15 = COERCE_FLOAT(rhs);
          v14 = COERCE_FLOAT(v18);
          v6 = rf_vector_multiply_scalar((const float *)(i + 84), scaled_result, 0.1);
          v7 = rf_vector_add(destination, v19, v6);
          v8 = rf_vector_add(v7, (float *)LODWORD(v14), (const float *)LODWORD(v15));
          rf_vector_copy(v27, v17, v8);
          v15 = 0.44;
          rf_vector3_copy_return_destination((float *)&v12, (float *)(i + 84));
          rf_random_unit_vector_in_cone(v28, *(float *)&v12, *(float *)&scalar, v14, v15);
          v15 = rf_random_float_range(1.0, 5.0);
          rf_vector3_scale_in_place_return_self(v28, v15);
          v15 = 0.0;
          v14 = 0.0;
          *(float *)&scalar = NAN;
          v12 = (int)destination;
          v9 = rf_receiver_get_first_dword((void *)i);
          rf_particle_allocate_and_initialize(0, (int)v27, v9, v12, scalar, (_DWORD *)LODWORD(v14), SLODWORD(v15));
        }
      }
      if ( v39 )
      {
        if ( *(_DWORD *)(i + 668) != -1 )
          rf_clutter_runtime_create(
            *(_DWORD *)(i + 668),
            &byte_63B0D1,
            *(_DWORD *)(i + 44),
            (float *)(i + 60),
            (float *)(i + 72),
            0);
        rf_object_mark_for_deferred_delete(i);
      }
      if ( v37 == 1 && !v36 && rf_rf_string_not_equals_cstring_case_insensitive(*(_DWORD *)(i + 660) + 24, byte_63B0D2) )
      {
        LODWORD(v15) = *(_DWORD *)(i + 660) + 32;
        v10 = *(_DWORD *)(i + 660);
        v14 = *(float *)&i;
        v14 = *(float *)(v10 + 120);
        scalar = 4000;
        v12 = -1;
        v11 = (char *)rf_string_object_c_str_or_empty((const void *)(*(_DWORD *)(i + 660) + 24));
        rf_clutter_spawn_authored_debris(i, v11, v12, scalar, v14, (std::exception *)LODWORD(v15));
      }
      return;
    }
  }
}

