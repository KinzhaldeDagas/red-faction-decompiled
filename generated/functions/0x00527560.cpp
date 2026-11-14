// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00527560 rf_renderer_spot_light_create
// VERIFIED: Renderer spot-light creation. The final optional byte argument is stored at renderer +0x4E; the non-world spot contribution helper squares its angular interpolation factor only when this byte is nonzero.
// UNREALRED VERIFIED [rfl-light-decode]: Creates a spot light; the optional record byte selects squared versus linear non-world angular contribution.
int __cdecl rf_renderer_spot_light_create(
        float *source,
        float *a2,
        float a3,
        float a4,
        float a5,
        float a6,
        float a7,
        float a8,
        float a9,
        char a10,
        int a11,
        float a12,
        int a13,
        char a14)
{
  float v15[3]; // [esp+8h] [ebp-20h] BYREF
  float copy_result[3]; // [esp+14h] [ebp-14h] BYREF
  int v17; // [esp+20h] [ebp-8h]
  int *v18; // [esp+24h] [ebp-4h]

  v17 = rf_renderer_light_allocate(a10);
  v18 = rf_renderer_light_resolve_handle(v17);
  v18[2] = 3;
  rf_vector_copy((float *)v18 + 3, copy_result, source);
  rf_vector_copy((float *)v18 + 9, v15, a2);
  *((float *)v18 + 16) = a7 * a6;
  *((float *)v18 + 17) = a8 * a6;
  *((float *)v18 + 18) = a9 * a6;
  *((float *)v18 + 15) = a5;
  *((float *)v18 + 32) = *((float *)v18 + 15) * *((float *)v18 + 15);
  *((_BYTE *)v18 + 76) = 1;
  *((_BYTE *)v18 + 77) = a10;
  v18[36] = 0;
  v18[20] = a11;
  *((float *)v18 + 14) = a12;
  v18[21] = a13;
  *((_BYTE *)v18 + 78) = a14;
  *((float *)v18 + 12) = 0.0;
  v18[22] = 0;
  rf_spot_light_set_cone_angles(v17, a3, a4);
  return v17;
}

