// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00527670 rf_renderer_tube_light_create
// UNREALRED VERIFIED [rfl-light-decode]: Creates a tube light with runtime range max(slot0 - 0.1, 0.1) and authored length from slot 5.
int __cdecl rf_renderer_tube_light_create(
        float *source,
        float *a2,
        float a3,
        float a4,
        float a5,
        float a6,
        float a7,
        char a8,
        int a9,
        int a10)
{
  float v11[3]; // [esp+0h] [ebp-20h] BYREF
  float copy_result[3]; // [esp+Ch] [ebp-14h] BYREF
  int v13; // [esp+18h] [ebp-8h]
  int *v14; // [esp+1Ch] [ebp-4h]

  v13 = rf_renderer_light_allocate(a8);
  v14 = rf_renderer_light_resolve_handle(v13);
  v14[2] = 4;
  rf_vector_copy((float *)v14 + 3, copy_result, source);
  rf_vector_copy((float *)v14 + 6, v11, a2);
  *((float *)v14 + 16) = a5 * a4;
  *((float *)v14 + 17) = a6 * a4;
  *((float *)v14 + 18) = a7 * a4;
  *((float *)v14 + 15) = a3 - 0.1000000014901161;
  if ( *((float *)v14 + 15) <= 0.0 )
    *((float *)v14 + 15) = 0.1;
  *((float *)v14 + 32) = *((float *)v14 + 15) * *((float *)v14 + 15);
  *((_BYTE *)v14 + 76) = 1;
  *((_BYTE *)v14 + 77) = a8;
  v14[36] = 0;
  v14[20] = a9;
  v14[21] = a10;
  v14[22] = 0;
  ++rf_renderer_light_change_serial;
  if ( a8 )
    rf_light_refresh_receiver_coverage((int)v14, 0);
  return v13;
}

