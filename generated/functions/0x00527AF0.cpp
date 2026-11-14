// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00527AF0 rf_renderer_light_recompute_scaled_rgb
// VERIFIED: Multiplies the authored RGB channels by a scalar, stores renderer RGB at +0x40..+0x48, and invalidates/relinks light spatial selection.
// UNREALRED VERIFIED [rfl-light-decode]: Recomputes runtime RGB from authored RGB times scalar, then invalidates and relinks affected caches.
int __cdecl rf_renderer_light_recompute_scaled_rgb(int a1, float a2, float a3, float a4, float a5)
{
  int *v6; // [esp+0h] [ebp-4h]

  v6 = rf_renderer_light_resolve_handle(a1);
  *((float *)v6 + 16) = a3 * a2;
  *((float *)v6 + 17) = a4 * a2;
  *((float *)v6 + 18) = a5 * a2;
  if ( *((_BYTE *)v6 + 77) )
    return rf_light_refresh_receiver_coverage((int)v6, 0);
  return ++rf_renderer_light_change_serial;
}

