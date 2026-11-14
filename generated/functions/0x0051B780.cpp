// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051B780 rf_geomod_debris_split_components_classify
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, shared-edge insertion,component classification/extraction,finite epsilon tests,original ECX/stack flow and PE bytes): Thiscall solid no stack args; clears vertex BYTE28 visited and all solid face labels44=-1. Empty face-list count returns0. Allocate4*facecount scratch (overflow sizeFFFFFFFF), without NULL test. In solid face-list order DFS every unlabeled face through circular corners and reciprocal vertex incidence32, mark each vertex once; assign sequential labels0..count-1 when first enqueued so each face pushed once. Shared vertex identity establishes connectivity even without a shared edge. No eligibility bit/portal filter, room requirement, sky exclusion, largest-component retention, shell validation or geometry extraction. Frees scratch, returns ALL component count including sole component1. Leaves labels and
// vertex visited marks.
int __thiscall rf_geomod_debris_split_components_classify(int this)
{
  int v2; // eax
  _DWORD *v3; // [esp+0h] [ebp-4Ch]
  int v5; // [esp+10h] [ebp-3Ch]
  int n; // [esp+14h] [ebp-38h]
  int v7; // [esp+18h] [ebp-34h]
  int v8; // [esp+1Ch] [ebp-30h]
  _DWORD *m; // [esp+20h] [ebp-2Ch]
  int v10; // [esp+24h] [ebp-28h]
  int v11; // [esp+28h] [ebp-24h]
  int v12; // [esp+2Ch] [ebp-20h]
  int *v13; // [esp+34h] [ebp-18h]
  int v14; // [esp+38h] [ebp-14h]
  int v15; // [esp+3Ch] [ebp-10h]
  int first_dword; // [esp+40h] [ebp-Ch]
  int j; // [esp+44h] [ebp-8h]
  int k; // [esp+44h] [ebp-8h]
  int i; // [esp+48h] [ebp-4h]

  first_dword = rf_receiver_get_first_dword((void *)(this + 120));
  for ( i = 0; i < first_dword; ++i )
    *(_BYTE *)(*(_DWORD *)sub_552200((_DWORD *)(this + 120), i) + 28) = 0;
  for ( j = rf_receiver_get_first_dword((void *)(this + 112)); j; j = rf_solid_face_next_link(j) )
    *(_DWORD *)(j + 44) = -1;
  v15 = 0;
  v14 = rf_shared_second_dword_getter_518050((_DWORD *)(this + 112));
  if ( !v14 )
    return 0;
  v13 = (int *)operator new(4 * v14);
  for ( k = rf_receiver_get_first_dword((void *)(this + 112)); k; k = rf_solid_face_next_link(k) )
  {
    if ( *(_DWORD *)(k + 44) == -1 )
    {
      v11 = 1;
      *(_DWORD *)(k + 44) = v15++;
      v12 = 0;
      *v13 = k;
      while ( v12 > -1 )
      {
        v10 = v13[v12--];
        for ( m = *(_DWORD **)(v10 + 64); m; m = v3 )
        {
          v8 = *m;
          if ( !*(_BYTE *)(*m + 28) )
          {
            *(_BYTE *)(v8 + 28) = 1;
            v7 = rf_receiver_get_first_dword((void *)(v8 + 32));
            for ( n = 0; n < v7; ++n )
            {
              v2 = sub_552200((_DWORD *)(v8 + 32), n);
              v5 = *(_DWORD *)v2;
              if ( *(_DWORD *)(*(_DWORD *)v2 + 44) == -1 )
              {
                *(_DWORD *)(v5 + 44) = *(_DWORD *)(k + 44);
                ++v11;
                v13[++v12] = v5;
              }
            }
          }
          if ( m[5] == *(_DWORD *)(v10 + 64) )
            v3 = nullptr;
          else
            v3 = (_DWORD *)m[5];
        }
      }
    }
  }
  operator delete(v13);
  return v15;
}

