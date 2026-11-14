// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00573590 rf_renderer_draw_face_multipass_backend_dispatch
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, fog output widths, channel-sum color filtering, backend dispatch, byte/int return distinctions and context startup): cdecl six32bit words(context,face,packedState,baseBitmap,lightmapBitmap,combinedOutcode),returnsBYTE. Only selector102 forwards all six unchanged to5D49F0 multipass face renderer and returns itsAL. Selector104 and default returnAL0 with no rendering. Does not perform own portal/clip/vertex/channel-capacity/readiness checks or mutate arguments before delegation;upper24EAX bits not a semantic result.
unsigned __int8 __cdecl rf_renderer_draw_face_multipass_backend_dispatch(
        int context,
        int face,
        unsigned int packed_state,
        unsigned int base_bitmap,
        unsigned int lightmap_bitmap,
        unsigned int combined_outcode)
{
  if ( dword_187CC9C == 102 )
    return rf_renderer_draw_face_multipass_backend_102(
             context,
             face,
             packed_state,
             base_bitmap,
             lightmap_bitmap,
             combined_outcode);
  else
    return 0;
}

