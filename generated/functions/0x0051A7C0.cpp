// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051A7C0 rf_geomod_face_edge_split_insert_vertex
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, shared-edge insertion,component classification/extraction,finite epsilon tests,original ECX/stack flow and PE bytes): Four stack arguments face,A,B,split vertex; RET16. ECX is saved but not used semantically. Skip if face already contains split pointer, or face metadata bit8 boolean differs from the all-incident-faces-bit8 predicate of endpoint A. Walk ORIGINAL circular corners using saved next, matching A->B or B->A pointer identity, never geometric collinearity. On first match compute t=float(distance(split,A)/distance(B,A)), except ORDERED split distance below epsilon gives0, and otherwise ORDERED edge distance below epsilon gives1; unordered comparisons take the division path rather than these below-epsilon fallbacks; epsilon is PE double0.00009999999747378752. No clamp/projection/segment test here. Insert a newly
// allocated28-byte corner between current and next, set vertex pointer, append face uniquely to split vertex incidence32. Interpolate corner floats4,8,12,16 with t for forward edges and1-t for reverse, storing F32. Continue over all original matching edges. After traversal, if face DWORD40 has0x200000 set OR0x80000 even when no edge matched. No plane/AABB/finalization call. Existing char return is AL residue (may face pointer low byte or flag-test result), not reliable insertion-success boolean.
char __stdcall rf_geomod_face_edge_split_insert_vertex(_DWORD *a1, float *a2, float *a3, float *a4)
{
  int v4; // eax
  double v5; // st7
  int v7; // [esp+0h] [ebp-3Ch]
  float v8; // [esp+8h] [ebp-34h]
  float v9; // [esp+Ch] [ebp-30h]
  float v10; // [esp+10h] [ebp-2Ch]
  float v11; // [esp+14h] [ebp-28h]
  int v12; // [esp+18h] [ebp-24h]
  float v13; // [esp+1Ch] [ebp-20h]
  float v14; // [esp+20h] [ebp-1Ch]
  char v15; // [esp+2Ah] [ebp-12h]
  char v16; // [esp+2Bh] [ebp-11h]
  int v17; // [esp+2Ch] [ebp-10h]
  float v18; // [esp+30h] [ebp-Ch]
  unsigned __int8 have_flag8; // [esp+37h] [ebp-5h]
  int v20; // [esp+38h] [ebp-4h]

  LOBYTE(v4) = rf_geomod_face_contains_shared_vertex(a1, (int)a4);
  if ( !(_BYTE)v4 )
  {
    have_flag8 = rf_vertex_all_incident_faces_have_flag8((int)a2);
    LOBYTE(v4) = rf_face_metadata_has_flag8(a1 + 10);
    if ( (unsigned __int8)v4 == have_flag8 )
    {
      v17 = a1[16];
      v20 = 0;
      v18 = 0.0;
      while ( v17 )
      {
        if ( *(_DWORD *)(v17 + 20) == a1[16] )
          v7 = 0;
        else
          v7 = *(_DWORD *)(v17 + 20);
        v15 = 0;
        v16 = 0;
        if ( *(float **)v17 == a2 && **(float ***)(v17 + 20) == a3 )
        {
          v15 = 1;
          v16 = 0;
        }
        else if ( *(float **)v17 == a3 && **(float ***)(v17 + 20) == a2 )
        {
          v15 = 1;
          v16 = 1;
        }
        if ( v15 )
        {
          if ( !v20 )
          {
            v9 = rf_vector_distance(a4, a2);
            v8 = rf_vector_distance(a3, a2);
            if ( v9 >= 0.00009999999747378752 )
            {
              if ( v8 >= 0.00009999999747378752 )
                v18 = v9 / v8;
              else
                v18 = 1.0;
            }
            else
            {
              v18 = 0.0;
            }
          }
          ++v20;
          v11 = *(float *)(*(_DWORD *)(v17 + 20) + 4);
          v14 = *(float *)(*(_DWORD *)(v17 + 20) + 8);
          v10 = *(float *)(*(_DWORD *)(v17 + 20) + 12);
          v13 = *(float *)(*(_DWORD *)(v17 + 20) + 16);
          v12 = rf_geomod_corner_allocate();
          *(_DWORD *)(v12 + 20) = *(_DWORD *)(v17 + 20);
          *(_DWORD *)(v12 + 24) = v17;
          *(_DWORD *)(*(_DWORD *)(v17 + 20) + 24) = v12;
          *(_DWORD *)(v17 + 20) = v12;
          rf_pointer_array_append_unique((_DWORD *)a4 + 8, (int)a1);
          *(_DWORD *)v12 = a4;
          if ( v16 )
          {
            *(float *)(v12 + 4) = (v11 - *(float *)(v17 + 4)) * (1.0 - v18) + *(float *)(v17 + 4);
            *(float *)(v12 + 8) = (v14 - *(float *)(v17 + 8)) * (1.0 - v18) + *(float *)(v17 + 8);
            *(float *)(v12 + 12) = (v10 - *(float *)(v17 + 12)) * (1.0 - v18) + *(float *)(v17 + 12);
            v5 = (v13 - *(float *)(v17 + 16)) * (1.0 - v18) + *(float *)(v17 + 16);
          }
          else
          {
            *(float *)(v12 + 4) = (v11 - *(float *)(v17 + 4)) * v18 + *(float *)(v17 + 4);
            *(float *)(v12 + 8) = (v14 - *(float *)(v17 + 8)) * v18 + *(float *)(v17 + 8);
            *(float *)(v12 + 12) = (v10 - *(float *)(v17 + 12)) * v18 + *(float *)(v17 + 12);
            v5 = (v13 - *(float *)(v17 + 16)) * v18 + *(float *)(v17 + 16);
          }
          *(float *)(v12 + 16) = v5;
        }
        v17 = v7;
      }
      v4 = a1[10] & 0x200000;
      if ( v4 )
      {
        a1[10] |= 0x80000u;
        LOBYTE(v4) = (_BYTE)a1;
      }
    }
  }
  return v4;
}

