// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00511320 rf_projectile_emit_distributed_trail_particles
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, weaponflag/accessor provenance,particle descriptors,trails,ricochet/piercing andx87unorderedbranches,original ECX/stack flow and PE bytes): Cdeclprojectile,noNULLguard,caller pops4,void. Copy currentposition60 tolhs. Source rhs selectedbyDWORDflags760:mask0x1 takespriority;withmask0x10 useprojectile108,otherwise resolveowner48 toplayer4DD720 andtry4EB9E0(player,&source,NULL) for local first-person prop origin;failure/noplayer usesprojectile776. Withoutmask0x1 requiremask0x4 anduseprojectile764,elseearlyreturn. DensityF32=global663A30-length(current60-fixed776)*global663A34,clamp[0,663A30]. Native gateTESTAH41/JP admits ORDEREDpositive ORUNORDEREDNaN,not C++ >0. Normalize(current-rhs) in place through559280 returning
// originalF32lengthL,withoutzeroguard;countFloat=F32(L*density),samepositive-OR-unorderedgate,clamp[0,100]. spacing=F32(L/countFloat). Setprojectile flags760|=0x10 BEFORE integerloopcount test. Loopi=0 whilei<nativeFTOL2(countFloat);forordinaryfinitecount in(0,1) flagis setwithZERO attempts. Loopcounttruncatestowardzero butspacingusesfloatcount,so evenintegercount omits exactsegmentendpoint. NaNisnotexcluded byearlier gates andpassesnativefloattointconversion;do not impose inventedfinitefallback. Eachiteration constructsdescriptor thenmemsetEXACT76bytes to0;drawX/Y/Z jitter via three RNGcalls in Z,Y,X callorder,eachrange(-.02,+.02). Descriptor position=rhs+direction*F32(i*spacing)+samejitter;velocity12=samejitter;F32size24=random(.01,.02),F32field28=random(-.01,-.03) withREVERSED endpoints
// retained,F32field36=random(-.03,-.1),lifetime40=random(1.5,3);bitmapDWORD44=global911C74,DWORD48=1,RGBA52=255/255/255/255,RGBA56=255/255/255/0,flagsDWORD60=0xC,F32fields32/64/68/72=0. Resolveowner entity48 EACHiteration;room=ownerDWORD0 ifresolved elseprojectileDWORD0. Callparticleallocator(0,descriptor,room,descriptorPosition,owner48,NULL,0);ignorefailure andcontinue. NoframeDelta scaling,endpointdedup,allocationfallback orclass flagrequirementbeyond760. Sharedclamp leavesNaN unchanged.
void __cdecl rf_projectile_emit_distributed_trail_particles(int a1)
{
  float *v1; // eax
  float *v2; // eax
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  int first_dword; // eax
  float v7; // [esp+4h] [ebp-160h]
  int v8; // [esp+4h] [ebp-160h]
  float v9; // [esp+8h] [ebp-15Ch]
  float v10; // [esp+Ch] [ebp-158h]
  float v11; // [esp+10h] [ebp-154h]
  float v12[3]; // [esp+14h] [ebp-150h] BYREF
  float v13[3]; // [esp+20h] [ebp-144h] BYREF
  float v14[3]; // [esp+2Ch] [ebp-138h] BYREF
  float sum_result[3]; // [esp+38h] [ebp-12Ch] BYREF
  int v16[3]; // [esp+44h] [ebp-120h] BYREF
  _BYTE v17[4]; // [esp+50h] [ebp-114h] BYREF
  float v18[3]; // [esp+54h] [ebp-110h] BYREF
  float v19[3]; // [esp+60h] [ebp-104h] BYREF
  float out_vector[3]; // [esp+6Ch] [ebp-F8h] BYREF
  float v21[3]; // [esp+78h] [ebp-ECh] BYREF
  float v22[3]; // [esp+84h] [ebp-E0h] BYREF
  float v23[3]; // [esp+90h] [ebp-D4h] BYREF
  float v24[3]; // [esp+9Ch] [ebp-C8h] BYREF
  float copy_result[3]; // [esp+A8h] [ebp-BCh] BYREF
  float v26[21]; // [esp+B4h] [ebp-B0h] BYREF
  void *v27; // [esp+108h] [ebp-5Ch]
  float source[3]; // [esp+10Ch] [ebp-58h] BYREF
  void *player; // [esp+118h] [ebp-4Ch]
  float destination[3]; // [esp+11Ch] [ebp-48h] BYREF
  float v31; // [esp+128h] [ebp-3Ch]
  float v32[3]; // [esp+12Ch] [ebp-38h] BYREF
  float v33; // [esp+138h] [ebp-2Ch]
  float v34; // [esp+13Ch] [ebp-28h]
  int v35; // [esp+140h] [ebp-24h] BYREF
  float lhs[3]; // [esp+144h] [ebp-20h] BYREF
  int v37; // [esp+150h] [ebp-14h] BYREF
  int i; // [esp+154h] [ebp-10h]
  float rhs[3]; // [esp+158h] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop(rhs);
  rf_vector3_copy_return_destination(lhs, (float *)(a1 + 60));
  rf_vector3_default_construct_noop(destination);
  if ( (*(_DWORD *)(a1 + 760) & 1) != 0 )
  {
    if ( (*(_DWORD *)(a1 + 760) & 0x10) != 0 )
    {
      rf_vector_copy(rhs, v22, (const float *)(a1 + 108));
    }
    else
    {
      rf_vector3_default_construct_noop(source);
      player = sub_4DD720(*(_DWORD *)(a1 + 48));
      if ( player )
      {
        if ( rf_player_compose_fpgun_muzzle_world_transform(player, source, nullptr) )
          rf_vector_copy(rhs, copy_result, source);
        else
          rf_vector_copy(rhs, v24, (const float *)(a1 + 776));
      }
      else
      {
        rf_vector_copy(rhs, v23, (const float *)(a1 + 776));
      }
    }
  }
  else
  {
    if ( (*(_DWORD *)(a1 + 760) & 4) == 0 )
      return;
    rf_vector_copy(rhs, v21, (const float *)(a1 + 764));
  }
  v1 = rf_vector_subtract(lhs, out_vector, (const float *)(a1 + 776));
  v33 = rf_vector3_length(v1);
  *(float *)&v35 = flt_663A30 - v33 * flt_663A34;
  rf_float_clamp_in_place((float *)&v35, 0.0, flt_663A30);
  if ( *(float *)&v35 > 0.0 )
  {
    rf_vector_subtract(lhs, v32, rhs);
    v34 = rf_vector3_normalize_return_length(v32);
    *(float *)&v37 = v34 * *(float *)&v35;
    if ( *(float *)&v37 > 0.0 )
    {
      rf_float_clamp_in_place((float *)&v37, 0.0, 100.0);
      v31 = v34 / *(float *)&v37;
      *(_DWORD *)(a1 + 760) |= 0x10u;
      for ( i = 0; i < (int)*(float *)&v37; ++i )
      {
        rf_particle_descriptor76_construct_noop((int)v26);
        memset(v26, 0, 0x4Cu);
        v10 = rf_random_float_range(-0.02, 0.02);
        v9 = rf_random_float_range(-0.02, 0.02);
        v7 = rf_random_float_range(-0.02, 0.02);
        v2 = rf_vector3_set_components_return_destination(v19, v7, v9, v10);
        rf_vector_copy(destination, v18, v2);
        LODWORD(v26[11]) = dword_911C74;
        v26[13] = *(float *)rf_rgba8_construct_components_return_self(v17, 255, 255, 255, 255);
        rf_color4_set_bytes_return_destination(&v26[14], 255, 255, 255, 0);
        LODWORD(v26[15]) |= 0xCu;
        v26[16] = 0.0;
        v26[7] = rf_random_float_range(-0.0099999998, -0.029999999);
        v26[10] = rf_random_float_range(1.5, 3.0);
        LODWORD(v26[12]) = 1;
        v11 = (double)i * v31;
        v3 = rf_vector_scale((float *)v16, v11, v32);
        v4 = rf_vector_add(rhs, sum_result, v3);
        v5 = rf_vector_add(v4, v14, destination);
        rf_vector_copy(v26, v13, v5);
        v26[6] = rf_random_float_range(0.0099999998, 0.02);
        rf_vector_copy(&v26[3], v12, destination);
        v26[9] = rf_random_float_range(-0.029999999, -0.1);
        v26[8] = 0.0;
        v26[17] = 0.0;
        v27 = (void *)rf_entity_resolve_handle(*(_DWORD *)(a1 + 48));
        v8 = *(_DWORD *)(a1 + 48);
        if ( v27 )
          first_dword = rf_receiver_get_first_dword(v27);
        else
          first_dword = rf_receiver_get_first_dword((void *)a1);
        rf_particle_allocate_and_initialize(0, v26, first_dword, (int)v26, v8, nullptr, 0);
      }
    }
  }
}

