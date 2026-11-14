// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00552CA0 rf_lightmap_atlas_page24_construct_register
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, lightmap clusters, tile mapping, atlas placement, seam blend snapshots, recovered halfplanes and original PE bytes): Thiscall24-byte page,width,height,makeOccupancyByte,optionalRGBPointer. Stores dimensions4/8;RGB24 pointer12 uses supplied pointer directly or operator-new(3*w*h) with NO zero-fill. Creates user bitmap(format literal5,width,height),stores handle16. If makeOccupancy nonzero allocatesw*h bytes at0 and zeroes them;else occupancy=NULL. Stores index20=current global page-array15A7148 count,appends page pointer,returns receiver. No pointer/dimension/overflow/bitmap failure checks;provided pixel pointer not copied or ownership-tagged here. Does not upload/initialize entire bitmap from RGB buffer or create tile descriptor.
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, atlas ownership, lightmap seam lifecycle, selected-face topology, SDK misidentification, x87 return ABI and PE bytes): ADDITIONAL VERIFIED OWNERSHIP:optional supplied RGB pointer is stored directly at+12,without separate ownership bit;552D90 destructor ALWAYS operator-deletes nonNULL+12,including externally supplied pointer. Thus this constructor transfers pixel-buffer cleanup responsibility to page lifetime;makeOccupancy byte controls only optional occupancy-map allocation,not RGB ownership. Earlier constructor/layout findings retained.
int __thiscall rf_lightmap_atlas_page24_construct_register(int this, int a2, int a3, char a4, int a5)
{
  *(_DWORD *)(this + 4) = a2;
  *(_DWORD *)(this + 8) = a3;
  if ( a5 )
    *(_DWORD *)(this + 12) = a5;
  else
    *(_DWORD *)(this + 12) = operator new(3 * *(_DWORD *)(this + 8) * *(_DWORD *)(this + 4));
  *(_DWORD *)(this + 16) = rf_bitmap_create_user_bitmap(5, *(_DWORD *)(this + 4), *(_DWORD *)(this + 8));
  if ( a4 )
  {
    *(_DWORD *)this = operator new(*(_DWORD *)(this + 8) * *(_DWORD *)(this + 4));
    memset(*(void **)this, 0, *(_DWORD *)(this + 8) * *(_DWORD *)(this + 4));
  }
  else
  {
    *(_DWORD *)this = 0;
  }
  *(_DWORD *)(this + 20) = rf_receiver_get_first_dword(unk_15A7148);
  rf_pointer_array_append_dword(unk_15A7148, this);
  return this;
}

