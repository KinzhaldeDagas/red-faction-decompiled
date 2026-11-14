// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FE1A0 rf_event_explode_forward
// UNREALRED VERIFIED [event-actions-presentation-continuation-20261027] event_explode forward, vtable0x63E064 slot+4. Optional GeoMod path requires byte+0x2B8 exactly1, builds direction(1,0,0), and only when helper on event+4 returns nonzero calls rf_geomod_operation_admit(radius float+0x2CC,-1,helper_result,event+0x40,direction,0,1). Independently always calls0x448DC0 with event dword+0x2C4, fresh helper(event+4) result,0,event position+0x40,float+0x2CC,float+0x2C8,0. No target traversal or successful-cut requirement before explosion/effect helper.
void __thiscall rf_event_explode_forward(int this)
{
  int first_dword; // eax
  int v2; // eax
  float v3; // [esp+10h] [ebp-20h]
  float v4; // [esp+14h] [ebp-1Ch]
  int v6[3]; // [esp+24h] [ebp-Ch] BYREF

  if ( *(_BYTE *)(this + 696) == 1 )
  {
    rf_vector3_default_construct_noop(v6);
    rf_vector3_set_components_thiscall((float *)v6, 1.0, 0.0, 0.0);
    if ( rf_receiver_get_first_dword((void *)(this + 4)) )
    {
      first_dword = rf_receiver_get_first_dword((void *)(this + 4));
      rf_geomod_operation_admit(*(float *)(this + 716), -1, first_dword, (float *)(this + 64), (float *)v6, 0, 1);
    }
  }
  v4 = *(float *)(this + 712);
  v3 = *(float *)(this + 716);
  v2 = rf_receiver_get_first_dword((void *)(this + 4));
  sub_448DC0(*(_DWORD *)(this + 708), v2, 0, (float *)(this + 64), v3, v4, 0);
}

