// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005141A0 rf_mesh_decal_collect_clipped_model_triangles
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projected mesh decal pools,shadow records,x87 unordered filters and recovered no-op constructors,original ECX/stack flow and PE bytes): Cdecl query176*,caller pops4. Normalize(start108-end120) with559200 NO zero guard. Take first48-byte collection fromfree sentinel929140,link into active sentinel929170 through40/44,--freeCount9287B8,init polygon-ring32/36 tocollection+4. This helper itself DOES NOT check collection freeCount;514780 caller checks. Follow query ownerDWORD96 ->owner+76 ->ptr+140 ->ptr+4 to mesh record. Iterate U16batchCount(mesh+12),56-byte batches atmesh+8,then U16triangleCount(batch+42),8-byte triangle records atbatch+20. If flagsDWORD168&4,require mesh material-mapDWORD[batchDWORD32] atmesh+32 equals selectorDWORD172. For normal-side admission use ONLY first SIGNED int16 vertex index to fetch batch
// normal-array8+12*index;dot against normalized start-end,roundF32. Ordered negative dot requiresflag1;ordered zero/positive requiresflag2. UNORDERED NaN bypasses BOTH flagrequirements because TESTAH5/JP thenTESTAH1/JNZ;fresh pseudocode is misleading for that case. Read all THREE signed int16 position indices fromtriangle0/2/4 into batch position-array4;no negative/index bounds checks or posed-vertex evaluation. Clip each triangle through513F60;tailappend each successful pooled polygon via28/32 tocollection+4 sentinel. Exhaustion/failure on later triangles does not undo earlier ones;continue all triangles. If>=1 polygon,store rawqueryDWORD100 ascollectionDWORD0(texture),returncollection. Ifnone,unlink activecollection,return it tofree tail,restorecollectionfreeCount andreturnNULL. No geometry deduplication,owner validation,world transforms or renderer submission here.
float *__cdecl rf_mesh_decal_collect_clipped_model_triangles(const float *a1)
{
  float v2[3]; // [esp+0h] [ebp-7Ch] BYREF
  float v3[3]; // [esp+Ch] [ebp-70h] BYREF
  float copy_result[3]; // [esp+18h] [ebp-64h] BYREF
  float *v5; // [esp+24h] [ebp-58h]
  float *v6; // [esp+28h] [ebp-54h]
  int j; // [esp+2Ch] [ebp-50h]
  __int16 *v8; // [esp+30h] [ebp-4Ch]
  float destination[3]; // [esp+34h] [ebp-48h] BYREF
  float v10[3]; // [esp+40h] [ebp-3Ch] BYREF
  float v11[3]; // [esp+4Ch] [ebp-30h] BYREF
  int v12; // [esp+58h] [ebp-24h]
  int i; // [esp+5Ch] [ebp-20h]
  float out_vector[3]; // [esp+60h] [ebp-1Ch] BYREF
  float *v15; // [esp+6Ch] [ebp-10h]
  int v16; // [esp+70h] [ebp-Ch]
  float v17; // [esp+74h] [ebp-8h]
  int v18; // [esp+78h] [ebp-4h]

  rf_vector_construct_no_unwind((char *)destination, 0xCu, 3, rf_vector3_default_construct_noop);
  v18 = 0;
  rf_vector_subtract(a1 + 27, out_vector, a1 + 30);
  rf_vector_normalize_reciprocal_sqrt(out_vector);
  v15 = (float *)unk_929168;
  *(_DWORD *)(*(_DWORD *)(unk_929168 + 44) + 40) = *(_DWORD *)(unk_929168 + 40);
  *(float *)(*((_DWORD *)v15 + 10) + 44) = v15[11];
  v15[10] = 0.0;
  v15[11] = 0.0;
  *((_DWORD *)v15 + 11) = unk_92919C;
  *((_DWORD *)v15 + 10) = &unk_929170;
  *(_DWORD *)(unk_92919C + 40) = v15;
  unk_92919C = v15;
  --unk_9287B8;
  *((_DWORD *)v15 + 8) = v15 + 1;
  *((_DWORD *)v15 + 9) = v15 + 1;
  v16 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*((_DWORD *)a1 + 24) + 76) + 140) + 4);
  for ( i = 0; i < *(unsigned __int16 *)(v16 + 12); ++i )
  {
    v12 = *(_DWORD *)(v16 + 8) + 56 * i;
    for ( j = 0; j < *(unsigned __int16 *)(v12 + 42); ++j )
    {
      v8 = (__int16 *)(*(_DWORD *)(v12 + 20) + 8 * j);
      if ( ((_DWORD)a1[42] & 4) == 0 || *(_DWORD *)(v16 + 4 * *(_DWORD *)(v12 + 32) + 32) == *((_DWORD *)a1 + 43) )
      {
        v5 = (float *)(*(_DWORD *)(v12 + 8) + 12 * *v8);
        v17 = rf_vector_dot(v5, out_vector);
        if ( (v17 >= 0.0 || ((_DWORD)a1[42] & 1) != 0) && (v17 < 0.0 || ((_DWORD)a1[42] & 2) != 0) )
        {
          rf_vector_copy(destination, copy_result, (const float *)(*(_DWORD *)(v12 + 4) + 12 * *v8));
          rf_vector_copy(v10, v3, (const float *)(*(_DWORD *)(v12 + 4) + 12 * v8[1]));
          rf_vector_copy(v11, v2, (const float *)(*(_DWORD *)(v12 + 4) + 12 * v8[2]));
          v6 = rf_mesh_decal_clip_polygon_take_pool_records((int)a1, (int)destination, 3);
          if ( v6 )
          {
            v6[8] = v15[9];
            *((_DWORD *)v6 + 7) = v15 + 1;
            *(_DWORD *)(*((_DWORD *)v15 + 9) + 28) = v6;
            *((_DWORD *)v15 + 9) = v6;
            ++v18;
          }
        }
      }
    }
  }
  if ( v18 > 0 )
  {
    *v15 = a1[25];
    return v15;
  }
  else
  {
    *(float *)(*((_DWORD *)v15 + 11) + 40) = v15[10];
    *(float *)(*((_DWORD *)v15 + 10) + 44) = v15[11];
    v15[10] = 0.0;
    v15[11] = 0.0;
    *((_DWORD *)v15 + 11) = unk_92916C;
    *((_DWORD *)v15 + 10) = &unk_929140;
    *(_DWORD *)(unk_92916C + 40) = v15;
    unk_92916C = v15;
    ++unk_9287B8;
    return nullptr;
  }
}

