// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C91F0 rf_material_texture_slot_frame_from_normalized_phase
// UNREALRED VERIFIED [renderer-lighting-20261028]: Texture slot this: handle+0,frameoffsetDWORD+40,modeDWORD+48. Negativehandle returns-1. Queries animationframecount and metadata; count1 returns originalhandle. Else frame=floor(count*phase)-offset. Modes0/2 modulo only when frame>=count; mode1 clamps high tocount-1; othermodes skip that switch. Negativeframe adds count ONCE,then final clamp0..count-1. Returns basehandle+frame+1. Phase not clamped0..1; large negativeoffset/phase can clamp ratherthan wrap. No zero-framecount guard before modulo. Returned metadatafloat not used.
unsigned int __thiscall rf_material_texture_slot_frame_from_normalized_phase(unsigned int *this, float a2)
{
  int v3; // [esp+4h] [ebp-18h]
  float value; // [esp+8h] [ebp-14h]
  int v6; // [esp+10h] [ebp-Ch]
  signed int v7; // [esp+14h] [ebp-8h]
  float v8; // [esp+18h] [ebp-4h] BYREF

  if ( (*this & 0x80000000) != 0 )
    return -1;
  v6 = rf_bitmap_animation_metadata_query(*this, &v8);
  if ( v6 == 1 )
    return *this;
  value = (double)v6 * a2;
  v7 = (int)rf_floor_float(value) - *(this + 10);
  v3 = *(this + 12);
  switch ( v3 )
  {
    case 0:
      goto LABEL_8;
    case 1:
      if ( v7 >= v6 )
        v7 = v6 - 1;
      break;
    case 2:
LABEL_8:
      if ( v7 >= v6 )
        v7 %= v6;
      break;
  }
  if ( v7 < 0 )
    v7 += v6;
  if ( v7 >= 0 )
  {
    if ( v7 >= v6 )
      v7 = v6 - 1;
  }
  else
  {
    v7 = 0;
  }
  return *this + v7 + 1;
}

