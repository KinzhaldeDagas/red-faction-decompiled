// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00527230 rf_renderer_directional_light_create
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, light handle/pool lifecycle,cache generations,active-list filters and trig extent,original ECX/stack flow and PE bytes): Cdecl directionXYZ,intensity,R,G,B,categoryBYTE,flagsDWORD,userDWORD. Allocate slot527340(category), immediately resolve returned handle WITHOUT -1 check, set typeDWORD8=1, copy raw direction to12..20 (no normalization). RGB64/68/72=F32(component*intensity); range60=0 and squaredRange128=0; enabledBYTE76=1,category77=rawBYTE,field144=0,flags80/user84 copied,referenceCounter88=0. Increment serial once; nonzero category calls receiver coverage(mode0), whose type1 path does no coverage. Return handle. Does not initialize every record field, alternate direction92, optional byte78 or cache fields. Allocation failure resolves base-268 and writes there instead of returning cleanly.
int __cdecl rf_renderer_directional_light_create(
        float *source,
        float a2,
        float a3,
        float a4,
        float a5,
        char a6,
        int a7,
        int a8)
{
  float copy_result[3]; // [esp+0h] [ebp-14h] BYREF
  int v10; // [esp+Ch] [ebp-8h]
  int *v11; // [esp+10h] [ebp-4h]

  v10 = rf_renderer_light_allocate(a6);
  v11 = rf_renderer_light_resolve_handle(v10);
  v11[2] = 1;
  rf_vector_copy((float *)v11 + 3, copy_result, source);
  *((float *)v11 + 16) = a3 * a2;
  *((float *)v11 + 17) = a4 * a2;
  *((float *)v11 + 18) = a5 * a2;
  *((float *)v11 + 15) = 0.0;
  *((float *)v11 + 32) = *((float *)v11 + 15) * *((float *)v11 + 15);
  *((_BYTE *)v11 + 76) = 1;
  *((_BYTE *)v11 + 77) = a6;
  v11[36] = 0;
  v11[20] = a7;
  v11[21] = a8;
  v11[22] = 0;
  ++rf_renderer_light_change_serial;
  if ( a6 )
    rf_light_refresh_receiver_coverage((int)v11, 0);
  return v10;
}

