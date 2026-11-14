// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F3310 rf_ui_container_sample_region_mask
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): No pixels892 ->-1. Converts screen x/y to local by subtracting gadget absolute coordinates. Within half-open bounds width20,height24,returns unsigned BYTE pixels[localX+width*localY],else-1. Uses GADGET WIDTH as row stride,not resolved bitmap dimensions;no mask format/size agreement check,so mismatched bitmap can misindex. Zero is a valid sampled region byte;no allocation or lock here.
int __thiscall rf_ui_container_sample_region_mask(_DWORD *this, int a2, int a3)
{
  int v5; // [esp+14h] [ebp+8h]
  int v6; // [esp+18h] [ebp+Ch]

  if ( !*(this + 223) )
    return -1;
  v5 = a2 - rf_ui_gadget_absolute_x(this, 0);
  v6 = a3 - rf_ui_gadget_absolute_y(this, 0);
  if ( v5 >= 0 && v6 >= 0 && v5 < *(this + 5) && v6 < *(this + 6) )
    return *(unsigned __int8 *)(*(this + 223) + v5 + *(this + 5) * v6);
  else
    return -1;
}

