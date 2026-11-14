// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00539450 rf_world_face_sample_lightmap_rgb555
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, UV descriptors and rebasing, lightmap sampling, array capacity/ownership, liquid fallback and original PE bytes): Thiscall world,outputRGBA DWORD,face,worldPoint. Starts opaque white. If signed face lightmap index+54>=0,looks up world array+192,computes normalized UV through5378D0,converts width*U,height*V to integers by truncation. Locks bitmap handle at imageHeader+16;successful lock reads WORD at pixels(lockDescriptor+12)+pitchBytes(+24)*y+2*x. Decodes RGB555 channels bits10..14,5..9,0..4,multiplies each by8 (max248,no bit replication),alpha255,ignores bit15,unlocks. Missing lightmap/lock failure returns white. Does not verify bitmap format or clamp x/y to dimension-1;helper inclusiveUV1 can yield x==width/y==height and sample outside intended pixel rectangle. No interpolation/wrap or stream access;returns output
// pointer.
_DWORD *__thiscall rf_world_face_sample_lightmap_rgb555(_DWORD *this, _DWORD *a2, int a3, char *a4)
{
  unsigned __int16 v6; // [esp+8h] [ebp-44h]
  unsigned int v7[8]; // [esp+14h] [ebp-38h] BYREF
  int v8; // [esp+34h] [ebp-18h]
  int v9; // [esp+38h] [ebp-14h]
  float v10; // [esp+3Ch] [ebp-10h] BYREF
  float v11; // [esp+40h] [ebp-Ch] BYREF
  int v12; // [esp+44h] [ebp-8h]
  int v13; // [esp+48h] [ebp-4h] BYREF

  rf_rgba8_construct_components_return_self(&v13, 255, 255, 255, 255);
  if ( *(__int16 *)(a3 + 54) >= 0 )
  {
    v9 = *(_DWORD *)sub_552200(this + 48, *(__int16 *)(a3 + 54));
    rf_lightmap_point_to_clamped_uv(v9, a4, &v10, &v11);
    v8 = (int)((double)*(int *)(*(_DWORD *)(v9 + 12) + 4) * v10);
    v12 = (int)((double)*(int *)(*(_DWORD *)(v9 + 12) + 8) * v11);
    if ( rf_bitmap_lock_pixels_backend_dispatch(*(_DWORD *)(*(_DWORD *)(v9 + 12) + 16), 0, (int)v7, 0) )
    {
      v6 = *(_WORD *)(v7[3] + v7[6] * v12 + 2 * v8);
      rf_color4_set_bytes_return_destination(
        &v13,
        8 * (((int)v6 >> 10) & 0x1F),
        8 * (((int)v6 >> 5) & 0x1F),
        8 * (v6 & 0x1F),
        255);
      rf_bitmap_unlock_pixels_backend_dispatch(v7);
    }
  }
  *a2 = v13;
  return a2;
}

