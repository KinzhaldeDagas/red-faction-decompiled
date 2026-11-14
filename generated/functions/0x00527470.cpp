// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00527470 rf_renderer_point_light_create
// UNREALRED VERIFIED [rfl-light-decode]: Creates a finite-range point light with scaled RGB and cached range squared.
// VERIFIED [transient-projectile-light]: Creates type-2 record: position +0x0C, range +0x3C and square +0x80, RGB*scalar +0x40/+0x44/+0x48, enabled +0x4C, category byte +0x4D, opaque caller value +0x50, attenuation selector +0x54, and release counter +0x58=0. Increments serial 0x00D035E0 and invokes category receiver-coverage refresh. Projectile creation passes category=1, +0x50=1, +0x54=0.
int __cdecl rf_renderer_point_light_create(
        float *source,
        float a2,
        float a3,
        float a4,
        float a5,
        float a6,
        char a7,
        int a8,
        int a9)
{
  float copy_result[3]; // [esp+0h] [ebp-14h] BYREF
  int v11; // [esp+Ch] [ebp-8h]
  int *v12; // [esp+10h] [ebp-4h]

  v11 = rf_renderer_light_allocate(a7);
  v12 = rf_renderer_light_resolve_handle(v11);
  v12[2] = 2;
  rf_vector_copy((float *)v12 + 3, copy_result, source);
  *((float *)v12 + 16) = a4 * a3;
  *((float *)v12 + 17) = a5 * a3;
  *((float *)v12 + 18) = a6 * a3;
  *((float *)v12 + 15) = a2;
  *((float *)v12 + 32) = *((float *)v12 + 15) * *((float *)v12 + 15);
  *((_BYTE *)v12 + 76) = 1;
  *((_BYTE *)v12 + 77) = a7;
  v12[36] = 0;
  v12[20] = a8;
  v12[21] = a9;
  v12[22] = 0;
  ++rf_renderer_light_change_serial;
  if ( a7 )
    rf_light_refresh_receiver_coverage((int)v12, 0);
  return v11;
}

