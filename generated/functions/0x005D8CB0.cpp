// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005D8CB0 rf_renderer_queue_visible_indexed_triangle
// UNREALRED VERIFIED [renderer-overlays-20261028]: Arguments triangle record and12-byte positionarray. Indices atrecord+20/+24/+28 select shared48-byte vertexcache0x182ABC8; transforms each worldpoint only when cachebyte+27clear,then setsbyte27=1. Rejects nonzero AND of three outcodes+24. Ensures cached normalrecord+96 via0x5DF900,then camera-facing test0x5818E0(normal,firstposition). Accepted triangle stored at16-byte queueentry0x1CF7C28+16*count,recordpointer+12; key+0=max(cameraZ of threevertices)+61*signedrecordDWORD+32. Clears DWORD+8 and byte+24 of each three external records pointed from triangle+132/+136/+140. Increments queuecount0x1D6D248. No queuecapacity,indexbound,cacheepoch or null-pointer guards; cache reset belongs to caller.
void __cdecl rf_renderer_queue_visible_indexed_triangle(int *a1, int a2)
{
  float v2; // [esp+0h] [ebp-40h]
  float v3; // [esp+4h] [ebp-3Ch]
  float v4; // [esp+8h] [ebp-38h]
  float v5; // [esp+Ch] [ebp-34h]
  float v6; // [esp+10h] [ebp-30h]
  float v7; // [esp+14h] [ebp-2Ch]
  float v8; // [esp+18h] [ebp-28h]
  float v9; // [esp+1Ch] [ebp-24h]
  float *v10[3]; // [esp+20h] [ebp-20h]
  int v11; // [esp+2Ch] [ebp-14h]
  int v12; // [esp+30h] [ebp-10h]
  int v13; // [esp+34h] [ebp-Ch]
  int i; // [esp+38h] [ebp-8h]
  char v15; // [esp+3Dh] [ebp-3h]

  v15 = -1;
  for ( i = 0; i < 3; ++i )
  {
    *(&v11 + i) = (int)&unk_182ABC8 + 48 * a1[i + 5];
    v10[i] = (float *)(a2 + 12 * a1[i + 5]);
    if ( !*(_BYTE *)(*(&v11 + i) + 27) )
    {
      rf_renderer_transform_world_point_backend_wrapper(*(&v11 + i), v10[i]);
      *(_BYTE *)(*(&v11 + i) + 27) = 1;
    }
    v15 &= *(_BYTE *)(*(&v11 + i) + 24);
  }
  if ( !v15 )
  {
    rf_renderer_cache_indexed_triangle_normal((int)a1, a2);
    if ( rf_renderer_plane_faces_camera_backend_wrapper((int)(a1 + 24), v10[0]) )
    {
      unk_1CF7C34[4 * dword_1D6D248] = (int)a1;
      *(_DWORD *)(a1[33] + 8) = 0;
      *(_DWORD *)(a1[34] + 8) = 0;
      *(_DWORD *)(a1[35] + 8) = 0;
      *(_BYTE *)(a1[33] + 24) = 0;
      *(_BYTE *)(a1[34] + 24) = 0;
      *(_BYTE *)(a1[35] + 24) = 0;
      v7 = (double)a1[8] * 61.0 + *(float *)(v11 + 8);
      v8 = (double)a1[8] * 61.0 + *(float *)(v12 + 8);
      v9 = (double)a1[8] * 61.0 + *(float *)(v13 + 8);
      if ( v8 >= (double)v7 )
        v6 = (double)a1[8] * 61.0 + *(float *)(v12 + 8);
      else
        v6 = (double)a1[8] * 61.0 + *(float *)(v11 + 8);
      if ( v9 >= (double)v8 )
        v5 = (double)a1[8] * 61.0 + *(float *)(v13 + 8);
      else
        v5 = (double)a1[8] * 61.0 + *(float *)(v12 + 8);
      if ( v5 >= (double)v6 )
      {
        if ( v9 >= (double)v8 )
          v2 = (double)a1[8] * 61.0 + *(float *)(v13 + 8);
        else
          v2 = (double)a1[8] * 61.0 + *(float *)(v12 + 8);
        v3 = v2;
      }
      else
      {
        if ( v8 >= (double)v7 )
          v4 = (double)a1[8] * 61.0 + *(float *)(v12 + 8);
        else
          v4 = (double)a1[8] * 61.0 + *(float *)(v11 + 8);
        v3 = v4;
      }
      *((float *)&unk_1CF7C28 + 4 * dword_1D6D248++) = v3;
    }
  }
}

