// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F3210 rf_ui_container_set_mask_bitmap
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Args handle,filename for diagnostic. If handle==stored888,no action/no relock. Otherwise unlock old handle if>=0,store new handle,query resolved bitmap dimensions into locals then DISCARD dimensions;lock CPU pixels into object892 with flags local. On lock failure formats bm_lock failure message into260-byte local but does not display/exit;sets handle888=-1,returns this. No explicit clear of pixels892 on failure,no resize of gadget/no stride or pixel-format storage;does not release bitmap asset. Success returns lock helper result;unchanged returns this,so not uniform success API.
unsigned int *__thiscall rf_ui_container_set_mask_bitmap(unsigned int *this, unsigned int a2, const char *a3)
{
  unsigned int *result; // eax
  int v5; // [esp+8h] [ebp-114h] BYREF
  int v6; // [esp+Ch] [ebp-110h] BYREF
  int v7; // [esp+10h] [ebp-10Ch] BYREF
  char Buffer[260]; // [esp+14h] [ebp-108h] BYREF

  result = this;
  if ( a2 != *(this + 222) )
  {
    if ( (*(this + 222) & 0x80000000) == 0 )
      rf_bitmap_unlock_cpu_handle_wrapper(*(this + 222));
    *(this + 222) = a2;
    rf_bitmap_get_resolved_dimensions(*(this + 222), &v6, &v7);
    result = (unsigned int *)rf_bitmap_lock_cpu_pixels_resolved(*(this + 222), this + 223, &v5);
    if ( !result )
    {
      sprintf(Buffer, "bm_lock() failed on bitmap \"%s\"\n", a3);
      *(this + 222) = -1;
      return this;
    }
  }
  return result;
}

