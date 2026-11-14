// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00552F40 rf_lightmap_atlas_page_scalar_deleting_destructor
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, atlas ownership, lightmap seam lifecycle, selected-face topology, SDK misidentification, x87 return ABI and PE bytes): Destroys page resources via552D90,optionally operator-deletes receiver when flags01,returns original receiver address(possibly freed). Other flag bits ignored,no vector cookie handling. Global atlas registry entry not erased here.
void *__thiscall rf_lightmap_atlas_page_scalar_deleting_destructor(void *this, char a2)
{
  rf_lightmap_atlas_page_destroy_resources((int)this);
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}

