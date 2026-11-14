// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051E0E0 rf_solid_split_faces_by_plane
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, plane splits,intrusive face lists,room/portal visibility,clip apertures and decal submission,original ECX/stack flow and PE bytes): Thiscall solid,plane RET4 no return value. Lazy guard global92EA30 mask0x1 constructs128 records at92DE30 stride24 with no-op constructor51EA00; guard set BEFORE construction, SEH clears bit on construction failure. Shared nonreentrant workspace. First scan solid face-list112: require56BA70 plane-intersection line success; reset record count0 and call5339B0(face,lowIndex,highIndex,plane,line,count,128,workspace). Queue unique face pointers when returned class is neither0 nor1 (normal values2/3), without mutating source during candidate collection. Second scan queue recomputes line but IGNORES its success byte, resets count0 and reclassifies; only classEXACT3 executes split. Build local
// array of pointers to24-byte records in emitted order, NO sort/dedup here. For each record with otherEndpoint4 nonNULL allocate44-byte vertex from recordXYZ8 into solid120, propagate insertion through common endpoint incidence51AAA0, then replace record vertex0 with new and other4=NULL. Call534120 using reported low/high indexes and record-pointer array; ignore split return and output children, unconditionally destroy original via51A090 flag0. No UV rebase, bounds/room-tree rebuild or rollback. Temporary candidate backing destroyed with SEH cleanup. Child validity and room/spatial linkage handled by splitter; no retry-to-stability loop here.
void __thiscall rf_solid_split_faces_by_plane(int *this, float *a2)
{
  int first_dword; // eax
  float *v4; // [esp+8h] [ebp-28Ch]
  int v5; // [esp+Ch] [ebp-288h] BYREF
  _DWORD v6[129]; // [esp+10h] [ebp-284h] BYREF
  int v7; // [esp+214h] [ebp-80h] BYREF
  int v8; // [esp+218h] [ebp-7Ch] BYREF
  float v9[6]; // [esp+21Ch] [ebp-78h] BYREF
  int v10; // [esp+234h] [ebp-60h] BYREF
  int v11; // [esp+238h] [ebp-5Ch]
  int v12; // [esp+23Ch] [ebp-58h] BYREF
  char v13; // [esp+243h] [ebp-51h]
  int k; // [esp+244h] [ebp-50h]
  int j; // [esp+248h] [ebp-4Ch]
  int v16; // [esp+24Ch] [ebp-48h] BYREF
  float v17[6]; // [esp+250h] [ebp-44h] BYREF
  int v18; // [esp+268h] [ebp-2Ch] BYREF
  unsigned int v19; // [esp+26Ch] [ebp-28h]
  int v20; // [esp+270h] [ebp-24h] BYREF
  float *i; // [esp+278h] [ebp-1Ch]
  void *v23[3]; // [esp+27Ch] [ebp-18h] BYREF
  int v24; // [esp+290h] [ebp-4h]

  if ( (dword_92EA30[0] & 1) == 0 )
  {
    dword_92EA30[0] |= 1u;
    rf_vector_construct_no_unwind(
      unk_92DE30,
      0x18u,
      128,
      (void *(__thiscall *)(void *))rf_geomod_intersection24_construct_noop);
    v24 = -1;
  }
  rf_dword_array_construct_capacity(v23, 0);
  v24 = 1;
  for ( i = (float *)rf_receiver_get_first_dword(this + 28); i; i = (float *)rf_solid_face_next_link((int)i) )
  {
    rf_force_sample44_construct_vectors_noop((char *)v17);
    if ( sub_56BA70(i, a2, v17) )
    {
      v18 = 0;
      v19 = sub_5339B0(i, &v20, &v16, (int)a2, (int)v17, &v18, 128, (int)unk_92DE30);
      if ( v19 > 1 )
        rf_pointer_array_append_unique(v23, (int)i);
    }
  }
  for ( j = 0; ; ++j )
  {
    first_dword = rf_receiver_get_first_dword(v23);
    if ( j >= first_dword )
      break;
    i = *(float **)sub_552200(v23, j);
    rf_force_sample44_construct_vectors_noop((char *)v9);
    v13 = sub_56BA70(i, a2, v9);
    v10 = 0;
    v11 = sub_5339B0(i, &v12, &v8, (int)a2, (int)v9, &v10, 128, (int)unk_92DE30);
    if ( v11 == 3 )
    {
      for ( k = 0; k < v10; ++k )
        v6[k] = &unk_92DE30[24 * k];
      for ( k = 0; k < v10; ++k )
      {
        if ( *(_DWORD *)(v6[k] + 4) )
        {
          v4 = rf_solid_vertex_copy_append(this, (float *)(v6[k] + 8));
          rf_geomod_split_vertex_propagate_to_incident_faces(*(float **)v6[k], *(float **)(v6[k] + 4), v4);
          *(_DWORD *)v6[k] = v4;
          *(_DWORD *)(v6[k] + 4) = 0;
        }
      }
      rf_geomod_face_split_between_intersection_vertices((int)i, (int)this, v12, v8, (int)v6, &v5, &v7);
      rf_solid_face_remove_destroy(this, i, 0);
    }
  }
  v24 = -1;
  rf_pointer_array_destroy_backing_storage(v23);
}

